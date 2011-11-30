/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief UC3-C2-Xplained board header file.
 *
 * This file contains definitions and services related to the features of the
 * UC3-C2-Xplained board.
 *
 * To use this board, define BOARD=UC3_C2_XPLAINED.
  *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR
 * - Supported devices:  UC3C2512C.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

/* Copyright (c) 2011 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef UC3_C2_XPLAINED_H_
#define UC3_C2_XPLAINED_H_

#include "compiler.h"

//! \name Atmel Xplained Development Board Configuration
// Automatically defined when compiling for AVR UC3, not when assembling.
#ifdef __AVR32_ABI_COMPILER__
#  include "led.h"
#endif  // __AVR32_ABI_COMPILER__


#ifdef __cplusplus
extern "C" {
#endif

//! \name Oscillator Definitions
//! @{

/*! \brief System oscillator frequencies (Hz.) and startup times (periods).
 *
 * RCOsc has no custom calibration by default. Set the following definition
 * to the appropriate value if a custom RCOsc calibration has been applied
 * to your part.
 */

//!< RCOsc frequency: Hz.

#define FRCOSC                      (AVR32_PM_RCOSC_FREQUENCY)

//!< Osc32 frequency (Hz.) and startup time (RCOsc periods).

#define FOSC32                      (AVR32_SCIF_OSC32_FREQUENCY)
#define OSC32_STARTUP               (AVR32_SCIF_OSCCTRL32_STARTUP_8192_RCOSC)

#define BOARD_OSC32_IS_XTAL         true
#define BOARD_OSC32_HZ              FOSC32
#define BOARD_OSC32_STARTUP_US      (71000)


//!< Osc frequency (Hz.) and startup time (RCOsc periods).

#define FOSC0                       (16000000)
#define OSC0_STARTUP                (AVR32_SCIF_OSCCTRL0_STARTUP_128_RCOSC)

#define BOARD_OSC0_IS_XTAL          true
#define BOARD_OSC0_HZ               FOSC0
#define BOARD_OSC0_STARTUP_US       (17000)

//! @}


/*! \name USB Definitions
 */
//! @{
//! Multiplexed pin used for USB_ID: AVR32_USBB_USB_ID_x_x.
//! To be selected according to the AVR32_USBB_USB_ID_x_x_PIN and
//! AVR32_USBB_USB_ID_x_x_FUNCTION definitions from <avr32/uc3cxxxx.h>.
#  define USB_ID                             AVR32_USBC_ID_1

//! Multiplexed pin used for USB_VBOF: AVR32_USBB_USB_VBOF_x_x.
//! To be selected according to the AVR32_USBB_USB_VBOF_x_x_PIN and
//! AVR32_USBB_USB_VBOF_x_x_FUNCTION definitions from <avr32/uc3cxxxx.h>.
#  define USB_VBOF                           AVR32_USBC_VBOF_1

//! Active level of the USB_VBOF output pin.
#  define USB_VBOF_ACTIVE_LEVEL       LOW

//! @}

//! Number of LEDs.
#define LED_COUNT   1

/*! \name GPIO Connections of LEDs
 */
//! @{
#  define LED0_GPIO   AVR32_PIN_PA08
//! @}

/*! \name PWM Channels of LEDs
 */
//! @{
#define LED0_PWM      (-1)
//! @}

/*! \name PWM Functions of LEDs
 */
//! @{
#define LED0_PWM_FUNCTION   (-1)
//! @}

/*! \name Color Identifiers of LEDs to Use with LED Functions
 */
//! @{
#define LED_MONO0_GREEN   LED0
//! @}

/*! \name GPIO Connections of Push Buttons
 * - PUSH_BUTTON_0, touch sensor TK0
 * - PUSH_BUTTON_1, touch sensor TK1
 * - PUSH_BUTTON_2, mechanical button
 */
//! @{
#define GPIO_PUSH_BUTTON_0            AVR32_PIN_PC15
#define GPIO_PUSH_BUTTON_0_PRESSED    0
#define GPIO_PUSH_BUTTON_1            AVR32_PIN_PA23
#define GPIO_PUSH_BUTTON_1_PRESSED    0
#define GPIO_PUSH_BUTTON_2            AVR32_PIN_PD21
#define GPIO_PUSH_BUTTON_2_PRESSED    0
//! @}

/*! \name SPI Connections of the AT45DBX DataFlash Memory
 */
//! @{
#define AT45DBX_SPI                 (&AVR32_SPI0)
#define AT45DBX_SPI_NPCS            1
#define AT45DBX_SPI_SCK_PIN         AVR32_SPI0_SCK_PIN
#define AT45DBX_SPI_SCK_FUNCTION    AVR32_SPI0_SCK_FUNCTION
#define AT45DBX_SPI_MISO_PIN        AVR32_SPI0_MISO_PIN
#define AT45DBX_SPI_MISO_FUNCTION   AVR32_SPI0_MISO_FUNCTION
#define AT45DBX_SPI_MOSI_PIN        AVR32_SPI0_MOSI_PIN
#define AT45DBX_SPI_MOSI_FUNCTION   AVR32_SPI0_MOSI_FUNCTION
#define AT45DBX_SPI_NPCS0_PIN       AVR32_SPI0_NPCS_1_4_PIN
#define AT45DBX_SPI_NPCS0_FUNCTION  AVR32_SPI0_NPCS_1_4_FUNCTION
//! @}

