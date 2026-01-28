#include "include.h"
#include "driver_com.h"
#include "bsp_saradc_key.h"
#include "bsp_io_key.h"

#if BSP_KEY_EN

static bool power_on_flag AT(.bss.key.flag);


AT(.com_rodata.key)
u16 allow_multiple_key_table[] = {
    KEY_ID_PP | KEY_SHORT_UP,
};

AT(.com_rodata.key)
key_param_t key_param = {
    .key_scan_times = KEY_SCAN_TIMES,
    .key_up_times   = KEY_UP_TIMES,
    .key_long_times = KEY_LONG_TIMES,
    .key_hold_times = KEY_HOLD_TIMES,
};


// mode: 0-事件检测  1-状态检测
AT(.com_text.key.scan)
u16 bsp_key_scan(u8 mode)
{
    u16 key, key_id = KEY_ID_NO;

#if BSP_IOKEY_EN
    key_id = bsp_get_io_key_id();
#endif // BSP_IOKEY_EN

#if BSP_ADKEY_EN
    if (key_id == KEY_ID_NO) {
        key_id = bsp_get_adkey_id();            // 根据ADC采样值返回键值
    }
#endif // BSP_ADKEY_EN

    if (mode) {
        return key_id;
    }

    if (power_on_flag) {
        if (key_id == KEY_ID_PP) {
            key_id = KEY_ID_NO;
        } else {
            power_on_flag = false;
        }
    }

    key = key_status_process(key_id, &key_param);   // 短按、长按、连按处理
    key = key_multi_press_process(key);             // 多击处理

    if(key){
        msg_enqueue(key);
    }

    return key;
}

void bsp_key_init(void)
{
    multiple_key_init(100, allow_multiple_key_table, sizeof(allow_multiple_key_table) / sizeof(u16));

#if BSP_ADKEY_EN
    bsp_adkey_init();
#endif // BSP_ADKEY_EN

#if BSP_IOKEY_EN
    bsp_io_key_init();
#endif // BSP_IOKEY_EN
}

void bsp_key_set_power_on_flag(bool flag)
{
    power_on_flag = flag;
}

#endif // BSP_KEY_EN
