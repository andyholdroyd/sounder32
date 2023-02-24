/*!
 * \file sounder.h
 * \brief header file for sounder.c
 *
 * \author Phil Lane
 * \date 19 December 2017
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
 * 1.0   12.2017  PSL     Move PoC files to new directory structure
 * 1.1   02.2018  PSL     Convert to new chip
 *
 * Module Description :
 * sounder.h is the header file for sounder.c
 *
*/ 
void Sounder_ChangeTone(uint8_t tone_num );
void Sounder_Activation( char enable );


typedef struct
{
	int16_t  start;
	int16_t  range;	
	int16_t 	length;
} FreqDef;

typedef struct
{
		FreqDef   freq[ 2];
  
		uint8_t 	repetitions;
		uint8_t 	pulseLength;
		uint16_t	silenceMs;
} ToneDefinition;


 

/*****************************END OF FILE**************************************/
