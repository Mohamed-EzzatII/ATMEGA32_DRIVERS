
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
void ADC_init(void)
{
	/*channel is channel(0) Vref=AVCC*/
	ADMUX=(1<<REFS0);

	/*Enable ADC , ADC interrupt is disabled*/
	ADCSRA=(1<<ADEN);

	/* Prescaler=128 so F(ADC)=125KHz*/
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

}

/* Description :
 * read the value at the channel ( The produced value of conversation )
 */
uint16 ADC_readChannel(uint8 channel_number)
{
	/*insert channel_number to ADMUX*/
	ADMUX&=0xf8;
	ADMUX|=channel_number;

	/*start conversation*/
	ADCSRA|=(1<<ADSC);

	/* polling : Looping till flag=1*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));

	/*Clear the flag*/
	SET_BIT(ADCSRA,ADIF);

	/*return data*/
	return ADC;
}
