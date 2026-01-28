/**********************************************************************
*
*   strong_ble.c
*   定义库里面部分WEAK函数的Strong函数，动态关闭库代码
***********************************************************************/
#include "include.h"

#if (!LE_DUT_UART_EN)
STRONG void hci_fcc_init(void){}
STRONG bool bt_uart_isr(void) {return false;}
#endif

#if !LE_SM_EN
STRONG void ble_sm_server_event_do(uint8_t *packet, uint16_t size){}
STRONG void ble_sm_client_event_do(uint8_t *packet, uint16_t size){}
STRONG void sm_send_security_request(uint16_t con_handle){}
STRONG void sm_request_pairing(uint16_t con_handle){}
STRONG void sm_passkey_input(uint16_t con_handle, uint32_t passkey){}
STRONG uint32_t sm_passkey_input_get(void){return 0;}
#endif

STRONG void ble_get_local_bd_addr(u8 *addr)
{
    memcpy(addr, xcfg_cb.le_addr, 6);
}

STRONG const uint8_t *bt_rf_get_param(void)
{
    if(xcfg_cb.bt_rf_param_en) {
        return (const uint8_t *)&xcfg_cb.rf_pa_gain;
    }

    return NULL;
}

AT(.com_sleep.rf.txpwr)
STRONG u8 bt_rf_get_tx_pwr(void)
{
    return xcfg_cb.rf_tx_pwr;
}

STRONG void ble_get_link_info(void *buf, u16 addr, u16 size)
{
    cm_read(buf, BLE_CM_PAGE(addr), size);
}

STRONG void ble_put_link_info(void *buf, u16 addr, u16 size)
{
    cm_write(buf, BLE_CM_PAGE(addr), size);
    cm_sync();
}

STRONG bool ble_mtu_exchange_enabled(void)
{
    return LE_MTU_EXCHANGE_EN;
}

STRONG uint16_t ble_sm_send_security_req_time_get(void)
{
    return LE_SM_SEND_SECURITY_REQ_TIME;
}

STRONG bool ble_sm_always_accept_ltk_req(void)
{
    return LE_SM_ALWAYS_ACCEPT_LTK_REQ_EN;
}

STRONG bool ble_sm_pairing_support(void)
{
    return LE_SM_EN;
}

STRONG bool ble_disconnected_restart_adv(void)
{
    return LE_DISCONN_RESTART_ADV_EN;
}

STRONG bool ble_rx_exit_sleep(void)
{
    return LE_RX_EXIT_SLEEP_EN;
}

AT(.com_text.ble.phy)
STRONG bool ble_phy_2M_enable(void)
{
    return LE_PHY_2M_EN;
}

STRONG bool ble_feature_exchange_enabled(void)
{
    return LE_FEATURE_EXCHANGE_EN;
}

STRONG bool ble_length_request_enabled(void)
{
    return LE_LENGTH_REQ_EN;
}

STRONG bool ble_phy_update_enable(void)
{
    return LE_PHY_UPDATE_EN;
}