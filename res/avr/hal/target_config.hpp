// Copyright (C) 2011  Unison Networks Ltd
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
 * @file		target_config.hpp
 * Provides definitions for to be used in implementations.
 * 
 * 
 * @author 		Zac Frank
 *
 * @date		15-12-2011
 *  
 * @section Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
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
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// DEFINITIONS WHICH ARE SPECIFIC TO INDIVIDUAL MCU TYPES.

#if defined(__AVR_ATmega2560__)

 	/* Watchdog timer. */

	enum Watchdog_timeout {WDTO_15MS,
						WDTO_30MS,
						WDTO_60MS,
						WDTO_120MS,
						WDTO_250MS,
						WDTO_500MS,
						WDTO_1S,
						WDTO_2S,
						WDTO_4S,
						WDTO_8S};

	/* GPIO */

	#define NUM_PORTS			12	
	#define NUM_PINS			8
	
	#define NUM_BANKS			3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
	#define EXT_INT_SIZE			8
	
	#define PORT_MULTIPLIER	3
	#define P_OFFSET			235

	#define EXTERNAL_NUM_INTERRUPTS		(NUM_BANKS + EXT_INT_SIZE)
									  
	#define PC_INT_SIZE			24

 	enum int_bank_t {PCINT_0, PCINT_1, PCINT_2, PCINT_NONE, EINT_0, EINT_1, EINT_2, EINT_3, EINT_4, EINT_5, EINT_6, EINT_7};
	enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L};
	enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};

	/* Timer/Counter */

	#define T0_SIZE				8
	#define T0_PWM				1
	#define T0_OC				2
	#define T0_IC				0
	#define T0_AS				0
	#define T0_REV				0

	#define T1_SIZE				16
	#define T1_PWM				1
	#define T1_OC				3
	#define T1_IC				1
	#define T1_AS				0
	#define T1_REV				0

	#define T2_SIZE				8
	#define T2_PWM				1
	#define T2_OC				2
	#define T2_IC				0
	#define T2_AS				1
	#define T2_REV				0

	#define T3_SIZE				16
	#define T3_PWM				1
	#define T3_OC				3
	#define T3_IC				1
	#define T3_AS				0
	#define T3_REV				0

	#define T4_SIZE				16
	#define T4_PWM				1
	#define T4_OC				3
	#define T4_IC				1
	#define T4_AS				0
	#define T4_REV				0

	#define T5_SIZE				16
	#define T5_PWM				1
	#define T5_OC				3
	#define T5_IC				1
	#define T5_AS				0
	#define T5_REV				0
	
	#define NUM_8_BIT_TIMERS		2
	#define NUM_16_BIT_TIMERS		4
	#define NUM_TIMERS			(NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS)

	#define INT_BIT				7

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
							   {{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},		// A
								{PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0},				// B
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// C
								{EINT_0, EINT_1, EINT_2, EINT_3, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  			// D
								{PCINT_1, PCINT_NONE, PCINT_NONE, PCINT_NONE, EINT_4, EINT_5, EINT_6, EINT_7},				// E
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// F
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// G
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// H
								{PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_NONE},		 		// J
								{PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2},				// K
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE}};	// L

	/* USART. */

		// TODO - Are these not already defined in io.h?

	    // Address locations of registers for USART0.
	#define UDR0_ADDRESS			0xC6	//MEM8
	#define UBRR0_ADDRESS			0xC4	//MEM16
	#define UCSR0C_ADDRESS			0XC2	//MEM8
	#define UCSR0B_ADDRESS			0xC1	//MEM8
	#define UCSR0A_ADDRESS			0xC0	//MEM8

    	// Address locations of registers for USART1.
	#define UDR1_ADDRESS			0xCE	//MEM8
	#define UBRR1_ADDRESS			0xCC	//MEM16
	#define UCSR1C_ADDRESS			0xCA	//MEM8
	#define UCSR1B_ADDRESS			0xC9	//MEM8
	#define UCSR1A_ADDRESS			0xC8	//MEM8

    	// Address locations of registers for USART2.
	#define UDR2_ADDRESS			0xD6	//MEM8
	#define UBRR2_ADDRESS			0xD4	//MEM26
	#define UCSR2C_ADDRESS			0xD2	//MEM8
	#define UCSR2B_ADDRESS			0xD1	//MEM8
	#define UCSR2A_ADDRESS			0xD0	//MEM8

    	// Address locations of registers for USART3.
	#define UDR3_ADDRESS			0x136	//MEM8
	#define UBRR3_ADDRESS			0x134	//MEM36
	#define UCSR3C_ADDRESS			0x132	//MEM8
	#define UCSR3B_ADDRESS			0x131	//MEM8
	#define UCSR3A_ADDRESS			0x130	//MEM8

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
	#define NUM_USART_CHANNELS		4
	#define NUM_CHANNEL_INTERRUPTS		3
	#define NUM_USART_INTERRUPTS		NUM_USART_CHANNELS * NUM_CHANNEL_INTERRUPTS
		
	// TODO - The enums below came from usart.hpp, which makes no sense.  So anyway, I have no idea whether this is the right number of UARTs etc?

	enum Usart_channel {USART_0, USART_1, USART_2, USART_3};

	enum Usart_setup_mode {USART_MODE_ASYNCHRONOUS, USART_MODE_ASYNCHRONOUS_DOUBLESPEED, USART_MODE_SYNCHRONOUS_MASTER, USART_MODE_SYNCHRONOUS_SLAVE, USART_MODE_SPI_MASTER};

	enum Usart_mspim_bit_order {USART_MSPIM_MSB_FIRST, USART_MSPIM_LSB_FIRST};

	enum Usart_mspim_mode {USART_MSPI_MODE_0, USART_MSPI_MODE_1, USART_MSPI_MODE_2, USART_MSPI_MODE_3};

