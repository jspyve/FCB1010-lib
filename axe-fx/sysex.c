#include "hardware/hardware.h"
#include "midi/sysex.h"
#include "sysex.h"
#include "sysex_cmd.h"
#include "ia.h"
#include "led/leds.h"

static inline uint8_t is_valid_checksum(uint8_t *buffer, uint16_t length)
{
    uint8_t c;

    if (length < 3)
    {
        // smallest packet length would be 0xf0, checksum, 0xf7, ie. no data payload
        //
        return 0;
    }

    c = *buffer++;

    while(--length > 1)
    {
        c ^= *buffer++;
    }

    c &= 0x7f;

    return (c == 0) && (*buffer == 0xf7);
}

static inline uint8_t is_axefx_message(uint8_t *buffer, uint16_t length)
{
    if (length < 6)
    {
        return 0;
    }
    else
    {
        return (buffer[0] == 0xf0)
            && (buffer[1] == 0x00)
            && (buffer[2] == 0x01)
            && (buffer[3] == 0x74)
            && (buffer[4] == 0x03);
    }
}

void process_sysex(uint8_t *buffer, uint16_t length)
{
    uint16_t i;

    if (!is_axefx_message(buffer, length))
    {
        return;
    }

    switch(buffer[5])
    {
        case 0x10:
            // tempo
            break;

        case 0x0d:
            // tuner packet, no checksum
            //
            if (buffer[8] == 63)
            {
                Nop();
            }
            else if (buffer[8] < 8)
            {
                Nop();
            }
            else if (buffer[8] < 16)
            {
                Nop();
            }
            else if (buffer[8] < 32)
            {
                Nop();
            }
            break;

        case 0x14:
            if (is_valid_checksum(buffer, length))
            {
                i = (((buffer[6] & 0x7f) << 7) | (buffer[7] & 0x7f)) + 1;

                LED_displayNumber(i);

                SYSEX_CMD_requestStates();
            }
            break;

        case 0x0e:
            //if (is_valid_checksum(buffer, length))
            {
                IA_prepareUpdateStates();

                for (i = 6; i < length - 2; i+=5)
                {
                    IA_updateState(
                      ((buffer[i+3] >> 3) & 0b1111) | ((buffer[i+4] & 0b1111) << 4),
                      ((buffer[i+1] >> 1) & 0b00111111) | ((buffer[i+2] & 0b11) << 6),
                      (buffer[i] & 0x01) ? 0 : 1,
                      (buffer[i] & 0x02) ? 0 : 1);
                }
            }
            break;

        case 0x21:
            if (is_valid_checksum(buffer, length))
            {
                SYSEX_CMD_requestStates();
            }
            break;
    }
}

