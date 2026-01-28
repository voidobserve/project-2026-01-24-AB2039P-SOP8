#ifndef _API_UPDATE_H
#define _API_UPDATE_H

typedef enum {
    FOT_ERR_OK,
    FOT_ERR_NO_UPDATA,
    FOT_ERR_KEY,
    FOT_ERR_FILE_FORMAT,
    FOT_ERR_FILE_TAG,
    FOT_ERR_FILE_DATA,
    FOT_ERR_MAC_SIZE,
    FOT_ERR_START,
    FOT_ERR_DOWN_START,
    FOT_ERR_HEAD2_START,
    FOT_ERR_DOWN_LAST,
    FOT_ERR_CRC_VERIFY,
    FOT_ERR_AREA_SIZE,
    /*以上err类型和库里面对应,通过fot_get_err()获取到*/

    FOT_ERR_SEQ = 0x40,
    FOT_ERR_DATA_LEN,

    FOT_UPDATE_PAUSE = 0xfd,
    FOT_UPDATE_CONTINUE = 0xfe,
    FOT_UPDATE_DONE = 0xff,
} FOT_ERR_ENUM;

//FOTA双备份升级
void fot_init(void);
u32 fot_get_curaddr(void);
bool fot_write(void *buf, u32 addr, u32 len);
u8 fot_get_err(void);
bool fot_breakpoint_info_read(void);
bool fot_is_update_success(void);
u32 fot_head_crc_get(void);

//FOTA压缩升级
void ota_pack_init(void);
bool ota_pack_write(u8 *buf);
u8 ota_pack_get_err(void);
bool ota_pack_is_update_success(void);
bool ota_pack_breakpoint_info_read(void);
u32 ota_pack_get_curaddr(void);

#endif
