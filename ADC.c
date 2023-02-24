/*!
 * \file ADC.c
 * \brief All functions for setup and control of ADC
 *
 * \author Phil Lane
 * \date 06 Marcg 2018
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
 * 1.0   03.2018  PSL     Split from main
 *
 * Module Description :
 * Contains all the functions to control and configure the ADC's used
 *
 *
*/

/* Include files **************************************************************/
//#include "STM8L051F3.h"

#include "stm_header.h" // stm8l15x.h"
#include "sounder.h"
#include "usart.h"
#include "ADC.h"
#include "gpio.h"

/* Defines ********************************************************************/

// ADC channel used for IDD measurement is channel 19
#define ADC_IDD_MEASUREMENT_CHANNEL     ADC_Channel_19

// Channel 19 is a slow channel
#define ADC_GROUP_SPEEDCHANNEL          ADC_Group_SlowChannels


/* Global variables ***********************************************************/
uint8_t	reqADC = 0;				//!< Has an ADC value been requested ?
extern uint8_t	mic;

/* Private function prototypes ************************************************/
char ToChar(uint8_t val);

/* Functions ******************************************************************/
void ADC_Config(void)
{
	// Enable ADC1 clock
	CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
	
	// Initialise and configure ADC1
	ADC_Init(ADC1, ADC_ConversionMode_Continuous, ADC_Resolution_12Bit, ADC_Prescaler_2);
	ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);

	
	// Enable ADC1 Channel 15
	//ADC_ChannelCmd(ADC1, ADC_Channel_15, ENABLE);		// Piezo
	ADC_ChannelCmd(ADC1, ADC_Channel_14, ENABLE);		// Microphone
	//ADC_ChannelCmd(ADC1, ADC_Channel_13, ENABLE);		// SPL_TRIG
	
	// Enable End of conversion ADC1 Interrupt
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	
	// Start ADC1 Conversion using Software trigger
	ADC_SoftwareStartConv(ADC1);

	// Disable ADC1
	ADC_Cmd(ADC1, DISABLE);
}



uint8_t	ADC_GetValue(void)
{
	uint16_t	ADC_value = 0;				//!< Current ADC value
	uint8_t	result = 0;
	
	// Value has been requested, but is it ready yet ?
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET)
	{
		ADC_value = ADC_GetConversionValue(ADC1);
		result = 1;
	}
	
	return result;
}

void ADC_Activation( char enable )
{	
	mic = enable;
	ADC_Cmd(ADC1, enable);
	
	if ( enable )
	{
		USART_SendString("MIC on\r\n"); 
		ADC_SoftwareStartConv(ADC1);
		
		GPIO_HIGH(VMIC_PORT, VMIC_SHDN);
	}
	else
	{
		USART_SendString("MIC off\r\n");		
		
		GPIO_LOW(VMIC_PORT, VMIC_SHDN);
	}		
}

/*****************************END OF FILE**************************************/
