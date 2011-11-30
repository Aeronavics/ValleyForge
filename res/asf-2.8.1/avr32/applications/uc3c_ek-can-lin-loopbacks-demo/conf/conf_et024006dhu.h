/**
 * \file
 *
 * \brief AVR UC3 Display ET024006DHU Configuration File
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
#ifndef _CONF_ET024006DHU_H_
#define _CONF_ET024006DHU_H_

#include "compiler.h"
#include "board.h"

/*! \brief Interface configuration 
 *
 * Currently only EBI mode supported
 */
#define ET024006_IFACE_MODE       ET024006_IFACE_MODE_EBI

#if BOARD == EVK1105

	#ifdef EVK1105_REV3

		/*! \brief address used to write to the index register 
		 * (or read device status 
		 */
		#define ET024006_CMD_ADDR     ((volatile unsigned short int *) AVR32_EBI_CS2_ADDRESS)

		/*! \brief address used to read/write from/to registers or RAM 
		 *
		 * The select signal is connected to address line 19 and because of that we
		 * have an offset of 0x80000 in the rev3 version.
		 */
		#define ET024006_PARAM_ADDR   ((volatile unsigned short int *) (AVR32_EBI_CS2_ADDRESS + 0x00080000))

	#else

		/*! \brief address used to write to the index register 
		 * (or read device status 
		 */
		#define ET024006_CMD_ADDR     ((volatile unsigned short int *) AVR32_EBI_CS0_ADDRESS)


		/*! \brief address used to read/write from/to registers or RAM 
		 *
		 * On the other boards we have the select signal connected to address line
		 * 21 and this implies an address offset of 0x200000.
		 */
		#define ET024006_PARAM_ADDR   ((volatile unsigned short int *) (AVR32_EBI_CS0_ADDRESS + 0x00200000))

	#endif // _EVK1105_REV3

#elif BOARD == UC3C_EK
	/*! \brief address used to write to the index register 
	 * (or read device status 
	 */
	#define ET024006_CMD_ADDR     ((volatile unsigned short int *) AVR32_EBI_CS0_ADDRESS)


	/*! \brief address used to read/write from/to registers or RAM 
	 *
	 * On the other boards we have the select signal connected to address line
	 * 22 and this implies an address offset of 0x400000.
	 */
	#define ET024006_PARAM_ADDR   ((volatile unsigned short int *) (AVR32_EBI_CS0_ADDRESS + 0x00400000))

#elif BOARD == EVK1104

	/*! \brief address used to write to the index register 
	 * (or read device status 
	 */
	#define ET024006_CMD_ADDR     ((volatile unsigned short int *) AVR32_EBI_CS0_ADDRESS)


	/*! \brief address used to read/write from/to registers or RAM 
	 *
	 * On the other boards we have the select signal connected to address line
	 * 21 and this implies an address offset of 0x200000.
	 */
	#define ET024006_PARAM_ADDR   ((volatile unsigned short int *) (AVR32_EBI_CS0_ADDRESS + 0x00200000))

#endif 

#endif // _CONF_ET024006DHU_H_
