#include "user_config.h"

#define USER_DATE_SAVE_START_ADDR 0x00 // 起始地址

volatile user_data_t user_data = {0};

void user_data_write(void)
{
    bsp_param_write((u8 *)&user_data, (u32)USER_DATE_SAVE_START_ADDR, sizeof(user_data_t));
    bsp_param_sync(); // 同步数据到flash
}

void user_data_read(void)
{
    bsp_param_read((u8 *)&user_data, (u32)USER_DATE_SAVE_START_ADDR, sizeof(user_data_t));
    if (user_data.valid != USER_DATA_VALID_VAL)
    {
        // 初始化存放的数据
        user_data.valid = USER_DATA_VALID_VAL;
        // user_data.is_ble_adv_en = 1; // 默认使能从机的广播
        user_data.is_ble_adv_en = 0; // 默认不打开从机的广播
        user_data_write();           // 将数据写回flash
    }

#if USER_DEBUG_ENABLE

    // 打印从flash中读出的数据：
    printf("user_data.is_ble_adv_en == %u\n", (u16)user_data.is_ble_adv_en);

#endif
}

void user_init(void)
{
    user_data_read();
    
}

void user_main(void)
{
}
