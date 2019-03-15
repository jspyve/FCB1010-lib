#ifndef __HARDWARE_H_
#define __HARDWARE_H_

#include "8051.h"
#include "types/types.h"

#define XDATA __xdata
#define IDATA __idata

#define Nop() __asm__("NOP")

#define UNREFERENCED(x) x = x

// LEDs can be muxed as fast as possible
// switches take 6 * 8 ticks to debounce, and you
// don't want a debounce to take more than 100ms really
//
#define T0_COUNT (0x10000 - 0x7d0)

#define EVENT_BUFFER_SIZE 16
#define MIDI_BUFFER_SIZE  254

#define HW_BASE 0x1ff8

#define PERIPHERAL_LATCH_COMMONS              0
#define PERIPHERAL_LATCH_SEGMENTS             1
#define PERIPHERAL_DUMMY_MUX                  2
#define PERIPHERAL_LATCH_RELAY_KEY_COLUMNS    5
#define PERIPHERAL_RESET_COMMONS_AND_SEGMENTS 6
#define PERIPHERAL_RESET_RELAY_KEY_COLUMNS    7

extern volatile XDATA __at (HW_BASE) uint8_t PERIPHERALS[];

#define WRITE_PERIPHERAL(p, v) {PERIPHERALS[PERIPHERAL_DUMMY_MUX] = 0; PERIPHERALS[p] = (v); PERIPHERALS[PERIPHERAL_DUMMY_MUX] = 0;}

#define SDA P3_5
#define SCL P3_4

#endif

