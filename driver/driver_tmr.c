/*
 * @File name    : driver_tmr.c
 * @Author       : Bluetrum IOT Team
 * @Date         : 2024-08-20
 * @Description  : This file provides functions to manage the most functionalities
 *                 of the TMR peripheral.
 *
 * Copyright (c) by Bluetrum, All Rights reserved.
 */
#include "driver_tmr.h"

/**
  * @brief  Initializes the timer base peripheral according to the specified
  *         parameters in the tmr_base_init_typedef.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  tmr_base_init_struct: pointer to a tmr_base_init_typedef structure that
  *         contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void tmr_base_init(tmr_typedef *tmrx, tmr_base_init_typedef *tmr_base_init_struct)
{
    //---------- tmr controller register ----------//
    tmrx->con &= ~(uint32_t)TMRxCON_TICKEN;
    tmrx->con |= (uint32_t)tmr_base_init_struct->tick_en;

    tmrx-> cnt = TMRxCNT;

    tmrx->period &= ~(uint32_t)TMRxPR;
    tmrx->period = (uint32_t)tmr_base_init_struct->period;

    tmrx->con &= ~(uint32_t)TMRxCON_TMRMODE;
    tmrx->con |= (uint32_t)tmr_base_init_struct->tmr_mode;

    tmrx->con &= ~(uint32_t)TMRxCON_PDIVSEL;
    tmrx->con |= (uint32_t)tmr_base_init_struct->clock_div;

    tmrx->con &= ~(uint32_t)TMRxCON_PCLKSEL;
    tmrx->con |= (uint32_t)tmr_base_init_struct->clock_source;
}

/**
 * @brief  De-initialize the specified tmr peripheral.
 * @retval None
 */
void tmr_deinit(tmr_typedef *tmrx)
{
    tmrx->con = 0;

    if (tmrx == TMR0) {
        clk_gate0_cmd(CLK_GATE0_TMR0, CLK_DIS);
    } else if (tmrx == TMR1) {
        clk_gate0_cmd(CLK_GATE0_TMR1, CLK_DIS);
    } else if (tmrx == TMR2) {
        clk_gate0_cmd(CLK_GATE0_TMR2, CLK_DIS);
    } else if (tmrx == TMR3) {
        clk_gate1_cmd(CLK_GATE1_TMR3, CLK_DIS);
    }
}

/**
  * @brief  Set the TMR counter register value.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  cnt: specifies the counter register new value.
  * @retval None
  */
void tmr_set_counter(tmr_typedef *tmrx, uint32_t cnt)
{
    tmrx->cnt = cnt;
}

/**
  * @brief  Set the TMR period register value.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  period: specifies the period register new value.
  * @retval None
  */
void tmr_set_period(tmr_typedef *tmrx, uint32_t period)
{
    tmrx->period = period;
}

/**
  * @brief  Get the TMR counter register value.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @retval specifies the counter register value.
  */
uint32_t tmr_get_counter(tmr_typedef *tmrx)
{
    return (uint32_t)(tmrx->cnt);
}

/**
  * @brief  Get the TMR period register value.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @retval specifies the period register value.
  */
uint32_t tmr_get_period(tmr_typedef *tmrx)
{
    return (uint32_t)(tmrx->period);
}

/**
  * @brief  Enable or disable the specified TMR peripheral.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  state: state of the TMRx peripheral.
            This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void tmr_cmd(tmr_typedef *tmrx, FUNCTIONAL_STATE state)
{
    if (state != DISABLE) {
        tmrx->con |= TMRxCON_TMREN;
    } else {
        tmrx->con &= (uint32_t)(~TMRxCON_TMREN);
    }
}

/**
  * @brief  Get the TMR capture register value.
  * @param  tmrx: where x can be (3) to select the TMR peripheral.
  * @retval specifies the capture register value.
  */
uint32_t tmr_get_capture(tmr_typedef *tmrx)
{
    if (tmrx == TMR0 || tmrx == TMR1) {
        return ~((uint32_t)0);
    }
    return (uint32_t)(tmrx->capture_val);
}

