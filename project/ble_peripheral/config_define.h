/*****************************************************************************
 * Module    : Configs
 * File      : config_define.h
 * Function  : 定义用户参数常量
 *****************************************************************************/
#ifndef CONFIG_DEFINE_H
#define CONFIG_DEFINE_H

/*****************************************************************************
 * Module    : FLASH大小定义
 *****************************************************************************/
#define FSIZE_1M                        0x100000
#define FSIZE_2M                        0x200000
#define FSIZE_512K                      0x80000
#define FSIZE_256K                      0x40000
#define FSIZE_128K                      0x20000


/*****************************************************************************
 * Module    : 软关机模式定义
 *****************************************************************************/
#define PWROFF_MODE1                    1
#define PWROFF_MODE2                    2

/*****************************************************************************
 * Module    : Printf IO 定义
 *****************************************************************************/
/* IO INDEX */
#define GPIO_NULL                     0x00
#define GPIO_PB0                      0xB0
#define GPIO_PB1                      0xB1
#define GPIO_PB2                      0xB2
#define GPIO_PB3                      0xB3
#define GPIO_PB4                      0xB4
#define GPIO_PB5                      0xB5
#define GPIO_PB6                      0xB6
#define GPIO_PB7                      0xB7
#define GPIO_PB8                      0xB8
#define GPIO_PB9                      0xB9
/* IO SWAPPER */
#define GPIO_PORT_GET(x)                (GPIOB_REG)
#define GPIO_PIN_GET(x)                 (1 << (x & 0x0F))

#endif //CONFIG_DEFINE_H
