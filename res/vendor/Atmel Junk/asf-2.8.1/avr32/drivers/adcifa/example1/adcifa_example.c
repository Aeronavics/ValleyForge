/**
 * \file
 *
 * \brief AVR UC3C ADCIFA driver example
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
/*! \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables, defines, enums, and
 * typedefs for the ADCIFA driver. <BR>It also gives an example of the usage of the
 * ADCIFA module, eg: <BR>
 * - [on UC3C_EK only] Use the potentiometer sensor and see the value change on a serial terminal,
 *
 * \section files Main Files
 * - adcifa.c : ADCIFA driver
 * - adcifa.h : ADCIFA header file
 * - adcifa_example.c : ADCIFA code example
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR32 and IAR Systems compiler
 * for AVR UC3. Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All AVR UC3 devices with a ADCIFA module can be used. This example has been tested
 * with the following setup:<BR>
 * - UC3C_EK evaluation kit
 *
 * \section setupinfo Setup Information
 * <BR>CPU speed: <i> 16 MHz </i>
 * - [on UC3C_EK only] Connect a PC USB cable to the USB VCP plug (the USB plug
 * on the right) of the UC3C_EK. The PC is used as a power source. The UC3C0512C
 * USART2 is connected to the UC3B USART1. The UC3B holds a firmware that acts as
 * a USART to USB gateway. It implements a USB
 * CDC class: when connected to a PC, it will enumerate as a Virtual Com Port.
 * Once the UC3B USB is correctly installed on Windows, to communicate on this
 * port, open a HyperTerminal configured with the following settings: 57600 bps,
 * 8 data bits, no parity bit, 1 stop bit, no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */

#include "board.h"
#include "print_funcs.h"
#include "gpio.h"
#include "power_clocks_lib.h"
#include "adcifa.h"

/*! \name ADCIFA channels choice
 */
//! @{
#if BOARD == UC3C_EK
#  define EXAMPLE_ADCIFA_NUMBER_OF_SEQUENCE     2
// Connection of the Potentiometer sensor
#  define EXAMPLE_ADC_POTENTIOMETER_INP         AVR32_ADCIFA_INP_ADCIN5
#  define EXAMPLE_ADC_POTENTIOMETER_INN         AVR32_ADCIFA_INN_GNDANA
#  define EXAMPLE_ADC_POTENTIOMETER_PIN         AVR32_ADCIN5_PIN
#  define EXAMPLE_ADC_POTENTIOMETER_FUNCTION    AVR32_ADCIN5_FUNCTION

#  define EXAMPLE_ADC_MIC_INP                   AVR32_ADCIFA_INP_GNDANA
#  define EXAMPLE_ADC_MIC_INN                   AVR32_ADCIFA_INN_ADCIN14
#  define EXAMPLE_ADC_MIC_PIN                   AVR32_ADCIN14_PIN
#  define EXAMPLE_ADC_MIC_FUNCTION              AVR32_ADCIN14_FUNCTION
#endif

#if !defined(EXAMPLE_ADC_MIC_INP) || \
    !defined(EXAMPLE_ADC_MIC_INN) || \
    !defined(EXAMPLE_ADC_MIC_PIN) || \
    !defined(EXAMPLE_ADC_MIC_FUNCTION)
#  error The ADCIFA configuration to use in this example is missing.
#endif
//! @}

/*!
 * \brief main function : initialization and loop to display ADC values
 */
