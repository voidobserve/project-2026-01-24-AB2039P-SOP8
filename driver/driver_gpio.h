/*
 * @File name    : driver_gpio.h
 * @Author       : Bluetrum IOT Team
 * @Date         : 2023-02-13
 * @Description  : This file contains all the functions prototypes for the GPIO library.
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#ifndef _DRIVER_GPIO_H
#define _DRIVER_GPIO_H

#include "driver_com.h"

/**
 * @brief GPIO_Pins_Definition
 */
#define GPIO_PIN_ALL                ((uint16_t)0x0fff)      /* All PIN bits definition */
#define GPIO_PIN_0                  ((uint16_t)0x0001)      /* PIN 0 bit definition */
#define GPIO_PIN_1                  ((uint16_t)0x0002)      /* PIN 1 bit definition */
#define GPIO_PIN_2                  ((uint16_t)0x0004)      /* PIN 2 bit definition */
#define GPIO_PIN_3                  ((uint16_t)0x0008)      /* PIN 3 bit definition */
#define GPIO_PIN_4                  ((uint16_t)0x0010)      /* PIN 4 bit definition */
#define GPIO_PIN_5                  ((uint16_t)0x0020)      /* PIN 5 bit definition */
#define GPIO_PIN_6                  ((uint16_t)0x0040)      /* PIN 6 bit definition */
#define GPIO_PIN_7                  ((uint16_t)0x0080)      /* PIN 7 bit definition */
#define GPIO_PIN_8                  ((uint16_t)0x0100)      /* PIN 8 bit definition */
#define GPIO_PIN_9                  ((uint16_t)0x0200)      /* PIN 9 bit definition */
#define GPIO_PIN_10                 ((uint16_t)0x0400)      /* PIN 10 bit definition */
#define GPIO_PIN_11                 ((uint16_t)0x0800)      /* PIN 11 bit definition */


/**
 * @brief GPIO Function Mapping Crossbar Peripheral Definition
 */
typedef enum {
    GPIO_CROSSBAR_OUT_PWM0 = 5,
    GPIO_CROSSBAR_OUT_PWM1,
    GPIO_CROSSBAR_OUT_PWM2,
    GPIO_CROSSBAR_OUT_PWM3,
    GPIO_CROSSBAR_OUT_PWM4,
    GPIO_CROSSBAR_OUT_PWM5,
    GPIO_CROSSBAR_OUT_LEDCDAT,
    GPIO_CROSSBAR_OUT_IRTX,
    GPIO_CROSSBAR_OUT_UARTTX,
    GPIO_CROSSBAR_OUT_HURTX,
    GPIO_CROSSBAR_OUT_HURRTS,
    GPIO_CROSSBAR_OUT_SPI1D0,
    GPIO_CROSSBAR_OUT_SPI1D1,
    GPIO_CROSSBAR_OUT_SPI1CLK,
    GPIO_CROSSBAR_OUT_CLKOUT,

    GPIO_CROSSBAR_PERIPHERAL_INPUT_BASE,
    GPIO_CROSSBAR_IN_UARTRX,
    GPIO_CROSSBAR_IN_NULL,
    GPIO_CROSSBAR_IN_SPI1CLK,
    GPIO_CROSSBAR_IN_SPI1DI0,
    GPIO_CROSSBAR_IN_SPI1DI1,
    GPIO_CROSSBAR_IN_HURRX,
    GPIO_CROSSBAR_IN_HURCTS,
    GPIO_CROSSBAR_IN_TMRINC0,
    GPIO_CROSSBAR_IN_TMRINC1,
    GPIO_CROSSBAR_IN_TMR2CAP,
    GPIO_CROSSBAR_IN_TMR3CAP,
    GPIO_CROSSBAR_IN_IRRX,
    GPIO_CROSSBAR_IN_SPI0CLK,
    GPIO_CROSSBAR_IN_SPI0DI0,
    GPIO_CROSSBAR_IN_SPI0DI1,
    GPIO_CROSSBAR_PERIPHERAL_MAX_IDX,
} GPIO_CROSSBAR_PERIPHERAL_DEF;

/**
 * @brief Bits detinition for GPIO
 */
typedef enum {
    BIT_RESET           = 0,
    BIT_SET,
} BIT_ACTION;

/**
 * @brief GPIO direction enumeration
 */
