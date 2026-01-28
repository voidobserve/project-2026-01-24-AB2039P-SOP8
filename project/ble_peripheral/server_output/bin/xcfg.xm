depend(0x01020000)

config(SUB, "系统配置", "系统相关配置");
config(LEVEL, 0x03);
config(CHECK, "BUCK MODE", "是否设置为BUCK MODE", BUCK_MODE_EN, 0);
config(LIST, "OSC基础电容", "同时配置24晶振OSCI与OSCO负载电容", UOSC_BOTH_CAP, 2, "0PF", "6PF", 0);
config(BYTE, "自定义OSCI电容", "配置24M晶振OSCI负载电容（0.25PF）。电容大小：n * 0.25PF + 基础电容", UOSCI_CAP, 0, 63, 45);
config(BYTE, "自定义OSCO电容", "配置24M晶振OSCO负载电容（0.25PF）。电容大小：n * 0.25PF + 基础电容", UOSCO_CAP, 0, 63, 45);
config(CHECK,  "优先使用产测电容值",  "是否优先使用产测校准的OSC电容值，没过产测或者关闭时使用<自定义OSCI电容>、<自定义OSCO电容>",  FT_OSC_CAP_EN,  1);


config(SUB, "蓝牙配置", "蓝牙的相关配置");
config(TEXT, "BLE名称", "手机上可以看到的BLE蓝牙名称", LE_NAME, 32, "LE-Remoter");
config(MAC, "蓝牙地址", "蓝牙的MAC地址", LE_ADDR, 6, 41:42:00:00:00:00, 41:42:FF:FF:FF:FF, 41:42:00:00:00:01);

config(SUB, "RF参数", "蓝牙RF参数");
config(LISTVAL, "RF TX功率选择", "选择RF的TX功率", RF_TX_PWR, BIT, 8, 0, 5, ("8dBm", 8), ("4dBm", 4), ("0dBm", 0), ("-4dBm", 0x84)), ("-6dBm", 0x86));

config(CHECK, "自定义RF参数", "选用自定义RF参数后", BT_RF_PARAM_EN, 0);
config(LEVEL, 0x00);
config(BYTE, "PA_GAIN",    "PA_GAIN, 参考值7",         RF_PA_GAIN,    0,  7,  7, BT_RF_PARAM_EN);
config(LEVEL, 0x03);
config(BYTE, "MIX_GAIN",   "MIX_GAIN, 参考值3~7",      RF_MIX_GAIN,   0,  7,  7, BT_RF_PARAM_EN);
config(BYTE, "DIG_GAIN",   "DIG_GAIN, 参考值30~59",    RF_DIG_GAIN,   30, 61, 58, BT_RF_PARAM_EN);


config(LEVEL, 0x0E);
config(SUB, "产测保留", "产测时保留的一些参数");
config(KEEP);
config(BYTE, "产测OSC基础电容", "同时配置24晶振OSCI与OSCO负载电容,0: 0PF, 1:6PF", OSC_BOTH_CAP, 0, 1, 0);
config(BYTE, "产测OSCI电容", "独立配置24M晶振OSCI负载电容，单位0.25PF。OSCI电容大小：n * 0.25PF + 基础电容, 不要改动默认值0", OSCI_CAP, 0, 63, 0);
config(BYTE, "产测OSCO电容", "独立配置24M晶振OSCO负载电容，单位0.25PF。OSCO电容大小：n * 0.25PF + 基础电容, 不要改动默认值0", OSCO_CAP, 0, 63, 0);
config(KEEPEND)

config(UPD, 0x1F, 0x0);

config(LEVEL, 0x00);
makecfgfile(xcfg.bin);
makecfgdef(xcfg.h);
xcopy(xcfg.h, ../../xcfg.h);
