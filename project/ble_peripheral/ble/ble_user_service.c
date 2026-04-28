#include "include.h"
#include "user_config.h"

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
#if USER_DEBUG_ENABLE
            my_printf("BLE_EVT_CONNECT\n");
#endif
            memcpy(&ble_cb.con_handle, &param[7], 2);
            printf("-->BLE_EVENT_CONNECTED:%x\n",ble_cb.con_handle);
        #if SYS_SLEEP_EN
            if (sys_cb.sleep_enter) {
                sys_cb.sleep_prevent = true;
            }
        #endif
            /*
                连接成功之后，从机需要判断主机的地址是否跟记忆的一样
                如果地址一致，则继续执行，否则，将地址保存，并返回
            */ 
            // 获取主机地址
            uint8_t addr[6]; // MAC地址
            memcpy(addr, &param[1], 6); // 地址内容
#if USER_DEBUG_ENABLE
            // 传输过来是大端格式，这里按小端格式打印：
            my_printf("Connected to Host Address: %02X:%02X:%02X:%02X:%02X:%02X\n", 
                addr[5], addr[4], addr[3], addr[2], addr[1], addr[0]);
#endif
            if (user_data.is_peer_addr_valid == 0) {
                // 如果之前记录的地址无效
                memcpy(user_data.peer_addr, addr, 6);
                user_data.is_peer_addr_valid = 1; // 表示记录的地址有效
                user_data_write();
            } else {
                // 如果之前记录的地址有效，跟当前连接上的主机的地址进行比较

                if (memcmp(user_data.peer_addr, addr, 6) == 0) {
                    // 如果地址一致
#if USER_DEBUG_ENABLE
                    my_printf("host addr is valid\n");
#endif
                } else {
                    // 如果地址不一致，断开与主机的连接
#if USER_DEBUG_ENABLE
                    my_printf("host addr is invalid\n");
#endif
                    ble_disconnect(ble_cb.con_handle);
                }
            }

        } break;

        case BLE_EVT_DISCONNECT:{
#if USER_DEBUG_ENABLE
            my_printf("BLE_EVT_DISCONNECT\n");
#endif
#if BSP_UART_DEBUG_EN
            uint16_t con_handle;
            uint8_t disc_reason = param[2];
            memcpy(&con_handle, &param[0], 2);
            printf("-->BLE_EVENT_DISCONNECTED:%x, disc_reason %x\n",con_handle, disc_reason);
#endif
            ble_cb.con_handle = 0;
            fff2_client_config = CCCD_DFT;

            /*
                测试发现，主机开始配对后，主机断开当前连接的从机，
                有概率会导致从机的广播不会再打开
            */ 
            if (user_data.is_ble_adv_en) {
                ble_adv_en();
            } else {
                ble_adv_dis();
            }


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

        // USER_TO_DO 这里要加入指令的判断，如果是指令，则处理；如果不是指令，则转发
        if (buffer_size >= 5 &&
            buffer[0] == 0x80 && 
            buffer[1] == 0x02 &&
            buffer[2] == 0x02 &&
            buffer[3] == 0x02 && 
            buffer[4] == 0x02
        ) { // 收到了关闭广播的控制命令
            user_data.is_ble_adv_en = 0; 
            user_data_write();
#if USER_DEBUG_ENABLE
            my_printf("ble recv adv dis\n"); // 标识收到了主机发送过来的关闭广播的指令
#endif
            // 之后等主机断开连接，在断开连接事件相关的回调函数中处理
            // 等主机断开连接，之后由 ble_disconnected_restart_adv()，根据 user_data.is_ble_adv_en 控制广播是否自动打开
            uart_send_cmd(CMD_ADV_DIS_PREFIX, CMD_ADV_DIS_SUFFIX);
        }
        else { // 没有收到控制命令        
            // 从机接收到主机的BLE WRITE，将数据通过串口发出
            uart_transfer_tx_buff(buffer, buffer_size);
        } 

#if USER_DEBUG_ENABLE
        // 打印收到的数据
        // u16 i;
        // for (i = 0; i < buffer_size; i++)
        // {
        //     my_printf("%02x ", buffer[i]);
        // }
        // my_printf("\n");
#endif

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
