/*
 * @File name    : driver_com.h
 * @Author       : Bluetrum IOT Team
 * @Date         : 2024-06-11
 * @Description  : AB202X Device Peripheral Access Layer Header File.
 *                 This file contains all the peripheral register's definitions, bits
 *                 definitions and memory mapping for MATE devices.
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#ifndef _DRIVER_COM_H
#define _DRIVER_COM_H

#include "global.h"
#include "api.h"
#include "driver_clk.h"

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FUNCTIONAL_STATE;
typedef enum {RESET = 0, SET = !RESET} FLAG_STATE, IT_STATE;
typedef enum {FAILED = 0, SUCCESS = !FAILED} STATUS_STATE;

//--------------------------- SFR BASE DECLARATION ---------------------------//
#define SFR_BASE                            0x00000100    // address 0~255 is reserved
#define SFR0_BASE                           (SFR_BASE + 0x000)
#define SFR1_BASE                           (SFR_BASE + 0x100)
#define SFR2_BASE                           (SFR_BASE + 0x200)
#define SFR3_BASE                           (SFR_BASE + 0x300)
#define SFR4_BASE                           (SFR_BASE + 0x400)
#define SFR5_BASE                           (SFR_BASE + 0x500)
#define SFR6_BASE                           (SFR_BASE + 0x600)
#define SFR7_BASE                           (SFR_BASE + 0x700)
#define SFR8_BASE                           (SFR_BASE + 0x800)
#define SFR9_BASE                           (SFR_BASE + 0x900)
#define SFR10_BASE                          (SFR_BASE + 0xa00)
#define SFR11_BASE                          (SFR_BASE + 0xb00)
#define SFR12_BASE                          (SFR_BASE + 0xc00)
#define SFR13_BASE                          (SFR_BASE + 0xd00)
#define SFR14_BASE                          (SFR_BASE + 0xe00)
#define SFR15_BASE                          (SFR_BASE + 0xf00)

//-------------------------------- SFR Group0 --------------------------------//
#define TICK0_BASE                          (SFR0_BASE + 0x01*4)
#define TICK1_BASE                          (SFR0_BASE + 0x05*4)
#define UART0_BASE                          (SFR0_BASE + 0x10*4)
#define TMR0_BASE                           (SFR0_BASE + 0x14*4)
#define WDT_BASE                            (SFR0_BASE + 0x1a*4)
#define SD0_BASE                            (SFR0_BASE + 0x20*4)
#define SPI0_BASE                           (SFR0_BASE + 0x2a*4)
#define TMR1_BASE                           (SFR0_BASE + 0x35*4)
#define TMR2_BASE                           (SFR0_BASE + 0x3a*4)

//---------------------------------- SFR Group1 -----------------------------------//

//---------------------------------- SFR Group3 -----------------------------------//
#define HSUART_BASE                         (SFR3_BASE + 0x30*4)

//---------------------------------- SFR Group4 -----------------------------------//

//---------------------------------- SFR Group5 -----------------------------------//
#define SARADC_BASE                         (SFR5_BASE + 0x20*4)

//---------------------------------- SFR Group6 -----------------------------------//
#define GPIOB_BASE                          (SFR6_BASE + 0x10*4)
#define FUNCMCON_BASE                       (SFR6_BASE + 0x30*4)

//---------------------------------- SFR Group7 -----------------------------------//
#define GPIOG_BASE                          (SFR7_BASE + 0x00*4)
#define KEYSCAN_BASE                        (SFR7_BASE + 0x19*4)
#define IRTX_BASE                           (SFR7_BASE + 0x25*4)
#define IRRX_BASE                           (SFR7_BASE + 0x2f*4)

//---------------------------------- SFR Group8 -----------------------------------//

//---------------------------------- SFR Group9 -----------------------------------//
#define TMR3_BASE                           (SFR9_BASE + 0x00*4)
#define SPI1_BASE                           (SFR9_BASE + 0x20*4)
#define FREQDET_BASE                        (SFR9_BASE + 0x28*4)
#define TMRP_BASE                           (SFR9_BASE + 0x30*4)

//---------------------------------- SFR Group10 -----------------------------------//

//---------------------------------- SFR Group12 -----------------------------------//
#define LEDC_BASE                           (SFR12_BASE + 0x30*4)

/**
 * @brief PERIPHERAL DECLARATION
 */
#define GPIOB_REG                           ((gpio_typedef *) GPIOB_BASE)
#define FUNCMAP                             ((func_map_typedef *) FUNCMCON_BASE)
#define TMR0                                ((tmr_typedef *) TMR0_BASE)
#define TMR1                                ((tmr_typedef *) TMR1_BASE)
#define TMR2                                ((tmr_typedef *) TMR2_BASE)
#define TMR3                                ((tmr_typedef *) TMR3_BASE)
#define UART                                ((uart_typedef *) UART0_BASE)
#define HSUART                              ((hsuart_typedef *) HSUART_BASE)
#define SPI0                                ((spi_typedef *) SPI0_BASE)
#define SPI1                                ((spi_typedef *) SPI1_BASE)
#define WDT                                 ((wdt_typedef *) WDT_BASE)
#define SARADC                              ((sadc_typedef *) SARADC_BASE)
#define KEYSCAN                             ((keyscan_typedef *) KEYSCAN_BASE)
#define IRTX                                ((irtx_typedef *) IRTX_BASE)
#define IRRX                                ((irrx_typedef *) IRRX_BASE)
#define LEDC                                ((ledc_typedef *) LEDC_BASE)
#define TICK                                ((tick_typedef *) TICK0_BASE)
#define TMRP                                ((tmrp_typedef *) TMRP_BASE)

