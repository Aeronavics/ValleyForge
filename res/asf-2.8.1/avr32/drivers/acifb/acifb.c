/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief ACIFB software driver for AVR32 UC3.
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

#include <avr32/io.h>
#include "compiler.h"
#include "acifb.h"


#ifdef AVR32_ACIFB_202_H_INCLUDED
#define AVR32_ACIFB_CONF7_EVENP                                      17
#define AVR32_ACIFB_CONF7_EVENP_MASK                         0x00020000
#define AVR32_ACIFB_CONF7_EVENP_OFFSET                               17
#define AVR32_ACIFB_CONF7_EVENP_SIZE                                  1
#define AVR32_ACIFB_CONF7_EVENN                                      16
#define AVR32_ACIFB_CONF7_EVENN_MASK                         0x00010000
#define AVR32_ACIFB_CONF7_EVENN_OFFSET                               16
#define AVR32_ACIFB_CONF7_EVENN_SIZE                                  1
// These defines are missing or wrong in the toolchain header files acifb_202.h
#endif

void acifb_channels_setup(volatile avr32_acifb_t *acifb, const acifb_channel_t *ac_chan, int nb_chan)
{
  int i;
  for (i=0; i<nb_chan; i++)
  {
    // Apply the channel configuration.
    *(&(acifb->conf0) + ac_chan[i].ac_n) =
        ( ((ac_chan[i].filter_len << AVR32_ACIFB_CONF7_FLEN_OFFSET) & AVR32_ACIFB_CONF7_FLEN_MASK) |
          ((ac_chan[i].hysteresis_value << AVR32_ACIFB_CONF7_HYS_OFFSET) & AVR32_ACIFB_CONF7_HYS_MASK) |
          (((ac_chan[i].event_negative)?1:0) << AVR32_ACIFB_CONF7_EVENN_OFFSET) |
          (((ac_chan[i].event_positive)?1:0) << AVR32_ACIFB_CONF7_EVENP_OFFSET) |
          ((ac_chan[i].positive_input << AVR32_ACIFB_CONF7_INSELP_OFFSET) & AVR32_ACIFB_CONF7_INSELP_MASK) |
          ((ac_chan[i].negative_input << AVR32_ACIFB_CONF7_INSELN_OFFSET) & AVR32_ACIFB_CONF7_INSELN_MASK) |
          ((ac_chan[i].mode << AVR32_ACIFB_CONF7_MODE_OFFSET) & AVR32_ACIFB_CONF7_MODE_MASK) |
          ((ac_chan[i].interrupt_settings << AVR32_ACIFB_CONF7_IS_OFFSET) & AVR32_ACIFB_CONF7_IS_MASK) );
  }
}


void acifb_setup_and_enable(volatile avr32_acifb_t *acifb, const acifb_t *ac)
{
  acifb->ctrl = ( ((ac->sut << AVR32_ACIFB_SUT_OFFSET) & AVR32_ACIFB_SUT_MASK) |
                  ((ac->actest << AVR32_ACIFB_ACTEST_OFFSET) & AVR32_ACIFB_ACTEST_MASK) |
                  ((ac->eventen << AVR32_ACIFB_EVENTEN_OFFSET) & AVR32_ACIFB_EVENTEN_MASK) |
                  (1u << AVR32_ACIFB_EN_OFFSET) ); // Enable
}


void acifb_wait_channels_ready(volatile avr32_acifb_t *acifb, const int acrdy_mask)
{
  while((acifb->sr & acrdy_mask) != acrdy_mask);
}
