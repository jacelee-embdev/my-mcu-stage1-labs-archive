#ifndef __ADC_H__
#define __ADC_H__

#include "stdint.h"

void adc_init(void);
uint32_t adc_get_result(uint32_t channel);

#endif
