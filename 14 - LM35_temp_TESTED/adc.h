
/******************************************************************************
 *
 * Module: adc
 *
 * File Name: adc.h
 *
 * Description: header file for the AVR ADC driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 5, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/
#include"std_types.h"

#ifndef ADC_H_
#define ADC_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_Vref 		 	   5
#define ADC_MAX_DIGITAL_VALUE  1023
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 * initiate the ADC module
 */
void ADC_init(void);

/* Description :
 * read the value at the channel ( The produced value of conversation )
 */
uint16 ADC_readChannel(uint8 channel);

#endif /* ADC_H_ */