/*---------------------------------------------------------------------------------*/
/*                                     TICK                                        */
/*---------------------------------------------------------------------------------*/
/******************** Bit definition for TICKCON register ********************/
#define TICKxCON_TMREN                       ((uint32_t)0x00000001)
#define TICKxCON_PCLKSEL                     ((uint32_t)0x0000000e)
#define TICKxCON_PDIVSEL                     ((uint32_t)0x00000070)
#define TICKxCON_TIE                         ((uint32_t)0x00000080)
#define TICKxCON_CPTIE                       ((uint32_t)0x00000100)
#define TICKxCON_TMRPND                      ((uint32_t)0x00000200)
#define TICKxCON_CPTPND                      ((uint32_t)0x00000400)
#define TICKxCON_HOLDEN                      ((uint32_t)0x00001000)
#define TICKxCON_TICKEN                      ((uint32_t)0x00002000)
#define TICKxCON_TMRMODE                     ((uint32_t)0x0000c000)

/******************** Bit definition for TICKCPND register *******************/
#define TICKxCPND_TPCLR                      ((uint32_t)0x00000200)
#define TICKxCPND_CPTPCLR                    ((uint32_t)0x00000400)
#define TICKxCPND_PDCNTCLR                   ((uint32_t)0x00001000)

/******************** Bit definition for TICKCNT register *******************/
#define TICKxCPND_TMRCNT                     ((uint32_t)0x0000ffff)

/******************** Bit definition for TICKPR register *******************/
#define TICKxCPND_TMRPR                      ((uint32_t)0x0000ffff)


/*---------------------------------------------------------------------------------*/
/*                                     TMR                                         */
/*---------------------------------------------------------------------------------*/
/******************** Bit definition for TMR[0.1.2.3]CON register ********************/
#define TMRxCON_TMREN                       ((uint32_t)0x00000001)
#define TMRxCON_PCLKSEL                     ((uint32_t)0x0000000e)
#define TMRxCON_PDIVSEL                     ((uint32_t)0x00000070)
#define TMRxCON_TIE                         ((uint32_t)0x00000080)
#define TMRxCON_CPTIE                       ((uint32_t)0x00000100)
#define TMRxCON_TMRPND                      ((uint32_t)0x00000200)
#define TMRxCON_CPTPND                      ((uint32_t)0x00000400)
#define TMRxCON_HOLDEN                      ((uint32_t)0x00001000)
#define TMRxCON_TICKEN                      ((uint32_t)0x00002000)
#define TMRxCON_TMRMODE                     ((uint32_t)0x0000c000)

/******************** Bit definition for TMR[0.1.2.3]CPND register *******************/
#define TMRxCPND_TPCLR                      ((uint32_t)0x00000200)
#define TMRxCPND_CPTPCLR                    ((uint32_t)0x00000400)
#define TMRxCPND_PDCNTCLR                   ((uint32_t)0x00001000)

/******************** Bit definition for TMRCNT[0.1.2.3] register *******************/
#define TMRxCNT                             ((uint32_t)0xffffffff)

/******************** Bit definition for TMRPR[0.1.2.3] register *******************/
#define TMRxPR                              ((uint32_t)0xffffffff)

/******************** Bit definition for TMRCPT[2.3] register *******************/
#define TMRxCPT                             ((uint32_t)0xffffffff)

/*---------------------------------------------------------------------------------*/
/*                                     UART                                        */
/*---------------------------------------------------------------------------------*/
/*********************** Bit definition for UART0CON register **********************/
#define UARTxCON_UTEN                       ((uint32_t)0x00000001)
#define UARTxCON_BIT9EN                     ((uint32_t)0x00000002)
#define UARTxCON_RXIE                       ((uint32_t)0x00000004)
#define UARTxCON_TXIE                       ((uint32_t)0x00000008)
#define UARTxCON_SB2EN                      ((uint32_t)0x00000010)
#define UARTxCON_FIXBAUD                    ((uint32_t)0x00000020)
#define UARTxCON_ONELINE                    ((uint32_t)0x00000040)
#define UARTxCON_RXEN                       ((uint32_t)0x00000080)
#define UARTxCON_TXPND                      ((uint32_t)0x00000100)
#define UARTxCON_RXPND                      ((uint32_t)0x00000200)
#define UARTxCON_KEYMAT                     ((uint32_t)0x00000400)
#define UARTxCON_RXBCNT                     ((uint32_t)0x00007800)
#define UARTxCON_RX4BUFERROR                ((uint32_t)0x00008000)
#define UARTxCON_RSTEN                      ((uint32_t)0x000f0000)
#define UARTxCON_KEYEN                      ((uint32_t)0x00f00000)
#define UARTxCON_KEYIE                      ((uint32_t)0x0f000000)
#define UARTxCON_TXPREDONE                  ((uint32_t)0x10000000)
#define UARTxCON_TXBUFFFULL                 ((uint32_t)0x20000000)
#define UARTxCON_TXPREDONE_IE               ((uint32_t)0x40000000)
#define UARTxCON_TSKEN                      ((uint32_t)0x80000000)

