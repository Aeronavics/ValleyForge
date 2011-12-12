/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief AVR32 UC3 Control Panel light sensor interface.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices can be used.
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

#ifndef __S_LIGHT_H__
#define __S_LIGHT_H__

#include "compiler.h"

//_____ M A C R O S ________________________________________________________



//_____ D E C L A R A T I O N S ____________________________________________

/*!
 *  \brief Get the current light sensor value.
 *
 *  \param buf char buffer in which the light sensor value is stored.
 *  \param result returns the light sensor value.
 *
 *  \return true upon success, false if error.
 */
bool b_light_get_value( char* buf, U32* result );

#endif // __S_LIGHT_H__