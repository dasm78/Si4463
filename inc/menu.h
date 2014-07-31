/**
  ******************************************************************************
  * @file    menu.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for menu.c
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
#ifndef __MENU_H
#define __MENU_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "joystick_button.h"
#include "stm8_eval_lcd.h"
#include "demo_help.h"
#include "demo_about.h"
#include "stm8_eval.h"
#include "demo_thermometer.h"
#include "demo_iddmeasure.h"
#include "demo_calendar.h"
#include "demo_lowpower.h"
#include "demo_audio.h"
#include "alarm.h"
#include<stdio.h>

/* Exported types ------------------------------------------------------------*/
/** State ID
  * @note Table element must not be equal to 0 as this element is
  * used to detect the end of table.
 */
typedef enum {
    /* Level 1 */
    HELP = 1,
    CALENDAR_DEMO,
    THERMOMETER_DEMO,
		IDDMEASURE_DEMO,
		LOWPOWER_DEMO,
		VOICE_DEMO,
    ABOUT,
    /* Level 2 */
    TIME_DEMO,
		DATE_DEMO,
		ALARM_DEMO,
		RUN_DEMO,
		WFI_DEMO,
		WFE_DEMO,
		ACTIVEHALT_DEMO,
		HALT_DEMO,
		VOICERECORDER_DEMO,
		VOICEPLAYER_DEMO,
    /* Level 3 */
    TIMESHOW_DEMO,
  	TIMEADJUST_DEMO,
		DATESHOW_DEMO,
  	DATEADJUST_DEMO,
		ALARMSHOW_DEMO,
  	ALARMADJUST_DEMO,		
		RUN_16MHZ_DEMO,
		RUN_8MHZ_DEMO,
		RUN_4MHZ_DEMO,
		RUN_2MHZ_DEMO,
    WFI_EXTI_DEMO,
		WFI_ALARM_DEMO,
    WFE_EXTEVENT_DEMO,
		WFE_COMPEVENT_DEMO,
		ACTIVEHALT_EXTI_DEMO,
		ACTIVEHALT_ALARM_DEMO,
    HALT_EXTI_DEMO,
		HALT_COMP_DEMO,
    /* Execution */
    EXE_HELP,
    EXE_TIMESHOW,
	  EXE_TIMEADJUST,
		EXE_DATESHOW,
	  EXE_DATEADJUST,
		EXE_ALARMSHOW,
	  EXE_ALARMADJUST,
    EXE_THERMOMETER,
	  EXE_IDDMEASURE,
		EXE_RUN_16MHZ,
		EXE_RUN_8MHZ,
		EXE_RUN_4MHZ,
		EXE_RUN_2MHZ,
		EXE_WFI_EXTI,
		EXE_WFI_ALARM,
		EXE_WFE_EXTEVENT,
		EXE_WFE_COMPEVENT,
		EXE_ACTIVEHALT_EXTI,
		EXE_ACTIVEHALT_ALARM,
		EXE_HALT_EXTI,
		EXE_HALT_COMP,
		EXE_VOICERECORDER,
		EXE_VOICEPLAYER,
	  EXE_ABOUT
} STATE_ID_T;

/** Menu NextState */
typedef struct
{
    STATE_ID_T State;
    JOYState_TypeDef Key;
    STATE_ID_T NextState;
}
MENU_NEXTSTATE_T;

/** Menu state */
typedef struct
{
    STATE_ID_T State;
    char* pText;
    void (*pFunc)(void);
}
MENU_STATE_T;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern STATE_ID_T State;
/* Exported functions --------------------------------------------------------*/
void MenuInit(void);
void MenuUpdate(JOYState_TypeDef ujoystick);
void MenuDisplay(void);

#endif /* __MENU_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
