#ifndef _UART_TRANSFER_H
#define _UART_TRANSFER_H


typedef struct {
    u8 timeout;
    u8 done;
    u16 len;
    u8 *buf;
} uart_transfer_cb_typedef;

// 指令码定义
typedef enum
{
    CMD_NONE = 0x00,

    CMD_ADV_EN_PREFIX = 0x01, // 打开广播
    CMD_ADV_EN_SUFFIX = 0x01,

    CMD_ADV_DIS_PREFIX = 0x02, // 关闭广播
    CMD_ADV_DIS_SUFFIX = 0x02,
} cmd_code_t;

void uart_send_cmd(cmd_code_t cmd_prefix, cmd_code_t cmd_suffix);

void uart_transfer_init(u32 baud);
void uart_transfer_tx_buff(uint8_t *buff, uint32_t len);
void uart_transfer_rx_event(void);
void uart_timeout_1ms_isr(void);

#endif // _UART_TRANSFER_H
