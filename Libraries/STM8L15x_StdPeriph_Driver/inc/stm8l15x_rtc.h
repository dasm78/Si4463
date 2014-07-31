/**
  ******************************************************************************
  * @file    stm8l15x_rtc.h
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    07/14/2010
  * @brief   This file contains all the functions prototypes for the RTC firmware
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
#ifndef __STM8L15x_RTC_H
#define __STM8L15x_RTC_H

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Exported variables ------------------------------------------------------- */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @addtogroup RTC_Exported_Enumerations
* @{
*/
/**
* @brief RTC Weekdays
*/

typedef enum
{
  RTC_Weekday_Monday      =  ((uint8_t)0x20), /*!< WeekDay Monday*/
  RTC_Weekday_Tuesday     =  ((uint8_t)0x40), /*!< WeekDay Tuesday */
  RTC_Weekday_Wednesday   =  ((uint8_t)0x60), /*!< WeekDay Wednesday*/
  RTC_Weekday_Thursday    =  ((uint8_t)0x80), /*!< WeekDay Thursday*/
  RTC_Weekday_Friday      =  ((uint8_t)0xA0), /*!< WeekDay Friday*/
  RTC_Weekday_Saturday    =  ((uint8_t)0xC0), /*!< WeekDay Saturday*/
  RTC_Weekday_Sunday      =  ((uint8_t)0xE0)  /*!< WeekDay Sunday*/
}
RTC_Weekday_TypeDef;

/**
* @brief RTC Months
*/

typedef enum
{
  RTC_Month_January   =  ((uint8_t)0x01), /*!< Month is January*/
  RTC_Month_February  =  ((uint8_t)0x02), /*!< Month is February*/
  RTC_Month_March     =  ((uint8_t)0x03), /*!< Month is March*/
  RTC_Month_April     =  ((uint8_t)0x04), /*!< Month is April*/
  RTC_Month_May       =  ((uint8_t)0x05), /*!< Month is May*/
  RTC_Month_June      =  ((uint8_t)0x06), /*!< Month is June*/
  RTC_Month_July      =  ((uint8_t)0x07), /*!< Month is July*/
  RTC_Month_August    =  ((uint8_t)0x08), /*!< Month is August*/
  RTC_Month_September =  ((uint8_t)0x09), /*!< Month is September*/
  RTC_Month_October   =  ((uint8_t)0x10), /*!< Month is October*/
  RTC_Month_November  =  ((uint8_t)0x11), /*!< Month is November*/
  RTC_Month_December  =  ((uint8_t)0x12)  /*!< Month is December*/
}
RTC_Month_TypeDef;

/**
* @brief RTC  HourFormat
*/
typedef enum
{
  RTC_HourFormat_24  = ((uint8_t)0x00), /*!< Hour Format is 24H */
  RTC_HourFormat_12  = ((uint8_t)0x40)  /*!< Hour Format is 12H (using AM/PM) */
}
RTC_HourFormat_TypeDef;


/**
* @brief RTC Time Definitions
*/
typedef enum
{
  RTC_H12_AM     = ((uint8_t)0x00), /*!< AM/PM notation is AM or 24 hour format  */
  RTC_H12_PM     = ((uint8_t)0x40)  /*!< AM/PM notation is PM  */
}
RTC_H12_TypeDef;
/**
* @brief RTC Alarm WeekDay Selection
*/
typedef enum
{
  RTC_AlarmDateWeekDaySel_Date     = ((uint8_t)0x00), /*!< Date/WeekDay selection is Date */
  RTC_AlarmDateWeekDaySel_WeekDay  = ((uint8_t)0x40)  /*!< Date/WeekDay selection is WeekDay */
}
RTC_AlarmDateWeekDaySel_TypeDef;
/**
* @brief RTC Alarm Masks
*/
typedef enum
{
  RTC_AlarmMask_None         =  ((uint8_t)0x00), /*!< Alarm Masks disabled */
  RTC_AlarmMask_Seconds      =  ((uint8_t)0x80), /*!< Alarm Seconds Mask */
  RTC_AlarmMask_Minutes      =  ((uint8_t)0x40), /*!< Alarm Minutes Mask */
  RTC_AlarmMask_Hours        =  ((uint8_t)0x20), /*!< Alarm Hours Mask */
  RTC_AlarmMask_DateWeekDay  =  ((uint8_t)0x10), /*!< Alarm Date/WeekDay Mask */
  RTC_AlarmMask_All          =  ((uint8_t)0xF0)  /*!< Alarm All Mask are enabled*/
}
RTC_AlarmMask_TypeDef;
/**
* @brief RTC Wake-up Clock Source for subseconds periodic interrupts
*/
typedef enum
{
  RTC_WakeUpClock_RTCCLK_Div16    = ((uint8_t)0x00), /*!< (RTC clock) div 16*/
  RTC_WakeUpClock_RTCCLK_Div8     = ((uint8_t)0x01), /*!< (RTC clock) div 8*/
  RTC_WakeUpClock_RTCCLK_Div4     = ((uint8_t)0x02), /*!< (RTC clock) div 4*/
  RTC_WakeUpClock_RTCCLK_Div2     = ((uint8_t)0x03), /*!< (RTC clock) div 2*/
  RTC_WakeUpClock_CK_SPRE_16bits  = ((uint8_t)0x04), /*!< CK SPRE with a counter from 0x0000 to 0xFFFF*/
  RTC_WakeUpClock_CK_SPRE_17bits  = ((uint8_t)0x06)  /*!< CK SPRE with a counter from 0x10000 to 0x1FFFF*/
}
RTC_WakeUpClock_TypeDef;
/**
* @brief RTC Output selection
*/
typedef enum
{
  RTC_Output_Disable = ((uint8_t)0x00), /*!< RTC Alternate function Output  is disabled  */
  RTC_Output_Alarm   = ((uint8_t)0x20), /*!< RTC Alternate function Output is the Alarm  event*/
  RTC_Output_WakeUp  = ((uint8_t)0x60)  /*!< RTC Alternate function Output is the WakeUp event */
}
RTC_Output_TypeDef;
/**
* @brief RTC Output Polarity
*/
typedef enum
{
  RTC_OutputPolarity_High  = ((uint8_t)0x00), /*!< RTC Alternate function Output Polarity is High  */
  RTC_OutputPolarity_Low   = ((uint8_t)0x10)  /*!< RTC Alternate function Output Polarity is Low  */
}
RTC_OutputPolarity_TypeDef;
/**
* @brief RTC DayLightSaving operations
*/
typedef enum
{
  RTC_DayLightSaving_SUB1H  = ((uint8_t)0x02), /*!< Substract 1 hour to the current Time (Winter Time Adjustment) */
  RTC_DayLightSaving_ADD1H  = ((uint8_t)0x01)  /*!< Add 1 hour to the current Time (Summer Time Adjustment) */
}
RTC_DayLightSaving_TypeDef;

/**
* @brief RTC Store operation state
*/
typedef enum
{
  RTC_StoreOperation_Set   = ((uint8_t)0x04), /*!< Store Operation Set */
  RTC_StoreOperation_Reset = ((uint8_t)0x00)  /*!< Store Operation Reset */
}
RTC_StoreOperation_TypeDef;
/**
* @brief RTC input parameter format
*/
typedef enum
{
  RTC_Format_BIN  = ((uint8_t)0x00), /*!< Binary Format is used  */
  RTC_Format_BCD  = ((uint8_t)0x01)  /*!< BCD Format is used  */
}
RTC_Format_TypeDef;
/**
* @brief RTC Flags
*/
typedef enum
{
  RTC_FLAG_WUTF   = ((uint16_t)0x0400), /*!< Wake up Timer Flag. If set, the Wake Up downcounter reaches 0 */
  RTC_FLAG_ALRAF  = ((uint16_t)0x0100), /*!< Alarm  Flag. If set, the Time/Date registers matches Alarm registers */
  RTC_FLAG_INITF  = ((uint16_t)0x0040), /*!< Initialisation Flag. If set,Calendar registers has been initialized  */
  RTC_FLAG_RSF    = ((uint16_t)0x0020), /*!< Registers Synchronization Flag. If set,Calendar registers synchronized  */
  RTC_FLAG_INITS  = ((uint16_t)0x0010), /*!< Initialisation Status Flag. If set,Calendar  update is allowed  */
  RTC_FLAG_WUTWF  = ((uint16_t)0x0004), /*!< Wake up Timer write Flag. If set, Wake up Timer update is allowed */
  RTC_FLAG_ALRAWF = ((uint16_t)0x0001)  /*!< Alarm write Flag. If set, Alarm update is allowed   */
}
RTC_Flag_TypeDef;
/**
* @brief RTC Interrupts
*/

typedef enum
{
  RTC_IT_WUT  = ((uint8_t)0x40), /*!< Wake up Timer Interrupt */
  RTC_IT_ALRA = ((uint8_t)0x10)  /*!< Alarm Interrupt */
}
RTC_IT_TypeDef;

/** @addtogroup RTC_Exported_Types
* @{
*/

/**
* @brief RTC Init structure definition
*/

typedef struct
{

  RTC_HourFormat_TypeDef RTC_HourFormat; /*!< RTC Hour Format */

  uint8_t RTC_AsynchPrediv;              /*!< RTC Asynchronious Predivisor.
                                                This parameter can be any value from 0x00 to 0x7F.*/

  uint16_t RTC_SynchPrediv;              /*!< RTC Synchronious Predivisor.
                                                This parameter can be any value from 0x0000 to 0x1FFF.*/
}
RTC_InitTypeDef;


/**
* @brief RTC Time structure definition
*/
typedef struct
{
  uint8_t RTC_Hours;       /*!< RTC Hours.
                                  If Binary format is selected :
                                    - If RTC_HourFormat is RTC_HourFormat_12, this parameter
                                      can be any value from 1 to 12.
                                    - If RTC_HourFormat is RTC_HourFormat_24, this parameter
                                      can be any value from 0 to 23.*
                                  If BCD format is selected :
                                    - If RTC_HourFormat is RTC_HourFormat_12, this parameter
                                      can be any BCD value from 0x01 to 0x12.
                                    - If RTC_HourFormat is RTC_HourFormat_24, this parameter
                                      can be any BCD value  from 0x00 to 0x23.*/

  uint8_t RTC_Minutes;     /*!< RTC Minutes.
                                  If Binary format is selected, this parameter can
                                  be any value from 0 to 59.
                                  If BCD format is selected, this parameter can
                                  be any BCD value from 0x00 to 0x59.*/
  uint8_t RTC_Seconds;     /*!< RTC Seconds.
                                  If Binary format is selected, this parameter can
                                  be any value from 0 to 59.
                                  If BCD format is selected, this parameter can
                                  be any BCD value from 0x00 to 0x59.*/

  RTC_H12_TypeDef RTC_H12; /*!< RTC 12-hour clock period (AM/PM)*/
}
RTC_TimeTypeDef;

/**
* @brief RTC Date structure definition
*/
typedef struct
{
  RTC_Weekday_TypeDef  RTC_WeekDay; /*!< The RTC Calendar Weekday. */

  RTC_Month_TypeDef RTC_Month;      /*!< The RTC Calendar Month. */

  uint8_t RTC_Date;                 /*!< The RTC Calendar Date.
                                           If Binary format is selected, this parameter
                                           can be any value from 1 to 31.
                                           If BCD format is selected, this parameter
                                           can be any BCD value from 0x01 to 0x31.*/

  uint8_t RTC_Year;                 /*!< The RTC Calendar Year.
                                           If Binary format is selected, this parameter
                                           can be any value from 0 to 99.
                                           If BCD format is selected, this parameter
                                           can be any BCD value from 0x00 to 0x99.*/
}
RTC_DateTypeDef;

/**
* @brief RTC Alarm structure definition
*/

typedef struct
{
  RTC_TimeTypeDef RTC_AlarmTime;                           /*!< RTC Alarm Time */

  uint8_t RTC_AlarmMask;                                   /*!< The RTC Alarm Fields Masks. */

  RTC_AlarmDateWeekDaySel_TypeDef RTC_AlarmDateWeekDaySel; /*!< The RTC Alarm Date/WeekDay selection. */

  uint8_t RTC_AlarmDateWeekDay;                            /*!< The RTC Alarm Date/WeekDay value.
                                                                  - If RTC Alarm Date/WeekDay selection is Date
                                                                    and if If Binary format is selected, this
                                                                    parameter can be any value from 1 to 31.
                                                                  - If RTC Alarm Date/WeekDay selection is WeekDay,
                                                                    this parameter can be one of the
                                                                    @ref RTC_Weekday_TypeDef enumeration.*/
}
RTC_AlarmTypeDef;




/** @addtogroup RTC_Exported_Macros
* @{
*/

/**
  * @brief Macro used by the assert_param function in order to check the used Calendar Hour format
  */

#define IS_RTC_HOUR_FORMAT(FORMAT) (((FORMAT) == RTC_HourFormat_12) || \
                                    ((FORMAT) == RTC_HourFormat_24))