/*! \name GPIO and SPI Connections of the SD/MMC Connector
 */
//! @{
#define SD_MMC_CARD_DETECT_PIN      AVR32_PIN_PA20
#define SD_MMC_WRITE_PROTECT_PIN    AVR32_PIN_PA210
#define SD_MMC_SPI                  (&AVR32_SPI0)
#define SD_MMC_SPI_NPCS             0
#define SD_MMC_SPI_SCK_PIN          AVR32_SPI0_SCK_PIN
#define SD_MMC_SPI_SCK_FUNCTION     AVR32_SPI0_SCK_FUNCTION
#define SD_MMC_SPI_MISO_PIN         AVR32_SPI0_MISO_PIN
#define SD_MMC_SPI_MISO_FUNCTION    AVR32_SPI0_MISO_FUNCTION
#define SD_MMC_SPI_MOSI_PIN         AVR32_SPI0_MOSI_PIN
#define SD_MMC_SPI_MOSI_FUNCTION    AVR32_SPI0_MOSI_FUNCTION
#define SD_MMC_SPI_NPCS_PIN         AVR32_SPI0_NPCS_0_PIN
#define SD_MMC_SPI_NPCS_FUNCTION    AVR32_SPI0_NPCS_0_FUNCTION
//! @}


/*! \name USART connection to the UC3B board controller
 */
//! @{
#define USART                       (&AVR32_USART3)
#define USART_RXD_PIN               AVR32_USART3_RXD_2_PIN
#define USART_RXD_FUNCTION          AVR32_USART3_RXD_2_FUNCTION
#define USART_TXD_PIN               AVR32_USART3_TXD_2_PIN
#define USART_TXD_FUNCTION          AVR32_USART3_TXD_2_FUNCTION
#define USART_IRQ                   AVR32_USART3_IRQ
#define USART_IRQ_GROUP             AVR32_USART3_IRQ_GROUP
#define USART_SYSCLK                SYSCLK_USART3
//! @}

/*! \name MACB connections to the RTL8201 external phy controller
 */
//! @{
#define EXTPHY_MACB                 (&AVR32_MACB)
#define EXTPHY_MACB_PHYRSTB_PIN     AVR32_PIN_PA09
#define EXTPHY_MACB_MDC_PIN         AVR32_MACB_MDC_1_PIN
#define EXTPHY_MACB_MDC_FUNCTION    AVR32_MACB_MDC_1_FUNCTION
#define EXTPHY_MACB_MDIO_PIN        AVR32_MACB_MDIO_1_PIN
#define EXTPHY_MACB_MDIO_FUNCTION   AVR32_MACB_MDIO_1_FUNCTION
#define EXTPHY_MACB_RXD_0_PIN       AVR32_MACB_RXD_0_1_PIN
#define EXTPHY_MACB_RXD_0_FUNCTION  AVR32_MACB_RXD_0_1_FUNCTION
#define EXTPHY_MACB_RXD_1_PIN       AVR32_MACB_RXD_1_1_PIN
#define EXTPHY_MACB_RXD_1_FUNCTION  AVR32_MACB_RXD_1_1_FUNCTION
#define EXTPHY_MACB_TXD_0_PIN       AVR32_MACB_TXD_0_1_PIN
#define EXTPHY_MACB_TXD_0_FUNCTION  AVR32_MACB_TXD_0_1_FUNCTION
#define EXTPHY_MACB_TXD_1_PIN       AVR32_MACB_TXD_1_1_PIN
#define EXTPHY_MACB_TXD_1_FUNCTION  AVR32_MACB_TXD_1_1_FUNCTION
#define EXTPHY_MACB_TX_EN_PIN       AVR32_MACB_TX_EN_1_PIN
#define EXTPHY_MACB_TX_EN_FUNCTION  AVR32_MACB_TX_EN_1_FUNCTION
#define EXTPHY_MACB_RX_ER_PIN       AVR32_MACB_RX_ER_1_PIN
#define EXTPHY_MACB_RX_ER_FUNCTION  AVR32_MACB_RX_ER_1_FUNCTION
#define EXTPHY_MACB_RX_DV_PIN       AVR32_MACB_RX_DV_1_PIN
#define EXTPHY_MACB_RX_DV_FUNCTION  AVR32_MACB_RX_DV_1_FUNCTION
#define EXTPHY_MACB_TX_CLK_PIN      AVR32_MACB_TX_CLK_PIN
#define EXTPHY_MACB_TX_CLK_FUNCTION AVR32_MACB_TX_CLK_FUNCTION

//! Phy Address (set through strap options)
#define EXTPHY_PHY_ADDR             0x01

//! Configure the ethernet phy component to use the RTL8201 phy
#define PHY_RTL8201

//! @}

#endif  // UC3_C2_XPLAINED_H_
