#include "include.h"
#include "driver_saradc.h"
#include "bsp_saradc_tsen.h"

#if BSP_TSENSOR_EN

#define TRACE_EN                    0
#if TRACE_EN
#define TRACE(...)                  printf("[BSP] ");\
                                    printf(__VA_ARGS__)
#define TRACE_R(...)                print_r(__VA_ARGS__)
#else
#define TRACE(...)
#define TRACE_R(...)
#endif

#define BSP_TSEN_RF_ADJUST_EN       1
#ifdef  DBG_TSEN
#define BSP_TSEN_MAP_DBG_EN         1
#endif


const bsp_tsen_volt_map_t bsp_tsen_volt_map = {{
//  -30   -25   -20   -15   -10   -5     0    5
    384,  392,  403,  411,  418,  424,  434,  443,
//  10    15    20    25    30    35    40    45
    450,  459,  469,  476,  483,  491,  500,  509,
//  50    55    60    65    70    75    80    85
    516,  524,  531,  540,  547,  556,  566,  576,
//  90    95    100   105   110   115   120   125
    583,  595,  602,  611,  618,  628,  634,  643,
//  130
    651, 
}};

static struct {
    uint32_t    refer_adc;
    uint32_t    tsen_adc;
    uint32_t    tick;
    uint16_t    intv;
    uint16_t    cnt;
} bsp_tsen_cb AT(.bss.bsp.tsen.sta);

#if BSP_TSEN_RF_ADJUST_EN

const bsp_rf_pll_cfg_t bsp_tsen_pll_cfg = {{
    /* level0: */   1398101,
    /* level1: */   1390000,
    /* level2: */   1330000,
}};

const bsp_rf_cfg_t bsp_tsen_rf_cfg = {
    .volt_th_up         = 60,
    .volt_th_down       = 40,
    .volt_level_vco     = 5,
    .volt_level_bt      = 10,
    .pll_th1_up         = 80,
    .pll_th1_donw       = 70,
    .pll_th2_up         = 110,
    .pll_th2_donw       = 100,
};

static struct {
    uint8_t     volt_level;
    uint8_t     pll_level;
    uint8_t     vddbt;
    uint8_t     vddvco;
} bsp_rf_cb AT(.bss.bsp.tsen.rf);

#endif

#if BSP_TSEN_MAP_DBG_EN
#define tsen_volt_map       dbg_tsen_volt_map.tbl
#define tsen_pll_cfg        dbg_tsen_pll_cfg.tbl
#define tsen_rf_cfg         dbg_tsen_rf_cfg
#else
#define tsen_volt_map       bsp_tsen_volt_map.tbl
#define tsen_pll_cfg        bsp_tsen_pll_cfg.tbl
#define tsen_rf_cfg         bsp_tsen_rf_cfg
#endif

// API: api_xxx.h
void ble_rf_vddvco_set(uint8_t level);
uint8_t ble_rf_vddvco_get(void);
void ble_rf_pll_set(uint32_t val);


static int bsp_tsensor_volt2temp(uint16_t volt)
{
    int temp = -273;
    u8 cursor = 0;

    while (cursor < T_TABLE_SIZE) {
        if (volt < tsen_volt_map[cursor]) {
            break;
        }
        cursor++;
    }

    if (cursor == 0) {
        temp = T_MIN;
    } else if (cursor == T_TABLE_SIZE) {
        temp = T_MIN + T_STEP * (T_TABLE_SIZE - 1);
    } else if ((volt - tsen_volt_map[cursor - 1]) < (tsen_volt_map[cursor] - volt)) {
        temp = T_MIN + (cursor - 1) * T_STEP;
    } else {
        temp = T_MIN + cursor * T_STEP;
    }

    return temp;
}

#if BSP_TSEN_RF_ADJUST_EN

static void bsp_tsensor_pll_level_upd(uint8_t level)
{
    if (level >= sizeof(tsen_pll_cfg)) {
        /* ASSERT: unexpected case */
        TRACE("error - cannot found pll value be level %d\n", level);
        return;
    }

    TRACE("level %d - pll: %d\n", level, tsen_pll_cfg[level]);

    ble_rf_pll_set(tsen_pll_cfg[level]);
}

