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
 * created date : 13/10/2022
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
	RISING_EDGE_DETECT,FALLING_EDGE_DETECT
}edge_Type;

typedef enum
{
	FOSC_4,FOSC_16,FOSC_64,FOSC_128,FOSC_2,FOSC_8,FOSC_32
}CLK_freq;

typedef enum
{
	MSB,LSB
}master_send_bit;

#define SPI_DEFAULT_DATA_VALUE  0xFF

#define MISO_PORT				PORTB_ID
#define MISO_PIN				PIN6_ID

#define MOSI_PORT				PORTB_ID
#define MOSI_PIN				PIN5_ID

#define SCLK_PORT				PORTB_ID
#define SCLK_PIN				PIN7_ID

#define SS_PORT					PORTB_ID
#define SS_PIN					PIN4_ID

/*******************************************************************************
 *                                FUNCTIONS                                  *
 *******************************************************************************/

/*
 * Description :
 * A function to initialize the master
 */
void SPI_init_master(edge_Type edge,CLK_freq clk,master_send_bit bit);
/*
 * Description :
 * A function to initialize the slave
 */
void SPI_init_slave(edge_Type edge,CLK_freq clk,master_send_bit bit);

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
