/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief DACIFB example driver for AVR32 UC3.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with an DACIFB
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
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the real time counter driver. It also comes
 * bundled with an application-example of usage.
 *
 * This example demonstrates how to use the DACIFB driver, the DACIFB clock being a generic clock (through the PEVC).
 * <b>Operating mode: </b>control the DAC output on PA15 [UC3C_EK] generating a sinus.
 *
 * \section files Main Files
 * - dacifb.c: DACIFB  driver;
 * - dacifb.h: DACIFB  driver header file;
 * - dacifb_example.c: DACIFB example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC for AVR32 and for IAR Embedded Workbench
 * for Atmel AVR32. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All AVR32 devices with a DACIFB and a USART module can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - UC3C_EK evaluation kit;
 * - CPU clock: 16 MHz;
 * - USART2 (on UC3C_EK) abstracted with a USB CDC connection to a PC;
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

#include "board.h"
#include "print_funcs.h"
#include "gpio.h"
#include "power_clocks_lib.h"
#include "dacifb.h"
#include "intc.h"
#include "pevc.h"
#include "pdca.h"
#include "sinus.h"

/*! \name DACIFB channels configuration
 */
//! @{
#if BOARD == UC3C_EK
// Connection of the AUDIO sensor
#  define EXAMPLE_DAC_AUDIO_INSTANCE            1
#  define EXAMPLE_DAC_AUDIO_CHANNEL             DACIFB_CHANNEL_SELECTION_B
#  define EXAMPLE_DAC_AUDIO_PIN                 AVR32_DAC1B_PIN
#  define EXAMPLE_DAC_AUDIO_FUNCTION            AVR32_DAC1B_PIN
#  define EXAMPLE_PDCA_CHANNEL_DAC              0
#  define AVR32_PDCA_PID_DAC_TX                 AVR32_PDCA_PID_DACIFB1_CHB_TX
#  define EXAMPLE_DAC_PRESCALER_CLOCK           FOSC0/2
#endif
//! @}

volatile avr32_dacifb_t *dacifb = &AVR32_DACIFB1; // DACIFB registers address
#if BOARD == UC3C_EK
 S16 dac_value_audio = -1;
#endif

  // Assign the on-board sensors to their DAC channel.
#if BOARD == UC3C_EK
 U8 dac_channel_audio = EXAMPLE_DAC_AUDIO_CHANNEL;
#endif

extern U16 sin_table[SINUS_SAMPLES];

volatile avr32_pevc_t         *ppevc  = &AVR32_PEVC;	// PEVC registers address

 // DACIFB Configuration
dacifb_opt_t dacifb_opt = {
                            .reference                  = DACIFB_REFERENCE_VDDANA,        // VDDANA Reference
                            .channel_selection          = DACIFB_CHANNEL_SELECTION_B,     // Selection Channels A&B
                            .low_power                  = false,                          // Low Power Mode     
                            .dual                       = false,                          // Dual Mode
                            .prescaler_clock_hz         = EXAMPLE_DAC_PRESCALER_CLOCK     // Prescaler Clock (Should be 500Khz)                              
};

// DACIFB Channel Configuration
dacifb_channel_opt_t dacifb_channel_opt = {
                                                .auto_refresh_mode    = false,                      // Auto Refresh Mode 
                                                .trigger_mode         = DACIFB_TRIGGER_MODE_EVENT, // Trigger selection
                                                .left_adjustment      = false,                      // Right Adjustment
                                                .data_shift           = 0,                          // Number of Data Shift 
                                                .data_round_enable    = false                       // Data Rouding Mode                                              };
};
  
/*! \brief The PDCA interrupt handler.
 *
 * The handler reload the PDCA settings with the correct ASCII animation address and size using the reload register.
 * The interrupt will happen each time half of the animation is played.
 * Let's use interrupt level 0 in the example.
 */
#if defined (__GNUC__)
__attribute__((__interrupt__))
#elif defined (__ICCAVR32__)
#if (UC3C)
#pragma handler = AVR32_PDCA_IRQ_GROUP0, 0
#endif
__interrupt
#endif
static void pdca_int_handler(void)
{
    // Set PDCA channel reload values with address where data to load are stored, and size of the data block to load.
    pdca_reload_channel(EXAMPLE_PDCA_CHANNEL_DAC, (void *)sin_table, SINUS_SAMPLES);
}

/*! \brief Init interrupt controller and register pdca_int_handler interrupt.
 */
void pdca_set_irq(void)
{
#if defined (__GNUC__)
  // Disable all interrupt/exception.
  Disable_global_interrupt();

  INTC_init_interrupts();

  // Register the compare interrupt handler to the interrupt controller
  // and enable the compare interrupt.
  // (__int_handler) &pdca_int_handler The handler function to register.
  // AVR32_PDCA_IRQ_0 The interrupt line to register to.
  // AVR32_INTC_INT0  The priority level to set for this interrupt line.
  // INTC_register_interrupt(__int_handler handler, int line, int priority);
  INTC_register_interrupt( (__int_handler) &pdca_int_handler, AVR32_PDCA_IRQ_0, AVR32_INTC_INT0);
#endif

  // Enable all interrupt/exception.
  Enable_global_interrupt();
}

