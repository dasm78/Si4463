/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    07/21/2010
  * @brief   Main program body
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

/* Includes ------------------------------------------------------------------*/

#include "stm8l15x_tim4.h"

#include "hardware_defs.h"
#include <stdio.h>
#include <stdlib.h>
#include "bsp.h"


volatile char txInt = 0;
int putchar (int chr)
{
	txInt = 0;
	USART_SendData8(USART1, chr);
	while (!txInt);
	return chr;
}


uint8_t writeReadSpiByte (uint8_t toWrite)
{
	uint8_t read = 0; uint8_t i;	
	for (i = 0; i < 8; i++)
	{
		read <<= 1;
		read |= GPIO_ReadInputDataBit(GPIOB, Si44_SDO) ? 1 : 0;		
		// MSB first
		(toWrite & (1 << 7)) ?
			GPIO_SetBits(GPIOB, Si44_SDI): GPIO_ResetBits(GPIOB, Si44_SDI);
		toWrite <<= 1; 
		GPIO_SetBits(GPIOB, Si44_SCLK); // pulse clk
		GPIO_ResetBits(GPIOB, Si44_SCLK); // pulse clk
	}
	return read;
}
volatile int _QQ;
void delay ()
{
	long int i;
	for (i = 0; i < 240000; i++)
		_QQ++;
}

void sdelay ()
{
	long int i;
	for (i = 0; i < 140; i++)
		_QQ++;
}




volatile uint8_t rd = 0;
uint8_t propBuf[48];

void waitSiReady ()
{
	uint8_t rd;
	do 
	{
		GPIO_ResetBits(GPIOB, Si44_nSEL); // select low
		writeReadSpiByte(0x44); // read com id
		rd = writeReadSpiByte(0x00); // dummy			
		GPIO_SetBits(GPIOB, Si44_nSEL); // select high
	} while (rd != 0xff);
}


const uint8_t cfgSiArray[] = RADIO_CONFIGURATION_DATA_ARRAY;

void configSi (const uint8_t  *pBuf)
{
	const uint8_t *ptr = pBuf; // this buffer has format "1 byte block len N , N bytes, 1 byte block len N2, N2 bytes, etc until zero len
	uint8_t len;
	while ((len = *ptr) > 0 )
	{
		
		waitSiReady ();
		GPIO_ResetBits(GPIOB, Si44_nSEL); // select low		
		while (len > 0)		
		{
			ptr++;
			writeReadSpiByte(*ptr); 
			len --;
		}
		ptr++;// to next header (byte cnt)
		GPIO_SetBits(GPIOB, Si44_nSEL); // select high
	}
}


uint8_t waitcnt = 0;

/**
  * @brief  USART1 RX Interrupt routine.
  * @param  None
  * @retval None
  */
#define RX_SZ 22
volatile uint8_t uart_rx_tmp_buffer[RX_SZ];
volatile uint8_t uart_rx_buffer[RX_SZ];

volatile uint8_t iuartrx = 0;
volatile uint8_t packReady = 0;
volatile U8 status;
INTERRUPT_HANDLER(USART1_RX_IRQHandler,28)
{
	
	status = USART1->SR;
	if (status & (1<<3)) // overrun
	{
		status = USART1->DR; // empty read
		iuartrx = 0; // start again
		return;
	}
		
	uart_rx_tmp_buffer[iuartrx] = USART1->DR;
	iuartrx++;
	if (iuartrx == RX_SZ)
	{
		iuartrx = 0;
		memcpy (uart_rx_buffer, uart_rx_tmp_buffer, sizeof (uart_rx_buffer));
		packReady = 1;
	}
//	USART1->DR = waitcnt;
}
INTERRUPT_HANDLER(USART1_TX_IRQHandler,27)
{
	USART1->SR = (USART1->SR) & ~USART_SR_TC; // writing 0 to TXC for clear
	txInt = 1;
	waitcnt = 0;
}
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_BRK_IRQHandler,25)
{
	/* In order to detect unexpected events during development,
	it is recommended to set a breakpoint on the following instruction.
	*/
	waitcnt++;
	TIM4->SR1 = 0; // clear int
}