/*********************** Bit definition for UART0CPND register *********************/
#define UARTxCPND_ALL                       ((uint32_t)0x00008b00)
#define UARTxCPND_CTXPND                    ((uint32_t)0x00000100)
#define UARTxCPND_CRXPND                    ((uint32_t)0x00000200)
#define UARTxCPND_CKEYMAT                   ((uint32_t)0x00000400)
#define UARTxCPND_CPREDONE                  ((uint32_t)0x00000800)
#define UARTxCPND_RX4BUF_ERR_CLR            ((uint32_t)0x00008000)
#define UARTxCPND_CBDCFM                    ((uint32_t)0x00040000)

/*---------------------------------------------------------------------------------*/
/*                                    HUART                                        */
/*---------------------------------------------------------------------------------*/
/*********************** Bit definition for HSUT0CON register **********************/
#define HSUT0CON_URXEN                      ((uint32_t)0x00000001)
#define HSUT0CON_UTXEN                      ((uint32_t)0x00000002)
#define HSUT0CON_RXIE                       ((uint32_t)0x00000004)
#define HSUT0CON_TXIE                       ((uint32_t)0x00000008)
#define HSUT0CON_RXTRSMODE                  ((uint32_t)0x00000010)
#define HSUT0CON_RXBITSEL                   ((uint32_t)0x00000020)
#define HSUT0CON_RXLPBUFEN                  ((uint32_t)0x00000040)
#define HSUT0CON_TXTRSMODE                  ((uint32_t)0x00000080)
#define HSUT0CON_TXBITSEL                   ((uint32_t)0x00000100)
#define HSUT0CON_SPBITSEL                   ((uint32_t)0x00000200)
#define HSUT0CON_HSUTTMREN                  ((uint32_t)0x00000400)
#define HSUT0CON_RXHF_PND                   ((uint32_t)0x00000800)
#define HSUT0CON_RXPND                      ((uint32_t)0x00001000)
#define HSUT0CON_TXPND                      ((uint32_t)0x00002000)
#define HSUT0CON_RXFAIL                     ((uint32_t)0x00004000)
#define HSUT0CON_TMROV                      ((uint32_t)0x00008000)
#define HSUT0CON_RXOVE_PND                  ((uint32_t)0x00010000)
#define HSUT0CON_RXHF_IE                    ((uint32_t)0x00020000)
#define HSUT0CON_ONELINE                    ((uint32_t)0x00040000)

/*********************** Bit definition for HSUT0CPND register *********************/
#define HSUT0CPND_CUTRX                     ((uint32_t)0x00000001)
#define HSUT0CPND_CUTTX                     ((uint32_t)0x00000002)
#define HSUT0CPND_CCTSPND                   ((uint32_t)0x00000400)
#define HSUT0CPND_CRXHFPND                  ((uint32_t)0x00000800)
#define HSUT0CPND_CRXPND                    ((uint32_t)0x00001000)
#define HSUT0CPND_CTXPND                    ((uint32_t)0x00002000)
#define HSUT0CPND_CRXFAIL                   ((uint32_t)0x00004000)
#define HSUT0CPND_CTMROV                    ((uint32_t)0x00008000)
#define HSUT0CPND_CRXOVEPND                 ((uint32_t)0x00010000)
#define HSUT0CPND_CRXLBBUF                  ((uint32_t)0x00020000)

/*********************** Bit definition for HSUT0FCCON register ********************/
#define HSUT0FCCON_UCTS_EN                   ((uint32_t)0x00000001)
#define HSUT0FCCON_URTS_EN                   ((uint32_t)0x00000002)
#define HSUT0FCCON_CTSIE                     ((uint32_t)0x00000004)
#define HSUT0FCCON_RTS_MODE                  ((uint32_t)0x00000008)
#define HSUT0FCCON_CTSPND                    ((uint32_t)0x00000010)
#define HSUT0FCCON_CTSS                      ((uint32_t)0x00000020)
#define HSUT0FCCON_RTSS                      ((uint32_t)0x00000040)
#define HSUT0FCCON_RTS_SW                    ((uint32_t)0x00000080)

/*---------------------------------------------------------------------------------*/
/*                                     RTC                                         */
/*---------------------------------------------------------------------------------*/
/************************ Bit definition for RTCCON register ***********************/
#define RTCCON_VRTCVSEL                     ((uint32_t)0x00000001)

