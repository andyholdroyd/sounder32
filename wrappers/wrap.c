

#include "..\stm_header.h"

#define TIMER3 TIM3	
#define TIMER4 TIM1	


void EXTI_ClearITPendingBit(int x)
{

}
	

void TIM4_TimeBaseInit( int pscale, int freq )
{
    htim1.Init.Prescaler = pscale;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = freq;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Instance = TIMER4;

		HAL_TIM_Base_Init (&htim1);
}
	
void TIM4_ClearFlag( int update)
{
	__HAL_TIM_CLEAR_FLAG(&htim1, update);
}
	

void TIM4_ITConfig( int x, int y)
{}
		
void TIM4_Cmd( int x )
{}

	
	
void TIM3_Cmd( int x )
{}
	
void TIM3_TimeBaseInit(int pscale, int countmode, int freq)
{
    htim3.Init.Prescaler = pscale;
    htim3.Init.CounterMode = countmode;
    htim3.Init.Period = freq;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.RepetitionCounter = 0;
    htim3.Instance = TIMER3;

		HAL_TIM_Base_Init (&htim3);
}	
	
void TIM3_SelectOCxM( int x,int y )
{}
	
void			
	TIM3_ARRPreloadConfig( int a )
			{}
				
void				
	TIM3_OC1PreloadConfig( int a )
				{}
					
void
	TIM3_OC1Init( int a, int s, int d, int f, int g )
{}	
	
	void
	TIM3_CtrlPWMOutputs( int x)
	{}
	
void		
	TIM4_ClearITPendingBit(int val)	
{

}		
	
	
	
void ADC_Init(void* x, int y, int z, int w)
{}
	
void ADC_SamplingTimeConfig(void* s, int t, int u)
{}

	
int ADC_GetFlagStatus(void *a, int d)
{ return (0); }
	
void ADC_ChannelCmd(void * a,int b, int c)
{}

unsigned short ADC_GetConversionValue(int a)
{
		return(0);
}

void ADC_Cmd(int z, int xz)
{}	
	
void	ADC_ITConfig(void* a, int b, int c)
{}
	
void	ADC_SoftwareStartConv(void *a)
{}	
	
	


void LED_Activation( int st )
{
}


void LED_SetFlashRate( int x)
{}



	
	
void I2C_IRQHandler(void) 	
{}
	
void I2C_Config(void)
{}
	
	
	

	
void GPIO_Config(void)
{


}





void DMA1_CHANNEL0_1_IRQHandler(void)
{}

void DMA1_CHANNEL2_3_IRQHandler(void)
{}

	
	
	


	
void FLASH_SetProgrammingTime(int a)
{
	// not used on stm32 ?
}
	
void FLASH_Unlock(int a)
{
	// not used on stm32
}
	
int FLASH_GetFlagStatus(int a)
{
	// not used on stm32 ?
return(0);
}

int FLASH_ReadByte(int a)
{
	uint32_t *p = (uint32_t *) a;
	
	return(p);
}

void FLASH_Lock(int a)
{
	// not used on stm32?
}

void FLASH_ProgramByte(int byte, int val)
{
	byte*=8;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, byte, val);
}

	
	
void
_stext()
{}


	
void
wfi()
{
 __WFI();
}
	

	

	
	void
	SYSCFG_REMAPPinConfig(int b, int a)
	{}
		
		void
		enableInterrupts()
		{}
	
	
	
			
void 
CLK_PeripheralClockConfig(int x , int y)
{}

void	
CLK_HSEConfig(int x)	// HSERDY
{}
	
int
CLK_GetFlagStatus(int x )
{
	return(0);
}

void
CLK_SYSCLKDivConfig(int x)
{}			

	
	