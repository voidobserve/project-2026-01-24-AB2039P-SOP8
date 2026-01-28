#ifndef _API_OS_H_
#define _API_OS_H_

typedef struct _thread_cfg_t{
    uint8_t enable;
    uint8_t priority;
    uint16_t stack_heap_size;
}thread_cfg_t;

struct thread_cfg_cb{
    thread_cfg_t bt_stack;
    thread_cfg_t dirver;
    thread_cfg_t timer;
    thread_cfg_t main;          //main线程必须使能
};

void thread_timer_create(void);
void thread_driver_create(void);
void thread_btstack_create(void);

typedef void (*thd_drv_callback_t)(uint32_t msg);

/**
 * @brief  Post a msg to driver thread.
 *         @note: if should be called after 'thread_driver_user_callback_register', or failed.
 * @param  msg: the msg need to post to driver thread.[0, 0x3fffffff]
 * @retval true if msg post successfully, or false.
 */
bool thread_driver_user_msg_post(uint32_t msg);

/**
 * @brief  Register a callback func for driver vendor msg.
 *         @note: the func should in Ram area and driver thread should be exists, or will failed.
 * @param  callback: the callback func.
 * @retval true if func register successfully, or false.
 */
bool thread_driver_user_callback_register(thd_drv_callback_t callback);

#endif

