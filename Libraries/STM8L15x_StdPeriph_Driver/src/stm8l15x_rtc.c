/**
  ******************************************************************************
  * @file    stm8l15x_rtc.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    07/14/2010
  * @brief   This file provides all the RTC firmware functions.
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
#include "stm8l15x_rtc.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define INIT_TIMEOUT       ((uint16_t)0xFFFF)
#define RSF_TIMEOUT        ((uint16_t)0xFFFF)
#define INITF_TIMEOUT      ((uint16_t)0xFFFF)
#define WUTWF_TIMEOUT      ((uint16_t)0xFFFF)
#define ALRAWF_TIMEOUT     ((uint16_t)0xFFFF)

#define TEN_VALUE_BCD      ((uint8_t)0x10)
#define TEN_VALUE_BIN      ((uint8_t)0x0A)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
    * @addtogroup RTC_Private_Functions_Prototype
    * @{
    */
static uint8_t ByteToBcd2(uint8_t Value);
static uint8_t Bcd2ToByte(uint8_t Value);

/**
    * @}
    */


/**
    * @addtogroup RTC_Public_Functions
    * @{
    */

/**
  * @brief  Deinitializes the RTC registers to their default reset values.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are deinitialized
  *          - ERROR: RTC registers are not deinitialized
  */
ErrorStatus RTC_DeInit(void)
{
  ErrorStatus status = ERROR;
  uint16_t wutcounter = 0;
  uint8_t wutwfstatus = 0;
  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(ENABLE);
  }
  else
  {
    /* Reset TR registers */
    RTC->TR1 = RTC_TR1_RESET_VALUE;
    RTC->TR2 = RTC_TR2_RESET_VALUE;
    RTC->TR3 = RTC_TR3_RESET_VALUE;

    /* Reset DR registers */
    RTC->DR1 = RTC_DR1_RESET_VALUE;
    RTC->DR2 = RTC_DR2_RESET_VALUE;
    RTC->DR3 = RTC_DR3_RESET_VALUE;

    /* Reset All CR0 bits except CR[2:0] */
    RTC->CR1 = 0x7;
    RTC->CR2 = RTC_CR2_RESET_VALUE;
    RTC->CR3 = RTC_CR3_RESET_VALUE;

    /* Wait till RTC WUTWF flag is set and if Time out is reached exit */
    do
    {
      wutwfstatus = (uint8_t)(RTC->ISR1 & RTC_ISR1_WUTWF);
      wutcounter++;
    }
    while ((wutwfstatus == RESET) && (wutcounter != INIT_TIMEOUT));

    if ((RTC->ISR1 & RTC_ISR1_WUTWF) == RESET)
    {
      status = ERROR;
      /* Enable the write protection for RTC registers */
      RTC_WriteProtectionCmd(ENABLE);
    }
    else
    {
      /* Reset All CR1 bits */
      RTC->CR1 = RTC_CR1_RESET_VALUE;

      /* Reset WUTR registers */
      RTC->WUTRH = RTC_WUTRH_RESET_VALUE;
      RTC->WUTRL = RTC_WUTRL_RESET_VALUE;

      /* Reset SPER & ARPER registers */
      RTC->SPRERH = RTC_SPRERH_RESET_VALUE;
      RTC->SPRERL = RTC_SPRERL_RESET_VALUE;
      RTC->APRER  = RTC_APRER_RESET_VALUE;

      /* Reset ALARM registers */
      RTC->ALRMAR1 = RTC_ALRMAR1_RESET_VALUE;
      RTC->ALRMAR2 = RTC_ALRMAR2_RESET_VALUE;
      RTC->ALRMAR3 = RTC_ALRMAR3_RESET_VALUE;
      RTC->ALRMAR4 = RTC_ALRMAR4_RESET_VALUE;

      /* Reset ISR register and exit initialization mode */
      RTC->ISR1 = (uint8_t)0x00;
      RTC->ISR2 = RTC_ISR2_RESET_VALUE;

      /* Enable the write protection for RTC registers */
      RTC_WriteProtectionCmd(ENABLE);

      if (RTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
  }
  return (ErrorStatus)status;
}

/**
  * @brief  Initializes the RTC registers according to the specified parameters
  *   in RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains
  *  the configuration information for the RTC peripheral.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are initialized
  *          - ERROR: RTC registers are not initialized
  */
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
  ErrorStatus status = ERROR;
  /* Check the parameters */
  assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
  assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));
  assert_param(IS_RTC_SYNCH_PREDIV(RTC_InitStruct->RTC_SynchPrediv));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    /* Clear the bits to be configured first */
    RTC->CR1 &= ((uint8_t)~( RTC_CR1_FMT ));

    /* Set RTC_CR1 register */
    RTC->CR1 |=  ((uint8_t)(RTC_InitStruct->RTC_HourFormat));

    RTC->SPRERH = (uint8_t)(RTC_InitStruct->RTC_SynchPrediv >> 8);
    RTC->SPRERL = (uint8_t)(RTC_InitStruct->RTC_SynchPrediv);
    RTC->APRER =  (uint8_t)(RTC_InitStruct->RTC_AsynchPrediv);

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    status = SUCCESS;
  }
  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
  return (ErrorStatus)(status);
}

