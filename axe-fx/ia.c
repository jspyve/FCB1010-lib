#include "hardware/hardware.h"
#include "ia.h"
#include "midi/midi_cmd.h"
#include "led/leds.h"

#define IA_COUNT 7

static XDATA IA instant_access[IA_COUNT] =
{
    {100, 6, 0, 0, 0, 0},
    {133, 7, 0, 0, 0, 0},
    {116, 8, 0, 0, 0, 0},
    {122, 9, 0, 0, 0, 0},
    {112, 10, 0, 0, 0, 0},
    {124, 11, 0, 0, 0, 0},
    {120, 12, 0, 0, 0, 0},
};

void IA_init()
{
}

static inline void IA_updateLED(uint8_t channel_id, uint8_t state)
{
    switch(channel_id)
    {
        case 6:
            LED_SET(LED_6, state);
            break;

        case 7:
            LED_SET(LED_7, state);
            break;

        case 8:
            LED_SET(LED_8, state);
            break;

        case 9:
            LED_SET(LED_9, state);
            break;

        case 10:
            LED_SET(LED_10, state);
            break;

        case 11:
            LED_SET(LED_EXP_1, state);
            break;

        case 12:
            LED_SET(LED_EXP_2, state);
            break;

        default:
            break;
    }
}

void IA_toggleState(uint8_t channel_id)
{
    uint8_t i;

    for (i = 0; i < IA_COUNT; i++)
    {
        if (instant_access[i].channel_id == channel_id)
        {
            if (instant_access[i].valid)
            {
                instant_access[i].current_state = !instant_access[i].current_state;

                MIDI_controlChange(instant_access[i].controller_id, 0, instant_access[i].current_state ? 127 : 0);

                IA_updateLED(instant_access[i].channel_id, instant_access[i].current_state);
            }
            break;
        }
    }
}

void IA_prepareUpdateStates()
{
    uint8_t i;

    for (i = 0; i < IA_COUNT; i++)
    {
        instant_access[i].valid = 0;
    }

    LED_OFF(LED_6);
    LED_OFF(LED_7);
    LED_OFF(LED_8);
    LED_OFF(LED_9);
    LED_OFF(LED_10);
}

void IA_updateState(uint8_t effect_id, uint8_t controller_id, uint8_t bypass_state, uint8_t xy_state)
{
    uint8_t i;

    for (i = 0; i < IA_COUNT; i++)
    {
        if (instant_access[i].effect_id == effect_id)
        {
            instant_access[i].valid = 1;

            instant_access[i].controller_id = controller_id;

            if (instant_access[i].is_xy)
            {
                instant_access[i].current_state = xy_state;
            }
            else
            {
                instant_access[i].current_state = !bypass_state;
            }

            IA_updateLED(instant_access[i].channel_id, instant_access[i].current_state);
        }
    }
}

uint8_t IA_getControllerForChannel(uint8_t channel_id)
{
    uint8_t i;

    for (i = 0; i < IA_COUNT; i++)
    {
        if (instant_access[i].valid && instant_access[i].channel_id == channel_id)
        {
            return instant_access[i].controller_id;
        }
    }

    return 0;
}
