/*
 * File:   ia.h
 * Author: jons
 *
 * Created on 12 October 2014, 16:38
 */

#ifndef IA_H
#define IA_H

#include "hardware/hardware.h"

typedef struct
{
    uint8_t effect_id;
    uint8_t  channel_id;
    uint8_t  is_xy;
    uint8_t  current_state;
    uint8_t  controller_id;
    uint8_t  valid;
} IA;

extern void IA_init();
extern void IA_prepareUpdateStates();
extern void IA_updateState(uint8_t effect_id, uint8_t controller_id, uint8_t bypass_state, uint8_t xy_state);
extern void IA_toggleState(uint8_t channel);
extern uint8_t IA_getControllerForChannel(uint8_t channel);
#endif  /* IA_H */

