/*
 * challenge1_board.c
 *
 *  Created on: Oct 8, 2022
 *      Author: ezzat
 */
#include"lcd.h"
#include"keypad.h"
int main(void)
{
	uint8 pressed_key;

	LCD_init();
	LCD_displayString("Challenge 2 :-");
	LCD_moveCursor(1,0);
	LCD_displayString("btn :-");

	while(1)
	{
		pressed_key=KEYPAD_getPressedKey();

		#ifndef STANDARD_KEYPAD

		if(pressed_key>=0 && pressed_key<=9)
			LCD_integerToString(pressed_key);
		else
			LCD_displayCharacter(pressed_key);

		#else
		LCD_integerToString(pressed_key);

		#endif/*STANDARD_KEYPAD*/

		while(pressed_key==KEYPAD_getPressedKey());

	}
}
