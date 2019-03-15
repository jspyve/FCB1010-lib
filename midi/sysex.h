#ifndef __MIDI_SYSEX_H__
#define __MIDI_SYSEX_H__

#include "hardware/hardware.h"
#include "serial/serial.h"

extern void process_sysex(uint8_t *buffer, uint8_t length);

void SYSEX_init();
void SYSEX_task();

#endif
