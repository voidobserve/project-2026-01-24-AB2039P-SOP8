/*
 * @File name    : driver_saradc.h
 * @Author       : Bluetrum IOT Team
 * @Date         : 2024-05-27
 * @Description  : This file contains all the functions prototypes for the SARADC library.
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#ifndef _DRIVER_SARADC_H
#define _DRIVER_SARADC_H

#include "driver_com.h"

#define SARADC_MAX_CH       16

/**
 * @brief ADC Channel
 */
#define ADC_CHANNEL_MICOUT              0x00000001  // channel 0
#define ADC_CHANNEL_PB2                 0x00000002  // channel 1
#define ADC_CHANNEL_PB3                 0x00000004  // channel 2
#define ADC_CHANNEL_PB4                 0x00000008  // channel 3
#define ADC_CHANNEL_PB5                 0x00000010  // channel 4
#define ADC_CHANNEL_PB6                 0x00000020  // channel 5
#define ADC_CHANNEL_PB7                 0x00000040  // channel 6
#define ADC_CHANNEL_PB8                 0x00000080  // channel 7
#define ADC_CHANNEL_PB9                 0x00000100  // channel 8
#define ADC_CHANNEL_PB10                0x00000200  // channel 9
#define ADC_CHANNEL_PB11                0x00000400  // channel 10
#define ADC_CHANNEL_VRTC                0x00000800  // channel 11
#define ADC_CHANNEL_WK0                 0x00001000  // channel 12
#define ADC_CHANNEL_BG                  0x00002000  // channel 13
#define ADC_CHANNEL_VBAT                0x00004000  // channel 14
#define ADC_CHANNEL_MIC2SAR             0x00008000  // channel 15
#define ADC_CHANNEL_TSEN                0x00010000  // channel 15'

/**
 * @brief SARADC ANALOG BIT
 */
typedef enum {
    SARADC_ANALOG_BIT_VBAT              = 0x01,
    SARADC_ANALOG_BIT_BG                = 0x02,
    SARADC_ANALOG_BIT_WK0               = 0x04 ,
    SARADC_ANALOG_BIT_VRTC              = 0x08,
    SARADC_ANALOG_BIT_MIC2SAR           = 0x10,
    SARADC_ANALOG_BIT_TSEN              = 0x20,
} SARADC_ANALOG_BIT_TYPEDEF;

/**
 * @brief SARADC Flag Definition
 */
typedef enum {
    SARADC_IT_FINISHED                  = 0x01,
    SARADC_MIC_SINGLE_SAMPLE            = 0x02,
    SARADC_MIC_DMA_HALF_DONE            = 0x04,
    SARADC_MIC_DMA_ALL_DONE             = 0x08,
} SARADC_IT_TYPEDEF;

/**
 * @brief SARADC Analog Mode Enumeration
 */
typedef enum {
    SARADC_MODE_NORMAL                  = 0x00000000,
    SARADC_MODE_TRIM                    = 0x00100000,
} SARADC_MODE_TYPEDEF;

/**
 * @brief SARADC Auto Enable Analog Enumeration
 */
typedef enum {
    SARADC_AUTO_ENABLE_ANALOG_DIS       = 0x00000000,
    SARADC_AUTO_ENABLE_ANALOG_EN        = 0x00080000,
} SARADC_AUTO_ENABLE_ANALOG_TYPEDEF;

/**
 * @brief SARADC Auto Enable IO Analog Enumeration
 */
typedef enum {
    SARADC_AUTO_ENABLE_ANALOG_IO_DIS    = 0x00000000,
    SARADC_AUTO_ENABLE_ANALOG_IO_EN     = 0x00040000,
} SARADC_AUTO_ENABLE_ANALOG_IO_TYPEDEF;

/**
 * @brief SARADC Internel Pullup Enumeration
 */
typedef enum {
    SARADC_PULLUP_DIS                   = 0x00000000,
    SARADC_PULLUP_EN                    = 0x00000001,
} SARADC_PULLUP_TYPEDEF;

/**
 * @brief SARADC setup timing enumeration
 */
typedef enum {
    SARADC_ST_0_CLK                     = 0x00,
    SARADC_ST_3_CLK                     = 0x01,
    SARADC_ST_6_CLK                     = 0x02,
    SARADC_ST_13_CLK                    = 0x03,
} SARADC_SETUP_TYPEDEF;

/**
 * @brief SARADC Base Init Structure
 */
typedef struct {
    uint32_t                                baud;
    SARADC_MODE_TYPEDEF                     mode;
    SARADC_AUTO_ENABLE_ANALOG_TYPEDEF       auto_analog;
    SARADC_AUTO_ENABLE_ANALOG_IO_TYPEDEF    auto_analog_io;
} saradc_base_init_typedef;

/**
 * @brief SARADC Channel call back structure
 */
typedef struct {
    volatile uint32_t                       channel;
    volatile uint16_t                       value[SARADC_MAX_CH];
} saradc_channel_cb_typedef;

/**
 * @brief SARADC MIC sampling rate enumeration
 */
typedef enum {
    SARADC_MIC_MIC_SR_8K                = 8000,
    SARADC_MIC_MIC_SR_16K               = 16000,
    SARADC_MIC_MIC_SR_32K               = 32000,
    SARADC_MIC_MIC_SR_48K               = 48000,
    SARADC_MIC_MIC_SR_64K               = 64000,
    SARADC_MIC_MIC_SR_96K               = 96000,
} SARADC_MIC_MIC_SR_TYPEDEF;

/**
 * @brief SARADC MIC Init structure
 */
typedef struct{
    uint16_t mask_length;
    SARADC_MIC_MIC_SR_TYPEDEF sample_rate;
    AUDIO_MIC_TYPE_TYPEDEF mic_rc;
    AUDIO_MIC_VDD_TYPEDEF mic_vdd;
    AUDIO_MIC_BIAS_RES_TYPEDEF mic_bias_res;
    AUDIO_MIC_ANA_GAIN_TYPEDEF mic_again;
    uint16_t micin_trim;
} sdadc_mic_init_typedef;

void saradc_init(saradc_base_init_typedef* saradc_init_struct);
void saradc_deinit(void);
uint32_t saradc_add_channel(uint32_t channel, SARADC_PULLUP_TYPEDEF pullup_en);
void saradc_cmd(FUNCTIONAL_STATE state);
void saradc_kick_start(void);
void saradc_set_baud(uint32_t baud);
void saradc_pic_config(isr_t isr, int pr, SARADC_IT_TYPEDEF interrupt_type, FUNCTIONAL_STATE state);
FLAG_STATE saradc_get_flag(SARADC_IT_TYPEDEF interrupt_type);
void saradc_clear_flag(SARADC_IT_TYPEDEF interrupt_type);
void saradc_get_result(void);
uint16_t saradc_get_channel_value(uint32_t adc_chx);

void saradc_mic_init(sdadc_mic_init_typedef *saradc_mic_init_struct);
void saradc_mic_cmd(FUNCTIONAL_STATE state);
void saradc_mic_dma_cmd(uint32_t addr, uint16_t len, FUNCTIONAL_STATE state);
#endif  // _DRIVER_SARADC_H
