
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
 * Created on: April 9, 2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/*******************************************************************************
 *                              	Includes		                           *
 *******************************************************************************/

#include"std_types.h"

/*******************************************************************************
 *                              	Definition		                           *
 *******************************************************************************/

/*******************************************************************************
 *                              	   ENUMS			                       *
 *******************************************************************************/

/* an enum to decide our reference voltage to use with ADMUX register*/
typedef enum {
	AREF_EXT=0,AVCC_5V=64,INT_2_56V=192
}ref_volt;

/* an enum to decide our ADC channel to use with ADMUX register*/
typedef enum{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}ch_no;

/* an enum to decide ADC frequency to make it between 50kHz~200kHz as Fadc = Fcpu / N
 * to use with ADCSRA register*/
typedef enum {
	N_2,N_4=2,N_8,N_16,N_32,N_64,N_128
}prescaler_N;

/* an enum to decide ADC result location in ADC register to use with ADMUX register
 * - > refer to datasheet page 217
 */
typedef enum {
	LSBs,MSBs=32
}ADC_res_bits;

/*******************************************************************************
 *                             Structures & Union			                   *
 *******************************************************************************/

/* a structure to use it to configure our ADC with function ADC_init*/
typedef struct {
	prescaler_N pre;
	ADC_res_bits bits;
	ref_volt volt;
}ADC_config;

/*******************************************************************************
 *                             Functions Prototype			                   *
 *******************************************************************************/

/* Description :
 * initiate the ADC module
 */
void ADC_init(const ADC_config* conf);

/* Description :
 * read the value at the channel ( The produced value of conversation )
 */
uint16 ADC_readChannel(ch_no channel);

#endif /* ADC_H_ */
