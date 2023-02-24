/*!
 * \file sounder.c
 * \brief Routines to create the required sound waves
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
 * Contains all the routines to create the required sound waves
 *
*/

/* Include files **************************************************************/
#include "stm_header.h"   // "stm8l15x.h"
#include "sounder.h"
#include "timers.h"
#include "gpio.h"
#include "registers.h"
#include "usart.h"
/* Defines ********************************************************************/
 

/* External variables *********************************************************/




/* Global variables ***********************************************************/

uint8_t	sound = 0;			//!< Making noise

 
extern uint8_t nosound_count;
 
const ToneDefinition tone_list[ ] = { 
	{{{  554,    0,  100 }, { 440,    0,  400 }}, 1, 200,    0 },   // 1	554Hz, 0.1s / 440Hz, 0.4s (AFNOR NF S 32 001)
	{{{  500,  700, 3500 }, {   0,    0,  500 }}, 1, 200,    0 },   // 2  500 - 1200hZ, 3.5s / 0.5 OFF
	{{{  420,    0,  625 }, {   0,    0,  625 }}, 1, 200,    0 },   // 3	420Hz 0.625s ON / 0.625s OFF (Australia AS1670 Alert tone)
	{{{  500,  700,  500 }, {   0,    0,  500 }}, 3, 200, 1000 },   // 4	500 - 1200Hz, 0.5s / 0.5s OFF x3 / 1.5s OFF (AS1670 Evacuation)
	{{{  970,    0,  500 }, {   0,    0,  500 }}, 3, 200, 1000 },   // 5	970Hz, 0.5s ON / 0.5s OFF x3 / 1.5s OFF (ISO 8201)
	{{{ 2850,    0,  500 }, {   0,    0,  500 }}, 3, 150, 1000 },   // 6	2850Hz, 0.5s ON / 0.5s OFF x3 / 1.5s OFF (ISO 8201 (US temporal HF))
	{{{ 1200, -700, 1000 }, {1200, -700, 1000 }}, 1, 200,    0 },   // 7	1200Hz - 500Hz @ 1Hz (DIN 33 404)
	{{{  500,  700, 3750 }, {   0,    0,  250 }}, 1, 200,    0 },   // 8	500Hz - 1200Hz, 3.75s / 0.25s OFF (AS2220)
	{{{  800,    0, 1000 }, { 800,    0, 2000 }}, 7, 200,    0 },   // 9	800 Hz continuous (LF contniuous tone BS5839)
	{{{  970,    0,  500 }, {   0,    0,  500 }}, 1, 200,    0 },   // 10 970 Hz 0.5s ON/0.5s OFF (ISO 8201 LF BS5839 Pt1 1988)
	{{{ 2850,    0,  500 }, {   0,    0,  500 }}, 1, 150,    0 },   // 11 2850Hz 0.5s ON/OFF (ISO 8201 HF)
	{{{  660,    0,  150 }, {   0,    0,  150 }}, 1, 200,    0 },   // 12 660Hz 0.15s ON / 0.15s OFF (Sweedish fire signal)
	{{{  660,    0, 1000 }, { 660,    0, 2000 }}, 7, 200,    0 },   // 13 660Hz (Swedish All clear signal)
	{{{  800,    0,  250 }, { 970,    0,  250 }}, 1, 200,    0 },   // 14 800Hz/970Hz @ 2Hz (FP 1063.1 Telecom)- Default Fire Tone
	{{{ 1000, 1500,  500 }, {  0,     0,  500 }}, 3, 150, 1000 },   // 15 1000 - 2500Hz, 0.5s / 0.5s OFF x3 / 1.5s OFF (AS1670 Evacuation)
	{{{  950,    0,  500 }, {   0,    0,  500 }}, 3, 200, 1000 },   // 16 950Hz 0.5s ON/ 0.5s OFF x 3 / 1.5s OFF repeat (US temporal LF)
	{{{  970,    0, 1000 }, { 970,    0, 2000 }}, 7, 200,    0 },   // 17 970Hz continuous
	{{{  800,  170,  333 }, { 800,  170,  333 }}, 1, 200,    0 },   // 18 800Hz - 970Hz @ 3Hz
	{{{  800,  170,  111 }, { 800,  170,  111 }}, 1, 200,    0 },   // 19 800Hz - 970Hz @ 9Hz
	{{{ 2400,    0, 1000 }, {2400,    0, 2000 }}, 7, 150,    0 },   // 20 2400Hz continuous
	{{{  970,    0,  500 }, { 630,    0,  500 }}, 1, 200,    0 },   // 21 970Hz, 0.5s / 630Hz, 0.5s
	{{{  800,  170, 1000 }, { 800,  170, 1000 }}, 1, 200,    0 },   // 22 800Hz - 970Hz @1Hz
	{{{  800,    0,  500 }, { 970,    0,  500 }}, 1, 200,    0 },   // 23 800Hz / 970Hz @ 1Hz 
	{{{ 2400,  500,  111 }, {2400,  500,  111 }}, 1, 150,    0 },   // 24 2400Hz - 2900Hz @ 9Hz
	{{{ 2400,  500,  333 }, {2400,  500,  333 }}, 1, 150,    0 },   // 25 2400Hz - 2900Hz @ 3Hz
	{{{  800,    0,  250 }, { 630,    0,  250 }}, 1, 200,    0 },   // 26 Dual tone 800/630 Hz @2Hz
	{{{  400,    0, 1000 }, { 400,    0, 2000 }}, 7, 200,    0 },   // 27 400Hz continuous
	{{{  550,    0, 1000 }, { 440,    0, 1000 }}, 1, 200,    0 },   // 28 550Hz / 440Hz @ 0.5Hz
	{{{ 1500, 1200,  333 }, {1500, 1200,  333 }}, 1, 150,    0 },   // 29 1500Hz - 2700Hz @ 3Hz
	{{{  550,    0,  700 }, {1000,    0,  330 }}, 1, 200,    0 },   // 30 550Hz, 0.7s / 1000Hz, 0.33s
	{{{  250,  950,   83 }, { 250,  950,   83 }}, 1, 200,    0 },   // 31 250Hz - 1200Hz @ 12Hz
	{{{  800,    0,  500 }, {1000,    0,  500 }}, 1, 200,    0 },   // 32 800 / 1000Hz 0.5s each (1Hz)
	{{{  800,    0,  250 }, { 970,    0,  250 }}, 2, 200, 7000 },   // 33 Dual tone 800/970 Hz @2Hz - 1s ON / 7s OFF - Default First Aid tone
	{{{    0,    0, 1000 }, {   0,    0, 1000 }}, 1, 200,10000 },   // 34 Silent tone 0 HZ  continuous 
	{{{  800,    0,  100 }, {   0,    0, 2000 }}, 1, 200, 2000 },   // 35 800Hz 0.1s ON / 2s OFF   
	{{{ 2200, 1300,  125 }, {3500,-1300,  125 }}, 1, 150,    0 }    // 36 2200Hz - 3500Hz 125ms / 3500Hz - 2200Hz 125ms (Cygnus 1 tone)
} ;
 
 

