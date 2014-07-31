/**
  ******************************************************************************
  * @file    demo_calendar.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for demo_calendar.c
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
#ifndef __DEMO_CALENDAR_H
#define __DEMO_CALENDAR_H


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#include "stm8l15x.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t ReadDigit(uint8_t* ptr, uint8_t ColBegin, uint8_t ValueMax, uint8_t ValueMin) ;
void SetCursorPosition(uint8_t* ptr, uint8_t Line, uint8_t Offset);
void ToggleCursorPosition(uint8_t* ptr, uint8_t Line, uint8_t Offset);
void Calendar_Init(void);
void Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(void);
void Date_Regulate(void);
void Date_Adjust(void);
void Date_Display(void);
void Date_Show(void);
void Alarm_Regulate(void);
void Alarm_Adjust(void);
void Alarm_Display(void);
void Alarm_Show(void);
uint16_t DayOfWeek(uint16_t nYear, uint16_t nMonth, uint16_t nDay);
uint16_t CountOfFeb29(uint16_t nYear);
bool IsLeapYear(uint16_t nYear);

/* Private functions ---------------------------------------------------------*/

#endif /* __DEMO_CALENDAR_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
