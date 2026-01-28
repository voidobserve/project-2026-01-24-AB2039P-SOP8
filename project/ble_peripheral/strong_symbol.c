/**********************************************************************
*
*   strong_symbol.c
*   定义库里面部分WEAK函数的Strong函数，动态关闭库代码
***********************************************************************/
#include "include.h"
#include "driver_uart.h"

STRONG uint8_t cfg_spiflash_speed_up_en = SPIFLASH_SPEED_UP_EN;

STRONG u8 mem_heap[OS_HEAP_SIZE] AT(.osmem);

static const struct thread_cfg_cb thread_cfg =
{
    /*                  Enable                              Priority    Stack   */
    .bt_stack   =       {OS_THREAD_BT_EN,                   23,         OS_THREAD_BT_STACK},
    .dirver     =       {OS_THREAD_DRIVER_EN,               17,         OS_THREAD_DRIVER_STACK},
    .timer      =       {OS_THREAD_TIMER_EN,                16,         OS_THREAD_TIMER_STACK},
    .main       =       {1,                                 25,         OS_THREAD_MAIN_STACK},
};

STRONG uint32_t mem_heap_size_get(void)
{
   return sizeof(mem_heap);
}

STRONG struct thread_cfg_cb* thread_cfg_get(void)
{
   return (struct thread_cfg_cb*)&thread_cfg;
}

STRONG void thread_create_callback(void)
{
    if (thread_cfg.timer.enable) {
        thread_timer_create();
    }

    if (thread_cfg.dirver.enable) {
        thread_driver_create();
    }

    if (thread_cfg.bt_stack.enable) {
        thread_btstack_create();
    }
}


STRONG void xosc_get_xcfg(u8 *osci_cap, u8 *osco_cap, u8 *both_cap)
{
    *osci_cap = xcfg_cb.osci_cap;
    *osco_cap = xcfg_cb.osco_cap;
    *both_cap = xcfg_cb.osc_both_cap;
}

STRONG void param_xosc_read(u8 *param)
{
    bsp_param_read(param, PARAM_BT_XOSC_CAP, PARAM_BT_XOSC_CAP_LEN);
}

STRONG void param_xosc_write(u8 *param)
{
    bsp_param_write(param, PARAM_BT_XOSC_CAP, PARAM_BT_XOSC_CAP_LEN);
    bsp_param_sync();
}

AT(.com_text.spiflash)
STRONG bool os_spiflash_addr_check(u32 addr, uint len)
{
    if ((addr >= CM_START) && ((addr + len) <= (CM_START + CM_SIZE))) {
        return true;
    }

#if AB_FOT_EN
    if ((addr >= FOT_PACK_START) && ((addr + len) <= (FOT_PACK_START + FOT_PACK_SIZE))) {
        return true;
    }
#endif

    printf("-->os_spiflash_addr_err:0x%x\n", addr);

    return false;
}

AT(.com_text.timer)
STRONG void usr_tmr5ms_thread_callback(void)
{
    usr_tmr5ms_callback();
}

STRONG void sys_clk_change_callback(void)
{
#if BSP_UART_DEBUG_EN
    uart_baud_config(UART, UART_DEBUG_BAUD);
#endif // BSP_UART_DEBUG_EN
}

#if BSP_UART_DEBUG_EN
STRONG void uart_debug_init_callback(void)
{
    bsp_uart_debug_init();
}
#else
AT(.com_text.printf)
STRONG void uart_debug_putchar(char ch)
{

}

STRONG void uart_debug_init_callback(void)
{
    my_printf_init(uart_debug_putchar);
}
#endif // BSP_UART_DEBUG_EN

