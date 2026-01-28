#ifndef __BLE_ALARM_H
#define __BLE_ALARM_H

#define ALARM_NUMBER        0//1

extern uint32_t alarm_handle[ALARM_NUMBER];

void ble_alarm_init(void);
void ble_alarm_enter_sleep_proc(void);
void ble_alarm_exit_sleep_proc(void);

#endif
