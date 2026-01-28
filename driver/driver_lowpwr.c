/*
 * @File name    : driver_lowpwr.c
 * @Author       : Bluetrum IOT Team
 * @Date         : 2023-02-15
 * @Version      : v2.0
 *
 * Copyright (c) by Bluetrum, All Rights Reserved.
 */

#include "driver_lowpwr.h"
#include "driver_saradc.h"

extern u32 __comm_vma;

static lowpwr_sfr_backup_t sfr_backup;


u32 lowpwr_get_wakeup_source(void)
{
    u32 reason = RTCCON9 | RTCCON10;

    if(reason){
        if(reason & WK_LP_KEYSCAN){
            printf("KEY_SCAN_WK\n");
        }

        if(reason & WK_LP_GPIO){
            printf("GPIO_WK\n");
        }

        if(reason & WK_LP_WK0){
            printf("WKO_WK\n");
        }

        if(reason & WK_LP_RTC_1S){
            printf("RTC1S_WK\n");
        }

        if(reason & WK_LP_ALARM){
            printf("ALMWKP_WK\n");
        }

        RTCCON9 = 0x1fff;                                //Clr wakeup pending
        RTCCON10 = 0xffff;
    }

    return (reason & 0x7fff);

}

void lowpwr_wakeup_disable(void)
{
    RTCCON9 = 0x1fff;                           //Clr wakeup pending
    RTCCON10 = 0xffff;
    RTCCON3 &= 0xFF;

    WKUPCPND = 0xff << 16;                      //clear wakeup pending
    WKUPEDG = 0;
    WKUPCON = 0;
    PORTINTEDG = 0;
    PORTINTEN = 0;
}

void lowpwr_clr_wakeup_pending(void)
{
    WKUPCPND = 0xff << 16;                      //clear wakeup pending

    RTCCON9 = 0x1fff;                           //Clr wakeup pending
    RTCCON10 = 0xffff;
}

void lowpwr_wk0_wakeup_config(lowpwr_wakeup_typedef *config)
{
    if (config) {
        WK_EDGE_SEL edge = config->gpio_cfg.edge;
        if (config->lp_type == LP_TYPE_SLEEP) {
            wk0_edge_capture_config(edge);
            WKUPCON |= BIT(17);             //wakeup sleep mode enable
            RTCCON3 |= BIT(17);
        } else if(config->lp_type == LP_TYPE_POWOFF) {
            if (edge == WK_EDGE_FALLING) {
                wko_io_config(1, 0, 1);
                RTCCON1 &= ~BIT(6);         //wk pin low level wakeup
            } else {
                wko_io_config(0, 1, 1);
                RTCCON1 |= BIT(6);          //wk pin high level wakeup
            }
            RTCCON3 |= BIT(10);
        }
    }
}

void lowpwr_gpio_wakeup_config(lowpwr_wakeup_typedef *config)
{
    if (config) {
        if(config->gpio_cfg.gpiox == GPIOB_REG){
            gpio_edge_capture_config(&config->gpio_cfg);

            RTCCON3 |= BIT(17);
            WKUPCON |= BIT(17);                         //wakeup sleep mode enable
            WKUPCPND = 0xff << 16;                      //clear wakeup pending
        }
    }
}

void lowpwr_gpio_wakeup_config_custom(lowpwr_wakeup_typedef *config)
{
    if (config) {
        if(config->gpio_cfg.gpiox == GPIOB_REG){
            gpio_edge_capture_config_custom(&config->gpio_cfg);

            RTCCON3 |= BIT(17);
            WKUPCON |= BIT(17);                         //wakeup sleep mode enable
            WKUPCPND = 0xff << 16;                      //clear wakeup pending
        }
    }
}

void lowpwr_wakeup_config(lowpwr_wakeup_typedef *config)
{
    bool snf_rc_en = false;
    bool pmu_rc_en = false;

    if(config){
        if(config->source & WK_LP_WK0){
            lowpwr_wk0_wakeup_config(config);
        }

        if(config->source & WK_LP_BT){
            RTCCON3 |= BIT(13);
            snf_rc_en = true;
        }

        if(config->source & WK_LP_ALARM){
            RTCCON3 |= BIT(8);
            snf_rc_en = true;
        }

        if(config->source & WK_LP_RTC_1S){
            RTCCON3 |= BIT(9);
            snf_rc_en = true;
        }

        if(config->source & WK_LP_KEYSCAN){
            RTCCON3 |= BIT(16);
            pmu_rc_en = true;
        }

        if(config->source & WK_LP_GPIO){
            lowpwr_gpio_wakeup_config(config);
        }

        if (snf_rc_en) {
            RTCCON0 |= BIT(19);
            RTCCON0 &= ~BIT(0);
            RTCCON1 |= (BIT(12) | BIT(13));
            RTCCON1 &= ~(BIT(14) | BIT(15));
        } else if(pmu_rc_en) {
            RTCCON0 &= ~BIT(19);
            RTCCON0 |= BIT(0);
        } else {
            RTCCON0 &= ~BIT(19);
            RTCCON0 &= ~BIT(0);
        }
    }
}