ToneDefinition* tone_ptr = tone_list;

int32_t 	mscount = 0;
uint8_t 	tone_index = 0;
uint8_t 	repetitions = 0;
uint16_t 	silencecount = 0;

extern uint16_t	   NumADCSamples;
extern uint16_t 	loudestADCSample;
extern char 			sound_on;
extern char 			led_on;

/*! \fn void Sounder_Activation( char enable )
 * \brief change tone style   
 * \param  wav : tone 1-35
 * \return None
*/
void Sounder_Activation( char enable )
{
	sound_on = enable;
									
	TIM3_Cmd( enable );
	TIM3_CtrlPWMOutputs( enable );
	
	if ( enable )
	{
		USART_SendString("Sound on\r\n");
		
		GPIO_HIGH(PIEZO_PORT, PIEZO_SHDN);
		GPIO_HIGH(PWM_PORT, TONE_PWM);	
		
		TIM4_Cmd(ENABLE);
	}
	else
	{
		USART_SendString("Sound off\r\n");
		
		GPIO_LOW(PIEZO_PORT, PIEZO_SHDN);	
		GPIO_LOW(PWM_PORT, TONE_PWM);
		
		if ( !led_on ) TIM4_Cmd(DISABLE);
	}
}
 
 
/*! \fn void ChangeTone(uint8_t wav)
 * \brief change tone style   
 * \param  wav : tone 0-34
 * \return None
*/
 
void Sounder_ChangeTone(uint8_t tone_num )
{
	USART_SendValue( "Tone:", tone_num + 1 );
			
	nosound_count = 0;
	loudestADCSample = 0;
	NumADCSamples = 0;
	
	if ( tone_num >= ( sizeof( tone_list ) / sizeof(*tone_list ) ) )
	{
		return;
	}
	
	tone_ptr = tone_list + tone_num ;
  	
	tone_index = 0;
	mscount = 0;
	repetitions = 0;
	silencecount = 0;
	    

	if ( tone_ptr->freq[ tone_index].start != 0 )
		Timers_ConfigWave( TIM3_RELOAD / tone_ptr->freq[ tone_index].start, tone_ptr->pulseLength );
 
	TIM3_ARRPreloadConfig( ENABLE );
	TIM3_OC1PreloadConfig( ENABLE );
	 
}

 

/*****************************END OF FILE**************************************/
