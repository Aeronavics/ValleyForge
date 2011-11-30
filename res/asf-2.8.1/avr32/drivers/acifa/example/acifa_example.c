/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief ACIFA example driver for AVR UC3.
 *
 * This file provides an example for the ACIFA on AVR UC3 devices.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR UC3
 * - Supported devices:  All AVR UC3 devices with an ACIFA
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
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIE
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
 *//*! \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables, defines, enums, and
 * typedefs for the ACIFA driver. <BR>It also gives an example of the usage of the
 * ACIFA module, eg: <BR>
 * - [on UC3C_EK only] Three internal comparators are used
 *        -- Comparator 1: Input + : PA06 and Input - : PA07,
 *        -- Comparator 2: Input + : PA20 and Input - : PA22,
 *        -- Comparator 3: Input + : PA23 and Input - : PA21
 * \section files Main Files
 * - acifa.c : ACIFA driver
 * - acifa.h : ACIFA header file
 * - acifa_example.c : ADCIFA code example
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR32 and IAR Systems compiler
 * for AVR UC3 devices. Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All AVR UC3 devices with a ACIFA module can be used. This example has been tested
 * with the following setup:<BR>
 * - UC3C_EK evaluation kit
 *
 * \section setupinfo Setup Information
 * <BR>CPU speed: <i> 16 MHz </i>
 * - [on UC3C_EK only] Connect a PC USB cable to the USB VCP plug (the USB plug
 * on the right) of the UC3C_EK. The PC is used as a power source. The UC3C0512
 * USART2 is connected to the UC3B USART1. The UC3B holds a firmware that acts as
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
#include "power_clocks_lib.h"
#include "acifa.h"

/*! \name ACIFA channels configuration for the example
 */
//! @{
#if BOARD == UC3C_EK
// Connection of the Analog Comparators
// ACMP0 : Comparator + (PA6)
#  define EXAMPLE_AC_ACMP0_INPUT        1
#  define EXAMPLE_AC_ACMP0_PIN          AVR32_AC1AP1_PIN
#  define EXAMPLE_AC_ACMP0_FUNCTION     AVR32_AC1AP1_FUNCTION
// ACMPN0 : Comparator - (PA7)
#  define EXAMPLE_AC_ACMPN0_INPUT       1
#  define EXAMPLE_AC_ACMPN0_PIN         AVR32_AC1AN1_PIN
#  define EXAMPLE_AC_ACMPN0_FUNCTION    AVR32_AC1AN1_FUNCTION
// ACMP1 : Comparator + (PA20)
#  define EXAMPLE_AC_ACMP1_INPUT        0
#  define EXAMPLE_AC_ACMP1_PIN          AVR32_AC0AP0_PIN
#  define EXAMPLE_AC_ACMP1_FUNCTION     AVR32_AC0AP0_FUNCTION
// ACMPN0 : Comparator - (PA22)
#  define EXAMPLE_AC_ACMPN1_INPUT       0
#  define EXAMPLE_AC_ACMPN1_PIN         AVR32_AC0AN0_PIN
#  define EXAMPLE_AC_ACMPN1_FUNCTION    AVR32_AC0AN0_FUNCTION
// ACMP2 : Comparator + (PA23)
#  define EXAMPLE_AC_ACMP2_INPUT        2
#  define EXAMPLE_AC_ACMP2_PIN          AVR32_AC0BP0_PIN
#  define EXAMPLE_AC_ACMP2_FUNCTION     AVR32_AC0BP0_FUNCTION
// ACMPN2 : Comparator - (PA21)
#  define EXAMPLE_AC_ACMPN2_INPUT       0
#  define EXAMPLE_AC_ACMPN2_PIN         AVR32_AC0BN0_PIN
#  define EXAMPLE_AC_ACMPN2_FUNCTION    AVR32_AC0BN0_FUNCTION
#endif
//! @}

#if !defined(EXAMPLE_AC_ACMP0_INPUT)    || \
    !defined(EXAMPLE_AC_ACMP0_PIN)      || \
    !defined(EXAMPLE_AC_ACMP0_FUNCTION) || \
    !defined(EXAMPLE_AC_ACMPN0_INPUT)   || \
    !defined(EXAMPLE_AC_ACMPN0_PIN)     || \
    !defined(EXAMPLE_AC_ACMPN0_FUNCTION)|| \
    !defined(EXAMPLE_AC_ACMP1_INPUT)    || \
    !defined(EXAMPLE_AC_ACMP1_PIN)      || \
    !defined(EXAMPLE_AC_ACMP1_FUNCTION) || \
    !defined(EXAMPLE_AC_ACMPN1_INPUT)   || \
    !defined(EXAMPLE_AC_ACMPN1_PIN)     || \
    !defined(EXAMPLE_AC_ACMPN1_FUNCTION)|| \
    !defined(EXAMPLE_AC_ACMP2_INPUT)    || \
    !defined(EXAMPLE_AC_ACMP2_PIN)      || \
    !defined(EXAMPLE_AC_ACMP2_FUNCTION) || \
    !defined(EXAMPLE_AC_ACMPN2_INPUT)   || \
    !defined(EXAMPLE_AC_ACMPN2_PIN)     || \
    !defined(EXAMPLE_AC_ACMPN2_FUNCTION)    
