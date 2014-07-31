/**
  ******************************************************************************
  * @file    stm8l15x_dac.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    07/14/2010
  * @brief   This file provides all the DAC firmware functions.
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
#include "stm8l15x_dac.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
    * @addtogroup DAC_Public_Functions
    * @{
    */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DAC_DeInit(void)
{
  DAC->CR1 = DAC_CR1_RESET_VALUE;
  DAC->CR2 = DAC_CR2_RESET_VALUE;
  DAC->SWTRIGR = DAC_SWTRIGR_RESET_VALUE;
  DAC->SR = DAC_SR_RESET_VALUE;
  DAC->RDHRH = DAC_RDHRH_RESET_VALUE;
  DAC->RDHRL = DAC_RDHRL_RESET_VALUE;
  DAC->LDHRH = DAC_LDHRH_RESET_VALUE;
  DAC->LDHRL = DAC_LDHRL_RESET_VALUE;
  DAC->DHR8 = DAC_DHR8_RESET_VALUE;
  DAC->DORH = DAC_DORH_RESET_VALUE;
  DAC->DORL = DAC_DORL_RESET_VALUE;
}

/**
  * @brief  Initializes the DAC according to the specified parameters.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_Trigger : the selected DAC trigger from @ref DAC_Trigger_TypeDef enumeration.
  * @param  DAC_OutputBuffer : the status of DAC Buffer from @ref DAC_OutputBuffer_TypeDef enumeration.
  * @retval None
  */
void DAC_Init(DAC_Channel_TypeDef DAC_Channel, DAC_Trigger_TypeDef DAC_Trigger,
              DAC_OutputBuffer_TypeDef DAC_OutputBuffer)
{
  uint8_t tmpreg1 = 0;

  /* Check the DAC parameters */
  assert_param(IS_DAC_TRIGGER(DAC_Trigger));
  assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_OutputBuffer));

  if ( DAC_Channel ==  DAC_Channel_1)
  {
    /*---------------------------- DAC CR1 Configuration --------------------------*/
    /* Get the DAC CR value */
    tmpreg1 = DAC->CR1;
    /* Clear BOFFx, TENx, TSELx bits */
    tmpreg1 &= (uint8_t)~(DAC_CR1_BOFF | DAC_CR1_TEN | DAC_CR1_TSEL );
    /* Configure for the selected DAC channel: buffer output, trigger*/
    /* Set BOFFx bit according to DAC_OutputBuffer value */
    tmpreg1 |= (uint8_t)(DAC_OutputBuffer);

    if (DAC_Trigger != DAC_Trigger_None)
    {
      /* Set TSELx and TEN  bits according to DAC_Trigger value */
      tmpreg1 |= (uint8_t)(DAC_CR1_TEN | DAC_Trigger) ;
    }
    /* Write to DAC CR1 */
    DAC->CR1 = tmpreg1;
  }
}

/**
  * @brief  Enables or disables the specified DAC channel.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the DAC channel. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_Cmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if ( DAC_Channel ==  DAC_Channel_1)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DAC channel */
      DAC->CR1 |= DAC_CR1_EN;
    }
    else
    {
      /* Disable the selected DAC channel */
      DAC->CR1 &= (uint8_t) ~(DAC_CR1_EN);
    }
  }
}

/**
  * @brief  Enables or disables the specified DAC interrupts.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_IT : the selected DAC interrupt from @ref DAC_IT_TypeDef enumeration.
  * @param  NewState : new state of the DAC interrupt .This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DAC_ITConfig(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT,
                  FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_DAC_IT(DAC_IT));
  if ( DAC_Channel == DAC_Channel_1)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DAC interrupts */
      DAC->CR2 |=  (uint8_t)(DAC_IT);
    }
    else
    {
      /* Disable the selected DAC interrupts */
      DAC->CR2 &= (uint8_t)(~(DAC_IT));
    }
  }
}

/**
  * @brief  Enables or disables the specified DAC channel DMA request.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the selected DAC channel DMA request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void DAC_DMACmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if ( DAC_Channel == DAC_Channel_1)
  {
    if (NewState != DISABLE)
    {
      /* Enable the selected DAC channel DMA request */
      DAC->CR2 |= DAC_CR2_DMAEN;
    }
    else
    {
      /* Disable the selected DAC channel DMA request */
      DAC->CR2 &= (uint8_t)~(DAC_CR2_DMAEN);
    }
  }
}

/**
  * @brief  Enables or disables the selected DAC channel software trigger.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  NewState : new state of the selected DAC channel software trigger.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void DAC_SoftwareTriggerCmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if ( DAC_Channel == DAC_Channel_1)
  {
    if (NewState != DISABLE)
    {
      /* Enable software trigger for the selected DAC channel */
      DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG;
    }
    else
    {
      /* Disable software trigger for the selected DAC channel */
      DAC->SWTRIGR &= (uint8_t)~(DAC_SWTRIGR_SWTRIG);
    }
  }
}

/**
  * @brief  Set the specified data holding register value for DAC channel1.
  * @param  DAC_Align : Specifies the data alignement for DAC channel1 from
  *   @ref DAC_Align_TypeDef enumeration.
  * @param  Data : Data to be loaded in the selected data holding register.
  * @retval None.
  */
