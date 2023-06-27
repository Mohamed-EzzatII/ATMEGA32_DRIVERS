
/******************************************************************************
 *
 * Module: Timer PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the atmega32 pwm
 *
 * Author: Mohamed Ezzat
 *
 * Created on: June 16, 2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                               Inclusions                                  *
 *******************************************************************************/

#include<avr/io.h>
#include"pwm.h"


/*******************************************************************************
 *                            Global Variables 	                               *
 *******************************************************************************/

uint8 g_dutyCycle=0;


/*******************************************************************************
 *                         FUNCTIONS definition	                               *
 *******************************************************************************/

void PWM_init(PWM_config *conf)
{
	if(conf->num == PWM0)
	{
		TCCR0=(1<<WGM01)|(1<<WGM00)|(conf->mode)|(conf->nt0);

		DDRB|=(1<<PB3);

		OCR0=(256*conf->duty_cycle)/100;

	}

	else if(conf->num == PWM2)
	{
		TCCR2=(1<<WGM21)|(1<<WGM20)|(conf->mode)|(conf->nt2);

		DDRD|=(1<<PD7);

		OCR2=(256*conf->duty_cycle)/100;

	}
}

void PWM_setDutyCycle(uint8 pwm_no,uint8 duty)
{
	if(pwm_no == 0)
	{
		OCR0=(256*duty)/100;
	}

	else if(pwm_no == PWM2)
	{
		OCR2=(256*duty)/100;
	}
}
