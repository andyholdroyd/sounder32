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
*  File         : registers.c
*
*  Description  : Implementation file for the registers exposed by the SVI 
*									interface to the radio board
*
* The information contained herein is confidential property of Bull Products Ltd
* The use, copying, transfer or disclosure of such information is prohibited 
* except by express written agreement with Bull Products Ltd.
*************************************************************************************/

/* Include files **************************************************************/
#include "registers.h"


/* Defines ********************************************************************/
#define REG_ADDRESS 0
#define REG_VALUE 1

/* Global variables ***********************************************************/
uint8_t sviRegister[SVI_REG_PARAMETER_TYPE_MAX_E][2];
bool registerChanged[SVI_REG_PARAMETER_TYPE_MAX_E];
uint8_t registerUpdated = 0;

/* Private function prototypes ************************************************/
static bool Regs_GetRegisterIndex( const uint8_t register_address, uint8_t *reg_index);
static bool Regs_IsReadOnly(const uint8_t register_address);


/* Functions ******************************************************************/

/*******************************************************************************
*
* REG_Initialise
* Set the startup values of the registers.
*
* param - None
*
* return - None.
*******************************************************************************/
void Regs_Config(void)
{
	uint8_t index;
	char* pVersion = VERSION_STR;
	
	/* set the register adresses */
	sviRegister[SVI_REG_TYPE_E][REG_ADDRESS] 							= REG_ADDRESS_TYPE;
	sviRegister[SVI_REG_ENABLE_E][REG_ADDRESS] 						= REG_ADDRESS_ENABLE;
	sviRegister[SVI_REG_TEST_MODE_E][REG_ADDRESS] 				= REG_ADDRESS_TEST_MODE;
	sviRegister[SVI_REG_FLASH_RATE_E][REG_ADDRESS] 				= REG_ADDRESS_FLASH_RATE;
	sviRegister[SVI_REG_TONE_SELECT_E][REG_ADDRESS] 			= REG_ADDRESS_TONE_SELECT;
	sviRegister[SVI_REG_TONE_ATTEN_E][REG_ADDRESS] 				= REG_ADDRESS_TONE_ATTEN;
	sviRegister[SVI_REG_FAULT_STATUS_E][REG_ADDRESS] 			= REG_ADDRESS_FAULT_STATUS;
	sviRegister[SVI_REG_FW_MAJOR_LS_E][REG_ADDRESS] 			= REG_ADDRESS_FW_MAJOR_LS;
	sviRegister[SVI_REG_FW_MAJOR_MS_E][REG_ADDRESS] 			= REG_ADDRESS_FW_MAJOR_MS;
	sviRegister[SVI_REG_FW_MINOR_LS_E][REG_ADDRESS] 			= REG_ADDRESS_FW_MINOR_LS;
	sviRegister[SVI_REG_FW_MINOR_MS_E][REG_ADDRESS] 			= REG_ADDRESS_FW_MINOR_MS;
	sviRegister[SVI_REG_FW_MAINT_REV_LS_E][REG_ADDRESS] 	= REG_ADDRESS_FW_MAINT_REV_LS;
	sviRegister[SVI_REG_FW_MAINT_REV_MS_E][REG_ADDRESS] 	= REG_ADDRESS_FW_MAINT_REV_MS;
	sviRegister[SVI_REG_FW_DATE_DAY_LS_E][REG_ADDRESS] 		= REG_ADDRESS_FW_DATE_DAY_LS;
	sviRegister[SVI_REG_FW_DATE_DAY_MS_E][REG_ADDRESS] 		= REG_ADDRESS_FW_DATE_DAY_MS;
	sviRegister[SVI_REG_FW_DATE_MONTH_LS_E][REG_ADDRESS] 	= REG_ADDRESS_FW_DATE_MONTH_LS;
	sviRegister[SVI_REG_FW_DATE_MONTH_MS_E][REG_ADDRESS] 	= REG_ADDRESS_FW_DATE_MONTH_MS;
	sviRegister[SVI_REG_FW_DATE_YEAR_LS_E][REG_ADDRESS] 	= REG_ADDRESS_FW_DATE_YEAR_LS;
	sviRegister[SVI_REG_FW_DATE_YEAR_MS_E][REG_ADDRESS] 	= REG_ADDRESS_FW_DATE_YEAR_MS;
	sviRegister[SVI_REG_SERIAL_NUMBER_0_E][REG_ADDRESS] 	= REG_ADDRESS_SERIAL_NUMBER_0;
	sviRegister[SVI_REG_SERIAL_NUMBER_1_E][REG_ADDRESS] 	= REG_ADDRESS_SERIAL_NUMBER_1;
	sviRegister[SVI_REG_SERIAL_NUMBER_2_E][REG_ADDRESS] 	= REG_ADDRESS_SERIAL_NUMBER_2;
	sviRegister[SVI_REG_SERIAL_NUMBER_3_E][REG_ADDRESS] 	= REG_ADDRESS_SERIAL_NUMBER_3;
		
	/* set the register values */
	sviRegister[SVI_REG_ENABLE_E][REG_VALUE] 							= 0; /* bit 0 = activate visual indicator, bit 1 = activate sounder */
	sviRegister[SVI_REG_TEST_MODE_E][REG_VALUE] 					= 0; /* bit 0 = enable sounder self test (sound monitored when output) */
	sviRegister[SVI_REG_FLASH_RATE_E][REG_VALUE] 					= 0; /* bits 0 to 5 hold flash rate setting */
	sviRegister[SVI_REG_TONE_SELECT_E][REG_VALUE] 				= 0; /* bits 0 to 5 hold the tone selection */
	sviRegister[SVI_REG_TONE_ATTEN_E][REG_VALUE] 					= 0; /* Tone attenuation.  0=max volume */
	sviRegister[SVI_REG_FAULT_STATUS_E][REG_VALUE] 				= 0; /* bit 0 = sounder self-test result - 0=no fault */
	
	/* extract the version details from VERSION_STR*/
	sviRegister[SVI_REG_FW_MAJOR_MS_E][REG_VALUE] 				= pVersion[ 0];
	sviRegister[SVI_REG_FW_MAJOR_LS_E][REG_VALUE] 				= pVersion[ 1];
	sviRegister[SVI_REG_FW_MINOR_MS_E][REG_VALUE] 				= pVersion[ 3];
	sviRegister[SVI_REG_FW_MINOR_LS_E][REG_VALUE] 				= pVersion[ 4];
	sviRegister[SVI_REG_FW_MAINT_REV_MS_E][REG_VALUE] 		= pVersion[ 6];
	sviRegister[SVI_REG_FW_MAINT_REV_LS_E][REG_VALUE] 		= pVersion[ 7];
	sviRegister[SVI_REG_FW_DATE_DAY_MS_E][REG_VALUE] 			= pVersion[ 9];
	sviRegister[SVI_REG_FW_DATE_DAY_LS_E][REG_VALUE] 			= pVersion[ 10];
	sviRegister[SVI_REG_FW_DATE_MONTH_MS_E][REG_VALUE] 		= pVersion[ 12];
	sviRegister[SVI_REG_FW_DATE_MONTH_LS_E][REG_VALUE] 		= pVersion[ 13];
	sviRegister[SVI_REG_FW_DATE_YEAR_MS_E][REG_VALUE] 		= pVersion[ 15];
	sviRegister[SVI_REG_FW_DATE_YEAR_LS_E][REG_VALUE] 		= pVersion[ 16];

	/* Read the Type and Serial number from NVM */
	sviRegister[SVI_REG_TYPE_E][REG_VALUE] 								= 3; /* bit 0 = visual indicator present, bit 1 = sounder present */
	sviRegister[SVI_REG_SERIAL_NUMBER_0_E][REG_VALUE] 		= 0x78;
	sviRegister[SVI_REG_SERIAL_NUMBER_1_E][REG_VALUE] 		= 0x56;
	sviRegister[SVI_REG_SERIAL_NUMBER_2_E][REG_VALUE] 		= 0x34;
	sviRegister[SVI_REG_SERIAL_NUMBER_3_E][REG_VALUE] 		= 0x12;
	
	registerUpdated = 0;
}

