#ifndef __BLE_CLIENT_H
#define __BLE_CLIENT_H

#define MAX_SERVICE_NUM              7
#define MAX_CHARACTERISTIC_NUM       20

typedef struct
{
    gatt_client_service_t  service[MAX_SERVICE_NUM];
    gatt_client_characteristic_t characteristic[MAX_CHARACTERISTIC_NUM];
    uint8_t service_cnt;
    uint8_t characteristic_cnt;
    uint8_t service_index;
    uint8_t characteristic_index;
    uint16_t conn_handle;
} server_info_t;

extern server_info_t server_info;

void ble_client_init(void);
void ble_scan_en_test(void);
void ble_write_test(void);
void ble_read_test(void);
void ble_write_to_server(uint8_t *buff, uint32_t len);

#endif