/**
  * @brief Macro used by the assert_param function in order to check the used Asynchronous Predivider
  */

#define IS_RTC_ASYNCH_PREDIV(PREDIV) ((PREDIV) <= 0x7F)
/**
  * @brief Macro used by the assert_param function in order to check the used Synchronous Predivider
  */
#define IS_RTC_SYNCH_PREDIV(PREDIV) ((PREDIV) <= 0x1FFF)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar Hours value (format 12h)
  */

#define IS_RTC_HOUR12_MAX(HOUR) ((HOUR) <= (uint8_t)12)
#define IS_RTC_HOUR12_MIN(HOUR) ((HOUR) > (uint8_t)0)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar Hours value (format 24h)
  */
#define IS_RTC_HOUR24(HOUR) ((HOUR) <= 23)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar minutes value
  */
#define IS_RTC_MINUTES(MINUTES) ((MINUTES) <= 59)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar seconds value
  */
#define IS_RTC_SECONDS(SECONDS) ((SECONDS) <= 59)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar H12 mode
  */
#define IS_RTC_H12(PM) (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))

/**
  * @brief Macro used by the assert_param function in order to check the used Calendar Year value
  */
#define IS_RTC_YEAR(YEAR) ((YEAR) <= 99)
/**
  * @brief Macro used by the assert_param function in order to check the used  Calendar month value
  */
