#ifndef _API_INTERRUPT_H
#define _API_INTERRUPT_H

#define GLOBAL_INT_DISABLE()    uint32_t cpu_ie = PICCON&BIT(0); PICCONCLR = BIT(0);asm volatile("":::"memory")
#define GLOBAL_INT_RESTORE()    asm volatile("":::"memory");PICCON |= cpu_ie

/**
 * @brief MATE Interrupt Number Definition.
 */
typedef enum {
    IRQn_SOFT                        = 2,
    IRQn_TMR0,
    IRQn_TMR1,
    IRQn_TMR2,
    IRQn_IR_QDEC_LEDC,
    IRQn_USB_CONTROL,
    IRQn_KEY_SCAN                   = 9,
    IRQn_UART0                      = 14,
    IRQn_HSUART,
    IRQn_TMR3,
    IRQn_TMR_PWM,
    IRQn_SPIx                       = 20,
    IRQn_URAT0_KEY_MATCH,
    IRQn_FREQUENCY_DET              = 23,
    IRQn_PORT                       = 26,
    IRQn_SARADC                     = 28,
    IRQn_RTC_SECOND_ALARM_LVD_WDT,
    IRQn_TICK0 = 31,
} IRQ_TYPEDEF;

typedef void (*isr_t)(void);

/**
 * @brief system interrupt init
 * @param interrupt number,define in IRQ_TYPEDEF
 * @param interrupt priority, 1 is high priority, 0 is low priority
 * @param interrupt callback function
 */
bool sys_irq_init(int vector, int pr, isr_t isr);

#endif
