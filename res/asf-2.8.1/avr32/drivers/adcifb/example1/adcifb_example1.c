/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief ADCIFB example driver for AVR32 UC3.
 *
 * This file provides an example for the ADCIFB on AVR32 UC3 devices.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with an ADCIFB
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/*! \page License
 * Copyright (c) 2010 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */
/*! \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables, defines, enums, and
 * typedefs for the ADCIFB software driver. <BR>It also gives an example of usage of the
 * ADCIFB module, eg: <BR>
 * - On the AT32UC3L-EK: Display on a serial terminal the battery voltage converted value.
 * - On the UC3-L0-Xplained: Display on a serial terminal the voltage from the NTC 
 *   temperature sensor.
 *
 * \section files Main Files
 * - adcifb.c : ADCIFB driver
 * - adcifb.h : ADCIFB header file
 * - adcifb_example1.c : ADCIFB example1
 * - adcifb_example1.h : Configuration for ADCIFB example1
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR32 and IAR Systems compiler
 * for AVR32. Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All AVR32 devices with an ADCIFB module can be used. This example has been tested
 * with the following setup:<BR>
 * - AT32UC3L-EK evaluation kit
 * - UC3-L0-Xplained kit
 *
 * \section setupinfo Setup Information for the AT32UC3L-EK kit
 * <BR>CPU speed: <i> 12 MHz </i>
 * - Insert a V450HR battery into the socket of the AT32UC3L-EK
 * - Connect a PC USB cable to the USB VCP plug of the AT32UC3L-EK
 * - PC terminal settings:
 *   - 57600 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section setupinfo Setup Information for the UC3-L0-Xplained kit
 * <BR>CPU speed: <i> 12 MHz </i>
 * - Connect a PC USB cable to the USB VCP plug of the AT32UC3L-EK
 * - Connect the RXD and TXD pins on header J4 to a serial port
 *   via a RS232<->TTL level converter.
 * - PC terminal settings:
 *   - 57600 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/products/AVR32/">Atmel AVR32</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */
#include <avr32/io.h>
#include "board.h"
#include "print_funcs.h"
#include "gpio.h"
#include "power_clocks_lib.h"
#include "adcifb.h"
#include "conf_adcifb_example1.h" // Board specific header file


/*! \name Clock frequencies
 */
//! @{
#define EXAMPLE_TARGET_DFLL_FREQ_HZ     96000000  // DFLL target frequency, in Hz
#define EXAMPLE_TARGET_MCUCLK_FREQ_HZ   12000000  // MCU clock target frequency, in Hz
#define EXAMPLE_TARGET_PBACLK_FREQ_HZ   12000000  // PBA clock target frequency, in Hz
#define EXAMPLE_TARGET_CLK_ADC_FREQ_HZ  1500000   // Internal ADCIFB CLK_ADC clock frequency, in Hz
//! @}


#if !defined(EXAMPLE_ADCIFB_PIN) || \
	!defined(EXAMPLE_ADCIFB_FUNCTION) || \
	!defined(EXAMPLE_ADCIFB_CHANNEL_MASK) || \
	!defined(EXAMPLE_ADCIFB_CHANNEL_NAME)
#	error "ADC defines not set"
#endif


/*! \name Parameters to pcl_configure_clocks().
 */
//! @{
static scif_gclk_opt_t gc_dfllif_ref_opt = { SCIF_GCCTRL_SLOWCLOCK, 0, false};
static pcl_freq_param_t pcl_dfll_freq_param = {
	.main_clk_src = PCL_MC_DFLL0,
	.cpu_f        = EXAMPLE_TARGET_MCUCLK_FREQ_HZ,
	.pba_f        = EXAMPLE_TARGET_PBACLK_FREQ_HZ,
	.pbb_f        = EXAMPLE_TARGET_PBACLK_FREQ_HZ,
	.dfll_f       = EXAMPLE_TARGET_DFLL_FREQ_HZ,
	.pextra_params = &gc_dfllif_ref_opt
};
//! @}

/*!
 * \brief main function : do init and loop to display ADC values
 */
