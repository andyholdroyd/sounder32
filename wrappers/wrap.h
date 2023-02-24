


#define CLK_Peripheral_ADC1 1

void CLK_PeripheralClockConfig(int, int);

	// system_clock / 1
void	CLK_SYSCLKDivConfig(int);
	
	// Enable TIMx clocks

void CLK_PeripheralClockConfig(int, int);

// timers

#define TIM4_Prescaler_128 1
#define TIM4_IT_Update 2
#define TIM4_FLAG_Update 1
#define TIM3_Channel_2 2
#define TIM3_OCMode_Inactive 6


void TIM4_TimeBaseInit( int ,int );
void TIM4_ClearFlag( int  );
void TIM4_ITConfig( int , int );
void TIM4_Cmd( int );
void TIM3_SelectOCxM( int ,int );
void TIM3_Cmd( int );


#define TIM4_FLAG_Update 1
#define TIM3_Prescaler_64 1
#define TIM3_CounterMode_Up 2
#define TIM3_OCMode_PWM1 0
#define TIM3_OutputState_Enable 0
#define TIM3_OCPolarity_High 1
#define TIM3_OCIdleState_Set 1

#define CLK_Peripheral_TIM1	1
#define CLK_Peripheral_TIM2	2
#define CLK_Peripheral_TIM3 3

#define CLK_SYSCLKDiv_1 1

#define ADC_ConversionMode_Continuous 0
#define ADC_Resolution_12Bit 0
#define ADC_Prescaler_2 0
#define ADC_SamplingTime_384Cycles 1
#define ADC_Group_SlowChannels 1

#define ADC_Channel_14 0

void ADC_ChannelCmd(void * ,int, int );

#define FLASH_MemType_Data 0
#define FLASH_ProgramTime_Standard 0
#define FLASH_FLAG_DUL 0

void ADC_Init(void * , int , int , int );
void ADC_SamplingTimeConfig(void *, int, int);
int ADC_GetFlagStatus(void *, int);
void ADC_Cmd(int, int);

void	ADC_ITConfig(void*, int, int);

void	ADC_SoftwareStartConv(void*);


void LED_Activation( int );
void LED_SetFlashRate( int);
				
void TIM3_TimeBaseInit(int prescale, int countmode, int period);	
void TIM4_ClearITPendingBit(int);	


void FLASH_SetProgrammingTime(int);	
void FLASH_Unlock(int);
int FLASH_GetFlagStatus(int);
int FLASH_ReadByte(int);
void FLASH_Lock(int);
void FLASH_ProgramByte(int, int);


#define USART_CR2_TEN 1
#define USART_CR2_REN 2

#define DMA_CSPR_TCIF 1
#define EXTI_IT_Pin5 16

void I2C_Config(void);
void I2C_IRQHandler(void); 	

unsigned short ADC_GetConversionValue(int);

void SYSCFG_REMAPPinConfig( int, int);

void GPIO_Config(void);

void EXTI_ClearITPendingBit(int);

void DMA1_CHANNEL0_1_IRQHandler(void);
void DMA1_CHANNEL2_3_IRQHandler(void);

#define REMAP_Pin_TIM2TRIGLSE 0 

	// Enable HSE clock
void CLK_HSEConfig(int);	// HSERDY
	
int CLK_GetFlagStatus(int); 

extern void wfi();

#define CLK_FLAG_HSERDY 1
#define CLK_HSE_ON	1


