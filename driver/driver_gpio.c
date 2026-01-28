/*
 * @File name    : driver_gpio.c
 * @Author       : Bluetrum IOT Team
 * @Date         : 2024-08-17
 * @Description  : This file provides functions to manage the most functionalities
 *                 of the GPIO peripheral.
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */
#include "driver_gpio.h"

#define GPIO_SUPPORT_STRONG_CURRENT_64MA(drv, gpiox, pin_bit_offset)           ((GPIOPB4_DRV_I_64MA & drv) && (GPIOB_REG == gpiox) && (GPIO_PIN_4 == pin_bit_offset))
#define GPIO_SUPPORT_HIGH_VOLTAGE_PB0(drv, gpiox, pin_bit_offset)              ((GPIOPB0_DRV_U_VBAT & drv) && (GPIOB_REG == gpiox) && (GPIO_PIN_0 == pin_bit_offset))
#define GPIO_SUPPORT_HIGH_VOLTAGE_PB1(drv, gpiox, pin_bit_offset)              ((GPIOPB1_DRV_U_VBAT & drv) && (GPIOB_REG == gpiox) && (GPIO_PIN_1 == pin_bit_offset))


/**
  * @brief  Initializes the gpiox peripheral according to the specified
  *         parameters in the gpio_init_struct.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @param  gpio_init_struct: pointer to a gpio_init_typedef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void gpio_init(gpio_typedef* gpiox, gpio_init_typedef* gpio_init_struct)
{
    u32 reg;
    uint32_t pin_idx = 0, pin_bit_offset = 0x00;
    uint8_t i = 0x00;

    /*--- Configure the port pins ---*/
    for (pin_idx = 0; pin_idx <= 11; pin_idx++) {
        pin_bit_offset = ((uint32_t)0x01) << pin_idx;
        if (gpio_init_struct->gpio_pin & pin_bit_offset) {
            /*--- Input or Output Configuration ---*/
            reg = gpiox->dir;
            reg &= ~pin_bit_offset;
            reg |= ((uint32_t)(gpio_init_struct->gpio_dir) << pin_idx);
            gpiox->dir = reg;

            /*--- Digital or Analog Configuration ---*/
            reg = gpiox->de;
            reg &= ~pin_bit_offset;
            reg |= ((uint32_t)(gpio_init_struct->gpio_mode) << pin_idx);
            gpiox->de = reg;

            /*--- Function Mapping Enable Configuration ---*/
            reg = gpiox->fen;
            reg &= ~pin_bit_offset;
            reg |= ((uint32_t)(gpio_init_struct->gpio_fen) << pin_idx);
            gpiox->fen = reg;

            /*--- GPIO Direction Select Configguratiopn ---*/
            reg = gpiox->fdir;
            reg &= ~pin_bit_offset;
            reg |= ((uint32_t)(gpio_init_struct->gpio_fdir) << pin_idx);
            gpiox->fdir = reg;

            /*--- Pull Up or Pull Down Configuration and clear driving cfg ---*/
            if (gpio_init_struct->gpio_dir == GPIO_DIR_INPUT) {
                gpiox->drv &= ~pin_bit_offset;
                for (i = 0; i < 6; i++) {
                    reg = gpiox->pupd[i];
                    reg &= ~pin_bit_offset;
                    if ((i + 1) == gpio_init_struct->gpio_pupd) {
                        reg |= pin_bit_offset;
                    }
                    gpiox->pupd[i] = reg;
                }
            /*--- Output driving Configuration and clear pupu cfg ---*/
            } else if (gpio_init_struct->gpio_dir == GPIO_DIR_OUTPUT) {
                for (i = 0; i < 6; i++) {
                    gpiox->pupd[i] &= ~pin_bit_offset;
                }
                if (gpio_init_struct->gpio_mode == GPIO_MODE_DIGITAL) {
                    reg = gpiox->drv;
                    if ((gpiox == GPIOB_REG) && (pin_bit_offset == GPIO_PIN_4)) {
                        reg &= ~BIT(14);
                    }

                    if (GPIO_SUPPORT_STRONG_CURRENT_64MA(gpio_init_struct->gpio_drv, gpiox, pin_bit_offset)) {
                        reg |= pin_bit_offset;
                        reg |= BIT(14);
                    } else if(gpio_init_struct->gpio_drv & GPIO_DRV_I_24MA) {
                        reg |=  pin_bit_offset;
                    } else {
                        reg &= ~pin_bit_offset;
                    }

                    if (GPIO_SUPPORT_HIGH_VOLTAGE_PB0(gpio_init_struct->gpio_drv, gpiox, pin_bit_offset)) {
                        reg |= BIT(12);
                    }
                    if (GPIO_SUPPORT_HIGH_VOLTAGE_PB1(gpio_init_struct->gpio_drv, gpiox, pin_bit_offset)) {
                        reg |= BIT(13);
                    }
                    gpiox->drv = reg;
                }
            }
        }
    }
}

