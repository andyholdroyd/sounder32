
#ifndef STM_HEAD
#define STM_HEAD


#include "stm32c031xx.h"
#include "stm32c0xx_hal.h"
#include "stm32c0xx_hal_def.h"
#include "stm32c0xx_hal_cortex.h"
#include "stm32c0xx_hal_pwr.h"
#include "stm32c0xx_hal_rcc.h"
#include "stm32c0xx_hal_adc.h"
#include "stm32c0xx_hal_gpio.h"
#include "stm32c0xx_hal_flash.h"
#include "stm32c0xx_hal_flash_ex.h"
#include "stm32c0xx_hal_tim.h"


#define GPIO_Pin_0 	GPIO_PIN_0 		               
#define GPIO_Pin_1 	GPIO_PIN_1		                 
#define GPIO_Pin_2 	GPIO_PIN_2		                 
#define GPIO_Pin_3 	GPIO_PIN_3		                 
#define GPIO_Pin_4 	GPIO_PIN_4		                 
#define GPIO_Pin_5 	GPIO_PIN_5		                 
#define GPIO_Pin_6 	GPIO_PIN_6		                 
#define GPIO_Pin_7 	GPIO_PIN_7 		                
#define GPIO_Pin_8 	GPIO_PIN_8 		                
#define GPIO_Pin_9 	GPIO_PIN_9  	               
#define GPIO_Pin_10	GPIO_PIN_10		                 
#define GPIO_Pin_11	GPIO_PIN_11 	                
#define GPIO_Pin_12	GPIO_PIN_12		                
#define GPIO_Pin_13	GPIO_PIN_13 	              
#define GPIO_Pin_14	GPIO_PIN_14 	               
#define GPIO_Pin_15	GPIO_PIN_15 	               
      



#include "stm32c0xx_hal_conf.h"
#include "stm32c0xx_hal_def.h"

#include "wrappers\wrap.h"
#include <string.h>


/*!< Signed integer types  */
//typedef   signed char     int8_t;
//typedef   signed short    int16_t;
//typedef   signed long     int32_t;

/*!< Unsigned integer types  */
//typedef unsigned char     uint8_t;
//typedef unsigned short    uint16_t;
//typedef unsigned long     uint32_t;

/*!< STM8Lx Standard Peripheral Library old types (maintained for legacy purpose) */

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


typedef enum {FALSE = 0, TRUE = !FALSE} bool;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

extern void enableInterrupts(void);

#endif 