#define IS_RTC_MONTH_MAX(MONTH) ((MONTH) <= (uint8_t)12)
#define IS_RTC_MONTH_MIN(MONTH) ((MONTH) >= (uint8_t)1)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar Date value
  */
#define IS_RTC_DATE_MAX(DATE) ((DATE) <= (uint8_t)31)
#define IS_RTC_DATE_MIN(DATE) ((DATE) >= (uint8_t)1)
/**
  * @brief Macro used by the assert_param function in order to check the used Calendar Week day value
  */
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) ==   RTC_Weekday_Monday) || \
                                 ((WEEKDAY) ==   RTC_Weekday_Tuesday) || \
                                 ((WEEKDAY) ==   RTC_Weekday_Wednesday) || \
                                 ((WEEKDAY) ==   RTC_Weekday_Thursday) || \
                                 ((WEEKDAY) ==   RTC_Weekday_Friday) || \
                                 ((WEEKDAY) ==   RTC_Weekday_Saturday) || \
                                 ((WEEKDAY) ==   RTC_Weekday_Sunday))

/**
  * @brief Macro used by the assert_param function in order to check the used Alarm Date/week day  selection
  */

#define IS_RTC_ALARM_DATEWEEKDAY_SEL(SEL) (((SEL) == RTC_AlarmDateWeekDaySel_Date) || ((SEL) == RTC_AlarmDateWeekDaySel_WeekDay))
/**
  * @brief Macro used by the assert_param function in order to check the used  Alarm Mask
  */
