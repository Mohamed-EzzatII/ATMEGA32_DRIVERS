 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver dynamic configurations
 *
 * Author: Mohamed Ezzat
 *
 * created date : 19/4/2023
 *
 * Version : v2.0.1
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

/*******************************************************************************
 *                                Inclusions                                  *
 *******************************************************************************/

#include"std_types.h"

/*******************************************************************************
 *                         	   Type Definitions                                *
 *******************************************************************************/

/* an enum to determine the number of stop bits*/
typedef enum{
	ONE,TWO=8
}stop_bit;

/* an enum to enable or disable the parity bit*/
typedef enum{
	DISABLE,EVEN=32,ODD=48
}parity_bit;

/* an enum to determine the size of our data*/
typedef enum{
	FIVE_BITS,SIX_BITS,SEVEN_BITS,EIGHT_BITS
}bit_data;

/*the struct which is responsible for all of that*/
typedef struct{
	stop_bit stop;
	parity_bit parity;
	bit_data bit;
	uint32 baud_rate;
}config;


/*******************************************************************************
 *                         FUNCTIONS Prototypes                                *
 *******************************************************************************/

/* Description :
 * A function to initialize the UART communication protocol using dynamic configurations
 */
void UART_init(const config *conf);

/*
 * Description :
 * A Function that send a byte using UART
 * return type is void and it takes a pointer to constant data (char)
 */
void UART_sendByte(const uint8 *byte);

/*
 * Description :
 * A Function that receive a byte using UART
 * return type is void and it takes a pointer to char and change its value with data received
 */
void UART_receiveByte( uint8 *byte);

/*
 * Description :
 * A Function that receive a string using UART
 * return type is void and it takes a pointer to char and change its value with data received.
 *
 * How does it work ?
 *the string ends with # as null , so we receive the whole string and replace # with null
 */
void UART_receiveString(uint8 *str);

/*
 * Description :
 * A Function that send a string using UART
 * return type is void and it takes a pointer to constant data (char).
 *
 * How does it work ?
 * in case of sending a string we send it byte by byte , and we send # as null
 */
void UART_sendString(const uint8 *str);

#endif /* UART_H_ */
