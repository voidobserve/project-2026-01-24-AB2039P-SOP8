#include "include.h"
#include "tbox_key.h"
#include "tbox_voice.h"
#include "api_sysclk.h"
#include "prod_test_tbox.h"

#if (FUNC_TBOX_EN && PROD_TEST_MIC_EN)
#include "tbox_voice_saradc.h"
#include "api_ring_buf.h"

#define VOICE_TEST_AUTO_START_DELAY  1000  //1s

static tbox_voice_var_t tbox_voice_var AT(.tbox.var);
static ring_buf_t tbox_voice_ring_buf AT(.tbox.ring_buf);

AT(.text.app.tbox.var_init)
static void tbox_voice_var_init(void)
{
    memset(&tbox_voice_var, 0, sizeof(tbox_voice_var_t));
#if (!PROD_TEST_KEY_EN)    
    tbox_voice_var.auto_start_flag = 1;
#endif  //(!PROD_TEST_KEY_EN)
}

AT(.text.app.proc.ble)
static uint32_t tbox_voice_dequeue_enc_buf_proc(uint8_t *buffer, uint32_t size)
{
    return ring_buf_read(&saradc_enc_ring_buf, buffer, size);
}

AT(.text.app.proc.ble)
static int16_t tbox_voice_notify_for_handle(uint16_t att_handle, uint8_t *data, uint16_t data_size)
{
    if (!tbox_var.voice_client_config) {
        printf("[err] %s, clien config err!\n", __func__);
        return -1;
    }

    int16_t ret = ble_notify_for_handle_kick(tbox_var.conn_handle, att_handle, data, data_size, TXPKT_KICK_ENABLE);
    // printf("ret = 0x%x\n", ret);
    return ret;
}

AT(.text.app.proc.ble)
static void tbox_voice_data_notify_do(void)
{
    uint8_t enc_buf[TBOX_VOICE_ENC_DATA_LEN];

    if (txpkt_get_available_len() < TBOX_VOICE_ENC_DATA_LEN) {
        return;
    }

    uint32_t enc_len = tbox_voice_dequeue_enc_buf_proc(enc_buf, TBOX_VOICE_ENC_DATA_LEN);

    if (enc_len != TBOX_VOICE_ENC_DATA_LEN) {
        return;
    }
    
    //AUDIO PACKET
    tbox_voice_notify_for_handle(ATT_CHARACTERISTIC_8002_01_VALUE_HANDLE, (uint8_t *)enc_buf, TBOX_VOICE_ENC_DATA_LEN);
}

AT(.text.app.proc.ble)
static void tbox_voice_data_notify_process(void)
{
    if (tbox_voice_var.voice_status != VOICE_STATUS_START) {
        return;
    }

    tbox_voice_data_notify_do();
}

AT(.text.prod_test.voice_start)
static void tbox_voice_start(void)
{
    if (tbox_voice_var.voice_status == VOICE_STATUS_START) { //防重开
        return;
    }
    printf("tbox voice start\n");
    
	ble_disable_latency(tbox_var.conn_handle);
    tbox_voice_var.voice_status = VOICE_STATUS_START;
    tbox_voice_var.exit_clk = sys_clk_get();
    sys_clk_set(SYS_120M);
    adpcm_sample_idx_reset();
    txpkt_free_for_handle(tbox_var.conn_handle);
    tbox_voice_saradc_start();
}

AT(.text.prod_test.voice_stop)
void tbox_voice_stop(void)
{
    if (tbox_voice_var.voice_status == VOICE_STATUS_STOP) {
        return;
    }

    printf("tbox voice stop\n");
    tbox_voice_var.voice_status = VOICE_STATUS_STOP;
    sys_clk_set(tbox_voice_var.exit_clk);
    tbox_voice_saradc_stop();
    ring_buf_clear(&tbox_voice_ring_buf);
}

AT(.text.app.proc.tbox_voice_proc)
void tbox_voice_proc(void)
{
    if (tbox_var.conn_handle == 0) {
        return;
    }
#if (PROD_TEST_KEY_EN)
    uint8_t tbox_key_msg = tbox_get_key_msg();
    if (tbox_key_msg == TBOX_KEY_MSG_VOICE_ON_TEST) {
        tbox_set_key_msg(TBOX_KEY_MSG_NONE);
        tbox_voice_start();
    } else if (tbox_key_msg == TBOX_KEY_MSG_VOICE_OFF_TEST) {
        tbox_set_key_msg(TBOX_KEY_MSG_NONE);
        tbox_voice_stop();
    }
#else
    if (tbox_voice_var.auto_start_flag && tick_check_expire(tbox_voice_var.tick, VOICE_TEST_AUTO_START_DELAY)) {
        tbox_voice_var.auto_start_flag = 0;
        tbox_voice_start();
    }
#endif  //(PROD_TEST_KEY_EN)

    tbox_voice_data_notify_process();
}

AT(.text.prod_test.voice_init)
void tbox_voice_init(void)
{
    tbox_voice_var_init();
    tbox_voice_saradc_init();
#if (!PROD_TEST_KEY_EN)    
    tbox_voice_var.tick = tick_get();
#endif  //(!PROD_TEST_KEY_EN)   
}

#endif //(FUNC_TBOX_EN && PROD_TEST_MIC_EN)
