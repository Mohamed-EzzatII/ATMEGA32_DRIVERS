
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

#include"std_types.h"
#include"adc.h"

#ifndef LM35_H_
#define LM35_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LM35_MAX_VOLT 		 1.5
#define LM35_MAX_TEMPERATURE 150
#define LM35_RESOLUTION		 0.001
#define LM35_OUTPUT_PIN		 0

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 * A Function that read the digital value read from the sensor by ADC
 * and return the temperature value
 */
uint8 LM35_getTemperature(void);

#endif /* LM35_H_ */