/**
 * @brief  De-initialize the specified GPIO peripheral.
 * @param  gpiox: where x can be (B) to select the GPIO peripheral.
 * @param  gpio_pin: specifies the port bits to be written. This parameter
 *         can be any combination of GPIO_PIN_x where x can be (0..11).
 * @retval None
 */
uint32_t gpio_deinit(gpio_typedef *gpiox, uint16_t gpio_pin)
{
    u32 reg_original_sta;

    reg_original_sta = gpiox->de;
    gpiox->de &= ~gpio_pin;

    return reg_original_sta;
}

/**
 * @brief  De-initialize the specified GPIO peripheral.
 * @param  gpiox: where x can be (B) to select the GPIO peripheral.
 * @param  gpio_pin: specifies the port bits to be written. This parameter
 *         can be any combination of GPIO_PIN_x where x can be (0..11).
 * @param  dir: GPIO_DIR_TYPEDEF.
 * @retval None
 */
AT(.com_periph.gpio.dir)
void gpio_set_dir(gpio_typedef* gpiox, uint16_t gpio_pin, GPIO_DIR_TYPEDEF dir)
{
    if (dir) {
        gpiox->dir |= gpio_pin;
    } else {
        gpiox->dir &= ~gpio_pin;
    }
}


/**
  * @brief  Sets the selected data port bits.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @param  gpio_pin: specifies the port bits to be written. This parameter
  *         can be any combination of GPIO_PIN_x where x can be (0..11).
  * @retval None
  */
AT(.com_periph.gpio.set)
void gpio_set_bits(gpio_typedef* gpiox, uint16_t gpio_pin)
{
    gpiox->io_set = gpio_pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @param  gpio_pin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_PIN_x where x can be (0..11).
  * @retval None
  */
AT(.com_periph.gpio.reset)
void gpio_reset_bits(gpio_typedef* gpiox, uint16_t gpio_pin)
{
    gpiox->io_clr = gpio_pin;
}

/**
  * @brief  Writes the specified GPIO output data port.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @param  port_val: specifies the port bits to be written. This parameter
  *         can be any combination of GPIO_PIN_x where x can be (0..11).
  * @retval None
  */
AT(.com_periph.gpio.write)
void gpio_write_data(gpio_typedef *gpiox, uint16_t port_val)
{
    gpiox->data = port_val;
}

/**
  * @brief  Toggles the selected output data port bits.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @param  gpio_pin: specifies the port bits to be written. This parameter
  *         can be any combination of GPIO_PIN_x where x can be (0..11).
  * @retval None
  */
AT(.com_periph.gpio.toggle)
void gpio_toggle_bits(gpio_typedef *gpiox, uint16_t gpio_pin)
{
    gpiox->data ^= gpio_pin;
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
AT(.com_periph.gpio.read_data)
uint16_t gpio_read_data(gpio_typedef* gpiox)
{
    return ((uint16_t)(gpiox->data));
}

/**
  * @brief  Reads the specified input port pin.
  * @param  gpiox: where x can be (B) to select the GPIO peripheral.
  * @param  gpio_pin: specifies the port bit to read.
  *         This parameter can be gpio_pin where x can be (0..11).
  * @retval The input port pin value.
  */
AT(.com_periph.gpio.read_bit)
uint8_t gpio_read_bit(gpio_typedef* gpiox, uint16_t gpio_pin)
{
    uint8_t bit_status;

    if ((gpiox->data & gpio_pin) != BIT_RESET) {
        bit_status = (uint8_t)SET;
    } else {
        bit_status = (uint8_t)RESET;
    }

    return bit_status;
}

/**
 * @brief  Configure GPIO function mapping.
 * @param  gpiox: where x can be (B) to select the GPIO peripheral.
 * @param  gpio_pin: specifies the port bit to read.
 *         This parameter can be gpio_pin where x can be (0..11).
 * @param  func_idx: Peripheral index that need to config mapping. The value of this param
 *         see enumeration "GPIO_CROSSBAR_PERIPHERAL_DEF" in the file "driver_gpio.h".
 * @retval None
 */
void gpio_func_mapping_config(gpio_typedef* gpiox, uint16_t gpio_pin, GPIO_CROSSBAR_PERIPHERAL_DEF func_idx)
{
    u8 i;
    u8 pin_idx;
    uint8_t register_idx, register_offset;

    u8 gpio_crossbar_idx_PB0 = 1;

    /*--- Calculate the pin_dix for function mapping ---*/
    for (i = 0; i <= 11; i++) {
        if ((1 << i) == gpio_pin) {
            break;
        }
    }

    pin_idx = gpio_crossbar_idx_PB0 + i;

    /*--- Check parameter validity ---*/
    if (func_idx >= GPIO_CROSSBAR_PERIPHERAL_MAX_IDX) {
        return;
    }

    /*--- function mapping config ---*/
    if (func_idx > GPIO_CROSSBAR_PERIPHERAL_INPUT_BASE) {
        register_idx = (func_idx - GPIO_CROSSBAR_PERIPHERAL_INPUT_BASE - 1) / 4;
        register_offset = (func_idx - GPIO_CROSSBAR_PERIPHERAL_INPUT_BASE - 1) % 4 * 8;

        /* Do nothing if the current peripheral is already mapped to the corresponding IO */
        if (((FUNCMAP->func_input_map[register_idx] >> register_offset) & 0x1f) == pin_idx) {
            return;
        }

        FUNCMAP->func_input_map[register_idx] |= (uint32_t)(0xff << register_offset);
        FUNCMAP->func_input_map[register_idx] |= (uint32_t)(pin_idx << register_offset);
    } else if (func_idx < GPIO_CROSSBAR_PERIPHERAL_INPUT_BASE) {
        register_idx = (pin_idx - 1) / 4 + 4;
        register_offset = (pin_idx - 1) % 4 * 8;

        /* Do nothing if the current peripheral is already mapped to the corresponding IO */
        if (((FUNCMAP->func_output_map[register_idx] >> register_offset) & 0x1f) == func_idx) {
            return;
        }

        FUNCMAP->func_output_map[register_idx] |= (uint32_t)(0xff << register_offset);
        FUNCMAP->func_output_map[register_idx] |= (uint32_t)(func_idx << register_offset);
    }
}

/**
 * @brief  Clear GPIO function mapping config.
 * @param  gpiox: where x can be (B) to select the GPIO peripheral.
 * @param  gpio_pin: specifies the port bit to read.
 *         This parameter can be gpio_pin where x can be (0..11).
 * @retval None
 */
void gpio_func_mapping_clear(gpio_typedef* gpiox, uint16_t gpio_pin)
{
    uint8_t register_idx, register_offset;
    uint8_t i, j;
    u8 pin_idx;

    u8 gpio_crossbar_idx_PB0 = 1;

    /* Calculate the pin_dix for function mapping */
    for (i = 0; i <= 11; i++) {
        if ((1 << i) == gpio_pin) {
            break;
        }
    }

    pin_idx = gpio_crossbar_idx_PB0 + i;

    /* Clear output mapping */
    register_idx = (pin_idx - 1) / 4 + 4;
    register_offset = (pin_idx - 1) % 4 * 8;
    FUNCMAP->func_output_map[register_idx] |= (uint32_t)(0xff << register_offset);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 32; j += 8)
        if (((FUNCMAP->func_input_map[i] >> j) & 0x1f) == pin_idx) {
            FUNCMAP->func_input_map[i] |= (uint32_t)(0xff << j);
        }
    }
}

