#ifndef __MCU_H__
#define __MCU_H__

#define BSET(reg, bit) {reg |= (unsigned char)(1 << bit); }
#define BCLR(reg, bit) {reg &= ~(unsigned char)(1 << bit); }

extern void MCU_init();
extern unsigned char _sdcc_external_startup(void);

#endif