#define RTCCON_BAUDSEL                      ((uint32_t)0x00000006)

#define RTCCON_RTC1SIE                      ((uint32_t)0x00000008)
#define RTCCON_ALMIE                        ((uint32_t)0x00000010)
#define RTCCON_WKUPRSTEN                    ((uint32_t)0x00000020)
#define RTCCON_VUSBRSTEN                    ((uint32_t)0x00000040)
#define RTCCON_RTC_WKSLPEN                  ((uint32_t)0x00000080)
#define RTCCON_ALM_WKEN                     ((uint32_t)0x00000100)
#define RTCCON_VUSBON_WKSLPEN               ((uint32_t)0x00000200)
#define RTCCON_INBOX_WKSLPEN                ((uint32_t)0x00000400)
#define RTCCON_VUSBONIE                     ((uint32_t)0x00000800)
#define RTCCON_INBOXIE                      ((uint32_t)0x00001000)
#define RTCCON_RTC_ON                       ((uint32_t)0x00010000)
#define RTCCON_ALMPND                       ((uint32_t)0x00020000)
#define RTCCON_RTCWKSLPPND                  ((uint32_t)0x00040000)
#define RTCCON_RTCWKP                       ((uint32_t)0x00080000)
#define RTCCON_VUSBONLINE                   ((uint32_t)0x00100000)
#define RTCCON_VUSBOFF                      ((uint32_t)0x00200000)
#define RTCCON_INBOX                        ((uint32_t)0x00400000)

/************************ Bit definition for RTCCPND register **********************/
#define RTCCPND_TKTSOE                      ((uint32_t)0x00000003)

#define RTCCPND_CALMPND                     ((uint32_t)0x00020000)
#define RTCCPND_CWKSLPPND                   ((uint32_t)0x00040000)

#define RTCCPND_VBCNTDIS                    ((uint32_t)0x30000000)

#define RTCCPND_VBCNTKST                    ((uint32_t)0x40000000)
#define RTCCPND_VBCNTCLR                    ((uint32_t)0x80000000)

/************************ Bit definition for RTCCON11 register *********************/
#define RTCCON11_RTCWKSLPEN                 ((uint32_t)0x00000400)

/*---------------------------------------------------------------------------------*/
/*                                     SPI                                         */
/*---------------------------------------------------------------------------------*/
/************************ Bit definition for SPIxCON register **********************/
#define SPIxCON_SPIEN                       ((uint32_t)0x00000001)
#define SPIxCON_SPISM                       ((uint32_t)0x00000002)
#define SPIxCON_BUSMODE                     ((uint32_t)0x0000000c)
#define SPIxCON_SPISEL                      ((uint32_t)0x00000010)
#define SPIxCON_CLKIDS                      ((uint32_t)0x00000020)
#define SPIxCON_SMPS                        ((uint32_t)0x00000040)
#define SPIxCON_SPIIE                       ((uint32_t)0x00000080)
#define SPIxCON_SPILF_EN                    ((uint32_t)0x00000100)
#define SPIxCON_SPIMBEN                     ((uint32_t)0x00000200)
#define SPIxCON_SPIOSS                      ((uint32_t)0x00000400)
#define SPIxCON_HOLDENRX                    ((uint32_t)0x00000800)
#define SPIxCON_HOLDENTX                    ((uint32_t)0x00001000)
#define SPIxCON_HOLDENSW                    ((uint32_t)0x00002000)
#define SPIxCON_SPIPND                      ((uint32_t)0x00010000)

/*---------------------------------------------------------------------------------*/
/*                                     WDT                                         */
/*---------------------------------------------------------------------------------*/
/************************ Bit definition for WDTCON register ***********************/
#define WDTCON_WDTCLR                       ((uint32_t)0x0000000f)
#define WDTCON_WDTEN                        ((uint32_t)0x000000f0)
#define WDTCON_RSTEN                        ((uint32_t)0x00000f00)
#define WDTCON_WDTIE                        ((uint32_t)0x0000f000)
#define WDTCON_WDTCSEL                      ((uint32_t)0x000f0000)
#define WDTCON_TMRSEL                       ((uint32_t)0x00700000)
#define WDTCON_TMRSEL_WR                    ((uint32_t)0x0f000000)
#define WDTCON_WDTPND                       ((uint32_t)0x80000000)

