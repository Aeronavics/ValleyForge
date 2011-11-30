/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief ACIFA header for AVR32 UC3.
 *
 * This file defines a useful set of functions for ACIFA on AVR UC3 devices.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR UC3
 * - Supported devices:  All AVR UC3 devices with ACIFA can be used.
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
 */
#ifndef _ACIFA_H_
#define _ACIFA_H_

#include <avr32/io.h>
#include "compiler.h"

//! Local Definition for Positive Inputs Comparator 0 Instance A used by the ACIFA
//! 
#define AVR32_ACIFA_AC0A_INSELP_AC0AP0                        0
#define AVR32_ACIFA_AC0A_INSELP_AC0AP1                        1
#define AVR32_ACIFA_AC0A_INSELP_DAC0_INT                      2

//! Local Definition for Negative Inputs Comparator 0 Instance A used by the ACIFA
//! 
#define AVR32_ACIFA_AC0A_INSELN_AC0AN0                        0
#define AVR32_ACIFA_AC0A_INSELN_AC0AN1                        1
#define AVR32_ACIFA_AC0A_INSELN_AC0BP0                        2
#define AVR32_ACIFA_AC0A_INSELN_AC0BP1                        3
#define AVR32_ACIFA_AC0A_INSELN_VDDANA_SCALED                 4
#define AVR32_ACIFA_AC0A_INSELN_DAC1_INT                      5

//! Local Definition for Positive Inputs Comparator 0 Instance B used by the ACIFA
//! 
#define AVR32_ACIFA_AC0B_INSELP_AC0AN0                        0
#define AVR32_ACIFA_AC0B_INSELP_AC0AN1                        1
#define AVR32_ACIFA_AC0B_INSELP_AC0BP0                        2
#define AVR32_ACIFA_AC0B_INSELP_AC0BP1                        3
#define AVR32_ACIFA_AC0B_INSELP_DAC0_INT                      4
#define AVR32_ACIFA_AC0B_INSELP_VDDANA_SCALED                 5

//! Local Definition for Negative Inputs Comparator 0 Instance B used by the ACIFA
//! 
#define AVR32_ACIFA_AC0B_INSELN_AC0BN0                        0
#define AVR32_ACIFA_AC0B_INSELN_AC0BN1                        1
#define AVR32_ACIFA_AC0B_INSELN_DAC1_INT                      2

//! Local Definition for Positive Inputs Comparator 1 Instance A used by the ACIFA
//! 
#define AVR32_ACIFA_AC1A_INSELP_AC1AP0                        0
#define AVR32_ACIFA_AC1A_INSELP_AC1AP1                        1
#define AVR32_ACIFA_AC1A_INSELP_DAC0_INT                      2

//! Local Definition for Negative Inputs Comparator 1 Instance A used by the ACIFA
//! 
#define AVR32_ACIFA_AC1A_INSELN_AC1AN0                        0
#define AVR32_ACIFA_AC0A_INSELN_AC1AN1                        1
#define AVR32_ACIFA_AC0A_INSELN_AC1BP0                        2
#define AVR32_ACIFA_AC0A_INSELN_AC1BP1                        3
#define AVR32_ACIFA_AC0A_INSELN_VDDANA_SCALED                 4
#define AVR32_ACIFA_AC0A_INSELN_DAC1_INT                      5

//! Local Definition for Positive Inputs Comparator 1 Instance B used by the ACIFA
//! 
#define AVR32_ACIFA_AC1B_INSELP_AC1AN0                        0
#define AVR32_ACIFA_AC0B_INSELP_AC1AN1                        1
#define AVR32_ACIFA_AC0B_INSELP_AC1BP0                        2
#define AVR32_ACIFA_AC0B_INSELP_AC1BP1                        3
#define AVR32_ACIFA_AC0B_INSELP_DAC0_INT                      4
#define AVR32_ACIFA_AC0B_INSELP_VDDANA_SCALED                 5

//! Local Definition for Negative Inputs Comparator 1 Instance B used by the ACIFA
//! 
#define AVR32_ACIFA_AC1B_INSELN_AC1BN0                        0
#define AVR32_ACIFA_AC0B_INSELN_AC1BN1                        1
#define AVR32_ACIFA_AC0B_INSELN_DAC1_INT                      2

/*! \name Comparator Selection
 */
//! @{
#define ACIFA_COMP_SELA   1
#define ACIFA_COMP_SELB   2
//! @}


/*! \name VCCSCALE Selection
 */
//! @{
#define ACIFA_VCCSCALE_SELA   1
#define ACIFA_VCCSCALE_SELB   2
//! @}

