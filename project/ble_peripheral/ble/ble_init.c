#include "include.h"
#include "ble_client.h"
#include "ble_init.h"


///////////////////////////////////////////////////////////////////////////
#define TX_POOL_SIZE       128


ble_cb_t ble_cb AT(.ble_buf.var);

BLE_WORK_MODE cfg_bt_work_mode            = MODE_NORMAL;


AT(.ble_cache.att)
uint32_t ble_tx_pool[TX_POOL_SIZE / 4 + 3];

void ble_set_work_mode(BLE_WORK_MODE mode)
{
    cfg_bt_work_mode = mode;
}

BLE_WORK_MODE ble_get_work_mode(void)
{
    return cfg_bt_work_mode;
}

void ble_txpkt_init(void)
{
    txpkt_init(ble_tx_pool, sizeof(ble_tx_pool));
}

void ble_sm_param_init(void)
{
    uint8_t security_req_en = 0;
    uint8_t auth_req = SM_AUTHREQ_BONDING | SM_AUTHREQ_MITM_PROTECTION;
    uint8_t io_capability = IO_CAPABILITY_NO_INPUT_NO_OUTPUT;

    ble_sm_init(security_req_en, io_capability, auth_req);
}

void ble_scan_param_init(void)
{
    scan_param_t scan_param;

    scan_param.scan_type = 1;
    scan_param.scan_interval = 0x100;
    scan_param.scan_window = 0x50;
    ble_set_scan_param(&scan_param);
    ble_scan_en();
}

void ble_central_init(void)
{
    ble_txpkt_init();
#if LE_SM_EN
    ble_sm_param_init();
#endif
    gatt_client_init();
    gap_random_address_set_mode(GAP_PUBLIC_ADDRESS_TYPE);
    //att_server_init(ble_get_profile_data());
    ble_client_init();
    ble_scan_param_init();
}


void ble_periph_init(void)
{
    ble_txpkt_init();
#if LE_SM_EN
    ble_sm_param_init();
#endif
    gap_random_address_set_mode(GAP_PUBLIC_ADDRESS_TYPE);
    att_server_init(ble_get_profile_data());
    ble_service_init();
    ble_adv_param_init();
}

void bsp_ble_init(void)
{
    memset(&ble_cb, 0x00, sizeof(ble_cb));

    btstack_init();

#ifdef CLIENT
    ble_init_callback_register(ble_central_init);
#else
    ble_init_callback_register(ble_periph_init);
#endif

    ble_setup();
    
#if ALARM_NUMBER
    ble_alarm_init();
#endif
}
