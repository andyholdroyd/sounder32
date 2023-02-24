/*!
 * \file timers.c
 * \brief Routines to configure and control timers
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
 * 1.0   03.2018  PSL     Split from sounder and interrupt code
 *
 * Module Description :
 * Contains all the routines to configure and control timers
 *
*/

/* Include files **************************************************************/
#include "stm_header.h"   // "stm8l15x.h"
#include "timers.h"

/* Defines ********************************************************************/
  //TIM3_RELOAD USED TO BE 50400 * 5 
/* External variables *********************************************************/
 
extern uint8_t			pulseLen;
 
 
/* Global variables ***********************************************************/
 
/* Function prototypes ********************************************************/
 
/* Functions ******************************************************************/

void Timers_Config( void )
{
	// TIM4 is the LED and tone adjustment 
	TIM4_TimeBaseInit( TIM4_Prescaler_128, 125 );
	TIM4_ClearFlag( TIM4_FLAG_Update );
	TIM4_ITConfig( TIM4_IT_Update, ENABLE );
	TIM4_Cmd( DISABLE );
  
	TIM3_SelectOCxM( TIM3_Channel_2,TIM3_OCMode_Inactive );
}

	
/*! \fn void TIM3_ConfigWave( uint16_t period, uint8_t pulse_usec )
 * \brief  Configure TIM3 peripheral   
 * \param  period : Timing period
 * \return None
*/
void Timers_ConfigWave(uint16_t period, uint8_t pulse_usec )
{
	TIM3_TimeBaseInit(TIM3_Prescaler_64, TIM3_CounterMode_Up, period);
	
	pulseLen = (TIM3_RELOAD * pulse_usec) / 1000000;
		
	TIM3_OC1Init( TIM3_OCMode_PWM1, TIM3_OutputState_Enable, pulseLen, TIM3_OCPolarity_High, TIM3_OCIdleState_Set );
}
 

/*****************************END OF FILE**************************************/