/**
 * @brief  WK0 IO level detect config.
 * @param  pull_up_en: Whether WK0 internal pull up enable.
 * @param  pull_down_en: Whether WK0 internal pull down enable.
 * @param  input_en: Whether WK0 input enable.
 * @retval None
 */
void wko_io_config(FUNCTIONAL_STATE pull_up_en, FUNCTIONAL_STATE pull_down_en, FUNCTIONAL_STATE input_en)
{
    if (pull_up_en) {
        RTCCON1 |= (uint32_t)(1 << 4);
    } else {
        RTCCON1 &= ~(uint32_t)(1 << 4);
    }

    if (pull_down_en) {
        RTCCON1 |= (uint32_t)(1 << 1);
    } else {
        RTCCON1 &= ~(uint32_t)(1 << 1);
    }

    if (input_en) {
        RTCCON1 |= (uint32_t)(1 << 0);
    } else {
        RTCCON1 &= ~(uint32_t)(1 << 0);
    }
}

/**
 * @brief  Read WK0 level.
 * @retval The state of interrupt_type (SET or RESET).
 */
AT(.com_periph.wk0.read_bit)
FLAG_STATE wko_io_read_bit(void)
{
    if (RTCCON & (1 << 19)) {
        return SET;
    } else {
        return RESET;
    }
}

void wk0_edge_capture_config(GPIO_EDGE_SEL edge)
{
    clk_gate0_cmd(CLK_GATE0_LP, CLK_EN);

    WKPINMAP &= ~(BIT(0) | BIT(1));

    if(edge == GPIO_EDGE_FALLING){
        wko_io_config(1, 0, 1);
        WKUPEDG |= BIT(0);
    }else{
        wko_io_config(0, 1, 1);
        WKUPEDG &= ~BIT(0);
    }

    WKUPCON |= BIT(0);

    WKUPCPND = 0xff << 16;                  //clear wakeup pending
}

