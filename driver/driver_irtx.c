/**
******************************************************************************************************************************
*
*@file driver_irtx.c
*
*@brief Source file for IR tx driver
*
*Copyright (c) 2024, BLUETRUM
******************************************************************************************************************************
**/
#include "driver_ir.h"
#include "driver_gpio.h"
#include "macro.h"
#include "driver_clk.h"

/**
  * @brief 
  * @param  irrx_param: irrx params
  * @retval None
  */
void irtx_init(irtx_param_t *irtx_param)
{
    /* Load the register value to variable */
    u32 tmp_reg = IRTX->con;

    /* Clear value need to configure */
    tmp_reg &= ~(uint32_t)(IRTXCON_INV | \
                           IRTXCON_CARRIER_EN | \
                           IRTXCON_CW_LENGTH | \
                           IRTXCON_CW_DUTY);

    /* Config output data all invert */
    tmp_reg |= irtx_param->invert_en & IRTXCON_INV;

    if (irtx_param->carrier_config.carrier_en) {
        clk_irtx_mod_clk_set(irtx_param->carrier_config.mod_clksel);
        tmp_reg |= irtx_param->carrier_config.carrier_en & IRTXCON_CARRIER_EN;
        tmp_reg |= (irtx_param->carrier_config.ircw_length << 8) & IRTXCON_CW_LENGTH;
        tmp_reg |= (irtx_param->carrier_config.ircw_duty << 16) & IRTXCON_CW_DUTY;
    }

    IRTX->con = tmp_reg;


    tmp_reg = IRTX->dmacon;
    tmp_reg &= ~(uint32_t)IRTX_RDMACON_EN;

    if (irtx_param->rdma_config.en) {
        tmp_reg |= irtx_param->rdma_config.en & IRTX_RDMACON_EN;
    }

    IRTX->dmacon = tmp_reg;
}

void irtx_pic_config(isr_t isr, int pr, IRTX_FLAG_TYPEDEF flag_type, FUNCTIONAL_STATE state)
{
    u32 flag_tx_pending_bit = 0;
    u32 flag_dma_pending_bit = 0;

    if (flag_type == 0) {
        return;
    }

    if (flag_type & IRTX_FLAG_TX) {
        flag_tx_pending_bit |= IRTXCON_IE;
    }

    if (flag_type & IRTX_FLAG_RDMA_HALF) {
        flag_dma_pending_bit |= IRTX_RDMACON_HPND_IE;
    }

    if (flag_type & IRTX_FLAG_RDMA_ALL) {
        flag_dma_pending_bit |= IRTX_RDMACON_APND_IE;
    }

    if (state != DISABLE) {
        IRTX->con |= flag_tx_pending_bit;
        IRTX->dmacon |= flag_dma_pending_bit;
        sys_irq_init(IRQn_IR_QDEC_LEDC, pr, isr);
    } else {
        IRTX->con &= ~flag_tx_pending_bit;
        IRTX->dmacon &= ~flag_dma_pending_bit;
    }
}

AT(.com_periph.irtx.flag)
FLAG_STATE irtx_get_flag(IRTX_FLAG_TYPEDEF flag_type)
{
    u32 flag_tx_pending_bit = 0;
    u32 flag_dma_pending_bit = 0;

    if (flag_type & IRTX_FLAG_TX) {
        flag_tx_pending_bit |= IRTXPEND_PND;
    }

    if (flag_type & IRTX_FLAG_RDMA_HALF) {
        flag_dma_pending_bit |= IRTX_RDMA_HPND;
    }

    if (flag_type & IRTX_FLAG_RDMA_ALL) {
        flag_dma_pending_bit |= IRTX_RDMA_APND;
    }

    if (((IRTX->pend & flag_tx_pending_bit) || (IRTX->dmapend & flag_dma_pending_bit)) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

AT(.com_periph.irtx.flag)
void irtx_clear_flag(IRTX_FLAG_TYPEDEF flag_type)
{
    u32 flag_tx_pending_bit = 0;
    u32 flag_dma_pending_bit = 0;

    if (flag_type & IRTX_FLAG_TX) {
        flag_tx_pending_bit |= IRTXPEND_PND;
    }

    if (flag_type & IRTX_FLAG_RDMA_HALF) {
        flag_dma_pending_bit |= IRTX_RDMA_HPND;
    }

    if (flag_type & IRTX_FLAG_RDMA_ALL) {
        flag_dma_pending_bit |= IRTX_RDMA_APND;
    }

    if (flag_tx_pending_bit) {
        IRTX->pend |= flag_tx_pending_bit;
    }

    if (flag_dma_pending_bit) {
        IRTX->dmapend |= flag_dma_pending_bit;
    }
}

void irtx_cmd(FUNCTIONAL_STATE state)
{
    if (state != DISABLE) {
        IRTX->con |= IRTXCON_EN;
    } else {
        IRTX->con &= ~IRTXCON_EN;
    }
}

void irtx_kick(void)
{
    IRTX->con |= IRTXCON_KST;
    while(!irtx_get_flag(IRTX_FLAG_TX));
    irtx_clear_flag(IRTX_FLAG_TX);
}

void irtx_dma_kick(uint32_t addr, uint16_t len)
{
    IRTX->dmaiadr = addr;
    IRTX->dmaisize = (len & IRTX_DMAISIZE_SIZE);
}

void irtx_deinit(void)
{
    IRTX->con &= ~IRTXCON_EN;
    IRTX->dmacon &= ~IRTX_RDMACON_EN;
    clk_gate1_cmd(CLK_GATE1_IRTX, CLK_DIS);
}