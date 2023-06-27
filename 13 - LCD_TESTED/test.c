/*
 * test.c
 *
 *  Created on: Oct 3, 2022
 *      Author: ezzat
 */
#include"lcd.h"
#include<util/delay.h>
int main(void)
{
	LCD_init();
	LCD_displayCharacter('A');
	_delay_ms(100);
	LCD_clearScreen();
	LCD_displayString("mohamed");
	_delay_ms(100);
	LCD_clearScreen();
	LCD_integerToString(200);

	while(1);
}