void lowpwr_wakeup_source_enable(WK_LP_SRC_SEL wk_src)
{
    if(wk_src & WK_LP_WK0){
        RTCCON3 |= BIT(17);
    }

    if(wk_src & WK_LP_BT){
        RTCCON3 |= BIT(13);
    }

    if(wk_src & WK_LP_ALARM){
        RTCCON3 |= BIT(8);
    }

    if(wk_src & WK_LP_RTC_1S){
        RTCCON3 |= BIT(9);
    }


    if(wk_src & WK_LP_KEYSCAN){
        RTCCON3 |= BIT(16);
    }

    if(wk_src & WK_LP_GPIO){
        RTCCON3 |= BIT(17);
    }
}

void lowpwr_wakeup_source_disable(WK_LP_SRC_SEL wk_src)
{
    if (wk_src == WK_LP_SRC_ALL) {
        RTCCON3 &= 0xFF;
        return;
    }

    if(wk_src & WK_LP_WK0){
        RTCCON3 &= ~BIT(17);
    }

    if(wk_src & WK_LP_BT){
        RTCCON3 &= ~BIT(13);
    }

    if(wk_src & WK_LP_ALARM){
        RTCCON3 &= ~BIT(8);
    }

    if(wk_src & WK_LP_RTC_1S){
        RTCCON3 &= ~BIT(9);
    }

    if(wk_src & WK_LP_KEYSCAN){
        RTCCON3 &= ~BIT(16);
    }

    if(wk_src & WK_LP_GPIO){
        RTCCON3 &= ~BIT(17);
    }
}

AT(.com_pwroff.mode1)
void lowpwr_pwroff_mode1_do(void)
{
    u32 rtccon3;

    saradc_deinit();

    PICCONCLR = BIT(0);     //disable global interrupt

    RTCCON9 = 0x1fff;       //Clr wakeup pending

    RTCCON0 &= ~(BIT(0) | BIT(19));   //RC2M_RTC disable, PMU RC2M disable

    RTCCON4 &= ~(BIT(17) | BIT(18) | BIT(15));    //FGS,FGBUF,VIO_PD

    RTCCON1 &= ~BIT(9);  //hwchg_vrtc11_en

    RTCCON4 = (RTCCON4 & ~(0x3f<<24)) | (3<<24) | (6<<27);  //no sfr access, bit26~bit24, VRTC11 is 1.025V; sfr access, bit29~27, VRTC11 is 1.09V

    CLKCON0 |= BIT(0);      //RC2M enable
    CLKCON0 &= ~0xc;        //sys_clk switch to RC
    asm("nop");
    asm("nop");
    asm("nop");

    XOSCCON = 0;
    PLL0CON = 0;

    rtccon3 = RTCCON3 & ~(0xFF);
    rtccon3 |= BIT(4) | BIT(6);      //core power down enable

    WDT_DIS();

    RTCCON |= BIT(5);       //RTC wake up power down mode reset system enable

    RTCCON3 = rtccon3;

    LPMCON |= BIT(0) | BIT(1);	    //sleep mode, idle mode

    asm("nop");asm("nop");asm("nop");

    while(1);
}


AT(.com_pwroff.mode2)
void pwroff_mode2_final(void)
{
    u32 rtccon3;

	RTCCON3 |= BIT(7);     //enable vddio aon ldo

	rtccon3 = RTCCON3;

	//select sniff rc clock and disable pll,xosc
    CLKCON0  = (CLKCON0 & ~(3<<2)) | (3<<2); // sel rc24m
    asm("nop");
    asm("nop");
    asm("nop");

    //PLL, XOSC, CLK2M_BT off
    PLL0CON  = 0;
    PLL0CON1 = 0;
    XOSCCON = 0;

    // 1. disable clock
    CLKGAT0 &= ~(BIT(15) | BIT(2)); //lp clk, sram0/ disable clock

    // 2. disable interface
    //    disable if, then deep sleep memory, can not do in 1 cycle
    RTCCON5 &= ~(1<<11);    // dis sram if

    RTCCON5 |= BIT(15);    //sram0 shut down

    RTCCON5 |= BIT(0);      //ldo mode

    // pmu power down ...
    rtccon3 &= ~(1<<5);     // VDDCORE and VLCORE
    rtccon3 |= ((1<<3) | (1<<4));      // VLCORE LDO enable, RI_PD_CORE2 from rtc
    rtccon3 &= ~(0x7<<0);   // VDDBT/VDDIO/VDDCORE LDO disable

    WDT_DIS();

    RTCCON |= BIT(5);       //RTC wake up power down mode reset system enable

    RTCCON3 = rtccon3;

    RTCRAMADR = 0x00;

    //LPMCON |= BIT(0);
    LPMCON |= BIT(1);       //idle mode
    asm("nop");
    asm("nop");
    asm("nop");
    while(1);
}

