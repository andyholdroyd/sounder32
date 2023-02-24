/*************************************************************************************
*  CONFIDENTIAL Bull Products Ltd.
**************************************************************************************
*  Cygnus2
*  Copyright 2019 Bull Products Ltd. All rights reserved.
*  Beacon House, 4 Beacon Rd
*  Rotherwas Industrial Estate
*  Hereford HR2 6JF UK
*  Tel: <44> 1432806806
*
**************************************************************************************
*  File         : utils.c
*
*  Description  : Implementation file for common utility functions
*
* The information contained herein is confidential property of Bull Products Ltd
* The use, copying, transfer or disclosure of such information is prohibited 
* except by express written agreement with Bull Products Ltd.
*************************************************************************************/

/* Include files **************************************************************/
#include "utils.h"
#include <string.h>	// andymod   added


/* Defines ********************************************************************/
#define MAX_STRING_LENGTH 250

/* Global variables ***********************************************************/

/* Private function prototypes ************************************************/


/* Functions ******************************************************************/

/*******************************************************************************
*
* strlen
* Find the length of a char string.
*
* param -pBuffer		Pointer to the string
*
* return - uint8_t	The length of the string
*******************************************************************************/
uint8_t strlen_32(const char *pBuffer)
{
	uint8_t	length = 0;
	if ( pBuffer )
	{
		while (pBuffer[length] != 0 && length < MAX_STRING_LENGTH)
		{
			length++;
		}
	}
	return length;
}

/*******************************************************************************
*
* strncpy
* Copy 'length' bytes from one string to another.
*
* param - pDest			[OUT] Pointer to the destination string
* param - pSource		Pointer to the source string
* param - length		Number of bytes to copy
*
* return - None
*******************************************************************************/
void strncpy_32(char *pDest, const char *pSource, const uint16_t length)
{
	uint16_t	i;
	
	if ( pDest && pSource )
	{
		for (i = 0; i < length; i++)
		{
			pDest[i] = pSource[i];
		}
	}
}

/*******************************************************************************
*
* strncpy
* Copy one string to another.
*
* param - pDest			[OUT] Pointer to the destination string
* param - pSource		Pointer to the source string
*
* return - None
*******************************************************************************/
void strcpy_32(char *pDest, const char *pSource)
{
	uint16_t	i;
	uint16_t length;

	if ( pDest && pSource )
	{
		length = strlen(pSource);
		
		for (i = 0; i < length; i++)
		{
			pDest[i] = pSource[i];
		}
		pDest[i] = 0;
	}
}

/*******************************************************************************
*
* strncmp
* Compare two strings for equality up to 'length' bytes..
*
* param - pStr1			Pointer to the first string
* param - pStr2			Pointer to the second string
* param - length		Number of bytes to compare
*
* return - uint16_t 0 = strings match, 1 = Strings don't match
*******************************************************************************/
uint8_t strncmp_32(const char *pStr1, const char *pStr2, const uint16_t length)
{
	uint16_t	i;
	uint8_t match = 0;
	
	if ( pStr1 && pStr2 )
	{
		for (i = 0; i < length; i++)
		{
			if (pStr1[i] != pStr2[i])
			{
				match = 1;
				break;
			}
		}
	}
	
	return match;
}

/*******************************************************************************
*
* strncpy
* Append one string to the end of another.
*
* param - pDest			[OUT] Pointer to the destination string
* param - pSource		Pointer to the string to append
*
* return - None
*******************************************************************************/
void strcat_32(char *pDest, const char *pSource)
{
	uint8_t	len;
	uint8_t	i = 0;
	
	if ( pDest && pSource )
	{
		len = strlen(pDest);
		pDest += len;
		
		while(pSource[i] != 0)
		{
			pDest[i] = pSource[i];
			i++;
		}
		pDest[i] = 0;
	}
}

/*******************************************************************************
*
* hex2text
* convert a hex number into a string e.g. 0x2D --> "2D".
*
* param - hex				The number to be converted
* param - pText			[OUT] Pointer to the destination string
*
* return - None
*******************************************************************************/
void hex2text(const uint8_t hex, const uint8_t* pText)
{
	u8 low_nib;
	u8 hi_nib;
	u8* pTxt = (u8*) pText;
	
	if ( pTxt )
	{
		low_nib = hex & 0x0f;
		low_nib += '0';
		if ( low_nib > '9' )
		{
			low_nib += 7;
		}
		
		hi_nib = (hex >> 4) & 0x0f;
		hi_nib += '0';
		if ( hi_nib > '9' )
		{
			hi_nib += 7;
		}
		
		*pTxt = hi_nib;
		pTxt++;
		*pTxt = low_nib;
	}
	
}

/*******************************************************************************
*
* memset

* Set 'length' bytes of an array to a specific value.
*
* param - pBuffer		[OUT] The target array
* param - value			The value to be written to each array element.
* param - length		The number of bytes to be written
*
* return - None
*******************************************************************************/
void memset_32(uint8_t* pBuffer, const uint8_t value, const uint8_t length)
{
	uint8_t index;
	uint8_t* pBuff = pBuffer;
	
	if ( pBuff )
	{
		for( index = 0; index < length; index++ )
		{
			*pBuff = value;
			pBuff++;
		}
	}
}


/*****************************END OF FILE**************************************/
