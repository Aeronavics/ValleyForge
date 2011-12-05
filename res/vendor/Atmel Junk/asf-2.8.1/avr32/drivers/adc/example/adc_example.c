/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief ADC example driver for AVR UC3.
 *
 * This file provides an example for the ADC on AVR UC3 devices.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR UC3
 * - Supported devices:  All AVR UC3 devices with an ADC
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/*! \page License
 * Copyright (c) 2009 Atmel Corporation. All rights reserved.
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
 * typedefs for the ADC driver. <BR>It also gives an example of the usage of the
 * ADC module, eg: <BR>
 * - [on EVK1100 and EVK1101 only] Use the temperature sensor and see the value change on a terminal,
 * - Use the light sensor and see the value change on a terminal,
 * - [on EVK1100 only] Use the adjustable resistor and see the value change on a terminal.<BR>
 *
 * \section files Main Files
 * - adc.c : ADC driver
 * - adc.h : ADC header file
 * - adc_example.c : ADC code example
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR32 and IAR Systems compiler
 * for AVR UC3. Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All AVR UC3 devices with a ADC module can be used. This example has been tested
 * with the following setup:<BR>
 * - EVK1100 evaluation kit,
 * - EVK1101 evaluation kit,
 * - EVK1104 evaluation kit.
 *
 * \section setupinfo Setup Information
 * <BR>CPU speed: <i> 12 MHz </i>
 * - [on EVK1100 and EVK1101 only] Connect USART_1 to your serial port via a
 * standard RS-232 D-SUB9 cable. Set the following settings in your terminal of
 * choice: 57600 8N1
 * - [on EVK1104 only] Connect a PC USB cable to the USB VCP plug (the USB plug
 * on the right) of the EVK1104. The PC is used as a power source. The UC3A3256
 * USART1 is connected to the UC3B USART1. The UC3B holds a firmware that acts as
 * a USART to USB gateway. On the USB side, the UC3B firmware implements a USB
 * CDC class: when connected to a PC, it will enumerate as a Virtual Com Port.
 * Once the UC3B USB is correctly installed on Windows, to communicate on this
 * port, open a HyperTerminal configured with the following settings: 57600 bps,
 * 8 data bits, no parity bit, 1 stop bit, no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/products/AVR32/">Atmel AVR UC3</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */

#include "board.h"
#include "print_funcs.h"
#include "gpio.h"
#include "pm.h"
#include "adc.h"
#include "delay.h"


/*! \name ADC channels choice
 */
//! @{
#if BOARD == EVK1100
// Connection of the temperature sensor
#  define EXAMPLE_ADC_TEMPERATURE_CHANNEL     0
#  define EXAMPLE_ADC_TEMPERATURE_PIN         AVR32_ADC_AD_0_PIN
#  define EXAMPLE_ADC_TEMPERATURE_FUNCTION    AVR32_ADC_AD_0_FUNCTION
// Connection of the light sensor
#  define EXAMPLE_ADC_LIGHT_CHANNEL           2
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_2_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_2_FUNCTION
// Connection of the potentiometer
#  define EXAMPLE_ADC_POTENTIOMETER_CHANNEL   1
#  define EXAMPLE_ADC_POTENTIOMETER_PIN       AVR32_ADC_AD_1_PIN
#  define EXAMPLE_ADC_POTENTIOMETER_FUNCTION  AVR32_ADC_AD_1_FUNCTION
// Note: Corresponding defines are defined in /BOARDS/EVK1100/evk1100.h.
// These are here for educational purposes only.
#elif BOARD == EVK1101
// Connection of the temperature sensor
#  define EXAMPLE_ADC_TEMPERATURE_CHANNEL     7
#  define EXAMPLE_ADC_TEMPERATURE_PIN         AVR32_ADC_AD_7_PIN
#  define EXAMPLE_ADC_TEMPERATURE_FUNCTION    AVR32_ADC_AD_7_FUNCTION
// Connection of the light sensor
#  define EXAMPLE_ADC_LIGHT_CHANNEL           6
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_6_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_6_FUNCTION
// Note: Corresponding defines are defined in /BOARDS/EVK1101/evk1101.h.
// These are here for educational purposes only.
#elif BOARD == EVK1104
// Connection of the light sensor
#  define EXAMPLE_ADC_LIGHT_CHANNEL           0
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_0_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_0_FUNCTION
// Note: Corresponding defines are defined in /BOARDS/EVK1104/evk1104.h.
// These are here for educational purposes only.
#elif BOARD == UC3_A3_XPLAINED
// Connection of the temperature sensor
#  define EXAMPLE_ADC_TEMPERATURE_CHANNEL     1
#  define EXAMPLE_ADC_TEMPERATURE_PIN         AVR32_ADC_AD_1_PIN
#  define EXAMPLE_ADC_TEMPERATURE_FUNCTION    AVR32_ADC_AD_1_FUNCTION
#endif
//! @}

