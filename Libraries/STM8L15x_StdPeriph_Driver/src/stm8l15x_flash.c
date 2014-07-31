/**
  ******************************************************************************
  * @file    stm8l15x_flash.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    07/14/2010
  * @brief   This file provides all the FLASH firmware functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_flash.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define FLASH_CLEAR_BYTE   ((uint8_t)0x00)
#define FLASH_SET_BYTE     ((uint8_t)0xFF)
#define OPERATION_TIMEOUT  ((uint16_t)0xFFFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup FLASH_Public_functions
  * @{
  */

/**
  * @brief  Unlocks the program or data EEPROM memory
  * @param  FLASH_MemType : Memory type to unlock
  *   This parameter can be a value of @ref FLASH_MemType_TypeDef
  * @retval None
  */
void FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType)
{
  /* Check parameter */
  assert_param(IS_FLASH_MEMORY_TYPE(FLASH_MemType));

  /* Unlock program memory */
  if (FLASH_MemType == FLASH_MemType_Program)
  {
    FLASH->PUKR = FLASH_RASS_KEY1;
    FLASH->PUKR = FLASH_RASS_KEY2;
  }

  /* Unlock data memory */
  if (FLASH_MemType == FLASH_MemType_Data)
  {
    FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
    FLASH->DUKR = FLASH_RASS_KEY1;
  }
}

/**
  * @brief Locks the program or data EEPROM memory
  * @param FLASH_MemType : Memory type
  *   This parameter can be a value of @ref FLASH_MemType_TypeDef
  * @retval None
  */
void FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType)
{
  /* Check parameter */
  assert_param(IS_FLASH_MEMORY_TYPE(FLASH_MemType));
  /* Lock memory */
  FLASH->IAPSR &= (uint8_t)FLASH_MemType;
}

/**
  * @brief  Deinitializes the FLASH registers to their default reset values.
  * @param  None
  * @retval None
  */
void FLASH_DeInit(void)
{
  FLASH->CR1 = FLASH_CR1_RESET_VALUE;
  FLASH->CR2 = FLASH_CR2_RESET_VALUE;
  FLASH->IAPSR = FLASH_IAPSR_RESET_VALUE;
  (void) FLASH->IAPSR; /* Reading of this register causes the clearing of status flags */
}

/**
  * @brief  Enables or Disables the Flash interrupt mode
  * @param  NewState : The new state of the flash interrupt mode
  *   This parameter can be a value of @ref FunctionalState enumeration.
  * @retval None
  */
void FLASH_ITConfig(FunctionalState NewState)
{

  /* Check parameter */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    FLASH->CR1 |= FLASH_CR1_IE; /* Enables the interrupt sources */
  }
  else
  {
    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_IE); /* Disables the interrupt sources */
  }
}

/**
  * @brief  Erases one byte in the program or data EEPROM memory
  * @param  Address : Address of the byte to erase
  * @retval None
  */
void FLASH_EraseByte(uint32_t Address)
{
  /* Check parameter */
  assert_param(IS_FLASH_ADDRESS(Address));

  *(PointerAttr uint8_t*) (uint16_t)Address = FLASH_CLEAR_BYTE; /* Erase byte */
}
/**
  * @brief  Programs one byte in program or data EEPROM memory
  * @param  Address : Address where the byte will be programmed
  * @param  Data : Value to be programmed
  * @retval None
  */
void FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
  /* Check parameters */
  assert_param(IS_FLASH_ADDRESS(Address));

  *(PointerAttr uint8_t*) (uint16_t)Address = Data;
}

/**
  * @brief  Programs one word (4 bytes) in program or data EEPROM memory
  * @param  Address : The address where the data will be programmed
  * @param  Data : Value to be programmed
  * @retval None
  */
void FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
  /* Check parameters */
  assert_param(IS_FLASH_ADDRESS(Address));
  /* Enable Word Write Once */
  FLASH->CR2 |= FLASH_CR2_WPRG;

  *((PointerAttr uint8_t*) (uint16_t)Address)       = *((uint8_t*)(&Data));   /* Write one byte - from lowest address*/
  *(((PointerAttr uint8_t*) (uint16_t)Address) + 1) = *((uint8_t*)(&Data) + 1); /* Write one byte*/
  *(((PointerAttr uint8_t*) (uint16_t)Address) + 2) = *((uint8_t*)(&Data) + 2); /* Write one byte*/
  *(((PointerAttr uint8_t*) (uint16_t)Address) + 3) = *((uint8_t*)(&Data) + 3); /* Write one byte - from higher address*/
}

