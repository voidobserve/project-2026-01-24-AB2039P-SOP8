#ifndef _API_BTSTACK_H
#define _API_BTSTACK_H

#include "btstack_define.h"

//control
void btstack_init(void);

int ble_setup(void);

void btstack_deinit(void);

//sleep
bool ble_is_sleep(void);

uint32_t ble_sleep_proc(void);

void ble_enter_sleep(void);

void ble_exit_sleep(void);

uint32_t txpkt_init(uint32_t *mem_pool, uint16_t total);

uint32_t txpkt_get_available_len(void);

void txpkt_free_for_handle(uint16_t con_handle);

/**
  * @brief  Triggers ble to start notify data, Can be used with ble_notify_for_handle_kick function
  * @param  txpkt
  * @param  con_handle
  */
void txpkt_server_send_tick(uint16_t con_handle);

/**
  * @brief  Triggers ble to start write data, Can be used with ble_write_cmd_for_character_kick function(Todo)
  * @param  txpkt
  * @param  con_handle
  */
void txpkt_client_send_tick(uint16_t con_handle);


/**
  * @brief  ble enter single tone mode
  * @param  rf_mode: FCC_TX_TONE
  * @param  tx_power: [0,7]
  * @param  tx_freq: [0,39],freq = 2402 + tx_freq * 2
  * @param  rx_freq: [0,39],freq = 2402 + rx_freq * 2, not used in single tone mode
  * @param  phy_type: 0:1M  1:2M, not used in single tone mode
  */
void ble_single_tone_mode_enter(fcc_cfg_t *cfg);

/**
 * @brief ble advertisement ctrl
 * @param none
 */
void ble_adv_dis(void);

void ble_adv_en(void);

bool ble_adv_is_en(void);

/**
  * @brief  set up ble advertisement interval
  * @param  interval: 0x20 - 0x4000(uint:0.625ms)
  * @return return true if ok, invalid parameters will return false
  */
bool ble_set_adv_interval(uint16_t interval);

/**
  * @brief  get ble advertisement interval
  * @param  interval: 0x20 - 0x4000(uint:0.625ms)
  * @return return true if ok, invalid parameters will return false
  */
bool ble_get_adv_interval(uint16_t *interval);

/**
 * @brief set advertisement data
 * @param advertising_data (max 31 octets)
 * @param advertising_data_length
 * @return return true if ok, invalid parameters will return false
 */
bool ble_set_adv_data(const uint8_t *adv_buf, uint32_t size);

/**
 * @brief set scan response Data
 * @param advertising_data (max 31 octets)
 * @param advertising_data_length
 * @return return true if ok, invalid parameters will return false
 */
bool ble_set_scan_rsp_data(const uint8_t *scan_rsp_buf, uint32_t size);

/**
 * @brief initialize advertisement parameter
 * @param advertisement parameter
 * @return return true if ok, invalid parameters will return false
 */
bool ble_set_adv_param(adv_param_t* param);


/**
 * @brief analyse advertisement report, the results will be store in advertisement struct
 * @param report, can be get by BLE_EVT_ADV_REPORT
 * @param adv_struct
 * @return analysis is complete will return true, else will return false
 */
bool ble_adv_report_info_analyse(adv_report_t* report, adv_struct_t* adv_struct);

/**
  * @brief  disconnect ble connection according to connect handle
  * @param  con_handle
  */
void ble_disconnect(uint16_t con_handle);

/**
 * @brief ble master create connect by ble address
 * @param addr_ptr
 * @param addr type : 0-3(0:public, 1:random, 2:public identity 3:random identity)
 * @param interval: 6 - 3200(unit: 1.25ms)
 * @param latency
 * @param timeout (unit: 10ms)
 * @return return LE_CONN_INITIATE_ERR_NO_ERR if ok, other refer to le_conn_initiate_err_code_t;
 */
le_conn_initiate_err_code_t ble_connect_by_addr(uint8_t *addr_ptr, uint8_t addr_type, uint16_t interval, uint16_t conn_latency, uint16_t supervision_timeout);

/**
 * @brief update of the connection parameter for a given LE connection
 * @param con_handle
 * @param interval: 6 - 3200(unit: 1.25ms)
 * @param latency
 * @param timeout (unit: 10ms)
 * @return return true if ok, invalid parameters will return false
 */
bool ble_update_conn_param(uint16_t con_handle, uint16_t interval, uint16_t latency, uint16_t timeout);

