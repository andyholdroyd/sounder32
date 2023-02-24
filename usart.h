//usart.h


#include "stm_header.h"   // "stm8l15x.h"


/**
  * @brief USART Interrupt definition
  * USART_IT possible values
  * Elements values convention: 0x0ZYX
  *   X: Position of the corresponding Interrupt
  *   Y: Flag position
  *   Z: Register index
  */
typedef enum 
{ 
  USART_IT_TXE        = (uint16_t)0x0277, /*!< Transmit interrupt */
  USART_IT_TC         = (uint16_t)0x0266, /*!< Transmission Complete interrupt */
  USART_IT_RXNE       = (uint16_t)0x0255, /*!< Receive interrupt */
  USART_IT_IDLE       = (uint16_t)0x0244, /*!< IDLE line interrupt */
  USART_IT_OR         = (uint16_t)0x0235, /*!< Overrun Error interrupt */
  USART_IT_PE         = (uint16_t)0x0100, /*!< Parity Error interrupt */
  USART_IT_ERR        = (uint16_t)0x0500, /*!< Error interrupt */
  USART_IT_NF         = (uint16_t)0x0102, /*!< Noise Error interrupt */
  USART_IT_FE         = (uint16_t)0x0101  /*!< Frame Error interrupt */
} USART_IT_TypeDef;

/**
 * @brief Definition for COM port1
 */
#define EVAL_COM1                   USART1
#define EVAL_COM1_GPIO              GPIOC
#define EVAL_COM1_CLK               CLK_Peripheral_USART1
#define EVAL_COM1_RxPin             GPIO_Pin_2
#define EVAL_COM1_TxPin             GPIO_Pin_3

// Receive buffer
#define MAX_RECV	20
#define MAX_REPLY	20

// Devide setup
#define PC_DDR	(*(volatile uint8_t *)0x500c)
#define PC_CR1	(*(volatile uint8_t *)0x500d)

#define CLK_DIVR	(*(volatile uint8_t *)0x50c0)
#define CLK_PCKENR1	(*(volatile uint8_t *)0x50c3)

#define USART1_SR	(*(volatile uint8_t *)0x5230)
#define USART1_DR	(*(volatile uint8_t *)0x5231)
#define USART1_BRR1	(*(volatile uint8_t *)0x5232)
#define USART1_BRR2	(*(volatile uint8_t *)0x5233)
#define USART1_CR2	(*(volatile uint8_t *)0x5235)
#define USART1_CR3	(*(volatile uint8_t *)0x5236)

#define USART_CR3_STOP2 (1 << 5)
#define USART_CR3_STOP1 (1 << 4)


void USART_Config( void );
void USART_EnableIT( USART_IT_TypeDef reg );
void USART_DisableIT( USART_IT_TypeDef USART_IT );

void USART_SendString( char *buffer );
char USART_ReceivePacket( char *buffer, uint8_t max );
void USART_SendValue( char *text, uint16_t val );
void USART_SendByte( char );
