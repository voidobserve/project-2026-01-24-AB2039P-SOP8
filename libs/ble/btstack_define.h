#ifndef _BTSTACK_DEFINE_H
#define _BTSTACK_DEFINE_H

#define BLE_ALARM_TIMER_LEN                                         28

/**
 * @format 21
 * @param handle
 * @param status
 */
#define BLE_EVT_PROFILE_FIND_DONE                                   0xA0

/**
 * @format 2228
 * @param con_handle
 * @param start_group_handle
 * @param end_group_handle
 * @param uuid128
 */
#define BLE_EVT_SERVICE_FIND_RESULT                                 0xA1

/**
 * @format 222228
 * @param con_handle
 * @param start_handle
 * @param value_handle
 * @param end_handle
 * @param properties
 * @param uuid128
 */
#define BLE_EVT_CHARACTERISTIC_FIND_RESULT                          0xA2


/**
 * @format 12222
 * @param status
 * @param handle
 * @param interval
 * @param latency
 * @param timeout
 */
#define BLE_EVT_CONNECT_PARAM_UPDATE_DONE                           0xB2

/**
 * @format 1621
 * @param address_type
 * @param address
 * @param handle
 * @param role
 */
#define BLE_EVT_CONNECT                                             0xB3

/**
 * @format 21
 * @param handle
 * @param disconnect_reason
 */
#define BLE_EVT_DISCONNECT                                          0xB4

/**
 * @format 22
 * @param handle
 * @param MTU
 */
#define BLE_EVT_MTU_EXCHANGE_DONE                                   0xB5

 /**
  * @format 122
  * @param status
  * @param conn_handle
  * @param attribute_handle
  */
#define BLE_EVT_INDICATE_DONE                                       0xB6

/**
 * @format 121
 * @param status
 * @param conn_handle
 * @param encryption_enabled
 */
#define BLE_EVT_ENCRYPTION_CHANGE                                   0xC7

 /**
  * @format 21614
  * @param handle
  * @param addr_type
  * @param address
  * @param secure_connection - set to 1 if LE Secure Connection pairing will be used
  * @param passkey
  */
#define BLE_EVT_PASSKEY_DISPLAY                                     0xC9


 /**
  * @format 2161
  * @param handle
  * @param addr_type
  * @param address
  * @param secure_connection - set to 1 if LE Secure Connection pairing will be used
  */
#define BLE_EVT_PASSKEY_INPUT                                       0xCB

 /**
  * @format 216
  * @param handle
  * @param addr_type
  * @param address
  */
#define BLE_EVT_IDENTITY_RESOLVING_FAIL                             0xCE

 /**
  * @brief Identify resolving succeeded
  *
  * @format 216162
  * @param handle
  * @param addr_type
  * @param address
  * @param identity_addr_type
  * @param identity_address
  * @param index
  *
  */
#define BLE_EVT_IDENTITY_RESOLVING_SUCCEED                          0xCF


/**
 * @brief Emitted to inform app that pairing has started.
 * @format 216
 * @param handle
 * @param addr_type
 * @param address
 */
#define BLE_EVT_PAIRING_START                                       0xD4

/**
  * @brief Emitted to inform app that pairing is complete.
  * @format 21611
  * @param handle
  * @param addr_type
  * @param address
  * @param status
  * @param reason
  */
#define BLE_EVT_PAIRING_DONE                                        0xD5

/**
 * @brief Emitted to inform app that ltk is missing.
 * @format 216
 * @param handle
 * @param addr_type
 * @param address
 */
#define BLE_EVT_LTK_MISSING                                         0xD8


/**
 * @format 11611N
 * @param advertising_event_type
 * @param address_type
 * @param address
 * @param rssi
 * @param data_length
 * @param data
 */
#define BLE_EVT_ADV_REPORT                                          0xE2