AT(.com_pwroff.mode2)
void lowpwr_pwroff_mode2_do(void)
{
    u8 *src, *dst;
    u32 i;
    void (*p_func)(void);

    u32 rtccon0;

    p_func = (void (*)(void))CACHE_ADDR;

    saradc_deinit();

    PICCONCLR = BIT(0);     //disable global interrupt

    RTCCON9 = 0x1fff;       //Clr wakeup pending

    RTCCON4 &= ~(BIT(17) | BIT(18) | BIT(15));    //FGS, FGBUF

    rtccon0 = RTCCON0;

    RTCCON1 &= ~BIT(9);     //hwchg_vrtc11_en
    RTCCON4 = (RTCCON4 & ~(0x3f<<24)) | (3<<24) | (6<<27);  //no sfr access, bit26~bit24, VRTC11 is 1.025V; sfr access, bit29~27, VRTC11 is 1.09V

    if ((RTCCON3 & BIT(16)) && (RTCCON0 & BIT(19))) {
        rtccon0 = (rtccon0 & ~(0x03 << 14)) | (0x02 << 14); //CLK2M in Keyscan select RC2M_RTC
    } else if ((RTCCON3 & BIT(16)) && (RTCCON0 & BIT(0))) {
        rtccon0 = (rtccon0 & ~(0x03 << 14)) | (0x01 << 14); //CLK2M in Keyscan select SNF_RC_RTC
    }


    RTCCON0 = rtccon0;

    PWRCON1 &= ~(0xf<<14);  //disable flash power gate

    GPIOGDE = 0;
    GPIOGPU = 0;

    RTCCON5 &= ~BIT(12);    //io interface disable

    RTCCON5 |= BIT(18);     //reset lp_top

    //copy pwroff_mode2_final() to cache ram

    dst = (u8*) CACHE_ADDR;
    src = (u8*) (&pwroff_mode2_final);
    for(i = 0; i < 0x300; i++){
        *dst++ = *src++;
    }

    //jmp to run pwroff_mode2_final()
    p_func();
}


AT(.com_sleep.sfr_save)
WEAK void lowpwr_sleep_sfr_user_save(void)
{

}

AT(.com_sleep.sfr_resume)
WEAK void lowpwr_sleep_sfr_user_resume(void)
{

}

AT(.com_sleep.sys)
void lp_sleep_do(void)
{
    u32 rtccon3;

	RTCCON3 |= BIT(7);     //enable vddio aon ldo

	rtccon3 = RTCCON3;

	//select sniff rc clock and disable pll,xosc
    CLKCON0  = (CLKCON0 & ~(3<<2)) | (3<<2); // sel rc24m
    asm("nop");
    asm("nop");
    asm("nop");

    //PLL, XOSC, CLK2M_BT off
    PLL0CON  = 0;
    PLL0CON1 = 0;
    XOSCCON = 0;

    // 1. disable clock
    CLKGAT0 &= ~(BIT(15) | BIT(2)); //lp clk, sram0/ disable clock

    // 2. disable interface
    //    disable if, then deep sleep memory, can not do in 1 cycle
    RTCCON5 &= ~(1<<11);    // dis sram if

    RTCCON5 |= BIT(0);

    WDT_DIS();

    // pmu power down ...
    rtccon3 &= ~(1<<5);     // VDDCORE and VLCORE
    rtccon3 |= ((1<<3) | (1<<4));      // VLCORE LDO enable, RI_PD_CORE2 from rtc
    rtccon3 &= ~(0x7<<0);   // VDDBT/VDDIO/VDDCORE LDO disable

    RTCCON |= BIT(5);       //RTC wake up power down mode reset system enable

    RTCCON3 = rtccon3;

    RTCRAMADR = 0x00;

    //LPMCON |= BIT(0);
    LPMCON |= BIT(1);       //idle mode
    asm("nop");
    asm("nop");
    asm("nop");
    while(1);
}

