# AB2039P-SOP8 蓝牙芯片固件项目说明文档

## 项目概述

这是一个基于鼎润科技AB2039P-SOP8蓝牙芯片的固件项目，主要实现了蓝牙低功耗（BLE）功能及多种外设驱动。项目采用模块化设计，具有完整的电源管理、低功耗控制和多种功能模式支持。

## 主要功能模块

### 1. 系统初始化模块
- [bsp_sys_init]：系统初始化函数，包括：
  - 配置参数获取 ([xcfg_init])
  - 变量初始化 ([bsp_var_init])
  - 电源管理初始化 ([pmu_init])
  - 时钟设置 ([sys_clk_set])
  - 外设初始化

### 2. 功能调度模块
- [func_run]：主功能循环，根据[func_cb.sta]状态切换不同的功能模式
- 支持的功能模式包括：
  - [FUNC_BT]：蓝牙功能
  - [FUNC_LE_FCC]：FCC射频测试模式
  - [FUNC_LE_BQB_RF]：BQB射频测试模式
  - [FUNC_IODM]：输入输出数据管理
  - [FUNC_TBOX]：TBox模式
  - [FUNC_IDLE]：空闲模式
  - [FUNC_PWROFF]：关机模式

## 函数层次调用关系

### 主程序入口
```
main()
├── [sys_rst_init] : 初始化复位原因
├── [lowpwr_get_wakeup_source] : 获取唤醒源
├── [sys_ram_info_dump] : 打印内存信息
├── [bsp_sys_init] : 系统初始化
├── [prod_test_init] : 生产测试初始化
└── [func_run] : 启动功能调度主循环
```

### 功能调度主循环
```
func_run()
├── [func_enter] : 进入功能前处理
└── 根据func_cb.sta状态选择执行以下函数之一：
    ├── [func_bt] : 蓝牙功能处理
    ├── [func_le_fcc] : FCC测试模式处理
    ├── [func_le_bqb_rf] : BQB射频测试模式处理
    ├── [func_iodm] : 输入输出数据管理
    ├── [func_tbox] : TBox模式处理
    ├── [func_idle] : 空闲模式处理
    └── [func_pwroff] : 关机处理
```

### 蓝牙功能处理流程
```
func_bt()
├── [func_bt_enter] : 蓝牙功能初始化
│   ├── [msg_queue_clear] : 清空消息队列
│   ├── [ble_set_work_mode] : 设置蓝牙工作模式
│   └── [func_bt_init] : 蓝牙初始化
│       └── [bsp_ble_init] : 底层蓝牙初始化
├── 循环执行直到func_cb.sta改变
│   ├── [func_bt_process] : 蓝牙处理函数
│   │   ├── [func_process] : 通用功能处理
│   │   │   ├── [WDT_CLR] : 喂狗操作
│   │   │   ├── [bsp_vbat_process] : 电池电压检测处理
│   │   │   ├── [bsp_tsensor_process] : 温度传感器处理
│   │   │   └── [uart_transfer_rx_event] : UART传输事件处理
│   │   ├── [func_bt_sub_process] : 蓝牙子处理
│   │   │   └── [ble_app_proc] : 蓝牙应用处理
│   │   └── 检查是否需要切换到其他模式或进入睡眠
│   └── [func_bt_message] : 消息处理
│       └── [msg_dequeue] : 获取并处理消息
└── [func_bt_exit] : 蓝牙功能退出处理
    ├── [btstack_deinit] : 蓝牙栈反初始化
    └── [ble_set_work_mode] : 恢复正常工作模式
```

### 系统定时器处理
```
usr_tmr5ms_callback()
├── tmr5ms_cnt++ : 计数器增加
├── [bsp_saradc_scan] : SARADC扫描
├── [bsp_key_scan] : 按键扫描
├── 每100ms执行一次
│   └── [lowpwr_tout_ticks] : 低功耗超时计数
├── 每500ms执行一次
│   └── [msg_enqueue] : 发送MSG_SYS_500MS消息
└── 每1s执行一次
    └── [msg_enqueue] : 发送MSG_SYS_1S消息
```

### 按键消息处理
```
func_message(msg)
├── 根据消息类型进行不同处理
├── [KEY_ID_PP | KEY_SHORT_UP] : PP按键短按抬起
├── [KEY_ID_PP | KEY_LONG] : PP长按
├── [KEY_ID_PP | KEY_HOLD] : PP连按
├── [KEY_ID_PP | KEY_LONG_UP] : PP长按抬起 → 设置状态为FUNC_PWROFF
├── [KEY_ID_PP | KEY_DOUBLE] : PP双击
├── [KEY_ID_PP | KEY_THREE] : PP三击
├── [KEY_ID_K1 | KEY_SHORT_UP] : K1短按抬起
├── [KEY_ID_K2 | KEY_SHORT_UP] : K2短按抬起
├── [KEY_ID_K3 | KEY_SHORT_UP] : K3短按抬起
├── [KEY_ID_K4 | KEY_SHORT_UP] : K4短按抬起
└── 有效事件处理后重置低功耗延迟计数器
```

## 驱动模块

项目包含多个硬件驱动模块：

- [driver_clk] : 时钟驱动
- [driver_gpio] : GPIO驱动
- [driver_hsuart] : 高速UART驱动
- [driver_ledc] : LED控制器驱动
- [driver_lowpwr] : 低功耗管理驱动
- [driver_pwm] : PWM驱动
- [driver_rtc] : RTC驱动
- [driver_saradc] : SAR ADC驱动
- [driver_spi] : SPI驱动
- [driver_tmr] : 定时器驱动
- [driver_uart] : UART驱动
- [driver_wdt] : 看门狗驱动

## 配置文件

- config.h : 主要配置文件
- config_define.h : 配置定义文件
- config_extra.h : 额外配置文件
- xcfg.h : 扩展配置文件

## 编译构建

项目使用Makefile进行构建，通过BUILD_README.md文件可以了解更多构建相关信息。