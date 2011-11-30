/**
 * \file
 *
 * \brief Display Usart Interface
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
#include <stdio.h>
#include "board.h"
#include "display.h"
#include "gpio.h"
#include "delay.h"
#include "stdio_usb.h"

//! Pointer to the module instance to use for stdio.
#if defined(__GNUC__) && defined(__AVR32__)
void (*ptr_get)(void volatile*,int*);
int (*ptr_put)(void volatile*,int);
volatile void *volatile stdio_base;
#endif

/*!
 * \brief Initialize Display function 
 *          - Initializa stdio interface using the USB CDC Interface,
 *          - Print startup message.
 * \param fcpu_hz CPU Frequency Value in Hz.
 */
void display_init(uint32_t fcpu_hz)
{

 	/* Start and attach USB CDC device interface for devices with
 	 * integrated USB interfaces.
 	 */
	stdio_usb_init(NULL);	

	// Specify that stdout and stdin should not be buffered.

#if defined(__GNUC__) && defined(__AVR32__)
	setbuf(stdout, NULL);	
#endif

	// Display default message.
	puts("\x1B[5;1H");
	puts("ATMEL  UC3_C2_Xplained \r\n");
	puts("lwIP with DHCP demo \r\n");
	puts("Not Connected \r\n");
}

/*!
 * \brief Display string message
 * \param str String input.
 */
void display_print(const char *str)
{
	puts(str);
	puts("\r\n");
}
