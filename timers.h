/*!
 * \file timers.h
 * \brief header file for timers.c
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
 * 1.0   03.2017  PSL     Split from sounder.c and interrupts
 *
 * Module Description :
 * sounder.h is the header file for sounder.c
 *
*/

#define TIM3_RELOAD (252000) 
#define TIM3_RELOAD_DIV4 (63000U)

/* Function prototypes ********************************************************/
//void	TIM1_SetPeriodMs(uint16_t timMs);

void Timers_Config( void );

void Timers_ConfigWave(uint16_t period, uint8_t pulse_usec );

 

/* Enums ---------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Defines ********************************************************************/


/*****************************END OF FILE**************************************/
