#include "hardware/hardware.h"
#include "adc.h"

#define NADC_CS P1_0
#define CLOCK   P3_4
#define DI      P1_2
#define DO      P1_1

static inline void init_delay()
{
    Nop();
    Nop();
    Nop();
    Nop();
}

static inline void bit_delay()
{
    Nop();
    Nop();
}

static inline void cs_delay()
{
    Nop();
    Nop();
    Nop();
    Nop();
}

uint8_t ADC_convert(uint8_t channel)
{
    uint8_t result = 0, i;

    NADC_CS = 1;
    CLOCK   = 0;
    DI      = 1;

    init_delay();

    NADC_CS = 0;

    cs_delay();

    // start bit
    //
    DI = 1;
    CLOCK = 1;
    bit_delay();
    CLOCK = 0;
    bit_delay();

    // diff bit
    //
    DI = 1;
    CLOCK = 1;
    bit_delay();
    CLOCK = 0;
    bit_delay();

    // channel bit
    //
    DI = (channel == 0) ? 0 : 1;
    CLOCK = 1;
    bit_delay();
    CLOCK = 0;
    bit_delay();

    // 9 bits, LSB first, 1st bit is dummy
    // and will be shifted away
    //
    for (i = 0; i < 9; i++)
    {
        result <<= 1;

        CLOCK = 1;
        bit_delay();
        result |= (DO == 1) ? 1 : 0;
        CLOCK = 0;
        bit_delay();
    }

    cs_delay();

    NADC_CS = 1;

    return result;
}