/*---------------------------------------------------------------------------------*/
/*                                    SARADC                                       */
/*---------------------------------------------------------------------------------*/
/************************ Bit definition for SADCCON register **********************/
#define SADCCON_CH0PUEN                     ((uint32_t)0x00000001)
#define SADCCON_CH1PUEN                     ((uint32_t)0x00000002)
#define SADCCON_CH2PUEN                     ((uint32_t)0x00000004)
#define SADCCON_CH3PUEN                     ((uint32_t)0x00000008)
#define SADCCON_CH4PUEN                     ((uint32_t)0x00000010)
#define SADCCON_CH5PUEN                     ((uint32_t)0x00000020)
#define SADCCON_CH6PUEN                     ((uint32_t)0x00000040)
#define SADCCON_CH7PUEN                     ((uint32_t)0x00000080)
#define SADCCON_CH8PUEN                     ((uint32_t)0x00000100)
#define SADCCON_CH9PUEN                     ((uint32_t)0x00000200)
#define SADCCON_CH10PUEN                    ((uint32_t)0x00000400)
#define SADCCON_CH11PUEN                    ((uint32_t)0x00000800)
#define SADCCON_CH12PUEN                    ((uint32_t)0x00001000)
#define SADCCON_CH13PUEN                    ((uint32_t)0x00002000)
#define SADCCON_CH14PUEN                    ((uint32_t)0x00004000)
#define SADCCON_CH15PUEN                    ((uint32_t)0x00008000)
#define SADCCON_ADCEN                       ((uint32_t)0x00010000)
#define SADCCON_ADCIE                       ((uint32_t)0x00020000)
#define SADCCON_ADCANGIOEN                  ((uint32_t)0x00040000)
#define SADCCON_ADCAEN                      ((uint32_t)0x00080000)
#define SADCCON_ADCMODE                     ((uint32_t)0x00100000)
#define SADCCON_MICIE                       ((uint32_t)0x00200000)

/************************ Bit definition for SADCCON register **********************/
#define SADCCH_ADCPND                       ((uint32_t)0x00010000)

/************************ Bit definition for SADCMCON register **********************/
#define SADCMCON_MICTPR                     ((uint32_t)0x000007ff)
#define SADCMCON_MIC_IE                     ((uint32_t)0x00001000)
#define SADCMCON_MIC_HDONE_IE               ((uint32_t)0x00002000)
#define SADCMCON_MIC_ADONE_IE               ((uint32_t)0x00004000)
#define SADCMCON_CHLENGTH                   ((uint32_t)0x01ff0000)
#define SADCMCON_MIC_DMAEN                  ((uint32_t)0x40000000)
#define SADCMCON_MIC_EN                     ((uint32_t)0x80000000)

/************************ Bit definition for SADCDMA register **********************/
#define SADCDMA_MIC_DMACNT                  ((uint32_t)0x00000fff)
#define SADCDMA_MIC_SMP_PND                 ((uint32_t)0x00001000)
#define SADCDMA_MIC_HDONE_PEND              ((uint32_t)0x00002000)
#define SADCDMA_MIC_ADONE_PEND              ((uint32_t)0x00004000)
#define SADCDMA_MIC_OFFSET                  ((uint32_t)0x03ff0000)

/************************ Bit definition for SADCDMABADR register **********************/
#define SADCDMABADR_DMA_BADR                ((uint32_t)0x001ffffe)

/************************ Bit definition for SADCCPND register **********************/
#define SADCCPND_MIC_SMP_PND                ((uint32_t)0x00001000)
#define SADCCPND_MIC_HDONE_PEND             ((uint32_t)0x00002000)
#define SADCCPND_MIC_ADONE_PEND             ((uint32_t)0x00004000)
#define SADCCPND_ADC_PEND                   ((uint32_t)0x00010000)

/*---------------------------------------------------------------------------------*/
/*                                   KEYSCAN                                       */
/*---------------------------------------------------------------------------------*/
/********************* Bit definition for KEYSCAN_CON0 register ********************/
#define KEYSCAN_CON0_KEYVALID_PND           ((uint32_t)0x80000000)
#define KEYSCAN_CON0_KEYINVALID_PND         ((uint32_t)0x40000000)

#define KEYSCAN_CON0_KEYPORT_EN             ((uint32_t)0x0000ff00)
#define KEYSCAN_CON0_KEYPORT_EN_0           ((uint32_t)0x00000100)

#define KEYSCAN_CON0_KEYSCAN_SWRSTN         ((uint32_t)0x00000080)
#define KEYSCAN_CON0_KEYINVALID_INT_EN      ((uint32_t)0x00000020)
#define KEYSCAN_CON0_KEYVALID_INT_EN        ((uint32_t)0x00000010)
#define KEYSCAN_CON0_KEYVALID_WKUP_EN       ((uint32_t)0x00000008)
#define KEYSCAN_CON0_KEYSCAN_LP             ((uint32_t)0x00000004)
#define KEYSCAN_CON0_KEYSCAN_MODE           ((uint32_t)0x00000002)
#define KEYSCAN_CON0_KEYSCAN_EN             ((uint32_t)0x00000001)

/********************* Bit definition for KEYSCAN_CON1 register ********************/
#define KEYSCAN_CON1_KEYDIV                 ((uint32_t)0x0f000000)
#define KEYSCAN_CON1_KEYDIV_0               ((uint32_t)0x01000000)

#define KEYSCAN_CON1_KEYPORT_STAB_TIME      ((uint32_t)0x00ff0000)
#define KEYSCAN_CON1_KEYPORT_STAB_TIME_0    ((uint32_t)0x00010000)