int main(void)
{
	volatile int i;
	// GPIO pin/adc-function map.
	static const gpio_map_t ADCIFB_GPIO_MAP = {
		{EXAMPLE_ADCIFB_PIN, EXAMPLE_ADCIFB_FUNCTION}
	};
	volatile avr32_adcifb_t *adcifb = &AVR32_ADCIFB; // ADCIFB IP registers address
	// ADCIFB Configuration
	adcifb_opt_t adcifb_opt = {
		.resolution = AVR32_ADCIFB_ACR_RES_12BIT, // Resolution mode
		.shtim  = 15,                             // Channels Sample & Hold Time in [0,15]
		.ratio_clkadcifb_clkadc = EXAMPLE_TARGET_PBACLK_FREQ_HZ/EXAMPLE_TARGET_CLK_ADC_FREQ_HZ,
		.startup = 3,                             // Startup time in [0,127], where Tstartup = startup * 8 * Tclk_adc (assuming Tstartup ~ 15us max)
		.sleep_mode_enable = false                // ADCIFB Sleep Mode disabled
	};
	unsigned long int adc_data;

	// Note: on the AT32UC3L-EK and UC3-L0-Xplained board, there are no crystal/external
	// clock connected to the OSC0 pinout XIN0/XOUT0. We shall then program the DFLL and
	// switch the main clock source to the DFLL.
	pcl_configure_clocks(&pcl_dfll_freq_param);
	// Note: since it is dynamically computing the appropriate field values of the
	// configuration registers from the parameters structure, this function is not
	// optimal in terms of code size. For a code size optimal solution, it is better
	// to create a new function from pcl_configure_clocks_dfll0() and modify it
	// to use preprocessor computation from pre-defined target frequencies.

	// init debug serial line
	init_dbg_rs232(EXAMPLE_TARGET_PBACLK_FREQ_HZ);

	// Assign and enable GPIO pins to the ADC function.
	gpio_enable_module(ADCIFB_GPIO_MAP, sizeof(ADCIFB_GPIO_MAP) / sizeof(ADCIFB_GPIO_MAP[0]));

	// Enable and configure the ADCIFB module
	if (PASS != adcifb_configure(adcifb, &adcifb_opt)) {
		// Config error.
		while (1) {
			gpio_tgl_gpio_pin(LED0_GPIO);
			for(i=100000; i; i--); // delay
		}
	}

	// Configure the trigger mode as "No trigger, only software trigger can start conversions".
	if(PASS != adcifb_configure_trigger(adcifb,
			AVR32_ADCIFB_TRGMOD_NT, 0)) {
		// Config error.
		while (1) {
			gpio_tgl_gpio_pin(LED1_GPIO);
			for(i=10000; i; i--); // delay
		}
	}

	// Enable the ADCIFB channel the battery is connected to.
	adcifb_channels_enable( adcifb, EXAMPLE_ADCIFB_CHANNEL_MASK);

	// do a loop
	for (;;) {
		// Wait until the ADC is ready to perform a conversion.
		while(false == adcifb_is_ready(adcifb));
		// Start an ADCIFB conversion sequence.
		adcifb_start_conversion_sequence(adcifb);

		// Wait until the converted data is available.
		while(false == adcifb_is_drdy(adcifb));

		// Get the last converted data.
		adc_data = adcifb_get_last_data(adcifb);

		// Display the current voltage of the battery.
		print_dbg("\x1B[2J\x1B[H\r\nADCIFB Example\r\nHEX Value for "
			  EXAMPLE_ADCIFB_CHANNEL_NAME " : 0x");
		print_dbg_hex(adc_data&AVR32_ADCIFB_LCDR_LDATA_MASK);
		print_dbg("\r\n");
		for(i=100000; i; i--); // delay

		// Note1: there is a resistor bridge between the battery and the ADC pad on
		// the AT32UC3L-EK. The data converted is thus half of the battery voltage.

		// Note2: if the battery is not in place, the conversion is out of spec because
		// the ADC input is then higher than ADVREF.
	}
}
