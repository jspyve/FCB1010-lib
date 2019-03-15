#ifndef __PEDAL_H__
#define __PEDAL_H__

#include "hardware/hardware.h"
#include "adc/adc.h"

void PEDAL_init();
void PEDAL_task();
uint8_t PEDAL_getLatestValues(uint8_t *v1, uint8_t *v2);

#endif // __PEDAL_H__