typedef enum {
    GPIO_DIR_OUTPUT     = 0x00,
    GPIO_DIR_INPUT      = 0x01,
} GPIO_DIR_TYPEDEF;

/**
 * @brief GPIO input pull resistance enumeration
 */
typedef enum {
    GPIO_PUPD_NULL      = 0x00,
    GPIO_PUPD_PU10K     = 0x01,
    GPIO_PUPD_PD10K     = 0x02,
    GPIO_PUPD_PU200K    = 0x03,
    GPIO_PUPD_PD200K    = 0x04,
    GPIO_PUPD_PU300     = 0x05,
    GPIO_PUPD_PD300     = 0x06,
} GPIO_PUPD_TYPEDEF;

/**
 * @brief GPIO port type enumeration
 */
typedef enum {
    GPIO_MODE_ANALOG    = 0x00,
    GPIO_MODE_DIGITAL   = 0x01,
} GPIO_MODE_TYPEDEF;

/**
 * @brief GPIO function mapping enable enumeration
 */
typedef enum {
    GPIO_FEN_GPIO       = 0x00,
    GPIO_FEN_PER        = 0x01,
} GPIO_FEN_TYPEDEF;

/**
 * @brief GPIO function mapping direction select register
 */
typedef enum {
    GPIO_FDIR_SELF      = 0x00,
    GPIO_FDIR_MAP       = 0x01,
} GPIO_FDIR_TYPEDEF;

/**
 * @brief GPIO output current enumeration, specially PB4 can output 64mA.
 */
typedef enum {
    GPIO_DRV_I_6MA        = 0x01,
    GPIO_DRV_I_24MA       = 0x02,
    GPIOPB4_DRV_I_64MA    = 0x04,
    GPIOPB0_DRV_U_VBAT    = 0x08,   //voltage
    GPIOPB1_DRV_U_VBAT    = 0x10,
} GPIO_DRV_TYPEDEF;

typedef enum {
    GPIO_EDGE_RISING    = 0x00,
    GPIO_EDGE_FALLING   = 0x01,
} GPIO_EDGE_SEL;

/**
 * @brief GPIO weak pin map enumeration, specially: one wkpinmap can have only one wkpinmap_int.
 */

typedef enum {
    GPIO_WK0MAP    = 0x01,
    GPIO_WK1MAP    = 0x02,
    GPIO_WK2MAP    = 0x02,
    GPIO_WK3MAP    = 0x03,
    GPIO_WK4MAP    = 0x04,
    GPIO_WK5MAP    = 0x05,
    GPIO_WK6MAP    = 0x06,
    GPIO_WK7MAP    = 0x07,
} GPIO_WKPINMAP_TYPEDEF;

typedef enum {
    GPIO_WK0MAP_INT0_G1_WKO         = (0 << 0),
    GPIO_WK0MAP_INT0_G2_PB2         = (1 << 0),
    GPIO_WK0MAP_INT0_G3_RESERVED    = (2 << 0),
    GPIO_WK0MAP_INT0_G4_RESERVED    = (3 << 0),

    GPIO_WK1MAP_INT1_G1_PB11        = (0 << 2),
    GPIO_WK1MAP_INT1_G2_PB5         = (1 << 2),
    GPIO_WK1MAP_INT1_G3_RESERVED    = (2 << 2),
    GPIO_WK1MAP_INT1_G4_RESERVED    = (3 << 2),

    GPIO_WK2MAP_INT2_G1_PB3         = (0 << 4),
    GPIO_WK2MAP_INT2_G2_PB4         = (1 << 4),
    GPIO_WK2MAP_INT2_G3_PB10        = (2 << 4),
    GPIO_WK2MAP_INT2_G4_RESERVED    = (3 << 4),

    GPIO_WK3MAP_INT3_G1_PB0         = (0 << 6),
    GPIO_WK3MAP_INT3_G2_PB1         = (1 << 6),
    GPIO_WK3MAP_INT3_G3_PB2         = (2 << 6),
    GPIO_WK3MAP_INT3_G4_RESERVED    = (3 << 6),

    GPIO_WK4MAP_INT4_G1_PB5         = (0 << 8),
    GPIO_WK4MAP_INT4_G2_PB6         = (1 << 8),
    GPIO_WK4MAP_INT4_G3_PB7         = (2 << 8),
    GPIO_WK4MAP_INT4_G4_RESERVED    = (3 << 8),

    GPIO_WK5MAP_INT5_G1_PB8         = (0 << 10),
    GPIO_WK5MAP_INT5_G2_PB9         = (1 << 10),
    GPIO_WK5MAP_INT5_G3_RESERVED    = (2 << 10),
    GPIO_WK5MAP_INT5_G4_RESERVED    = (3 << 10),

    GPIO_WK6MAP_INT6_G1_PB4         = (0 << 12),
    GPIO_WK6MAP_INT6_G2_RESERVED    = (1 << 12),
    GPIO_WK6MAP_INT6_G3_RESERVED    = (2 << 12),
    GPIO_WK6MAP_INT6_G4_PALL_FALL   = (3 << 12),

    GPIO_WK7MAP_INT7_G1_PB1         = (0 << 14),
    GPIO_WK7MAP_INT7_G2_RESERVED    = (1 << 14),
    GPIO_WK7MAP_INT7_G3_RESERVED    = (2 << 14),
    GPIO_WK7MAP_INT7_G4_PALL_RISE   = (3 << 14),
} GPIO_WKPINMAP_INT_TYPEDEF;

