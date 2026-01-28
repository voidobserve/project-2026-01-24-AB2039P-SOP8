/*
 * @File name    : driver_clk.c
 * @Author       : Bluetrum IOT Team
 * @Date         : 2023-04-04
 * @Description  : This file provides functions to manage the most functionalities
 *                 of the CLK peripheral.
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#include "driver_clk.h"

void clk_gate0_cmd(uint32_t clock_gate, CLK_STATE state)
{
    if (state != CLK_DIS) {
        CLKGAT0 |= clock_gate;
    } else {
        CLKGAT0 &= ~clock_gate;
    }
}

void clk_gate1_cmd(uint32_t clock_gate, CLK_STATE state)
{
    if (state != CLK_DIS) {
        CLKGAT1 |= clock_gate;
    } else {
        CLKGAT1 &= ~clock_gate;
    }
}

void clk_gate2_cmd(uint32_t clock_gate, CLK_STATE state)
{
    if (state != CLK_DIS) {
        CLKGAT2 |= clock_gate;
    } else {
        CLKGAT2 &= ~clock_gate;
    }
}

void clk_clkout_set(CLK_CLKOUT_TYPEDEF clk_sel, uint8_t div, CLK_STATE state)
{
    if (state != CLK_DIS) {
        CLKCON0 &= ~(0x0f << 13);
        CLKCON0 |= ((clk_sel & 0x0f) << 13);

        CLKDIVCON0 &= ~(0x1f << 17);
        CLKDIVCON0 |= ((div & 0x1f) << 17);
    } else {
        CLKCON0 &= ~(0x0f << 13);
        CLKDIVCON0 &= ~(0x1f << 17);
    }
}

void clk_clk32k_rtc_set(CLK_CLK32K_RTC_TYPEDEF clk_sel)
{
    uint32_t rtccon0 = RTCCON0;

    if ((CLK_CLK32K_RTC_RC2M_RTC == clk_sel) || (CLK_CLK32K_RTC_SNF_RC_RTC == clk_sel)) {
        rtccon0  |= BIT(19);                                //RC2M_RTC enable
    }
    
    rtccon0 &= ~(0x03 << 8);
    rtccon0 |= ((clk_sel & 0x03) << 8);

    RTCCON0 = rtccon0;
}

uint32_t clk_clk32k_rtc_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t rtccon0 = RTCCON0;
    u8 index;

    index = (rtccon0 >> 8) & 0x03;

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_CLK32K_RTC_1BIT:
                return -1L;

            case CLK_CLK32K_RTC_RC2M_RTC:
            case CLK_CLK32K_RTC_SNF_RC_RTC:
                return rc2m_clk_nhz_get(1) / 64;

            case CLK_CLK32K_RTC_X24MDIV12_RTC:
                return 2000000 / 64;

            default:
                return 0;
        }
    }
}

void clk_hsut0_clk_set(CLK_HSUART_CLK_TYPEDEF clk_sel, uint8_t div)
{
    uint32_t clkcon0 = CLKCON0;

    clkcon0 &= ~(0x07 << 17);
    clkcon0 |= ((clk_sel & 0x07) << 17);

    CLKCON0 = clkcon0;

    // if (clk_sel >= CLK_HSUT0_CLK_PLLDIV2_CLK) {
    //     CLKDIVCON0 &= ~(0x03 << 22);
    //     CLKDIVCON0 |= ((div & 0x03) << 22);
    //     PLL0CON |= BIT(13);
    // }
}

uint32_t clk_hsut0_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t clkcon0 = CLKCON0;
    u8 index;

    index = ((clkcon0 >> 17) & 0x07);

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_HSUT0_CLK_XOSC24M_CLK:
                return 24000000;

            case CLK_HSUT0_CLK_XOSC48M:
                return 48000000;

            case CLK_HSUT0_CLK_UART0_PCLKPP_CLK:
                return 0; //待添加

            case CLK_HSUT0_CLK_1BIT_CLK:
                return 0; //待添加

            case CLK_HSUT0_CLK_PLLDIV2_CLK:
                return 0; //待添加

            case CLK_HSUT0_CLK_PLLDIV3_CLK:
                return 0; //待添加

            case CLK_HSUT0_CLK_PLLDIV4_CLK:
                return 0; //待添加

            case CLK_HSUT0_CLK_PLLDIV8_CLK:
                return 0; //待添加

            default:
                return 0;
        }
    }
}

void clk_saradc_clk_set(CLK_SARADC_CLK_TYPEDEF clk_sel)
{
    uint32_t clkcon0 = CLKCON0;

    clkcon0 &= ~(0x03 << 28);
    clkcon0 |= ((clk_sel & 0x03) << 28);

    CLKCON0 = clkcon0;
}

uint32_t clk_saradc_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t clkcon0 = CLKCON0;
    u8 index;

    index = ((clkcon0 >> 28) & 0x03);

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_SARADC_CLK_RC2M_CLK:
                return rc2m_clk_nhz_get(0);

            case CLK_SARADC_CLK_X24M_CLKDIV4:
                return 6000000;

            case CLK_SARADC_CLK_X24M_CLKDIV2:
                return 12000000;

            default:
                return 0;
        }
    }
}

void clk_uart_clk_set(CLK_UART_CLK_TPYEDEF clk_sel)
{
    uint32_t clkcon1 = CLKCON1;

    clkcon1 &= ~(0x03 << 14);
    clkcon1 |= ((clk_sel & 0x03) << 14);

    CLKCON1 = clkcon1;
}

uint32_t clk_uart_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t clkcon1 = CLKCON1;
    u8 index;

    index = (clkcon1 >> 14) & 0x03;

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_UART_CLK_TMR_INC0_CR:
                return 0;  //不确定

            case CLK_UART_CLK_X24M_DIV_CLK:
                return 24000000;

            case CLK_UART_CLK_X48M:
                return 48000000;

            default:
                return 0;
        }
    }
}

void clk_clk2m_ks_set(CLK_CLK2M_KS_TYPEDEF clk_sel)
{
    uint32_t rtccon0 = RTCCON0;

    rtccon0 &= ~(0x03 << 14);
    rtccon0 |= ((clk_sel & 0x03) << 14);

    if (clk_sel == CLK_CLK2M_KS_SNF_RC_RTC) {
        rtccon0 |= BIT(19);
    } else if (clk_sel == CLK_CLK2M_KS_RC2M_RTC){
        rtccon0 |= BIT(0);
    }

    RTCCON0 = rtccon0;
}

uint32_t clk_clk2m_ks_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t rtccon0 = RTCCON0;
    u8 index;

    index = (rtccon0 >> 14) & 0x03;

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_CLK2M_KS_1BIT:
                return -1L;

            case CLK_CLK2M_KS_RC2M_RTC:
                return rc2m_clk_nhz_get(1);

            case CLK_CLK2M_KS_SNF_RC_RTC:
                return rc2m_clk_nhz_get(0);

            case CLK_CLK2M_KS_X24MDIV12_RTC:
                return 2000000;

            default:
                return 0;
        }
    }
}

void clk_ledc_clk_set(CLK_LEDC_CLK_TYPEDEF clk_sel)
{
    u32 clkcon1 = CLKCON1;

    clkcon1 &= ~(0x01 << 27);
    clkcon1 |= (clk_sel & 0x01) << 27;

    CLKCON1 = clkcon1;
}

uint32_t clk_ledc_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    u32 clkcon1 = CLKCON1;
    u8 index;

    index = (clkcon1 >> 27) & 0x01;

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_LEDC_CLK_XOSC24M:
                return 24000000;

            case CLK_LEDC_CLK_X24M_CLKDIV2:
                return 12000000;

            default:
                return 0;
        }
    }
}

void clk_irtx_clk_set(CLK_IR_CLK_TYPEDEF clk_sel)
{
    uint32_t clkcon1 = CLKCON1;

    clkcon1 &= ~(0x03 << 4);
    clkcon1 |= ((clk_sel & 0x03) << 4);

    CLKCON1 = clkcon1;
}

uint32_t clk_irtx_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t clkcon1 = CLKCON1;
    u8 index;

    index = ((clkcon1 >> 4) & 0x03);

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_IR_CLK_X24M_32K:
                return 32000;

            case CLK_IR_CLK_X24M_CLKDIV24:
                return 1000000;

            case CLK_IR_CLK_OSC32K:
                return clk_clk32k_rtc_get(CLK_VALUE_MODE_FREQ);

            case CLK_IR_CLK_RC32K_CLK:
                return 32000; //?

            default:
                return 0;
        }
    }
}

void clk_irtx_mod_clk_set(CLK_IR_MOD_CLK_TYPEDEF clk_sel)
{
    uint32_t clkcon1 = CLKCON1;

    clkcon1 &= ~(0x01 << 9);
    clkcon1 |= ((clk_sel & 0x01) << 9);

    CLKCON1 = clkcon1;
}

uint32_t clk_irtx_mod_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t clkcon1 = CLKCON1;
    u8 index;

    index = ((clkcon1 >> 9) & 0x01);

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_IR_MOD_CLK_X24M_CLKDIV8:
                return 3000000;

            case CLK_IR_MOD_CLK_X24M_CLKDIV6:
                return 4000000;

            default:
                return 0;
        }
    }
}

void clk_irrx_clk_set(CLK_IR_CLK_TYPEDEF clk_sel)
{
    uint32_t clkcon1 = CLKCON1;

    clkcon1 &= ~(0x03 << 4);
    clkcon1 |= ((clk_sel & 0x03) << 4);

    CLKCON1 = clkcon1;
}

uint32_t clk_irrx_clk_get(CLK_VALUE_MODE_TYPEDEF mode)
{
    uint32_t clkcon1 = CLKCON1;
    u8 index;

    index = ((clkcon1 >> 4) & 0x03);

    if (mode == CLK_VALUE_MODE_IDX) {
        return index;
    } else {
        switch (index) {
            case CLK_IR_CLK_X24M_32K:
                return 32000;

            case CLK_IR_CLK_X24M_CLKDIV24:
                return 1000000;

            case CLK_IR_CLK_OSC32K:
                return clk_clk32k_rtc_get(CLK_VALUE_MODE_FREQ);

            case CLK_IR_CLK_RC32K_CLK:
                return 32000;  //?

            default:
                return 0;
        }
    }
}
