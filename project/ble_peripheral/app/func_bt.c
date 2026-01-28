#include "include.h"
#include "func.h"

#if FUNC_BT_EN

AT(.text.func.msg)
void func_bt_message_do(u16 msg)
{
    switch (msg) {
        case MSG_SYS_1S:
            // printf("MSG_SYS_1S\n");
            break;

        default:
            func_message(msg);
            break;
    }
}


AT(.text.app.proc.msg)
void func_bt_message(u16 msg)
{
    if(msg){
        func_bt_message_do(msg);
    }
}

AT(.text.app.proc.bt)
void func_bt_sub_process(void)
{
    ble_app_proc();
}

AT(.text.app.proc.bt)
void func_bt_process(void)
{
    func_process();
    func_bt_sub_process();

#if FUNC_TBOX_EN
    if (is_prod_test_tbox_mode()) {
        func_cb.sta = FUNC_TBOX;
        return;
    }
#endif

#if SYS_PWROFF_TIME
    if(sys_cb.pwroff_delay == 0) {
        func_cb.sta = FUNC_PWROFF;
        return;
    }
#endif

#if SYS_SLEEP_EN
    if(sleep_process(ble_is_sleep)) {

    }
#endif
}

AT(.text.func.bt)
void func_bt_init(void)
{
    bsp_ble_init();
}

AT(.text.func.bt)
void func_bt_enter(void)
{
    msg_queue_clear();

#if LE_FCC_TEST_EN
    ble_set_work_mode(MODE_FCC_TEST);
#elif LE_BQB_RF_EN
    ble_set_work_mode(MODE_BQB_RF_BLE);
#else
    ble_set_work_mode(MODE_NORMAL);
#endif

    func_bt_init();
}

AT(.text.func.bt)
void func_bt_exit(void)
{
#if FUNC_TBOX_EN
    if (is_prod_test_tbox_mode() == 0)
#endif //FUNC_TBOX_EN
    {
        btstack_deinit();
    }

    ble_set_work_mode(MODE_NORMAL);

    func_cb.last = FUNC_BT;
}

AT(.text.func.bt)
void func_bt(void)
{
    printf("%s\n", __func__);

    func_bt_enter();

    while (func_cb.sta == FUNC_BT) {
        func_bt_process();
        func_bt_message(msg_dequeue());
    }

    func_bt_exit();
}

#endif //FUNC_BT_EN
