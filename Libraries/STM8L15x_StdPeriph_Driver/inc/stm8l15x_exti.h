/**
  ******************************************************************************
  * @file    stm8l15x_exti.h
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    07/14/2010
  * @brief   This file contains all the functions prototypes for the EXTI firmware
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
#ifndef __STM8L15x_EXTI_H
#define __STM8L15x_EXTI_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/

/** @addtogroup EXTI_Exported_Types
  * @{
  */

/**
  * @brief EXTI Sensitivity values
  */
typedef enum
{
  EXTI_Trigger_Falling_Low    = (uint8_t)0x00, /*!< Interrupt on Falling edge and Low level */
  EXTI_Trigger_Rising         = (uint8_t)0x01, /*!< Interrupt on Rising edge only */
  EXTI_Trigger_Falling        = (uint8_t)0x02, /*!< Interrupt on Falling edge only */
  EXTI_Trigger_Rising_Falling = (uint8_t)0x03  /*!< Interrupt on Rising and Falling edges */
} EXTI_Trigger_TypeDef;

/**
  * @brief EXTI halfPort possible values
  */
typedef enum
{
  EXTI_HalfPort_B_LSB  = (uint8_t)0x01, /*!< Interrupt selector PB(3:0) */
  EXTI_HalfPort_B_MSB  = (uint8_t)0x02, /*!< Interrupt selector PB(7:4) */
  EXTI_HalfPort_D_LSB  = (uint8_t)0x04, /*!< Interrupt selector PD(3:0) */
  EXTI_HalfPort_D_MSB  = (uint8_t)0x08, /*!< Interrupt selector PD(7:4) */
  EXTI_HalfPort_E_LSB  = (uint8_t)0x10, /*!< Interrupt selector PE(3:0) */
  EXTI_HalfPort_E_MSB  = (uint8_t)0x20, /*!< Interrupt selector PE(7:4) */
  EXTI_HalfPort_F_LSB  = (uint8_t)0xC0  /*!< Interrupt selector PF(3:0) */
} EXTI_HalfPort_TypeDef;

/**
  * @brief EXTI Port possible values
  */
typedef enum
{
  EXTI_Port_B = (uint8_t)0x00, /*!< GPIO Port B */
  EXTI_Port_D = (uint8_t)0x02, /*!< GPIO Port D */
  EXTI_Port_E = (uint8_t)0x04, /*!< GPIO Port E */
  EXTI_Port_F = (uint8_t)0x06  /*!< GPIO Port F */
} EXTI_Port_TypeDef;

/**
  * @brief EXTI PinNum possible values
  */
typedef enum
{
  EXTI_Pin_0 = (uint8_t)0x00, /*!< GPIO Pin 0 */
  EXTI_Pin_1 = (uint8_t)0x02, /*!< GPIO Pin 1 */
  EXTI_Pin_2 = (uint8_t)0x04, /*!< GPIO Pin 2 */
  EXTI_Pin_3 = (uint8_t)0x06, /*!< GPIO Pin 3 */
  EXTI_Pin_4 = (uint8_t)0x10, /*!< GPIO Pin 4 */
  EXTI_Pin_5 = (uint8_t)0x12, /*!< GPIO Pin 5 */
  EXTI_Pin_6 = (uint8_t)0x14, /*!< GPIO Pin 6 */
  EXTI_Pin_7 = (uint8_t)0x16  /*!< GPIO Pin 7 */
} EXTI_Pin_TypeDef;

/**
  * @brief EXTI IT pending bit possible values
  */
