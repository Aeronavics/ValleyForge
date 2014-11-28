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
 * @file		atmega2560.hpp
 * Provides target configuration for the ATmega2560 family of chips
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
#ifndef __TARGET_ATMEGA2560_H__
#define __TARGET_ATMEGA2560_H__


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
	WDTO_2S,
	WDTO_4S,
	WDTO_8S
};

/* GPIO */

#define NUM_PORTS		12
#define NUM_PINS			8

#define NUM_BANKS		3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
#define EXT_INT_SIZE		8

#define PORT_MULTIPLIER	3
#define P_OFFSET			235

#define EXTERNAL_NUM_INTERRUPTS	(NUM_BANKS + EXT_INT_SIZE)

#define PC_INT_SIZE		24

enum int_bank_t {PCINT_0, PCINT_1, PCINT_2, PCINT_NONE, EINT_0, EINT_1, EINT_2, EINT_3, EINT_4, EINT_5, EINT_6, EINT_7};
enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};

/* Timer/Counter */

#define T0_SIZE			8
#define T0_PWM			1
#define T0_OC			2
#define T0_IC			0
#define T0_AS			0
#define T0_REV			0

#define T1_SIZE			16
#define T1_PWM			1
#define T1_OC			3
#define T1_IC			1
#define T1_AS			0
#define T1_REV			0

#define T2_SIZE			8
#define T2_PWM			1
#define T2_OC			2
#define T2_IC			0
#define T2_AS			1
#define T2_REV			0

#define T3_SIZE			16
#define T3_PWM			1
#define T3_OC			3
#define T3_IC			1
#define T3_AS			0
#define T3_REV			0

#define T4_SIZE			16
#define T4_PWM			1
#define T4_OC			3
#define T4_IC			1
#define T4_AS			0
#define T4_REV			0

#define T5_SIZE			16
#define T5_PWM			1
#define T5_OC			3
#define T5_IC			1
#define T5_AS			0
#define T5_REV			0

#define NUM_8_BIT_TIMERS		2
#define NUM_16_BIT_TIMERS	4
#define NUM_TIMERS		(NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS)

#define INT_BIT			7

enum Tc_number {TC_0, TC_1, TC_2, TC_3, TC_4, TC_5};
enum Tc_oc_channel {TC_OC_A, TC_OC_B, TC_OC_C};
enum Tc_oc_mode {TC_OC_NONE, TC_OC_MODE_1, TC_OC_MODE_2, TC_OC_MODE_3, TC_OC_MODE_4, TC_OC_MODE_5, TC_OC_MODE_6, TC_OC_MODE_7, TC_OC_MODE_8, TC_OC_MODE_9, TC_OC_MODE_10, TC_OC_MODE_11, TC_OC_MODE_12, TC_OC_MODE_13, TC_OC_MODE_14, TC_OC_MODE_15};
enum Tc_oc_channel_mode {TC_OC_CHANNEL_MODE_0, TC_OC_CHANNEL_MODE_1, TC_OC_CHANNEL_MODE_2, TC_OC_CHANNEL_MODE_3};
enum Tc_ic_channel {TC_IC_A};
enum Tc_ic_mode {TC_IC_NONE, TC_IC_MODE_1, TC_IC_MODE_2, TC_IC_MODE_3, TC_IC_MODE_4};
enum Tc_clk_src {TC_SRC_INT};
enum Tc_prescalar {TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024};

// TODO - Realised this might be an issue if not all the timers are the same size.

// This shows which pins have External Interrupts, and which have pin change interrupts assignable. The ATmega2560 has only 8 External Pin interrupts, and a range of Pin Change interrupts.
static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =
						   {{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},	// A
							{PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0},							// B
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// C
							{EINT_0, EINT_1, EINT_2, EINT_3, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  					// D
							{PCINT_1, PCINT_NONE, PCINT_NONE, PCINT_NONE, EINT_4, EINT_5, EINT_6, EINT_7},						// E
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// F
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// G
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// H
							{PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_NONE},		 				// J
							{PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2},							// K
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE}};	// L

/* USART. */

// Generic bit addresses for register manipulation.

// UCSRnA Register.
#define RXC_BIT				7
#define TXC_BIT				6
#define UDRE_BIT			5
#define FE_BIT				4
#define DOR_BIT				3
#define UPE_BIT				2
#define U2X_BIT				1
#define MPCM_BIT			0

// UCSRnB Register.
#define RXCIE_BIT			7
#define TXCIE_BIT			6
#define UDRIE_BIT			5
#define RXEN_BIT			4
#define TXEN_BIT			3
#define UCSZ2_BIT			2
#define RXB8_BIT			1
#define TXB8_BIT			0

// UCSRnC Register.
#define UMSEL1_BIT			7
#define UMSEL0_BIT			6
#define UPM1_BIT			5
#define UPM0_BIT			4
#define USBS_BIT			3
#define UCSZ1_BIT			2
#define UCSZ0_BIT			1
#define UCPOL_BIT			0

// UCSRnC Register (when in Master SPI Mode).
#define UDORD_BIT			2
#define UCPHA_BIT			1

// GPIO addresses of transmitter and receiver pins for each USART channel.
#define USART0_TX_PORT			PORT_E
#define USART0_TX_PIN			PIN_1
#define USART0_RX_PORT			PORT_E
#define USART0_RX_PIN			PIN_0
#define USART0_XCK_PORT			PORT_E
#define USART0_XCK_PIN			PIN_2

#define USART1_TX_PORT			PORT_D
#define USART1_TX_PIN			PIN_3
#define USART1_RX_PORT			PORT_D
#define USART1_RX_PIN			PIN_2
#define USART1_XCK_PORT			PORT_D
#define USART1_XCK_PIN			PIN_5

#define USART2_TX_PORT			PORT_H
#define USART2_TX_PIN			PIN_1
#define USART2_RX_PORT			PORT_H
#define USART2_RX_PIN			PIN_0
#define USART2_XCK_PORT			PORT_H
#define USART2_XCK_PIN			PIN_2

#define USART3_TX_PORT			PORT_J
#define USART3_TX_PIN			PIN_1
#define USART3_RX_PORT			PORT_J
#define USART3_RX_PIN			PIN_0
#define USART3_XCK_PORT			PORT_J
#define USART3_XCK_PIN			PIN_2

// General preprocessor macros for convenience.
#define NUM_USART_CHANNELS			4
#define NUM_CHANNEL_INTERRUPTS		3
#define NUM_USART_INTERRUPTS		NUM_USART_CHANNELS * NUM_CHANNEL_INTERRUPTS

// NOTE - This chip supports additional SPI channels through the use of the USART modules.
//  If using a USARTSPI channel, the corresponding USART channel may not be used.
enum Usart_channel {USART_0, USART_1, USART_2, USART_3};
enum Spi_channel {SPI_0, USARTSPI_0, USARTSPI_1, USARTSPI_2, USARTSPI_3};

enum Usart_setup_mode {USART_MODE_ASYNCHRONOUS, USART_MODE_ASYNCHRONOUS_DOUBLESPEED, USART_MODE_SYNCHRONOUS_MASTER, USART_MODE_SYNCHRONOUS_SLAVE};

// Specify which USART channels to support
#define USE_USART0 USART_0
#define USE_USART1 USART_1
#define USE_USART2 USART_2
#define USE_USART3 USART_3


#endif /*__TARGET_ATMEGA2560_H__*/