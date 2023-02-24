/*! 
 * \file stm8_interrupt_vector.c
 * \brief interrupt routines
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
 * stm8_interrupt_vector.c contains all the interrupt routines
 *
*/

/* Include files **************************************************************/
#include "stm_header.h"   // "stm8l15x.h"
#include "usart.h"
#include "timers.h"
#include "sounder.h"
#include "gpio.h"
#include "i2c.h"
#include "registers.h"

/* Defines **************************************************************/
#define LED_HALFSEC 500
#define LED_ONESEC  1000
 
extern uint8_t mic;
extern uint8_t sound_on;

extern uint8_t flash_rate;
extern ToneDefinition* tone_ptr;
extern uint8_t tone_index;

extern int32_t mscount;
extern uint8_t repetitions;
extern uint16_t silencecount;

uint8_t 		silence = 0;
uint16_t	  NumADCSamples = 0; 

/* USART ---------------------------------------------------------------------*/
/* Send buffer */
volatile char		*txBuffer = 0;	//!< Pointer to send buffer
volatile uint8_t	txCounter = 0;	//!< Number of bytes left to send
volatile uint8_t 	txSize = 0;		//!< Size of senf buffer

/* Receive buffer */
char		Slave_Buffer_Rx[MAX_RECV];		//!< Receive buffer
char		uartRxBuffer[MAX_RECV];		//!< Receive buffer
uint8_t 	rxSize = 0;					//!< Number of bytes in receive buffer
uint8_t	recvPacket = 0;			//!< Flag to indicate we have received a packet

/* New types and structs ******************************************************/
/*!
 * \brief interrupt handler function
 */
typedef void (*interrupt_handler_t)(void);

/* Structs -------------------------------------------------------------------*/
/*!
 * \struct interrupt_vector
 *
 * \brief Used to describe the interrupt vector table
 *
 */
struct interrupt_vector 
{
	unsigned char interrupt_instruction;	//!< interrupt instruction
	interrupt_handler_t interrupt_handler;	//!< interrupt handler function
};

/* External Functions *********************************************************/
extern void _stext();									//!< external function

/* External variables *********************************************************/
extern uint8_t	i2c_address;

/* Global variables ***********************************************************/
//volatile uint8_t	Slave_Buffer_Rx[155];	//!< I2C reception buffer
volatile uint8_t	tx_Idx = 0;				//!< I2C Transmit index
volatile uint8_t	rx_Idx = 0;				//!< I2C Receive index
volatile uint16_t	Event = 0x00;			//!< I2C Event type
volatile uint8_t	SPL_Trig = 0;	//!< SPL Trigger, 1 = trigger activated

int16_t	t4Cntr = 0;			//!< Timer four counter
uint16_t	loudestADCSample = 0;		//!< Max ADC value

// Sweep variables
int16_t	frqStart = 0;
int16_t	frqEnd = 0;
uint16_t	decCount = 0;
int16_t	frq = 0;
int16_t	dec = 0;
uint16_t loops = 0;
uint16_t sleep = 0;
uint8_t pulsePercent = 50; 
uint8_t	pulseLen;
uint8_t	led_on = 0;
uint16_t	LEDCounter = 0;

/* Functions ******************************************************************/

void TIM3_ConfigPeriod(uint16_t period, uint8_t pulse_usec );


////////////////////////////////////////////////////////////////////////////////
/* Interrupt routines *********************************************************/
 
/*! \fn void NonHandledInterrupt(void)
 * \brief Placeholder routine - does nothing but allows bugs to be caught.
 * \return None
 */
void NonHandledInterrupt(void)
{
	// In order to detect unexpected events during development, 
	// it is recommended to set a breakpoint on the following instruction
	return;
}

////////////////////////////////////////////////////////////////////////////////


/*! \fn void DMA1_CHANNEL0_1_IRQHandler(void)
 * \brief DMA1 channel0 and channel1 Interrupt routine.
 * \return None
 */

