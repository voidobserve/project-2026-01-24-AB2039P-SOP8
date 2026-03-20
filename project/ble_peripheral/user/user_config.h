#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#include "include.h"

#define USER_DEBUG_ENABLE 0

#define ARRAY_SIEZE(array) (sizeof(array) / sizeof(array[0]))
#define USER_DATA_VALID_VAL 0xC5 // 用户数据有效时，对应的数值

// 需要掉电保存的数据
typedef struct __attribute__((packed))
{
    u8 valid;         // 校验，用于验证是不是第一次上电，之前写入的数据是否有效
    u8 is_ble_adv_en; // 从机的广播功能是否使能
} user_data_t;
extern volatile user_data_t user_data;



void user_init(void);
void user_main(void);

#endif
