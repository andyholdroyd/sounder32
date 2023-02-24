/*!
 * \file main.c
 * \brief starting point and main loop for the program
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
 * 1.2	 06.2019	PC			Added I2C interface
 *
 * Module Description :
 * stm8_interrupt_vector.c contains all the interrupt routines
 *
 * Note: 
 * Compile with "Long Stack (+modsl0)" option, not "Short Stack (+mods0)"
 * This memory model will place all variables into the .data & .bss segments 
 * which should give you about 1.5K bytes for your variables.
 *
 * OLD CHIP:
 * Rx = PC2 (connect to PC Tx)
 * Tx = PC3 (connect to PC Rx)
 * PWM = PB0
 * TIM = PD2
 *
*/

//#define ENABLE_USART_COMMANDS //uncomment this to disable I2C interface and enable USART commands

/* Include files **************************************************************/
#include "stm_header.h"   // "stm8l15x.h"
#include "utils.h"
#include "sounder.h"
#include "usart.h"
#include "ADC.h"
#include "timers.h"
#include "clock.h"
#include "gpio.h"
#include "I2C.h"
#include "registers.h"
// #include "led.h"	// andymod	removed line

/* Defines ********************************************************************/
#define CR 					0x0D			//!< Carriage Return (ASCII)
#define LF 					0x0A			//!< Line Feed (ASCII)

#define BIT_0				0x01
#define BIT_1				0x02

#define MAX_ADC_SAMPLES 4000

#define MINIMUM_SIGNAL 400

#define PWM_MAX 99
#define PWM_MIN 1

#define MAX_NO_SOUND 20

/* Global variables ***********************************************************/
char	reply[MAX_REPLY];		//!< Reply to radio buffer
int		numReply = 0;			//!< Size of reply
uint8_t	sound_on = 0;			//!< 1 = sound on, 0 = sound off
uint8_t	mic = 0;					//!< 1 = microphone & ADC on, 0 = mic. & ADC off
uint8_t infault = 0;
uint8_t current_pulse_width = 0;
uint8_t percentage = 50;
uint8_t nosound_count = 0;
  
unsigned long int i;



uint8_t flash_rate = 1;

//#ifdef ENABLE_USART_COMMANDS
const char	menu[] = "\r\n\r\n"
						VERSION_STR
						"\r\n[1-35]=Tones\r\n"  
						"[u,l,m,h]=SPL UL/L/M/H\r\n" 
						"[a,d]=Sounder on/off\r\n" 
						"[z,f,x,p]=LED on 1s/on 0.5s/off/PWM\r\n"
						"[c,v]=MIC on/off\r\n"
						"[q,w,e,r,t]=PL, 50%, (10, 50, 150, 250)us\r\n"
						"[+,-]=PW +/- 1%\r\n"
						"[++,--]=PW +/- 10%\r\n"
						"[s]=Sleep\r\n"
						"[h]=Halt\r\n"
						"[option][RETURN]\r\n";
					
//#else
//const char		menu[] = "\r\n\r\n"
//						VERSION_STR
//						"\r\nI2C interface enabled\r\n\r\n";
//#endif 

extern volatile uint8_t	SPL_Trig;	//!< SPL Trigger, 1 = trigger activated
extern uint16_t		NumADCSamples;              
extern uint16_t		loudestADCSample;		//!< Max ADC value
extern uint8_t		led_on;		//!< 2=LED PWM Flash, 1=LED on, 0=LED off
extern uint8_t		recvPacket;	//!< Flag to indicate we have received a packet
extern uint16_t		LEDCounter;	//!< Flash, PWM counter for LED
extern uint8_t  	i2cRxBuffer[MAX_BUFFER];
extern uint8_t 		registerUpdated;
extern bool 			registerChanged[SVI_REG_PARAMETER_TYPE_MAX_E];

/* Private function prototypes ************************************************/
static void 			DecodePacket(char *packet);
static void 			ProcessRegisterChange(void);

 

/* Public function prototypes ************************************************/
int main(void);

/* Functions ******************************************************************/