/**
  * @brief  Fills each RTC_InitStruct member with its default value.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure which will be
  *   initialized.
  * @retval None
  */
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct)
{
  /* Initialize the RTC_HourFormat member */
  RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24;

  /* Initialize the RTC_AsynchPrediv member */
  RTC_InitStruct->RTC_AsynchPrediv = RTC_APRER_RESET_VALUE;

  /* Initialize the RTC_SynchPrediv member */
  RTC_InitStruct->RTC_SynchPrediv = RTC_SPRERL_RESET_VALUE;
}

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_IT_WUT:  WakeUp Timer interrupt mask
  *     @arg RTC_IT_ALRA:  Alarm A interrupt mask
  * @param  NewState: new state of the specified RTC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void RTC_ITConfig(RTC_IT_TypeDef RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_CONFIG_IT(RTC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  if (NewState != DISABLE)
  {
    /* Configure the Interrupts in the RTC_CR2 register */
    RTC->CR2 |= (uint8_t)RTC_IT;
  }
  else
  {
    /* Configure the Interrupts in the RTC_CR2 register */
    RTC->CR2 &= (uint8_t)~(RTC_IT);
  }

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC is in Init mode
  *          - ERROR: RTC is not in Init mode
  */
ErrorStatus RTC_EnterInitMode(void)
{
  ErrorStatus status = ERROR;
  uint16_t initfcount = 0;

  /* Check if the Initialization mode is set */
  if ((RTC->ISR1 & RTC_ISR1_INITF) == RESET)
  {
    /* Set the Initialization mode */
    RTC->ISR1 = (uint8_t)RTC_ISR1_INIT;

    /* Wait until INITF flag is set */
    while (((RTC->ISR1 & RTC_ISR1_INITF) == RESET) && ( initfcount != INITF_TIMEOUT))
    {
      initfcount++;
    }
  }

  if ((RTC->ISR1 & RTC_ISR1_INITF) == RESET)
  {
    status = ERROR;
  }
  else
  {
    status = SUCCESS;
  }
  return (ErrorStatus)status;
}

/**
  * @brief  Exits the RTC Initialization mode.
  * @param  None
  * @retval None
  */
void RTC_ExitInitMode(void)
{
  /* Exit Initialization mode */
  RTC->ISR1 &= (uint8_t)~RTC_ISR1_INIT;
}

/**
  * @brief  Enables or disables the RTC registers write protection.
  * @param  NewState: new state of the write protection.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WriteProtectionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the write protection for RTC registers */
    RTC->WPR = RTC_WPR_EnableKey;
  }
  else
  {
    /* Disable the write protection for RTC registers */
    RTC->WPR = RTC_WPR_DisableKey1;
    RTC->WPR = RTC_WPR_DisableKey2;
  }
}

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR)
  *   are synchronized with RTC clock.
  * @note   This function must be called before any read operation.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are synchronised
  *          - ERROR: RTC registers are not synchronised
  */
ErrorStatus RTC_WaitForSynchro(void)
{
  uint16_t rsfcount = 0;
  ErrorStatus status = ERROR;

  /* Clear RSF flag */
  RTC->ISR1 &= (uint8_t)~(RTC_ISR1_RSF | RTC_ISR1_INIT);

  /* Wait the registers to be synchronised */
  while (((RTC->ISR1 & RTC_ISR1_RSF) == RESET) && ( rsfcount != RSF_TIMEOUT))
  {
    rsfcount++;
  }

  /* Check the Synchronisation status*/
  if ((RTC->ISR1 & RTC_ISR1_RSF) != RESET)
  {
    status = ERROR;
  }
  else
  {
    status = SUCCESS;
  }

  return (ErrorStatus)status;
}


