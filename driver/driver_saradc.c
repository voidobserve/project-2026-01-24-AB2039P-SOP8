/*
 * @File name    : driver_saradc.c
 * @Author       : Bluetrum IOT Team
 * @Date         : 2024-08-13
 * @Description  : This file provides functions to manage the most functionalities
 *                 of the SARADC peripheral.
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#include "driver_saradc.h"

static saradc_channel_cb_typedef saradc_channel_cb AT(.bss.periph.saradc);

/**
 * @brief  Initializes the saradc mic according to the specified
 *         parameters in the saradc_mic_init_struct.
 * @param  saradc_mic_init_struct: pointer to a sdadc_mic_init_typedef structure that
 *         contains the configuration information for the specified SARADC mic.
 * @retval None
 */
void saradc_mic_init(sdadc_mic_init_typedef *saradc_mic_init_struct)
{
    u32 saradc_clk;
    /* Config MIC digital register */
    saradc_clk = clk_saradc_clk_get(CLK_VALUE_MODE_FREQ);
    SARADC->mcon = 0;

    SARADC->mcon &= ~SADCMCON_CHLENGTH;
    SARADC->mcon |= saradc_mic_init_struct->mask_length << 16;

    SARADC->mcon &= ~SADCMCON_MICTPR;
    SARADC->mcon |= (saradc_clk/saradc_mic_init_struct->sample_rate) & SADCMCON_MICTPR;

     /* Config MIC analog register */
    audio_mic_analog_init(saradc_mic_init_struct->mic_rc, saradc_mic_init_struct->mic_vdd, saradc_mic_init_struct->mic_bias_res, saradc_mic_init_struct->mic_again, saradc_mic_init_struct->micin_trim);
}

/**
 * @brief  Saradc mic enable
 * @param  state: ENABLE or DISABLE
 * @retval None
 */
void saradc_mic_cmd(FUNCTIONAL_STATE state)
{
    if(state != DISABLE) {
        SARADC->mcon |= SADCMCON_MIC_EN;
    } else {
        SARADC->mcon &= (uint32_t)~SADCMCON_MIC_EN;
    }
}

/**
 * @brief  Saradc mic dma enable
 * @param  addr:  buf address， uint32_t
 * @param  len:   buf size, sample points
 * @param  state: ENABLE or DISABLE
 * @retval None
 */
void saradc_mic_dma_cmd(uint32_t addr, uint16_t len, FUNCTIONAL_STATE state)
{
    if(state != DISABLE) {
        SARADC->badr = addr;
        SARADC->dma &= ~SADCDMA_MIC_DMACNT;
        SARADC->dma |= len & SADCDMA_MIC_DMACNT;

        SARADC->mcon |= SADCMCON_MIC_DMAEN;
    } else {
        SARADC->mcon &= (uint32_t)~SADCMCON_MIC_DMAEN;
    }
}

/**
 * @brief  Initializes the saradc peripheral according to the specified
 *         parameters in the saradc_base_init_struct.
 * @param  saradc_base_init_struct: pointer to a sadc_init_typedef structure that
 *         contains the configuration information for the specified SARADC peripheral.
 * @retval None
 */
void saradc_init(saradc_base_init_typedef* saradc_base_init_struct)
{
    u16 baud_reg;
    u32 saradc_clk;

    saradc_clk = clk_saradc_clk_get(CLK_VALUE_MODE_FREQ);

    /* Configure Baud Register */
    baud_reg = (saradc_clk / (2 * saradc_base_init_struct->baud) - 1) & 0x3ff;
    SARADC->baud = baud_reg;

    /* Configure SARADC Mode */
    SARADC->con &= ~SADCCON_ADCMODE;
    SARADC->con |=  saradc_base_init_struct->mode & SADCCON_ADCMODE;

    /* Configure SARADC auto enable analog enable bit */
    SARADC->con &= ~SADCCON_ADCAEN;
    SARADC->con |= saradc_base_init_struct->auto_analog & SADCCON_ADCAEN;

    /* Configure SARADC auto enable analog IO enable bit */
    SARADC->con &= ~SADCCON_ADCANGIOEN;
    SARADC->con |= saradc_base_init_struct->auto_analog_io & SADCCON_ADCANGIOEN;

    memset(&saradc_channel_cb, 0, sizeof(saradc_channel_cb_typedef));
}