AT(.com_sleep.lp_proc)
void lp_sleep_proc(void)
{
    u32 rtccon0 = RTCCON0;
    u32 *dst = (u32 *)0x70000;
    u32 *src = (u32 *)&lp_sleep_do;

    for(uint i=0; i<512/4; i++) {
        *dst++ = *src++;
    }

    RTCCON9 = 0x1fff;           //Clr wakeup pending

    // 2, analog disable
    RTCCON4 &= ~(BIT(17) | BIT(18) | BIT(15));    //FGS,FGBUF

    RTCCON4 = (RTCCON4 & ~(0x3f<<24)) | (3<<24) | (6<<27);                  //no sfr access, bit26~bit24, VRTC11 is 0.83V; sfr access, bit29~27, VRTC11 is 1.1V

    if ((RTCCON3 & BIT(16)) && (RTCCON0 & BIT(19))) {
        rtccon0 = (rtccon0 & ~(0x03 << 14)) | (0x02 << 14); //CLK2M in Keyscan select RC2M_RTC
    } else if ((RTCCON3 & BIT(16)) && (RTCCON0 & BIT(0))) {
        rtccon0 = (rtccon0 & ~(0x03 << 14)) | (0x01 << 14); //CLK2M in Keyscan select SNF_RC_RTC
    }


    RTCCON0 = rtccon0;

    RTCCON0 |= BIT(24);     //system reset time select:32 * rc32K clk

    RTCCON5 &= ~BIT(12);    //io interface disable

    RTCCON5 |= (1<<17);     // set lp_flag

    asm("j 0x70000");
};

AT(.com_sleep.lp_wakeup)
void lp_wakeup_proc(void)
{
    LVDCON &= ~BIT(30);                     //Enable reset pending

    RTCCON4 &= ~BIT(6);                     //VDDBT to VCORE dis

    RTCCON4 |= BIT(5) ;                     //VCORE from VDDIO

    PICADR = (u32)&__comm_vma;

    if(!(sfr_backup.rtccon5 & BIT(0))){
        PWRCON1 = (PWRCON1 & ~(0X3<<2)) | (0X1<<2);       // DI_CLIMIT_S   109:85:366mA
        RTCCON5 &= ~BIT(0);
    }

    PWRCON0 |= BIT(20);                     //pmu normal

    RTCCON5 |= (1<<12);                     //select system port config

    PWRCON1 |= BIT(8);

    // 2, analog init
    RTCCON3 |= BIT(0);                                          //VDDDBT
    PWRCON0 = (PWRCON0 & ~0x1f) | pmu_get_vddcore();            //VDDCORE is 1.15V
    asm("nop");

    PLL0CON |= BIT(12);                         //DI_EN_LDO

    // 3, PLL,XOSC,CLK2M_BT, on
    XOSCCON = sfr_backup.xosccon;

    delay(380);                                 //delay 2ms - 3ms for xosc to work

    PWRCON1 &= ~BIT(8);

    PLL0CON  = sfr_backup.pll0con;
    PLL0CON1 = sfr_backup.pll0con1;

    CLKDIVCON0 = sfr_backup.clkdivcon0;

    // 4, resume CLK
    CLKCON1 = sfr_backup.clkcon1;               //xosc_mux_clk select xosc24m
    asm("nop");
    asm("nop");
    asm("nop");

    CLKCON0 = sfr_backup.clkcon0;               //sysclk select xosc_mux_clk
    asm("nop");
    asm("nop");

    if (CLKGAT0 & BIT(13)) {
        MICAUDCON0 = (uint32_t)(1 << 6);        // MICLDO bypass AVDD enable
    } else {
        CLKGAT0 |= BIT(13);                     // Enable sdadcl_clken
        delay_us(10);
        MICAUDCON0 = (uint32_t)(1 << 6);        // MICLDO bypass AVDD enable
        CLKGAT0 &= ~BIT(13);                    // Disable sdadcl_clken
    }

}

AT(.com_sleep.proc_do)
WEAK void lowpwr_sleep_proc_do(void)
{
    lowpwr_sleep_sfr_save(&sfr_backup);
    lowpwr_sleep_sfr_user_save();

    u32 gpiogde = GPIOGDE;
    u32 gpiogpu = GPIOGPU;

    GPIOGDE = 0;
    GPIOGPU = 0;
    PWRCON1 &= ~(0XF<<14);                          //DI_SW DISABLE

    lp_sleep(lp_sleep_proc, lp_wakeup_proc);

    RTCCON4 |= BIT(5) | BIT(6);                     //VCORE from VDDBT & VDDIO

    lowpwr_sleep_sfr_resume(&sfr_backup);

    lowpwr_sleep_sfr_user_resume();

    GPIOGDE = gpiogde;
    GPIOGPU = gpiogpu;

    if(sfr_backup.rtccon5 & BIT(0)){
        RTCCON4 &= ~BIT(6);                         //LDO Mode,VCORE disable VDDBT, from VDDIO
    }else{
        RTCCON4 &= ~BIT(5);                         //Buck Mode,VCORE disable VDDIO, from VDDBT
    }

    PWRCON1 &= ~BIT(7);


}

AT(.com_sleep.sleep)
void lowpwr_sleep_proc(void)
{
    lowpwr_sleep_proc_do();
}

