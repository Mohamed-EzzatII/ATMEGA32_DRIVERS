
/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: ICU.h
 *
 * Description: source file for the LM35 driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: Oct 6, 2022
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                               Inclusions                                    *
 *******************************************************************************/

#include"icu.h"
#include<avr/io.h>
#include"common_macros.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_theCallBackFunction)(void)=NULL_PTR;

/*******************************************************************************
 *                           	Functions & INT	                               *
 *******************************************************************************/

/*
 * Description:
 * The ISR code which call the call back function
 */
ISR(TIMER1_CAPT_vect)
{
	if(g_theCallBackFunction!= NULL_PTR)
		(*g_theCallBackFunction)();
}

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 * 	NOTE : Sorry ! i tried to make it with dynamic configuration with timer modes
 */
void ICU_init(const ICU_ConfigType * Config_Ptr)
{
	/*set the ICU1 pin as input PD6*/
	DDRD&=(1<<PD6);

	/*
	 * TCCR1A register :-
	 * 1 - COM1A 1:0 & COM1B 1:0 are set to 0 (disconnect OC1A & OC1B)
	 * 2 - FOC1A & FOC1B are set to 0 (non-pwm mode)
	 * 3 - WGM1 3:0 are set to 0 (normal mode)
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*
	 * TCCR1B register :-
	 * 1 - ICNC1 is set to remove noise cancellation at low frequency
	 * 2 - ICES1 is set(rising edge) or cleared(falling edge) according to user choice (6th bit)
	 * 3 - WGM1 3:0 are set to 0 (normal mode)
	 * 4 - CS1 2:0 is dynamic configurable which is responsible for prescaler ( 1st & 2nd & 3rd bits)
	 */
	TCCR1B|=( (Config_Ptr->edge) <<6 ) | (Config_Ptr->clock);

	/*
	 * TIMSK register :-
	 * 1 - set TICIE1 to enable the interrupts
	 */
	TIMSK|=(1<<TICIE1);

	/************************* The following are optional :)**********************/

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;
	TIMSK |= (1<<TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void))
{
	g_theCallBackFunction=a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_edge_Type edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) |( edgeType << 6 );
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0 ;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	/* clear TCCR1A and TCCR1B registers*/
	TCCR1A = 0;
	TCCR1B = 0;

	/* clear the counter*/
	TCNT1 = 0;

	/* Disable the flag*/
	TIMSK &=~(1<<TICIE1);

	/*clear the value stored at ICR register*/
	ICR1=0;
}