#elif defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)

 	/* Watchdog timer. */

	enum Watchdog_timeout {WDTO_15MS,
						   WDTO_30MS,
						   WDTO_60MS,
						   WDTO_120MS,
						   WDTO_250MS,
						   WDTO_500MS,
						   WDTO_1S,
						   WDTO_2S};

	/* GPIO */
	#define NUM_PORTS			3
	#define NUM_PINS			8
	
	#define NUM_BANKS			3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
	#define EXT_INT_SIZE			4
	
	#define PORT_MULTIPLIER	3
	#define P_OFFSET			235

	#define EXTERNAL_NUM_INTERRUPTS	(NUM_BANKS + EXT_INT_SIZE + 1)
									  
	#define PC_INT_SIZE			24

	enum int_bank_t {PCINT_0, PCINT_1, PCINT_2, PCINT_NONE, EINT_0, EINT_1, EINT_2, EINT_3};
	enum port_t {PORT_B=1, PORT_C, PORT_D};
	enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};								

	/* Timer/Counter */
	#define INT_BIT				7
	
	#define T0_SIZE				8
	#define T0_PWM				1
	#define T0_OC				2
	#define T0_IC				0
	#define T0_AS				0
	#define T0_REV				0

	#define T1_SIZE				16
	#define T1_PWM				1
	#define T1_OC				2
	#define T1_IC				1
	#define T1_AS				0
	#define T1_REV				0
	
	#define NUM_8_BIT_TIMERS		1
	#define NUM_16_BIT_TIMERS		1
	#define NUM_TIMERS			(NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS)

	enum Tc_number {TC_0, TC_1};
	enum Tc_oc_channel {TC_OC_A, TC_OC_B, TC_OC_C};
	enum Tc_oc_mode {TC_OC_NONE, TC_OC_MODE_1, TC_OC_MODE_2, TC_OC_MODE_3, TC_OC_MODE_4, TC_OC_MODE_5, TC_OC_MODE_6, TC_OC_MODE_7, TC_OC_MODE_8, TC_OC_MODE_9, TC_OC_MODE_10, TC_OC_MODE_11, TC_OC_MODE_12, TC_OC_MODE_13, TC_OC_MODE_14, TC_OC_MODE_15};
	enum Tc_oc_channel_mode {TC_OC_CHANNEL_MODE_0, TC_OC_CHANNEL_MODE_1, TC_OC_CHANNEL_MODE_2, TC_OC_CHANNEL_MODE_3};
	enum Tc_ic_channel {TC_IC_A, TC_IC_B};
	enum Tc_ic_mode {TC_IC_NONE, TC_IC_MODE_1, TC_IC_MODE_2, TC_IC_MODE_3, TC_IC_MODE_4};
	enum Tc_clk_src {TC_SRC_INT};
	enum Tc_prescalar {TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024};
	
	/* CAN */
	#define CAN_NUM_BUFFERS  		6
	#define CAN_NUM_FILTERS 		6
	#define CAN_NUM_MASKS 			6
	#define CAN_NUM_BANKS			6
	#define CAN_NUM_BUF_INT			3
	#define CAN_NUM_CHAN_INT 		2

	enum Can_id_controller {CAN_0, NB_CTRL};
	enum Can_id_buffer {CAN_BUF_0, CAN_BUF_1, CAN_BUF_2, CAN_BUF_3, CAN_BUF_4, CAN_BUF_5};
	enum Can_id_filter {CAN_FIL_0, CAN_FIL_1, CAN_FIL_2, CAN_FIL_3, CAN_FIL_4, CAN_FIL_5};
	enum Can_id_mask {CAN_MSK_0, CAN_MSK_1, CAN_MSK_2, CAN_MSK_3, CAN_MSK_4, CAN_MSK_5};
	enum Can_id_filmask {CAN_FM_0, CAN_FM_1, CAN_FM_2, CAN_FM_3, CAN_FM_4, CAN_FM_5, CAN_FM_6};
	enum Can_id_bank {CAN_BNK_0, CAN_BNK_1, CAN_BNK_2, CAN_BNK_3, CAN_BNK_4, CAN_BNK_5}; 
	enum Can_bank_mode {CAN_BNK_MODE_FM};
	enum Can_buffer_interrupt_type {CAN_RX_COMPLETE, CAN_TX_COMPLETE, CAN_GEN_ERROR};
	enum Can_channel_interrupt_type {CAN_BUS_OFF, CAN_TIME_OVERRUN};

	// This shows which pins have External Interrupts, and which have pin change interrupts assignable. 
	//The Atmega64M1/C1 has 3 interrupt ports with 8 pins each. Note that the EINT pins are also PCINT pins, but the EINT vector has priority over the PCINT.
	static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =  
							   {{PCINT_0, PCINT_0, EINT_1, PCINT_0, PCINT_0, EINT_2, PCINT_0, PCINT_0},		// B
								{EINT_3, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1},  	// C
								{PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, EINT_0, PCINT_2}};   // D
								// Port E exists but only has three pins and is for special features only.

