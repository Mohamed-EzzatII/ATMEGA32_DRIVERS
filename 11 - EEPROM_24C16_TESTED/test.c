/*
 ================================================================================================
 Name        : External_EEPROM_I2C.c
 Author      : Mohamed Tarek
 Description : Code to test the external EEPROM driver
 Date        : 12/3/2014
 ================================================================================================
 */

#include "E24c16.h"
#include "gpio.h"
#include "util/delay.h"
#include "i2c.h"

int main(void)
{
	uint8 val = 1;

//	/* Initialize the TWI/I2C Driver */
	I2C_init(0b00000010);
//
	GPIO_setupPortDirection(PORTD_ID,0xFF); /* All PORTD pins are o/p pins */
//
	uint8 x=EEPROM_writeByte(0x0311, 0x0F); /* Write 0x0F in the external EEPROM */
	_delay_ms(100);
	uint8 y=EEPROM_readByte(0x0311, &val);  /* Read 0x0F from the external EEPROM */

	while(1)
	{
		GPIO_writePort(PORTD_ID,val); /* out the read value from the external EEPROM */
	}
	return 0;
}
