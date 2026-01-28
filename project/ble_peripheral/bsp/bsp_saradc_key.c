#include "include.h"
#include "driver_saradc.h"
#include "bsp_saradc_key.h"
#include "bsp_key.h"

#if BSP_ADKEY_EN

AT(.com_rodata.key)
const key_val_mapping_typedef key_val_mapping_table[6] = {
		{KEY_VALUE_PP,      KEY_ID_PP},
		{KEY_VALUE_KEY1,    KEY_ID_K1},
		{KEY_VALUE_KEY2,    KEY_ID_K2},
		{KEY_VALUE_KEY3,    KEY_ID_K3},
		{KEY_VALUE_KEY4,    KEY_ID_K4},
		{KEY_VALUE_NULL,    KEY_ID_NO},
};


// 初始化ADC按键
void bsp_adkey_init(void)
{
    saradc_add_channel(ADC_CHANNEL_SEL, SARADC_PULLUP_DIS);
    saradc_kick_start();
}

// 读取按键的ADC采样值并根据数值返回键值
AT(.com_text.adkey.get)
u8 bsp_get_adkey_id(void)
{
    u8 num = 0;

    u16 key_adc_val = saradc_get_channel_value(ADC_CHANNEL_SEL);

    while (key_adc_val > key_val_mapping_table[num].adc_val) {
        num++;
    }

    return key_val_mapping_table[num].usage_id;
}

#endif // BSP_ADKEY_EN