void gpio_edge_capture_config(gpio_edge_cap_typedef* config)
{
    clk_gate0_cmd(CLK_GATE0_LP, CLK_EN);

    gpio_init_typedef gpio_config;
    uint32_t gpio_pin = config->gpio_pin;

    gpio_config.gpio_pin = config->gpio_pin;
    gpio_config.gpio_dir = GPIO_DIR_INPUT;
    gpio_config.gpio_fen = GPIO_FEN_GPIO;
    gpio_config.gpio_fdir = GPIO_FDIR_SELF;
    gpio_config.gpio_mode = GPIO_MODE_DIGITAL;
    gpio_config.gpio_pupd = config->gpio_pupd;

    gpio_init(config->gpiox, &gpio_config);

    if(config->edge == GPIO_EDGE_RISING){
        WKUPCON = (WKUPCON & ~(0x3 << 22)) | (config->filter << 22);
        PORTINTEDG &= ~gpio_pin;
        PORTINTEN |= gpio_pin;
        WKPINMAP |= (BIT(14) | BIT(15));
        WKUPEDG &= ~BIT(7);
        WKUPCON |= BIT(7);
    }else{
        WKUPCON = (WKUPCON & ~(0x3 << 20)) | (config->filter << 20);
        PORTINTEDG |= gpio_pin;
        PORTINTEN |= gpio_pin;
        WKPINMAP |= (BIT(12) | BIT(13));
        WKUPEDG |= BIT(6);
        WKUPCON |= BIT(6);
    }

    WKUPCPND = 0xff << 16;
}

void gpio_edge_capture_config_custom(gpio_edge_cap_typedef* config)
{
    clk_gate0_cmd(CLK_GATE0_LP, CLK_EN);

    gpio_init_typedef gpio_config;
    uint32_t gpio_pin = config->gpio_pin;

    gpio_config.gpio_pin = config->gpio_pin;
    gpio_config.gpio_dir = GPIO_DIR_INPUT;
    gpio_config.gpio_fen = GPIO_FEN_GPIO;
    gpio_config.gpio_fdir = GPIO_FDIR_SELF;
    gpio_config.gpio_mode = GPIO_MODE_DIGITAL;
    gpio_config.gpio_pupd = config->gpio_pupd;

    gpio_init(config->gpiox, &gpio_config);

    if(config->edge == GPIO_EDGE_RISING){
        WKUPCON = (WKUPCON & ~(0x3 << 22)) | (config->filter << 22);
        PORTINTEDG &= ~gpio_pin;
        PORTINTEN |= gpio_pin;
        WKPINMAP = (WKPINMAP & ~(0x3 << (config->wkpinmap * 2))) | config->wkpinmap_int;
        WKUPEDG &= ~BIT(config->wkpinmap);
        WKUPCON |= BIT(config->wkpinmap);
    }else{
        WKUPCON = (WKUPCON & ~(0x3 << 20)) | (config->filter << 20);
        PORTINTEDG |= gpio_pin;
        PORTINTEN |= gpio_pin;
        WKPINMAP = (WKPINMAP & ~(0x3 << (config->wkpinmap * 2))) | config->wkpinmap_int;
        WKUPEDG |= BIT(config->wkpinmap);
        WKUPCON |= BIT(config->wkpinmap);
    }

    WKUPCPND = 0xff << 16;
}

void gpio_set_reset_pin(uint16_t reset_pin)
{
    clk_gate0_cmd(CLK_GATE0_LP, CLK_EN);

    WKUPCON = (WKUPCON & ~(0x1f << 24)) | (reset_pin << 24) | BIT(29);

    RTCCON1 &= ~BIT(10);

    RTCCON12 &= ~BIT(5);
}

uint32_t gpio_get_edge_pin(void)
{
    return PORTINTEN;
}

AT(.com_periph.gpio.rise.src)
uint32_t gpio_get_rise_pending_src(void)
{
    return WKRSRC;   //gpio pin index
}

AT(.com_periph.gpio.fall.src)
uint32_t gpio_get_fall_pending_src(void)
{
    return ~WKFSRC;  //gpio pin index
}

AT(.com_periph.gpio.pending_clr)
void gpio_edge_pending_clear(void)
{
    WKUPCPND = 0xff << 16;
}

AT(.com_periph.gpio.pending_is)
bool gpio_edge_pending(void)
{
   return ((WKUPEDG>>16) & 0xff) ? true : false;
}

void gpio_edge_pic_config(isr_t isr, int pr, FUNCTIONAL_STATE state)
{
    if (state == ENABLE) {
        sys_irq_init(IRQn_PORT, pr, isr);

        WKUPCPND = 0xff << 16;
        WKUPCON |= BIT(16);
    } else {
        PICEN &= ~BIT(IRQn_PORT);
        WKUPCON &= ~BIT(16);
    }
}