/**
  * @brief  Enable or disable the specified TMRx interrupt.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  isr: Function to be executed for service interruption.
  * @param  pr: Priority of service interruption.
  * @param  interrup_type: specifies the TRMx interrupt sources to be enable or disable.
  *         this parameter can be one of the following values:
  *             @arg TMR_IT_UPDATE1: TMR(1..2) overflow interrupt enable bit.
  *             @arg TMR_IT_CAP: TMR(3..5) capture interrupt enable bit.
  *             @arg TMR_IT_UPDATE2: TMR(3..5) overflow interrupt enable bit.
  * @param  state: the state of the TMRx peripheral.
  *         this parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void tmr_pic_config(tmr_typedef *tmrx, isr_t isr, int pr, TMR_IT_TYPEDEF interrup_type, FUNCTIONAL_STATE state)
{
    uint8_t irq_vector;
    uint32_t tmr_interrupt_bit = 0;
    uint32_t all_interrupt_type_mask = TMR_IT_UPDATE | TMR_IT_CAPTURE;

    if (interrup_type == 0) {
        return;
    }

    if (tmrx == TMR0 || tmrx == TMR1) {
        if (interrup_type & TMR_IT_CAPTURE) {
            interrup_type &= ~TMR_IT_CAPTURE;
        }
    }

    /*--- Get interrupt vector ---*/
    if (tmrx == TMR0) {
        irq_vector = IRQn_TMR0;
    }else if (tmrx == TMR1) {
        irq_vector = IRQn_TMR1;
    } else if (tmrx == TMR2) {
        irq_vector = IRQn_TMR2;
    } else if (tmrx == TMR3) {
        irq_vector = IRQn_TMR3;
    } else {
        return;
    }

    /*--- Get interrupt ctrl bit ---*/
    if (interrup_type & TMR_IT_UPDATE) {
        tmr_interrupt_bit |= TMRxCON_TIE;
    }

    if (interrup_type & TMR_IT_CAPTURE) {
        tmr_interrupt_bit |= TMRxCON_CPTIE;
    }

    /*--- Execute configured ---*/
    if (state != DISABLE) {
        tmrx->con |= tmr_interrupt_bit;
        sys_irq_init(irq_vector, pr, isr);
    } else {
        tmrx->con &= ~tmr_interrupt_bit;
        if (tmr_interrupt_bit == all_interrupt_type_mask) {
            PICENCLR = BIT(irq_vector);
        }
    }
}

/**
  * @brief  Get the TMR interrupt pending.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  interrupt_type: specifies the IT to clear.
  *         this parameter can be one of the following values:
  *             @arg TMR_IT_UPDATE: TMR overflow interrupt.
  *             @arg TMR_IT_CAPTURE: TMR capture interrupt.
  * @retval The state of interrupt_type (SET or RESET).
  */
AT(.com_periph.tmr.get)
FLAG_STATE tmr_get_flag(tmr_typedef *tmrx, TMR_IT_TYPEDEF interrupt_type)
{
    uint32_t interrupt_pending_bit = 0;

    if (tmrx == TMR0 || tmrx == TMR1) {
        if (interrupt_type & TMR_IT_CAPTURE) {
            return RESET;
        } else if (interrupt_type & TMR_IT_UPDATE) {
            interrupt_pending_bit |= TMRxCON_TMRPND;
        }
    } else if (tmrx == TMR2 || tmrx == TMR3) {
        if (interrupt_type & TMR_IT_CAPTURE) {
            interrupt_pending_bit |= TMRxCON_CPTPND;
        }
        if (interrupt_type & TMR_IT_UPDATE) {
            interrupt_pending_bit |= TMRxCON_TMRPND;
        }
    } else {
        return RESET;
    }

    if ((tmrx->con & interrupt_pending_bit) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the TMR interrupt pending.
  * @param  tmrx: where x can be (0..3) to select the TMR peripheral.
  * @param  interrupt_type: specifies the interrupt to clear.
  *         this parameter can be one of the following values:
  *             @arg TMR_IT_UPDATE: TMR overflow interrupt.
  *             @arg TMR_IT_CAPTURE: TMR capture interrupt.
  * @retval None
  */
AT(.com_periph.tmr.clear)
void tmr_clear_flag(tmr_typedef *tmrx, TMR_IT_TYPEDEF interrupt_type)
{
    uint32_t interrupt_pending_bit = 0;

    if (tmrx == TMR0 || tmrx == TMR1) {
        if (interrupt_type & TMR_IT_UPDATE) {
            interrupt_pending_bit |= TMRxCPND_TPCLR;
        }
    } else if (tmrx == TMR2 || tmrx == TMR3) {
        if (interrupt_type & TMR_IT_CAPTURE) {
            interrupt_pending_bit |= TMRxCPND_CPTPCLR;
        } else if (interrupt_type & TMR_IT_UPDATE) {
            interrupt_pending_bit |= TMRxCPND_TPCLR;
        }
    } else {
        return;
    }

    tmrx->cpnd |= interrupt_pending_bit;
}
