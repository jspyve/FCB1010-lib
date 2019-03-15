#ifdef __DEVKIT_BUILD__
#warning Building for DevKit
#include "at89c51ed2.h"
#endif

#include "mcu.h"

unsigned char _sdcc_external_startup(void)
{
#ifdef __DEVKIT_BUILD__
    BSET(AUXR, 1);
#endif

    return 0;
}

void MCU_init()
{
#ifdef __DEVKIT_BUILD__
    // slow down RD/WR cycles
    //
    //AUXR |= 0b00100011;
    BSET(AUXR, 5);
    BSET(AUXR, 1);
    BSET(AUXR, 0);
#endif
}
