#include "hardware/hardware.h"
#include "i2c/i2c.h"
#include "eeprom/eeprom.h"

#define DEVICE_CODE 0xA0

void EEPROM_read(uint16_t address, uint8_t *buffer, uint16_t len)
{
    I2C_start();

    // set start address
    //
    I2C_send(DEVICE_CODE | ((address & 0x700) >> 7));
    I2C_send(address & 0xff);

    /* Actual read */
    I2C_restart();
    I2C_send(DEVICE_CODE | 0x01);

    while(len--)
    {
        *buffer++ = I2C_read();

        if (len == 1)
        {
            //I2C_nak();
        }
        else
        {
            I2C_ack();
        }
    }

    I2C_stop();
}

static uint8_t EEPROM_isBusy()
{
    uint8_t ack;

    I2C_start();
    ack = I2C_send(DEVICE_CODE);
    I2C_stop();

    return (ack == 1) ? 0 : 1;
}

void EEPROM_write(uint16_t address, uint8_t *buffer, uint16_t len)
{
    I2C_start();

    // set start address
    //
    I2C_send(DEVICE_CODE | ((address & 0x700) >> 7));
    I2C_send(address & 0xff);

    while(len--)
    {
        I2C_send(*buffer++);
    }

    I2C_stop();

    while(EEPROM_isBusy())
    {
    }
}

