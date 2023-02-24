/*!
 * \file clock.h
 * \brief header file for sounder.c
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
 * clock.h is the header file for clock.c
 *
*/

/* Function prototypes ********************************************************/
void WriteType(void);
void WriteEnabled(void);
void WriteTest(void);
void WriteFlash(void);
void WriteTone(void);
void WriteSPL(void);
void WriteSNo_1(void);
void WriteSNo_2(void);
void WriteSNo_3(void);
void WriteSNo_4(void);

void WriteMem(uint32_t Address, uint8_t Data);

void ReadType(void);
void ReadEnabled(void);
void ReadTest(void);
void ReadFlash(void);
void ReadTone(void);
void ReadSPL(void);
void ReadSNo_1(void);
void ReadSNo_2(void);
void ReadSNo_3(void);
void ReadSNo_4(void);

uint8_t ReadByte(uint32_t address);
void DumpMem(void);

/* Enums ---------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Defines ********************************************************************/

/*****************************END OF FILE**************************************/
