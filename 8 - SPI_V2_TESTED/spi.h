 /******************************************************************************
 *
 * Module: SPI
 *
 * File Name: spi.h
 *
 * Description: Header file for the SPI driver
 *
 * Author: Mohamed Ezzat
 *
 * created date : 19/4/2023
 *
 * Version : v1.0.1
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

typedef enum
{
	RISING_FIRST,FALING_FIRST=1
}clk_Shape;

typedef enum
{
	FIRST_EDGE,SECOND_EDGE=1
}signal_detection;

typedef enum
{
	MSB,LSB
}first_bit;

typedef enum
{
	N_4,N_16,N_64,N_128,N_2,N_8,N_32,N_64
}prescaler_value;

typedef struct{
	clk_Shape clock;
	signal_detection signal;
	prescaler_value prescaler;
	first_bit bit;
}config;


/*******************************************************************************
 *                                FUNCTIONS                                  *
 *******************************************************************************/

/*
 * Description :
 * A function to initialize the master
 */
void SPI_init_master(const config *conf);
/*
 * Description :
 * A function to initialize the slave
 */
void SPI_init_slave(const config *conf);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
uint8 SPI_sendReceiveByte(uint8 data);
/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const uint8 *str);
/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(uint8 *str);

#endif /* SPI_H_ */
