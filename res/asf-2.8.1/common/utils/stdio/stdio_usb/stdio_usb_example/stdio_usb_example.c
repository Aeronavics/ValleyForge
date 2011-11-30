/**
 * \file
 *
 * \brief USB Standard I/O (stdio) Example
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This example demonstrates how to configure a C-library Standard I/O interface
 * to the ASF Common usb_group Service.  The initialization routines, along with
 * board and clock configuration constants, illustrate how to perform serial I/O
 * via a Communication Device Class (CDC) device protocol.
 *
 * \section files Main Files
 * - stdio_usb_example.c: the example application.
 * - conf_board.h: board configuration
 * - conf_clock.h: board configuration
 * - stdio_usb.h: Common USB CDC Standard I/O Implementation
 * - read.c : System implementation function used by standard library
 * - write.c : System implementation function used by standard library
 *
 * \section deviceinfo Device Info
 * All AVR and AVR32 devices supported by the ASF Common USB Protocol can be
 * used. This example has been tested with the following:
 *   - UC3-A3 Xplained Evaluation kit
 *
 * \sa cdc_protocol_group
 *
 * \section exampledescription Description of the example
 *   - Send message on USB CDC device to a Virtual Com Port.
 *   - Performs echo of any received character
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR and AVR32.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */

#include <board.h>
#include <sysclk.h>
#include <stdio_usb.h>

/**
 * \brief Specify the MCU serial I/O interface
 *
 * A constant like this is, ideally, defined in a separate configuration header
 * file along with other configurable parameters describing a particular part
 * or board configuration.
 */
#define CONFIG_USART_IF (AVR32_USART2)

/**
 * \brief Initialize USB CDC support for C-Library Standard I/O functions
 */
static void sio_init (void)
{
 	/* Start and attach USB CDC device interface for devices with
 	 * integrated USB interfaces.
 	 */
	stdio_usb_init(&CONFIG_USART_IF);	

	// Specify that stdout and stdin should not be buffered.

#if defined(__GNUC__) && defined(__AVR32__)
	setbuf(stdout, NULL);
	setbuf(stdin,  NULL);	
#endif
}

/**
 * \brief main function
 */
int main (void)
{
	/* Initialize basic board support features.
	 * - Initialize system clock sources according to device-specific
	 *   configuration parameters supplied in a conf_clock.h file.
	 * - Set up GPIO and board-specific features using additional configuration
	 *   parameters, if any, specified in a conf_board.h file.
	 */
	sysclk_init();
	board_init();

    // Initialize interrupt vector table support.
    irq_initialize_vectors();

    // Enable interrupts
    cpu_irq_enable();	

	/* Call a local utility routine to initialize C-Library Standard I/O over
	 * a USB CDC protocol.  Tunable parameters in a conf_usb.h file must be
	 * supplied to configure the protocol correctly.
     */
    sio_init();

	// Get and echo characters forever.

	uint8_t ch;

	while (true) {

		scanf("%c",&ch);            // get one input character
		
		if (ch) {
			printf("%c",ch);        // echo to output
		}
	}
}
