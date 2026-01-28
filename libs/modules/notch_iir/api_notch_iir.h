#ifndef _API_NOTCH_IIR_H
#define _API_NOTCH_IIR_H

void eq_init(u32 sr, u16 part_len, s32 *data_out_i);
void notch_iir_process(s16* data);

#endif