#define KEYSCAN_CON1_KEY_DEBO_TIMES         ((uint32_t)0x0000ff00)
#define KEYSCAN_CON1_KEY_DEBO_TIMES_0       ((uint32_t)0x00000100)

#define KEYSCAN_CON1_KEY_WAIT_TIMES         ((uint32_t)0x000000ff)
#define KEYSCAN_CON1_KEY_WAIT_TIMES_0       ((uint32_t)0x00000001)

/********************* Bit definition for KEYSCAN_CLR register *********************/
#define KEYSCAN_CLR_KEYVALID_PND_CLR        ((uint32_t)0x80000000)
#define KEYSCAN_CLR_KEYINVALID_PND_CLR      ((uint32_t)0x40000000)

/********************* Bit definition for KEYSCAN_INFO0 register *******************/
#define KEYSCAN_INFO0_KD7_KD0               ((uint32_t)0xff000000)
#define KEYSCAN_INFO0_KD7_KD0_0             ((uint32_t)0x01000000)

#define KEYSCAN_INFO0_KC7_KC0               ((uint32_t)0x00ff0000)
#define KEYSCAN_INFO0_KC7_KC0_0             ((uint32_t)0x00010000)

#define KEYSCAN_INFO0_KB7_KB0               ((uint32_t)0x0000ff00)
#define KEYSCAN_INFO0_KB7_KB0_0             ((uint32_t)0x00000100)

#define KEYSCAN_INFO0_KA7_KA0               ((uint32_t)0x000000ff)
#define KEYSCAN_INFO0_KA7_KA0_0             ((uint32_t)0x00000001)

/********************* Bit definition for KEYSCAN_INFO1 register *******************/
#define KEYSCAN_INFO1_KH7_KH0               ((uint32_t)0xff000000)
#define KEYSCAN_INFO1_KH7_KH0_0             ((uint32_t)0x01000000)

#define KEYSCAN_INFO1_KG7_KG0               ((uint32_t)0x00ff0000)
#define KEYSCAN_INFO1_KG7_KG0_0             ((uint32_t)0x00010000)

#define KEYSCAN_INFO1_KF7_KF0               ((uint32_t)0x0000ff00)
#define KEYSCAN_INFO1_KF7_KF0_0             ((uint32_t)0x00000100)

#define KEYSCAN_INFO1_KE7_KE0               ((uint32_t)0x000000ff)
#define KEYSCAN_INFO1_KE7_KE0_0             ((uint32_t)0x00000001)

/********************* Bit definition for KEYSCAN_INFO2 register *******************/
#define KEYSCAN_INFO2_KI7_KI0               ((uint32_t)0x0000ff00)
#define KEYSCAN_INFO2_KI7_KI0_0             ((uint32_t)0x00000100)

#define KEYSCAN_INFO2_KJ7_KJ0               ((uint32_t)0x000000ff)
#define KEYSCAN_INFO2_KJ7_KJ0_0             ((uint32_t)0x00000001)


/*---------------------------------------------------------------------------------*/
/*                                    LEDC                                         */
/*---------------------------------------------------------------------------------*/
/*********************** Bit definition for LEDCCON register ***********************/
#define LEDC_CON_DMA_INT_EN                 ((uint32_t)0x04000000)
#define LEDC_CON_OUT_INV                    ((uint32_t)0x02000000)
#define LEDC_CON_RST_INT_EN                 ((uint32_t)0x01000000)

#define LEDC_CON_BAUD                       ((uint32_t)0x00ff0000)

#define LEDC_CON_DELAY                      ((uint32_t)0x0000ff00)

#define LEDC_CON_IN_FORMAT                  ((uint32_t)0x00000080)
#define LEDC_CON_INT_EN                     ((uint32_t)0x00000040)
#define LEDC_CON_IDLE_LEVEL                 ((uint32_t)0x00000020)
#define LEDC_CON_VLD_INV                    ((uint32_t)0x00000010)

#define LEDC_CON_BYTE_INV                   ((uint32_t)0x0000000c)
#define LEDC_CON_BYTE_INV_0                 ((uint32_t)0x00000004)
#define LEDC_CON_BYTE_INV_1                 ((uint32_t)0x00000008)

#define LEDC_CON_LEDC_KICK                  ((uint32_t)0x00000002)
#define LEDC_CON_EN                         ((uint32_t)0x00000001)

/*********************** Bit definition for LEDCPEND register **********************/
#define LEDC_PEND_DMA_PND                   ((uint32_t)0x00000004)
#define LEDC_PEND_RST_PND                   ((uint32_t)0x00000002)
#define LEDC_PEND_LEDC_PND                  ((uint32_t)0x00000001)


/*---------------------------------------------------------------------------------*/
/*                                    TICK                                         */
/*---------------------------------------------------------------------------------*/
/*********************** Bit definition for TICK0CON register **********************/
#define TICK_CON_TPND                       ((uint32_t)0x00000200)
#define TICK_CON_TIE                        ((uint32_t)0x00000080)
#define TICK_CON_INCSRC                     ((uint32_t)0x00000040)

