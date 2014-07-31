/*! @file hardware_defs.h
 * @brief This file contains hardware specific definitions defined by the platform.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#ifndef HARDWARE_DEFS_H
#define HARDWARE_DEFS_H

/*-------------------------------------------------------------*/
/*						      Global definitions				                 */
/*-------------------------------------------------------------*/
#define Si44_SDRST GPIO_Pin_1
#define Si44_nSEL GPIO_Pin_2
#define Si44_SDI GPIO_Pin_3
#define Si44_SDO GPIO_Pin_4
#define Si44_SCLK GPIO_Pin_5
#define Si44_nIRQ GPIO_Pin_6
#define Si44_GPIO1 GPIO_Pin_7
#define SETB GPIO_Pin_5
#if (defined SILABS_PLATFORM_RFSTICK)

/*!* LED state Type definition */
typedef enum
{
  ILLUMINATE,
  EXTINGUISH
} eLEDStates;

#define M_P0_UART_TX 0x10
#define M_P0_UART_RX 0x20

#define M_P0_I2C_SCL 0x40
#define M_P0_I2C_SDA 0x80

#define M_P0_RF_GPIO0 0x01
#define M_P0_RF_GPIO1 0x02
#define M_P0_RF_GPIO2 0x04
#define M_P0_RF_GPIO3 0x08

#define M_P1_SPI1_SCK  0x01
#define M_P1_SPI1_MISO 0x02
#define M_P1_SPI1_MOSI 0x04

#define M_P1_RF_NSEL  0x08
#define M_P1_RF_NIRQ  0x10
#define M_P1_RF_PWRDN 0x20

#define M_P0_PB1  0x01
#define M_P0_PB2  0x02
#define M_P0_PB3  0x04
#define M_P0_PB4  0x08

#define M_P2_LED1 0x01
#define M_P2_LED2 0x02
#define M_P2_LED3 0x04
#define M_P2_LED4 0x08

#define M_P2_SW1_A 0x20
#define M_P2_SW1_B 0x40
#define M_P1_SW1_C 0x80
#define M_P1_SW1_D 0x40

#define M_P2_BZ1  0x10
#define M_P2_C2D  0x80

#define NUMOF_PUSHBUTTONS 0x04

/* Definition of pins that are used by basic HWs, be aware not to have same*/
#define M_LED1 M_P2_LED1
#define M_LED2 M_P2_LED2
#define M_LED3 M_P2_LED3
#define M_LED4 M_P2_LED4

#define M_BZ1 M_P2_BZ1

#define B_P0_UART_TX 4
#define B_P0_UART_RX 5

#define B_P0_RF_GPIO0 0
#define B_P0_RF_GPIO1 1
#define B_P0_RF_GPIO2 2
#define B_P0_RF_GPIO3 3

#define B_P1_SPI1_SCK  0
#define B_P1_SPI1_MISO 1
#define B_P1_SPI1_MOSI 2

#define B_P1_RF_NSEL  3
#define B_P1_RF_NIRQ  4
#define B_P1_RF_PWRDN 5

#define B_P0_PB1  0
#define B_P0_PB2  1
#define B_P0_PB3  2
#define B_P0_PB4  3
#define B_P2_LED1 0
#define B_P2_LED2 1
#define B_P2_LED3 2
#define B_P2_LED4 3

#define B_P2_SW1_A 5
#define B_P2_SW1_B 6
#define B_P1_SW1_C 7
#define B_P1_SW1_D 6

#define B_P2_BZ1  4
#define B_P2_C2D  7

SBIT(RF_GPIO0,   SFR_P0, B_P0_RF_GPIO0);
SBIT(RF_GPIO1,   SFR_P0, B_P0_RF_GPIO1);
SBIT(RF_GPIO2,   SFR_P0, B_P0_RF_GPIO2);
SBIT(RF_GPIO3,   SFR_P0, B_P0_RF_GPIO3);

SBIT(SPI1_SCK,   SFR_P1, B_P1_SPI1_SCK);
SBIT(SPI1_MISO,  SFR_P1, B_P1_SPI1_MISO);
SBIT(SPI1_MOSI,  SFR_P1, B_P1_SPI1_MOSI);

SBIT(RF_NSEL,  SFR_P1, B_P1_RF_NSEL);
SBIT(RF_IRQ,   SFR_P1, B_P1_RF_NIRQ);
SBIT(RF_NIRQ,  SFR_P1, B_P1_RF_NIRQ);
SBIT(RF_PWRDN, SFR_P1, B_P1_RF_PWRDN);

