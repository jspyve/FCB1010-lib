#ifndef _RELAY_H_
#define _RELAY_H_

#define RELAY_1_MASK 0x01
#define RELAY_2_MASK 0x02

extern volatile uint8_t XDATA g_relay_state;

#define RELAY_get_relay_state() (g_relay_state & (RELAY_1_MASK | RELAY_2_MASK))

static inline void RELAY_init()
{
    g_relay_state = 0;
}

static inline void RELAY_setRelayOn(uint8_t mask)
{
    g_relay_state |= (mask & (RELAY_1_MASK | RELAY_2_MASK));
}

static inline void RELAY_setRelayOff(uint8_t mask)
{
    g_relay_state = (g_relay_state & ~(RELAY_1_MASK | RELAY_2_MASK)) | (mask & (RELAY_1_MASK | RELAY_2_MASK));
}

#endif


