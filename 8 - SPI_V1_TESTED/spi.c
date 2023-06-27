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
 * Created on: Oct 13, 2022
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
void SPI_init_master(edge_Type edge,CLK_freq clk,master_send_bit bit)
{
	/******** Configure SPI Master Pins *********
	 * SS   --> Output
	 * MOSI --> Output
	 * MISO --> Input
	 * SCK  --> Output
	 ********************************************/
	GPIO_setupPinDirection(MISO_PORT,MISO_PIN,PIN_INPUT);
	GPIO_setupPinDirection(MOSI_PORT,MOSI_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(SCLK_PORT,SCLK_PORT,PIN_OUTPUT);
	GPIO_setupPinDirection(SS_PORT,SS_PIN,PIN_OUTPUT);

	/*
	 * For SPCR register : -
	 * 7 - SPIE = 0    : disable interrupts
	 * 6 - SPE  = 1    : enable SPI
	 * 5 - DORD = bit  : master send MSB(0) or LSB(1) at first
	 * 4 - MSTR = 1    : we initialize the master
	 * 3 - CPOL = edge : choose if master send rising(0) and slave receive falling
	 * 				   : or master send falling(1) and slave receive rising at sending bit
	 * 2 - CPHA = edge : choose when to send the data
	 * 1,0 - SPR1:0    : choose the frequency of clock relative to frequency of CPU
	 */
	SPCR=(bit<<DORD)|(1<<MSTR)|(edge<<CPOL)|(edge<<CPHA)|(GET_BIT(clk,1)<<SPR1)|((GET_BIT(clk,0)<<SPR0));

	/*
	 * For SPSR register : -
	 * put the value of SPI2X to set the clock frequency
	 */
	SPSR |= (GET_BIT(clk,2)<<SPI2X);
}

/*
 * Description :
 * A function to initialize the slave
 */
void SPI_init_slave(edge_Type edge,CLK_freq clk,master_send_bit bit)
{
	/******** Configure SPI Slave Pins *********
	 * SS   --> Input
	 * MOSI --> Input
	 * MISO --> Output
	 * SCK  --> Input
	 ********************************************/
	GPIO_setupPinDirection(MISO_PORT,MISO_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOSI_PORT,MOSI_PIN,PIN_INPUT);
	GPIO_setupPinDirection(SCLK_PORT,SCLK_PORT,PIN_INPUT);
	GPIO_setupPinDirection(SS_PORT,SS_PIN,PIN_INPUT);

	/*
	 * For SPCR register : -
	 * 7 - SPIE = 0    : disable interrupts
	 * 6 - SPE  = 1    : enable SPI
	 * 5 - DORD = bit  : master send MSB(0) or LSB(1) at first
	 * 4 - MSTR = 0    : we initialize the slave
	 * 3 - CPOL = edge : choose if master send rising(0) and slave receive falling
	 * 				   : or master send falling(1) and slave receive rising at sending bit
	 * 2 - CPHA = edge : choose when to send the data
	 * 1,0 - SPR1:0    : choose the frequency of clock relative to frequency of CPU
	 */
	SPCR=(bit<<DORD)|(edge<<CPOL)|(edge<<CPHA)|(GET_BIT(clk,1)<<SPR1)|((GET_BIT(clk,0)<<SPR0));

	/*
	 * For SPSR register : -
	 * put the value of SPI2X to set the clock frequency
	 */
	SPSR |= (GET_BIT(clk,2)<<SPI2X);
}

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data)
{

	/* read the data */
	SPDR=data;

	/* polling tell the data is send*/
	while(BIT_IS_CLEAR(SPSR,SPIF));

	/* return the data */
	return SPDR;
}

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str)
{
	uint8 i = 0;

	/* a temp value to store the recived data in it*/
	uint8 temp;

	for(i=0;str[i]!='\0';i++)
		temp=SPI_sendReceiveByte(str[i]);
}

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0;
	str[i]=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	while(str[i]!='#')
	{
		i++;
		str[i]=SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	}
	str[i]='\0';
}
