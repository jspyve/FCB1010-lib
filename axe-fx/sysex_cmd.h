/*
 * File:   sysex_cmd.h
 * Author: jons
 *
 * Created on 07 October 2014, 20:49
 */

#ifndef SYSEX_CMD_H
#define SYSEX_CMD_H

#include "serial/serial.h"

static inline void SYSEX_CMD_requestStates()
{
    // request bypass state, etc
    //
    SERIAL_tx(0xf0);
    SERIAL_tx(0x00);
    SERIAL_tx(0x01);
    SERIAL_tx(0x74);
    SERIAL_tx(0x03);
    SERIAL_tx(0x0e);
    SERIAL_tx(0x08);
    SERIAL_tx(0xf7);
}

static inline void SYSEX_CMD_requestName()
{
    // request preset name
    //
    SERIAL_tx(0xf0);
    SERIAL_tx(0x00);
    SERIAL_tx(0x01);
    SERIAL_tx(0x74);
    SERIAL_tx(0x03);
    SERIAL_tx(0x0f);
    SERIAL_tx(0x09);
    SERIAL_tx(0xf7);
}

static inline void SYSEX_CMD_requestPresetNumber()
{
    SERIAL_tx(0xf0);
    SERIAL_tx(0x00);
    SERIAL_tx(0x01);
    SERIAL_tx(0x74);
    SERIAL_tx(0x03);
    SERIAL_tx(0x14);
    SERIAL_tx(0x12);
    SERIAL_tx(0xf7);
}

#endif  /* SYSEX_CMD_H */