#define IS_RTC_ALARM_MASK(MASK) (((MASK) & 0x0F) == (uint8_t)(RESET))


/**
  * @brief Macro used by the assert_param function in order to check the used wake up clock source
  */


#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WakeUpClock_RTCCLK_Div16) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div8)  || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div4)  || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div2)  || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_16bits) || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_17bits))


/**
  * @brief Macro used by the assert_param function in order to check the used Output selection
  */

#define IS_RTC_OUTPUT_SEL(SEL) (((SEL) == RTC_Output_Disable) || \
                                ((SEL) == RTC_Output_Alarm) || \
                                ((SEL) == RTC_Output_WakeUp))
/**
  * @brief Macro used by the assert_param function in order to check the used Output polarity
  */
#define IS_RTC_OUTPUT_POL(POL) (((POL) == RTC_OutputPolarity_High) || \
                                ((POL) == RTC_OutputPolarity_Low))

/**
  * @brief Macro used by the assert_param function in order to check the used Daylight saving mode
  */
#define IS_RTC_DAYLIGHT_SAVING(SAVE) (((SAVE) ==  RTC_DayLightSaving_SUB1H) || \
                                      ((SAVE) == RTC_DayLightSaving_ADD1H))

/**
  * @brief Macro used by the assert_param function in order to check the used Store Operation status
  */
#define IS_RTC_STORE_OPERATION(OP) (((OP) ==  RTC_StoreOperation_Set) || \
                                    ((OP) == RTC_StoreOperation_Reset))


/**
  * @brief Macro used by the assert_param function in order to check the used format (bin/bcd) for data user insert
  */

#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_Format_BIN) || ((FORMAT) == RTC_Format_BCD))
/**
  * @brief Macro used by the assert_param function in order to check the used Flag to get
  */

