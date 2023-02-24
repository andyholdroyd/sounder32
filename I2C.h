/*!
 * \file I2C.h
 * \brief header file for I2C.c
 *
 * \author Phil Lane
 * \date 06 March 2018
 *
 *******************************************************************************
 * Copyright 2017 Bull Products Ltd as an unpublished work
 * All Rights Reserved.
 *
 * The information contained herein is confidential property of Bull Products Ltd
 * The use, copying, transfer or disclosure of such information is prohibited 
 * except by express written agreement with Bull Products Ltd.
 *******************************************************************************
 *
 * File History :
 * Rev   Date     Author  Description
 * 1.0   03.2018  PSL     Split from sounder.h
 *
 * Module Description :
 * I2C.h is the header file for I2C.c
 *
*/
#define MAX_BUFFER  8

extern uint8_t i2cRxBuffer[MAX_BUFFER];
extern uint8_t messageBegin;

/* Function prototypes ********************************************************/
//void I2C_Config(void);
void I2C_Config(void);
 
void I2C_ByteReceived(uint8_t RxData);

/* Enums ---------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Defines ********************************************************************/
//#define SLAVE_ADDRESS	0x10			//!< I2C address of this device	// RM: as before
#define SLAVE_ADDRESS	0x08			//!< I2C address of this device		// RM: Updated to match Salve Address 0x08 the Master is using

/*****************************END OF FILE**************************************/
