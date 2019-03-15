#include "hardware/hardware.h"
#include "i2c.h"

#define BIT_DELAY() {Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); }

void I2C_init()
{
    SDA = 1;
    SCL = 1;
    BIT_DELAY();
}

void I2C_start()
{
    BIT_DELAY();
    SCL = 1;
    BIT_DELAY();
    SDA = 0;
    BIT_DELAY();
    SCL = 0;
    BIT_DELAY();
}

void I2C_restart()
{
    BIT_DELAY();
    SDA = 1;
    BIT_DELAY();
    SCL = 1;
    BIT_DELAY();
    SDA = 0;
    BIT_DELAY();
}

void I2C_stop()
{
    BIT_DELAY();
    SDA = 0;
    BIT_DELAY();
    SCL = 1;
    BIT_DELAY();
    SDA = 1;
    BIT_DELAY();
}

void I2C_ack()
{
    BIT_DELAY();
    SDA = 0;
    BIT_DELAY();
    SCL = 1;
    BIT_DELAY();
    SCL = 0;
    BIT_DELAY();
}

void I2C_nak()
{
    BIT_DELAY();
    SDA = 1;
    BIT_DELAY();
    SCL = 1;
    BIT_DELAY();
    SCL = 0;
    BIT_DELAY();
}

uint8_t I2C_send(uint8_t data)
{
    uint8_t i, ack_bit;

    BIT_DELAY();

    for(i=0; i<8; i++)
    {
        SCL = 0;

        BIT_DELAY();

        if (data & 0x80)
        {
            SDA = 1;
        }
        else
        {
            SDA = 0;
        }

        BIT_DELAY();

        SCL = 1;

        data <<= 1;
     }

    BIT_DELAY();

    SCL = 0;
    Nop();
    SDA = 1;
    BIT_DELAY();
    ack_bit = SDA;
    BIT_DELAY();
    SCL = 1;
    BIT_DELAY();
    SCL = 0;
    BIT_DELAY();

     return !ack_bit;
}

uint8_t I2C_read()
{
    uint8_t i, data=0;

    BIT_DELAY();

    SDA = 1;

    for(i=0; i<8; i++)
    {
        data <<= 1;

        SCL = 0;
        BIT_DELAY();
        SCL = 1;
        BIT_DELAY();

        if(SDA)
        {
            data |=1;
        }

        BIT_DELAY();
    }

    SCL = 0;
    BIT_DELAY();
    SDA = 1;
    BIT_DELAY();

    return data;
}
