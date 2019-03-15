#include "hardware/hardware.h"
#include "serial.h"

#define CBUFF_BUFFER_SIZE MIDI_BUFFER_SIZE

#include "cbuff/cbuff.h"

static volatile uint8_t XDATA ti_restart = 0;  /* NZ if TI=1 is required */

static volatile XDATA CBUFF rx_buffer;

static volatile XDATA CBUFF tx_buffer;

void SERIAL_isr (void) __interrupt (SI0_VECTOR)
{
    static uint8_t i;

    if (RI == 1)
    {
        RI = 0;

        CB_put(&rx_buffer, SBUF);
    }

    if (TI == 1)
    {
        TI = 0;

        if (!CB_isEmpty(&tx_buffer))
        {
            SBUF = CB_get(&tx_buffer);

            ti_restart = 0;
        }
        else
        {
            ti_restart = 1;
        }
    }
}

uint8_t SERIAL_isIdle()
{
    return CB_isEmpty(&tx_buffer);
}

void SERIAL_tx(uint8_t c) __critical
{
    CB_put(&tx_buffer, c);

    if (ti_restart)
    {
        ti_restart = 0;
        TI = 1;
    }
}

uint8_t SERIAL_hasData() __critical
{
    return !CB_isEmpty(&rx_buffer);
}

uint8_t SERIAL_rx() __critical
{
    while(!SERIAL_hasData())
    {
    }

    return CB_get(&rx_buffer);
}

void SERIAL_init()
{
    CB_init(&rx_buffer);
    CB_init(&tx_buffer);

    SCON = 0b01010010;
    PCON |= 0x80;
    TH1 = 256 - 2;

    TMOD &= ~0x10;
    TMOD |= 0x20;

    ES = 1;
    PS = 1;
    TR1 = 1;

    TI = 0;

    ti_restart = 1;
}

/*void SERIAL_put8Bits(uint8_t b)
{
    uint8_t i;

    for (i = 0; i < 8; i++, b <<= 1)
    {
        if (b & 0x80)
        {
            SERIAL_tx('1');
        }
        else
        {
            SERIAL_tx('0');
        }
    }

    SERIAL_tx('\r');
    SERIAL_tx('\n');
}

static inline void SERIAL_putNibble(uint8_t c)
{
    c &= 0x0f;

    if (c < 0x0a)
    {
        SERIAL_tx(c + '0');
    }
    else
    {
        SERIAL_tx(c - 0x0a + 'a');
    }
}

void SERIAL_putByte(uint8_t c)
{
    SERIAL_putNibble(c >> 4);
    SERIAL_putNibble(c & 0x0f);
}*/

