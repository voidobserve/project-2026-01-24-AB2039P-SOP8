#ifndef _API_SYS_H_
#define _API_SYS_H_

#define CACHE_ADDR          0x70000

typedef uint8_t flash_id_t[16];

/**
  * @brief  Sets whether to call the timer2 interrupt callback function
  * @param  tmr5ms_en: set to true, usr_tmr5ms_thread_callback will be called once in 5ms
  * @param  tmr1ms_en: set to true, usr_tmr1ms_isr_callback will be called once in 1ms
  */
void sys_set_tmr_enable(bool tmr5ms_en, bool tmr1ms_en);

/**
  * @brief  system reset init
  * @param  wk pin 10s reset config
  * @return system reset source
    reset source:   BIT(31):PWRUP_RST
                    BIT(24):SW_RST
                    BIT(19):WK Pin 10S_RST
                    BIT(18):WAKEUP_RST
                    BIT(16):WDT_RST
                    BIT(20)|BIT(7):LVD_RST
  */
u32 sys_rst_init(bool wko10s_rst);

/**
  * @brief  dump the system reset source info
  * @param  reason: system reset source, can be get by the return value of the function sys_rst_init
  */
void sys_rst_dump(u32 reason);

/**
  * @brief  The system reset can be triggered by software
  * @param  software reset source [1 ~ 15], it can be define by the user
  */
void sw_reset_kick(u8 source);

/**
  * @brief  Get the software reset source,it must be called as soon as the system is reset
  * @return software reset source
  */
u8 sw_reset_source_get(void);

void xosc_init(void);


/**
  * @brief  Gets a random number between 0 and num
  * @param  number
  */
u16 get_random(u16 num);


/**
  * @brief  Read data from the chip's built-in flash
  * @param  buf
  * @param  flash address to read
  * @param  len
  */
uint os_spiflash_read(void *buf, u32 addr, uint len);

/**
  * @brief  Program data to the chip's built-in flash
  * @param  buf
  * @param  flash address to program to
  * @param  len, Cannot be written across pages, 256 bytes per page
  */
void os_spiflash_program(void *buf, u32 addr, uint len);

/**
  * @brief  Erase the chip's built-in flash
  * @param  flash base addresses that need to be erased, erase 4K bytes at a time
  */
void os_spiflash_erase(u32 addr);

/**
  * @brief  Get the chip's built-in flash id
  * @param  flash id buf
  */
void os_spiflash_id_get(flash_id_t id);

#endif // _API_SYS_H_

