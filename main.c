#include "hardware/hardware.h"
#include "isr/isr.h"
#include "fcb/fcb.h"
#include "led/leds.h"
#include "switch/switches.h"
#include "adc/adc.h"
#include "serial/serial.h"
#include "i2c/i2c.h"
#include "eeprom/eeprom.h"
#include "relay/relay.h"
#include "midi/midi_cmd.h"
#include "midi/sysex.h"
#include "axe-fx/sysex.h"
#include "axe-fx/ia.h"
#include "axe-fx/axe-fx.h"
#include "pedal/pedal.h"

#define MIDI_CHANNEL 0


static uint16_t XDATA bank = 0;

static uint16_t XDATA bank_size;
static uint16_t XDATA num_banks;

void APPLICATION_init()
{
    bank_size = 5;
    num_banks = ((NUM_PROGRAMS % bank_size) == 0) ? (NUM_PROGRAMS / bank_size) : ((NUM_PROGRAMS + bank_size) / bank_size);

    IA_init();

    //LED_FLASH(LED_MIDI_FUNC);
    //LED_FLASH_QUICK(LED_MIDI_CHAN);
}

static void AXE_programChange(uint8_t channel, uint16_t program)
{
    LED_OFF(LED_1);
    LED_OFF(LED_2);
    LED_OFF(LED_3);
    LED_OFF(LED_4);
    LED_OFF(LED_5);
    LED_OFF(LED_6);
    LED_OFF(LED_7);
    LED_OFF(LED_8);
    LED_OFF(LED_9);
    LED_OFF(LED_10);

    switch(program % bank_size)
    {
        case 0:
            LED_ON(LED_1);
            break;

        case 1:
            LED_ON(LED_2);
            break;

        case 2:
            LED_ON(LED_3);
            break;

        case 3:
            LED_ON(LED_4);
            break;

        case 4:
            LED_ON(LED_5);
            break;

        case 5:
            LED_ON(LED_6);
            break;

        case 6:
            LED_ON(LED_7);
            break;

        case 7:
            LED_ON(LED_8);
            break;

        case 8:
            LED_ON(LED_9);
            break;

        case 9:
            LED_ON(LED_10);
            break;
    }

    LED_displayNumber(program + 1);

    MIDI_programChange16(program, channel);
}

void handle_switches(uint8_t event)
{
    if (SWITCH_isLongPress(event))
    {
        Nop();
    }
    else if (SWITCH_isShortPress(event))
    {
        switch(SWITCH_getCode(event))
        {
        case SWITCH_1_CODE:
            if (bank_size >= 1)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 0);
            }
            else
            {
                IA_toggleState(1);
            }
            break;

        case SWITCH_2_CODE:
            if (bank_size >= 2)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 1);
            }
            else
            {
                IA_toggleState(2);
            }
            break;

        case SWITCH_3_CODE:
            if (bank_size >= 3)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 2);
            }
            else
            {
                IA_toggleState(3);
            }
            break;

        case SWITCH_4_CODE:
            if (bank_size >= 4)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 3);
            }
            else
            {
                IA_toggleState(4);
            }
            break;

        case SWITCH_5_CODE:
            if (bank_size >= 5)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 4);
            }
            else
            {
                IA_toggleState(5);
            }
            break;

        case SWITCH_6_CODE:
            if (bank_size >= 6)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 5);
            }
            else
            {
                IA_toggleState(6);
            }
            break;

        case SWITCH_7_CODE:
            if (bank_size >= 7)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 6);
            }
            else
            {
                IA_toggleState(7);
            }
            break;

        case SWITCH_8_CODE:
            if (bank_size >= 8)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 7);
            }
            else
            {
                IA_toggleState(8);
            }
            break;

        case SWITCH_9_CODE:
            if (bank_size >= 9)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 8);
            }
            else
            {
                IA_toggleState(9);
            }
            break;

        case SWITCH_10_CODE:
            if (bank_size >= 10)
            {
                AXE_programChange(MIDI_CHANNEL, (bank * bank_size) + 9);
            }
            else
            {
                IA_toggleState(10);
            }
            break;

        case SWITCH_UP_CODE:
            if (bank < num_banks - 1)
            {
                bank++;
            }
            break;

        case SWITCH_DOWN_CODE:
            if (bank > 0)
            {
                bank--;
            }
            break;
        }
    }
}

void main()
{
    static char XDATA eeprom_buffer[256];
    static uint8_t pedal_mask;
    static uint8_t adc0_result = 0, adc1_result = 0;
    static uint8_t event, ch1, ch2;

    FCB_init();

    while(1)
    {
        // Sysex
        //
        SYSEX_task();

        // Pedals
        //
        PEDAL_task();

        pedal_mask = PEDAL_getLatestValues(&adc0_result, &adc1_result);

        if (pedal_mask & 0x01)
        {
            ch1 = IA_getControllerForChannel(11);

            if (ch1)
            {
                MIDI_controlChange(ch1, MIDI_CHANNEL, adc0_result);
            }
        }

        if (pedal_mask & 0x02)
        {
            ch2 = IA_getControllerForChannel(12);

            if (ch2)
            {
                MIDI_controlChange(ch2, MIDI_CHANNEL, adc1_result);
            }
        }

        // Switches
        //
        event = SWITCH_getNextEvent();

        if (SWITCH_isValidEvent(event))
        {
            handle_switches(event);
        }
    }
}
