/**
  ******************************************************************************
  * @file    demo_audio.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Header for demo_audio.c
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

/* Define to prevent recursive inclusion ---------------------------------------*/
#ifndef __DEMO_VOICE_H
#define __DEMO_VOICE_H

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stm8_eval_spi_flash.h"
/* Private macro -------------------------------------------------------------*/
#define PAGE_SIZE                 256
#define SECTOR_SIZE               0x40000  
#define SECTORS_NUMBER            3 
#define RECORD_INFO_ADDR          0x700000
#define RECORD_INFO_CODE_OK       0xA5
#define RECORD_READ_WRITED_ADDR   0x700100
#define MAX_RECORD_DATA_LENGTH    0x0A17FC  /* Max SPI Flash size dedicated for voice recording */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void VOICERECORDER_Exec(void);
void VOICEPLAYER_Exec(void);
void ALARMPLAYER_Exec(void);

void VoiceRec_Init(void);
void VoiceRec_Start(void);
void VoiceRec_Recording(void);
void VoiceRec_Stop(void);
void VoiceRec_SPIFlashErase(void);

void VoicePlay_Init(void);
void VoicePlay_Start(void);
void VoicePlay_Playing(void);
void VoicePlay_Stop(void);

void VoiceAlarm_Init(void);
void VoiceAlarm_Start(void);
void VoiceAlarm_Playing(void);
void VoiceAlarm_Stop(void);
/* Private functions ---------------------------------------------------------*/
#endif /*__DEMO_VOICE_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/	