/**
 * @brief update of the connection parameter for a given LE connection
 * @param con_handle
 * @param interval_min: 6 - 3200(unit: 1.25ms)
 * @param interval_max: 6 - 3200(unit: 1.25ms) interval_min <= interval_max
 * @param latency
 * @param timeout (unit: 10ms)
 * @return return true if ok, invalid parameters will return false
 */
bool ble_update_conn_param_2(uint16_t con_handle, uint16_t interval_min, uint16_t interval_max, uint16_t latency, uint16_t timeout);

/**
 * @brief update of the connection parameter for a given LE connection through the LL layer
 * @param con_handle
 * @param interval_min: 6 - 3200(unit: 1.25ms)
 * @param interval_max: 6 - 3200(unit: 1.25ms) interval_min <= interval_max
 * @param latency
 * @param timeout (unit: 10ms)
 * @return return true if ok, invalid parameters will return false
 */
bool ble_ll_update_conn_param(uint16_t con_handle, uint16_t interval_min, uint16_t interval_max, uint16_t latency, uint16_t timeout);

/**
 * @brief get of the connection parameter for a given LE connection
 * @param con_handle
 * @param interval: 6 - 3200(unit: 1.25ms)
 * @param latency
 * @param timeout (unit: 10ms)
 * @return return true if ok, invalid parameters will return false
 */
bool ble_get_conn_param(uint16_t con_handle, uint16_t *interval, uint16_t *latency, uint16_t *timeout);

/**
 * @brief Disable latency, only valid for the slave role. Even if connection parameters are updated later, latency is disabled also
 * @param con_handle
 * @return return true if ok, invalid parameters will return false
 */
bool ble_disable_latency(uint16_t con_handle);

/**
 * @brief Enable latency, only valid for the slave role.
 * @param con_handle
 * @return return true if ok, invalid parameters will return false
 */
bool ble_enable_latency(uint16_t con_handle);

/**
  * @brief  notify data according to handle
  * @param  connect handle
  * @param  attribute handle
  * @param  buf to be send
  * @param  len(must be less than att mtu)
  * @return return 0 if ok, other refer to ATT_ERR_CORE
  */
int ble_notify_for_handle(uint16_t con_handle, uint16_t att_handle, uint8_t* buf, uint16_t len);

/**
  * @brief  notify data according to handle
  * @param  connect handle
  * @param  attribute handle
  * @param  buf to be send
  * @param  len(must be less than att mtu)
  * @param  kick_cfg, The value is as follows:
            TXPKT_KICK_ENABLE: the Bluetooth thread is triggered to start sending data,
            TXPKT_KICK_DISABLE: the Bluetooth thread will not be triggered to send data immediately, but the data will be cached
            TXPKT_KICK_AUTO: Automatically managed by the Btstack
            It is suitable for continuous data transmission, and can trigger the Bluetooth thread to send data at the last to reduce the switching of threads
  * @return return 0 if ok, other refer to ATT_ERR_CORE
  */
int ble_notify_for_handle_kick(uint16_t con_handle, uint16_t att_handle, uint8_t* buf, uint16_t len, uint8_t kick_cfg);

/**
  * @brief  indicate data according to handle
  * @param  connect handle
  * @param  attribute handle
  * @param  buf to be send
  * @param  len(must be less than att mtu)
  * @return return 0 if ok, other refer to ATT_ERR_CORE
  */
int ble_indicate_for_handle(uint16_t con_handle, uint16_t att_handle, uint8_t* buf, uint16_t len);


/**
  * @brief  Writes the characteristic value using the characteristic's value handle
  * @param  connect handle
  * @param  character
  * @param  buf to be send
  * @param  len(must be less than att mtu)
  * @return return 0 if ok, other refer to ATT_ERR_CORE
  */
int ble_write_req_for_character(uint16_t con_handle, gatt_client_characteristic_t* character, uint8_t* buf, uint16_t len);

/**
  * @brief  Writes the characteristic value using the characteristic's value handle without an acknowledgment that the write was successfully performed.
  * @param  connect handle
  * @param  character
  * @param  buf to be send
  * @param  len(must be less than att mtu)
  * @return return 0 if ok, other refer to ATT_ERR_CORE
  */
int ble_write_cmd_for_character(uint16_t con_handle, gatt_client_characteristic_t* character, uint8_t* buf, uint16_t len);