#define TICK_CON_INCSEL                     ((uint32_t)0x0000000c)
#define TICK_CON_INCSEL_0                   ((uint32_t)0x00000004)
#define TICK_CON_INCSEL_1                   ((uint32_t)0x00000008)

#define TICK_CON_EN                         ((uint32_t)0x00000001)

/*********************** Bit definition for TICK0CPND register *********************/
#define TICK_CPND_TPCLR                     ((uint32_t)0x00000200)

/*---------------------------------------------------------------------------------*/
/*                                     PWM                                         */
/*---------------------------------------------------------------------------------*/
/******************** Bit definition for TMRPCON register ********************/
#define TMRPCON_TMREN                       ((uint32_t)0x00000001)
#define TMRPCON_PCLKSEL                     ((uint32_t)0x0000000e)
#define TMRPCON_PDIVSEL                     ((uint32_t)0x00000070)
#define TMRPCON_TIE                         ((uint32_t)0x00000080)
#define TMRPCON_G2EN                        ((uint32_t)0x00000100)
#define TMRPCON_TG2IE                       ((uint32_t)0x00000200)
#define TMRPCON_TMRPND                      ((uint32_t)0x00000400)
#define TMRPCON_TMRG2PND                    ((uint32_t)0x00000800)
#define TMRPCON_HOLDEN                      ((uint32_t)0x00001000)
#define TMRPCON_TICKEN                      ((uint32_t)0x00002000)
#define TMRPCON_TICKG2EN                    ((uint32_t)0x00004000)
#define TMRPCON_PWM_NUM                     ((uint32_t)0x05550000)
#define TMRPCON_PWM_INV                     ((uint32_t)0x0aaa0000)
#define TMRPCON_PWMG2EN                     ((uint32_t)0x10000000)

/******************** Bit definition for TMRPCPND register *******************/
#define TMRPCPND_TPCLR                      ((uint32_t)0x00000400)
#define TMRPCPND_TG2PCLR                    ((uint32_t)0x00000800)
#define TMRPCPND_PDCNTCLR                   ((uint32_t)0x00001000)

/******************** Bit definition for TMRPDUTY[0.1.2.3.4.5] register *******************/
#define TMRPDUTY                           ((uint32_t)0x0000ffff)

/******************** Bit definition for PWMDZCON  PWM[0.1] register *******************/
#define PWMDZCON_DZEN                       ((uint32_t)0x00000001)
#define PWMDZCON_DZMODE                     ((uint32_t)0x00000002)
#define PWMDZCON_DZLEN                      ((uint32_t)0x0003fffc)
#define PWMDZCON_DZLEN_0                    ((uint32_t)0x00000004)

/*---------------------------------------------------------------------------------*/
/*                                    IR TX                                        */
/*---------------------------------------------------------------------------------*/
/******************** Bit definition for IR TX CON register ************************/
#define IRTXCON_EN                         ((uint32_t)0x00000001)
#define IRTXCON_KST                        ((uint32_t)0x00000002)
#define IRTXCON_INV                        ((uint32_t)0x00000004)
#define IRTXCON_IE                         ((uint32_t)0x00000008)
#define IRTXCON_CARRIER_EN                 ((uint32_t)0x00000010)
#define IRTXCON_CW_LENGTH                  ((uint32_t)0x0000ff00)
#define IRTXCON_CW_DUTY                    ((uint32_t)0x00ff0000)

/******************** Bit definition for IR TX PEND register *************************/
#define IRTXPEND_PND                       ((uint32_t)0x00000001)

/******************** Bit definition for IR READ DMA CON register ********************/
#define IRTX_RDMACON_EN                    ((uint32_t)0x00000001)
#define IRTX_RDMACON_APND_IE               ((uint32_t)0x00000002)
#define IRTX_RDMACON_HPND_IE               ((uint32_t)0x00000004)

/******************** Bit definition for IR DMA INPUT SIZE register ********************/
#define IRTX_DMAISIZE_SIZE                 ((uint32_t)0x0000ffff)
#define IRTX_DMAISIZE_CNT                  ((uint32_t)0xffff0000)

/******************** Bit definition for IR READ DMA PEND register ********************/
#define IRTX_RDMA_APND                     ((uint32_t)0x00000001)
#define IRTX_RDMA_HPND                     ((uint32_t)0x00000002)

/*---------------------------------------------------------------------------------*/
/*                                    IR RX                                        */
/*---------------------------------------------------------------------------------*/
/******************** Bit definition for IR RX CON register ************************/
#define IRRXCON_EN                         ((uint32_t)0x00000001)
#define IRRXCON_IE                         ((uint32_t)0x00000002)
#define IRRXCON_DATA_SEL                   ((uint32_t)0x00000004)
#define IRRXCON_WK_EN                      ((uint32_t)0x00000010)
#define IRRXCON_RX_PND                     ((uint32_t)0x00010000)
#define IRRXCON_KEY_RELS                   ((uint32_t)0x00020000)

