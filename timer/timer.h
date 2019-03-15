#ifndef _TIMER_H_
#define _TIMER_H_

extern void TIMER_isr (void) __interrupt (TF0_VECTOR);

extern void TIMER_init();

#endif
