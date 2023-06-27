
#include"lm35_sensor.h"
#include"lcd.h"

int main(void)
{
	LCD_init();
	ADC_init();

	LCD_displayString("Temp =    C");

	while(1)
	{
		LCD_moveCursor(0,7);
		if(LM35_getTemperature()<=99){
			LCD_integerToString(LM35_getTemperature());
			LCD_displayCharacter(' ');
		}
		else
			LCD_integerToString(LM35_getTemperature());
	}

}
