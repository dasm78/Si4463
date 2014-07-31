/*!
 * File:
 *  radio_hal.c
 *
 * Description:
 *  This file contains RADIO HAL.
 *
 * Silicon Laboratories Confidential
 * Copyright 2011 Silicon Laboratories, Inc.
 */

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */

#include "bsp.h"
#include "spi.h"
#include "stm8l15x_gpio.h"

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */

                /* ======================================= *
                 *      L O C A L   F U N C T I O N S      *
                 * ======================================= */

                /* ======================================= *
                 *     P U B L I C   F U N C T I O N S     *
                 * ======================================= */

void radio_hal_AssertShutdown(void)
{
  GPIO_SetBits(GPIOB, Si44_SDRST);
}

void radio_hal_DeassertShutdown(void)
{
  GPIO_ResetBits(GPIOB, Si44_SDRST);  
}

void radio_hal_ClearNsel(void)
{
  GPIO_ResetBits(GPIOB, Si44_nSEL); // select low

}

void radio_hal_SetNsel(void)
{
  GPIO_SetBits(GPIOB, Si44_nSEL); // select high    
}

BIT radio_hal_NirqLevel(void)
{
  return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);

}

void radio_hal_SpiWriteByte(U8 byteToWrite)
{
  SpiReadWrite(byteToWrite);

}

U8 radio_hal_SpiReadByte(void)
{
  return SpiReadWrite(0xFF);
}

void radio_hal_SpiWriteData(U8 byteCount, U8* pData)
{
  SpiWriteData(byteCount, pData);
}

void radio_hal_SpiReadData(U8 byteCount, U8* pData)
{
  SpiReadData(byteCount, pData);
}
#if 0
#ifdef RADIO_DRIVER_EXTENDED_SUPPORT
BIT radio_hal_Gpio0Level(void)
{
#ifdef SILABS_PLATFORM_DKMB
  return 0;
#endif
#ifdef SILABS_PLATFORM_UDP
  return EZRP_RX_DOUT;
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB)
  return RF_GPIO0;
#endif
#if (defined SILABS_PLATFORM_WMB)
  return 0;
#endif
}

BIT radio_hal_Gpio1Level(void)
{
#ifdef SILABS_PLATFORM_DKMB
  return FSK_CLK_OUT;
#endif
#ifdef SILABS_PLATFORM_UDP
  return 0; //No Pop
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return RF_GPIO1;
#endif
}

BIT radio_hal_Gpio2Level(void)
{
#ifdef SILABS_PLATFORM_DKMB
  return DATA_NFFS;
#endif
#ifdef SILABS_PLATFORM_UDP
  return 0; //No Pop
#endif
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return RF_GPIO2;
#endif
}

BIT radio_hal_Gpio3Level(void)
{
#if (defined SILABS_PLATFORM_RFSTICK) || (defined SILABS_PLATFORM_LCD_BB) || (defined SILABS_PLATFORM_WMB)
  return RF_GPIO3;
#else
  return 0;
#endif
}

#endif
#endif