#ifndef _SERIAL_H_
#define _SERIAL_H_

extern void SERIAL_isr (void) __interrupt (SI0_VECTOR);
extern void SERIAL_tx(uint8_t c);
extern void SERIAL_init();
extern void SERIAL_put8Bits(uint8_t b);
extern void SERIAL_putByte(uint8_t c);
extern uint8_t SERIAL_hasData();
extern uint8_t SERIAL_isIdle();
extern uint8_t SERIAL_rx();

#endif


