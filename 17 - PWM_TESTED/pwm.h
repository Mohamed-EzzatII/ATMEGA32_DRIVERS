
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

#ifndef MCAL_PWM_H_
#define MCAL_PWM_H_

/*******************************************************************************
 *                               Inclusions                                  *
 *******************************************************************************/

#include"std_types.h"

/*******************************************************************************
 *                               	Typedef	                                   *
 *******************************************************************************/

typedef enum{PWM0,PWM2}PWM_NUMBER;

typedef enum{NON_INVERTING=32,INVERTING=16+32}MODE;

typedef enum{N2_NOCLK,N2_0,N2_8,N2_32,N2_64,N2_128,N2_256,N2_1024}PRESCALER_TIMER2;

typedef enum{N0_NOCLK,N0_0,N0_8,N0_64,N0_256,N0_1024,N0_EXT_FALLING,N0_EXT_RISING}PRESCALER_TIMER0;

typedef struct{
	PWM_NUMBER num;
	MODE mode;
	PRESCALER_TIMER0 nt0;
	PRESCALER_TIMER2 nt2;
	uint8 duty_cycle;
}PWM_config;


/*******************************************************************************
 *                         FUNCTIONS Prototype	                               *
 *******************************************************************************/

void PWM_init(PWM_config *conf);

void PWM_setDutyCycle(uint8 pwm_no,uint8 duty);
#endif /* MCAL_PWM_H_ */
