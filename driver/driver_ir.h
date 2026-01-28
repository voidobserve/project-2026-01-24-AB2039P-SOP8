/**
******************************************************************************************************************************
*
*@file driver_ir.h
*
*@brief Header file for IR driver
*
*Copyright (c) 2024, BLUETRUM
******************************************************************************************************************************
**/
#ifndef _IR_H_
#define _IR_H_

#include "driver_com.h"

////////// irrx
typedef enum {
    IRRX_FLAG_RXPND          = BIT(0),
    IRRX_FLAG_KEYRELS        = BIT(1),
} IRRX_FLAG_TYPEDEF;

typedef enum
{
    IRRX_DATA_SELECT_32BIT = 0x00000000,
    IRRX_DATA_SELECT_16BIT = 0x00000004,
}irrx_data_select_t;

typedef enum
{
    IRRX_WAKUP_SLEEP_DISABLE = 0x00000000,
    IRRX_WAKUP_SLEEP_ENABLE  = 0x00000010,
}irrx_wakup_en_t;

typedef enum
{
    IRRX_FILTER_DISABLE = 0x00000000,
    IRRX_FILTER_ENABLE  = 0x00000001,
}irrx_filter_en_t;

typedef enum
{
    IRRX_FILTER_SRCS_RXIN   = 0x00000000,
    IRRX_FILTER_SRCS_TMRIN  = 0x00000002,
}irrx_filter_srcs_t;

typedef struct
{
    irrx_wakup_en_t wakup_en;
    irrx_data_select_t data_format;
    irrx_filter_en_t filter_en;
    irrx_filter_srcs_t filter_srcs;
    u8 filter_len;
}irrx_param_t;


////////// irtx
typedef enum {
    IRTX_FLAG_TX               = BIT(0),
    IRTX_FLAG_RDMA_HALF        = BIT(1),
    IRTX_FLAG_RDMA_ALL         = BIT(2),
} IRTX_FLAG_TYPEDEF;

typedef enum
{
    IRTX_INV_DIS,
    IRTX_INV_EN = 0x00000004,
}irtx_inv_en_t;

typedef enum
{
    IRTX_MOD_DIS,
    IRTX_MOD_EN = 0x00000010,
}irtx_mod_en_t;

typedef enum
{
    IRTX_MOD_CLKSEL_3M,
    IRTX_MOD_CLKSEL_4M,
}irtx_mod_clksel_t;

typedef enum
{
    IRTX_DMA_MODE_DIS,
    IRTX_DMA_MODE_EN = 0x00000001,
}irtx_dma_en_t;

typedef struct
{
    irtx_mod_en_t carrier_en;
    irtx_mod_clksel_t mod_clksel;        // Tx Modulation Clock Select.
    uint16_t ircw_duty;                  // Tx Carrier Duty = (ircw_duty) / (ircw_length + 1))
    uint16_t ircw_length;                // Tx Carrier Freq = (3M or 4M)  / (ircw_length + 1))
}irtx_carrier_config_t;

typedef struct
{
    irtx_dma_en_t en;
}irtx_rdma_config_t;

typedef struct
{
    irtx_inv_en_t invert_en;
    irtx_carrier_config_t carrier_config;
    irtx_rdma_config_t rdma_config;
}irtx_param_t;

//IR RX
void irrx_init(irrx_param_t *irrx_param);
void irrx_pic_config(isr_t isr, int pr, IRRX_FLAG_TYPEDEF flag_type, FUNCTIONAL_STATE state);
FLAG_STATE irrx_get_flag(IRRX_FLAG_TYPEDEF flag_type);
void irrx_clear_flag(IRRX_FLAG_TYPEDEF flag_type);
u32 irrx_get_data(void);
void irrx_cmd(FUNCTIONAL_STATE state);
void irrx_deinit(void);

//IR TX
void irtx_init(irtx_param_t *irtx_param);
void irtx_pic_config(isr_t isr, int pr, IRTX_FLAG_TYPEDEF flag_type, FUNCTIONAL_STATE state);
FLAG_STATE irtx_get_flag(IRTX_FLAG_TYPEDEF flag_type);
void irtx_clear_flag(IRTX_FLAG_TYPEDEF flag_type);
void irtx_cmd(FUNCTIONAL_STATE state);
void irtx_kick(void);
void irtx_dma_kick(uint32_t addr, uint16_t len);
void irtx_deinit(void);

#endif
