/* usart.c file
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h> // andymod added
#include "utils.h"
#include "usart.h"

/* Send buffer */
extern char *txBuffer;
extern uint8_t txCounter;
extern uint8_t txSize;


/* Receive buffer */
extern char uartRxBuffer[ MAX_RECV ];
extern uint8_t 	rxSize;
extern uint8_t	recvPacket;


/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE 50
/* Private functions ---------------------------------------------------------*/


void USART_Config()
{	
	CLK_DIVR = 0x00;		// Set the frequency to 16 MHz
	CLK_PCKENR1 = 0xFF;	// Enable peripherals

	PC_DDR |= 0x08;			// Put TX line on
	PC_CR1 |= 0x08;

	USART1_CR2 = USART_CR2_TEN | USART_CR2_REN; // Allow TX and RX
	USART1_CR3 &= ~(USART_CR3_STOP1 | USART_CR3_STOP2); // 1 stop bit
	USART1_BRR2 = 0x01; 
	USART1_BRR1 = 0x34; // 19200 baud
	
	USART_EnableIT(USART_IT_RXNE);
}


/*! \fn char USART_ReceivePacket(char *buffer, uint8_t max)
 * \brief  Decodes received bytes, indicates when packet is complete.   
 * \param  *buffer: where to place the data.
 * \param  max: maximum buffer length.
 * \return 1 = full packet received, 0 = Partial or no packet
*/
char USART_ReceivePacket(char *buffer, uint8_t max)
{
	int	i;
	uint8_t	result = recvPacket;
	char		c;
		
	if (rxSize > 0)
	{
		if (max > rxSize)
		{
			max = rxSize;
		}
		
		if (recvPacket == 1)
		{
			for (i = 0; i < max; i++)
			{
				c = uartRxBuffer[i];
				buffer[i] = c;
			}
			
			recvPacket = 0;
			rxSize = 0;
			for(i = 0; i < MAX_RECV; i++)
			{
				uartRxBuffer[i] = 0;
			}
		}
	}
	
	return result;
}


void USART_DisableIT( USART_IT_TypeDef USART_IT )
{
  uint8_t usartreg = 0x00;
  uint8_t itpos = 0x00;
  
  assert_param(IS_USART_CONFIG_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the USART register index */
  usartreg = (uint8_t)((uint16_t)USART_IT >> 0x08);
  
  /* Get the USART IT index */
  itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)USART_IT & (uint8_t)0x0F));

  {
    /**< Disable the interrupt bits according to USART_IT mask */
    if (usartreg == 0x01)
    {
      EVAL_COM1->CR1 &= (uint8_t)(~itpos);
    }
    else if (usartreg == 0x05)
    {
      EVAL_COM1->CR1 &= (uint8_t)(~itpos);	// andymod   was ->cr5
    }
    /*uartreg =0x02*/
    else
    {
      EVAL_COM1->CR2 &= (uint8_t)(~itpos);
    }
  }
}

void USART_EnableIT(USART_IT_TypeDef reg)
{
	uint8_t	itpos = 0x00;
	
	itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)reg & (uint8_t)0x0F));
	EVAL_COM1->CR2 |= itpos;	
}

void USART_WhileBusy( void )
{
	/* Wait for send buffer to empty */
//	while (txCounter > 0);
}

void USART_WhileBusy( void );

void USART_SendByte(char b)
{
	USART_WhileBusy( );
	
	txCounter = 1;
	*txBuffer = b;
	txSize   = 1;
	USART_EnableIT( USART_IT_TC );	
}

 
void USART_SendString( char *buffer)
{
	uint8_t length = strlen(buffer);	
	
	/* Wait for send buffer to empty before allowing any more data*/
	USART_WhileBusy();
	/* Update parameters and start interrupt*/
	/* TxCounter goes from 1 to size. 0 = no data. If left as 0 here, it would 
		fail "any data to send" test */
	txCounter = 1;
	
	txBuffer = buffer;
	txSize   = length;
	USART_EnableIT( USART_IT_TC );
}
 

void USART_SendValue(char *text, uint16_t val)
{
	uint8_t len;
	uint8_t	digit;
	char		szbuffer[BUFFER_SIZE];
	
	len = strlen(text);
	if ((len + 8) >= BUFFER_SIZE)
	{
		strcpy(szbuffer, "Text too long\r\n");
	}
	else
	{
		int n;
		strcpy(szbuffer, text);
		
		for( n = 0; n < 6; n++ )                          
		{
			if ( val > 0 )
			{
				digit = val % 10;
				szbuffer[len + (5 - n)] = '0' + digit;                
				val /= 10;
			}
			else 
			{
				szbuffer[len + (5 - n)] = ' ';
			}
		}
		 
		szbuffer[len ] = ' ';
		szbuffer[len + 6] = '\r';
		szbuffer[len + 7] = '\n';
		szbuffer[len + 8] = 0;		
	}

	USART_SendString((uint8_t *) szbuffer);
}



