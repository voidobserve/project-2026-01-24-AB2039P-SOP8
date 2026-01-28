#ifndef __VOICE_SDADC_H
#define __VOICE_SDADC_H

#if (FUNC_TBOX_EN && PROD_TEST_MIC_EN)

#include "api_ring_buf.h"

extern ring_buf_t saradc_enc_ring_buf;

void tbox_voice_saradc_init(void);
void tbox_voice_saradc_start(void);
void tbox_voice_saradc_stop(void);
#endif  //(FUNC_TBOX_EN && PROD_TEST_MIC_EN)
#endif  //__VOICE_SDADC_H
