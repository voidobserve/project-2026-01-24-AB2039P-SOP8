#ifndef _API_CODEC_H
#define _API_CODEC_H


/* 采样点数 -> PCM16字节数 */
#define SAMPLE_2_PCM16_BYTE(x)              (x*2)
/* PCM16字节数 -> 采样点数 */
#define PCM16_BYTE_2_SAMPLE(x)              (x/2)
/* 采样点数 -> ADPCM块字节数 */
#define SAMPLE_2_ADPCM_BYTE(x)              ((x-1)/2+4)
/* ADPCM块字节数 -> 采样点数 */
#define ADPCM_BYTE_2_SAMPLE(x)              (((x-4)*2)+1)
/* ADPCM块字节数 -> PCM16字节数 */
#define ADPCM_BYTE_2_PCM16_BYTE(x)          (((x-4)*4)+2)


//sbc
/* sampling frequency */
enum {
    SBC_FREQ_16000 = 0x00,
    SBC_FREQ_32000 = 0x01,
    SBC_FREQ_44100 = 0x02,
    SBC_FREQ_48000 = 0x03,
};

/* blocks */
enum {
    SBC_BLK_4  = 0x00,
    SBC_BLK_8  = 0x01,
    SBC_BLK_12 = 0x02,
    SBC_BLK_16 = 0x03,
};

/* subbands */
enum {
    SBC_SB_4 = 0x00,
    SBC_SB_8 = 0x01,
};

/* channel mode */
enum {
    SBC_MODE_MONO         = 0x00,
    SBC_MODE_DUAL_CHANNEL = 0x01,
    SBC_MODE_STEREO       = 0x02,
    SBC_MODE_JOINT_STEREO = 0x03,
};

/* allocation method */
enum {
    SBC_AM_LOUDNESS = 0x00,
    SBC_AM_SNR      = 0x01,
};
/**
  * @brief  SBC encode
  *  @brief  Take the mono 16K sampling rate as an example
  * @brief  mSBC parameter cannot be changed, ilen = 120 * 2, olen = 57;
  *
  * @brief  subbands_l = subbands ? 8 : 4;
  * @brief  blocks_l = 4 + (blocks * 4);
  * @brief  channels_l = mode ? 2 : 1;
  * @brief  SBC ilen = subbands_l * blocks_l * channels_l * 2;
  * @brief  SBC olen = 4 + (4 * subbands_l * channels_l) / 8  +  ((blocks_l * channels_l * bitpool) + 7) / 8;  //Ignore the decimal point
  *
  * @brief  mic sample points = ilen / 2;
  */
void sbc_encode_init(uint8_t freq, uint8_t blocks, uint8_t subbands, uint8_t mode, uint8_t allocation, uint8_t bitpool);
uint16_t sbc_encode_frame(uint8_t *ibuf, uint16_t ilen, uint8_t *obuf, uint16_t olen);
void msbc_encode_init(void);
uint16_t msbc_encode_frame(uint8_t *ibuf, uint16_t ilen, uint8_t *obuf, uint16_t olen);

/**
 * @brief  SBC decode
 * 
 * @brief  is_msbc:  1 -- msbc, 0 -- sbc.
 * @brief  ibuf: SBC encoded buf
 * @brief  ilen: SBC encoded buf len
 * @brief  obuf: SBC decoded output buf
 * 
 * @brief  return: decode output buf sample points. (max: 128)
 */
void sbc_decode_init(bool is_msbc);
uint16_t sbc_decode_frame(uint8_t *ibuf, uint16_t ilen, uint8_t *obuf);

//adpcm
/**
  * @brief  adpcm encode compression ratio 4:1
  * @brief  encode output buf format:2byte prediction sample, 1byte index, 1byte reserve, nbyte data
  * @brief  decode input buf format:2byte prediction sample, 1byte index, 1byte reserve, nbyte data
  * @param  p_dst: output buf
  * @param  p_src: input buf
  * @param  sample_len:sample points
  */
void adpcm_decode_block(uint8_t *p_dst,uint8_t *p_src,uint32_t sample_len);
void adpcm_encode_block(uint8_t *p_dst, uint8_t *p_src, uint32_t sample_len);
void adpcm_decode_block_big(uint8_t *p_dst, uint8_t *p_src, uint32_t sample_len);
void adpcm_encode_block_big(uint8_t *p_dst, uint8_t *p_src, uint32_t sample_len);
void adpcm_sample_idx_set(int16_t idx);
void adpcm_sample_idx_reset(void);
void adpcm_presample_set(int32_t pcm_16);
uint16_t adpcm_sample_idx_get(void);
int16_t adpcm_presample_get(void);



#endif // _API_CODEC_H
