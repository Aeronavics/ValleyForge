/**
 * \file
 *
 * \brief AVR XMEGA USART example
 *
 * Copyright (C) 2010 Atmel Corporation. All rights reserved.
 *
 * \page License
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

/*! \mainpage
 * \section intro Introduction
 * This example demonstrates how to use XMEGA USART module.
 *
 * \section files Main Files
 * - usart_example.c: the example application.
 * - conf_board.h: board configuration
 * - conf_usart_example.h: configuration of the example
 *
 * \section usart_apiinfo drivers/usart API
 * The USART driver API can be found \ref usart_group "here".
 *
 * \section deviceinfo Device Info
 * All AVR XMEGA devices can be used. This example has been tested
 * with the following setup:
 *   - Xplain evaluation kit (USARTD0 on PORTD is used by default.
 *     Change to USARTC0 to use the USB Virtual COM PORT of the Xplain).
 *   - ATxmega128A1 and ATxmega256A3 on the STK600 (RC064X and RC100C routing
 *     boards), respectively (USARTC0 should be connected to the RS22 spare port
 *     of STK600)
 *
 * \section exampledescription Description of the example
 * The example waits for a received character on the configured USART and echoes
 * the character back to the same USART.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */
#include <conf_usart_example.h>
#include <asf.h>

/*! \brief Main function.
 */
int main(void)
{
	uint8_t tx_buf[] = "\n\rHello AVR world ! : ";
	uint8_t tx_length = 22;
	uint8_t received_byte;
	uint8_t i;

	// USART options.
	static usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SERIAL_EXAMPLE_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};

	sysclk_init();

	/* Initialize the board.
	 * The board-specific conf_board.h file contains the configuration of
	 * the board initialization.
	 */
	board_init();

#ifdef USARTC0
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTC0) {
		sysclk_enable_module(SYSCLK_PORT_C, PR_USART0_bm);
	} else
#endif
#ifdef USARTC1
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTC1) {
		sysclk_enable_module(SYSCLK_PORT_C, PR_USART1_bm);
	} else
#endif
#ifdef USARTD0
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTD0) {
		sysclk_enable_module(SYSCLK_PORT_D, PR_USART0_bm);
	} else
#endif
#ifdef USARTD1
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTD1) {
		sysclk_enable_module(SYSCLK_PORT_D, PR_USART1_bm);
	} else
#endif
#ifdef USARTE0
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTE0) {
		sysclk_enable_module(SYSCLK_PORT_E, PR_USART0_bm);
	} else
#endif
#ifdef USARTE1
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTE1) {
		sysclk_enable_module(SYSCLK_PORT_E, PR_USART1_bm);
	} else
#endif
#ifdef USARTF0
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTF0) {
		sysclk_enable_module(SYSCLK_PORT_F, PR_USART0_bm);
	} else
#endif
#ifdef USARTF1
	if ((uint16_t) USART_SERIAL_EXAMPLE == (uint16_t) & USARTF1) {
		sysclk_enable_module(SYSCLK_PORT_F, PR_USART1_bm);
	}
#endif

	// Initialize usart driver in RS232 mode
	usart_init_rs232(USART_SERIAL_EXAMPLE, &USART_SERIAL_OPTIONS);

	// Send "message header"
	for (i = 0; i < tx_length; i++) {
		usart_putchar(USART_SERIAL_EXAMPLE, tx_buf[i]);
	}
	// Get and echo a character forever, specific '\r' processing.
	while (true) {
		received_byte = usart_getchar(USART_SERIAL_EXAMPLE);
		if (received_byte == '\r') {
			for (i = 0; i < tx_length; i++) {
				usart_putchar(USART_SERIAL_EXAMPLE, tx_buf[i]);
			}
		} else
			usart_putchar(USART_SERIAL_EXAMPLE, received_byte);
	}
}