U8 toTx[64] = {0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};
uint8_t a1 @ 0x1000; // eeprom data
volatile uint8_t rb;
volatile unsigned int sz;
void main(void)
{
	uint8_t i;
	int sd;

	
	CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
	CLK_SYSCLKSourceSwitchCmd(ENABLE);
	while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI)
	{};
	CLK_PeripheralClockConfig(CLK_Peripheral_SPI1, ENABLE);
	CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);
	CLK_PeripheralClockConfig(CLK_PCKENR1_TIM3, ENABLE);
	CLK_PeripheralClockConfig(CLK_PCKENR1_TIM4, ENABLE);


// USART1
	USART_Init(USART1, 115200,USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, USART_Mode_Rx | USART_Mode_Tx);	
	USART_Cmd(USART1, ENABLE);



	SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA, ENABLE);
	GPIO_Init(GPIOA,GPIO_Pin_2,GPIO_Mode_Out_PP_Low_Slow); // tx ppin
	GPIO_Init(GPIOA,GPIO_Pin_3,GPIO_Mode_In_PU_No_IT); // rx ppin

	USART_ITConfig(USART1,  USART_IT_RXNE, ENABLE);

	USART_ITConfig(USART1,  USART_IT_TXE, DISABLE);
	USART_ITConfig(USART1,  USART_IT_TC, ENABLE);

	
	
	TIM4_TimeBaseInit(TIM4_Prescaler_256, 1000);	
	TIM4_ITConfig(TIM2_IT_Update, ENABLE);
	TIM4_Cmd(ENABLE);



	//Si4463 iface
	GPIO_Init(GPIOB,Si44_nSEL, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(GPIOB,Si44_SDI, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(GPIOB,Si44_SDO, GPIO_Mode_In_PU_No_IT);
	GPIO_Init(GPIOB,Si44_SCLK, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(GPIOB,Si44_nIRQ, GPIO_Mode_In_PU_No_IT);		
	GPIO_Init(GPIOB,Si44_GPIO1, GPIO_Mode_In_PU_No_IT);
	GPIO_Init(GPIOB,Si44_SDRST, GPIO_Mode_Out_PP_Low_Slow);
	GPIO_Init(GPIOD,(1 << 3), GPIO_Mode_Out_PP_Low_Fast); //led
        GPIO_Init(GPIOA, SETB, GPIO_Mode_Out_PP_Low_Fast); //seta

	GPIO_SetBits(GPIOB, Si44_nSEL); // select high
	GPIO_ResetBits(GPIOB, Si44_SCLK); // clk low

	GPIO_SetBits(GPIOB, Si44_SDRST); // RST  high
	delay();
	GPIO_ResetBits(GPIOB, Si44_SDRST); // RST  low
	delay();

#define LED_OFF	GPIO_SetBits(GPIOD,(1 << 3)); //LED
#define LED_ON	GPIO_ResetBits(GPIOD,(1 << 3)); //LED
#define SETB_ON	GPIO_SetBits(GPIOA,SETB); //
#define SETB_OFF	GPIO_ResetBits(GPIOA,SETB); //

	enableInterrupts();
   /* int adr;
	int ofs = 0x1000;
	FLASH_Unlock(FLASH_MemType_Data);
	a1 = 0x22;

	static  const U8 Radio_Configuration_Data_Array[20000];//  =  RADIO_CONFIGURATION_DATA_ARRAY;
	sz = sizeof (Radio_Configuration_Data_Array);
	sz = (int) &Radio_Configuration_Data_Array[0];
	 
	for (adr = 0; adr < 64; adr++)
	{
		//FLASH_ProgramWord (ofs + adr, adr);
		FLASH_ProgramByte (ofs + adr, 0xa2);
		rb = FLASH_ReadByte (ofs + adr);
	}
	
	rb = 0;
*/
        



        
	unsigned long int tmp, tmp2;
	
	unsigned int toG;
	unsigned char errcnt;

        // Initialize the Radio		
        vRadio_Init();	
	//	si446x_apply_patch();        
		printf ("Hi!\r\n");
      U8 prop[] = {0};
      si446x_set_property( 0x12, 1, 0x0a, prop); 
      si446x_get_property(0x12, 8, 0);
        vRadio_StartRXVarLen(0);


        char q;
        for (;;)
        {
#if    0      
         // delay();
				while (packReady == 0)
					;
				packReady = 0;
                                si446x_fifo_info (3); // rst rx tx fifo 
                //vRadio_StartTx(0, (U8*)uart_rx_buffer);       
				uart_rx_buffer[0]=15;
				vRadio_StartTxVarLen(0, (U8*) uart_rx_buffer, 35);
                while ((GPIO_ReadInputDataBit(GPIOB, Si44_nIRQ) & Si44_nIRQ))
                  ;
                delay(60);
              //  si446x_get_int_status(0xff, 0xff, 0xff); 
               // if (Si446xCmd.GET_INT_STATUS.PH_STATUS & (1 << 5))
                {
                  si446x_get_int_status(0x0, 0x0, 0x00); 
                  LED_ON;
				  delay(100);
                  LED_OFF;
  				  delay(100);
                }
                
                
        } 
#endif    

#if 1
//RF_MODEM_OOK_CNT1_11 - last byte == RSSI latch time
#define PACKET_RX_PEND (1 << 4)
#define CRC_ERROR_PEND (1 << 3)
#define RX_FIFO_ALMOST_FULL_PEND (1 <<0)

	int inrxfifo;
        
      
	if (GPIO_ReadInputDataBit(GPIOB, Si44_nIRQ) == RESET)
	{
                si446x_fifo_info (0); // rst rx tx fifo 
                printf ("in rx fifo 0x%x\r\n", Si446xCmd.FIFO_INFO.RX_FIFO_COUNT);
		si446x_get_int_status(0x0, 0xff, 0xff); 
		printf("INT_PEND=0x%x   PH_PEND=0x%x  MODEM=0x%x\r\n", Si446xCmd.GET_INT_STATUS.INT_PEND, Si446xCmd.GET_INT_STATUS.PH_PEND, Si446xCmd.GET_INT_STATUS.MODEM_PEND);		
		si446x_get_packet_info(0, 0,0 );			
		printf("lenH = %d, lenL= %d\r\n", Si446xCmd.PACKET_INFO.LENGTH_15_8, Si446xCmd.PACKET_INFO.LENGTH_7_0);		                
/*
			if (Si446xCmd.GET_INT_STATUS.PH_PEND & CRC_ERROR_PEND)
			{
				printf("crc err\n");
				si446x_fifo_info(3); // rst fifo
				vRadio_StartRXVarLen(0);
				continue;
				goto begin;

			}
*/
//			else if (Si446xCmd.GET_INT_STATUS.PH_PEND & PACKET_RX_PEND)
		//			if (Si446xCmd.GET_INT_STATUS.PH_PEND & 1)
			{				


				LED_ON;
				inrxfifo = 7;// Si446xCmd.PACKET_INFO.LENGTH_7_0;	
                                if (inrxfifo != 0)
                                { 
                                  si446x_read_rx_fifo(inrxfifo, toTx);
				for (i = 0; i < inrxfifo; i++)
					printf ("%x,", toTx[i]);
				printf ("\r\n");
                                si446x_fifo_info (3); // rst rx tx fifo 
				LED_OFF;
begin:
				si446x_get_modem_status(0xff);				
				printf ("latch RSSI = %d  ", Si446xCmd.GET_MODEM_STATUS.LATCH_RSSI);
				vRadio_StartRXVarLen(0);
				si446x_get_modem_status(0xff);
				printf ("RSSI = %d  ", Si446xCmd.GET_MODEM_STATUS.CURR_RSSI);				
                                }

			}
	
		}
	}
		  
#endif            
}			