SBIT(PB1,   SFR_P0, B_P0_PB1);
SBIT(PB2,   SFR_P0, B_P0_PB2);
SBIT(PB3,   SFR_P0, B_P0_PB3);
SBIT(PB4,   SFR_P0, B_P0_PB4);
SBIT(LED1,  SFR_P2, B_P2_LED1);
SBIT(LED2,  SFR_P2, B_P2_LED2);
SBIT(LED3,  SFR_P2, B_P2_LED3);
SBIT(LED4,  SFR_P2, B_P2_LED4);

SBIT(SW1_A, SFR_P2, B_P2_SW1_A);
SBIT(SW1_B, SFR_P2, B_P2_SW1_B);
SBIT(SW1_C, SFR_P1, B_P1_SW1_C);
SBIT(SW1_D, SFR_P1, B_P1_SW1_D);

SBIT(BZ1,   SFR_P2, B_P2_BZ1);

#elif (defined SILABS_PLATFORM_LCD_BB)

/*!* LED state Type definition */
typedef enum
{
  ILLUMINATE,
  EXTINGUISH
} eLEDStates;

#define M_P0_UART_TX 0x10
#define M_P0_UART_RX 0x20

#define M_P0_I2C_SCL 0x40
#define M_P0_I2C_SDA 0x80

#define M_P0_RF_GPIO0 0x01
#define M_P0_RF_GPIO1 0x02
#define M_P0_RF_GPIO2 0x04
#define M_P0_RF_GPIO3 0x08

#define M_P1_SPI1_SCK  0x01
#define M_P1_SPI1_MISO 0x02
#define M_P1_SPI1_MOSI 0x04

#define M_P1_RF_NSEL  0x08
#define M_P1_RF_NIRQ  0x10
#define M_P1_RF_PWRDN 0x20

#define M_P1_LCD_NSEL 0x40
#define M_P1_LCD_A0   0x80

#define M_P0_PB1  0x01
#define M_P0_PB2  0x02
#define M_P0_PB3  0x04
#define M_P0_PB4  0x08

#define M_P2_LED1 0x01
#define M_P2_LED2 0x02
#define M_P2_LED3 0x04
#define M_P2_LED4 0x08

#define M_P2_JP4  0x20
#define M_P2_JP5  0x40

#define M_P2_BZ1  0x10
#define M_P2_C2D  0x80

/* Definition of pins that are used by basic HWs, be aware not to have same*/
#define M_LED1 M_P2_LED1
#define M_LED2 M_P2_LED2
#define M_LED3 M_P2_LED3
#define M_LED4 M_P2_LED4

#define M_BZ1 M_P2_BZ1

#define B_P0_UART_TX 4
#define B_P0_UART_RX 5

#define B_P0_I2C_SCL 7
#define B_P0_I2C_SDA 6

#define B_P0_RF_GPIO0 0
#define B_P0_RF_GPIO1 1
#define B_P0_RF_GPIO2 2
#define B_P0_RF_GPIO3 3

#define B_P1_SPI1_SCK  0
#define B_P1_SPI1_MISO 1
#define B_P1_SPI1_MOSI 2

#define B_P1_RF_NSEL  3
#define B_P1_RF_NIRQ  4
#define B_P1_RF_PWRDN 5

#define B_P1_LCD_NSEL 6
#define B_P1_LCD_A0   7

#define B_P0_PB1  0
#define B_P0_PB2  1
#define B_P0_PB3  2
#define B_P0_PB4  3

#define B_P2_LED1 0
#define B_P2_LED2 1
#define B_P2_LED3 2
#define B_P2_LED4 3

#define B_P2_JP4  5
#define B_P2_JP5  6

#define B_P2_BZ1  4
#define B_P2_C2D  7

SBIT(RF_GPIO0,  SFR_P0, B_P0_RF_GPIO0);
SBIT(RF_GPIO1,  SFR_P0, B_P0_RF_GPIO1);
SBIT(RF_GPIO2,  SFR_P0, B_P0_RF_GPIO2);
SBIT(RF_GPIO3,  SFR_P0, B_P0_RF_GPIO3);

SBIT(SPI1_SCK,  SFR_P1, B_P1_SPI1_SCK);
SBIT(SPI1_MISO, SFR_P1, B_P1_SPI1_MISO);
SBIT(SPI1_MOSI, SFR_P1, B_P1_SPI1_MOSI);

SBIT(RF_NSEL,   SFR_P1, B_P1_RF_NSEL);
SBIT(RF_IRQ,    SFR_P1, B_P1_RF_NIRQ);
SBIT(RF_NIRQ,   SFR_P1, B_P1_RF_NIRQ);
SBIT(RF_PWRDN,  SFR_P1, B_P1_RF_PWRDN);

SBIT(LCD_NSEL,  SFR_P1, B_P1_LCD_NSEL);
SBIT(LCD_A0,    SFR_P1, B_P1_LCD_A0);

