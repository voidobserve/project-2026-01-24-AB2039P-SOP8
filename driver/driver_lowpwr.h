/*
 * @File name    : driver_lowpwr.h
 * @Author       : Bluetrum IOT Team
 * @Date         : 2023-02-15
 * @Version      : v1.0
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#ifndef _DRIVER_LOWPWR_H
#define _DRIVER_LOWPWR_H

#include "driver_com.h"
#include "driver_gpio.h"

typedef enum {
    WK_EDGE_RISING        = 0x00,
    WK_EDGE_FALLING       = 0x01,
} WK_EDGE_SEL;

typedef enum {
    LP_TYPE_POWOFF          = 0x00,
    LP_TYPE_SLEEP           = 0x01,
} LP_TYPE_SEL;

typedef enum {
    WK_LP_ALARM             = BIT(0),
    WK_LP_RTC_1S            = BIT(1),
    WK_LP_WK0               = BIT(2),
    WK_LP_BT                = BIT(5),
    WK_LP_GPIO              = BIT(7),
    WK_LP_KEYSCAN           = BIT(12),
    WK_LP_SRC_ALL           = 0x1FFF,
} WK_LP_SRC_SEL;

typedef struct {
    LP_TYPE_SEL             lp_type;
    WK_LP_SRC_SEL           source;
    gpio_edge_cap_typedef   gpio_cfg;
} lowpwr_wakeup_typedef;


u32 lowpwr_get_wakeup_source(void);
void lowpwr_wakeup_disable(void);
bool lowpwr_is_wakeup_pending(u32 ignore_src);
void lowpwr_clr_wakeup_pending(void);
void lowpwr_wakeup_config(lowpwr_wakeup_typedef *config);
void lowpwr_wakeup_source_enable(WK_LP_SRC_SEL wk_src);
void lowpwr_wakeup_source_disable(WK_LP_SRC_SEL wk_src);
void lowpwr_wk0_wakeup_config(lowpwr_wakeup_typedef *config);
void lowpwr_gpio_wakeup_config(lowpwr_wakeup_typedef *config);
void lowpwr_gpio_wakeup_config_custom(lowpwr_wakeup_typedef *config);
void lowpwr_sleep_proc(void);

/**
  * @brief  only rtc digital, vddio is disable, only wk0 can wakeup system
  */
void lowpwr_pwroff_mode1_do(void);

/**
  * @brief  rtc digital,low power and vddio is enable, wk0, keyscan, gpio can wakeup system
  */
void lowpwr_pwroff_mode2_do(void);


#endif
