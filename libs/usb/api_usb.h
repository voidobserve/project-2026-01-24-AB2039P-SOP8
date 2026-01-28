#ifndef _USB_API_H
#define _USB_API_H

#include "usb_define.h"

#define EP_CNT                  4

#define USB_EP0_MAX_SIZE        64
#define USB_EP1_MAX_SIZE        64
#define USB_EP2_MAX_SIZE        256
#define USB_EP3_MAX_SIZE        1023


enum {
    USBCHK_ONLY_HOST,
    USBCHK_ONLY_DEVICE,
    USBCHK_OTG,
};

enum {
    USB_DISCONNECT,
    USB_DEV_CONNECTED,
    USB_HOST_CONNECTED,
    USB_DETECTING,
};

enum {
    ///usb device message.
    MSG_USB_EP_RESET = 32,          //usb device ep0 reset message.
    MSG_USB_EP0_CTL_FLOW,           //usb device control flow message.
    MSG_USB_EP1_IN,
    MSG_USB_EP1_OUT,
    MSG_USB_EP2_IN,
    MSG_USB_EP2_OUT,
    MSG_USB_EP3_IN,
    MSG_USB_EP3_OUT,
    MSG_USB_SUSPEND,
    MSG_USB_RESUME,
};

typedef struct _epcb_t {
    psfr_t sfr;

    u8 type;                        //EP Type: Ctrl, Bulk, Int, ISOC
    u8 index;                       //EP Index
    volatile u8  error      : 1,    //USB通信出错
        dir                 : 1,    //EP的方向
        halt                : 1,    //Halt标志
        first_pkt           : 1;    //Transfer first packet

    u8 *buf;                        //EP的BUF地址

    const u8 *xptr;                 //当前发送/接收指针
    u16 xlen;                       //当前发送/接收剩余
    u16 xcnt;                       //已发送/接收统计
    u16 epsize;                     //EP Size
} epcb_t;

typedef struct _spb_wrap_t {
    union {
        struct {
            u8 recipient        : 5,
                type            : 2,
                dir             : 1;
        };
        u8 reqtype;
    };
    u8 req;
    u16 val;
    u16 index;
    u16 len;
} spb_wrap_t;


typedef bool (*usb_init_handler)(void);
typedef bool (*usb_evt_handler)(uint8_t event, spb_wrap_t *spb, uint8_t *data, uint8_t data_len);

typedef struct {
    usb_init_handler init;
    usb_evt_handler evt;
}usb_handler_cb_t;


void usb_handler_register(usb_handler_cb_t *handler);
void usb_sof_hook_register(void (*callback)(void));

u8 usbchk_connect(u8 mode);
u8 usbchk_host_connect(void);
u8 usbchk_host_connect_2(void);

void usb_init(void);
void usb_device_enter(void);
void usb_device_exit(void);
bool usb_device_is_suspend(void);
void usb_device_suspend_enable(void);
void usb_device_resume(void);


void usb_ep_init(epcb_t *epcb);
uint16_t usb_ep_get_max_len(uint8_t ep_index);
uint16_t usb_ep_get_rx_len(epcb_t *epcb);
void usb_ep_clear_rx_fifo(epcb_t *epcb);
bool usb_ep_start_transfer(epcb_t *epcb, uint len);
bool usb_ep_transfer(epcb_t *epcb);
bool usb_ep0_start_transfer(void *buf, uint len);
bool usb_ep0_transfer(void *buf, uint len);
epcb_t * usb_ep_get_for_index(uint8_t index, uint8_t dir);
void usb_ep_reset(epcb_t *epcb);
void usb_ep_clear(epcb_t *epcb);
void usb_ep_halt(epcb_t *epcb);

#endif // _USB_API_H