/**
 * @brief reads the characteristic value using the characteristic's value handle.
 * @param  con_handle
 * @param  character
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
int ble_read_req_for_character(uint16_t con_handle, gatt_client_characteristic_t* character);

/**
 * @brief reads the characteristic value using the characteristic's value handle.
 * @param  con_handle
 * @param  character
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
int ble_read_req_for_character_report_ref(uint16_t con_handle, gatt_client_characteristic_t* character);

/**
 * @brief reads the long characteristic value using the characteristic's value handle.
 * @param  con_handle
 * @param  character
 * @param  offset
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
int ble_read_blob_for_character(uint16_t con_handle, gatt_client_characteristic_t* character, uint16_t offset);

/**
 * @brief set ble address type
 * @param address type
 */
void gap_random_address_set_mode(gap_random_address_type_t random_address_type);

/**
 * @brief BLE initialize callback function registration,
 * @param callback function, which will be called in bluetooth thread
 */
void ble_init_callback_register(ble_init_callback_t  func);

/**
 * @brief BLE test box initialize callback function registration,
 * @param callback function, which will be called in bluetooth thread
 */
void ble_vs_tbox_init_callback_register(ble_vs_tbox_init_callback_t  func);

/**
 * @brief Register server packet handle
 */
void att_server_register_service_handler(att_service_handler_t * handler);

/**
 * @brief Register client packet handle
 */
void att_client_register_handler(att_client_handler_t * handler);

/**
 * @brief ble sm init
 * @param security_req_en(whether to send an sm request when ble connecting)
 * @param io_capability
 * @param authentication_req_flag
 */
void ble_sm_init(uint8_t security_req_en, uint8_t io_capability, uint8_t authentication_req_flag);

/**
 * @brief Trigger Security Request
 */
void ble_sm_send_security_request(ble_con_handle_t con_handle);

/**
 * @brief setup ATT server
 * @param db attribute database created by profile tool
 */
void att_server_init(uint8_t const * db);

/**
 * @brief Set up GATT client.
 */
void gatt_client_init(void);

/**
 * @brief get att mtu
 * @param con_handle
 * @return mtu if ok, 0 otherwise
 */
uint8_t ble_att_get_mtu(uint16_t con_handle, uint16_t * mtu);

/**
 * @brief ble scan ctrl
 * @param none
 */
void ble_scan_en(void);

void ble_scan_dis(void);

/**
 * @brief  ble get scan status
 * @param  none
 * @return sta : 0-3(refer to le_scanning_state_t)
 */
le_scanning_state_t ble_get_scan_sta(void);

/**
 * @brief ble set scan param
 * @param type    : 0 or 1，0(Passive scan,no scan_rsp)，1(Active scan,adv+scan_rsp)
 * @param interval: 4 - 16384(unit: 0.625ms)
 * @param window  : 4 - 16384(less than or equal to interval unit: 0.625ms)
 * @return return true if ok, invalid parameters will return false
 */
bool ble_set_scan_param(scan_param_t* param);


/**
 * @brief Discovers all primary services. For each found service, BLE_EVT_SERVICE_FIND_RESULT will be generated and passed to the registered callback. BLE_EVT_PROFILE_FIND_DONE, marks the end of discovery.
 * @param  con_handle
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
uint8_t ble_client_discover_primary_services(uint16_t con_handle);

/**
 * @brief Discovers a specific primary service given its UUID. For each found service, BLE_EVT_SERVICE_FIND_RESULT will be generated and passed to the registered callback. BLE_EVT_PROFILE_FIND_DONE, marks the end of discovery.
 * @param con_handle
 * @param uuid16
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
uint8_t ble_client_discover_primary_services_by_uuid16(uint16_t con_handle, uint16_t uuid16);

uint8_t ble_client_discover_primary_services_by_uuid128(uint16_t con_handle, const uint8_t * uuid128);


/**
 * @brief Get field service from event BLE_EVT_SERVICE_FIND_RESULT
 * @param event packet
 * @param Pointer to storage for service
 */
void ble_service_query_result_get_service(const uint8_t * event, gatt_client_service_t * service);

/**
 * @brief Discovers all characteristics within the specified service. For each found characteristic, an le_characteristics_event_t with type set to BLE_EVT_CHARACTERISTIC_FIND_RESULT will be generated and passed to the registered callback. The gatt_complete_event_t with type set to BLE_EVT_PROFILE_FIND_DONE, marks the end of discovery.
 * @param  callback
 * @param  con_handle
 * @param  service
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
uint8_t ble_client_discover_characteristics_for_service(uint16_t con_handle, gatt_client_service_t * service);

/**
 * @brief Get field characteristic from event BLE_EVT_CHARACTERISTIC_FIND_RESULT
 * @param event packet
 * @param Pointer to storage for characteristic
 */
void ble_characteristic_query_result_get_characteristic(const uint8_t * event, gatt_client_characteristic_t * characteristic);