void init_pevc(void)
{
  // PEVC Event Shaper options.
  static const pevc_evs_opt_t PEVC_EVS_OPTIONS = 
  {
    .igfdr = 0x0A,            // Set the IGF clock (don't care here).
    .igf = PEVC_EVS_IGF_OFF,  // Input Glitch Filter off
    .evf = PEVC_EVS_EVF_OFF,   // Enable Event on falling edge
    .evr = PEVC_EVS_EVR_ON    // Enable Event on rising edge
  };
  
  // PEVC Init.
  // Configuring the PEVC path: input is the generic clock, each clock cycle, the PEVC trigger a new DAC sample
  // The sinus samples are sent through the PDCA.  
  // a change on PEVC input pin0 event will trigger the PDCA channel 0/1 transfer
  if(FAIL == pevc_channel_configure(ppevc, 
                                    AVR32_PEVC_ID_USER_DACIFB1_CHB, 
                                    AVR32_PEVC_ID_GEN_GCLK_0, 
                                    &PEVC_EVS_OPTIONS))
  {
    while(1); // error
  }
    
  // Enable the PEVC channel 0.
  pevc_channels_enable(ppevc, 1<<AVR32_PEVC_ID_USER_DACIFB1_CHB);
}

void init_gclk(void)
{
  // Setup Sampling Rate
  // Sampling Rate = (115200/100) = 1152Hz
  // Setup the generic clock for EVENT
  scif_gc_setup(AVR32_SCIF_GCLK_GCLK2_EVENT, 
                SCIF_GCCTRL_SLOWCLOCK, 
                AVR32_SCIF_GC_DIV_CLOCK, 
                100);  
  // Now enable the generic clock
  scif_gc_enable(AVR32_SCIF_GCLK_GCLK2_EVENT);
}

/*!
 * \brief main function : do init and loop to display ADC values
 */
int main( void )
{
  // GPIO pin/dac-function map.
  static const gpio_map_t DACIFB_GPIO_MAP =
  {
    {AVR32_DACREF_PIN,AVR32_DACREF_FUNCTION},
    {AVR32_ADCREFP_PIN,AVR32_ADCREFP_FUNCTION},
    {AVR32_ADCREFN_PIN,AVR32_ADCREFN_FUNCTION},
#if BOARD == UC3C_EK
    {EXAMPLE_DAC_AUDIO_PIN, EXAMPLE_DAC_AUDIO_FUNCTION}
#endif
  };

  // switch to oscillator 0
  pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
  
  // init debug serial line
  init_dbg_rs232(FOSC0);

  // Assign and enable GPIO pins to the DAC function.
  gpio_enable_module(DACIFB_GPIO_MAP, sizeof(DACIFB_GPIO_MAP) / sizeof(DACIFB_GPIO_MAP[0]));

  // Get DACIFB Factory Configuration
  dacifb_get_calibration_data(dacifb, 
                              &dacifb_opt,
                              EXAMPLE_DAC_AUDIO_INSTANCE);
                              
  // configure DACIFB
  dacifb_configure(dacifb,
                   &dacifb_opt,
                   FOSC0);
  
  // Enable the DACIFB channels.
#if BOARD == UC3C_EK
  // configure channel DACIFB
  dacifb_configure_channel(dacifb,
                           dac_channel_audio,
                           &dacifb_channel_opt,
                           EXAMPLE_DAC_PRESCALER_CLOCK);
  
  dacifb_start_channel(dacifb,
                       dac_channel_audio,
                       FOSC0);
  
#endif

  // Initialize Event Controller
  init_pevc();
  
  // PDCA channel options
  static const pdca_channel_options_t PDCA_OPTIONS =
  {
    .addr = (void *)sin_table,                     // memory address
    .pid = AVR32_PDCA_PID_DAC_TX,                  // select peripheral - data are transmit on the DAC output
    .size = SINUS_SAMPLES,                         // transfer counter
    .r_addr = NULL,                                // next memory address
    .r_size = 0,                                   // next transfer counter
    .transfer_size = PDCA_TRANSFER_SIZE_HALF_WORD  // select size of the transfer      
  };

  // Init PDCA channel with the pdca_options.
  pdca_init_channel(EXAMPLE_PDCA_CHANNEL_DAC, &PDCA_OPTIONS); // init PDCA channel with options.

  // Register PDCA IRQ interrupt.
  pdca_set_irq();

  // Enable pdca interrupt each time the reload counter reaches zero.
  pdca_enable_interrupt_reload_counter_zero(EXAMPLE_PDCA_CHANNEL_DAC);
  
  // Enable now the transfer.
  pdca_enable(EXAMPLE_PDCA_CHANNEL_DAC);
  
  // Initialize Generic Clock
  init_gclk();
  
  // do a loop
  for (;;)
  {
  }

}