/**
  * @brief  Configures the RTC Ratio.
  * @param  NewState: new state of the Ratio feature.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC ratio is configured
  *         - ERROR: RTC ratio is not configured
  */
ErrorStatus RTC_RatioCmd(FunctionalState NewState)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    if (NewState != DISABLE)
    {
      /* Set the RATIO bit */
      RTC->CR1 |= (uint8_t)RTC_CR1_RATIO;
    }
    else
    {
      /* Reset the RATIO bit */
      RTC->CR1 &= (uint8_t)~RTC_CR1_RATIO;
    }

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    status = SUCCESS;
  }
  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);

  return (ErrorStatus)(status);
}

/**
  * @brief Sets the RTC current time.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *   This parameter can be one of the @ref RTC_Format_TypeDef enumeration.
  * @param  RTC_TimeStruct:  pointer to a  @ref RTC_TimeTypeDef structure that
  *  contains the time configuration information for the RTC
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Time register is configured
  *          - ERROR: RTC Time register is not configured
  */
ErrorStatus RTC_SetTime(RTC_Format_TypeDef RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  ErrorStatus status = ERROR;
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR1 & RTC_CR1_FMT) != RESET )
    {
      assert_param(IS_RTC_HOUR12_MAX(RTC_TimeStruct->RTC_Hours));
      assert_param(IS_RTC_HOUR12_MIN(RTC_TimeStruct->RTC_Hours));
    }
    else
    {
      assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
    }
    assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
  }
  else
  {
    if ((RTC->CR1 & RTC_CR1_FMT) != RESET )
    {
      assert_param(IS_RTC_HOUR12_MAX(Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
      assert_param(IS_RTC_HOUR12_MIN(Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
    }
    else
    {
      assert_param(IS_RTC_HOUR24(Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
    }
    assert_param(IS_RTC_MINUTES(Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
  }
  assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(ENABLE);
  }
  else
  {
    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
      RTC->TR1 = (uint8_t)(RTC_TimeStruct->RTC_Seconds);
      RTC->TR2 = (uint8_t)(RTC_TimeStruct->RTC_Minutes) ;
      RTC->TR3 = (uint8_t)(RTC_TimeStruct->RTC_H12 | RTC_TimeStruct->RTC_Hours) ;
    }
    else
    {
      RTC->TR1 = (uint8_t)(ByteToBcd2(RTC_TimeStruct->RTC_Seconds));
      RTC->TR2 = (uint8_t)(ByteToBcd2(RTC_TimeStruct->RTC_Minutes)) ;
      RTC->TR3 = (uint8_t)(RTC_TimeStruct->RTC_H12 | ByteToBcd2(RTC_TimeStruct->RTC_Hours));
    }

    (void)(RTC->DR3);

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(ENABLE);

    if (RTC_WaitForSynchro() == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
  return (ErrorStatus)status;
}
/**
  * @brief Set the RTC current date.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *   This parameter can be one of the @ref RTC_Format_TypeDef enumeration.
  * @param  RTC_DateStruct:  pointer to a  @ref RTC_TimeTypeDef structure that
  *  contains the date configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Date register is configured
  *          - ERROR: RTC Date register is not configured
  */
ErrorStatus RTC_SetDate(RTC_Format_TypeDef RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  ErrorStatus status = ERROR;
  if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & TEN_VALUE_BCD) == TEN_VALUE_BCD))
  {
    RTC_DateStruct->RTC_Month = (RTC_Month_TypeDef)((RTC_DateStruct->RTC_Month & (uint8_t)~(TEN_VALUE_BCD)) + TEN_VALUE_BIN);
  }

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));
  if (RTC_Format == RTC_Format_BIN)
  {
    assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
    assert_param(IS_RTC_MONTH_MIN(RTC_DateStruct->RTC_Month));
    assert_param(IS_RTC_MONTH_MAX(RTC_DateStruct->RTC_Month));
    assert_param(IS_RTC_DATE_MIN(RTC_DateStruct->RTC_Date));
    assert_param(IS_RTC_DATE_MAX(RTC_DateStruct->RTC_Date));
  }
  else
  {
    assert_param(IS_RTC_YEAR(Bcd2ToByte(RTC_DateStruct->RTC_Year)));
    assert_param(IS_RTC_MONTH_MAX(Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Month)));
    assert_param(IS_RTC_MONTH_MIN(Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Month)));
    assert_param(IS_RTC_DATE_MIN(Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Date)));
    assert_param(IS_RTC_DATE_MAX(Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Date)));
  }
  assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(ENABLE);
  }
  else
  {
    (void)(RTC->TR1);
    /* Set the RTC_DR registers */
    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
      RTC->DR1 = (uint8_t)(RTC_DateStruct->RTC_Date);
      RTC->DR2 = (uint8_t)((uint8_t)(RTC_DateStruct->RTC_Month) | (uint8_t)(RTC_DateStruct->RTC_WeekDay));
      RTC->DR3 = (uint8_t)((RTC_DateStruct->RTC_Year));
    }
    else
    {
      RTC->DR1 = (uint8_t)(ByteToBcd2 ((uint8_t)RTC_DateStruct->RTC_Date));
      RTC->DR2 = (uint8_t)((ByteToBcd2((uint8_t)RTC_DateStruct->RTC_Month)) | (RTC_DateStruct->RTC_WeekDay));
      RTC->DR3 = (uint8_t)(ByteToBcd2((uint8_t)RTC_DateStruct->RTC_Year));
    }

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(ENABLE);

    if (RTC_WaitForSynchro() == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
  return (ErrorStatus)status;
}