static void bsp_tsensor_rf_freq_adjust(int temp)
{
    if (bsp_rf_cb.volt_level == 0 && temp >= tsen_rf_cfg.volt_th_up) {
        bsp_rf_cb.volt_level = 1;
        TRACE("level %d - vco&vbt update: %d %d\n", bsp_rf_cb.volt_level, tsen_rf_cfg.volt_level_vco, tsen_rf_cfg.volt_level_bt);
        bsp_rf_cb.vddvco = ble_rf_vddvco_get();
        bsp_rf_cb.vddbt  = pmu_get_vddbt();
        ble_rf_vddvco_set(tsen_rf_cfg.volt_level_vco);
        pmu_set_vddbt(tsen_rf_cfg.volt_level_bt);
    } else if (bsp_rf_cb.volt_level == 1 && temp <= tsen_rf_cfg.volt_th_down) {
        bsp_rf_cb.volt_level = 0;
        TRACE("level %d - vco&vbt update: %d %d\n", bsp_rf_cb.volt_level, bsp_rf_cb.vddvco, bsp_rf_cb.vddbt);
        ble_rf_vddvco_set(bsp_rf_cb.vddvco);
        pmu_set_vddbt(bsp_rf_cb.vddbt);
    }

    if (bsp_rf_cb.pll_level == 0) {
        if (temp >= tsen_rf_cfg.pll_th1_up) {
            bsp_rf_cb.pll_level = 1;
            bsp_tsensor_pll_level_upd(bsp_rf_cb.pll_level);
        } else {
            /* Nothing: the minimum level */
        }
    } else if (bsp_rf_cb.pll_level == 1) {
        if (temp >= tsen_rf_cfg.pll_th2_up) {
            bsp_rf_cb.pll_level = 2;
            bsp_tsensor_pll_level_upd(bsp_rf_cb.pll_level);
        } else if (temp <= tsen_rf_cfg.pll_th1_donw) {
            bsp_rf_cb.pll_level = 0;
            bsp_tsensor_pll_level_upd(bsp_rf_cb.pll_level);
        } else {
            /* Nothing: hysteresis */
        }
    } else if (bsp_rf_cb.pll_level == 2) {
        if (temp <= tsen_rf_cfg.pll_th2_donw) {
            bsp_rf_cb.pll_level = 1;
            bsp_tsensor_pll_level_upd(bsp_rf_cb.pll_level);
        } else {
            /* Nothing: hysteresis */
        }
    } else {
        /* Nothing: unexpected case */
    }
}

#endif

#if BSP_TSEN_MAP_DBG_EN

void bsp_tsensor_rf_cfg_change(uint8_t type, uint8_t idx)
{
    if (type == 0 && idx == bsp_rf_cb.pll_level) {
        bsp_tsensor_pll_level_upd(bsp_rf_cb.pll_level);
    }
    
    if (type == 1 && bsp_rf_cb.volt_level == 1) {
        ble_rf_vddvco_set(tsen_rf_cfg.volt_level_vco);
        pmu_set_vddbt(tsen_rf_cfg.volt_level_bt);
    }
}

#endif

void bsp_tsensor_init(void)
{
    saradc_add_channel(ADC_CHANNEL_TSEN | REFERENCE_VOLTAGE_CHANNEL, SARADC_PULLUP_DIS);
    saradc_kick_start();

    bsp_tsen_cb.cnt  = ADC_AVG_NUM;
    bsp_tsen_cb.intv = ADC_INTV_PROC;
}

void bsp_tsensor_process(void)
{
    u16 tsen_volt;
    int temp;

    do {
        if (!tick_check_expire(bsp_tsen_cb.tick, bsp_tsen_cb.intv)) {
            break;
        }

        bsp_tsen_cb.tick = tick_get();

        bsp_tsen_cb.tsen_adc  += saradc_get_channel_value(ADC_CHANNEL_TSEN);
        bsp_tsen_cb.refer_adc += saradc_get_channel_value(REFERENCE_VOLTAGE_CHANNEL);
        bsp_tsen_cb.cnt--;

        if (bsp_tsen_cb.cnt > 0) {
            bsp_tsen_cb.intv = ADC_INTV_SAMP;
            break;
        }

        tsen_volt = REFERENCE_VOLTAGE_VALUE * bsp_tsen_cb.tsen_adc / bsp_tsen_cb.refer_adc;

        #if BSP_TSEN_MAP_DBG_EN
        TRACE("tsen/refer adc: %d %d\n", bsp_tsen_cb.tsen_adc / ADC_AVG_NUM,
                                         bsp_tsen_cb.refer_adc / ADC_AVG_NUM);
        if (tsen_test_mode) {
            tsen_volt = tsen_test_volt;
        }
        #endif

        TRACE("tsen volt: %d\n", tsen_volt);

        temp = bsp_tsensor_volt2temp(tsen_volt);

        TRACE("temp: %d\n", temp);

        #if BSP_TSEN_RF_ADJUST_EN
        bsp_tsensor_rf_freq_adjust(temp);
        #endif

        #if BSP_TSEN_MAP_DBG_EN
        TRACE("trace end.\n\n");
        #endif

        bsp_tsen_cb.intv        = ADC_INTV_PROC;
        bsp_tsen_cb.cnt         = ADC_AVG_NUM;
        bsp_tsen_cb.tsen_adc    = 0;
        bsp_tsen_cb.refer_adc   = 0;

    } while (0);
}

#endif
