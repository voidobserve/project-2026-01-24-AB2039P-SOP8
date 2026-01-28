#include "include.h"
#include "notch_iir.h"

#ifndef NOTCH_IIR_PART_LEN1
#define NOTCH_IIR_PART_LEN1			   128           //128个样点处理一次
#endif


static s32 data_out_i[NOTCH_IIR_PART_LEN1] AT(.notch_iir.buf);

AT(.text.notch_iir.init)
void notch_iir_init(u32 sr)
{
	eq_init(sr, NOTCH_IIR_PART_LEN1, data_out_i);
}