/*******************************************************************************
*
* REG_GetRegisterIndex
* return the array index into sviRegister[] for the given register address.
*
* param - register_address	The register to find
* param - reg_index					[OUT] The returned index
*
* return - bool.						TRUE if the index was returned
*******************************************************************************/
bool Regs_GetRegisterIndex(const uint8_t register_address, uint8_t* reg_index)
{
	bool bFound = FALSE;
	uint8_t index;
	
	if ( reg_index )
	{
		for ( index = 0; index < SVI_REG_PARAMETER_TYPE_MAX_E; index++)
		{
			if ( sviRegister[index][REG_ADDRESS] == register_address )
			{
				*reg_index = index;
				bFound = TRUE;
				break;
			}
		}
	}
	
	return bFound;
}

/*******************************************************************************
*
* REG_IsReadOnly
* Checks whether a register is non-modifiable.
*
* param - register_address	The register to check
*
* return - bool.						TRUE if the register is read-only
*******************************************************************************/
bool Regs_IsReadOnly(const uint8_t register_address)
{
	bool is_read_only;
	
	switch ( register_address )
	{
		case REG_ADDRESS_ENABLE: /* intentional drop-through */
		case REG_ADDRESS_TEST_MODE:
		case REG_ADDRESS_FLASH_RATE:
		case REG_ADDRESS_TONE_SELECT:
		case REG_ADDRESS_FAULT_STATUS:
		case REG_ADDRESS_TONE_ATTEN:
			is_read_only = FALSE;
			break;
		default:
			/* all other addresses are non-modifiable */
			is_read_only = TRUE;
			break;
	}
	
	return is_read_only;
}

