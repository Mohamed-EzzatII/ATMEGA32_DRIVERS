
/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: source file for the UART driver dynamic configurations
 *
 * Author: Mohamed Ezzat
 *
 * Created on : 19/4/2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/*******************************************************************************
 *                               Inclusions                                    *
 *******************************************************************************/

#include<avr/io.h>
#include"uart.h"
#include"common_macros.h"

/*******************************************************************************
 *                           	Functions definition	                       *
 *******************************************************************************/

/* Description :
 * A function to initialize the UART communication protocol using dynamic configurations
 */
void UART_init(const config *conf)
{
	/* double speed mode */
	SET_BIT(UCSRA,U2X);

	/* Enable receiver and transmitter */
	UCSRB |= (1<<RXEN) | (1<<TXEN);

	/* register select - async mode - disable parity - 1 bit stop bit - 8-bit character size */
	UCSRC=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0) | (conf->parity) | (conf->stop) | (conf->bit);

	/* set the baud rate */
	uint16 UBR_value = (F_CPU/ (8*(conf->baud_rate))) -1;

	UBRRH = (UBR_value &0xFF00)>>8;
	UBRRL = (uint8)(UBR_value&0xFF);
}

/*
 * Description :
 * A Function that send a byte using UART
 * return type is void and it takes a pointer to constant data (char)
 */
void UART_sendByte(const uint8 *byte)
{
	/* wait till the UDR is empty */
	while(BIT_IS_CLEAR(UCSRA,UDRE));

	/* transmit the data*/
	UDR= *byte;
}

/*
 * Description :
 * A Function that receive a byte using UART
 * return type is void and it takes a pointer to char and change its value with data received
 */
void UART_receiveByte( uint8 *byte)
{
	/* wait till the data is received */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	/* get the data*/
	*byte= UDR;
}

/*
 * Description :
 * A Function that receive a string using UART
 * return type is void and it takes a pointer to char and change its value with data received.
 *
 * How does it work ?
 *the string ends with # as null , so we receive the whole string and replace # with null
 */
void UART_receiveString(uint8 *str)
{
	uint8 counter=0;

	/* receive the first byte */
	UART_receiveByte(str);


	/* receive the whole string till the null (#) */
	while(str[counter] != '#' )
	{
		counter++;
		UART_receiveByte(str+counter);
	}

	/* replace the non-real null (#) with real null (\0)*/
	str[counter] = '\0';
}

/*
 * Description :
 * A Function that send a string using UART
 * return type is void and it takes a pointer to constant data (char).
 *
 * How does it work ?
 * in case of sending a string we send it byte by byte , and we send # as null
 */
void UART_sendString(const uint8 *str)
{
	uint8 counter=0;

	/* send the whole string till the null (\0) */
	for(counter=0;str[counter] != '\0';counter++ )
	{
		UART_sendByte(str+counter);
	}


	/* send the non-real null (#)*/
	UART_sendByte(&counter);
}
