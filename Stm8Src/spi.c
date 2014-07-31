#include "stm8l15x.h"
#include "bsp.h"
#include "spi.h"
#include "hardware_defs.h"
#include "hardware_defs.h"
volatile int _spidel =0;
void spidel()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		_spidel++;
	}
}

U8 SpiReadWrite( U8 byteToWrite)
{  
	U8 read = 0; U8 i;	
	
	for (i = 0; i < 8; i++)
	{
		spidel();
		read <<= 1;
		read |= GPIO_ReadInputDataBit(GPIOB, Si44_SDO) ? 1 : 0;		
		// MSB first
		(byteToWrite & (1 << 7)) ?
			GPIO_SetBits(GPIOB, Si44_SDI): GPIO_ResetBits(GPIOB, Si44_SDI);
		byteToWrite <<= 1; 
		spidel();
		GPIO_SetBits(GPIOB, Si44_SCLK); // pulse clk
		spidel();
		GPIO_ResetBits(GPIOB, Si44_SCLK); // pulse clk
	}
	return read;
  
}
void SpiWriteData(U8 byteCount, U8 *pData)
{
  U8 i;
  for (i = 0; i < byteCount; i++)
    SpiReadWrite(*pData++);
}
void SpiReadData(U8 byteCount, U8 *pData)
{
  U8 i;
  for (i = 0; i < byteCount; i++)
    *pData++ = SpiReadWrite(0xff);
  
}
