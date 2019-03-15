#include "hardware/hardware.h"
#include "leds.h"

const uint8_t digits_table[] =
{
    SEG_A_MASK | SEG_B_MASK | SEG_C_MASK | SEG_D_MASK | SEG_E_MASK | SEG_F_MASK,               // 0
    SEG_B_MASK | SEG_C_MASK,                                                                   // 1
    SEG_A_MASK | SEG_B_MASK | SEG_D_MASK | SEG_E_MASK | SEG_G_MASK,                            // 2
    SEG_A_MASK | SEG_B_MASK | SEG_C_MASK | SEG_D_MASK | SEG_G_MASK,                            // 3
    SEG_B_MASK | SEG_C_MASK | SEG_F_MASK | SEG_G_MASK,                                         // 4
    SEG_A_MASK | SEG_C_MASK | SEG_D_MASK | SEG_F_MASK | SEG_G_MASK,                            // 5
    SEG_A_MASK | SEG_C_MASK | SEG_D_MASK | SEG_E_MASK | SEG_F_MASK | SEG_G_MASK,               // 6
    SEG_A_MASK | SEG_B_MASK | SEG_C_MASK,                                                      // 7
    SEG_A_MASK | SEG_B_MASK | SEG_C_MASK | SEG_D_MASK | SEG_E_MASK | SEG_F_MASK | SEG_G_MASK,  // 8
    SEG_A_MASK | SEG_B_MASK | SEG_C_MASK | SEG_D_MASK | SEG_F_MASK | SEG_G_MASK                // 9
};

uint8_t XDATA LED_MAP[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
uint8_t XDATA LED_FLASH_MAP[6] = {0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t XDATA LED_QUICK_FLASH_MAP[6] = {0x00, 0x00, 0x00, 0x00, 0x00};