/**
 * @brief  Add smpling channel
 * @param  channel: driver_saradc.h ADC Channel
 * @param  pullup_en: 100k PULL UP enable
 * @retval active channel
 */
uint32_t saradc_add_channel(uint32_t channel, SARADC_PULLUP_TYPEDEF pullup_en)
{
    u8 i = 0;

    /* Battery channel config */
    if (channel & ADC_CHANNEL_VBAT) {
        PWRCON0  |= (uint32_t)(1 << 10);
    }

    /* Bandgap channel config */
    if (channel & ADC_CHANNEL_BG) {
        PWRCON0  |= (uint32_t)(0x3 << 21);
    }

    /* PWRKEY channel config */
    if (channel & ADC_CHANNEL_WK0) {
        RTCCON1 |= (uint32_t)(1 << 5);
    }

    /* VDDRTC channel config */
    if (channel & ADC_CHANNEL_VRTC) {
        RTCCON1 |= (uint32_t)(1 << 7);
    }

    /* PB8 channel config */
    if (channel & ADC_CHANNEL_PB8) {
        MICAUDCON0 = (uint32_t)(1 << 6);        // MICLDO bypass AVDD enable
    }

    /* MIC2SAR channel config */
    if (channel & ADC_CHANNEL_MIC2SAR) {
        PWRCON2 &= ~(uint32_t)(0x03 << 5);      // TSEN disable
        MICAUDCON0 &= ~(uint32_t)(1 << 1);      // MIC BG voltage
        MICAUDCON0 = (uint32_t)(1 << 9);        // MIC IN voltage
        channel &= ~ADC_CHANNEL_TSEN;
        channel |= ADC_CHANNEL_MIC2SAR;  //TSEN and MI2SAR multiplexed channel 15
    /* TSEN channel config */
    } else if (channel & ADC_CHANNEL_TSEN) {
        MICAUDCON0 &= ~(uint32_t)(1 << 1);      // MIC BG voltage
        MICAUDCON0 &= ~(uint32_t)(1 << 9);      // MIC IN voltage
        PWRCON2 |= (uint32_t)(0x03 << 5);       // TSEN enable, res_x1
        channel &= ~ADC_CHANNEL_TSEN;
        channel |= ADC_CHANNEL_MIC2SAR;  //TSEN and MI2SAR multiplexed channel 15
    }

    /* Configure each channel */
    for (i = 0; i < 16; i++) {
        if (channel & (0x01 << i)) {
            SARADC->cst &= ~(0x03 << (i * 2));
            SARADC->cst |= (SARADC_ST_3_CLK) << (i * 2);

            SARADC->con &= ~(0x01 << i);
            SARADC->con |= (pullup_en & 0x01) << i;
        }
    }

    saradc_channel_cb.channel |= channel;
    return saradc_channel_cb.channel;
}
/**
 * @brief  remove smpling channel
 * @param  channel: driver_saradc.h ADC Channel
 * @retval active channel
 */
uint32_t saradc_remove_channel(uint32_t remove_ch)
{
    /* Battery channel config */
    if (remove_ch & ADC_CHANNEL_VBAT) {
        PWRCON0 &= ~((uint32_t)(1 << 10));
    }

    /* Bandgap channel config */
    if (remove_ch & ADC_CHANNEL_BG) {
        PWRCON0 &= ~((uint32_t)(0x3 << 21));
    }

    /* PWRKEY channel config */
    if (remove_ch & ADC_CHANNEL_WK0) {
        RTCCON1 &= ~((uint32_t)(1 << 5));
    }

    /* VDDRTC channel config */
    if (remove_ch & ADC_CHANNEL_VRTC) {
        RTCCON1 &= ~((uint32_t)(1 << 7));
    }

    /* MIC2SAR channel config */
    if (remove_ch & ADC_CHANNEL_MIC2SAR) {
        MICAUDCON0 &= ~(1 << 9);
        MICAUDCON0 &= ~(1 << 1);
    }

    /* TSEN channel config */
    if (remove_ch & ADC_CHANNEL_TSEN) {
        PWRCON2 &= ~(0x03 << 5);
    }
    
    /* PB8 channel config */
    if (remove_ch & ADC_CHANNEL_PB8) {
        MICAUDCON0 &= ~(1 << 6);
    }

    saradc_channel_cb.channel &= ~remove_ch;
    return saradc_channel_cb.channel;
}