void DAC_SetChannel1Data(DAC_Align_TypeDef DAC_Align, uint16_t DAC_Data)
{
  /* Check the parameters */
  assert_param(IS_DAC_ALIGN(DAC_Align));


  if (DAC_Align == DAC_Align_12b_R)
  {
    assert_param(IS_DAC_DATA_12R(DAC_Data));
    /* Set the DAC channel1 selected data holding register */
    DAC->RDHRH = (uint8_t)(((uint16_t)DAC_Data) >> 8);
    DAC->RDHRL = (uint8_t)DAC_Data;
  }
  else if (DAC_Align == DAC_Align_12b_L)
  {
    assert_param(IS_DAC_DATA_12L(DAC_Data));
    /* Set the DAC channel1 selected data holding register */
    DAC->LDHRH = (uint8_t)(((uint16_t)DAC_Data) >> 8);
    DAC->LDHRL = (uint8_t)(DAC_Data);
  }
  else
  {
    assert_param(IS_DAC_DATA_08R(DAC_Data));
    /* Set the DAC channel1 selected data holding register */
    DAC->DHR8 = (uint8_t)(DAC_Data);
  }
}

/**
  * @brief  Returns the last data output value of the selected DAC channel.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @retval The selected DAC channel data output value.
  */
uint16_t DAC_GetDataOutputValue(DAC_Channel_TypeDef DAC_Channel)
{
  uint16_t outputdata = 0, tmpdata = 0;
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));

  tmpdata = ((uint16_t)((uint16_t)DAC->DORH << 8));
  /* Returns the DAC channel data output register value */
  outputdata = (uint16_t)( tmpdata | DAC->DORL);

  return (uint16_t)outputdata;
}

/**
  * @brief  Checks whether the specified DAC flag is set or not.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_FLAG : specifies the flag to check from @ref DAC_FLAG_TypeDef enumeration.
  * @retval FlagStatus The new state of DAC_FLAG (SET or RESET).
  */
FlagStatus DAC_GetFlagStatus(DAC_Channel_TypeDef DAC_Channel, DAC_FLAG_TypeDef DAC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));
  if ( DAC_Channel ==  DAC_Channel_1)
  {
    /* Check the status of the specified DAC flag */
    if ((DAC->SR & DAC_FLAG ) != (uint8_t)RESET)
    {
      /* DAC_FLAG is set */
      bitstatus = SET;
    }
    else
    {
      /* DAC_FLAG is reset */
      bitstatus = RESET;
    }
  }
  /* Return the DAC_FLAG status */
  return  bitstatus;
}


/**
  * @brief  Clears the DAC channelx's pending flags.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_FLAG : specifies the flag to clear from @ref DAC_FLAG_TypeDef enumeration.
  * @retval None.
  */
void DAC_ClearFlag(DAC_Channel_TypeDef DAC_Channel, DAC_FLAG_TypeDef DAC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_FLAG(DAC_FLAG));
  if ( DAC_Channel ==  DAC_Channel_1)
  {
    /* Clear the selected DAC flags */
    DAC->SR = (uint8_t)(~DAC_FLAG);
  }
}

/**
  * @brief   Checks whether the specified DAC interrupt has occurred or not.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_IT : specifies the DAC interrupt source to check from
  *   @ref DAC_IT_TypeDef enumeration.
  * @retval ITStatus The new state of DAC_IT (SET or RESET).
  */
ITStatus DAC_GetITStatus(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT)
{
  ITStatus bitstatus = RESET;
  uint8_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));
  if ( DAC_Channel ==  DAC_Channel_1)
  {
    /* Get the DAC_IT enable bit status */
    enablestatus = (uint8_t)(DAC->CR2 & (DAC_IT)) ;

    /* Check the status of the specified DAC interrupt */
    if (((DAC->SR & (uint8_t)((uint8_t)DAC_IT >> 0x05)) != (uint8_t)RESET) && enablestatus)
    {
      /* DAC_IT is set */
      bitstatus = SET;
    }
    else
    {
      /* DAC_IT is reset */
      bitstatus = RESET;
    }
  }
  /* Return the DAC_IT status */
  return  bitstatus;
}

/**
  * @brief   Clears the DAC channelx’s interrupt pending bits.
  * @param  DAC_Channel : the selected DAC channel from @ref DAC_Channel_TypeDef enumeration.
  * @param  DAC_IT : specifies the DAC interrupt pending bit to clear from
  *   @ref DAC_IT_TypeDef enumeration.
  * @retval None.
  */
void DAC_ClearITPendingBit(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT)
{
  /* Check the parameters */
  assert_param(IS_DAC_CHANNEL(DAC_Channel));
  assert_param(IS_DAC_IT(DAC_IT));
  if ( DAC_Channel ==  DAC_Channel_1)
  {
    /* Clear the selected DAC interrupt pending bits */
    DAC->SR = (uint8_t)(~(uint8_t)((uint8_t)DAC_IT >> 0x05));
  }
}

/**
    * @}
    */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
