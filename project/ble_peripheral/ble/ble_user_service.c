#include "include.h"

static att_service_handler_t       fff0_service;
static uint16_t fff2_client_config;

#define BLE_CMD_BUF_LEN     32
#define BLE_CMD_BUF_MASK    (BLE_CMD_BUF_LEN - 1)
#define BLE_RX_BUF_LEN      20


struct ble_cmd_t{
    u16 len;
    u8 buf[BLE_RX_BUF_LEN];
    uint16_t handle;
};

struct ble_user_cb_t {
    struct ble_cmd_t cmd[BLE_CMD_BUF_LEN];
    u8 cmd_rptr;
    u8 cmd_wptr;
    bool pending;
} ble_user_cb;

AT(.com_sleep.ble.sleep)
bool ble_user_service_pending(void)
{
    return ble_user_cb.pending;
}

static void ble_event_callback(uint8_t event_type, uint8_t *param, uint16_t size)
{
    switch(event_type){
        case BLE_EVT_CONNECT:{
            memcpy(&ble_cb.con_handle, &param[7], 2);
            printf("-->BLE_EVENT_CONNECTED:%x\n",ble_cb.con_handle);
        #if SYS_SLEEP_EN
            if (sys_cb.sleep_enter) {
                sys_cb.sleep_prevent = true;
            }
        #endif
        } break;

        case BLE_EVT_DISCONNECT:{
#if BSP_UART_DEBUG_EN
            uint16_t con_handle;
            uint8_t disc_reason = param[2];
            memcpy(&con_handle, &param[0], 2);
            printf("-->BLE_EVENT_DISCONNECTED:%x, disc_reason %x\n",con_handle, disc_reason);
#endif
            ble_cb.con_handle = 0;
            fff2_client_config = CCCD_DFT;
        #if SYS_SLEEP_EN
            if (sys_cb.sleep_enter) {
                sys_cb.sleep_prevent = true;
            }
        #endif
        } break;

        case BLE_EVT_CONNECT_PARAM_UPDATE_DONE: {
            printf("BLE_EVT_CONNECT_PARAM_UPDATE_DONE\n");
#if BSP_UART_DEBUG_EN
            u8 status = param[0];
            u16 handle = param[1] | (param[2] << 8);
            u16 interval = param[3] | (param[4] << 8);
            u16 latency = param[5] | (param[6] << 8);
            u16 timeout = param[7] | (param[8] << 8);
            printf("%d, %d, %d, %d, %d\n", status, handle, interval, latency, timeout);
#endif
        } break;

        default:
            break;
    }
}

static uint16_t service_read_callback(uint16_t con_handle, uint16_t attribute_handle, uint16_t offset, uint8_t * buffer, uint16_t buffer_size)
{
    printf("service_read_callback\n");

    if(attribute_handle == ATT_CHARACTERISTIC_FFF1_01_VALUE_HANDLE){
        u8 read_data[] = "hello";
        u8 data_len = sizeof(read_data) - 1;
        if(buffer){
            data_len = (buffer_size < (data_len - offset))? buffer_size: (data_len - offset);
            memcpy(buffer, read_data + offset, data_len);
        }
        return data_len;
    }

	return 0;
}

// static void service_notify_event_test(uint8_t *buffer, uint16_t len)
// {
//     u8 wptr = ble_user_cb.cmd_wptr & BLE_CMD_BUF_MASK;
//     ble_user_cb.cmd_wptr++;
//     if (len > BLE_RX_BUF_LEN) {
//         len = BLE_RX_BUF_LEN;
//     }
//     for (uint16_t i = 0; i < len; i++)
//     {
//         ble_user_cb.cmd[wptr].buf[len - i - 1] = buffer[i];
//     }
//     ble_user_cb.cmd[wptr].len = len;
//     ble_user_cb.pending = 1;
// }

static int service_write_callback(uint16_t con_handle, uint16_t attribute_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size)
{
    printf("service_write_callback\n");

    if(attribute_handle == ATT_CHARACTERISTIC_FFF2_01_CLIENT_CONFIGURATION_HANDLE){
        fff2_client_config = GET_LE16(&buffer[0]);
    }else if(attribute_handle == ATT_CHARACTERISTIC_FFF1_01_VALUE_HANDLE){
        printf("BLE RX [%d]: \n", buffer_size);
        print_r(buffer, buffer_size);

#if BSP_UART_TRANSFER_EN
        // 从机接收到主机的BLE WRITE，将数据通过串口发出
        uart_transfer_tx_buff(buffer, buffer_size);
        // service_notify_event_test(buffer, buffer_size);
#endif

#if 0
        u8 wptr = ble_user_cb.cmd_wptr & BLE_CMD_BUF_MASK;
        ble_user_cb.cmd_wptr++;
        if (buffer_size > BLE_RX_BUF_LEN) {
            buffer_size = BLE_RX_BUF_LEN;
        }
        memcpy(ble_user_cb.cmd[wptr].buf, buffer, buffer_size);
        ble_user_cb.cmd[wptr].len = buffer_size;
        ble_user_cb.cmd[wptr].handle = attribute_handle;
        ble_user_cb.pending = 1;
#endif
        lowpwr_sleep_delay_reset();
        lowpwr_pwroff_delay_reset();
    }

	return ATT_ERR_NO_ERR;
}

void service_notify_event(u8 *buffer, u16 len)
{
    u8 wptr = ble_user_cb.cmd_wptr & BLE_CMD_BUF_MASK;
    ble_user_cb.cmd_wptr++;
    if (len > BLE_RX_BUF_LEN) {
        len = BLE_RX_BUF_LEN;
    }
    memcpy(ble_user_cb.cmd[wptr].buf, buffer, len);
    ble_user_cb.cmd[wptr].len = len;
    ble_user_cb.pending = 1;
}

void ble_user_service_init(void)
{
    printf("ble_user_service_init\n");

    // get service handle range
	uint16_t start_handle = ATT_SERVICE_FFF0_START_HANDLE;
	uint16_t end_handle   = ATT_SERVICE_FFF0_END_HANDLE;

    // register service with ATT Server
	fff0_service.start_handle   = start_handle;
	fff0_service.end_handle     = end_handle;
	fff0_service.read_callback  = &service_read_callback;
	fff0_service.write_callback = &service_write_callback;
	fff0_service.event_handler  = &ble_event_callback;
	att_server_register_service_handler(&fff0_service);

	fff2_client_config = CCCD_DFT;
}

AT(.text.app.proc.ble)
void ble_user_service_proc(void)
{
    if (ble_user_cb.cmd_rptr == ble_user_cb.cmd_wptr) {
        ble_user_cb.pending = 0;
        return;
    }
    u8 rptr = ble_user_cb.cmd_rptr & BLE_CMD_BUF_MASK;
    ble_user_cb.cmd_rptr++;
    u8 *ptr = ble_user_cb.cmd[rptr].buf;
    u16 len = ble_user_cb.cmd[rptr].len;
    //uint16_t handle = ble_user_cb.cmd[rptr].handle;

    if(fff2_client_config){
        printf("BLE TX [%d]: \n", len);
        print_r((u8 *)ptr, len);
        ble_notify_for_handle(ble_cb.con_handle, ATT_CHARACTERISTIC_FFF2_01_VALUE_HANDLE, ptr, len);
    }
}
