#include "hardware/hardware.h"
#include "serial/serial.h"
#include "sysex.h"

static uint8_t XDATA sysex_buff[128];
static uint16_t XDATA sysex_index = 0;
static uint8_t XDATA sysex_valid = 0;

void SYSEX_init()
{
    sysex_index = 0;
    sysex_valid = 0;
}

void SYSEX_task()
{
    static uint8_t c;

    while (SERIAL_hasData())
    {
        c = SERIAL_rx();

        if (c == 0xf0)
        {
            sysex_index = 0;

            sysex_valid = 1;

            sysex_buff[sysex_index++] = c;
        }
        else if (c == 0xf7 && sysex_valid)
        {
            sysex_buff[sysex_index++] = c;

            process_sysex(sysex_buff, sysex_index);

            sysex_index = 0;

            sysex_valid = 0;
        }
        else if (c & 0x80)
        {
            sysex_valid = 0;

            sysex_index = 0;
        }
        else if (sysex_valid)
        {
            sysex_buff[sysex_index++] = c;
        }
    }
}