/*! \brief Configure ACIFA Normal Mode. Mandatory to call.
 *
 * \param *acifa     Base address of the ACIFA
 * \param comp_sel   Comparator Selection
 * \param input_p    Input Positive Selection
 * \param input_n    Input Negative Selection  
 * \param pb_hz      Periphal Bus frequency 
 */
extern void acifa_configure(volatile avr32_acifa_t * acifa,
                            U8 comp_sel, 
                            U8 input_p,
                            U8 input_n,
                            U32 pb_hz);

/*! \brief Configure ACIFA Window Mode. Mandatory to call.
 *
 * \param *acifa          Base address of the ACIFA
 * \param input_p         Input Positive Selection for window mode
 * \param input_n         Input Negative Selection for window mode 
 * \param common_input    Common Input Selection for window mode
 * \param pb_hz           Periphal Bus frequency 
 */
void acifa_configure_window( volatile avr32_acifa_t * acifa,  
                             U8 input_p,  
                             U8 input_n,
                             U8 common_input,
                             U32 pb_hz);

/*! \brief Start comparator in Normal Mode
 * \param *acifa        Base address of the ACIFA
 * \param comp_sel      Comparator Selection 
 */
extern void acifa_start(volatile avr32_acifa_t * acifa, 
                        U8 comp_sel);


/*! \brief Start comparator in Window Mode
 * \param *acifa        Base address of the ACIFA
 */
extern void acifa_start_window(volatile avr32_acifa_t * acifa);

/*! \brief Enable Output on comparator
 *  \param *acifa Base address of the ACIFA
 *  \param comp_sel      Comparator Selection 
 */
extern void acifa_enable_output(volatile avr32_acifa_t * acifa, 
                                U8 comp_sel);

/*! \brief Configure Hysteresis on comparator
 *  \param *acifa        Base address of the ACIFA
 *  \param comp_sel      Comparator Selection 
 *  \param level         Level On Hysteresis
 */
extern void acifa_configure_hysteresis(volatile avr32_acifa_t * acifa, 
                                      U8 comp_sel,
                                      U8 level);

/*! \brief Configure VCC Scale on comparator
 *  \param *acifa        Base address of the ACIFA
 *  \param vccscale_sel  VCC Scale Selection
 *  \param scale         Scale
 */
extern void acifa_configure_vccscale(volatile avr32_acifa_t * acifa, 
                                       U8 vccscale_sel,
                                       U8 scale);                                                         
                     
/*! \brief Return comparator A status
 *  \param *acifa Base address of the ACIFA
 *  return 1: ACA Input P is higher than Input N / 0: ACA Input P is Lower than Input N 
 */
extern int acifa_is_aca_inp_higher(volatile avr32_acifa_t *acifa);

/*! \brief Return comparator B status
 *  \param *acifa Base address of the ACIFA
 *  return 1: ACB Input P is higher than Input N / 0: ACB Input P is Lower than Input N 
 */
extern int acifa_is_acb_inp_higher(volatile avr32_acifa_t *acifa);

/*! \brief Return Window status
 *  \param *acifa Base address of the ACIFA
 *  return 1: Common Input Signal inside the window / 0: Common Input Signal outside the window 
 */
extern int acifa_is_ci_inside_window(volatile avr32_acifa_t *acifa);

/*! \brief Clear Flags
 * \param *acifa        Base address of the ACIFA
 * \param flag_mask     FLag Mask Value
 */
extern void acifa_clear_flags(volatile avr32_acifa_t * acifa, uint32_t flag_mask);

/*! \brief Enable AC Interrupt when Vinp>Vin
 * \param *acifa         Base address of the ACIFA
 *  \param comp_sel      Comparator Selection 
 */
extern void acifa_enable_interrupt_inp_higher(volatile avr32_acifa_t * acifa, U8 comp_sel);

/*! \brief Enable AC Interrupt when Vinp<Vin
 * \param *acifa         Base address of the ACIFA
 *  \param comp_sel      Comparator Selection 
 */
extern void acifa_enable_interrupt_inp_lower(volatile avr32_acifa_t * acifa, U8 comp_sel);

/*! \brief Enable AC Interrupt when a toggle of the comparator occurs
 * \param *acifa        Base address of the ACIFA
 *  \param comp_sel      Comparator Selection 
 */
extern void acifa_enable_interrupt_toggle(volatile avr32_acifa_t * acifa, U8 comp_sel);
/*! \brief Enable Interrupt Flags
 * \param *acifa        Base address of the ACIFA
 * \param flag_mask     FLag Mask Value
 */
void acifa_enable_interrupt(volatile avr32_acifa_t * acifa, uint32_t flag_mask);
#endif  // _ACIFA_H_