/**
 * @brief Discover all characteristics within the specified service, and return those that match the given UUID. For each found characteristic, BLE_EVT_CHARACTERISTIC_FIND_RESULT will be generated and passed to the registered callback. BLE_EVT_PROFILE_FIND_DONE, marks the end of discovery.
 * @param  con_handle
 * @param  service
 * @param  uuid
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
uint8_t ble_client_discover_characteristics_for_service_by_uuid16(uint16_t con_handle, gatt_client_service_t * service, uint16_t uuid16);

uint8_t ble_client_discover_characteristics_for_service_by_uuid128(uint16_t con_handle, gatt_client_service_t * service, const uint8_t * uuid128);


/**
 * @brief Writes the client characteristic configuration of the specified characteristic.
 * @param  con_handle
 * @param  characteristic
 * @param  configuration : GATT_CCC_NOTIFICATION, GATT_CCC_INDICATION
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
uint8_t ble_client_write_client_characteristic_configuration(uint16_t con_handle, gatt_client_characteristic_t * characteristic, uint16_t configuration);

/**
 * @brief Get specific characteristic struct by its uuid.
 * @param  ALL characteristics to be matched
 * @param  The number of characteristics
 * @param  uuid
 * @return return 0 if ok, other refer to ATT_ERR_CORE
 */
gatt_client_characteristic_t* ble_get_characteristic_for_uuid16(gatt_client_characteristic_t *characteristic, uint8_t num, uint16_t uuid16);

gatt_client_characteristic_t* ble_get_characteristic_for_uuid128(gatt_client_characteristic_t *characteristic, uint8_t num, uint8_t *uuid128);


/**
  * @brief  Host renew resolvable private address timeout.
  * @param  rpa params. mainly timeout in seconds and address resolution enable.
  * @return none
  */
void ble_set_rslv_renew_to(rpa_param_t *param);

/**
  * @brief  Host set address resolution enable.
  * @param  1 enable
            0 disable.
  * @return none
  */
void ble_set_rslv_enable(uint8_t enable);

/**
  * @brief  Host add device to resolvable address list.
  * @param  privacy mode.
  * @param  peer device address.
  * @param  peer device irk.
  * @return none
  */
void ble_add_dev_to_ral_list(gap_ral_dev_info_t *ral_dev_info);

/**
  * @brief  Host remove device from resolvable address list.
  * @param  privacy mode.
  * @param  peer device address.
  * @param  peer device irk.
  * @return none
  */
void ble_rmv_dev_from_ral_list(gap_ral_dev_info_t *ral_dev_info);

/**
  * @brief  Host add device to filter accept list.
  * @param  size of wlist.
  * @param  peer device identity address type.
  * @param  peer device identity address.
  * @return none
  */
void ble_add_dev_to_white_list(wlist_param_t *param);

/**
  * @brief  Host remove device from filter accept list.
  * @param  peer device identity address type.
  * @param  peer device identity address.
  * @return none
  */
void ble_rmv_dev_from_white_list(wlist_param_t *param);

/**
  * @brief  Host read filter accept list size.
  * @return none
  */
void ble_rd_dev_white_list(void);

/**
  * @brief  Host clear filter accept list.
  * @return none
  */
void ble_clr_dev_white_list(void);

/**
  * @brief  Used by the user to enter passkey when BLE_EVT_PASSKEY_INPUT event is triggered.
  * @return none
  */
bool ble_sm_passkey_input(uint16_t con_handle, uint32_t passkey);

/**
 * @brief Delete the bonding information of a specified address
 * @param address_type
 * @param address
 * @return return true if ok, invalid parameters will return false
 */
bool ble_delete_bonding_for_addr(bd_addr_type_t address_type, bd_addr_t address);

/**
 * @brief Delete the bonding information of a specified index
 * @param index: [0,N), N can be get form ble_get_bonding_cnt() function
 * @return return true if ok, invalid parameters will return false
 */
bool ble_delete_bonding_for_index(uint8_t index);

/**
 * @brief Delete all bonding information
 */
void ble_delete_bonding_all(void);

/**
 * @brief Get the number of bonding information
 * @return The number of binding information
 */
uint8_t ble_get_bonding_cnt(void);


/**
 * @brief Gets the bonding information for the specified index
 * @param index: [0,N), N can be get form ble_get_bonding_cnt() function
 * @return return true if ok, invalid parameters will return false
 */
bool ble_get_bonding_info_for_index(uint8_t index, sm_bonding_info_t* info);

/**
 * @brief Get the bonding index for connect handle
 * @return index. -1 is unknown
 */
