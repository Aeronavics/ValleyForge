 /**
 * \file
 *
 * \brief Example of usage of the io port drivers for xmega.
 *
 * Copyright (c) 2011 Atmel Corporation. All rights reserved.
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
 * This example demonstrates how to use the Xmega port drivers.
 *
 * \section files Main Files
 * - ioport_example.c: port drivers example application.
 * - conf_board.h: board initialization process configuration
 * - conf_ioport_example.h: board-specific mapping of resources used by this
 *                          example
 * - init.c: board-specific initialization function
 * - ioport.c: port drivers for Xmega
 *
 * \section ioapiinfo drivers/io API
 * The io API can be found \ref ioport.h "here".
 *
 * \section deviceinfo Device Info
 * All AVR Xmega devices can be used. This example has been tested
 * with the following setup:
 *   - Simulator 
 *
 * \section exampledescription Description of the example
 *   - Simulator: Watch in IO View
 * \section setupinfo Setup Information
 *   - AVR XMega: the CPU clock uses the default configuration which is to run
 *                on the <i> 2 MHz internal RC oscillator </i>.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */
#include <preprocessor.h>
#include <conf_ioport_example.h>
#include <asf.h>

/*! \name Pin Configuration
 *  The pin config is done in the board-specific conf_io_example.h file.
 */
//! @{
#if !defined(IOPORT_PIN_EXAMPLE_1) || \
		!defined(IOPORT_PIN_EXAMPLE_2) || \
		!defined(IOPORT_PIN_EXAMPLE_3)
#error The pin configuration to use in this example is missing.
#endif
//! @}

/*! \brief Main function.
 */
int main(void)
{
	int8_t state = 0;

	// Initialize the board.
	// The board-specific conf_board.h file contains the configuration of
	// the board initialization.
	board_init();

	while (1)
	{
		// Dummy switch structure on a tri-state variable to show the
		// usage of the functions ioport_set_pin_low(),
		// port_set_pin_high(), port_toggle_pin().
		switch (state) {
		case 0:
			// Set the IOPORT_PIN_EXAMPLE_1 pin to low.
			ioport_set_pin_low(IOPORT_PIN_EXAMPLE_1);
			state++;
			break;

		case 1:
			// Set the IOPORT_PIN_EXAMPLE_1 pin to high.
			ioport_set_pin_high(IOPORT_PIN_EXAMPLE_1);
			state++;
			break;

		case 2:
			// Toggle the IOPORT_PIN_EXAMPLE_1 pin.
			ioport_toggle_pin(IOPORT_PIN_EXAMPLE_1);
			state++;
			break;

		case 3:
			// Toggle the IOPORT_PIN_EXAMPLE_1 pin.
			ioport_toggle_pin(IOPORT_PIN_EXAMPLE_1);
			state = 0;
			break;

		default:
			break;
		}
	}
}

