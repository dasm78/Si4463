/**
  ******************************************************************************
  * @file    demo_help.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for demo_help.c
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
#ifndef __DEMO_HELP_H
#define __DEMO_HELP_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8_eval_lcd.h"
#include "functions.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Following delay is based on 5ms time base */
/* Define how long each each help message is displayed - Delay = 2s */
#define HELP_PERIOD ((uint16_t)400)

/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void HELP_Exec(void);

#endif /* __DEMO_HELP_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
