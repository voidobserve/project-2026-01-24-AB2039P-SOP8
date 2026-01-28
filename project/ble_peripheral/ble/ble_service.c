#include "include.h"
#include "ble_service.h"
#include "ble_user_service.h"
#include "ble_fota_service.h"



void ble_service_init(void)
{
    printf("ble_service_init\n");

    ble_user_service_init();

#if LE_FOTA_EN
    ble_fota_service_init();
#endif
}

