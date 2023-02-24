/*************************************************************************************
*  CONFIDENTIAL Bull Products Ltd.
**************************************************************************************
*  Cygnus2
*  Copyright 2019 Bull Products Ltd. All rights reserved.
*  Beacon House, 4 Beacon Rd
*  Rotherwas Industrial Estate
*  Hereford HR2 6JF UK
*  Tel: <44> 1432806806
*
**************************************************************************************
*  File         : I2C.c
*
*  Description  : Implementation file for the I2C interface
*
* The information contained herein is confidential property of Bull Products Ltd
* The use, copying, transfer or disclosure of such information is prohibited 
* except by express written agreement with Bull Products Ltd.
*************************************************************************************/

/* Include files **************************************************************/
#include "registers.h"
#include "I2C.h"


/* Defines ********************************************************************/

/* Global variables ***********************************************************/
uint8_t i2cRxBuffer[ MAX_BUFFER ];

/* Private variables ---------------------------------------------------------*/
uint8_t *pRxBuffer;
uint8_t messageBegin;

/* Private function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/

/*******************************************************************************
*
* I2C_byte_received
* Accepts a byte and adds it to the Rx Buffer.
*
* param - RxData	The data byte to be added to the Rx Buffer
*
* return - None.
*******************************************************************************/
void I2C_ByteReceived(uint8_t rxData)
{
	if ( messageBegin == TRUE )
	{
		pRxBuffer = i2cRxBuffer;
		*pRxBuffer = rxData;
		pRxBuffer++;
		messageBegin = FALSE;
	}
	else if ( pRxBuffer < i2cRxBuffer + MAX_BUFFER )
	{
		*pRxBuffer = rxData;
		pRxBuffer++;
	}
}


// ************************* I2C init Function  *************************

/*******************************************************************************
*
* Init_I2C
* Set up the I2C interface for normal operation.
*
* param - None
*
* return - None.
*******************************************************************************/

/*	andymod, extensive changes
void I2C_Config(void)
{
	
	I2C1->CR1   = 0x00;						// Disable I2C peripheral
	
	CLK->CKDIVR = 0;							// sys clock /1
	CLK->PCKENR1 |= 0x08;					// enable I2C peripheral clk

	// andymod  changed gpioc to gpiob 
	// Init GPIO for I2C use
	GPIOB->DDR &= ~0x03;					// Input mode for PC0 and PC1
	GPIOB->CR1 |= 0x03;						// pull up
	GPIOB->CR2 &= ~0x03;					// Ext interrupts disabled

	
	// Cannot change I2C1 parameters if it is not active!
	I2C1->CR1   |= 0x01;									// Enable I2C peripheral
	I2C1->CR2   = 0x04;					     			// Enable I2C acknowledgement
	I2C1->FREQR = 10; 					     			// Set I2C Freq value (16MHz)
	I2C1->OARL  = (SLAVE_ADDRESS << 1) ;	// set slave address (put 0xA2 for the register dues to7bit address) 
	I2C1->OAR2 = 0x00;										//Only use primary address
	I2C1->OARH  = 0x40;					     			// Set 7bit address mode
	I2C1->ITR	= 0x07;					      			// all I2C interrupt enable
	// Set the clock control register (CCR)
	I2C1->CCRL = 0x32;         						// 0x50 Provides an output clock of 100kHz...
	I2C1->CCRH = (uint8_t)0;          		// ...at 50% duty cycle
	
}


/*****************************END OF FILE**************************************/
