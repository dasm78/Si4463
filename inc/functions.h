/**
  ******************************************************************************
  * @file    function.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for function.c
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
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

/* Includes ------------------------------------------------------------------*/
#include "stm8_eval_lcd.h"
#include "menu.h"

/* Exported types ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
/* Help Menu Status - bit definition */
/* Bit[3..0] used as counter */
#define HELP_DISPLAY_STATUS_ENABLE                7

/* Application Status 1 - bit definition */
#define APPLICATION_STATUS_1_EXT_IT               0
#define APPLICATION_STATUS_1_RTCAWU_IT            1
#define APPLICATION_STATUS_1_PVD_IT               2
#define APPLICATION_STATUS_1_PVD_LEVEL            3
#define APPLICATION_STATUS_1_NAVIGATION_ENABLED   4
#define APPLICATION_STATUS_1_LED_ACTIVITY_ENABLED 5

/* LEDs I/Os */

#define LEDBICOLOR_PORT (GPIOB)
#define LEDBICOLOR_PIN  (GPIO_Pin_0)

#define LEDS_PORT (GPIOD)
#define LED2_PIN  (GPIO_Pin_4)
#define LED3_PIN  (GPIO_Pin_5)
#define LED4_PIN  (GPIO_Pin_6)


/* Exported macro ------------------------------------------------------------*/
#define LEDS_OFF()        GPIO_SetBits(LEDS_PORT, (LED2_PIN | LED3_PIN | LED4_PIN))
#define LEDS_ON()         GPIO_ResetBits(LEDS_PORT, ( LED2_PIN | LED3_PIN | LED4_PIN))
#define LEDS_TOG()        GPIO_ToggleBits(LEDS_PORT, ( LED2_PIN | LED3_PIN | LED4_PIN))
#define LEDBICOLOR_TOG()  GPIO_ToggleBits(LEDBICOLOR_PORT,LEDBICOLOR_PIN )

#define LEDBICOLOR_OFF()  GPIO_SetBits(LEDBICOLOR_PORT, LEDBICOLOR_PIN)
#define LED2_OFF()        GPIO_SetBits(LEDS_PORT, LED2_PIN)
#define LED3_OFF()        GPIO_SetBits(LEDS_PORT, LED3_PIN)
#define LED4_OFF()        GPIO_SetBits(LEDS_PORT, LED4_PIN)
#define LEDBICOLOR_ON()   GPIO_ResetBits(LEDBICOLOR_PORT, LEDBICOLOR_PIN)
#define LED2_ON()         GPIO_ResetBits(LEDS_PORT, LED2_PIN)
#define LED3_ON()         GPIO_ResetBits(LEDS_PORT, LED3_PIN)
#define LED4_ON()         GPIO_ResetBits(LEDS_PORT, LED4_PIN)

/* Exported variables --------------------------------------------------------*/
extern uint32_t GTimeStamp;
extern uint16_t TimeOutStartTime;
extern uint8_t EEPBuffer[];
extern uint8_t GUseEeprom;

/* Exported functions --------------------------------------------------------*/
void Init_Application(void);
void Init_SPISimplex(void);
void Init_SPIFullDuplex(void);
void Init_GPIO(void);
void Init_Clock(void);
void Init_TIM3(void);
void Init_TIM4(void);
uint32_t GetTimeStamp(void);
void GetTimeOutStartTime(void);
bool TimeOut(uint16_t Delay);
void WaitDelay(uint16_t Delay);

#endif /* __FUNCTIONS_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
