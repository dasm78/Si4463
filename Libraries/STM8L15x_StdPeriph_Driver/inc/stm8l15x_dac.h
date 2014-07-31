/**
  ******************************************************************************
  * @file    stm8l15x_dac.h
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    07/14/2010
  * @brief   This file contains all the functions prototypes for the DAC firmware
  *          library.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8L15x_DAC_H
#define __STM8L15x_DAC_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup DAC_Exported_Types
  * @{
  */

/**
  * @brief  DAC trigger selection
  */
typedef enum
{
  DAC_Trigger_None     = ((uint8_t)0x10), /*!< DAC trigger None  */
  DAC_Trigger_T4_TRGO  = ((uint8_t)0x00), /*!< DAC trigger TIM4 TRGO  */
  DAC_Trigger_Software = ((uint8_t)0x38)  /*!< DAC trigger software  */
}DAC_Trigger_TypeDef;

/**
  * @brief  DAC data alignement
  */
typedef enum
{
  DAC_Align_12b_R = ((uint8_t)0x00), /*!< DAC alignement  Right 12bit */
  DAC_Align_12b_L = ((uint8_t)0x04), /*!< DAC alignement  Left 12bit */
  DAC_Align_8b_R  = ((uint8_t)0x08)  /*!< DAC alignement  Right 8bit */
}DAC_Align_TypeDef;

/**
  * @brief  DAC Channel selection
  */
typedef enum
{
  DAC_Channel_1 = ((uint8_t)0x00) /*!< DAC Channel 1 selection  */
}DAC_Channel_TypeDef;

/**
  * @brief   DAC output buffer state
  */
typedef enum
{
  DAC_OutputBuffer_Enable  = ((uint8_t)0x00), /*!< DAC output buffer Enabled  */
  DAC_OutputBuffer_Disable = ((uint8_t)0x02)  /*!< DAC output buffer Disabled  */
}DAC_OutputBuffer_TypeDef;

/**
  * @brief  DAC interrupt definition
  */
typedef enum
{
  DAC_IT_DMAUDR = ((uint8_t)0x20) /*!< DMA Underrun Interrupt */
}DAC_IT_TypeDef;

/**
  * @brief  DAC Flag definition
  */
typedef enum
{
  DAC_FLAG_DMAUDR = ((uint8_t)0x01) /*!< DMA Underrun flag  */
}DAC_FLAG_TypeDef;

/**
  * @}
  */


/** @addtogroup DAC_Private_Macros
  * @{
  */
/**
  * @brief Macro used by the assert_param function in order to check the  DAC  Trigger selection
  */
#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None) || \
                                 ((TRIGGER) == DAC_Trigger_T4_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_Software))

/**
  * @brief Macro used by the assert_param function in order to check the DAC data alignement
  */
#define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || \
                             ((ALIGN) == DAC_Align_12b_L) || \
                             ((ALIGN) == DAC_Align_8b_R))
/**
  * @brief Macro used by the assert_param function in order to check the  DAC Channel selection
  */
#define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1))


/**
  * @brief Macro used by the assert_param function in order to check the  DAC Buffer state
  */
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || \
    ((STATE) == DAC_OutputBuffer_Disable))
/**
  * @brief Macro used by the assert_param function in order to check the  DAC  Flag to get status
  */
#define IS_DAC_GET_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))

/**
  * @brief Macro used by the assert_param function in order to check the  DAC interrupts
  */
#define IS_DAC_IT(IT) (((IT) == DAC_IT_DMAUDR))

/**
  * @brief Macro used by the assert_param function in order to check the  DAC Flags
  */
#define IS_DAC_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))

/**
  * @brief Macro used by the assert_param function in order to check the  DAC Data
  */
#define IS_DAC_DATA_12R(DATA) ((DATA) <= 0x0FFF)
#define IS_DAC_DATA_12L(DATA) ((((DATA) <= 0xFFF0) && ((DATA) >= 0x0010)) || ((DATA) == 0x0000))
#define IS_DAC_DATA_08R(DATA) ((DATA) <= 0x00FF)
/**
  * @}
  */

/** @addtogroup DAC_Exported_Functions
  * @{
  */
void DAC_DeInit(void);
void DAC_Init(DAC_Channel_TypeDef DAC_Channel, DAC_Trigger_TypeDef DAC_Trigger,
              DAC_OutputBuffer_TypeDef DAC_OutputBuffer);
void DAC_Cmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState);
void DAC_ITConfig(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT,
                  FunctionalState NewState);
void DAC_DMACmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(DAC_Channel_TypeDef DAC_Channel, FunctionalState NewState);
void DAC_SetChannel1Data(DAC_Align_TypeDef DAC_Align, uint16_t DAC_Data);
uint16_t DAC_GetDataOutputValue(DAC_Channel_TypeDef DAC_Channel);
FlagStatus DAC_GetFlagStatus(DAC_Channel_TypeDef DAC_Channel, DAC_FLAG_TypeDef DAC_FLAG);
void DAC_ClearFlag(DAC_Channel_TypeDef DAC_Channel, DAC_FLAG_TypeDef DAC_FLAG);
ITStatus DAC_GetITStatus(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT);
void DAC_ClearITPendingBit(DAC_Channel_TypeDef DAC_Channel, DAC_IT_TypeDef DAC_IT);

/**
  * @}
  */

#endif /*__STM8L15x_DAC_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
