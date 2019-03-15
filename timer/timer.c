#include "hardware/hardware.h"
#include "led/leds.h"
#include "switch/switches.h"
#include "relay/relay.h"
#include "timer.h"
#include "cbuff/cbuff.h"

#define IS_LONG_PRESS(x) ((x) == 0xffffffff)
#define IS_SHORT_PRESS(x) (((x) & 0xff) == 0xff)
#define IS_RELEASE(x) (((x) & 0xff) == 0x00)
#define MAKE_LONG_PRESS_EVENT(x) (0x80 | (x))
#define MAKE_SHORT_PRESS_EVENT(x) (0x40 | (x))
#define MAKE_LONG_RELEASE_EVENT(x) (0x20 | (x))
#define MAKE_SHORT_RELEASE_EVENT(x) (0x10 | (x))

static volatile IDATA uint8_t column = 1;
static volatile IDATA uint8_t row = 0;

static volatile IDATA uint8_t key = 0;

static volatile IDATA uint8_t flash_tick = 0;

static volatile XDATA uint32_t key_debounce[12];

static volatile uint16_t XDATA key_last = 0;
static volatile uint16_t XDATA key_last_long = 0;

void TIMER_isr (void) __interrupt (TF0_VECTOR)
{
    static int i;
    static uint32_t val, mask, code;

    TR0 = 0;
    TF0 = 0;

    // LED mux task
    //
    PERIPHERALS[PERIPHERAL_DUMMY_MUX] = 0;
    PERIPHERALS[PERIPHERAL_LATCH_SEGMENTS] = 0xff;
    PERIPHERALS[PERIPHERAL_LATCH_COMMONS] = column;
    PERIPHERALS[PERIPHERAL_LATCH_SEGMENTS] = LED_MAP[row];
    PERIPHERALS[PERIPHERAL_DUMMY_MUX] = 0;

    flash_tick++;

    if (flash_tick == 100)
    {
        flash_tick = 0;

        for (i = 0; i < 6; i++)
        {
            LED_MAP[i] ^= LED_FLASH_MAP[i];
            LED_MAP[i] ^= LED_QUICK_FLASH_MAP[i];
        }
    }
    else if (flash_tick == 50)
    {
        for (i = 0; i < 6; i++)
        {
            LED_MAP[i] ^= LED_QUICK_FLASH_MAP[i];
        }
    }

    row++;
    column <<= 1;

    if (row == 6)
    {
        row = 0;
        column = 1;
    }

    // Switch debounce task
    //
    WRITE_PERIPHERAL(PERIPHERAL_LATCH_RELAY_KEY_COLUMNS, (4 << key) | RELAY_get_relay_state());

    key_debounce[key] <<= 1;
    key_debounce[key+6] <<= 1;

    key_debounce[key]  |= (P1_6 ? 1 : 0);
    key_debounce[key+6] |= (P1_5 ? 1 : 0);

    for (code = key, i = 0; i < 2; i++, code = key+6)
    {
        val = key_debounce[code];
        mask = 1 << code;

        if (IS_LONG_PRESS(val))
        {
            if ((key_last & mask) == 0)
            {
                key_last |= mask;
                CB_put(&event_buffer, MAKE_SHORT_PRESS_EVENT(code));
            }
            else if ((key_last_long & mask) == 0)
            {
                key_last_long |= mask;
                CB_put(&event_buffer, MAKE_LONG_PRESS_EVENT(code));
            }
        }
        else if (IS_SHORT_PRESS(val))
        {
            if ((key_last & mask) == 0)
            {
                key_last |= mask;
                CB_put(&event_buffer, MAKE_SHORT_PRESS_EVENT(code));
            }
        }
        else if (IS_RELEASE(val) == 0)
        {
            if (((key_last | key_last_long) & mask) != 0)
            {
                if (key_last_long & mask)
                {
                    CB_put(&event_buffer, MAKE_LONG_RELEASE_EVENT(code));
                }
                else if (key_last & mask)
                {
                    CB_put(&event_buffer, MAKE_SHORT_RELEASE_EVENT(code));
                }
                key_last &= ~mask;
                key_last_long &= mask;
            }
        }
    }

    key++;

    if (key > 5)
    {
        key = 0;
    }

    // Reload timer
    //
    TH0 = (T0_COUNT >> 8);
    TL0 = (T0_COUNT & 0xff);

    TR0 = 1;
}


void TIMER_init()
{
    // Timer 0, 16-bit timer
    //
    TMOD = (TMOD & 0xf0 ) | 1;
    TH0 = (T0_COUNT >> 8);
    TL0 = (T0_COUNT & 0xff);
    TF0 = 0x00;

    ET0 = 1;
    TR0 = 0x01;
}

