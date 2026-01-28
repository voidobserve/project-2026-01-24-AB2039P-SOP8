/*
 * @File name    : driver_tmr.h
 * @Author       : Bluetrum IOT Team
 * @Date         : 2023-02-14
 * @Description  : This file contains all the functions prototypes for the TMR library.
 * 
 * Copyright (c) by Bluetrum, All Rights reserved.
 */
#ifndef _DRIVER_TMR_H
#define _DRIVER_TMR_H

#include "driver_com.h"

/**
 * @brief TMR Interrupt Flag Definition
 */
typedef enum {
    TMR_IT_UPDATE           = 0x01,
    TMR_IT_CAPTURE          = 0x02,
} TMR_IT_TYPEDEF;

/**
 * @brief TMR MODE Selection
 */
typedef enum {
    TMR_TIMER_MODE                 = 0x00000000,
    TMR_CAP_RISING_EDGE            = 0x00004000,
    TMR_CAP_FALLING_EDGE           = 0x00008000,
    TMR_CAP_RISING_OR_FALLING_EDGE = 0x0000c000,
} TMR_MODE_TYPEDEF;

/**
 * @brief Clock Divide Selection
 */
typedef enum {
    TMR_CLOCK_DIV_1        = 0x00000000,
    TMR_CLOCK_DIV_2        = 0x00000010,
    TMR_CLOCK_DIV_4        = 0x00000020,
    TMR_CLOCK_DIV_8        = 0x00000030,
    TMR_CLOCK_DIV_16       = 0x00000040,
    TMR_CLOCK_DIV_32       = 0x00000050,
    TMR_CLOCK_DIV_64       = 0x00000060,
    TMR_CLOCK_DIV_UNUSED   = 0x00000070,
} TMR_PDIVSEL_TYPEDEF;

/**
 * @brief Clock Source Selection
 */
typedef enum {
    TMR_CLK_1BIT            = 0x00000000,
    TMR_SYS_CLK             = 0x00000002,
    TMR_XOSC24M_CLK         = 0x00000004,
    TMR_TMR_INC0_CR         = 0x00000006,
    TMR_XOSC_CLKDIV24       = 0x00000008,
    TMR_RTC_RC2M            = 0x0000000a,
    TMR_TMR_INC1_CR         = 0x0000000c,
    TMR_CLKOUT_PINP         = 0x0000000e,
} TMR_PCLKSEL_TYPEDEF;

/**
 * @brief Timer Init Structure
 */
typedef struct {
    bool                    tick_en;
    uint32_t                period;
    TMR_MODE_TYPEDEF        tmr_mode;
    TMR_PDIVSEL_TYPEDEF     clock_div;
    TMR_PCLKSEL_TYPEDEF     clock_source;
} tmr_base_init_typedef;

/********************** Function used to configure timer base **********************/
void tmr_base_init(tmr_typedef *tmrx, tmr_base_init_typedef *tmr_base_init_struct);
void tmr_deinit(tmr_typedef *tmrx);
void tmr_set_counter(tmr_typedef *tmrx, uint32_t cnt);
void tmr_set_period(tmr_typedef *tmrx, uint32_t period);
uint32_t tmr_get_counter(tmr_typedef *tmrx);
uint32_t tmr_get_period(tmr_typedef *tmrx);
void tmr_cmd(tmr_typedef *tmrx, FUNCTIONAL_STATE state);
/************************** Function used to set capture ***************************/
uint32_t tmr_get_capture(tmr_typedef *tmrx);
/********************** Function used to configure interrupt ***********************/
void tmr_pic_config(tmr_typedef *tmrx, isr_t isr, int pr, TMR_IT_TYPEDEF interrupt_type, FUNCTIONAL_STATE state);
FLAG_STATE tmr_get_flag(tmr_typedef *tmrx, TMR_IT_TYPEDEF interrupt_type);
void tmr_clear_flag(tmr_typedef *tmrx, TMR_IT_TYPEDEF interrupt_type);

#endif // _DRIVER_TMR_H