#error The ADCIFA configuration to use in the example is missing.
#endif

/*!
 * \brief main function : do init and loop to display ACIFA values
 */
int main( void )
{
  // GPIO pin/adc-function map.
  static const gpio_map_t ACIFA_GPIO_MAP =
  {
    {AVR32_ADCREF0_PIN,AVR32_ADCREF0_FUNCTION},
    {AVR32_ADCREFP_PIN,AVR32_ADCREFP_FUNCTION},
    {AVR32_ADCREFN_PIN,AVR32_ADCREFN_FUNCTION},
#if BOARD == UC3C_EK
    {EXAMPLE_AC_ACMP0_PIN, EXAMPLE_AC_ACMP0_FUNCTION},
    {EXAMPLE_AC_ACMPN0_PIN, EXAMPLE_AC_ACMPN0_FUNCTION},
    {EXAMPLE_AC_ACMP1_PIN, EXAMPLE_AC_ACMP1_FUNCTION},
    {EXAMPLE_AC_ACMPN1_PIN, EXAMPLE_AC_ACMPN1_FUNCTION},
    {EXAMPLE_AC_ACMP2_PIN, EXAMPLE_AC_ACMP2_FUNCTION},
    {EXAMPLE_AC_ACMPN2_PIN, EXAMPLE_AC_ACMPN2_FUNCTION}
#endif
  };

  volatile avr32_acifa_t *acifa0 = &AVR32_ACIFA0; // ACIFA0 IP registers address
  volatile avr32_acifa_t *acifa1 = &AVR32_ACIFA1; // ACIFA1 IP registers address

  volatile int i;

  // switch to oscillator 0
  pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);

  // init debug serial line
  init_dbg_rs232(FOSC0);

  // Assign and enable GPIO pins to the AC function.
  gpio_enable_module(ACIFA_GPIO_MAP, sizeof(ACIFA_GPIO_MAP) / sizeof(ACIFA_GPIO_MAP[0]));

  // configure ACIFA
  acifa_configure(acifa1,
                  ACIFA_COMP_SELA,
                  EXAMPLE_AC_ACMP0_INPUT,
                  EXAMPLE_AC_ACMPN0_INPUT,
                  FOSC0);

  // Start the ACIFA.
  acifa_start(acifa1,
              ACIFA_COMP_SELA);

  // configure ACIFA
  acifa_configure(acifa0,
                  ACIFA_COMP_SELA,
                  EXAMPLE_AC_ACMP1_INPUT,
                  EXAMPLE_AC_ACMPN1_INPUT,
                  FOSC0);
  acifa_configure(acifa0,
                  ACIFA_COMP_SELB,
                  EXAMPLE_AC_ACMP2_INPUT,
                  EXAMPLE_AC_ACMPN2_INPUT,
                  FOSC0);
  
  // Start the ACIFA.
  acifa_start(acifa0,
              (ACIFA_COMP_SELA|ACIFA_COMP_SELB));

  
  // do a loop
  for (;;)
  {
    // slow down operations
    for ( i=0 ; i < 1000000 ; i++);

    // display a header to user
    print_dbg("\x1B[2J\x1B[H\r\nACIFA Example\r\n");

#if BOARD == UC3C_EK
    if (acifa_is_aca_inp_higher(acifa1))
    {
      print_dbg("ACMP0 > ACMPN0");
      print_dbg("\r\n");
    }
    else
    {
      print_dbg("ACMP0 < ACMPN0");
      print_dbg("\r\n");
    }
    if (acifa_is_aca_inp_higher(acifa0))
    {
      print_dbg("ACMP1 > ACMPN1");
      print_dbg("\r\n");
    }
    else
    {
      print_dbg("ACMP1 < ACMPN1");
      print_dbg("\r\n");
    } 
 
    if (acifa_is_acb_inp_higher(acifa0))
    {
      print_dbg("ACMP2 > ACMPN2");
      print_dbg("\r\n");
    }
    else
    {
      print_dbg("ACMP2 < ACMPN2");
      print_dbg("\r\n");
    } 
#else
#error No board defined.       
#endif
  }

}
