#include "include.h"
#include "driver_saradc.h"
#include "bsp_saradc.h"
#include "bsp_saradc_vbat.h"

#if BSP_SARADC_EN

void bsp_saradc_init(void)
{
    saradc_base_init_typedef saradc_base_init_struct;

    clk_gate0_cmd(CLK_GATE0_SARADC, CLK_EN);
    clk_saradc_clk_set(CLK_SARADC_CLK_X24M_CLKDIV2);

    saradc_base_init_struct.mode = SARADC_MODE_NORMAL;
    saradc_base_init_struct.baud = 1500000;
    saradc_base_init_struct.auto_analog = SARADC_AUTO_ENABLE_ANALOG_EN;
    saradc_base_init_struct.auto_analog_io = SARADC_AUTO_ENABLE_ANALOG_IO_EN;
    saradc_init(&saradc_base_init_struct);

    saradc_cmd(ENABLE);
}

void bsp_saradc_exit(void)
{
    saradc_deinit();
}

AT(.com_text.saradc_scan)
bool bsp_saradc_scan(void)
{
    if (saradc_get_flag(SARADC_IT_FINISHED)) {
        saradc_clear_flag(SARADC_IT_FINISHED);
        saradc_get_result();
        saradc_kick_start();
        return true;
    }

    return false;
}
#endif