SBIT(PB1,   SFR_P0, B_P0_PB1);
SBIT(PB2,   SFR_P0, B_P0_PB2);
SBIT(PB3,   SFR_P0, B_P0_PB3);
SBIT(PB4,   SFR_P0, B_P0_PB4);
SBIT(LED1,  SFR_P2, B_P2_LED1);
SBIT(LED2,  SFR_P2, B_P2_LED2);
SBIT(LED3,  SFR_P2, B_P2_LED3);
SBIT(LED4,  SFR_P2, B_P2_LED4);

SBIT(SW1_A, SFR_P2, B_P2_JP4);
SBIT(SW1_B, SFR_P2, B_P2_JP5);

SBIT(BZ1,   SFR_P2, B_P2_BZ1);

#elif (defined SILABS_PLATFORM_WMB)

/*!* LED state Type definition */
typedef enum
{
  ILLUMINATE,
  EXTINGUISH
} eLEDStates;

#define M_P0_LED1       0x01
#define M_P0_LED2       0x40
#define M_P0_LED3       0x04
#define M_P0_LED4       0x08

#define M_LED1          M_P0_LED1
#define M_LED2          M_P0_LED2
#define M_LED3          M_P0_LED3
#define M_LED4          M_P0_LED4

#define B_P1_RF_NSEL    4
#define B_P0_RF_NIRQ    1
#define B_P2_RF_PWRDN   3

//#define B_P0_RF_GPIO0 1
#define B_P1_RF_GPIO1   3
#define B_P2_RF_GPIO2   5
#define B_P2_RF_GPIO3   4

#define B_P1_SPI0_SCK   5
#define B_P1_SPI0_MISO  6
#define B_P1_SPI0_MOSI  7

#define B_P1_SPI1_SCK   0
#define B_P1_SPI1_MISO  1
#define B_P1_SPI1_MOSI  2

#define B_P2_LCD_NSEL   0
#define B_P0_LCD_A0     7

#define B_P2_I2C_SDA    1
#define B_P2_I2C_SCL    2

#define B_P0_PB1        0
#define B_P0_PB2        6
#define B_P0_PB3        2
#define B_P0_PB4        3

#define B_P0_LED1       0
#define B_P0_LED2       6
#define B_P0_LED3       2
#define B_P0_LED4       3

#define B_P2_BZ1        6

//SBIT(RF_GPIO0,  SFR_P0, B_P0_RF_GPIO0);
SBIT(RF_GPIO1,  SFR_P1, B_P1_RF_GPIO1);
SBIT(RF_GPIO2,  SFR_P2, B_P2_RF_GPIO2);
SBIT(RF_GPIO3,  SFR_P2, B_P2_RF_GPIO3);

/* SMBus */
SBIT(MCU_SDA,   SFR_P2, B_P2_I2C_SDA);
SBIT(MCU_SCL,   SFR_P2, B_P2_I2C_SCL);

/* LEDs */
SBIT(LED1,      SFR_P0, B_P0_LED1);
SBIT(LED2,      SFR_P0, B_P0_LED2);
SBIT(LED3,      SFR_P0, B_P0_LED3);
SBIT(LED4,      SFR_P0, B_P0_LED4);

/* MCU SPI0 */
SBIT(SPI0_SCK,  SFR_P1, B_P1_SPI1_SCK);
SBIT(SPI0_MISO, SFR_P1, B_P1_SPI1_MISO);
SBIT(SPI0_MOSI, SFR_P1, B_P1_SPI1_MOSI);

/* MCU SPI1 */
SBIT(SPI1_SCK,  SFR_P1, B_P1_SPI1_SCK);
SBIT(SPI1_MISO, SFR_P1, B_P1_SPI1_MISO);
SBIT(SPI1_MOSI, SFR_P1, B_P1_SPI1_MOSI);

/* RF related */
SBIT(RF_NSEL,   SFR_P1, B_P1_RF_NSEL);
SBIT(RF_IRQ,    SFR_P0, B_P0_RF_NIRQ);
SBIT(RF_NIRQ,   SFR_P0, B_P0_RF_NIRQ);
SBIT(RF_PWRDN,  SFR_P2, B_P2_RF_PWRDN);

/* LCD related */
SBIT(LCD_NSEL,  SFR_P2, B_P2_LCD_NSEL);
SBIT(LCD_A0,    SFR_P0, B_P0_LCD_A0);

SBIT(PB1,       SFR_P0, B_P0_PB1);
SBIT(PB2,       SFR_P0, B_P0_PB2);
SBIT(PB3,       SFR_P0, B_P0_PB3);
SBIT(PB4,       SFR_P0, B_P0_PB4);

/* Buzzer */
SBIT(BZ1,       SFR_P2, B_P2_BZ1);

#else
//#error Other platforms are not supported yet!
#endif

#endif //HARDWARE_DEFS_H
