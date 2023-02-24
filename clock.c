/*!
 * \file clock.c
 * \brief Routines to create and control the clocks
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
 * 1.0   03.2018  PSL     Split fron soundet.c
 *
 * Module Description :
 * Routines to create and control the clocks
 *
*/

/* Include files **************************************************************/

#include "stm_header.h"   // "stm8l15x.h"
#include "clock.h"

/* Defines ********************************************************************/

/* External variables *********************************************************/

/* Global variables ***********************************************************/

/* Function prototypes ********************************************************/

/* Sound Data *****************************************************************/

/* Functions ******************************************************************/

/*! \fn void CLK_Config(void)
 * \brief  Configure peripherals Clock   
 * \return None
*/
void Clock_Config( void )
{
	// system_clock / 1
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
	
	// Enable TIM2 & TIM3 clocks
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
	
	// Remap TIM2 ETR to LSE: TIM2 external trigger is controlled by LSE clock      //change from Ext CLK to Int CLK OMAR
	SYSCFG_REMAPPinConfig(REMAP_Pin_TIM2TRIGLSE, ENABLE);
	
	// Enable HSE clock
	CLK_HSEConfig(CLK_HSE_ON);	// HSERDY
	
	// Wait for LSERDY flag to be reset
	while (CLK_GetFlagStatus(CLK_FLAG_HSERDY) == RESET);
}

/*****************************END OF FILE**************************************/
