
/******************************************************************************
 *
 * Module: LM35 temperature sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: header file for the LM35 driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 6, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                               Inclusions                                  *
 *******************************************************************************/

#include"lm35_sensor.h"

/*******************************************************************************
 *                              Functions                           *
 *******************************************************************************/

/* Description :
 * A Function that read the digital value read from the sensor by ADC
 * and return the temperature value
 */
uint8 LM35_getTemperature(void)
{
	uint8 temperature=0;
	uint16 digitalValue=0;

	/*get the digital value from ADC*/
	digitalValue = ADC_readChannel(LM35_OUTPUT_PIN);

	/*calculate the temperature */
	temperature=(uint8)(((uint32)digitalValue*LM35_MAX_TEMPERATURE*ADC_Vref)/(ADC_MAX_DIGITAL_VALUE*LM35_MAX_VOLT));

	/*return the temperature*/
	return temperature;
}
