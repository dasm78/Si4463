/**
  ******************************************************************************
  * @file    demo_lowpower.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for demo_lowpower.c
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
#ifndef __DEMO_LOWPOWER_H
#define __DEMO_LOWPOWER_H


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#include "stm8l15x.h"

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SetSysClockTo16(void);
void SetSysClockTo8(void);
void SetSysClockTo4(void);
void SetSysClockTo2(void);
void EnterWFIMode_EXTI(void);
void EnterWFIMode_RTCAlarm(void);
void EnterWFEMode_EXTEvent(void);
void EnterWFEMode_COMPEvent(void);
void EnterActiveHaltMode_EXTI(void);
void EnterActiveHaltMode_RTCAlarm(void);
void EnterHaltMode_EXTI(void);
void EnterHaltMode_COMP(void);
/* Private functions ---------------------------------------------------------*/

#endif /* __DEMO_LOWPOWER_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
