#ifndef __BLE_USER_SERVICE_H
#define __BLE_USER_SERVICE_H

/*
PRIMARY_SERVICE, FFF0
CHARACTERISTIC, FFF1, READ | WRITE | DYNAMIC,
CHARACTERISTIC, FFF2, NOTIFY,
*/

void ble_user_service_init(void);
void ble_user_service_proc(void);
bool ble_user_service_pending(void);
void service_notify_event(u8 *buffer, u16 len);

#endif