// ATT_ERR_CODE
#define ATT_ERR_NO_ERR                                              0x00
#define ATT_ERR_INVALID_HANDLE                                      0x01
#define ATT_ERR_READ_NOT_PERMITTED                                  0x02
#define ATT_ERR_WRITE_NOT_PERMITTED                                 0x03
#define ATT_ERR_INVALID_PDU                                         0x04
#define ATT_ERR_INSUFFICIENT_AUTHENTICATION                         0x05
#define ATT_ERR_REQUEST_NOT_SUPPORTED                               0x06
#define ATT_ERR_INVALID_OFFSET                                      0x07
#define ATT_ERR_INSUFFICIENT_AUTHORIZATION                          0x08
#define ATT_ERR_PREPARE_QUEUE_FULL                                  0x09
#define ATT_ERR_ATTRIBUTE_NOT_FOUND                                 0x0a
#define ATT_ERR_ATTRIBUTE_NOT_LONG                                  0x0b
#define ATT_ERR_INSUFFICIENT_ENCRYPTION_KEY_SIZE                    0x0c
#define ATT_ERR_INVALID_ATTRIBUTE_VALUE_LENGTH                      0x0d
#define ATT_ERR_UNLIKELY_ERROR                                      0x0e
#define ATT_ERR_INSUFFICIENT_ENCRYPTION                             0x0f
#define ATT_ERR_UNSUPPORTED_GROUP_TYPE                              0x10
#define ATT_ERR_INSUFFICIENT_RESOURCES                              0x11
#define ATT_ERR_VALUE_NOT_ALLOWED                                   0x13
#define ATT_ERR_IN_WRONG_STATE                                      0x80
#define ATT_ERR_NOTIFICATION_NOT_SUPPORTED                          0x81
#define ATT_ERR_INDICATION_NOT_SUPPORTED                            0x82
#define ATT_ERR_INDICATION_IN_PORGRESS                              0x83
#define ATT_ERR_TIMEOUT                                             0x84
#define ATT_ERR_DISCONNECT                                          0x85
#define ATT_ERR_DATA_MISMATCH                                       0x86




//Attribute Property
#define ATT_PROPERTY_BROADCAST                                      0x01
#define ATT_PROPERTY_READ                                           0x02
#define ATT_PROPERTY_WRITE_WITHOUT_RESPONSE                         0x04
#define ATT_PROPERTY_WRITE                                          0x08
#define ATT_PROPERTY_NOTIFY                                         0x10
#define ATT_PROPERTY_INDICATE                                       0x20
#define ATT_PROPERTY_AUTHENTICATED_SIGNED_WRITE                     0x40
#define ATT_PROPERTY_EXTENDED_PROPERTIES                            0x80


//GATT_CLIENT_CHARACTERISTIC_CONFIGURATION
#define GATT_CCC_NOTIFICATION                                       0x01
#define GATT_CCC_INDICATION                                         0x02


//ATT_TRANSACTION_MODE
#define ATT_TRANSACTION_WRITE                                       0x00
#define ATT_TRANSACTION_PREPARE_WRITE                               0x01
#define ATT_TRANSACTION_WRITE_EXECUTE                               0x02
#define ATT_TRANSACTION_WRITE_CANCEL                                0x03


//SM_AUTHREQ
#define SM_AUTHREQ_NO_BONDING                                       0x00
#define SM_AUTHREQ_BONDING                                          0x01
#define SM_AUTHREQ_MITM_PROTECTION                                  0x04
#define SM_AUTHREQ_SECURE_CONNECTION                                0x08
#define SM_AUTHREQ_KEYPRESS                                         0x10
#define SM_AUTHREQ_CT2                                              0x20


//BLE WORK MODE
typedef enum {
    MODE_NORMAL     = 0,        //normal mode
    MODE_FCC_TEST,              //fcc test mode, use uart for communication
    MODE_BQB_RF_BLE,            //bqb test mode，use uart for communication
    MODE_IODM_TEST,             //iodm test mode，use uart for communication
    MODE_WIRELESS,              //wireless mode
} BLE_WORK_MODE;


typedef enum {
    FCC_TX_TONE = 1,
    FCC_TX_TEST,
    FCC_RX_TEST,
} FCC_RF_MODE;

enum {
    TXPKT_KICK_DISABLE = 0,
    TXPKT_KICK_ENABLE,
    TXPKT_KICK_AUTO,
};

