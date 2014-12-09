// Copyright (C) 2014  Unison Networks Ltd
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 *
 * @file		atmega64c1.hpp
 * Provides target configuration for the ATmega64M1/C1 automotive family of chips
 *
 *
 * @author 		Jared Sanson
 *
 * @date		28/11/2014
 *
 * @section Licence
 *
 * Copyright (C) 2014  Unison Networks Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @brief
 * This contains device specific definitions for AVR architecture targets. Information such as timer size, interrupt specifications and so on are defined here.
 */

// Only include this header file once.
#ifndef __TARGET_ATMEGA64C1_H__
#define __TARGET_ATMEGA64C1_H__

/* Watchdog timer. */

enum Watchdog_timeout
{
	WDTO_15MS,
	WDTO_30MS,
	WDTO_60MS,
	WDTO_120MS,
	WDTO_250MS,
	WDTO_500MS,
	WDTO_1S,
	WDTO_2S
};

/* GPIO */
#define NUM_PORTS			3
#define NUM_PINS			8

#define NUM_BANKS			3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
#define EXT_INT_SIZE		4

#define PORT_MULTIPLIER		3
#define P_OFFSET			235

#define EXTERNAL_NUM_INTERRUPTS	(NUM_BANKS + EXT_INT_SIZE + 1) // NOTE - fixed overflow bug	[14:13,4 Dec 2014]

#define PC_INT_SIZE		24

enum int_bank_t {PCINT_0, PCINT_1, PCINT_2, PCINT_NONE, EINT_0, EINT_1, EINT_2, EINT_3};
enum port_t {PORT_B=1, PORT_C, PORT_D};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};

/* Timer/Counter */
#	define INT_BIT			7

#	define T0_SIZE			8
#	define T0_PWM			1
#	define T0_OC			2
#	define T0_IC			0
#	define T0_AS			0
#	define T0_REV			0

#	define T1_SIZE			16
#	define T1_PWM			1
#	define T1_OC			2
#	define T1_IC			1
#	define T1_AS			0
#	define T1_REV			0

#	define NUM_8_BIT_TIMERS		1
#	define NUM_16_BIT_TIMERS	1
# 	define NUM_TIMERS		(NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS)

enum Tc_number {TC_0, TC_1};
enum Tc_oc_channel {TC_OC_A, TC_OC_B};
enum Tc_oc_mode {TC_OC_NONE, TC_OC_MODE_1, TC_OC_MODE_2, TC_OC_MODE_3, TC_OC_MODE_4, TC_OC_MODE_5, TC_OC_MODE_6, TC_OC_MODE_7, TC_OC_MODE_8, TC_OC_MODE_9, TC_OC_MODE_10, TC_OC_MODE_11, TC_OC_MODE_12, TC_OC_MODE_13, TC_OC_MODE_14, TC_OC_MODE_15};
enum Tc_oc_channel_mode {TC_OC_CHANNEL_MODE_0, TC_OC_CHANNEL_MODE_1, TC_OC_CHANNEL_MODE_2, TC_OC_CHANNEL_MODE_3};
enum Tc_ic_channel {TC_IC_A, TC_IC_B};
enum Tc_ic_mode {TC_IC_NONE, TC_IC_MODE_1, TC_IC_MODE_2, TC_IC_MODE_3, TC_IC_MODE_4};
enum Tc_clk_src {TC_SRC_INT};
enum Tc_prescalar {TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024};

/* CAN */
#define CAN_NUM_BUFFERS  6
#define CAN_NUM_FILTERS  6
#define CAN_NUM_MASKS 	6
#define CAN_NUM_BANKS	6
#define CAN_NUM_BUF_INT	3
#define CAN_NUM_CHAN_INT 2

enum Can_id_controller {CAN_0, NB_CTRL};
enum Can_id_buffer {CAN_BUF_0, CAN_BUF_1, CAN_BUF_2, CAN_BUF_3, CAN_BUF_4, CAN_BUF_5};
enum Can_id_filter {CAN_FIL_0, CAN_FIL_1, CAN_FIL_2, CAN_FIL_3, CAN_FIL_4, CAN_FIL_5};
enum Can_id_mask {CAN_MSK_0, CAN_MSK_1, CAN_MSK_2, CAN_MSK_3, CAN_MSK_4, CAN_MSK_5};
enum Can_id_filmask {CAN_FM_0, CAN_FM_1, CAN_FM_2, CAN_FM_3, CAN_FM_4, CAN_FM_5, CAN_FM_6};
enum Can_id_bank {CAN_BNK_0, CAN_BNK_1, CAN_BNK_2, CAN_BNK_3, CAN_BNK_4, CAN_BNK_5};
enum Can_bank_mode {CAN_BNK_MODE_FM};
enum Can_buffer_interrupt_type {CAN_RX_COMPLETE, CAN_TX_COMPLETE, CAN_GEN_ERROR};
enum Can_channel_interrupt_type {CAN_BUS_OFF, CAN_TIME_OVERRUN};

// This shows which pins have External Interrupts, and which have pin change interrupts assignable. The Atmega64M1/C1 has 3 interrupt ports with 8 pins each. Note that the EINT pins are also PCINT pins, but the EINT vector has priority over the PCINT.
static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =
						   {{PCINT_0, PCINT_0, EINT_1, PCINT_0, PCINT_0, EINT_2, PCINT_0, PCINT_0},		// B
							{EINT_3, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1},  	// C
							{PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, EINT_0, PCINT_2}};   // D
							// Port E exists but only has three pins and is for special features only.

/* USART */

// TXLIN/RXLIN pins
#define USARTLIN_TX_PORT		PORT_D
#define USARTLIN_TX_PIN			PIN_3
#define USARTLIN_RX_PORT		PORT_D
#define USARTLIN_RX_PIN			PIN_4

// TODO - What modes does LIN actually support?
enum Usart_setup_mode {USART_MODE_ASYNCHRONOUS, USART_MODE_ASYNCHRONOUS_DOUBLESPEED, USART_MODE_SYNCHRONOUS_MASTER, USART_MODE_SYNCHRONOUS_SLAVE};

// Specify which USART channels to support
enum Usart_channel {USART_0};
#define USE_USART_LIN USART_0

/* SPI */

// Port addresses for GPIO pins required for SPI
#define SPI0_MISO_PORT		PORT_B
#define SPI0_MISO_PIN		PIN_0
#define SPI0_MOSI_PORT		PORT_B
#define SPI0_MOSI_PIN		PIN_1
#define SPI0_SCK_PORT		PORT_B
#define SPI0_SCK_PIN		PIN_7
#define SPI0_SS_PORT		PORT_D
#define SPI0_SS_PIN			PIN_3

//TODO - How do we allow alternate pins to be used?
//  NB: They are selected through MCUCR<SPIPS>
#define SPI0_ALT_MISO_PORT		PORT_D
#define SPI0_ALT_MISO_PIN		PIN_2
#define SPI0_ALT_MOSI_PORT		PORT_D
#define SPI0_ALT_MOSI_PIN		PIN_3
#define SPI0_ALT_SCK_PORT		PORT_D
#define SPI0_ALT_SCK_PIN		PIN_4
#define SPI0_ALT_SS_PORT		PORT_C
#define SPI0_ALT_SS_PIN			PIN_1

// General preprocessor macros for convenience
#define NUM_SPI_CHANNELS		1
#define NUM_SPI_INTERRUPTS		1

enum Spi_channel {SPI_0};

#endif /*__TARGET_ATMEGA64C1_H__*/

