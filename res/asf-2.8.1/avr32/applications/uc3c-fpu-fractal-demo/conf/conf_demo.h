/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief UC3C-EK FPU demo configuration file.
 *
 *
 * - Compiler:           IAR EWAVR32 for AVR32
 * - Supported devices:  All AVR32 with a FPU.
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
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. ATMEL grants developer a non-exclusive, limited license to use the Software
 * as a development platform solely in connection with an Atmel AVR product
 * ("Atmel Product").
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 */

#ifndef _CONF_DEMO_H_
#define _CONF_DEMO_H_

#include "board.h"
#include "conf_et024006dhu.h"

/*! \name System Clock Frequencies
 */
//! @{
#define FMCK_HZ   60000000
#define FCPU_HZ   FMCK_HZ
#define FHSB_HZ   FCPU_HZ
#define FPBA_HZ   FMCK_HZ
#define FPBB_HZ   FMCK_HZ
//! @}

#define OFFSET_DISPLAY  16
// LCD Half of width
#define WIDTH     160 
// LCD height
#define HEIGHT    240  


// Delay to display one point without FPU optimization
#define DELAY_US  5130 

#endif //_CONF_DEMO_H_