#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_WUTF) || ((FLAG) == RTC_FLAG_ALRAF) || \
                               ((FLAG) == RTC_FLAG_INITF) || ((FLAG) == RTC_FLAG_RSF) || \
                               ((FLAG) == RTC_FLAG_INITS) || ((FLAG) == RTC_FLAG_WUTWF) || \
                               ((FLAG) == RTC_FLAG_ALRAWF))

/**
  * @brief Macro used by the assert_param function in order to check the used Flag to clear
  */
#define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint16_t)RESET) && ((uint16_t)((uint16_t)(FLAG) & (uint16_t)(~(uint16_t)((RTC_FLAG_RSF|RTC_FLAG_ALRAF|RTC_FLAG_WUTF)))) == (uint16_t)RESET))

/**
  * @brief Macro used by the assert_param function in order to check the used Interrupt to config
  */

#define IS_RTC_CONFIG_IT(IT) ((((IT) != (uint8_t)RESET) && ((uint8_t)((IT) & (uint8_t)(~(uint8_t)(RTC_IT_WUT|RTC_IT_ALRA))))) == (uint8_t)RESET)
/**
  * @brief Macro used by the assert_param function in order to check the used Interrupt to get
  */
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_WUT) ||((IT) == RTC_IT_ALRA))
/**
  * @brief Macro used by the assert_param function in order to check the used Interrupt to clear
  */
#define IS_RTC_CLEAR_IT(IT)  (((IT) != (uint8_t)RESET) && (((IT) & (uint8_t)(~(uint8_t)(RTC_IT_WUT|RTC_IT_ALRA))) == (uint8_t)RESET))



/* Exported functions ------------------------------------------------------- */

/* RTC Initialization functions */
ErrorStatus RTC_DeInit(void);
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct);
void RTC_ITConfig(RTC_IT_TypeDef RTC_IT, FunctionalState NewState);
ErrorStatus RTC_EnterInitMode(void);
void RTC_ExitInitMode(void);
void RTC_WriteProtectionCmd(FunctionalState NewState);
ErrorStatus RTC_WaitForSynchro(void);
ErrorStatus RTC_RatioCmd(FunctionalState NewState);


/* RTC Time and Date Functions */
ErrorStatus RTC_SetTime(RTC_Format_TypeDef RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
ErrorStatus RTC_SetDate(RTC_Format_TypeDef RTC_Format, RTC_DateTypeDef* RTC_DateStruct);
void RTC_GetTime(RTC_Format_TypeDef RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct);
void RTC_GetDate(RTC_Format_TypeDef RTC_Format, RTC_DateTypeDef* RTC_DateStruct);

/* RTC Alarms Functions */
ErrorStatus RTC_SetAlarm(RTC_Format_TypeDef RTC_Format, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_GetAlarm(RTC_Format_TypeDef RTC_Format, RTC_AlarmTypeDef* RTC_AlarmStruct);
void RTC_AlarmCmd(FunctionalState NewState);

/* RTC WakeUp Timer Functions */
ErrorStatus RTC_WakeUpClockConfig(RTC_WakeUpClock_TypeDef RTC_WakeupClock);
ErrorStatus RTC_SetWakeUpCounter(uint16_t RTC_WakeupCounter);
uint16_t RTC_GetWakeUpCounter(void);
void RTC_WakeUpCmd(FunctionalState NewState);

/* RTC Daylight Saving Function */
void RTC_DayLightSavingConfig(RTC_DayLightSaving_TypeDef RTC_DayLightSaving,
                              RTC_StoreOperation_TypeDef RTC_StoreOperation);
RTC_StoreOperation_TypeDef  RTC_GetStoreOperation(void);

/* RTC Output pin Configuration Function */
void RTC_OutputConfig(RTC_Output_TypeDef RTC_Output,
                      RTC_OutputPolarity_TypeDef RTC_OutputPolarity);

/* RTC Calibration Output pin Function */
void RTC_CalibOutputCmd(FunctionalState NewState);

/* RTC Flags ans IT functions */
FlagStatus RTC_GetFlagStatus(RTC_Flag_TypeDef RTC_FLAG);
void RTC_ClearFlag(RTC_Flag_TypeDef RTC_FLAG);
ITStatus RTC_GetITStatus(RTC_IT_TypeDef RTC_IT);
void RTC_ClearITPendingBit(RTC_IT_TypeDef RTC_IT);

#endif /*__STM8L15x_RTC_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
