/*
 * @File name    : driver_tmr.h
 * @Author       : Bluetrum IOT Team
 * @Date         : 2023-02-14
 * @Description  : This file contains all the functions prototypes for the TMR library.
 *
 * Copyright (c) by Bluetrum, All Rights reserved.
 */
#ifndef _DRIVER_TMRP_H
#define _DRIVER_TMRP_H

#include "driver_com.h"

/**
 * @brief TMRP IT TYPE Selection
 */
typedef enum {
    TMRP_TIE                 = 0x01,
    TMRP_TG2IE               = 0x02,
} TMRP_IT_TYPEDEF;

/**
 * @brief TMRP TICK MODE Selection
 */
typedef enum {
    TMRP_TICK_MODE_UNUSED   = 0x00,
    TMRP_TICK_MODE          = 0x01,
    TMRP_TICK_MODE_G2       = 0x02,
} TMRP_TICK_MODE_TYPEDEF;

/**
 * @brief TMRP TMR MODE Selection
 *        TMRP_TMR_MODE: period variable controls PWM0~PWM5 cycles
 *        TMRP_TMR_MODE_G2: period variable controls PWM0~PWM2 cycles,
 *                          g2_period variable controls PWM3~PWM5 cycles
 */
typedef enum {
    TMRP_TMR_MODE          = 0x01,
    TMRP_TMR_MODE_G2       = 0x02,
} TMRP_TMR_MODE_TYPEDEF;

/**
 * @brief PWM Channel Selection
 */
typedef enum {
    TMRP_PWM_UNUSED        = 0x00000000,
    TMRP_PWM0              = 0x00010000,
    TMRP_PWM1              = 0x00040000,
    TMRP_PWM2              = 0x00100000,
    TMRP_PWM3              = 0x00400000,
    TMRP_PWM4              = 0x01000000,
    TMRP_PWM5              = 0x04000000,
} TMRP_PWM_NUM_TYPEDEF;

/**
 * @brief PWM Output Invert Selection
 */
typedef enum {
    TMRP_PWM_INV_UNUSED    = 0x00000000,
    TMRP_PWM0_INV          = 0x00020000,
    TMRP_PWM1_INV          = 0x00080000,
    TMRP_PWM2_INV          = 0x00200000,
    TMRP_PWM3_INV          = 0x00800000,
    TMRP_PWM4_INV          = 0x02000000,
    TMRP_PWM5_INV          = 0x08000000,
} TMRP_INV_TYPEDEF;

/**
 * @brief Clock Divide Selection
 */
typedef enum {
    TMRP_CLOCK_DIV_1        = 0x00000000,
    TMRP_CLOCK_DIV_2        = 0x00000010,
    TMRP_CLOCK_DIV_4        = 0x00000020,
    TMRP_CLOCK_DIV_8        = 0x00000030,
    TMRP_CLOCK_DIV_16       = 0x00000040,
    TMRP_CLOCK_DIV_32       = 0x00000050,
    TMRP_CLOCK_DIV_64       = 0x00000060,
    TMRP_CLOCK_DIV_UNUSED   = 0x00000070,
} TMRP_PDIVSEL_TYPEDEF;

/**
 * @brief Clock Source Selection
 */

typedef enum {
    TMRP_1BIT               = 0x00000000,
    TMRP_SYS_CLOCK          = 0x00000002,
    TMRP_XOSC24M_CLK        = 0x00000004,
    TMRP_TMR_INC0_CR        = 0x00000006,
    TMRP_XOSC_CLKDIV24      = 0x00000008,
    TMRP_RTC_RC2M           = 0x0000000a,
    TMRP_TMR_INC1_CR        = 0x0000000c,
    TMRP_CLKOUT_PINP        = 0x0000000e,
} TMRP_PCLKSEL_TYPEDEF;

/**
 * @brief TMRP Dead Zone Mode Selection
 */
typedef enum {
    TMRP_DZMODE_0          = 0x00000000,
    TMRP_DZMODE_1          = 0x00000002,
} TMRP_DZMODE_TYPEDEF;


/**
 * @brief Timer Init Structure
 */
typedef struct {
    TMRP_PCLKSEL_TYPEDEF     clock_source;
    TMRP_PDIVSEL_TYPEDEF     clock_div;
    uint32_t                 period;
    uint32_t                 g2_period;
    TMRP_TICK_MODE_TYPEDEF   tick_mode;
    TMRP_TMR_MODE_TYPEDEF    tmr_mode;
    TMRP_PWM_NUM_TYPEDEF     pwm_num;
    TMRP_INV_TYPEDEF         pwm_inv;
    uint32_t                 start_duty0;
    uint32_t                 start_duty1;
    uint32_t                 start_duty2;
    uint32_t                 start_duty3;
    uint32_t                 start_duty4;
    uint32_t                 start_duty5;
    bool                     dz_en;
    TMRP_DZMODE_TYPEDEF      dzmode;
    uint16_t                 dzlen;
} tmrp_base_init_typedef;

/********************** Function used to configure timer base **********************/
void tmrp_base_init(tmrp_typedef *tmrp, tmrp_base_init_typedef *tmrp_base_init_struct);
void tmrp_deinit(tmrp_typedef *tmrp);
void tmrp_open_pwm(tmrp_typedef *tmrp, TMRP_PWM_NUM_TYPEDEF pwm_num, TMRP_INV_TYPEDEF inv);
void tmrp_close_pwm(tmrp_typedef *tmrp, TMRP_PWM_NUM_TYPEDEF pwm_num);
void tmrp_set_counter(tmrp_typedef *tmrp, uint32_t cnt);
void tmrp_set_duty(tmrp_typedef *tmrp, TMRP_PWM_NUM_TYPEDEF pwm_num, uint16_t duty);
void tmrp_set_period(tmrp_typedef *tmrp, uint32_t period);
void tmrp_set_g2period(tmrp_typedef *tmrp, uint32_t period);
uint32_t tmrp_get_counter(tmrp_typedef *tmrp);
uint32_t tmrp_get_period(tmrp_typedef *tmrp);
uint32_t tmrp_get_g2period(tmrp_typedef *tmrp);
void tmrp_cmd(tmrp_typedef *tmrp, FUNCTIONAL_STATE state);
/********************** Function used to configure interrupt ***********************/
void tmrp_pic_config(tmrp_typedef *tmrp, isr_t isr, int pr, TMRP_IT_TYPEDEF interrupt_type, FUNCTIONAL_STATE state);
FLAG_STATE tmrp_get_flag(tmrp_typedef *tmrp, TMRP_IT_TYPEDEF interrupt_type);
void tmrp_clear_flag(tmrp_typedef *tmrp, TMRP_IT_TYPEDEF interrupt_type);

#endif // _DRIVER_TMRP_H
