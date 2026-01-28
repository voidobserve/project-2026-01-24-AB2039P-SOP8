/*
 * @File name    : driver_tmr.c
 * @Author       : Bluetrum IOT Team
 * @Date         : 2024-08-26
 * @Description  : This file provides functions to manage the most functionalities
 *                 of the TMRP peripheral.
 *
 * Copyright (c) by Bluetrum, All Rights reserved.
 */
#include "driver_pwm.h"

/**
  * @brief  Initializes the timer base peripheral according to the specified
  *         parameters in the tmrp_base_init_typedef.
  * @param  tmrp: TMRP.
  * @param  tmrp_base_init_struct: pointer to a tmrp_base_init_typedef structure that
  *         contains the configuration information for the specified TMRP peripheral.
  * @retval None
  */
void tmrp_base_init(tmrp_typedef *tmrp, tmrp_base_init_typedef *tmrp_base_init_struct)
{
    //---------- tmrp controller register ----------//

    //con
    tmrp->con &= ~(uint32_t)TMRPCON_PCLKSEL;
    tmrp->con |= tmrp_base_init_struct->clock_source & TMRPCON_PCLKSEL;

    tmrp->con &= ~(uint32_t)TMRPCON_PDIVSEL;
    tmrp->con |= tmrp_base_init_struct->clock_div & TMRPCON_PDIVSEL;

    if (tmrp_base_init_struct->tick_mode == TMRP_TICK_MODE) {
        tmrp->con &= ~(uint32_t)TMRPCON_TICKEN;
        tmrp->con |= TMRPCON_TICKEN;
    } else if (tmrp_base_init_struct->tick_mode == TMRP_TICK_MODE_G2) {
        tmrp->con &= ~(uint32_t)TMRPCON_TICKG2EN;
        tmrp->con |= TMRPCON_TICKG2EN;
    }

    tmrp->period = tmrp_base_init_struct->period;

    if (tmrp_base_init_struct->tmr_mode == TMRP_TMR_MODE_G2) {
        tmrp->con &= ~(uint32_t)TMRPCON_G2EN;
        tmrp->con |= TMRPCON_G2EN;

        tmrp->con &= ~(uint32_t)TMRPCON_PWMG2EN;
        tmrp->con |= TMRPCON_PWMG2EN;

        tmrp->g2period = tmrp_base_init_struct->g2_period;
    }

    //pwm num
    tmrp->con &= ~(uint32_t)TMRPCON_PWM_NUM;
    tmrp->con |= tmrp_base_init_struct->pwm_num & TMRPCON_PWM_NUM;

    tmrp->con &= ~(uint32_t)TMRPCON_PWM_INV;
    tmrp->con |= tmrp_base_init_struct->pwm_inv & TMRPCON_PWM_INV;

    //duty
    tmrp->duty0 = tmrp_base_init_struct->start_duty0 & TMRPDUTY;
    tmrp->duty1 = tmrp_base_init_struct->start_duty1 & TMRPDUTY;
    tmrp->duty2 = tmrp_base_init_struct->start_duty2 & TMRPDUTY;
    tmrp->duty3 = tmrp_base_init_struct->start_duty3 & TMRPDUTY;
    tmrp->duty4 = tmrp_base_init_struct->start_duty4 & TMRPDUTY;
    tmrp->duty5 = tmrp_base_init_struct->start_duty5 & TMRPDUTY;

    //dead zone
    tmrp->dzcon &= ~(uint32_t)PWMDZCON_DZLEN;
    tmrp->dzcon |= (tmrp_base_init_struct->dzlen * PWMDZCON_DZLEN_0) & PWMDZCON_DZLEN;

    tmrp->dzcon &= ~(uint32_t)PWMDZCON_DZMODE;
    tmrp->dzcon |= tmrp_base_init_struct->dzmode & PWMDZCON_DZMODE;

    tmrp->dzcon &= ~(uint32_t)PWMDZCON_DZEN;
    tmrp->dzcon |= tmrp_base_init_struct->dz_en & PWMDZCON_DZEN;
}

/**
 * @brief  De-initialize the specified tmr peripheral.
 * @param  tmrp: TMRP.
 * @retval None
 */
void tmrp_deinit(tmrp_typedef *tmrp)
{
    tmrp->con = 0;

    clk_gate2_cmd(CLK_GATE2_TMRP, CLK_DIS);
}

/**
  * @brief  Open the PWM.
  * @param  tmrp: TMRP.
  * @param  pwm_num: TMRP_PWM_NUM_TYPEDEF.
  * @param  inv: TMRP_INV_TYPEDEF.
  * @retval None
  */
void tmrp_open_pwm(tmrp_typedef *tmrp, TMRP_PWM_NUM_TYPEDEF pwm_num, TMRP_INV_TYPEDEF inv)
{
    tmrp->con |= pwm_num & TMRPCON_PWM_NUM;

    tmrp->con |= inv & TMRPCON_PWM_INV;
}

/**
  * @brief  Close the PWM.
  * @param  tmrp: TMRP.
  * @param  pwm_num: TMRP_PWM_NUM_TYPEDEF.
  * @retval None
  */
void tmrp_close_pwm(tmrp_typedef *tmrp, TMRP_PWM_NUM_TYPEDEF pwm_num)
{
    tmrp->con &= ~(uint32_t)(pwm_num & TMRPCON_PWM_NUM);
}

/**
  * @brief  Set the TMRP counter register value.
  * @param  tmrp: TMRP.
  * @param  cnt: specifies the counter register new value.
  * @retval None
  */
void tmrp_set_counter(tmrp_typedef *tmrp, uint32_t cnt)
{
    tmrp->cnt = cnt;
}