/*  andymod   extensive fixoing

void DMA1_CHANNEL0_1_IRQHandler(void)
{
	if(DMA1_Channel0->CSPR & DMA_CSPR_TCIF)
	{
		DMA1_Channel0->CSPR &= ~DMA_CSPR_TCIF;
	}
}

*/

/*! \fn void DMA1_CHANNEL2_3_IRQHandler(void)
 * \brief DMA1 channel2 and channel3 Interrupt routine.
 * \return None
 */
 
/*  andymod   extensive fixoing 
 
void DMA1_CHANNEL2_3_IRQHandler(void)
{
	if(DMA1_Channel3->CSPR & DMA_CSPR_TCIF)
	{
		DMA1_Channel3->CSPR &= ~DMA_CSPR_TCIF;
	}
}

*/

/*! \fn void EXTI5_IRQHandler(void)
 * \brief Catches PB5 going high.
 * \return None
 */
 
 /*	andymod
void EXTI5_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_IT_Pin5);
	SPL_Trig = 1;
	return;
}
*/

//uint16_t wavelen; 

/*! \fn void TIM4_UPD_IRQHandler(void)
 * \brief TIM4 update Interrupt routine. Counts in 1ms intervals. sets 
 * toneChange to 1, when it reaches preset value.
 * \return None
 */
void TIM4_UPD_IRQHandler(void)
{
	// Clear Interrupt Pending bit
	TIM4_ClearITPendingBit(TIM4_IT_Update);	
	
	if (led_on == 2)
  {	
		LEDCounter += flash_rate;
		
		if (LEDCounter == LED_HALFSEC)
		{
			// LED off for 0.5 seconds
			GPIO_LOW(PWM_PORT, LED_PWM);
		}
		else if ( LEDCounter >= LED_ONESEC || LEDCounter == 0 )
		{
			LEDCounter = 0;
			GPIO_HIGH(PWM_PORT, LED_PWM);
		}
	}
	
	 
	if ( !silence )
	{
		 uint16_t* w;
		
		 // calculate range from start to end freqency, Non sweepsing tones should produce range of zero. 
		 int32_t range = tone_ptr->freq[ tone_index].range;
		 
		 // Now need to multipy range by current counter
		 int32_t multiply = range * mscount;  

	   // Then divide by countre limit
		 int16_t freq =  multiply / tone_ptr->freq[tone_index].length; 
		 
		 // Now we know our frequency within range we need st add the start frequecny of course.
 		 freq += tone_ptr->freq[ tone_index].start;
	 
		 // If freqency is zero, we assujme silence
		 if ( freq == 0 )
		 {
			 // Set the pulse ength to zero -  NOTE: Polarity neeeds to be correct else could be leavnbing PWM high
			  TIM3->CCR1 = 0;	// andymod was CCR1L
	   }
		 else
		 {		
				// Calc frequency using timebase constant
				int16_t wavelen = TIM3_RELOAD / freq;
			
			
				 // Set the re-load values
	//			TIM3->ARRH = (uint8_t)(wavelen >> 8) ;
	//			TIM3->ARRL = (uint8_t)(wavelen );	
				TIM3->ARR = wavelen; 								// andymod
 			 
			   // Pulse len doesnt change, apart from when is silent so is precalced on tone selection
				TIM3->CCR1 = pulseLen;		// andymod,  was ccr1l
		 }
		 
		 w = (((uint16_t*)&mscount) + 1); 
		 (*w)++;
	   //  counter reached length 
		 if ( *w > tone_ptr->freq[tone_index].length )
		 {
			 //  reset it
			  *w = 0;
				
				//if first tone
				if ( tone_index == 0 )
				{
					// got 2nd
					tone_index = 1;
			  }
				else // if second go back to first
				{
					// go to first tone
					tone_index = 0;
 
			    // Are repitions complete?
					if ( ++repetitions >= tone_ptr->repetitions )
					{
						 repetitions = 0;
						 // Do we hve a silent period?
						 if ( tone_ptr->silenceMs > 0 )
						 {
								// Set to silent mode
								silence = 1;
								
								// Reset silent count
								silencecount = 0;
						 }
			    }
				}	 
		 }	
	}
	else // is silent mode
	{
		// Silence PWM 
		TIM3->CCR1 = 0;			// andymod,  was CCR1L

		// if silencecount has reached limit
		if ( ++silencecount > tone_ptr->silenceMs )
		{
			// Back to start/ non siloent mode
   		silence = 0;
			
			// Reset tone count
			mscount = 0;
			
			 
		}
  }	
}