/**
  * @brief  Gets the RTC current Time.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *   This parameter can be one of the @ref RTC_Format_TypeDef enumeration.
  * @param  RTC_TimeStruct: pointer to a @ref RTC_TimeTypeDef structure that
  *   will contain the returned current time configuration.
  * @retval None
  */
void RTC_GetTime(RTC_Format_TypeDef RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint8_t  tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Fill the structure fields with the read parameters */

  RTC_TimeStruct->RTC_Seconds = RTC->TR1;
  RTC_TimeStruct->RTC_Minutes = RTC->TR2;
  /* Get the RTC_TR3 register */
  tmpreg = (uint8_t)RTC->TR3;
  (void) (RTC->DR3) ;

  RTC_TimeStruct->RTC_Hours = (uint8_t)(tmpreg & (uint8_t)~(RTC_TR3_PM));

  RTC_TimeStruct->RTC_H12 = (RTC_H12_TypeDef)(tmpreg & RTC_TR3_PM);
  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_TimeStruct->RTC_Hours = (uint8_t)Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);
  }
}

/**
  * @brief  Get the RTC current date.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *   This parameter can be one of the @ref RTC_Format_TypeDef enumeration.
  * @param  RTC_DateStruct: pointer to a @ref RTC_DateTypeDef structure that
  *   will contain the returned current Date configuration.
  * @retval None
  */
void RTC_GetDate(RTC_Format_TypeDef RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint8_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_DR registers */


  /* Fill the structure fields with the read parameters */
  (void) (RTC->TR1) ;
  RTC_DateStruct->RTC_Date = (uint8_t)(RTC->DR1);
  tmpreg = (uint8_t)RTC->DR2;
  RTC_DateStruct->RTC_Year = (uint8_t)(RTC->DR3);


  RTC_DateStruct->RTC_Month = (RTC_Month_TypeDef)(tmpreg & (uint8_t)(RTC_DR2_MT | RTC_DR2_MU));
  RTC_DateStruct->RTC_WeekDay = (RTC_Weekday_TypeDef)(tmpreg & RTC_DR2_WD);

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_DateStruct->RTC_Year = (uint8_t)Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Year);
    RTC_DateStruct->RTC_Month = (RTC_Month_TypeDef)Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Month);
    RTC_DateStruct->RTC_Date = (uint8_t)Bcd2ToByte((uint8_t)RTC_DateStruct->RTC_Date);
  }
}

/**
  * @brief  Sets the RTC Alarm configuration.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *   This parameter can be one of the @ref RTC_Format_TypeDef enumeration.
  * @param  RTC_AlarmStruct:  pointer to a  @ref RTC_AlarmTypeDef structure that
  *  contains the Alarm configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Alarm is configured
  *          - ERROR: RTC Alarm is not configured
  */
