/**
******************************************************************************************************************************
*
*@file driver_irrx.c
*
*@brief Source file for IR rx driver
*
*Copyright (c) 2024, BLUETRUM
******************************************************************************************************************************
**/
#include "driver_ir.h"

//1m时钟下的解码timing
#define RPTERR_CNT              500
#define DATERR_CNT              500
#define ONEERR_CNT              250
#define ZEROERR_CNT             125
#define TOPR_CNT                1750
#define RPTPR_CNT               11249
#define DATPR_CNT               13499
#define DATA_0_CNT              1119
#define DATA_1_CNT              2249

/**
  * @brief  Set irrx wakup_en/int_en/data_format.
  * @param  irrx_reg: irrx register address
  * @param  irrx_param: irrx params,include wakup_en/clock/int_en/data_format.
  * @retval None
  */
void irrx_init(irrx_param_t *irrx_param)
{
    //rx con
    u32 tmp_reg = IRRX->con;
    tmp_reg &= ~(uint32_t)(IRRXCON_DATA_SEL | \
                           IRRXCON_WK_EN);
    tmp_reg |= irrx_param->data_format & IRRXCON_DATA_SEL;
    tmp_reg |= irrx_param->wakup_en & IRRXCON_WK_EN;
    IRRX->con = tmp_reg;

    //filter
    tmp_reg = IRRX->fltcon;
    tmp_reg &= ~(uint32_t)(IRFLTCON_EN | \
                           IRFLTCON_SRCS);
    tmp_reg |= irrx_param->filter_en & IRFLTCON_EN;
    tmp_reg |= irrx_param->filter_srcs & IRFLTCON_SRCS;
    tmp_reg |= (irrx_param->filter_len << 8) & IRFLTCON_LEN;
    IRRX->fltcon = tmp_reg;

    //timing
    u32 irrx_clk = clk_irrx_clk_get(CLK_VALUE_MODE_FREQ);

    IRRX->period0   = BIT(16) * (uint16_t)((uint64_t)RPTPR_CNT   * irrx_clk/1000000)|
                                (uint16_t)((uint64_t)DATPR_CNT   * irrx_clk/1000000);

    IRRX->period1   = BIT(16) * (uint16_t)((uint64_t)DATA_1_CNT  * irrx_clk/1000000)|
                                (uint16_t)((uint64_t)DATA_0_CNT  * irrx_clk/1000000);

    IRRX->err0      = BIT(16) * (uint16_t)((uint64_t)RPTERR_CNT  * irrx_clk/1000000)|
                                (uint16_t)((uint64_t)DATERR_CNT  * irrx_clk/1000000);

    IRRX->err1      = BIT(20) * (uint16_t)((uint64_t)TOPR_CNT    * irrx_clk/1000000)|
                      BIT(10) * (uint16_t)((uint64_t)ONEERR_CNT  * irrx_clk/1000000)|
                                (uint16_t)((uint64_t)ZEROERR_CNT * irrx_clk/1000000);
}

void irrx_pic_config(isr_t isr, int pr, IRRX_FLAG_TYPEDEF flag_type, FUNCTIONAL_STATE state)
{
    u32 flag_pending_bit = 0;

    if (flag_type == 0) {
        return;
    }

    if (flag_type & IRRX_FLAG_RXPND) {
        flag_pending_bit |= IRRXCON_IE;
    }

    if (state != DISABLE) {
        IRRX->con |= flag_pending_bit;
        sys_irq_init(IRQn_IR_QDEC_LEDC, pr, isr);
    } else {
        IRRX->con &= ~flag_pending_bit;
    }
}

AT(.com_periph.irrx.flag)
FLAG_STATE irrx_get_flag(IRRX_FLAG_TYPEDEF flag_type)
{
    u32 flag_pending_bit = 0;

    if (flag_type & IRRX_FLAG_RXPND) {
        flag_pending_bit |= IRRXCON_RX_PND;
    }

    if (flag_type & IRRX_FLAG_KEYRELS) {
        flag_pending_bit |= IRRXCON_KEY_RELS;
    }

    if ((IRRX->con & flag_pending_bit) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

AT(.com_periph.irrx.flag)
void irrx_clear_flag(IRRX_FLAG_TYPEDEF flag_type)
{
    u32 flag_pending_bit = 0;

    if (flag_type & IRRX_FLAG_RXPND) {
        flag_pending_bit |= IRRXCPEND_RX_PND;
    }

    if (flag_type & IRRX_FLAG_KEYRELS) {
        flag_pending_bit |= IRRXCPEND_RELS_PND;
    }

    IRRX->cpnd = flag_pending_bit;
}

AT(.com_periph.irrx.data)
u32 irrx_get_data(void)
{
    return IRRX->dat;
}

void irrx_cmd(FUNCTIONAL_STATE state)
{
    if (state != DISABLE) {
        IRRX->con |= IRRXCON_EN;
    } else {
        IRRX->con &= ~IRRXCON_EN;
    }
}

void irrx_deinit(void)
{
    IRRX->con &= ~(IRRXCON_IE | \
                   IRRXCON_WK_EN | \
                   IRRXCON_EN);
    clk_gate2_cmd(CLK_GATE1_IRRX, CLK_DIS);
}