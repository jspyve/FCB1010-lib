/*
 * File:   midi_cmd.h
 * Author: jons
 *
 * Created on 07 October 2014, 21:11
 */

#ifndef MIDI_CMD_H
#define MIDI_CMD_H

#include "serial/serial.h"

static inline void MIDI_programChange(uint8_t program, uint8_t channel)
{
    SERIAL_tx(0b11000000 | (channel & 0x0f));
    SERIAL_tx(program & 0x7f);
}

static inline void MIDI_controlChange(uint8_t controller, uint8_t channel, uint8_t value)
{
    value &= 0x7f;
    controller &= 0x7f;
    channel &= 0x0f;

    SERIAL_tx(0b10110000 | channel);
    SERIAL_tx(controller);
    SERIAL_tx(value);
}

static inline void MIDI_programChange16(uint16_t program, uint8_t channel)
{
    MIDI_controlChange(0, channel, (program >> 7) & 0x7f);
    MIDI_programChange(program & 0x7f, channel);
}

static inline void MIDI_controlChange16(uint8_t controller, uint8_t channel, uint16_t value)
{
    if (controller > 31)
    {
        return;
    }

    value &= 0b0011111111111111;

    SERIAL_tx(0b10110000 | (channel & 0x0f));
    SERIAL_tx((controller | 0x20) & 0x7f);
    SERIAL_tx(value & 0x7f);

    SERIAL_tx(0b10110000 | (channel & 0x0f));
    SERIAL_tx(controller & 0x7f);
    SERIAL_tx(value >> 7);

}

#endif  /* MIDI_CMD_H */

