#include "hardware/hardware.h"
#include "mcu/mcu.h"
#include "fcb.h"
#include "led/leds.h"
#include "switch/switches.h"
#include "adc/adc.h"
#include "serial/serial.h"
#include "timer/timer.h"
#include "i2c/i2c.h"
#include "eeprom/eeprom.h"
#include "relay/relay.h"
#include "pedal/pedal.h"
#include "midi/sysex.h"

extern void APPLICATION_init();

static void delay()
{
    uint8_t i;

    for (i = 0; i < 255; i++)
    {
    }
}

void FCB_init()
{
    uint8_t i;

    MCU_init();

    delay();
    delay();
    delay();
    delay();

    for (i = 0; i < 6; i++)
    {
        LED_MAP[i] = 0xff;
    }

    WRITE_PERIPHERAL(PERIPHERAL_RESET_COMMONS_AND_SEGMENTS, 0);

    WRITE_PERIPHERAL(PERIPHERAL_RESET_RELAY_KEY_COLUMNS, 0);

    RELAY_init();

    SERIAL_init();

    SYSEX_init();

    TIMER_init();

    I2C_init();

    SWITCH_init();

    PEDAL_init();

    APPLICATION_init();

    EA = 1;
}
