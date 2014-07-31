/*! @file radio.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#include "bsp.h"
//#include "radio_config_Si4463.h"
/*****************************************************************************
 *  Local Macros & Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variables
 *****************************************************************************/
/*
#define RADIO_CONFIGURATION_DATA { \
                            Radio_Configuration_Data_Array,                            \
                            RADIO_CONFIGURATION_DATA_CHANNEL_NUMBER,                   \
                            RADIO_CONFIGURATION_DATA_RADIO_PACKET_LENGTH,              \
*/
typedef struct
{
    const U8    *Radio_ConfigurationArray;

    U8   Radio_ChannelNumber;
    U8   Radio_PacketLength;
    U8   Radio_State_After_Power_Up;

    U16  Radio_Delay_Cnt_After_Reset;
} tRadioConfiguration1;


const U8 Radio_Configuration_Data_Array[] =  RADIO_CONFIGURATION_DATA_ARRAY;

const tRadioConfiguration RadioConfiguration = RADIO_CONFIGURATION_DATA;

const tRadioConfiguration *pRadioConfiguration = &RadioConfiguration;

/*****************************************************************************
 *  Local Function Declarations
 *****************************************************************************/
void vRadio_PowerUp(void);
/*!
 *  Power up the Radio.
 *
 *  @note
 *
 */
void vRadio_PowerUp(void)
{
  
  SEGMENT_VARIABLE(wDelay,  U16, SEG_XDATA) = 0u;
  SEGMENT_VARIABLE(lBootOpt, U8, SEG_XDATA) = 0u;

  /* Hardware reset the chip */
  si446x_reset();

  /* Wait until reset timeout or Reset IT signal */
  for (; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);
}

/*!
 *  Radio Initialization.
 *
 *  @author Sz. Papp
 *
 *  @note
 *
 */
void vRadio_Init(void)
{
  U16 wDelay;

  /* Power Up the radio chip */
  vRadio_PowerUp();

  /* Load radio configuration */
  while (SI446X_SUCCESS != si446x_configuration_init(pRadioConfiguration->Radio_ConfigurationArray))
  {
    /* Error hook */    
    for (wDelay = 0x7FFF; wDelay--; ) ;

    /* Power Up the radio chip */
    vRadio_PowerUp();
  }

  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);
}

/*!
 *  Set Radio to RX mode, fixed packet length.
 *
 *  @param channel Freq. Channel
 *
 *  @note
 *
 */
void vRadio_StartRX(U8 channel)
{
  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);

  /* Start Receiving packet, channel 0, START immediately, Packet n bytes long */
  si446x_start_rx(channel, 0u, RadioConfiguration.Radio_PacketLength,
                  SI446X_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_RX,
                  //SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_RX,
				  SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_READY, 
                  SI446X_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}

void vRadio_StartRXVarLen(U8 channel)
{
	// Read ITs, clear pending ones
	si446x_get_int_status(0u, 0u, 0u);

	/* Start Receiving packet, channel 0, START immediately, Packet n bytes long */
	si446x_start_rx(channel, 0u, 0,
		SI446X_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_RX,
		//SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_RX,
		SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_READY, 
		SI446X_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}


/*!
 *  Set Radio to TX mode, fixed packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent
 *
 *  @note
 *
 */

void vRadio_StartTx(U8 channel, U8 *pioFixRadioPacket)
{
  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);
  /* Fill the TX fifo with datas */
  si446x_write_tx_fifo(RadioConfiguration.Radio_PacketLength, pioFixRadioPacket);

  /* Start sending packet on channel, START immediately, Packet according to PH */
  /* Start sending packet, channel 0, START immediately, Packet n bytes long, go READY when done */
  si446x_start_tx(channel, 0x30,  RadioConfiguration.Radio_PacketLength);
}

void vRadio_StartTxVarLen(U8 channel, U8 *pData, U8 len)
{
	// Read ITs, clear pending ones
	si446x_get_int_status(0u, 0u, 0u);
	/* Fill the TX fifo with datas */
	si446x_write_tx_fifo(len, pData);

	/* Start sending packet on channel, START immediately, Packet according to PH */
	/* Start sending packet, channel 0, START immediately, Packet n bytes long, go READY when done */
	si446x_start_tx(channel, 0x30,  0);
}
