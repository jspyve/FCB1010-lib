#include "hardware/hardware.h"
#include "switches.h"
#include "relay/relay.h"
#include "cbuff/cbuff.h"

volatile XDATA CBUFF event_buffer;

void SWITCH_init()
{
    CB_init(&event_buffer);
}

uint8_t SWITCH_getNextEvent()
{
    static uint8_t event;

    if (CB_isEmpty(&event_buffer))
    {
        return EVENT_NONE;
    }
    else
    {
        event = CB_get(&event_buffer);

        return event;
    }
}