#elif defined (__AVR_AT90CAN128__)

 	/* Watchdog timer. */

	enum Watchdog_timeout {WDTO_15MS,
						   WDTO_30MS,
						   WDTO_60MS,
						   WDTO_120MS,
						   WDTO_250MS,
						   WDTO_500MS,
						   WDTO_1S,
						   WDTO_2S};

	/* GPIO */
	#define NUM_PORTS			7
	#define NUM_PINS			8
		
	#define NUM_BANKS			0	// No PCINT pins hence no PCINT ports.
	#define EXT_INT_SIZE			8
	
	#define PORT_MULTIPLIER	3
	#define P_OFFSET			235

	#define EXTERNAL_NUM_INTERRUPTS		(NUM_BANKS + EXT_INT_SIZE)
									  
	#define PC_INT_SIZE			0	// No PCINT pins.

	enum int_bank_t {PCINT_NONE, EINT_0, EINT_1, EINT_2, EINT_3, EINT_4, EINT_5, EINT_6, EINT_7};
	enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G};
	enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};								
	
	/* Timer/Counter */	
	#define T0_SIZE				8
	#define T0_PWM				1
	#define T0_OC				2
	#define T0_IC				0
	#define T0_AS				0
	#define T0_REV				0

	#define T1_SIZE				16
	#define T1_PWM				1
	#define T1_OC				3
	#define T1_IC				1
	#define T1_AS				0
	#define T1_REV				0

	#define T2_SIZE				8
	#define T2_PWM				1
	#define T2_OC				2
	#define T2_IC				0
	#define T2_AS				0
	#define T2_REV				0

	#define T3_SIZE				16
	#define T3_PWM				1
	#define T3_OC				3
	#define T3_IC				1
	#define T3_AS				0
	#define T3_REV				0

	#define NUM_8_BIT_TIMERS		2
	#define NUM_16_BIT_TIMERS		2
	#define NUM_TIMERS			(NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS)
	#define INT_BIT				7

	enum Tc_number {TC_0, TC_1, TC_2, TC_3};
	enum Tc_oc_channel {TC_OC_A, TC_OC_B, TC_OC_C};
	enum Tc_oc_mode {TC_OC_NONE, TC_OC_MODE_1, TC_OC_MODE_2, TC_OC_MODE_3, TC_OC_MODE_4, TC_OC_MODE_5, TC_OC_MODE_6, TC_OC_MODE_7, TC_OC_MODE_8, TC_OC_MODE_9, TC_OC_MODE_10, TC_OC_MODE_11, TC_OC_MODE_12, TC_OC_MODE_13, TC_OC_MODE_14, TC_OC_MODE_15};
	enum Tc_oc_channel_mode {TC_OC_CHANNEL_MODE_0, TC_OC_CHANNEL_MODE_1, TC_OC_CHANNEL_MODE_2, TC_OC_CHANNEL_MODE_3};
	enum Tc_ic_channel {TC_IC_A};
	enum Tc_ic_mode {TC_IC_NONE, TC_IC_MODE_1, TC_IC_MODE_2, TC_IC_MODE_3, TC_IC_MODE_4};
	enum Tc_clk_src {TC_SRC_INT};
	enum Tc_prescalar {TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024};
	
	/* CAN */
	#define CAN_NUM_BUFFERS  		15
	#define CAN_NUM_FILTERS  		15
	#define CAN_NUM_MASKS 			15
	#define CAN_NUM_BANKS			15
	#define CAN_NUM_BUF_INT			3
	#define CAN_NUM_CHAN_INT 		2
	
	enum Can_id_controller {CAN_0, NB_CTRL};
	enum Can_id_buffer {CAN_BUF_0, CAN_BUF_1, CAN_BUF_2, CAN_BUF_3, CAN_BUF_4, CAN_BUF_5, CAN_BUF_6, CAN_BUF_7, CAN_BUF_8, CAN_BUF_9, CAN_BUF_10, CAN_BUF_11, CAN_BUF_12, CAN_BUF_13, CAN_BUF_14};
	enum Can_id_filter {CAN_FIL_0, CAN_FIL_1, CAN_FIL_2, CAN_FIL_3, CAN_FIL_4, CAN_FIL_5, CAN_FIL_6, CAN_FIL_7, CAN_FIL_8, CAN_FIL_9, CAN_FIL_10, CAN_FIL_11, CAN_FIL_12, CAN_FIL_13, CAN_FIL_14};
	enum Can_id_mask {CAN_MSK_0, CAN_MSK_1, CAN_MSK_2, CAN_MSK_3, CAN_MSK_4, CAN_MSK_5, CAN_MSK_6, CAN_MSK_7, CAN_MSK_8, CAN_MSK_9, CAN_MSK_10, CAN_MSK_11, CAN_MSK_12, CAN_MSK_13, CAN_MSK_14};
	enum Can_id_filmask {CAN_FM_0, CAN_FM_1, CAN_FM_2, CAN_FM_3, CAN_FM_4, CAN_FM_5, CAN_FM_6, CAN_FM_7, CAN_FM_8, CAN_FM_9, CAN_FM_10, CAN_FM_11, CAN_FM_12, CAN_FM_13, CAN_FM_14};
	enum Can_id_bank {CAN_BNK_0, CAN_BNK_1, CAN_BNK_2, CAN_BNK_3, CAN_BNK_4, CAN_BNK_5, CAN_BNK_6, CAN_BNK_7, CAN_BNK_8, CAN_BNK_9, CAN_BNK_10, CAN_BNK_11, CAN_BNK_12, CAN_BNK_13, CAN_BNK_14};
	enum Can_bank_mode {CAN_BNK_MODE_FM};
	enum Can_buffer_interrupt_type {CAN_RX_COMPLETE, CAN_TX_COMPLETE, CAN_GEN_ERROR};
	enum Can_channel_interrupt_type {CAN_BUS_OFF, CAN_TIME_OVERRUN};

	// This shows which pins have External Interrupts, and which have pin change interrupts assignable. The AT90CAN128 has 6 ports each with 8 pins. It only has external interrupt pins and no pin-change interrupts.
	static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =  
							   {{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},		// A
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},	// B
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// C
								{EINT_0, EINT_1, EINT_2, EINT_3, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  			// D
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, EINT_4, EINT_5, EINT_6, EINT_7},			// E
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},	// F
								{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE}}; 	// G
									
#else
	#error "No peripheral definition for this configuration."	
#endif

// DEFINITIONS WHICH ARE COMMON TO ALL AVR ARCHITECTURE TARGETS.

/* General */

#define TOTAL_PINS	(NUM_PORTS * PINS_PER_PORT)

/* GPIO */

// GPIO pin modes.  AVR devices have an optional pull-up on inputs, with all outputs operating push-pull.
enum Gpio_mode {GPIO_INPUT_PU, GPIO_OUTPUT_PP, GPIO_INPUT_FL};

/* EEPROM */

// EEPROM address (width).
typedef uint16_t Eeprom_address;

#endif /*__TARGET_CONFIG_H__*/
