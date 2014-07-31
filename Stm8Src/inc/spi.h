#ifndef SPI_H
#define SPI_H
#include "bsp.h"
U8 SpiReadWrite( U8 byteToWrite);
void SpiWriteData(U8 byteCount, U8 *pData);
void SpiReadData(U8 byteCount, U8 *pData);
#endif