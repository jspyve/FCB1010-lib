#ifndef _LEDS_H_
#define _LEDS_H_

// footswitch LEDs
//
#define LED_6_ADDR  0x04
#define LED_6_MASK  (1 << 7)

#define LED_7_ADDR  0x04
#define LED_7_MASK  (1 << 6)

#define LED_8_ADDR  0x04
#define LED_8_MASK  (1 << 5)

#define LED_9_ADDR  0x04
#define LED_9_MASK  (1 << 4)

#define LED_10_ADDR 0x04
#define LED_10_MASK (1 << 3)

#define LED_1_ADDR  0x04
#define LED_1_MASK  (1 << 2)

#define LED_2_ADDR  0x04
#define LED_2_MASK  (1 << 1)

#define LED_3_ADDR  0x04
#define LED_3_MASK  (1 << 0)

#define LED_4_ADDR  0x03
#define LED_4_MASK  (1 << 7)

#define LED_5_ADDR  0x03
#define LED_5_MASK  (1 << 6)

// Status LEDs
//
#define LED_CONFIG_ADDR 0x05
#define LED_CONFIG_MASK (1 << 6)

#define LED_SWITCH_ADDR 0x05
#define LED_SWITCH_MASK (1 << 5)

#define LED_SELECT_ADDR 0x05
#define LED_SELECT_MASK (1 << 4)

#define LED_NUMBER_ADDR 0x05
#define LED_NUMBER_MASK (1 << 3)

#define LED_VALUE_1_ADDR 0x05
#define LED_VALUE_1_MASK (1 << 2)

#define LED_VALUE_2_ADDR 0x05
#define LED_VALUE_2_MASK (1 << 1)

#define LED_DIRECT_BANK_SEL_ADDR 0x05
#define LED_DIRECT_BANK_SEL_MASK (1 << 0)

//

#define LED_MIDI_CHAN_ADDR 0x03
#define LED_MIDI_CHAN_MASK (1 << 1)

#define LED_MIDI_FUNC_ADDR 0x03
#define LED_MIDI_FUNC_MASK (1 << 0)

#define LED_EXP_1_ADDR 0x03
#define LED_EXP_1_MASK (1 << 3)

#define LED_EXP_2_ADDR 0x03
#define LED_EXP_2_MASK (1 << 2)

#define LED_SWITCH_1_ADDR 0x03
#define LED_SWITCH_1_MASK (1 << 4)

#define LED_SWITCH_2_ADDR 0x03
#define LED_SWITCH_2_MASK (1 << 5)

//

#define LED_OFF(name)          {LED_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_QUICK_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_MAP[name##_ADDR] |= name##_MASK;}
#define LED_ON(name)           {LED_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_QUICK_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_MAP[name##_ADDR] &= ~name##_MASK;}
#define LED_SET(name, state)   {LED_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_QUICK_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_MAP[name##_ADDR] = (LED_MAP[name##_ADDR] & ~name##_MASK) | (state == 0 ? name##_MASK : 0);}
#define LED_FLASH(name)        {LED_MAP[name##_ADDR] &= ~name##_MASK; LED_QUICK_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_FLASH_MAP[name##_ADDR] |= name##_MASK; }
#define LED_FLASH_QUICK(name)  {LED_MAP[name##_ADDR] &= ~name##_MASK; LED_FLASH_MAP[name##_ADDR] &= ~name##_MASK; LED_QUICK_FLASH_MAP[name##_ADDR] |= name##_MASK; }

// Segment macros
//
#define SEG_DIGIT_MASK 0xfe
#define SEG_DP_MASK    0x01

#define SEG_A_MASK   0x80
#define SEG_B_MASK   0x40
#define SEG_C_MASK   0x20
#define SEG_D_MASK   0x10
#define SEG_E_MASK   0x08
#define SEG_F_MASK   0x04
#define SEG_G_MASK   0x02
#define SEG_DP_MASK  0x01

#define SEG_DIGIT_UNITS    0
#define SEG_DIGIT_TENS     1
#define SEG_DIGIT_HUNDREDS 2

#define SEG_DIGIT_SET(digit, value)   {LED_MAP[digit] = (LED_MAP[digit] & SEG_DP_MASK) | ((~digits_table[(value) % 10]) & SEG_DIGIT_MASK);}
#define SEG_DIGIT_SET_DP_ON(digit)    {LED_MAP[digit] &= ~SEG_DP_MASK;}
#define SEG_DIGIT_SET_DP_OFF(digit)   {LED_MAP[digit] |= SEG_DP_MASK;}
#define SEG_DIGIT_CLEAR(digit)        {LED_MAP[digit] = 0xff; }

#define SEG_DIGIT_100_SET(value)      SEG_DIGIT_SET(SEG_DIGIT_HUNDREDS, value)
#define SEG_DIGIT_100_SET_DP_ON       SEG_DIGIT_SET_DP_ON(SEG_DIGIT_HUNDREDS)
#define SEG_DIGIT_100_SET_DP_OFF      SEG_DIGIT_SET_DP_OFF(SEG_DIGIT_HUNDREDS)
#define SEG_DIGIT_100_CLEAR()         SEG_DIGIT_CLEAR(SEG_DIGIT_HUNDREDS)

#define SEG_DIGIT_10_SET(value)       SEG_DIGIT_SET(SEG_DIGIT_TENS, value)
#define SEG_DIGIT_10_SET_DP_ON        SEG_DIGIT_SET_DP_ON(SEG_DIGIT_TENS)
#define SEG_DIGIT_10_SET_DP_OFF       SEG_DIGIT_SET_DP_OFF(SEG_DIGIT_TENS)
#define SEG_DIGIT_10_CLEAR()          SEG_DIGIT_CLEAR(SEG_DIGIT_TENS)

#define SEG_DIGIT_1_SET(value)        SEG_DIGIT_SET(SEG_DIGIT_UNITS, value)
#define SEG_DIGIT_1_SET_DP_ON         SEG_DIGIT_SET_DP_ON(SEG_DIGIT_UNITS)
#define SEG_DIGIT_1_SET_DP_OFF        SEG_DIGIT_SET_DP_OFF(SEG_DIGIT_UNITS)
#define SEG_DIGIT_1_CLEAR()           SEG_DIGIT_CLEAR(SEG_DIGIT_UNITS)

extern const uint8_t digits_table[];
extern uint8_t XDATA LED_MAP[];
extern uint8_t XDATA LED_FLASH_MAP[];
extern uint8_t XDATA LED_QUICK_FLASH_MAP[];

static inline void LED_displayNumber(uint8_t number)
{
	if (number >= 100)
	{
		SEG_DIGIT_100_SET(number / 100);

		number %= 100;
	}
	else
	{
		SEG_DIGIT_100_CLEAR();
	}

	if (number >= 10)
	{
		SEG_DIGIT_10_SET(number / 10);

		number %= 10;
	}
	else
	{
		SEG_DIGIT_10_CLEAR();
	}

	SEG_DIGIT_1_SET(number);
}

#endif
