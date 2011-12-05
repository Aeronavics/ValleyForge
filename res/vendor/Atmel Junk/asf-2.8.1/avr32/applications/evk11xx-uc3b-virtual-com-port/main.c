/*This file is prepared for Doxygen automatic documentation generation.*/
/**
 * \file
 *
 * \brief Main file of the AVR UC3 USB Virtual Com Port application.
 *
 * Copyright (C) 2009 - 2011 Atmel Corporation. All rights reserved.
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
 * This application is a USB UART-USB bridge, using the USB CDC class (Virtual Communication Port).
 * This application is used on several AVR UC3 kits for the UC3B MCU (USB VCP port). 
 *
 * \section files Main files:
 * - main.c: main file with
 *   - setup the clocks,
 *   - setup the USB
 *   - main loop.
 * - user_board.h: default board configuration for the UC3B MCU (UART config).
 *
 * \section deviceinfo Device Info
 * This application is targeted for the UC3B MCU on the EVK1104, EVK1105, AT32UC3L-EK and UC3C-EK boards.
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


//_____  I N C L U D E S ___________________________________________________

#include "compiler.h"
#include "print_funcs.h"
#include "intc.h"
#include "pm.h"
#include "conf_usb.h"
#include "usb_task.h"
#include "power_clocks_lib.h"
#if USB_DEVICE_FEATURE == true
# include "device_cdc_task.h"
#endif


//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________

/*! \name System Clock Frequencies
 */
//! @{
pcl_freq_param_t pcl_freq_param =
{
#define APPLI_CPU_SPEED   24000000
#define APPLI_PBA_SPEED   24000000
	.cpu_f        = APPLI_CPU_SPEED,
	.pba_f        = APPLI_PBA_SPEED,
	.osc0_f       = FOSC0,
	.osc0_startup = OSC0_STARTUP
};
//! @}


	#if (defined __GNUC__)

/*! \brief Low-level initialization routine called during startup, before the
 *         main function.
 *
 * This version comes in replacement to the default one provided by the Newlib
 * add-ons library.
 * Newlib add-ons' _init_startup only calls init_exceptions, but Newlib add-ons'
 * exception and interrupt vectors are defined in the same section and Newlib
 * add-ons' interrupt vectors are not compatible with the interrupt management
 * of the INTC module.
 * More low-level initializations are besides added here.
 */
int _init_startup(void)
{
	// Import the Exception Vector Base Address.
	extern void _evba;

	// Load the Exception Vector Base Address in the corresponding system register.
	Set_system_register(AVR32_EVBA, (int)&_evba);

	// Enable exceptions.
	Enable_global_exception();

	// Initialize interrupt handling.
	INTC_init_interrupts();

	// Don't-care value for GCC.
	return 1;
}

  #elif (defined __ICCAVR32__)

/*! \brief Low-level initialization routine called during startup, before the
 *         main function.
 */
int __low_level_init(void)
{
	// Enable exceptions.
	Enable_global_exception();

	// Initialize interrupt handling.
	INTC_init_interrupts();

	// Request initialization of data segments.
	return 1;
}

	#endif  // Compiler



/*! \brief Main function. Execution starts here.
 *
 * \retval No return value.
 */
int main(void)
{
	// Configure system clocks.
	if (pcl_configure_clocks(&pcl_freq_param) != PASS)
		while(true);

	// Initialize USB clock
	pcl_configure_usb_clock();

	// Initialize USB task
	usb_task_init();

#if USB_DEVICE_FEATURE == true
	// Initialize device CDC USB task
	device_cdc_task_init();
#endif

	// Call each task in round-robin mode.
	while (true) {
		usb_task();
	#if USB_DEVICE_FEATURE == true
		device_cdc_task();
	#endif
	}
}