ErrorStatus RTC_SetAlarm(RTC_Format_TypeDef RTC_Format, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  ErrorStatus status = ERROR;
  uint16_t alrawfcount = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR1 & RTC_CR1_FMT) != RESET)
    {
      assert_param(IS_RTC_HOUR12_MAX(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
      assert_param(IS_RTC_HOUR12_MIN(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
    }
    else
    {
      assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
    }
    assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));
    assert_param(IS_RTC_DATE_MAX(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
    assert_param(IS_RTC_DATE_MIN(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
  }
  else
  {
    if ((RTC->CR1 & RTC_CR1_FMT) != RESET)
    {
      assert_param(IS_RTC_HOUR12_MAX(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
      assert_param(IS_RTC_HOUR12_MIN(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
    }
    else
    {
      assert_param(IS_RTC_HOUR24(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
    }

    assert_param(IS_RTC_MINUTES(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)));
    assert_param(IS_RTC_DATE_MAX(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay)));
    assert_param(IS_RTC_DATE_MIN(Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay)));
  }
  assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
  assert_param(IS_RTC_ALARM_DATEWEEKDAY_SEL(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel));
  assert_param(IS_RTC_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Check if the initialiazation mode is not set */
  if ((RTC->ISR1 & RTC_ISR1_INITF) == RESET)
  {
    /* Disable the Alarm in RTC_CR2 register */
    RTC->CR2 &= (uint8_t)~RTC_CR2_ALRAE;

    /* Wait until ALRxWF flag is set */
    while (((RTC->ISR1 & RTC_ISR1_ALRAWF) == RESET) && ( alrawfcount != ALRAWF_TIMEOUT))
    {
      alrawfcount++;
    }

    if ((RTC->ISR1 &  RTC_ISR1_ALRAWF) == RESET)
    {
      status = ERROR;
    }
    else
    {
      /* Check the input parameters format & Configure the Alarm register */
      if (RTC_Format != RTC_Format_BIN)
      {
        RTC->ALRMAR1 = (uint8_t)((RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) | \
                                 (uint8_t)(RTC_AlarmStruct->RTC_AlarmMask & RTC_ALRMAR1_MSK1));

        RTC->ALRMAR2 = (uint8_t)((RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) | \
                                 (uint8_t)((uint8_t)(RTC_AlarmStruct->RTC_AlarmMask << 1) & RTC_ALRMAR2_MSK2));

        RTC->ALRMAR3 = (uint8_t)((uint8_t)((RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) | \
                                           (RTC_AlarmStruct->RTC_AlarmTime.RTC_H12)) | \
                                 (uint8_t)((uint8_t)(RTC_AlarmStruct->RTC_AlarmMask << 2) & RTC_ALRMAR3_MSK3));

        RTC->ALRMAR4 = (uint8_t)((uint8_t)((RTC_AlarmStruct->RTC_AlarmDateWeekDay) | \
                                           (RTC_AlarmStruct->RTC_AlarmDateWeekDaySel)) | \
                                 (uint8_t)((uint8_t)(RTC_AlarmStruct->RTC_AlarmMask << 3) & RTC_ALRMAR4_MSK4));
      }
      else
      {
        RTC->ALRMAR1 = (uint8_t)((ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)) | \
                                 (uint8_t)(RTC_AlarmStruct->RTC_AlarmMask & RTC_ALRMAR1_MSK1));

        RTC->ALRMAR2 = (uint8_t)((ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)) | \
                                 (uint8_t)((uint8_t)(RTC_AlarmStruct->RTC_AlarmMask << 1) & RTC_ALRMAR2_MSK2));

        RTC->ALRMAR3 = (uint8_t)((uint8_t)((ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)) | \
                                           (RTC_AlarmStruct->RTC_AlarmTime.RTC_H12)) | \
                                 (uint8_t)((uint8_t)(RTC_AlarmStruct->RTC_AlarmMask << 2) & RTC_ALRMAR3_MSK3));

        RTC->ALRMAR4 = (uint8_t)((uint8_t)((ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDateWeekDay)) | \
                                           RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
                                 (uint8_t)((uint8_t)(RTC_AlarmStruct->RTC_AlarmMask << 3) & RTC_ALRMAR4_MSK4));
      }
      status = SUCCESS;
    }
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);

  return (ErrorStatus)status;
}

/**
  * @brief  Gets the RTC Alarm configuration.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *   This parameter can be one of the @ref RTC_Format_TypeDef enumeration.
  * @param  RTC_AlarmStruct:  pointer to a  @ref RTC_AlarmTypeDef structure that will
  *  contains the Alarm configuration information of  the RTC.
  * @retval None
  */
void RTC_GetAlarm(RTC_Format_TypeDef RTC_Format, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
  uint8_t tmpreg = 0;
  uint8_t alarmmask = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));


  /* Fill the structure with the read parameters */
  tmpreg = RTC->ALRMAR1;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint8_t)(tmpreg & (uint8_t)(RTC_ALRMAR1_ST | RTC_ALRMAR1_SU));
  alarmmask = (uint8_t)(tmpreg & RTC_ALRMAR1_MSK1);

  tmpreg = RTC->ALRMAR2;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint8_t)(tmpreg & (uint8_t)(RTC_ALRMAR2_MNT | RTC_ALRMAR2_MNU));
  alarmmask = (uint8_t)((alarmmask) | (uint8_t)((uint8_t)(tmpreg & RTC_ALRMAR2_MSK2) >> 1));

  tmpreg = RTC->ALRMAR3;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint8_t)(tmpreg & (uint8_t)(RTC_ALRMAR3_HT | RTC_ALRMAR3_HU));
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (RTC_H12_TypeDef)(tmpreg & RTC_ALRMAR3_PM);
  alarmmask = (uint8_t)((alarmmask) | (uint8_t)((uint8_t)(tmpreg & RTC_ALRMAR3_MSK3) >> 2));

  tmpreg = (uint8_t)(RTC->ALRMAR4);
  RTC_AlarmStruct->RTC_AlarmDateWeekDay = (uint8_t)(tmpreg & (uint8_t)(RTC_ALRMAR4_DT | RTC_ALRMAR4_DU));
  RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = (RTC_AlarmDateWeekDaySel_TypeDef)(tmpreg & RTC_ALRMAR4_WDSEL);
  alarmmask = (uint8_t)((alarmmask) | (uint8_t)((uint8_t)(tmpreg & RTC_ALRMAR4_MSK4) >> 3));

  RTC_AlarmStruct->RTC_AlarmMask = alarmmask;

  if (RTC_Format == RTC_Format_BIN)
  {
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds);
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
  }
}