/**
 * @brief  Set tmrp_typedef duty of specified TMRP periperal.
 * @param  tmrp: TMRP.
 * @param  pwm_num: TMRP_PWM_NUM_TYPEDEF
 * @param  duty: The high level time of the tmrp_typedef to be configured.
 * @retval
 */
void tmrp_set_duty(tmrp_typedef *tmrp, TMRP_PWM_NUM_TYPEDEF pwm_num, uint16_t duty)
{
    switch (pwm_num)
    {
        case TMRP_PWM0:
            tmrp->duty0 = duty;
            break;
        case TMRP_PWM1:
            tmrp->duty1 = duty;
            break;
        case TMRP_PWM2:
            tmrp->duty2 = duty;
            break;
        case TMRP_PWM3:
            tmrp->duty3 = duty;
            break;
        case TMRP_PWM4:
            tmrp->duty4 = duty;
            break;
        case TMRP_PWM5:
            tmrp->duty5 = duty;
            break;

        default:
            break;
    }
}

/**
  * @brief  Set the TMRP period register value.
  * @param  tmrp: TMRP.
  * @param  period: specifies the period register new value.
  * @retval None
  */
void tmrp_set_period(tmrp_typedef *tmrp, uint32_t period)
{
    tmrp->period = period;
}

/**
  * @brief  Set the TMRP period register value.
  * @param  tmrp: TMRP.
  * @param  period: specifies the period register new value.
  * @retval None
  */
void tmrp_set_g2period(tmrp_typedef *tmrp, uint32_t period)
{
    tmrp->g2period = period;
}

/**
  * @brief  Get the TMRP counter register value.
  * @param  tmrp: TMRP.
  * @retval specifies the counter register value.
  */
uint32_t tmrp_get_counter(tmrp_typedef *tmrp)
{
    return (uint32_t)(tmrp->cnt);
}

/**
  * @brief  Get the TMRP period register value.
  * @param  tmrp: TMRP.
  * @retval specifies the period register value.
  */
uint32_t tmrp_get_period(tmrp_typedef *tmrp)
{
    return (uint32_t)(tmrp->period);
}

/**
  * @brief  Get the TMRP period register value.
  * @param  tmrp: TMRP.
  * @retval specifies the period register value.
  */
uint32_t tmrp_get_g2period(tmrp_typedef *tmrp)
{
    return (uint32_t)(tmrp->g2period);
}

/**
  * @brief  Enable or disable the specified TMRP peripheral.
  * @param  tmrp: TMRP.
  * @param  state: state of the tmrp peripheral.
            This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void tmrp_cmd(tmrp_typedef *tmrp, FUNCTIONAL_STATE state)
{
    if (state != DISABLE) {
        tmrp->con |= TMRPCON_TMREN;
    } else {
        tmrp->con &= (uint32_t)(~TMRPCON_TMREN);
    }
}

/**
  * @brief  Enable or disable the specified tmrp interrupt.
  * @param  tmrp: TMRP.
  * @param  isr: Function to be executed for service interruption.
  * @param  pr: Priority of service interruption.
  * @param  interrup_type: TMRP_IT_TYPEDEF.
  * @param  state: the state of the tmrp peripheral.
  *         this parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void tmrp_pic_config(tmrp_typedef *tmrp, isr_t isr, int pr, TMRP_IT_TYPEDEF interrup_type, FUNCTIONAL_STATE state)
{
    uint8_t irq_vector;
    uint32_t tmrp_interrupt_bit = 0;
    uint32_t all_interrupt_type_mask = TMRP_TIE | TMRP_TG2IE;
    if (tmrp == TMRP) {
        irq_vector = IRQn_TMR_PWM;
    }

    if (interrup_type & TMRP_TIE) {
        tmrp_interrupt_bit |= TMRPCON_TIE;
    }

    if (interrup_type & TMRP_TG2IE) {
        tmrp_interrupt_bit |= TMRPCON_TG2IE;
    }

    /*--- Execute configured ---*/
    if (state != DISABLE) {
        tmrp->con |= tmrp_interrupt_bit;
        sys_irq_init(irq_vector, pr, isr);
    } else {
        tmrp->con &= ~tmrp_interrupt_bit;
        if (tmrp_interrupt_bit == all_interrupt_type_mask) {
            PICENCLR = BIT(irq_vector);
        }
    }
}

/**
  * @brief  Get the TMRP interrupt pending.
  * @param  tmrp: TMRP.
  * @param  interrupt_type: TMRP_IT_TYPEDEF.
  * @retval The state of interrupt_type (SET or RESET).
  */
AT(.com_periph.tmr.get)
FLAG_STATE tmrp_get_flag(tmrp_typedef *tmrp, TMRP_IT_TYPEDEF interrupt_type)
{
    uint32_t interrupt_pending_bit = 0;

    if (interrupt_type & TMRP_TIE) {
        interrupt_pending_bit |= TMRPCON_TMRPND;
    }

    if (interrupt_type & TMRP_TG2IE) {
        interrupt_pending_bit |= TMRPCON_TMRG2PND;
    }

    if ((tmrp->con & interrupt_pending_bit) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the TMRP interrupt pending.
  * @param  tmrp: TMRP.
  * @param  interrupt_type: TMRP_IT_TYPEDEF.
  * @retval None
  */
AT(.com_periph.tmr.clear)
void tmrp_clear_flag(tmrp_typedef *tmrp, TMRP_IT_TYPEDEF interrupt_type)
{
    uint32_t interrupt_pending_bit = 0;

    if (interrupt_type & TMRP_TIE) {
        interrupt_pending_bit |= TMRPCPND_TPCLR;
    }

    if (interrupt_type & TMRP_TG2IE) {
        interrupt_pending_bit |= TMRPCPND_TG2PCLR;
    }

    tmrp->cpnd |= interrupt_pending_bit;
}
