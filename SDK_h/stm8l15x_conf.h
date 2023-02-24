/*!
 * \file stm8l15x_conf.h
 * \brief header configuration file for sounder project
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
 * header configuration file for sounder project
 *
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L15x_CONF_H
#define __STM8L15x_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

/* Uncomment the line below to enable peripheral header file inclusion */
#include "stm8l15x_adc.h"
//#include "stm8l15x_aes.h"
//#include "stm8l15x_beep.h"
#include "stm8l15x_clk.h"
//#include "stm8l15x_comp.h"
//#include "stm8l15x_dac.h"
//#include "stm8l15x_dma.h"
#include "stm8l15x_exti.h"
#include "stm8l15x_flash.h"
#include "stm8l15x_gpio.h"
#include "stm8l15x_i2c.h"
//#include "stm8l15x_irtim.h"
//#include "stm8l15x_itc.h"
//#include "stm8l15x_iwdg.h"
//#include "stm8l15x_lcd.h"
//#include "stm8l15x_pwr.h"
//#include "stm8l15x_rst.h"
//#include "stm8l15x_rtc.h"
//#include "stm8l15x_spi.h"
#include "stm8l15x_syscfg.h"
//#include "stm8l15x_tim1.h"
//#include "stm8l15x_tim2.h"
#include "stm8l15x_tim3.h"
#include "stm8l15x_tim4.h"
//#include "stm8l15x_tim5.h"
//#include "stm8l15x_usart.h"
//#include "stm8l15x_wfe.h"
//#include "stm8l15x_wwdg.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    (1) */ 

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed. 
  *   If expr is true, it returns no value.
  * @retval : None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)	//!< do nothing
#endif /* USE_FULL_ASSERT */

#endif /* __STM8L15x_CONF_H */

/*****************************END OF FILE**************************************/