/**
  * @brief  Enables or disables the RTC Alarm.
  * @param  NewState: new state of the alarm. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlarmCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Configure the Alarm state */
  if (NewState != DISABLE)
  {
    RTC->CR2 |= (uint8_t)RTC_CR2_ALRAE;
  }
  else
  {
    RTC->CR2 &= (uint8_t)~RTC_CR2_ALRAE;
  }

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
}

/**
  * @brief  Configures the RTC Wakeup clock source.
  * @param  RTC_WakeupClockSrc: specifies the Wakeup clock source,
  * this parameter  can be one of the @ref RTC_WakeupClockSrc_TypeDef enumeration.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC Wakeup clock source configured
  *         - ERROR: RTC Wakeup clock source not configured
  */
ErrorStatus RTC_WakeUpClockConfig(RTC_WakeUpClock_TypeDef RTC_WakeupClock)
{
  ErrorStatus status = ERROR;
  uint16_t wutwfcount = 0;

  /* Check the parameters */
  assert_param(IS_RTC_WAKEUP_CLOCK(RTC_WakeupClock));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Disable the Wake-up timer in RTC_CR2 register */
  RTC->CR2 &= (uint8_t)~RTC_CR2_WUTE;

  /* Wait until WUTWF flag is set */
  while (((RTC->ISR1 & RTC_ISR1_WUTWF) == RESET) && ( wutwfcount != WUTWF_TIMEOUT))
  {
    wutwfcount++;
  }

  /* Clear the Wakeup Timer clock source bits in CR1 register */
  RTC->CR1 &= (uint8_t)~RTC_CR1_WUCKSEL;

  /* Configure the clock source */
  RTC->CR1 |= (uint8_t)RTC_WakeupClock;


  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);

  if ((RTC->ISR1 & RTC_ISR1_WUTWF) == RESET)
  {
    status = ERROR;
  }
  else
  {
    status = SUCCESS;
  }

  return (ErrorStatus)status;
}

