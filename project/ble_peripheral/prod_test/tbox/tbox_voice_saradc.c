#include "include.h"
#include "tbox_voice_saradc.h"
#include "driver_gpio.h"
#include "api_modules.h"

#if (FUNC_TBOX_EN && PROD_TEST_MIC_EN)
#include "api_ring_buf.h"
#include "driver_saradc.h"

#define SARADC_MIC_BUF_LEN   (512+2)      //DMA样点数
#define ENC_OUTPUT_SIZE      (4+128)      //压缩后byte数，2byte presample + 1byte index + 1byte reserve + 128byte 偏差值
#define SARADC_SPR           SARADC_MIC_MIC_SR_8K  //采样率
#define SARADC_BUF_CNT       5           //5包缓存
#define SARADC_SKIP_FRAME    25          //丢弃mic刚启动时的不稳定数据

static int16_t saradc_mic_dma_buf[SARADC_MIC_BUF_LEN] AT(.tbox.voice_enc_obuf);
static uint8_t saradc_enc_buf[ENC_OUTPUT_SIZE * SARADC_BUF_CNT] AT(.tbox.voice_enc_buf);
static uint8_t saradc_skip_frame = SARADC_SKIP_FRAME;
ring_buf_t saradc_enc_ring_buf;

AT(.com_text.saradc.isr)
void tbox_voice_saradc_isr(void)
{
    uint8_t enc_output_buf[ENC_OUTPUT_SIZE];

    if (saradc_skip_frame) {
        saradc_skip_frame--;
        if (saradc_get_flag(SARADC_MIC_DMA_ALL_DONE) != RESET) {
            saradc_clear_flag(SARADC_MIC_DMA_ALL_DONE);
        } else if (saradc_get_flag(SARADC_MIC_DMA_HALF_DONE) != RESET) {
            saradc_clear_flag(SARADC_MIC_DMA_HALF_DONE);
        }
        return;
    }

    if (saradc_get_flag(SARADC_MIC_DMA_ALL_DONE) != RESET) {
        saradc_clear_flag(SARADC_MIC_DMA_ALL_DONE);
        for (int i = (SARADC_MIC_BUF_LEN/2); i<(SARADC_MIC_BUF_LEN); i++) {
            audio_mic_dc_filter(&saradc_mic_dma_buf[i]);
        }

#if NOTCH_IIR_EN
        notch_iir_process(&saradc_mic_dma_buf[SARADC_MIC_BUF_LEN/2]);
        notch_iir_process(&saradc_mic_dma_buf[(SARADC_MIC_BUF_LEN/2)+128]);
#endif  //NOTCH_IIR_EN

        adpcm_encode_block_big((uint8_t *)enc_output_buf, (uint8_t *)&saradc_mic_dma_buf[SARADC_MIC_BUF_LEN/2], SARADC_MIC_BUF_LEN/2);
        ring_buf_write(&saradc_enc_ring_buf, (uint8_t *)enc_output_buf, ENC_OUTPUT_SIZE);
    } else if (saradc_get_flag(SARADC_MIC_DMA_HALF_DONE) != RESET) {
        saradc_clear_flag(SARADC_MIC_DMA_HALF_DONE);
        for (int i = 0; i<(SARADC_MIC_BUF_LEN/2); i++) {
            audio_mic_dc_filter(&saradc_mic_dma_buf[i]);
        }

#if NOTCH_IIR_EN
        notch_iir_process(&saradc_mic_dma_buf[0]);
        notch_iir_process(&saradc_mic_dma_buf[128]);
#endif  //NOTCH_IIR_EN

        adpcm_encode_block_big((uint8_t *)enc_output_buf, (uint8_t *)saradc_mic_dma_buf, SARADC_MIC_BUF_LEN/2);
        ring_buf_write(&saradc_enc_ring_buf, (uint8_t *)enc_output_buf, ENC_OUTPUT_SIZE);
    }
}

AT(.text.prod_test.voice_saradc_init)
void tbox_voice_saradc_init(void)
{
    ring_buf_init(&saradc_enc_ring_buf, saradc_enc_buf, sizeof(saradc_enc_buf));

    saradc_deinit();

    /********************************saradc base init*******************************/
    saradc_base_init_typedef saradc_base_init_struct;
    clk_gate0_cmd(CLK_GATE0_SARADC, CLK_EN);
    clk_saradc_clk_set(CLK_SARADC_CLK_X24M_CLKDIV2);

    saradc_base_init_struct.mode = SARADC_MODE_NORMAL;
    saradc_base_init_struct.baud = 1500000;
    saradc_base_init_struct.auto_analog = SARADC_AUTO_ENABLE_ANALOG_EN;
    saradc_base_init_struct.auto_analog_io = SARADC_AUTO_ENABLE_ANALOG_IO_EN;
    saradc_init(&saradc_base_init_struct);

    /********************************mic channel init*******************************/
    sdadc_mic_init_typedef saradc_mic_init_struct;
    saradc_mic_init_struct.mask_length = 0;
    saradc_mic_init_struct.sample_rate = SARADC_SPR;
    saradc_mic_init_struct.mic_rc = AUDIO_MIC_NOT_RC;
    saradc_mic_init_struct.mic_vdd = AUDIO_MIC_VDD_2V0;
    saradc_mic_init_struct.mic_bias_res =  AUDIO_MIC_BIAS_RES_4K;
    saradc_mic_init_struct.mic_again = AUDIO_MIC_ANA_GAIN_7;
    saradc_mic_init_struct.micin_trim = 1400;  //micin trim target value, uint:mV, AUDIO_MIC_NOT_RC and AUDIO_MIC_NOT_R valid

    saradc_mic_init(&saradc_mic_init_struct);

    if ((saradc_mic_init_struct.mic_vdd != AUDIO_MIC_VDD_NONE)  && \
        (saradc_mic_init_struct.mic_rc != AUDIO_MIC_NOT_RC)) {
        GPIOBDE &= ~BIT(8);     //mic bias PB8
    }

    saradc_pic_config(tbox_voice_saradc_isr, 0, SARADC_MIC_DMA_HALF_DONE | SARADC_MIC_DMA_ALL_DONE, ENABLE);

    /********************************saradc start*******************************/
    saradc_cmd(ENABLE);
}

AT(.text.prod_test.voice_saradc_start)
void tbox_voice_saradc_start(void)
{
    #if NOTCH_IIR_EN
        notch_iir_init(SARADC_SPR);
    #endif  //NOTCH_IIR_EN
    saradc_skip_frame = SARADC_SKIP_FRAME;
    audio_mic_dc_filter_init();
    saradc_mic_dma_cmd((uint32_t)saradc_mic_dma_buf, SARADC_MIC_BUF_LEN, ENABLE);
    saradc_mic_cmd(ENABLE);
}

AT(.text.prod_test.voice_saradc_stop)
void tbox_voice_saradc_stop(void)
{
    saradc_mic_dma_cmd((uint32_t)saradc_mic_dma_buf, SARADC_MIC_BUF_LEN, DISABLE);
    saradc_mic_cmd(DISABLE);
    saradc_deinit();
}
#endif  //(FUNC_TBOX_EN && PROD_TEST_MIC_EN)
