/*!
 * \file flash.c
 * \brief Routines to create and control the clocks
 *
 * \author Phil Lane
 * \date 07 March 2018
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
 * 1.0   03.2018  PSL     Copied from beacon
 *
 * Module Description :
 * Routines to allow access to flash memory
 *
*/

/* Include files **************************************************************/
#include "stm_header.h"   // "stm8l15x.h"
#include "stm32c0xx_hal_flash.h" // andymod stm8l15x_flash.h"
#include "flash.h"

/* Defines ********************************************************************/
#define DATA_EEPROM		((uint32_t)0x00001000)	//!< Data Eeprom: start address

/* External variables *********************************************************/

/* Private typedef -----------------------------------------------------------*/
/*!
 * \struct _tagSAVEDATA
 *
 * \brief Used to store data in flash
 *
 */
typedef struct _tagSAVEDATA 
{
	uint8_t	type;		//!< Detector type
	uint8_t	enabled;	//!< Enabled / Disabled
	uint8_t	test;		//!< On / off test
	uint8_t	flash;	//!< Flash rate (0 - 63)
	uint8_t	tone;		//!< Tone Selection (1 - 33)
	uint8_t	spl;		//!< Sound pressure level (????)
	uint8_t	sno_1;	//!< Serial Number bits  0 -  7
	uint8_t	sno_2;	//!< Serial Number bits  8 - 15
	uint8_t	sno_3;	//!< Serial Number bits 16 - 23
	uint8_t	sno_4;	//!< Serial Number bits 24 - 31
} SAVEDATA;

/* Global variables ***********************************************************/
SAVEDATA	self;						//!< Struct to store data in flash

/* Function prototypes ********************************************************/

/* Sound Data *****************************************************************/

/* Functions ******************************************************************/

 
/*! \fn uint8_t ReadByte(uint32_t address)
 * \brief  read a byte from flash memory   
 * \param  address : where to write the value, just a number, NOT A POINTER
 * \return value written
*/
uint8_t ReadByte(uint32_t address)
{
	uint8_t	byte;
	
	/* Define flash programming Time*/
	FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
	
	/* Unlock flash data eeprom memory */
	FLASH_Unlock(FLASH_MemType_Data);
	
	/* Wait until Data EEPROM area unlocked flag is set*/
	while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
	{}	
	
	byte = FLASH_ReadByte(address);

	FLASH_Lock(FLASH_MemType_Data);
	
	return byte;
}

/*! \fn void ReadType(void)
 * \brief  Read type from flash memory 
 * \return None
*/
void ReadType(void)
{
	self.type = ReadByte(DATA_EEPROM + 0);
}

/*! \fn void ReadEnabled(void)
 * \brief  Read Enabled from flash memory   
 * \return None
*/
void ReadEnabled(void)
{
	self.enabled = ReadByte(DATA_EEPROM + 1);
}

/*! \fn void ReadTest(void)
 * \brief  Read test from flash memory  
 * \return None
*/
void ReadTest(void)
{
	self.test = ReadByte(DATA_EEPROM + 2);
}

/*! \fn void ReadFlash(void)
 * \brief  Read flash freqency from flash
 * \return None
*/
void ReadFlash(void)
{
	self.flash = ReadByte(DATA_EEPROM + 3);
}

/*! \fn void ReadTone(void)
 * \brief  Read Tone Number from flash
 * \return None
*/
void ReadTone(void)
{
	self.flash = ReadByte(DATA_EEPROM + 4);
}

/*! \fn void ReadSPL(void)
 * \brief  Read SPL from flash
 * \return None
*/
void ReadSPL(void)
{
	self.flash = ReadByte(DATA_EEPROM + 5);
}

/*! \fn void ReadSNo_1(void)
 * \brief  Read part one of the serial number from flash
 * \return None
*/
void ReadSNo_1(void)
{
	self.flash = ReadByte(DATA_EEPROM + 6);
}

/*! \fn void ReadSNo_2(void)
 * \brief  Read part two of the serial number from flash
 * \return None
*/
void ReadSNo_2(void)
{
	self.flash = ReadByte(DATA_EEPROM + 7);
}

/*! \fn void ReadSNo_3(void)
 * \brief  Read part three of the serial number from flash
 * \return None
*/
void ReadSNo_3(void)
{
	self.flash = ReadByte(DATA_EEPROM + 8);
}

/*! \fn void ReadSNo_4(void)
 * \brief  Read part four of the serial number from flash
 * \return None
*/
void ReadSNo_4(void)
{
	self.flash = ReadByte(DATA_EEPROM + 9);
}

/*! \fn void WriteMem(uint32_t Address, uint8_t Data)
 * \brief  Write byte to internal flash memory
 * \param  Address Where to write memory too, just a number, NOT A POINTER
 * \param  Data Byte to write to flash
 * \return None
*/
void WriteMem(uint32_t Address, uint8_t Data)
{
	/* Define flash programming Time*/
	FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
	
	/* Unlock flash data eeprom memory */
	FLASH_Unlock(FLASH_MemType_Data);
	
	/* Wait until Data EEPROM area unlocked flag is set*/
	while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
	{}
	
	FLASH_ProgramByte(Address, Data);
	FLASH_Lock(FLASH_MemType_Data);
}

/*! \fn void WriteType(void)
 * \brief  Write type to internal flash memory
 * \return None
*/
void WriteType(void)
{
	WriteMem(DATA_EEPROM + 0, self.type);
}

/*! \fn void WriteEnabled(void)
 * \brief  Write "enabled" to flash memory
 * \return None
*/
void WriteEnabled(void)
{
	WriteMem(DATA_EEPROM + 1, self.enabled);
}

/*! \fn void WriteTest(void)
 * \brief  Write test to flash memory
 * \return None
*/
void WriteTest(void)
{
	WriteMem(DATA_EEPROM + 2, self.test);
}

/*! \fn void WriteFlash(void)
 * \brief  Write Flash Frequency to flash memory
 * \return None
*/
void WriteFlash(void)
{
	WriteMem(DATA_EEPROM + 3, self.flash);
}

/*! \fn void WriteTone(void)
 * \brief  Write Tone number to flash memory
 * \return None
*/
void WriteTone(void)
{
	WriteMem(DATA_EEPROM + 4, self.flash);
}

/*! \fn void WriteSPL(void)
 * \brief  Write SPL (volume) to flash memory
 * \return None
*/
void WriteSPL(void)
{
	WriteMem(DATA_EEPROM + 5, self.flash);
}

/*! \fn void WriteSNo_1(void)
 * \brief  Write part one of the serial number to flash memory
 * \return None
*/
void WriteSNo_1(void)
{
	WriteMem(DATA_EEPROM + 6, self.flash);
}

/*! \fn void WriteSNo_2(void)
 * \brief  Write part two of the serial number to flash memory
 * \return None
*/
void WriteSNo_2(void)
{
	WriteMem(DATA_EEPROM + 7, self.flash);
}

/*! \fn void WriteSNo_3(void)
 * \brief  Write part three of the serial number to flash memory
 * \return None
*/
void WriteSNo_3(void)
{
	WriteMem(DATA_EEPROM + 8, self.flash);
}

/*! \fn void WriteSNo_4(void)
 * \brief  Write part four of the serial number to flash memory
 * \return None
*/
void WriteSNo_4(void)
{
	WriteMem(DATA_EEPROM + 9, self.flash);
}

/*****************************END OF FILE**************************************/
