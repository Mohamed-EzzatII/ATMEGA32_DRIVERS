/******************************************************************************
 *
 * Module: adc
 *
 * File Name: adc.c
 *
 * Description: source file for the AVR ADC driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 5, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/************************Libraries and inclusions*******************************/

#include"common_macros.h"
#include<avr/io.h>
#include"adc.h"

/*******************************************************************************/

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description :
 * initiate the ADC module
 */
void ADC_init(const ADC_config* conf)
{
	/* Set reference voltage , ADC Left Adjust Result , channel is 0 at default*/
	ADMUX|=(conf->bits)|(conf->volt);

	/* Enable ADC & set our prescaler N */
	ADCSRA|=(1<<ADEN)|(conf->pre);

}

/* Description :
 * read the value at the channel ( The produced value of conversation )
 */
uint16 ADC_readChannel(ch_no channel)
{
	/*set our channel number*/
	ADMUX &= 0xF8;
	ADMUX|=channel;

	/*start conversation from Analog to digital*/
	ADCSRA|=(1<<ADSC);

	/*wait till we recieve the result of conversation*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	/*Clear the flag*/
	SET_BIT(ADCSRA,ADIF);

	/* return the read value at ADC register*/
	return ADC;
}