/**
  * @brief  Enables or Disables the RTC Wakeup timer.
  * @param  NewState: new state of the Wakeup timer. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WakeUpCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  if (NewState != DISABLE)
  {
    /* Enable the Wakeup Timer */
    RTC->CR2 |= (uint8_t)RTC_CR2_WUTE;
  }
  else
  {
    /* Disable the Wakeup Timer */
    RTC->CR2 &= (uint8_t)~RTC_CR2_WUTE;
  }

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
}

/**
  * @brief  Sets the RTC Wakeup counters.
  * @param  RTC_WakeupCounter: specifies the Wake up counter,
  *  This parameter can be a value from 0x0000 to 0xFFFF.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC Wakeup countersconfigured
  *         - ERROR: RTC Wakeup counters not configured
  */
ErrorStatus RTC_SetWakeUpCounter(uint16_t RTC_WakeupCounter)
{
  ErrorStatus status = ERROR;
  uint16_t wutwfcount = 0;

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Disable the Wake-up timer in RTC_CR2 register */
  RTC->CR2 &= (uint8_t)~RTC_CR2_WUTE;

  /* Wait until WUTWF flag is set */
  while (((RTC->ISR1 & RTC_ISR1_WUTWF) == RESET) && ( wutwfcount != WUTWF_TIMEOUT))
  {
    wutwfcount++;
  }

  /* Configure the Wakeup Timer counter */
  RTC->WUTRH = (uint8_t)(RTC_WakeupCounter >> 8);
  RTC->WUTRL = (uint8_t)(RTC_WakeupCounter);

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);

  if ((RTC->ISR1 & RTC_ISR1_WUTWF) == RESET)
  {
    status = ERROR;
  }
  else
  {
    status = SUCCESS;
  }

  return (ErrorStatus)status;
}

/**
  * @brief  Returns the RTC Wakeup timer counter value.
  * @param  None
  * @retval RTC Wakeup Counter value
  */
uint16_t RTC_GetWakeUpCounter(void)
{
  uint16_t tmpreg = 0;

  /* Get the counter value */
  tmpreg = ((uint16_t)RTC->WUTRH) << 8;
  tmpreg |= RTC->WUTRL;

  return (uint16_t)tmpreg;
}

/**
  * @brief  Adds or subtracts one hour from the current time depending on
  *  the daylight saving parameter.
  * @param  RTC_DayLightSaving: the day light saving Mode
  *   This parameter can be one of the @ref RTC_DayLightSaving_TypeDef enumeration.
  * @param  RTC_StoreOperation: the day light saving store operation
  *   This parameter can be one of the @ref RTC_StoreOperation_TypeDef enumeration.
  * @retval None
  */
void RTC_DayLightSavingConfig(RTC_DayLightSaving_TypeDef RTC_DayLightSaving,
                              RTC_StoreOperation_TypeDef RTC_StoreOperation)
{
  /* Check the parameters */
  assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
  assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);


  /* Clear the bits to be configured */
  RTC->CR3 &= (uint8_t)~(RTC_CR3_BCK);

  /* Configure the RTC_CR3 register */
  RTC->CR3 |= (uint8_t)((uint8_t)RTC_DayLightSaving | (uint8_t)RTC_StoreOperation);

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
}

/**
  * @brief  Returns the stored operation.
  * @param  None
  * @retval the stores operation, this parameter can be one of
  * the @ref RTC_StoreOperation_TypeDef enumeration.
  */

RTC_StoreOperation_TypeDef  RTC_GetStoreOperation(void)
{
  return (RTC_StoreOperation_TypeDef)(RTC->CR3 & RTC_CR3_BCK);
}

/**
  * @brief  Configures the RTC output for the output pin.
  * @param  RTC_OutputSel: Specifies which signal will be mapped to the output.
  * This parameter can be one parameter from the @ref RTC_OutputSel_TypeDef enumeration.
  * @param  RTC_OutputPolarity: Specifies the polarity of the output signal.
  * This parameter can be one parameter from the @ref RTC_OutputPolarity_TypeDef enumeration.
  * @retval None
  */

