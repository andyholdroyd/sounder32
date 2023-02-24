/*!
 * \file ADC.h
 * \brief ADC Header file
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
 * 1.0   03.2018  PSL     Split from main file
 *
 * Module Description :
 * Headre file for all ADC related functions
 *
 *
*/

/* Include files **************************************************************/
//#include "STM8L051F3.h"
#include "stm_header.h"   // "stm8l15x.h"

/* Functions ******************************************************************/
void		ADC_Config(void);
uint8_t	GetADC(void);
void		ADCDebugDec(uint16_t adc );
void ADC_Activation( char enable );

/*****************************END OF FILE**************************************/
