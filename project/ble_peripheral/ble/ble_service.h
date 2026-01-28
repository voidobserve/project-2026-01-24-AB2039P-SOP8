#ifndef __BLE_SERVICE_H
#define __BLE_SERVICE_H

#define CCCD_DFT                    0           //定义client config的默认值,对于有些应用，主机不会进行订阅的情况，可以设置成1


void ble_service_init(void);

#endif
