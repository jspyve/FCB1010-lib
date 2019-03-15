#include "hardware/hardware.h"
#include "adc/adc.h"

#define AVG_READINGS 4

static XDATA uint8_t counter = 0;

static XDATA uint16_t avg[2] = {0,0};

static XDATA uint8_t current_results[2] = {0,0};
static XDATA uint8_t last_results[2]    = {0,0};

void PEDAL_init()
{

}

void PEDAL_task()
{
    if ((counter++ & 1) == 0)
    {
        // read first pedal
        avg[0] += ADC_convert(0) >> 1;
    }
    else
    {
        // read second pedal

        avg[1] += ADC_convert(1) >> 1;
    }

    if (counter == (AVG_READINGS << 1))
    {
        current_results[0] = avg[0] / AVG_READINGS;
        current_results[1] = avg[1] / AVG_READINGS;

        counter = 0;
        avg[0] = avg[1] = 0;
    }
}

uint8_t PEDAL_getLatestValues(uint8_t *v1, uint8_t *v2)
{
    uint8_t change_mask = 0;

    if (current_results[0] != last_results[0])
    {
        last_results[0] = current_results[0];

        change_mask |= 1;
    }

    if (current_results[1] != last_results[1])
    {
        last_results[1] = current_results[1];

        change_mask |= 2;
    }

    *v1 = current_results[0];
    *v2 = current_results[1];

    return change_mask;
}

