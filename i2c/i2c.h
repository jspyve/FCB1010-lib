#ifndef __I2C_H__
#define __I2C_H__

extern void I2C_init();
extern void I2C_start();
extern void I2C_restart();
extern void I2C_stop();
extern void I2C_ack();
extern void I2C_nak();
extern uint8_t I2C_send(uint8_t data);
extern uint8_t I2C_read();

#endif