void RTC_OutputConfig(RTC_Output_TypeDef RTC_Output,
                      RTC_OutputPolarity_TypeDef RTC_OutputPolarity)
{
  /* Check the parameters */
  assert_param(IS_RTC_OUTPUT_SEL(RTC_Output));
  assert_param(IS_RTC_OUTPUT_POL(RTC_OutputPolarity));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  /* Clear the bits to be configured */
  RTC->CR3 &= (uint8_t)~(RTC_CR3_OSEL | RTC_CR3_POL);

  /* Configure the output selection and polarity */
  RTC->CR3 |= (uint8_t)((uint8_t)RTC_Output | (uint8_t)RTC_OutputPolarity);

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *   This parameter can be one of the @ref RTC_Flag_TypeDef enumeration.
  * @retval Status of RTC_FLAG (SET or RESET)
  */
FlagStatus RTC_GetFlagStatus(RTC_Flag_TypeDef RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint16_t tmpreg = 0;
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

  /* Get all the flags */
  tmp = (uint16_t)((uint16_t)RTC->ISR2 << 8);
  tmpreg = (uint16_t)( tmp | (uint8_t)RTC->ISR1);

  /* Return the status of the flag */
  if ((tmpreg & (uint16_t)RTC_FLAG) != RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return (FlagStatus)bitstatus;
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTC_FLAG: specifies the RTC flag to clear.
  *   This parameter can be any combination of the @ref RTC_Flag_TypeDef enumeration.
  * @retval None
  */
void RTC_ClearFlag(RTC_Flag_TypeDef RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

  /* Clear the Flags in the RTC_ISR register */
  RTC->ISR2 = (uint8_t)(~((uint8_t)((uint16_t)RTC_FLAG >> 8))) ;
  RTC->ISR1 = (uint8_t)((uint8_t)((uint16_t)~((uint16_t)RTC_FLAG)) & ((uint8_t)~(RTC_ISR1_INIT)));
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_IT: specifies the RTC interrupt source to check.
  *   This parameter can be one of the @ref RTC_IT_TypeDef enumeration.
  * @retval Status of RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(RTC_IT_TypeDef RTC_IT)
{
  ITStatus bitstatus = RESET;
  uint8_t status = 0, tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_GET_IT(RTC_IT));

  /* Get the Interrupt enable Status */
  status = (uint8_t)(RTC->CR2 & RTC_IT);

  /* Get the Interrupt pending bit */
  tmpreg = (uint8_t)(RTC->ISR2 & (uint8_t)(RTC_IT >> 4));

  /* Get the status of the Interrupt */
  if ((status != RESET) && (tmpreg != RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return (ITStatus)bitstatus;
}

/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_IT: specifies the RTC interrupt pending bit to clear.
  *   This parameter can be any combination of the @ref RTC_IT_TypeDef enumeration.
  * @retval None
  */
void RTC_ClearITPendingBit(RTC_IT_TypeDef RTC_IT)
{
  uint8_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_IT(RTC_IT));

  /* get flag position */
  flagpos = (uint8_t)(RTC_IT >> 4);
  /* Clear the interrupt pending bits in the RTC_ISR registers */
  RTC->ISR2 = (uint8_t)~ flagpos;
}

/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  NewState: new state of the RTC clock output
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CalibOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC_WriteProtectionCmd(DISABLE);

  if (NewState != DISABLE)
  {
    /* Enable the RTC clock output */
    RTC->CR3 |= (uint8_t)RTC_CR3_COE;
  }
  else
  {
    /* Disable the RTC clock output */
    RTC->CR3 &= (uint8_t)~RTC_CR3_COE;
  }

  /* Enable the write protection for RTC registers */
  RTC_WriteProtectionCmd(ENABLE);
}

/**
    * @addtogroup RTC_Private_Functions
    * @{
    */
/**
  * @brief  Converts a 2 digit decimal to BCD format
  * @param  Value: Byte to be converted.
  * @retval Converted byte
  */
static uint8_t ByteToBcd2(uint8_t Value)
{
  uint8_t bcdhigh = 0;

  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }

  return  (uint8_t)((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Converts from 2 digit BCD to Binary format
  * @param  Value: BCD value to be converted.
  * @retval Converted word
  */
static uint8_t Bcd2ToByte(uint8_t Value)
{
  uint8_t tmp = 0;

  tmp = (uint8_t)(((uint8_t)((uint8_t)Value & (uint8_t)0xF0) >> 4) * (uint8_t)10);

  return (uint8_t)(tmp + (Value & (uint8_t)0x0F));
}
/**
    * @}
    */
/**
    * @}
    */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