/*! \fn void main(void)
 * \brief  Entry into program, main loop   
 * \return None
*/
int main_8(void)
{
	char		packet[MAX_RECV] = "";	//!< UART Receive packet

	uint8_t	adcwait = 0;
	uint8_t	spl_trig;
	
	// Configuration ------------------------------------------------------------
	Clock_Config();
	USART_Config();
	
	GPIO_Config();
	ADC_Config();
	I2C_Config();
	Regs_Config();
	Timers_Config();

	// Set to lowest volume
	GPIO_LOW(SPL_PORT, SPL_SEL_L);
	GPIO_LOW(SPL_PORT, SPL_SEL_M);
       
	USART_SendString( (char*) menu );
	
	enableInterrupts();
	
	// Main Loop ----------------------------------------------------------------
	while (1)
	{	
		// Anything in the usart receive buffer ?
		if (recvPacket == 1)
		{
			memset(packet, 0, MAX_RECV);
			USART_ReceivePacket(packet, MAX_RECV);
			DecodePacket(packet);
			recvPacket = 0;
		}

		/* Has I2C updated any of the interface registers? */
		if ( registerUpdated )
		{
			ProcessRegisterChange();
			registerUpdated--;
		}
		
/*		 
		if ( mic && sound_on && TIM3->CCR1L )
		{
			if ( NumADCSamples > MAX_ADC_SAMPLES )
			{
				// Copy value now to prevent it changing while we report old value
				 
				USART_SendValue( "Max:", loudestADCSample );
				
				if ( loudestADCSample < MINIMUM_SIGNAL )
				{
					if ( !infault )
					{
				    Regs_SetRegisterValue( REG_ADDRESS_FAULT_STATUS, 1 );
					  USART_SendString("Setting fault reg.\n" );
					  infault = 1; 
					}
				}
				else if ( infault )
				{
					 Regs_SetRegisterValue( REG_ADDRESS_FAULT_STATUS, 0 );
					 USART_SendString("UnSetting fault.\n" );
					 infault = 0; 
			  }
				
				loudestADCSample = 0;
				NumADCSamples = 0;
			}
		}
	andymod		*/

	}
  
}
 
  
/*! \fn void DecodePacket(char *packet)
 * \brief  Decodes radio commands   
 * \param  *packet : Points to packet.
 * \return None
*/
void DecodePacket(char *packet)
{
	uint8_t	i;
	uint8_t	val;
	uint8_t	tone;
	uint8_t	sleep = 0;

//#ifdef ENABLE_USART_COMMANDS

	reply[0] = 0;
	
	// --- Single char command ---
	if (packet[1] == '\r')
	{
		// --- Single digit wave command ---
		if ((packet[0] >= '1') &&
			 (packet[0] <= '9'))
		{						
			tone = packet[0] - '1';
		 			
			Sounder_ChangeTone( tone );
		}	
		// --- ULow SPL ---
		else if ((packet[0] == 'u') || (packet[0] == 'U'))
		{
			USART_SendString( "Ulow\r\n" );
			GPIO_LOW(SPL_PORT, SPL_SEL_L);
			GPIO_LOW(SPL_PORT, SPL_SEL_M);
		}
		// --- Low SPL ---
		else if ((packet[0] == 'l') || (packet[0] == 'L'))
		{
			USART_SendString( "Low\r\n" );
			GPIO_HIGH( SPL_PORT, SPL_SEL_L );	
			GPIO_LOW( SPL_PORT, SPL_SEL_M );
		}
		// --- Medium SPL ---
		else if ((packet[0] == 'm') || (packet[0] == 'M'))
		{
			USART_SendString( "Med\r\n");
			GPIO_LOW(SPL_PORT, SPL_SEL_L);
			GPIO_HIGH(SPL_PORT, SPL_SEL_M);	
		}
		// --- High SPL ---
		else if ((packet[0] == 'h') || (packet[0] == 'H'))
		{
			USART_SendString( "High\r\n");
			GPIO_HIGH(SPL_PORT, SPL_SEL_M);	
			GPIO_HIGH(SPL_PORT, SPL_SEL_L);		
		}		
		// --- Activate Sounder ---
		else if ((packet[0] == 'a') || (packet[0] == 'A'))
		{	
			Sounder_Activation( ENABLE );
		}
		// --- Deactivate Sounder ---
		else if ((packet[0] == 'd') || (packet[0] == 'D'))
		{
			Sounder_Activation( DISABLE );
		}	
		// --- LEDFlashing On ---
		else if ((packet[0] == 'p') || (packet[0] == 'P'))
		{
			LED_Activation( ENABLE );
		}
		// --- LED Flashing Off ---
		else if ((packet[0] == 'x') || (packet[0] == 'X'))
		{
			LED_Activation( DISABLE );
		}
		// --- Flash Rate
		else if ((packet[0] == 'z') || (packet[0] == 'Z'))
		{
			LED_SetFlashRate( 1 );
		}		
		else if ((packet[0] == 'f') || (packet[0] == 'F'))
		{
			LED_SetFlashRate( 2 );
		}
		// --- Microphone Off ---
		else if ((packet[0] == 'c') || (packet[0] == 'C'))
		{
			ADC_Activation( DISABLE );
		}
		// --- Microphone On ---
		else if ((packet[0] == 'v') || (packet[0] == 'V'))
		{
			ADC_Activation( ENABLE );
		}
		// --- SleepTest ---
		else if ((packet[0] == 's') || (packet[0] == 'S'))
		{
			USART_SendString( "SleepTest\r\n" );
			sleep = 1;
		}
		// --- Halt ---
		else if ((packet[0] == 'h') || (packet[0] == 'H'))
		{
			USART_SendString( "Halt\r\n" );
			sleep = 2;
		}
		else
		{
			USART_SendString( "Unknown command.\r\n" );
		}
	}
	else if (packet[2] == '\r')
	{
		// --- Two digit wave command ---
		if (((packet[0] >= '1') &&
			  (packet[0] <= '2') &&
			  (packet[1] >= '0') &&
			  (packet[1] <= '9')) ||
			 ((packet[0] == '3') &&
			  (packet[1] >= '0') &&
			  (packet[1] <= '6')))	  
		{
			// 1-36
			strcpy(reply, "Wave xx : ");
			reply[5] = packet[0];
			reply[6] = packet[1];
			
			tone = (packet[0] - '0') * 10;
			tone += packet[1] - '1';
		 		
			Sounder_ChangeTone( tone );
		}	     	
		else
		{ 
			USART_SendString( "Unknown command.\r\n" );
		}
	}
	 

	// Go to sleep
	if (sleep == 1)
	{
		wfi();
		//wfe();
	
		USART_SendString("awake\r\n");
	}
	else if (sleep == 2)
	{
		halt();
	}
}



