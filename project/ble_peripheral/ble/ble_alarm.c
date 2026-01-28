#include "include.h"


#if ALARM_NUMBER

uint8_t alarm_pool[BLE_ALARM_TIMER_LEN * ALARM_NUMBER] AT(.btmem.alarm);
uint32_t alarm_handle[ALARM_NUMBER];


AT(.com_text.timer)
static void ble_alarm_timer_5ms_callback(ble_timer_handle_t handle)
{
    usr_tmr5ms_callback();
}

#if SYS_PWROFF_TIME
AT(.com_text.timer)
static void ble_alarm_timer_poweroff_callback(ble_timer_handle_t handle)
{
    sys_cb.pwroff_delay = 0;
    func_cb.sta = FUNC_PWROFF;
}
#endif

void ble_alarm_enter_sleep_proc(void)
{
    ble_alarm_timer_release(alarm_handle[0]);   //stop 5ms timer

#if SYS_PWROFF_TIME
    ble_alarm_timer_acquire(&alarm_handle[0], sys_cb.pwroff_delay * 100, 0, ble_alarm_timer_poweroff_callback);
    ble_alarm_timer_start(alarm_handle[0]);
#endif
}

void ble_alarm_exit_sleep_proc(void)
{
#if SYS_PWROFF_TIME
    ble_alarm_timer_release(alarm_handle[0]);   //stop poweroff timer
#endif
    ble_alarm_timer_acquire(&alarm_handle[0], 5, 1, ble_alarm_timer_5ms_callback);
    ble_alarm_timer_start(alarm_handle[0]);
}

void ble_alarm_init(void)
{
    ble_alarm_timer_init(alarm_pool, sizeof(alarm_pool));
    ble_alarm_timer_acquire(&alarm_handle[0], 5, 1, ble_alarm_timer_5ms_callback);
    ble_alarm_timer_start(alarm_handle[0]);
}


#endif