/*!
 * \brief main function : do init and loop to display ADC values
 */
int main( void )
{
	volatile avr32_adc_t *adc = &AVR32_ADC; // ADC IP registers address

#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
	signed short adc_value_temp = -1;
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
	signed short adc_value_light = -1;
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
	signed short adc_value_pot = -1;
#endif

	// switch to oscillator 0
	pm_switch_to_osc0(&AVR32_PM, FOSC0, OSC0_STARTUP);

	// init debug serial line
	init_dbg_rs232(FOSC0);
	
	// Init delay module
	delay_init(FOSC0);

	// GPIO pin/adc-function map.
	static const gpio_map_t ADC_GPIO_MAP =
	{
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
		{EXAMPLE_ADC_TEMPERATURE_PIN, EXAMPLE_ADC_TEMPERATURE_FUNCTION},
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
		{EXAMPLE_ADC_LIGHT_PIN, EXAMPLE_ADC_LIGHT_FUNCTION},
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
		{EXAMPLE_ADC_POTENTIOMETER_PIN, EXAMPLE_ADC_POTENTIOMETER_FUNCTION}
#endif
	};

	// Assign and enable GPIO pins to the ADC function.
	gpio_enable_module(ADC_GPIO_MAP, sizeof(ADC_GPIO_MAP) / sizeof(ADC_GPIO_MAP[0]));

	// configure ADC
	// Lower the ADC clock to match the ADC characteristics (because we configured
	// the CPU clock to 12MHz, and the ADC clock characteristics are usually lower;
	// cf. the ADC Characteristic section in the datasheet).
	AVR32_ADC.mr |= 0x1 << AVR32_ADC_MR_PRESCAL_OFFSET;
	adc_configure(adc);

  // Enable the ADC channels.
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
	adc_enable(adc, EXAMPLE_ADC_TEMPERATURE_CHANNEL);
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
	adc_enable(adc, EXAMPLE_ADC_LIGHT_CHANNEL);
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
	adc_enable(adc, EXAMPLE_ADC_POTENTIOMETER_CHANNEL);
#endif

	// display a header to user
	print_dbg("\x1B[2J\x1B[H\r\nADC Example\r\n");

	// do an infinite loop
	while (true)
	{
		// launch conversion on all enabled channels
		adc_start(adc);
		
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
		// get value for the temperature adc channel
		adc_value_temp = adc_get_value(adc, EXAMPLE_ADC_TEMPERATURE_CHANNEL);
		// display value to user
		print_dbg("HEX Value for Channel temperature : 0x");
		print_dbg_hex(adc_value_temp);
		print_dbg("\r\n");
#endif

#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
		// get value for the light adc channel
		adc_value_light = adc_get_value(adc, EXAMPLE_ADC_LIGHT_CHANNEL);
		// display value to user
		print_dbg("HEX Value for Channel light : 0x");
		print_dbg_hex(adc_value_light);
		print_dbg("\r\n");
#endif

#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
		// get value for the potentiometer adc channel
		adc_value_pot = adc_get_value(adc, EXAMPLE_ADC_POTENTIOMETER_CHANNEL);
		// display value to user
		print_dbg("HEX Value for Channel pot : 0x");
		print_dbg_hex(adc_value_pot);
		print_dbg("\r\n");
#endif

		// slow down operations
		delay_ms(1000);
	}

	// Disable the ADC channels.
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
	adc_disable(adc, EXAMPLE_ADC_TEMPERATURE_CHANNEL);
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
	adc_disable(adc, EXAMPLE_ADC_LIGHT_CHANNEL);
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
	adc_disable(adc, EXAMPLE_ADC_POTENTIOMETER_CHANNEL);
#endif

	while (true);

	return 0;
}
