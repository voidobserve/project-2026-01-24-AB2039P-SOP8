#ifndef _UART_TRANSFER_H
#define _UART_TRANSFER_H


typedef struct {
    u8 timeout;
    u8 done;
    u16 len;
    u8 *buf;
} uart_transfer_cb_typedef;


void uart_transfer_init(u32 baud);
void uart_transfer_tx_buff(uint8_t *buff, uint32_t len);
void uart_transfer_rx_event(void);
void uart_timeout_1ms_isr(void);

#endif // _UART_TRANSFER_H