/**
 * @brief  Deinit all channel config.
 * @retval None.
 */
void saradc_deinit(void)
{
    /* Battery channel config */
    if (PWRCON0 & (uint32_t)(1 << 10)) {
        PWRCON0 &= ~((uint32_t)(1 << 10));
    }

    /* Bandgap channel config */
    if (PWRCON0 & (uint32_t)(0x3 << 21)) {
        PWRCON0 &= ~((uint32_t)(0x3 << 21));
    }

    /* PWRKEY channel config */
    if (RTCCON1 & (uint32_t)(1 << 5)) {
        RTCCON1 &= ~((uint32_t)(1 << 5));
    }

    /* VDDRTC channel config */
    if (RTCCON1 & (uint32_t)(1 << 7)) {
        RTCCON1 &= ~((uint32_t)(1 << 7));
    }


    /* MIC2SAR channel config */
    if ((MICAUDCON0 & (1 << 9)) || (MICAUDCON0 & (1 << 1))) {
        MICAUDCON0 &= ~(1 << 9);
        MICAUDCON0 &= ~(1 << 1);
    }

    /* TSEN channel config */
    if (PWRCON2 & (0x03 << 5)) {
        PWRCON2 &= ~(0x03 << 5);
    }

    /* Clear saradc register config */
    memset(SARADC, 0, sizeof(sadc_typedef));
    saradc_channel_cb.channel = 0;

    /* Disable SARADC clock */
    clk_gate0_cmd(CLK_GATE0_SARADC, CLK_DIS);

    /* Disable SARADC IRQ */
    PICEN &= ~BIT(IRQn_SARADC);
}

/**
  * @brief  Enable or disable the specified SARADC peripheral.
  * @param  state: state of the SARADC peripheral.
            This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void saradc_cmd(FUNCTIONAL_STATE state)
{
    if(state) {
        SARADC->con |= SADCCON_ADCEN;
    } else {
        SARADC->con &= ~(uint32_t)SADCCON_ADCEN;
    }
}

/**
  * @brief  SARADC start kick.
  * @retval None
  */
AT(.com_periph.saradc.kick)
void saradc_kick_start(void)
{
    uint32_t adc_ch = saradc_channel_cb.channel;

    if (!adc_ch) {
        return;
    }

    if (adc_ch & ADC_CHANNEL_TSEN) {
        adc_ch &= ~ADC_CHANNEL_TSEN;
        adc_ch |= ADC_CHANNEL_MIC2SAR;
    }

    while(SARADC->ch & 0xffff);

    SARADC->ch = (adc_ch & 0xffff);
}

/**
  * @brief  Set the SARADC baud register value.
  * @param  baud: specifies the baud register new value.
  * @retval None
  */
void saradc_set_baud(uint32_t baud)
{
    uint16_t baud_reg;
    uint32_t saradc_clk;

    saradc_clk = clk_saradc_clk_get(CLK_VALUE_MODE_FREQ);

    /* Configure Baud Register */
    baud_reg = ((saradc_clk / (2 * baud)) -1) & 0x3ff;
    SARADC->baud = baud_reg;
}

/**
 * @brief  Enable or disable the specified SARADC interrupt.
 * @param  isr: Function to be executed for service interruption.
 * @param  pr: Priority of service interruption.
 * @param  interrupt_type: SARADC_IT_TYPEDEF
 * @param  state: state of the SARADC peripheral.
 *         this parameter can be: EANBLE or DISABLE.
 * @retval None
 */
void saradc_pic_config(isr_t isr, int pr, SARADC_IT_TYPEDEF interrupt_type, FUNCTIONAL_STATE state)
{
    uint32_t saradc_interrupt_bit = 0;
    uint32_t mic_interrupt_bit = 0;

    /* Get interrupt ctrl bit */
    if (interrupt_type & SARADC_IT_FINISHED) {
        saradc_interrupt_bit |= SADCCON_ADCIE;
    }

    if (interrupt_type & SARADC_MIC_SINGLE_SAMPLE) {
        mic_interrupt_bit |= SADCMCON_MIC_IE;
    }

    if (interrupt_type & SARADC_MIC_DMA_HALF_DONE) {
        mic_interrupt_bit |= SADCMCON_MIC_HDONE_IE;
    }

    if (interrupt_type & SARADC_MIC_DMA_ALL_DONE) {
        mic_interrupt_bit |= SADCMCON_MIC_ADONE_IE;
    }

    if(state != DISABLE) {
        SARADC->con |= saradc_interrupt_bit;
        SARADC->mcon |= mic_interrupt_bit;
        sys_irq_init(IRQn_SARADC, pr, isr);
    } else {
        SARADC->con &= ~saradc_interrupt_bit;
        SARADC->mcon &= ~mic_interrupt_bit;
        PICEN &= ~BIT(IRQn_SARADC);
    }
}