int16_t ble_get_bonding_index_for_conn_handle(uint16_t conn_handle);

/**
 * @brief  Initialize the timer memery pool.
 * @note   This function and a series of related functions are invoked after bt init.
 * @param  pool: memery pool head address.
 * @param  size: byte size of memery pool, one alarm timer need 28Bytes memery.
 * @retval None.
 */
void ble_alarm_timer_init(void *pool, uint32_t size);

/**
 * @brief  Start specified handle alarm timer.
 * @param  handle: alarm timer handle.
 * @retval result code.
 */
uint8_t ble_alarm_timer_start(ble_timer_handle_t handle);

/**
 * @brief  Stop specified handle alarm timer.
 * @param  handle: alarm timer handle.
 * @retval result code.
 */
uint8_t ble_alarm_timer_stop(ble_timer_handle_t handle);

/**
 * @brief  Acquire a alarm timer.
 * @param  handle: alarm timer handle.
 * @param  interval: alarm timer trigger interval, unit [1, 0xffffff) ms.
 * @param  is_repeat: trigger mode.
 * @param  callback: callback function.
 * @retval result code.
 */
uint8_t ble_alarm_timer_acquire(ble_timer_handle_t *handle, uint32_t interval, uint8_t is_repeat, bt_timer_callback_t callback);

/**
 * @brief  Release specified id alarm timer.
 * @param  handle: alarm timer handle.
 * @retval result code.
 */
uint8_t ble_alarm_timer_release(ble_timer_handle_t handle);

/**
 * @brief  Query specified handle alarm timer remain time.
 * @param  handle: alarm timer handle.
 * @param  remain: the remain time for specified handle alarm timer.
 * @retval result code.
 */
uint8_t ble_alarm_timer_query_time(ble_timer_handle_t handle, uint32_t *remain);

/**
 * @brief  Modify specified handle alarm timer interval, if the timer is start, it
 *         will be re-start after update interval param.
 * @param  handle: alarm timer handle.
 * @param  interval: new interval, unit [1, 0xffffff) ms.
 * @param  is_repeat: new is_repeat mode state.
 * @retval result code.
 */
uint8_t ble_alarm_timer_modify_interval(ble_timer_handle_t handle, uint32_t interval, uint8_t is_repeat);


/**
 * @brief  Get connection rssi .
 * @param  conhdl: connect handle.
 * @retval -128 ~ 127dBm.
 */
int8_t ble_get_conn_rssi(uint16_t conhdl);

/**
 * @brief Set ble max mtu.
 * @param max_mtu, the current maximum value is 247.
 * @return return true if ok, invalid parameters will return false
 */
bool ble_max_mtu_set(uint16_t max_mtu);

/**
 * @brief Set ble tx power.
 * @param  tx_pwr_sel:  BLE_TXPWR_MINUS_12DB(-12dbm)
 *                      BLE_TXPWR_MINUS_8DB(-8dbm)
 *                      BLE_TXPWR_MINUS_6DB(-6dbm)
 *                      BLE_TXPWR_MINUS_4DB(-4dbm)
 *                      BLE_TXPWR_0DB(0dbm)
 *                      BLE_TXPWR_4DB(4dbm)
 *                      BLE_TXPWR_8DB(8dbm)
 *         txpwr_dec:   from 0 to 24, each gear will result in a 0.5db reduction in TX power.
 * @return return true if ok, invalid parameters will return false
 */
bool ble_rf_set_tx_pwr(uint8_t tx_pwr_sel, uint8_t txpwr_dec);

/**
 * @brief Get link layer remote version info
 * @param  con_handle
 * @param  vers
 * @return return true if ok, invalid parameters will return false
 */
bool ble_ll_version_get(uint16_t con_handle, ll_version_t *vers);

/**
 * @brief Initialize external Power Amplifier gpio.
 * @param  gpio_pin_txen, only support PB0 to PA7, which means formal parameter is between GPIO_PIN_0 and GPIO_PIN_7
 * @param  gpio_pin_rxen, only support PB0 to PA7, which means formal parameter is between GPIO_PIN_0 and GPIO_PIN_7
 * @return return true if ok, invalid parameters will return false
 */
bool ble_rf_external_pa_init(uint32_t gpio_pin_txen, uint32_t gpio_pin_rxen);

/**
 * @brief Get link layer feature exchage
 * @param  con_handle
 * @param  feature_data
 * @return return true if ok, invalid parameters will return false
 */
bool ble_ll_feature_exchange_get(uint16_t con_handle, struct le_features *feature_data);

#endif //_API_BTSTACK_H
