/**
  ******************************************************************************
  * @file    joystick_button.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for joystick_button.c
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
#ifndef __JOYSTICK_BUTTON_H
#define __JOYSTICK_BUTTON_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8_eval.h"
/* Exported types ------------------------------------------------------------*/

/** Button ID
 */
typedef enum {
    B_NONE = 1,
    B_RELEASED,
    B_PRESSED
} BUTTON_ID_T;

/* Exported constants --------------------------------------------------------*/
/* Button Status - bit definition */
#define BUTTON_STATUS_JOYSTICK_DEBOUNCE_ENABLE    0
#define BUTTON_STATUS_BUTTON_DEBOUNCE_ENABLE      1

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint8_t ButtonStatus;

/* Exported functions --------------------------------------------------------*/
JOYState_TypeDef ReadJoystick(void);
BUTTON_ID_T ReadButton(void);

#endif /*__JOYSTICK_BUTTON_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

