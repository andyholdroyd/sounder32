/*!
 * \file gpio.c
 * \brief Routines to configure and control GPIO
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
 * 1.0   03.2018  PSL     Split from sounder.c
 *
 * Module Description :
 * Routines to configure and control GPIO
 *
*/

/* Include files **************************************************************/
#include "stm_header.h"   // "stm8l15x.h"
// #include "stm8l15x_gpio.h"
#include "gpio.h"

/* Defines ********************************************************************/

/* External variables *********************************************************/

/* Global variables ***********************************************************/

/* Function prototypes ********************************************************/
void GPIO_Config(void);

/* Functions ******************************************************************/

/*! \fn void GPIO_Config(void)
 * \brief  Configure GPIO Channels GPIO   
 * \return None
*/

/*  andymod extensive changes

void GPIO_Config(void)
{
	// I2C
	GPIO_Init(GPIOC, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Mode_Out_OD_HiZ_Fast);
//	GPIO_Init(GPIOC, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Mode_Out_OD_Low_Fast);
	
	// Microphone
	GPIO_Init(VMIC_PORT, VMIC_SHDN, GPIO_Mode_Out_PP_High_Fast);      //How come the MIC is defined as O/P pin OMAR ????
	GPIO_LOW(VMIC_PORT, VMIC_SHDN);

	// PWM
	GPIO_Init(PWM_PORT, TONE_PWM, GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(PWM_PORT, LED_PWM, GPIO_Mode_Out_PP_Low_Fast);

	// SPL ; Sound Pressure Level
	GPIO_Init(SPL_PORT, SPL_SEL_M, GPIO_Mode_Out_PP_High_Fast);
	GPIO_Init(SPL_PORT, SPL_SEL_L, GPIO_Mode_Out_PP_High_Fast);
	GPIO_LOW(SPL_PORT, SPL_SEL_L);
	GPIO_LOW(SPL_PORT, SPL_SEL_M);
	
	// SPL Trigger
	GPIO_Init(SPL_PORT, SPL_TRIG, GPIO_Mode_In_PU_IT);
	EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Rising);
	
	// Piezo on / off - Active low
	GPIO_Init(PIEZO_PORT, PIEZO_SHDN, GPIO_Mode_Out_PP_High_Slow);
	GPIO_LOW(PIEZO_PORT, PIEZO_SHDN);
	
	//	Comparator OMAR
	GPIO_Init(SPL_PORT, SPL_TRIG, GPIO_Mode_Out_PP_Low_Slow); //Initialise PortB5 as output low push-pull OMAR(tried OD Mode but sound is very low)
	GPIO_LOW(SPL_PORT, SPL_TRIG);                               //Put PORTB5 low OMAR
	
	GPIO_Init(SPL_PORT, SPL_TRIG2, GPIO_Mode_Out_PP_Low_Slow);  //Initialise PortB2 as output low push-pull OMAR
	GPIO_LOW(SPL_PORT, SPL_TRIG2);                               //Put PORTB5 low OMAR
}

*/

/*****************************END OF FILE**************************************/
