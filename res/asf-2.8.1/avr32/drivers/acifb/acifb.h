/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief ACIFB software driver interface for AVR32 UC3.
 *
 * This file defines a useful set of functions for the ACIFB module on AVR32 devices.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with an ACIFB module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
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

#ifndef _ACIFB_H_
#define _ACIFB_H_

#include <avr32/io.h>
#include "compiler.h"


//! AC channel configuration
typedef struct
{
  //! Filter length
  char filter_len;
  //! Hysteresis value
  char hysteresis_value;
  //! Output event when ACOUT is zero?
  bool event_negative;
  //! Output event when ACOUT is one?
  bool event_positive;
  //! Set the positive input
  enum
  {
    PI_ACP,
  } positive_input;
  //! Set the negative input
  enum
  {
    NI_ACN,
    NI_ACREFN
  } negative_input;
  //! Set the comparator mode
  enum
  {
    MODE_OFF,
    MODE_CONTINUOUS,
    MODE_USER_TRIGGERED,
    MODE_EVENT_TRIGGERED
  } mode;
  //! Interrupt settings
  enum
  {
    IS_VINP_GT_VINN,
    IS_VINP_LT_VINN,
    IS_OUTPUT_TGL,
    IS_COMP_DONE
  } interrupt_settings;
  //! Analog comparator number
  int ac_n;
} acifb_channel_t;

//! ACIFB configuration
typedef struct
{
  //! Startup time (such that AC startup time = SUT/Fgclk)
  unsigned int sut;
  //! Test mode
  enum
  {
    TESTMODE_OFF,
    TESTMODE_ON
  } actest;
  //! Peripheral Event Trigger Enable
  bool eventen;
} acifb_t;

/*! \brief Configure a set of AC channels in normal mode
 *
 * \param acifb Base address of the ACIFB
 * \param ac_chan Array of channels configuration [INPUT]
 * \param nb_chan The size of the ac_chan[] array [INPUT]
 *
 */
void acifb_channels_setup(volatile avr32_acifb_t *acifb, const acifb_channel_t *ac_chan, int nb_chan);

/*! \brief Configure and enable the ACIFB module
 *
 * \param acifb Base address of the ACIFB
 * \param ac ACIFB configuration [INPUT]
 *
 */
void acifb_setup_and_enable(volatile avr32_acifb_t *acifb, const acifb_t *ac);

/*! \brief Wait for channels to be ready
 *
 * \param acifb Base address of the ACIFB
 * \param acrdy_mask Mask of several AVR32_ACIFB_SR_ACRDYn_MASK [INPUT]
 *
 * \warning the wait is not timed-out, i.e. an infinite loop is possible in this function.
 */
void acifb_wait_channels_ready(volatile avr32_acifb_t *acifb, const int acrdy_mask);

#endif  // _ACIFB_H_
