#ifndef _BSP_SARADC_TSEN_H
#define _BSP_SARADC_TSEN_H

#define REFERENCE_VOLTAGE_CHANNEL       ADC_CHANNEL_BG
#define REFERENCE_VOLTAGE_VALUE         pmu_get_vbg_mv()

#define T_STEP                          5
#define T_TABLE_SIZE                    33
#define T_MIN                           -30
#define T_MAX                           (T_MIN + TSTEP * (T_TABLE_SIZE - 1))

#define ADC_AVG_NUM                     5
#define ADC_INTV_SAMP                   5
#define ADC_INTV_PROC                   500


typedef struct {
    uint16_t tbl[T_TABLE_SIZE];
} bsp_tsen_volt_map_t;

typedef struct {
    uint32_t tbl[3];
} bsp_rf_pll_cfg_t;

typedef struct {
    uint8_t volt_th_up;
    uint8_t volt_th_down;
    uint8_t volt_level_vco;
    uint8_t volt_level_bt;
    uint8_t pll_th1_up;
    uint8_t pll_th1_donw;
    uint8_t pll_th2_up;
    uint8_t pll_th2_donw;
} bsp_rf_cfg_t;


void bsp_tsensor_init(void);
void bsp_tsensor_process(void);

#endif // _BSP_SARADC_TSEN_H
