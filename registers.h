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
*  File         : registers.h
*
*  Description  : Header file for the registers exposed by the SVI 
*									interface to the radio board
*
* The information contained herein is confidential property of Bull Products Ltd
* The use, copying, transfer or disclosure of such information is prohibited 
* except by express written agreement with Bull Products Ltd.
*************************************************************************************/

#ifndef SVI_REGISTERS_H
#define SVI_REGISTERS_H

#include "stm_header.h"   // "stm8l15x.h"


/* Defines -----------------------------------------------*/

#define VERSION_STR	"00.00.03,16/10/18"

#define REG_ADDRESS_TYPE 0x00
#define REG_ADDRESS_ENABLE  0x10
#define REG_ADDRESS_TEST_MODE 0x20
#define REG_ADDRESS_FLASH_RATE 0x40
#define REG_ADDRESS_TONE_SELECT 0x80
#define REG_ADDRESS_TONE_ATTEN 0x90
#define REG_ADDRESS_FAULT_STATUS 0xC0
#define REG_ADDRESS_FW_MAJOR_LS   0xE0
#define REG_ADDRESS_FW_MAJOR_MS   0xE1
#define REG_ADDRESS_FW_MINOR_LS   0xE2
#define REG_ADDRESS_FW_MINOR_MS   0xE3
#define REG_ADDRESS_FW_MAINT_REV_LS 0xE4
#define REG_ADDRESS_FW_MAINT_REV_MS 0xE5
#define REG_ADDRESS_FW_DATE_DAY_LS   0xE6
#define REG_ADDRESS_FW_DATE_DAY_MS   0xE7
#define REG_ADDRESS_FW_DATE_MONTH_LS   0xE8
#define REG_ADDRESS_FW_DATE_MONTH_MS   0xE9
#define REG_ADDRESS_FW_DATE_YEAR_LS   0xEA
#define REG_ADDRESS_FW_DATE_YEAR_MS   0xEB
#define REG_ADDRESS_SERIAL_NUMBER_0  0xFC
#define REG_ADDRESS_SERIAL_NUMBER_1  0xFD
#define REG_ADDRESS_SERIAL_NUMBER_2  0xFE
#define REG_ADDRESS_SERIAL_NUMBER_3  0xFF


/* Enums -------------------------------------------------*/
typedef enum
{
   SVI_REG_TYPE_E,
   SVI_REG_ENABLE_E,
   SVI_REG_TEST_MODE_E,
   SVI_REG_FLASH_RATE_E,
   SVI_REG_TONE_SELECT_E,
   SVI_REG_TONE_ATTEN_E,
   SVI_REG_FAULT_STATUS_E,
   SVI_REG_FW_MAJOR_LS_E,
   SVI_REG_FW_MAJOR_MS_E,
   SVI_REG_FW_MINOR_LS_E,
   SVI_REG_FW_MINOR_MS_E,
   SVI_REG_FW_MAINT_REV_LS_E,
   SVI_REG_FW_MAINT_REV_MS_E,
   SVI_REG_FW_DATE_DAY_LS_E,
   SVI_REG_FW_DATE_DAY_MS_E,
   SVI_REG_FW_DATE_MONTH_LS_E,
   SVI_REG_FW_DATE_MONTH_MS_E,
   SVI_REG_FW_DATE_YEAR_LS_E,
   SVI_REG_FW_DATE_YEAR_MS_E,
   SVI_REG_SERIAL_NUMBER_0_E,
   SVI_REG_SERIAL_NUMBER_1_E,
   SVI_REG_SERIAL_NUMBER_2_E,
   SVI_REG_SERIAL_NUMBER_3_E,
   SVI_REG_PARAMETER_TYPE_MAX_E
} DM_SviParameterType_t;

/* Structs -----------------------------------------------*/

/* Function prototypes -----------------------------------*/
void Regs_Config(void);
bool Regs_GetRegisterValue(const uint8_t register_address, uint8_t* reg_value);
bool Regs_GetRegisterValueByIndex(const uint8_t register_index, uint8_t* reg_value);
bool Regs_SetRegisterValue(const uint8_t register_address, const uint8_t value);


#endif /* SVI_REGISTERS_H */
/*****************************END OF FILE**************************************/