typedef enum
{
  EXTI_IT_Pin0    = (uint8_t)0x01, /*!< GPIO Pin pos 0 */
  EXTI_IT_Pin1    = (uint8_t)0x02, /*!< GPIO Pin pos 1 */
  EXTI_IT_Pin2    = (uint8_t)0x04, /*!< GPIO Pin pos 2 */
  EXTI_IT_Pin3    = (uint8_t)0x08, /*!< GPIO Pin pos 3 */
  EXTI_IT_Pin4    = (uint8_t)0x10, /*!< GPIO Pin pos 4 */
  EXTI_IT_Pin5    = (uint8_t)0x20, /*!< GPIO Pin pos 5 */
  EXTI_IT_Pin6    = (uint8_t)0x40, /*!< GPIO Pin pos 6 */
  EXTI_IT_Pin7    = (uint8_t)0x80, /*!< GPIO Pin pos 7 */
  EXTI_IT_PortB   = (uint8_t)0xF1, /*!< GPIO Port B */
  EXTI_IT_PortD   = (uint8_t)0xF2, /*!< GPIO Port D */
  EXTI_IT_PortE   = (uint8_t)0xF4, /*!< GPIO Port E */
  EXTI_IT_PortF   = (uint8_t)0xF8  /*!< GPIO Port F */
} EXTI_IT_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup EXTI_Private_Macros
  * @{
  */

/**
  * @brief Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief Macro used by the assert function in order to check the different values
  *  of EXTI Sensitivity
  */
#define IS_EXTI_TRIGGER(TRIGGER) \
  (((TRIGGER) == EXTI_Trigger_Falling_Low)  || \
   ((TRIGGER) == EXTI_Trigger_Rising) || \
   ((TRIGGER) == EXTI_Trigger_Falling) || \
   ((TRIGGER) == EXTI_Trigger_Rising_Falling))

/**
  * @brief Macro used by the assert function in order to check the different
  *   half ports values for configuration.
  */
#define IS_EXTI_HALFPORT(HALFPORT) \
  (((HALFPORT) == EXTI_HalfPort_B_LSB) ||\
   ((HALFPORT) == EXTI_HalfPort_B_MSB) ||\
   ((HALFPORT) == EXTI_HalfPort_D_LSB) ||\
   ((HALFPORT) == EXTI_HalfPort_D_MSB) ||\
   ((HALFPORT) == EXTI_HalfPort_E_LSB) ||\
   ((HALFPORT) == EXTI_HalfPort_E_MSB) ||\
   ((HALFPORT) == EXTI_HalfPort_F_LSB))

/**
  * @brief Macro used by the assert function in order to check the different Port Number values
  */
#define IS_EXTI_PORT(PORT) (((PORT) == EXTI_Port_B) ||\
                            ((PORT) == EXTI_Port_D) ||\
                            ((PORT) == EXTI_Port_E) ||\
                            ((PORT) == EXTI_Port_F))

/**
  * @brief Macro used by the assert function in order to check the different Pin numbers values
  */
#define IS_EXTI_PINNUM(PINNUM) \
  (((PINNUM) == EXTI_Pin_0) ||\
   ((PINNUM) == EXTI_Pin_1) ||\
   ((PINNUM) == EXTI_Pin_2) ||\
   ((PINNUM) == EXTI_Pin_3) ||\
   ((PINNUM) == EXTI_Pin_4) ||\
   ((PINNUM) == EXTI_Pin_5) ||\
   ((PINNUM) == EXTI_Pin_6) ||\
   ((PINNUM) == EXTI_Pin_7))

/**
  * @brief Macro used by the assert function in order to check the different flags values
  */
#define IS_EXTI_ITPENDINGBIT(ITPENDINGBIT) \
  (((ITPENDINGBIT) == EXTI_IT_Pin0) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin1) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin2) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin3) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin4) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin5) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin6) ||\
   ((ITPENDINGBIT) == EXTI_IT_Pin7) ||\
   ((ITPENDINGBIT) == EXTI_IT_PortB)   ||\
   ((ITPENDINGBIT) == EXTI_IT_PortD)   ||\
   ((ITPENDINGBIT) == EXTI_IT_PortE)   ||\
   ((ITPENDINGBIT) == EXTI_IT_PortF))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup EXTI_Exported_Functions
  * @{
  */

void EXTI_DeInit(void);
void EXTI_SetPortSensitivity(EXTI_Port_TypeDef EXTI_Port, EXTI_Trigger_TypeDef EXTI_Trigger);
void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin, EXTI_Trigger_TypeDef EXTI_Trigger);
void EXTI_SetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort, FunctionalState NewState);
EXTI_Trigger_TypeDef EXTI_GetPortSensitivity(EXTI_Port_TypeDef EXTI_Port);
EXTI_Trigger_TypeDef EXTI_GetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin);
FunctionalState EXTI_GetHalfPortSelection(EXTI_HalfPort_TypeDef EXTI_HalfPort);
ITStatus EXTI_GetITStatus(EXTI_IT_TypeDef EXTI_IT);
void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT);

/**
  * @}
  */

#endif /* __STM8L15x_EXTI_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