int main( void )
{
	// GPIO pin/adc-function map.
	static const gpio_map_t ADCIFA_GPIO_MAP = {
		{AVR32_ADCREF0_PIN,AVR32_ADCREF0_FUNCTION},
		{AVR32_ADCREFP_PIN,AVR32_ADCREFP_FUNCTION},
		{AVR32_ADCREFN_PIN,AVR32_ADCREFN_FUNCTION},
		#if BOARD == UC3C_EK
		{EXAMPLE_ADC_POTENTIOMETER_PIN, EXAMPLE_ADC_POTENTIOMETER_FUNCTION},
		{EXAMPLE_ADC_MIC_PIN, EXAMPLE_ADC_MIC_FUNCTION}
		#endif
	};

	volatile avr32_adcifa_t *adcifa = &AVR32_ADCIFA; // ADCIFA IP registers address

	int16_t adc_values[EXAMPLE_ADCIFA_NUMBER_OF_SEQUENCE];

	// ADC Configuration
	adcifa_opt_t adc_config_t = {
		.frequency                = 1000000,  // ADC frequency (Hz)
		.reference_source         = ADCIFA_ADCREF0, // Reference Source
		.sample_and_hold_disable  = false,    // Disable Sample and Hold Time
		.single_sequencer_mode    = false,    // Single Sequencer Mode 
		.free_running_mode_enable = false,    // Free Running Mode 
		.sleep_mode_enable        = false     // Sleep Mode
	};
  
	// Sequencer Configuration
	adcifa_sequencer_opt_t adcifa_sequence_opt = {
		.convnb               = EXAMPLE_ADCIFA_NUMBER_OF_SEQUENCE, // Number of sequence
		.resolution           = ADCIFA_SRES_12B,         // Resolution selection
		.trigger_selection    = ADCIFA_TRGSEL_SOFT,      // Trigger selection
		.start_of_conversion  = ADCIFA_SOCB_ALLSEQ,      // Conversion Management
		.sh_mode              = ADCIFA_SH_MODE_OVERSAMP, // Oversampling Management 
		.half_word_adjustment = ADCIFA_HWLA_NOADJ,       // Half word Adjustment
		.software_acknowledge = ADCIFA_SA_NO_EOS_SOFTACK // Software Acknowledge
	};
    
	#if BOARD == UC3C_EK
	// Conversions in the Sequencer Configuration  
	adcifa_sequencer_conversion_opt_t 
		adcifa_sequence_conversion_opt[EXAMPLE_ADCIFA_NUMBER_OF_SEQUENCE] = {
		{
			.channel_p = EXAMPLE_ADC_POTENTIOMETER_INP,   // Positive Channel
			.channel_n = EXAMPLE_ADC_POTENTIOMETER_INN,   // Negative Channel
			.gain      = ADCIFA_SHG_1                     // Gain of the conversion
		},
		{
			.channel_p = EXAMPLE_ADC_MIC_INP,             // Positive Channel
			.channel_n = EXAMPLE_ADC_MIC_INN,             // Negative Channel
			.gain      = ADCIFA_SHG_8                     // Gain of the conversion
		}
	};
	#endif // end BOARD == UC3C_EK

	volatile int32_t i;

	// switch to oscillator 0
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);

	// init debug serial line
	init_dbg_rs232(FOSC0);

	// Assign and enable GPIO pins to the ADC function.
	gpio_enable_module(ADCIFA_GPIO_MAP, sizeof(ADCIFA_GPIO_MAP) / sizeof(ADCIFA_GPIO_MAP[0]));

	// Get ADCIFA Factory Configuration
	adcifa_get_calibration_data(adcifa, &adc_config_t);
	if ((uint16_t)adc_config_t.offset_calibration_value == 0xFFFF){ 
	// Set default calibration if Engineering samples and part is not programmed
		adc_config_t.offset_calibration_value = 0x3B;
		adc_config_t.gain_calibration_value = 0x4210;
		adc_config_t.sh0_calibration_value = 0x210;
		adc_config_t.sh1_calibration_value = 0x210;
	}
	adc_config_t.offset_calibration_value = 0x3B; // offset correction

	// Configure ADCIFA core
	adcifa_configure(adcifa, &adc_config_t, FOSC0);

	// Configure ADCIFA sequencer 0
	adcifa_configure_sequencer(adcifa, 0, &adcifa_sequence_opt, adcifa_sequence_conversion_opt);

	// do a loop
	while (true) {
		// slow down operations
		for ( i=0 ; i < 1000000 ; i++);

		// display a header to user
		print_dbg("\x1B[2J\x1B[H\r\nADCIFA Example\r\n");

		// Start ADCIFA sequencer 0
		adcifa_start_sequencer(adcifa, 0);

		// Get Values from sequencer 0
		if (adcifa_get_values_from_sequencer(adcifa,
				0,
				&adcifa_sequence_opt,
				adc_values) == ADCIFA_STATUS_COMPLETED) {
				#if BOARD == UC3C_EK    
				// display value to user
				print_dbg("HEX Value for Channel potentiometer: 0x");
				print_dbg_hex(adc_values[0]);
				print_dbg("\r\n");
				print_dbg("HEX Value for Channel microphone: 0x");
				print_dbg_hex(~adc_values[1]);
				print_dbg("\r\n");        
				#endif // BOARD == UC3C_EK
		}
	}
}
