/*!
 * \file gpio.h
 * \brief header file for gpio.c
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
 * 1.0   03.2018  PSL     split from sounder.h
 *
 * Module Description :
 * gpio.h is the header file for sounder.c
 *
*/


/* Function prototypes ********************************************************/
void	GPIO_Config(void);

/* Enums ---------------------------------------------------------------------*/

/* Structs -------------------------------------------------------------------*/

/* Defines ********************************************************************/

// IO Ports
#define SPL_PORT			GPIOB
#define PWM_PORT			GPIOB
#define PIEZO_PORT		GPIOB
#define PIEZOADC_PORT	GPIOA
#define VMIC_PORT			GPIOD

// --- IO Pins---
// PORT B
#define LED_PWM			  GPIO_Pin_5
#define TONE_PWM			GPIO_Pin_4
#define SPL_TRIG			GPIO_Pin_5
#define SPL_TRIG2     GPIO_Pin_2     //Adding PortB2 OMAR
#define SPL_SEL_M			GPIO_Pin_1
#define SPL_SEL_L			GPIO_Pin_0

// PORT C
#define PIEZO_SHDN		GPIO_Pin_4
#define PIEZO_ADC			GPIO_Pin_8

// PORT D
#define VMIC_SHDN			GPIO_Pin_0

// Other
#define GPIO_HIGH(a,b) 	a->ODR|=b
#define GPIO_LOW(a,b)	a->ODR&=~b


/*****************************END OF FILE**************************************/
