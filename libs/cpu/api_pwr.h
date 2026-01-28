#ifndef _API_PWR_H_
#define _API_PWR_H_

enum{
    PMU_CFG_BUCK_EN         = BIT(0),
    PMU_CFG_VBAT_5V         = BIT(1),    //VBAT 5V供电
    PMU_CFG_VBAT_3V         = BIT(2),    //VBAT 干电池供电
    PMU_CFG_VBAT_4V2        = BIT(3),    //VBAT 锂电池供电
};

typedef struct {
    u32 piccon;
    u32 picen;
    u32 picpr;
    u32 nmicon;

    u32 clkgat0;
    u32 clkgat1;
    u32 clkgat2;

    u32 pwrcon0;
    u32 pwrcon1;
    u32 pwrcon2;

    u32 xosccon;
    u32 pll0con;
    u32 pll0con1;
    u32 clkcon0;
    u32 clkcon1;
    u32 clkdivcon0;

    u16 rstcon0;
    u32 rtccon;
    u32 rtccon0;
    u32 rtccon12;
    u32 rtccon5;

    u32 protcon0;
    u32 protcon1;
} lowpwr_sfr_backup_t;

/**
  * @brief  pmu initialization
  * @param  pmu_cfg: PMU_CFG_ENUM
  */
void pmu_init(u32 pmu_cfg);

/**
  * @brief  get vddio level, vddio = 1.7V + 0.1V * level
  * @return  level: 0 ~ 0x1F
  */
u8 pmu_get_vddio(void);

/**
  * @brief  get vbg voltage values, uint:mV
  * @return  vbg voltage value, about 600mv
  */
u16 pmu_get_vbg_mv(void);

/**
  * @brief  set vddio level, vddio = 1.7V + 0.1V * level
  * @param  level: 0 ~ 0x1F
  */
void pmu_set_vddio(u8 level);

/**
  * @brief  get vddcore level, vddcore = 0.7 + 0.025 * x
  * @return  level: 0 ~ 0x1F
  */
u8 pmu_get_vddcore(void);

/**
  * @brief  set vddcore level, vddcore = 0.7 + 0.025 * x
  * @param  level: 0 ~ 0x1F
  */
void pmu_set_vddcore(uint8_t level);

/**
  * @brief  get vbat saradc voltage distribution coefficient
  * @return  vbat saradc voltage distribution coefficient, about 2
  */
u16 pmu_get_vbatdet(void);

/**
  * @brief  get lvd level
  * @return  level: 0 ~ 0x7
  */
u8 pmu_get_lvd(void);

/**
  * @brief  set lvd level
    0: 1.7V
    1: 1.8V
    2-7: 2.0V + 0.2V * (level - 2)
  * @param  level: 0 ~ 0x7
  */
void pmu_set_lvd(u8 level);

/**
  * @brief  enable buck mode or disable buck mode
  * @param 1:enable buck mode 0:disable buck mode, pmu work in ldo mode
  */
void pmu_set_buck_mode(u8 buck_en);

/**
  * @brief  set vddbt level
  * @param  level: 0 ~ 0xf, vddbt=0.85 + 0.05*level
  */
void pmu_set_vddbt(uint8_t level);

/**
  * @brief  get vddbt level
  * @return  level: 0 ~ 0xf
  */
uint8_t pmu_get_vddbt(void);


void lowpwr_sleep_sfr_save(lowpwr_sfr_backup_t *sfr_bk);
void lowpwr_sleep_sfr_resume(lowpwr_sfr_backup_t *sfr_bk);
void lp_sleep(void (*sleep_cb)(void), void (*wakeup_cb)(void));

#endif // _API_PWR_H_