/*! \fn void USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler(void)
  * \brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * \retval None
  */
void USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler(void)
{
	/* Write one byte to the transmit data register */
	/* TxCounter goes from 1 to size. 0 = special (no send)*/
			// andymod needs fixing			EVAL_COM1->DR = txBuffer[txCounter - 1];
	txCounter++;
	
	/*< Clear RXNE or TC pending bit */
	assert_param(IS_USART_CLEAR_IT(USART_IT_TC));
			// andymod needs fixing			EVAL_COM1->SR &= (uint8_t)(~USART_SR_TC);

	if (txCounter > txSize)
	{
		txCounter = 0;
		USART_DisableIT( USART_IT_TC );	
	}
}

/*! \fn void USART1_RX_TIM5_CC_IRQHandler(void)
  * \brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @retval None
  */
void USART1_RX_TIM5_CC_IRQHandler(void)
{
	char c;
	
	/* Read one byte from the receive data register and send it back */
	if (rxSize < MAX_RECV)
	{
		// andymod needs fixing				c = EVAL_COM1->DR & 0x7F;

		if (c == '\r')
		{
			recvPacket = 1;
		}
		
		uartRxBuffer[rxSize] = c;
		rxSize++;
	}
}
 
 
/*! \fn void ADC1_COMP_IRQHandler(void)
 * \brief ADC1/Comparator Interrupt routine.
 * \return None
 */
void ADC1_COMP_IRQHandler(void)
{
	// if not silent
	uint16_t	ADCvalue;	
	 
	
	GPIO_HIGH(SPL_PORT, SPL_TRIG);
	
	ADCvalue = ADC_GetConversionValue(ADC1);
	 
	if (mic && sound_on )
	if ( TIM3->CCR1 != 0 ) 				// andymod   was ->CCR1L 
	{		
		if ( ADCvalue > loudestADCSample )
		{
			loudestADCSample = ADCvalue;
		}
		NumADCSamples++; // count
	}
	GPIO_LOW(SPL_PORT, SPL_TRIG);
}



/*******************************************************************************
*
* I2C_Slave_check_event
* Interrupt handler for I2C interrupts.
*
* param - None
*
* return - None.
*******************************************************************************/
/*	andymod, extensive changes to be made , 

void I2C_IRQHandler_8(void) 	
{
	static uint8_t sr1;	
	static uint8_t sr2;
	static uint8_t sr3;	
	static uint8_t sendByte = 0;
	
	// save the I2C registers configuration
	sr1 = I2C1->SR1;
	sr2 = I2C1->SR2;
	sr3 = I2C1->SR3;
	
		// Communication error?
	if (sr2 & I2C_SR2_WUFH)
	{		
		I2C1->CR2 |= I2C_CR2_STOP;  // stop communication - release the lines
		I2C1->SR2 = 0;					// clear all error flags
	}
	else if (sr2 & I2C_SR2_OVR)
	{		
		I2C1->CR2 |= I2C_CR2_STOP;  // stop communication - release the lines
		I2C1->SR2 = 0;					// clear all error flags
	}
	else if (sr2 & I2C_SR2_BERR)
	{		
		I2C1->CR2 |= I2C_CR2_STOP;  // stop communication - release the lines
		I2C1->SR2 = 0;					// clear all error flags
	}
	else
	{	
		// More bytes received ?
		if ((sr1 & (I2C_SR1_RXNE | I2C_SR1_BTF)) == (I2C_SR1_RXNE | I2C_SR1_BTF))
		{
			I2C_ByteReceived(I2C1->DR);
		}
		
		// Byte received ?
		if (sr1 & I2C_SR1_RXNE)
		{
			I2C_ByteReceived(I2C1->DR);
		}
		
		// NAK? (=end of slave transmit comm)
		if (sr2 & I2C_SR2_AF)
		{	
			I2C1->SR2 &= ~I2C_SR2_AF;	  // clear AF
		}
		
		// Stop bit from Master  (= end of slave receive comm)
		if (sr1 & I2C_SR1_STOPF) 
		{
			I2C1->CR2 |= I2C_CR2_ACK;	  // CR2 write to clear STOPF
			Regs_SetRegisterValue( i2cRxBuffer[0], i2cRxBuffer[1]);
		}
		
		// Slave address matched (= Start Comm)
		if (sr1 & I2C_SR1_ADDR)
		{	 
			messageBegin = TRUE;
		}
		
		// More bytes to transmit ?
		if ((sr1 & (I2C_SR1_TXE | I2C_SR1_BTF)) == (I2C_SR1_TXE | I2C_SR1_BTF))
		{
			sendByte = 0;
			Regs_GetRegisterValue( i2cRxBuffer[0], &sendByte);
			I2C1->DR = sendByte;
		}
		
		// Byte to transmit ?
		if (sr1 & I2C_SR1_TXE)
		{
			sendByte = 0;
			Regs_GetRegisterValue( i2cRxBuffer[0], &sendByte);
			I2C1->DR = sendByte;
		}
	}
}

*/

