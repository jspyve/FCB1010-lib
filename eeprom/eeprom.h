#ifndef __EEPROM_H__
#define __EEPROM_H__

extern void EEPROM_read(uint16_t address, uint8_t *buffer, uint16_t len);
extern void EEPROM_write(uint16_t address, uint8_t *buffer, uint16_t len);

#endif