// IO Capability Values
enum {
    IO_CAPABILITY_DISPLAY_ONLY = 0,
    IO_CAPABILITY_DISPLAY_YES_NO,
    IO_CAPABILITY_KEYBOARD_ONLY,
    IO_CAPABILITY_NO_INPUT_NO_OUTPUT,
    IO_CAPABILITY_KEYBOARD_DISPLAY, // not used by secure simple pairing
};

//ADDRESS TYPE
typedef enum {
    GAP_PUBLIC_ADDRESS_TYPE = 0,
    GAP_RANDOM_ADDRESS_TYPE_STATIC,
    GAP_RANDOM_ADDRESS_NON_RESOLVABLE,
    GAP_RANDOM_ADDRESS_RESOLVABLE,
} gap_random_address_type_t;

typedef enum {
    BD_ADDR_TYPE_PUBLIC = 0,
    BD_ADDR_TYPE_RANDOM = 1,
} bd_addr_type_t;


//ADV_TYPE
enum {
    ADV_TYPE_IND = 0,
    ADV_TYPE_DIRECT_HI_IND,
    ADV_TYPE_SCAN_IND,
    ADV_TYPE_NONCONN_IND,
    ADV_TYPE_DIRECT_LO_IND,
};

enum adv_channel_map
{
    ///Byte value for advertising channel map for channel 37 enable
    ADV_CHNL_37_EN                = 0x01,
    ///Byte value for advertising channel map for channel 38 enable
    ADV_CHNL_38_EN                = 0x02,
    ///Byte value for advertising channel map for channel 39 enable
    ADV_CHNL_39_EN                = 0x04,
    ///Byte value for advertising channel map for channel 37, 38 and 39 enable
    ADV_ALL_CHNLS_EN              = 0x07,
};

///Advertising filter policy
enum le_adv_filter_policy
{
    ///Allow both scan and connection requests from anyone
    LE_ADV_ALLOW_SCAN_ANY_CON_ANY    = 0x00,
    ///Allow both scan req from White List devices only and connection req from anyone
    LE_ADV_ALLOW_SCAN_WLST_CON_ANY,
    ///Allow both scan req from anyone and connection req from White List devices only
    LE_ADV_ALLOW_SCAN_ANY_CON_WLST,
    ///Allow scan and connection requests from White List devices only
    LE_ADV_ALLOW_SCAN_WLST_CON_WLST,
};

//SCAN STA
typedef enum {
    LE_SCAN_STA_DISABLE,
    LE_SCAN_STA_ENABLE,
    LE_SCAN_STA_W4_DISABLE,
    LE_SCAN_STA_W4_ENABLE,
} le_scanning_state_t;

typedef enum {
    LE_CONN_INITIATE_ERR_NO_ERR,
    LE_CONN_INITIATE_ERR_CONN_EXISTS,
    LE_CONN_INITIATE_ERR_MEMORY_CAPA_EXCEED,
    LE_CONN_INITIATE_ERR_INVALID_PARAM,
} le_conn_initiate_err_code_t;

typedef enum
{
    BLE_TXPWR_MINUS_12DB = 0x8c,
    BLE_TXPWR_MINUS_8DB = 0x88,
    BLE_TXPWR_MINUS_6DB = 0x86,
    BLE_TXPWR_MINUS_4DB = 0x84,
    BLE_TXPWR_0DB = 0x00,
    BLE_TXPWR_4DB = 0x04,
    BLE_TXPWR_8DB = 0x08,
} ble_txpwr_sel_t;

typedef uint16_t ble_con_handle_t;

typedef uint32_t ble_timer_handle_t;

typedef void (*kick_func_t)(uint16_t con_handle, uint16_t config);

typedef uint16_t (*att_read_callback_t)(uint16_t con_handle, uint16_t attribute_handle, uint16_t offset, uint8_t * buffer, uint16_t buffer_size);

typedef int (*att_write_callback_t)(uint16_t con_handle, uint16_t attribute_handle, uint16_t trans_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size);

typedef uint16_t (*att_notify_callback_t)(uint16_t con_handle, uint16_t attribute_handle, uint8_t * buffer, uint16_t buffer_size);

typedef void (*att_event_callback_t) (uint8_t event_type, uint8_t *param, uint16_t size);

typedef void (*ble_init_callback_t)(void);

typedef void (*bb_timer_proc_callback_t)(uint32_t time);