//	GPIO_ToggleBits(GPIOB, GPIO_Pin_6);	// DEBUG ONLY : TP15


/*! \fn void TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler(void)
 * \brief TIM3_IT_Update Interrupt routine. Gets called each time the PWM 
 *        tone changes. Routine is enabled / disabled depending on tone.
 * \return None
 */

/*!
 * \struct _vectab
 *
 * \brief Interrupt vector table
 *
 */
 struct interrupt_vector const _vectab[] = 	//!< Interrupt vector table
{
	{0x82, (interrupt_handler_t)_stext}, // reset
	{0x82, NonHandledInterrupt},	// trap
	{0x82, NonHandledInterrupt},	// irq0
	{0x82, NonHandledInterrupt},	// irq1
	{0x82, DMA1_CHANNEL0_1_IRQHandler},	// irq2
	{0x82, DMA1_CHANNEL2_3_IRQHandler},	// irq3
	{0x82, NonHandledInterrupt},	// irq4
	{0x82, NonHandledInterrupt},	// irq5
	{0x82, NonHandledInterrupt},	// irq6
	{0x82, NonHandledInterrupt},	// irq7
	{0x82, NonHandledInterrupt},	// irq8
	{0x82, NonHandledInterrupt},	// irq9
	{0x82, NonHandledInterrupt},	// irq10
	{0x82, NonHandledInterrupt},	// irq11
	{0x82, NonHandledInterrupt},	// irq12
	{0x82, HAL_EXTI_IRQHandler},	// irq13	andymod
	{0x82, NonHandledInterrupt},	// irq14
	{0x82, NonHandledInterrupt}, 	// irq15
	{0x82, NonHandledInterrupt},	// irq16
	{0x82, NonHandledInterrupt},	// irq17
	{0x82, ADC1_COMP_IRQHandler},	// irq18
	{0x82, NonHandledInterrupt}, 	// irq19
	{0x82, NonHandledInterrupt}, 	// irq20
	{0x82, NonHandledInterrupt},	// irq21
	{0x82, NonHandledInterrupt},	// irq22
	{0x82, NonHandledInterrupt},	// irq23
	{0x82, NonHandledInterrupt},	// irq24
	{0x82, TIM4_UPD_IRQHandler}, 	// irq25
	{0x82, NonHandledInterrupt},	// irq26
	{0x82, USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler},	// irq27
	{0x82, USART1_RX_TIM5_CC_IRQHandler},	// irq28
	{0x82, I2C_IRQHandler},	// irq29
	
};

/*****************************END OF FILE**************************************/

