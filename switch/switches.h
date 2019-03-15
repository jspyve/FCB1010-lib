#ifndef _SWITCHES_H_
#define _SWITCHES_H_

#include "hardware/hardware.h"

#define CBUFF_BUFFER_SIZE EVENT_BUFFER_SIZE
#include "cbuff/cbuff_type.h"

#define EVENT_NONE 0x00

#define SWITCH_1_CODE       0x00
#define SWITCH_2_CODE       0x01
#define SWITCH_3_CODE       0x02
#define SWITCH_4_CODE       0x03
#define SWITCH_5_CODE       0x04
#define SWITCH_DOWN_CODE    0x05
#define SWITCH_6_CODE       0x06
#define SWITCH_7_CODE       0x07
#define SWITCH_8_CODE       0x08
#define SWITCH_9_CODE       0x09
#define SWITCH_10_CODE      0x0a
#define SWITCH_UP_CODE      0x0b

#define SWITCH_isLongPress(ev) (((ev) & 0x80) != 0)
#define SWITCH_isShortPress(ev) (((ev) & 0x40) != 0)
#define SWITCH_isLongRelease(ev) (((ev) & 0x20) != 0)
#define SWITCH_isShortRelease(ev) (((ev) & 0x10) != 0)
#define SWITCH_isRelease(ev) (((ev) & 0x30) != 0)
#define SWITCH_getCode(ev) ((ev) & 0x0f)
#define SWITCH_isValidEvent(ev) (((ev) & 0xf0) != 0)

extern void SWITCH_init();
extern uint8_t SWITCH_getNextEvent();

extern volatile XDATA CBUFF event_buffer;
#endif
