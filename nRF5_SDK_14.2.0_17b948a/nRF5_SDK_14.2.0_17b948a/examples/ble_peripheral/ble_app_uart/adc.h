
#ifndef _adc_int_h_
#define _adc_int_h_

#include "stdint.h"

void adc_init();
void adc_uninit();
int16_t adc_convert();

#endif