/*******************************************************************************
*
* REG_GetRegisterValue
* return the value held in the supplied register address.
*
* param - register_address	The register to read
* param - reg_value					[OUT] The returned value
*
* return - bool.						TRUE if the value was returned
*******************************************************************************/
bool Regs_GetRegisterValue(const uint8_t register_address, uint8_t* reg_value)
{
	bool bFound = FALSE;
	uint8_t index;
	
	if ( reg_value )
	{
		if ( TRUE == Regs_GetRegisterIndex(register_address, &index) )
		{
				*reg_value = sviRegister[index][REG_VALUE];
				bFound = TRUE;
		}
	}
	
	return bFound;
}

/*******************************************************************************
*
* REG_GetRegisterValueByIndex
* return the value held in the register array for the supplied index.
*
* param - register_index		The array index to read
* param - reg_value					[OUT] The returned value
*
* return - bool.						TRUE if the value was returned
*******************************************************************************/
bool Regs_GetRegisterValueByIndex(const uint8_t register_index, uint8_t* reg_value)
{
	bool bFound = FALSE;
	uint8_t index;
	
	if ( reg_value )
	{
		if ( SVI_REG_PARAMETER_TYPE_MAX_E > register_index )
		{
				*reg_value = sviRegister[register_index][REG_VALUE];
				bFound = TRUE;
		}
	}
	
	return bFound;
}

/*******************************************************************************
*
* REG_SetRegisterValue
* Update the value held in the supplied register address.
* The global registerUpdated is incremented to indicate that 
*	a register has changed.
* Array item registerChanged[index] is set to TRUE 
* so that the application can identify what changed.
*
* param - register_address	The register to read
* param - value							The value to be stored
*
* return - bool.						TRUE if the value was updated
*******************************************************************************/
bool Regs_SetRegisterValue(const uint8_t register_address, const uint8_t value)
{
	bool bUpdated = FALSE;
	uint8_t index;
	/* check that the requested address isn't read-only */
	if ( FALSE == Regs_IsReadOnly(register_address) )
	{
		/* convert the supplied address into the array index where the data is stored */
		if ( Regs_GetRegisterIndex(register_address, &index) )
		{
				sviRegister[index][REG_VALUE] = value;
				bUpdated = TRUE;
				registerChanged[index] = TRUE;
				registerUpdated++;
		}
	}
	return bUpdated;
}

/*****************************END OF FILE**************************************/