/*******************************************************************************
*
* ProcessRegisterChange
* Called when the RBU has updated one of the interface registers over I2C.
* This function actions the RBUs commands
*
* param - None
*
* return - None.
*******************************************************************************/
void ProcessRegisterChange(void)
{
	uint8_t reg_value = 0;
	uint8_t reg_str[3];
	
	reg_str[2] = 0;// terminate the string for debug out
	
	if ( registerChanged[SVI_REG_ENABLE_E] )
	{
		// check the ENABLE register for new output commands
		if ( Regs_GetRegisterValueByIndex(SVI_REG_ENABLE_E, &reg_value) )
		{
			// activate/deactivate Sounder			 
			Sounder_Activation( reg_value & BIT_0 );
			ADC_Activation( reg_value & BIT_0  );			
			 
			LED_Activation( !!( reg_value & BIT_1 )); 
		}
		/* mark the register as up-to-date */
		registerChanged[SVI_REG_ENABLE_E] = FALSE;
	}
	
	if ( registerChanged[SVI_REG_TEST_MODE_E] )
	{
		if ( Regs_GetRegisterValueByIndex(SVI_REG_TEST_MODE_E, &reg_value) )
		{
			// --- activate test mode ---
			ADC_Activation( !!( reg_value & BIT_1 ) );			
		}
		registerChanged[SVI_REG_TEST_MODE_E] = FALSE;
	}

/* Flash rate */
	if ( registerChanged[SVI_REG_FLASH_RATE_E] )
	{
		if ( Regs_GetRegisterValueByIndex(SVI_REG_FLASH_RATE_E, &reg_value) )
		{
			//Bit 0 holds the output value for the low attenuation pin (SPL_SEL_L)
			if ( 0 == reg_value )
			{
				LED_SetFlashRate( 2);
			}
			else
			{
				// flash rate = 1s
				LED_SetFlashRate(1);
			}			  
		}
		registerChanged[SVI_REG_FLASH_RATE_E] = FALSE;
	}
	
	/* Tone selection */
	if ( registerChanged[SVI_REG_TONE_SELECT_E] )
	{
		if ( Regs_GetRegisterValueByIndex(SVI_REG_TONE_SELECT_E, &reg_value) )
		{
			Sounder_ChangeTone(reg_value);			
		}
		registerChanged[SVI_REG_TONE_SELECT_E] = FALSE;
	}

	/* Tone attenuation */
	if ( registerChanged[SVI_REG_TONE_ATTEN_E] )
	{
		if ( Regs_GetRegisterValueByIndex(SVI_REG_TONE_ATTEN_E, &reg_value) )
		{
			//Bit 0 holds the output value for the low attenuation pin (SPL_SEL_L)
			if ( reg_value & BIT_0 )
			{
				GPIO_HIGH(SPL_PORT, SPL_SEL_L);
			}
			else
			{
				GPIO_LOW(SPL_PORT, SPL_SEL_L);
			}
			
			//Bit 1 holds the output value for the high attenuation pin (SPL_SEL_M)
			if ( reg_value & BIT_1 )
			{
				GPIO_HIGH(SPL_PORT, SPL_SEL_M);
			}
			else
			{
				GPIO_LOW(SPL_PORT, SPL_SEL_M);
			}
 
			USART_SendValue("Tone atten:", reg_value );
		}
		registerChanged[SVI_REG_TONE_ATTEN_E] = FALSE;
	}
}


/*****************************END OF FILE**************************************/