/**
  * @brief  Programs option byte
  * @param  Address : option byte address to program
  * @param  Data : Value to write
  * @retval None
  */
void FLASH_ProgramOptionByte(uint16_t Address, uint8_t Data)
{
  /* Check parameter */
  assert_param(IS_OPTION_BYTE_ADDRESS(Address));

  /* Enable write access to option bytes */
  FLASH->CR2 |= FLASH_CR2_OPT;

  /* Program option byte and his complement */
  *((PointerAttr uint8_t*)Address) = Data;

  FLASH_WaitForLastOperation(FLASH_MemType_Program);

  /* Disable write access to option bytes */
  FLASH->CR2 &= (uint8_t)(~FLASH_CR2_OPT);
}

/**
  * @brief  Erases option byte
  * @param  Address : Option byte address to erase
  * @retval None
  */
void FLASH_EraseOptionByte(uint16_t Address)
{
  /* Check parameter */
  assert_param(IS_OPTION_BYTE_ADDRESS(Address));

  /* Enable write access to option bytes */
  FLASH->CR2 |= FLASH_CR2_OPT;

  /* Erase option byte and his complement */
  *((PointerAttr uint8_t*)Address) = FLASH_CLEAR_BYTE;

  FLASH_WaitForLastOperation(FLASH_MemType_Program);

  /* Disable write access to option bytes */
  FLASH->CR2 &= (uint8_t)(~FLASH_CR2_OPT);
}

/**
  * @brief  Reads one byte from flash memory
  * @param  Address : Address to read
  * @retval Value of the byte
  */
uint8_t FLASH_ReadByte(uint32_t Address)
{
  /* Read byte */
  return(*(PointerAttr uint8_t *)  (uint16_t)Address);
}
/**
  * @brief  Sets the fixed programming time
  * @param  FLASH_ProgTime : Indicates the programming time to be fixed
  *   This parameter can be a value of @ref FLASH_ProgramTime_TypeDef
  * @retval None
  */
void FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgTime)
{
  /* Check parameter */
  assert_param(IS_FLASH_PROGRAM_TIME(FLASH_ProgTime));

  FLASH->CR1 &= (uint8_t)(~FLASH_CR1_FIX);
  FLASH->CR1 |= (uint8_t)FLASH_ProgTime;
}

/**
  * @brief  Configues the power state for Flash program and data EEPROM during
  *   wait for interrupt mode
  * @param  FLASH_Power: The power state for Flash program and data EEPROM during
  *   wait for interrupt mode
  *   This parameter can be a value of @ref FLASH_Power_TypeDef
  * @retval None
  */
void FLASH_PowerWaitModeConfig(FLASH_Power_TypeDef FLASH_Power)
{
  /* Check parameter */
  assert_param(IS_FLASH_POWER(FLASH_Power));

  /* Flash program and data EEPROM in IDDQ during wait for interrupt mode*/
  if (FLASH_Power != FLASH_Power_On)
  {
    FLASH->CR1 |= (uint8_t)FLASH_CR1_WAITM;
  }
  /* Flash program and data EEPROM not in IDDQ during wait for interrupt mode*/
  else
  {
    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_WAITM);
  }
}

/**
  * @brief  Returns the fixed programming time
  * @param  None
  * @retval Fixed programming time value
  */
FLASH_ProgramTime_TypeDef FLASH_GetProgrammingTime(void)
{
  return((FLASH_ProgramTime_TypeDef)(FLASH->CR1 & FLASH_CR1_FIX));
}

/**
  * @brief  Returns the Boot memory size in bytes
  * @param  None
  * @retval Boot memory size in bytes
  */
uint16_t FLASH_GetBootSize(void)
{
  uint16_t temp = 0;

  /* Calculates the number of bytes */
  temp = (uint16_t)((uint16_t)OPT->UBC * (uint8_t)128);

  /* Correction because size upper 8kb doesn't exist */
  if (OPT->UBC > 0x7F)
  {
    temp = 8192;
  }

  /* Return value */
  return(temp);

}
/**
 *
  * @brief  Returns the Code Area size in bytes
  * @param  None
  * @retval Code Area size in bytes
  */
