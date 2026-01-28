#include "include.h"
#include "driver_gpio.h"
#include "driver_uart.h"
#include "bsp_uart_transfer.h"

#if BSP_UART_TRANSFER_EN

// #define UART_TX_PORT              GPIOB_REG
// #define UART_TX_PIN               GPIO_PIN_3
// #define UART_RX_PORT              GPIOB_REG
// #define UART_RX_PIN               GPIO_PIN_4

#define UART_TX_PORT              GPIOB_REG
#define UART_TX_PIN               GPIO_PIN_4
#define UART_RX_PORT              GPIOB_REG
#define UART_RX_PIN               GPIO_PIN_3

static uint8_t uart_transfer_timeout AT(.tbox.voice_enc_buf);
static ring_buf_t uart_transfer_ring_buf AT(.tbox.voice_enc_buf);
static uint8_t uart_transfer_buf[512] AT(.tbox.voice_enc_buf);
static uint8_t uart_transfer_buf_temp[512];

AT(.com_text.isr)
void uart_isr(void)
{
    if (uart_get_flag(UART, UART_IT_RX) != RESET) {
        u8 sbuf = uart_receive_data(UART);
        uart_clear_flag(UART, UART_IT_RX);

        // ring_buf_write(&uart_transfer_ring_buf, &sbuf, 1);  // 此函数不在公共区，不能在中断调用
        uart_transfer_ring_buf.buf[uart_transfer_ring_buf.buf_write++] = sbuf;
        uart_transfer_ring_buf.data_len++;
        if (uart_transfer_ring_buf.buf_write >= uart_transfer_ring_buf.total_len)
            uart_transfer_ring_buf.buf_write = 0;
        uart_transfer_timeout = 6;
    }
}

AT(.com_text.isr)
void uart_timeout_1ms_isr(void)
{
    if (uart_transfer_timeout > 1)
        uart_transfer_timeout--;
}

void uart_transfer_init(u32 baud)
{
    // uart ring buf init
    ring_buf_init(&uart_transfer_ring_buf, uart_transfer_buf, sizeof(uart_transfer_buf));
    uart_transfer_timeout = 0;

    // uart io init
    uart_init_typedef uart_init_struct;
    gpio_init_typedef gpio_init_structure;

    clk_gate0_cmd(CLK_GATE0_UART, CLK_EN);
    clk_uart_clk_set(CLK_UART_CLK_X24M_DIV_CLK);

    // RX
    gpio_init_structure.gpio_pin = UART_RX_PIN;
    gpio_init_structure.gpio_dir = GPIO_DIR_INPUT;
    gpio_init_structure.gpio_fen = GPIO_FEN_PER;
    gpio_init_structure.gpio_fdir = GPIO_FDIR_SELF;
    gpio_init_structure.gpio_mode = GPIO_MODE_DIGITAL;
    gpio_init_structure.gpio_pupd = GPIO_PUPD_PU10K;
    gpio_init(UART_RX_PORT, &gpio_init_structure);

    // TX
    gpio_init_structure.gpio_pin = UART_TX_PIN;
    gpio_init_structure.gpio_dir = GPIO_DIR_OUTPUT;
    gpio_init_structure.gpio_drv = GPIO_DRV_I_6MA;
    gpio_init(UART_TX_PORT, &gpio_init_structure);

    gpio_func_mapping_config(UART_RX_PORT, UART_RX_PIN, GPIO_CROSSBAR_IN_UARTRX);
    gpio_func_mapping_config(UART_TX_PORT, UART_TX_PIN, GPIO_CROSSBAR_OUT_UARTTX);

    uart_init_struct.baud = baud;
    uart_init_struct.mode = UART_SEND_RECV_MODE;
    uart_init_struct.word_len = UART_WORD_LENGTH_8b;
    uart_init_struct.stop_bits = UART_STOP_BIT_1BIT;
    uart_init_struct.one_line_enable = UART_SEPARATE;
    uart_init_struct.baud_fix = UART_BAUD_FIX;
    uart_init(UART, &uart_init_struct);

    uart_pic_config(UART, uart_isr, 0, UART_IT_RX, ENABLE);

    uart_cmd(UART, ENABLE);
}

AT(.com_periph.uart.send)
void uart_transfer_tx_buff(uint8_t *buff, uint32_t len)
{
    if (buff == NULL || len == 0)
        return;
    
    while (len)
    {
        uart_send_data(UART, *buff++);
        while (uart_get_flag(UART, UART_IT_TX) != SET);
        len--;
    }
}

// uint8_t test_buff[20];
// uint8_t test_time = 0;
// static uint32_t tick_timeout = 50;
// void uart_transfer_test_event(void)
// {
//     static uint32_t ticks = 0;
//     if (tick_check_expire(ticks, tick_timeout) && test_time > 0)
//     {
//         ticks = tick_get();
//         for (uint8_t i = 0; i < 20; i++)
//             test_buff[i] = i;
//         ble_write_to_server(test_buff, 20);
//         test_time--;
//     }
// }

void uart_transfer_rx_event(void)
{
    uint8_t *ptr = NULL;
    u32 len = 0;

#ifdef CLIENT
    // uart_transfer_test_event();
#endif

    if (uart_transfer_timeout == 1)
    {
        uart_transfer_timeout = 0;
        
        len = ring_buf_read(&uart_transfer_ring_buf, uart_transfer_buf_temp, uart_transfer_ring_buf.data_len);
        ptr = uart_transfer_buf_temp;
        
#ifdef CLIENT
        // 主机接收串口然后通过BLE WRITE到从机
        ble_write_to_server(ptr, len);
        // test_time = ptr[0];
        // tick_timeout = ptr[1];
        // if (tick_timeout < 50)
        //     tick_timeout = 50;
#else
        // 从机接收串口然后通过BLE NOTIFY到主机
        service_notify_event(ptr, len);
#endif
    }
}
#endif
 