/**
 * @brief  Get the SARADC pending.
 * @param  flag_type: SARADC_IT_TYPEDEF
 * @retval The state of flag_type (SET or RESET).
 */
AT(.com_periph.saradc.get)
FLAG_STATE saradc_get_flag(SARADC_IT_TYPEDEF flag_type)
{
    u32 saradc_flag_pending_bit = 0;
    u32 mic_flag_pending_bit = 0;

    if (flag_type & SARADC_IT_FINISHED) {
        saradc_flag_pending_bit |= SADCCH_ADCPND;
    }

    if (flag_type & SARADC_MIC_SINGLE_SAMPLE) {
        mic_flag_pending_bit |= SADCDMA_MIC_SMP_PND;
    }

    if (flag_type & SARADC_MIC_DMA_HALF_DONE) {
        mic_flag_pending_bit |= SADCDMA_MIC_HDONE_PEND;
    }

    if (flag_type & SARADC_MIC_DMA_ALL_DONE) {
        mic_flag_pending_bit |= SADCDMA_MIC_ADONE_PEND;
    }

    if (((SARADC->ch & saradc_flag_pending_bit) && saradc_flag_pending_bit) != RESET) {
        return SET;
    } else if (((SARADC->dma & mic_flag_pending_bit) && mic_flag_pending_bit) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
 * @brief  Clear the SARADC pending.
 * @param  flag_type: SARADC_IT_TYPEDEF
 * @retval None
 */
AT(.com_periph.saradc.clear)
void saradc_clear_flag(SARADC_IT_TYPEDEF flag_type)
{
    u32 flag_pending_bit = 0;

    if (flag_type & SARADC_IT_FINISHED) {
        flag_pending_bit |= SADCCPND_ADC_PEND;
    }

    if (flag_type & SARADC_MIC_SINGLE_SAMPLE) {
        flag_pending_bit |= SADCCPND_MIC_SMP_PND;
    }

    if (flag_type & SARADC_MIC_DMA_HALF_DONE) {
        flag_pending_bit |= SADCCPND_MIC_HDONE_PEND;
    }

    if (flag_type & SARADC_MIC_DMA_ALL_DONE) {
        flag_pending_bit |= SADCCPND_MIC_ADONE_PEND;
    }

    SARADC->cpnd |= flag_pending_bit;
}

/**
  * @brief  Get the SARADC all channel value.
  * @param  None.
  * @retval None.
  */

AT(.com_text.saradc.done)
void saradc_get_result(void)
{
    for(uint i=0; i<SARADC_MAX_CH; i++) {
        if(saradc_channel_cb.channel & BIT(i)) {
            saradc_channel_cb.value[i] = SARADC->dat[i];
        }
    }
}

/**
  * @brief  Get the SARADC specifies channel value.
  * @param  adc_chx: the channel that wants to query.
  * @retval saradc data.
  */
AT(.com_periph.saradc.get_data)
uint16_t saradc_get_channel_value(uint32_t adc_chx)
{
    u8 i = 0;

    while (i < 17) {
        if ((adc_chx & BIT(i)) && (saradc_channel_cb.channel & BIT(i))) {
            break;
        }
        i++;
    }

    if (adc_chx == ADC_CHANNEL_VBAT) {
        return saradc_channel_cb.value[14] * pmu_get_vbatdet() / 1000;
    } else if (adc_chx == ADC_CHANNEL_MIC2SAR) {
        return saradc_channel_cb.value[15];
    } else if (adc_chx == ADC_CHANNEL_TSEN) {
        return saradc_channel_cb.value[15];
    } else if (i < 16) {
        return saradc_channel_cb.value[i];
    } else {
        return 0;
    }
}
