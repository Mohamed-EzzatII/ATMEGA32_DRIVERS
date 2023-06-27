 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.c
 *
 * Description: Source file for the SPI driver
 *
 * Author: Mohamed Ezzat
 *
 * Created on: 19/4/2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

/************************Libraries and inclusions*******************************/

#include"common_macros.h"
#include<avr/io.h>
#include"spi.h"
#include"gpio.h"
/*******************************************************************************/

/*******************************************************************************
 *                      		   FUNCTIONS                                   *
 *******************************************************************************/

/*
 * Description :
 * A function to initialize the master
 */
void SPI_init_master(const config *conf)
{
	/*
	 * Make the pins directions : -
	 * SS(PB4) , PB5(MOSI) , PB7(SCK) -> output
	 * PB6(MISO)                      -> input
	 */
	DDRB |=0xB0; //0b10110000
	DDRB &= ~(1<<6);

	/*
	 * Enable SPI - configure data order - configure clock shape
	 * set as master - prescaler - data detection
     */
	SPCR = (1<<SPE) | (conf->bit << DORD) | (1<<MSTR) | (conf->clock << CPOL) | (conf->signal << CPHA) | ((conf->prescaler)&0b11);

	/*
	 * The double speed bit which is the third bit in prescaler
	 */
	SPSR |= ( ( (conf->prescaler) >> 2 ) & 1 );
}

/*
 * Description :
 * A function to initialize the slave
 */
void SPI_init_slave(const config *conf)
{
	/*
	 * Make the pins directions : -
	 * SS(PB4) , PB5(MOSI) , PB7(SCK) -> input
	 * PB6(MISO)                      -> output
	 */
	DDRB &= ~0xB0; //0b10110000
	DDRB |= 1<<6;

	/*
	 * Enable SPI - configure data order - configure clock shape
	 * set as slave - prescaler - data detection
     */
	SPCR = (1<<SPE) | (conf->bit << DORD) | (conf->clock << CPOL) | (conf->signal << CPHA) | ((conf->prescaler)&0b11);

	/*
	 * The double speed bit which is the third bit in prescaler
	 */
	SPSR |= ( ( (conf->prescaler) >> 2 ) & 1 );

}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{
	/*send the data*/
	SPDR = data;

	/*wait till it send*/
	while(BIT_IS_CLEAR(SPSR,SPIF));

	/*get the received data*/
	return SPDR;

}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 counter=0;
	for(counter=0;str[counter] != '\0';counter++)
		SPI_sendReceiveByte(str+counter);

}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 counter=0,dummy=0xFF;
	str[counter]=SPI_sendReceiveByte(&dummy);
	while(str[counter] != '#'){
		counter++;
		str[counter]=SPI_sendReceiveByte(&dummy);
	}
	str[counter]='\0';
}