typedef void (*ble_vs_tbox_init_callback_t)(void);

typedef void (*bt_timer_callback_t)(ble_timer_handle_t hdl);


typedef struct {
    uint8_t adv_en;
    uint8_t adv_data[31];
    uint8_t adv_len;
    uint8_t scan_rsp[31];
    uint8_t scan_rsp_len;
    uint16_t adv_int_min;           //advertisement interval
    uint16_t adv_int_max;           //advertisement interval
    uint8_t adv_type;
    uint8_t direct_address_typ;     //only use for direct adv
    uint8_t direct_address[6];      //only use for direct adv
    uint8_t channel_map;
    uint8_t filter_policy;
} adv_param_t;

typedef struct __attribute__((packed)){
    uint8_t     event_type;
    uint8_t     addr_type;
    uint8_t     addr[6];
    char        rssi;
    uint8_t     report_len;
    const uint8_t * report;
    uint8_t     offset;
} adv_report_t;

typedef struct {
     uint8_t   adv_type;
     uint8_t   data_len;
     uint8_t*  data;
} adv_struct_t;

typedef struct {
    uint8_t scan_type;
    uint16_t scan_interval;
    uint16_t scan_window;
} scan_param_t;

typedef uint8_t bd_addr_t[6];

typedef struct {
    // Key value MSB -> LSB
    uint8_t key[16];
}gap_sec_key_t;

// Do not modify!!
typedef struct {
    // Address type of device. 0 public/1 random
    uint8_t addr_type;
    // BD Address of device
    bd_addr_t addr;
}gap_bdaddr_t;

/**
 * @brief Identity Resolving Key Information
 */
typedef struct {
    // Identify Resolving Key
    gap_sec_key_t irk;
    // Identity broadcast address of device
    gap_bdaddr_t addr;
}gapc_irk_t;

/**
 * @brief Resolving list information about a device.
 */
typedef struct {
    // Privacy Mode
    uint8_t priv_mode;  //PRIV_TYPE_NETWORK = 0x00, Controller accept identity address only
                        //PRIV_TYPE_DEVICE  = 0x01, Controller accept both identity address and resolvable address.
    // Device Identity address
    gap_bdaddr_t addr;
    // Peer device identity resolve key
    uint8_t peer_irk[16];
}gap_ral_dev_info_t;

typedef struct {
    uint8_t rpa_en;
    uint8_t privacy_mode;
    uint16_t renew_to;
    gap_sec_key_t peer_irk;
    gap_bdaddr_t addr;
}rpa_param_t;

typedef struct {
    // Number of entries to be added in the list. 0 means that list content has to be cleard.
    uint8_t size;
    // List of entries to be added in the list.
    gap_bdaddr_t addr;
}wlist_param_t;

typedef struct {
    uint16_t        address_type;
    uint16_t        real_address_type;
    bd_addr_t       address;
    gap_sec_key_t   peer_irk;
} sm_bonding_info_t;

// Read & Write Callbacks for handle range
typedef struct att_service_handler {
    void * item;
    uint16_t start_handle;
    uint16_t end_handle;
    att_read_callback_t read_callback;
    att_write_callback_t write_callback;
    att_event_callback_t event_handler;
} att_service_handler_t;

typedef struct att_client_handler {
    void * item;
    att_read_callback_t read_callback;
    att_notify_callback_t notify_callback;
    att_event_callback_t event_handler;
} att_client_handler_t;

typedef struct {
    uint16_t start_group_handle;
    uint16_t end_group_handle;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} gatt_client_service_t;

typedef struct {
    uint16_t start_handle;
    uint16_t value_handle;
    uint16_t end_handle;
    uint16_t properties;
    uint16_t uuid16;
    uint8_t  uuid128[16];
} gatt_client_characteristic_t;


typedef struct {
    uint8_t rf_mode;
    uint8_t tx_power;
    uint8_t tx_freq;
    uint8_t rx_freq;
    uint8_t phy_type;
} fcc_cfg_t;

typedef struct
{
    uint8_t  vers;
    uint16_t compid;
    uint16_t subvers;
} ll_version_t;

///Supported LE Features structure
struct le_features
{
    ///8-byte array for LE features
    uint8_t feats[8];
};

#endif