/**
 * @brief GPIO Init Structure
 */
typedef struct {
    uint32_t              gpio_pin;
    GPIO_DIR_TYPEDEF      gpio_dir;
    GPIO_PUPD_TYPEDEF     gpio_pupd;
    GPIO_MODE_TYPEDEF     gpio_mode;
    GPIO_FEN_TYPEDEF      gpio_fen;
    GPIO_FDIR_TYPEDEF     gpio_fdir;
    GPIO_DRV_TYPEDEF      gpio_drv;
} gpio_init_typedef;

typedef struct {
    GPIO_EDGE_SEL                 edge;
    gpio_typedef*                 gpiox;
    uint16_t                      gpio_pin;
    GPIO_PUPD_TYPEDEF             gpio_pupd;
    uint8_t                       filter;
    GPIO_WKPINMAP_TYPEDEF         wkpinmap;
    GPIO_WKPINMAP_INT_TYPEDEF     wkpinmap_int;
} gpio_edge_cap_typedef;

/************************ Function used to set or R/W GPIO *************************/
void gpio_init(gpio_typedef *gpiox, gpio_init_typedef *gpio_init_struct);
uint32_t gpio_deinit(gpio_typedef *gpiox, uint16_t gpio_pin);
void gpio_set_dir(gpio_typedef* gpiox, uint16_t gpio_pin, GPIO_DIR_TYPEDEF dir);
void gpio_set_bits(gpio_typedef *gpiox, uint16_t gpio_pin);
void gpio_reset_bits(gpio_typedef *gpiox, uint16_t gpio_pin);
void gpio_write_data(gpio_typedef *gpiox, uint16_t port_val);
void gpio_toggle_bits(gpio_typedef *gpiox, uint16_t gpio_pin);
uint16_t gpio_read_data(gpio_typedef *gpiox);
uint8_t gpio_read_bit(gpio_typedef *gpiox, uint16_t gpio_pin);
void gpio_func_mapping_config(gpio_typedef* gpiox, uint16_t gpio_pin, GPIO_CROSSBAR_PERIPHERAL_DEF func_idx);
void gpio_func_mapping_clear(gpio_typedef* gpiox, uint16_t gpio_pin);
void wko_io_config(FUNCTIONAL_STATE pull_up_en, FUNCTIONAL_STATE pull_down_en, FUNCTIONAL_STATE input_en);
FLAG_STATE wko_io_read_bit(void);
void wk0_edge_capture_config(GPIO_EDGE_SEL edge);
void gpio_edge_capture_config(gpio_edge_cap_typedef* config);
void gpio_edge_capture_config_custom(gpio_edge_cap_typedef* config);
bool gpio_edge_pending(void);
void gpio_edge_pending_clear(void);
void gpio_edge_pic_config(isr_t isr, int pr, FUNCTIONAL_STATE state);
uint32_t gpio_get_edge_pin(void);
uint32_t gpio_get_rise_pending_src(void);
uint32_t gpio_get_fall_pending_src(void);
void gpio_set_reset_pin(uint16_t reset_pin);

#endif  // _DRIVER_GPIO_H
