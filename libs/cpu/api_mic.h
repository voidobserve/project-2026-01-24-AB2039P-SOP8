#ifndef _API_MIC_H
#define _API_MIC_H

/**
 * @brief AUDIO MIC DMA flag enumeration
 */
typedef enum{
    AUDIO_MIC_ALL_DONE,
    AUDIO_MIC_HALF_DONE,
}AUDIO_MIC_DONE_TYPEDEF;

/**
 * @brief AUDIO MIC res cap enumeration
 */
typedef enum {
    AUDIO_MIC_NOT_RC   = 0,  //省电阻电容
    AUDIO_MIC_NOT_R,         //省电阻不省电容
    AUDIO_MIC_NORMAL,        //不省电阻电容
} AUDIO_MIC_TYPE_TYPEDEF;

/**
 * @brief AUDIO MIC bias enumeration
 */
typedef enum {
    AUDIO_MIC_VDD_1V6             = 0x0,    //1.6V
    AUDIO_MIC_VDD_1V7             = 0x1,
    AUDIO_MIC_VDD_1V8             = 0x2,
    AUDIO_MIC_VDD_1V9             = 0x3,
    AUDIO_MIC_VDD_2V0             = 0x4,
    AUDIO_MIC_VDD_2V1             = 0x5,
    AUDIO_MIC_VDD_2V2             = 0x6,
    AUDIO_MIC_VDD_2V3             = 0x7,
    AUDIO_MIC_VDD_2V4             = 0x8,
    AUDIO_MIC_VDD_2V5             = 0x9,
    AUDIO_MIC_VDD_2V6             = 0xa,
    AUDIO_MIC_VDD_2V7             = 0xb,
    AUDIO_MIC_VDD_2V8             = 0xc,
    AUDIO_MIC_VDD_2V9             = 0xd,
    AUDIO_MIC_VDD_3V0             = 0xe,
    AUDIO_MIC_VDD_3V1             = 0xf,

    AUDIO_MIC_VDD_NONE            = 0xff,   //close mic bias
} AUDIO_MIC_VDD_TYPEDEF;

/**
 * @brief AUDIO MIC bias res enumeration
 */
typedef enum {
    AUDIO_MIC_BIAS_RES_16K          = 0x1,
    AUDIO_MIC_BIAS_RES_8K           = 0x2,
    AUDIO_MIC_BIAS_RES_4K           = 0x4,
    AUDIO_MIC_BIAS_RES_2K           = 0x8,
    AUDIO_MIC_BIAS_RES_1K           = 0xf,
} AUDIO_MIC_BIAS_RES_TYPEDEF;

/**
 * @brief AUDIO MIC analog gain enumeration
 */
typedef enum {
    AUDIO_MIC_ANA_GAIN_0           = 0x0,
    AUDIO_MIC_ANA_GAIN_1           = 0x1,
    AUDIO_MIC_ANA_GAIN_2           = 0x2,
    AUDIO_MIC_ANA_GAIN_3           = 0x3,
    AUDIO_MIC_ANA_GAIN_4           = 0x4,
    AUDIO_MIC_ANA_GAIN_5           = 0x5,
    AUDIO_MIC_ANA_GAIN_6           = 0x6,
    AUDIO_MIC_ANA_GAIN_7           = 0x7,
} AUDIO_MIC_ANA_GAIN_TYPEDEF;

/**
 * @brief AUDIO MIC trim status enumeration
 */
typedef enum {
    AUDIO_MIC_TRIM_STA_INIT       = 0,
    
    AUDIO_MIC_TRIM_STA_DBG,

    AUDIO_MIC_TRIM_STA_MICBIAS_STEP0_INIT,
    AUDIO_MIC_TRIM_STA_MICBIAS_STEP0_WAITING,
    AUDIO_MIC_TRIM_STA_MICBIAS_STEP0_RUN,
    AUDIO_MIC_TRIM_STA_MICBIAS_STEP1_INIT,
    AUDIO_MIC_TRIM_STA_MICBIAS_STEP1_WAITING,
    AUDIO_MIC_TRIM_STA_MICBIAS_STEP1_RUN,
    AUDIO_MIC_TRIM_STA_MICBIAS_STEP2_RUN,

    AUDIO_MIC_TRIM_STA_MICDC_STEP0_INIT,
    AUDIO_MIC_TRIM_STA_MICDC_STEP0_WAITING,
    AUDIO_MIC_TRIM_STA_MICDC_STEP0_RUN,
    AUDIO_MIC_TRIM_STA_MICDC_STEP1_INIT,
    AUDIO_MIC_TRIM_STA_MICDC_STEP1_WAITING,
    AUDIO_MIC_TRIM_STA_MICDC_STEP1_RUN,
    AUDIO_MIC_TRIM_STA_MICDC_STEP2_INIT,
    AUDIO_MIC_TRIM_STA_MICDC_STEP2_WAITING,
    AUDIO_MIC_TRIM_STA_MICDC_STEP2_RUN,
  
    AUDIO_MIC_TRIM_FINISH,
} AUDIO_MIC_TRIM_STA_TYPEDEF;

void audio_mic_dc_filter_init(void);
void audio_mic_dc_filter(int16_t *pcmIn);
void audio_mic_analog_init(AUDIO_MIC_TYPE_TYPEDEF mic_type, AUDIO_MIC_VDD_TYPEDEF mic_vdd, \
                    AUDIO_MIC_BIAS_RES_TYPEDEF mic_bias_res, AUDIO_MIC_ANA_GAIN_TYPEDEF mic_again, uint16_t micin_trim);
uint8_t audio_mic_trim_proc(void);    
bool audio_mic_trim_is_finish(void);                
#endif //_API_MIC_H