/******************** Bit definition for IR RX CLEAR PEND register ********************/
#define IRRXCPEND_RX_PND                   ((uint32_t)0x00010000)
#define IRRXCPEND_RELS_PND                 ((uint32_t)0x00020000)

/******************** Bit definition for IR RX FILTER CON register ****************/
#define IRFLTCON_EN                         ((uint32_t)0x00000001)
#define IRFLTCON_SRCS                       ((uint32_t)0x00000002)
#define IRFLTCON_LEN                        ((uint32_t)0x0000ff00)

/**
 * @brief GPIO Register Structure
 */
typedef struct {
    volatile u32 io_set;
    volatile u32 io_clr;
    volatile u32 data;
    volatile u32 dir;
    volatile u32 de;
    volatile u32 fen;
    volatile u32 fdir;
    volatile u32 drv;
    volatile u32 pupd[6];
} gpio_typedef;

/**
 * @brief Function and IO Mapping Register Structure
 */
typedef struct {
    volatile u32 func_output_map[8];
    volatile u32 func_input_map[4];
} func_map_typedef;

/**
 * @brief Timer Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 cpnd;
    volatile u32 cnt;
    volatile u32 period;
    volatile u32 capture_val;
} tmr_typedef;

/**
 * @brief Uart Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 cpnd;
    volatile u32 baud;
    volatile u32 data;
} uart_typedef;

/**
 * @brief High Speed UART Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 cpnd;
    volatile u32 baud;
    volatile u32 data;
    volatile u32 tx_cnt;
    volatile u32 tx_adr;
    volatile u32 rx_cnt;
    const    u32 reserve0;
    const    u32 reserve1;
    volatile u32 rx_adr;
    volatile u32 fifo_cnt;
    volatile u32 fifo;
    volatile u32 fifo_adr;
    volatile u32 tmr_cnt;
    volatile u32 flow_ctrl;
} hsuart_typedef;

/**
 * @brief SPI Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 buf;
    volatile u32 baud;
    volatile u32 cpnd;
    volatile u32 dma_cnt;
    volatile u32 dma_adr;
} spi_typedef;

/**
 * @brief WDT Register Structure
 */
typedef struct {
    volatile u32 con;
} wdt_typedef;

/**
 * @brief SARADC Register Structure
 */
typedef struct {
    volatile u32 dat[16];
    volatile u32 con;
    volatile u32 ch;
    volatile u32 cst;
    volatile u32 baud;
    volatile u32 dma;
    volatile u32 badr;
    volatile u32 mcon;
    volatile u32 cpnd;
} sadc_typedef;

/**
 * @brief KEYSCAN Register Structure
 */
typedef struct {
    volatile u32 con0;
    volatile u32 con1;
    volatile u32 clr;
    volatile u32 info0;
    volatile u32 info1;
    volatile u32 info2;
} keyscan_typedef;

/**
 * @brief IRRX Register Structure
 */
typedef struct {
    // IR RX Con Register
    volatile u32 con;
    // IR RX Data Register
    volatile u32 dat;
    // IR RX Clear Pending Register
    volatile u32 cpnd;
    // IR RX Error Config Register0
    volatile u32 err0;
    // IR RX Error Config Register1
    volatile u32 err1;
    // IR RX Period Config Register0
    volatile u32 period0;
    // IR RX Period Config Register1
    volatile u32 period1;
    // IR RX Filter Con Config Register
    volatile u32 fltcon;
} irrx_typedef;

/**
 * @brief IRTX Register Structure
 */
typedef struct {
    // IR TX Con Register
    volatile u32 con;
    // RESERVE
    const    u32 reserve0;
    // RESERVE
    const    u32 reserve1;
    // IR TX Pending Register
    volatile u32 pend;
    // IR TX DMA Con Register
    volatile u32 dmacon;
    // IR TX DMA Input Address Register
    volatile u32 dmaiadr;
    // IR TX DMA Input Size Register
    volatile u32 dmaisize;
    // RESERVE
    const    u32 reserve2;
    // RESERVE
    const    u32 reserve3;
    // IR TX DMA Pending Register
    volatile u32 dmapend;
} irtx_typedef;

/**
 * @brief LEDC Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 fd;
    volatile u32 lp;
    volatile u32 tix;
    volatile u32 rstx;
    volatile u32 addr;
    volatile u32 cnt;
    volatile u32 pend;
} ledc_typedef;

/**
 * @brief TICK0 Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 cpnd;
    volatile u32 cnt;
    volatile u32 pr;
} tick_typedef;


/**
 * @brief TIMER PWM Register Structure
 */
typedef struct {
    volatile u32 con;
    volatile u32 cpnd;
    volatile u32 cnt;
    volatile u32 period;
    volatile u32 duty0;
    volatile u32 duty1;
    volatile u32 duty2;
    volatile u32 duty3;
    volatile u32 duty4;
    volatile u32 duty5;
    volatile u32 g2cnt;
    volatile u32 g2period;
    volatile u32 dzcon;
} tmrp_typedef;


#endif // _DRIVER_COM_H
