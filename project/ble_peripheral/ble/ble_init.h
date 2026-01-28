#ifndef __BLE_INIT_H
#define __BLE_INIT_H

#include "ble_service.h"
#include "ble_alarm.h"
#include "ble_profile.h"
#include "ble_adv.h"


typedef struct _ble_cb_t {
    ble_con_handle_t con_handle;
} ble_cb_t;

extern ble_cb_t ble_cb;


void bsp_ble_init(void);
void ble_set_work_mode(BLE_WORK_MODE mode);
BLE_WORK_MODE ble_get_work_mode(void);

#endif