uint16_t FLASH_GetCodeSize(void)
{
  uint16_t temp;

  /* Calculates the number of bytes */
  temp = (uint16_t)((uint16_t)OPT->PCODESIZE * (uint8_t)128);

  /* Correction because size upper of 8kb doesn't exist */
  if (OPT->PCODESIZE > 0x7F)
  {
    temp = 8192;
  }

  /* Return value */
  return(temp);
}

/**
  * @brief  Returns the FLASH Read Out Protection Status.
  * @param  None
  * @retval FunctionalState: Indicates the FLASH Read Out Protection Status.
  *   This parameter can be a ENABLE or DISABLE
  */
FunctionalState FLASH_GetReadOutProtectionStatus(void)
{
  FunctionalState state = DISABLE;

  if (OPT->ROP == FLASH_READOUTPROTECTION_KEY)
  {
    /* The status of the Flash read out protection is enabled*/
    state =  ENABLE;
  }
  else
  {
    /* The status of the Flash read out protection is disabled*/
    state =  DISABLE;
  }

  return state;
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  Flash_FLAG : specifies the Flash Flag to check.
  *   This parameter can be a value of @ref FLASH_FLAG_TypeDef
  * @retval FlagStatus : Indicates the state of the Flash_FLAG.
  *   This parameter can be a value of @ref FlagStatus enumeration.
  */
FlagStatus FLASH_GetFlagStatus(FLASH_FLAG_TypeDef FLASH_FLAG)
{
  FlagStatus status = RESET;
  assert_param(IS_FLASH_FLAGS(FLASH_FLAG));

  /* Check the status of the specified flash flag*/
  if ((FLASH->IAPSR  & (uint8_t)FLASH_FLAG) != (uint8_t)RESET)
  {
    status = SET; /* Flash_FLAG is set*/
  }
  else
  {
    status = RESET; /* Flash_FLAG is reset*/
  }

  /* Return the Flash_FLAG status*/
  return status;
}

/**
  * @brief  Waits for a Flash operation to complete.
  * @param FLASH_MemType : Memory type
  *   This parameter can be a value of @ref FLASH_MemType_TypeDef
  * @retval FLASH status
  * @par    Required preconditions: This function should be executed from RAM.
  */
FLASH_Status_TypeDef FLASH_WaitForLastOperation(FLASH_MemType_TypeDef FLASH_MemType)
{
  uint32_t timeout = OPERATION_TIMEOUT;
  uint8_t flagstatus = 0x00;
  /* Wait until operation completion or write protected page occured */
  if (FLASH_MemType == FLASH_MemType_Program)
  {
    while ((flagstatus == 0x00) && (timeout != 0x00))
    {
      flagstatus = (uint8_t)(FLASH->IAPSR & (uint8_t)(FLASH_IAPSR_EOP |
                             FLASH_IAPSR_WR_PG_DIS));
      timeout--;
    }
  }
  else
  {
    while ((flagstatus == 0x00) && (timeout != 0x00))
    {
      flagstatus = (uint8_t)(FLASH->IAPSR & (uint8_t)(FLASH_IAPSR_HVOFF |
                             FLASH_IAPSR_WR_PG_DIS));
      timeout--;
    }
  }
  if (timeout == 0x00 )
  {
    flagstatus = FLASH_Status_TimeOut;
  }

  return((FLASH_Status_TypeDef)flagstatus);
}
/* ****************************************************************************/
/*                    Uncomment the line below to use these functions         */
/*                                                                            */
/* ****************************************************************************/
/* LINKER SECTIONS DEFINITION FOR THIS FILE ONLY */
#ifdef USE_COSMIC_SECTIONS
#pragma section (FLASH_CODE)
#pragma section const {FLASH_CONST}
#pragma section @near [FLASH_URAM]
#pragma section @near {FLASH_IRAM}
#pragma section @tiny [FLASH_UZRAM]
#pragma section @tiny {FLASH_IZRAM}
#endif

/**
  * @brief  Configues the power state for Flash program and data EEPROM during
  *   run, low power run and low power wait modes
  * @param  FLASH_Power: power state of the Flash program and data EEPROM
  *   This parameter can be a value of @ref FLASH_Power_TypeDef
  * @retval None
  */
void FLASH_PowerRunModeConfig(FLASH_Power_TypeDef FLASH_Power)
{
  /* Check parameter */
  assert_param(IS_FLASH_POWER(FLASH_Power));

  if (FLASH_Power != FLASH_Power_On)
  {
    FLASH->CR1 |= (uint8_t)FLASH_CR1_EEPM;
  }
  else
  {
    FLASH->CR1 &= (uint8_t)(~FLASH_CR1_EEPM);
  }
}

/**
  * @brief  Checks the power status for Flash program and data EEPROM
  * @param  None
  * @retval Flash program and data EEPROM power status
  *   This parameter can be a value of @ref FLASH_PowerStatus_TypeDef
  * @par    Required preconditions: This function should be executed from RAM.
  */
FLASH_PowerStatus_TypeDef FLASH_GetPowerStatus(void)
{
  return(FLASH_PowerStatus_TypeDef)(FLASH->CR1 & (uint8_t)0x0C);
}

/**
  * @brief  Programs a memory block
  * @param  FLASH_MemType : The type of memory to program
  * @param  BlockNum : The block number
  * @param  FLASH_ProgMode : The programming mode.
  * @param  Buffer : Pointer to buffer containing source data.
  * @retval None.
  * @par    Required preconditions: This function should be executed from RAM.
  */
void FLASH_ProgramBlock(uint16_t BlockNum, FLASH_MemType_TypeDef FLASH_MemType,
                        FLASH_ProgramMode_TypeDef FLASH_ProgMode, uint8_t *Buffer)
{
  uint16_t Count = 0;
  uint32_t StartAddress = 0;

  /* Check parameters */
  assert_param(IS_FLASH_MEMORY_TYPE(FLASH_MemType));
  assert_param(IS_FLASH_PROGRAM_MODE(FLASH_ProgMode));
  if (FLASH_MemType == FLASH_MemType_Program)
  {
    assert_param(IS_FLASH_PROGRAM_BLOCK_NUMBER(BlockNum));
    StartAddress = FLASH_PROGRAM_START_PHYSICAL_ADDRESS;
  }
  else
  {
    assert_param(IS_FLASH_DATA_EEPROM_BLOCK_NUMBER(BlockNum));
    StartAddress = FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS;
  }

  /* Point to the first block address */
  StartAddress = StartAddress + ((uint32_t)BlockNum * FLASH_BLOCK_SIZE);

  /* Selection of Standard or Fast programming mode */
  if (FLASH_ProgMode == FLASH_ProgramMode_Standard)
  {
    /* Standard programming mode */
    FLASH->CR2 |= FLASH_CR2_PRG;
  }
  else
  {
    /* Fast programming mode */
    FLASH->CR2 |= FLASH_CR2_FPRG;
  }

  /* Copy data bytes from RAM to FLASH memory */
  for (Count = 0; Count < FLASH_BLOCK_SIZE; Count++)
  {
    *((PointerAttr uint8_t*) (uint16_t)(StartAddress + Count)) = ((uint8_t)(Buffer[Count]));
  }
}

/**
  * @brief  Erases a block in the program or data memory.
  * @param  FLASH_MemType :  The type of memory to erase
  * @param  BlockNum : Indicates the block number to erase
  * @retval None.
  * @par    Required preconditions: This function should be executed from RAM.
  */
void FLASH_EraseBlock(uint16_t BlockNum, FLASH_MemType_TypeDef FLASH_MemType)
{
  uint32_t *pwFlash;
  uint32_t StartAddress = 0;

  /* Check parameters */
  assert_param(IS_FLASH_MEMORY_TYPE(FLASH_MemType));
  if (FLASH_MemType == FLASH_MemType_Program)
  {
    assert_param(IS_FLASH_PROGRAM_BLOCK_NUMBER(BlockNum));
    StartAddress = FLASH_PROGRAM_START_PHYSICAL_ADDRESS;
  }
  else
  {
    assert_param(IS_FLASH_DATA_EEPROM_BLOCK_NUMBER(BlockNum));
    StartAddress = FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS;
  }
  /* Point to the first block address */
  pwFlash = (PointerAttr uint32_t *)((uint16_t)(StartAddress + ((uint32_t)BlockNum * FLASH_BLOCK_SIZE)));

  /* Enable erase block mode */
  FLASH->CR2 |= FLASH_CR2_ERASE;

  *pwFlash = (uint32_t)0;

}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
