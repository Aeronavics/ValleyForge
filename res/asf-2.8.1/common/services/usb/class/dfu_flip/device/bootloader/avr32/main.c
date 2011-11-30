/**
 * \file
 *
 * \brief Main functions
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

#include "compiler.h"
#include "preprocessor.h"
#include "board.h"
#include "conf_usb.h"
#include "udd.h"
#include "udc.h"
#include "udi_dfu_atmel.h"
#include "isp.h"
#include "sysclk_auto.h"

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	cpu_irq_enable();

	sysclk_auto_init();

	// Start USB stack to authorize VBus monitoring
	udc_start();

	if (!udc_include_vbus_monitoring()) {
		// VBUS monitoring is not available on this product
		// thereby VBUS has to be considered as present
		main_vbus_action(true);
	}

	while (true) {
	}
}

void main_vbus_action(bool b_high)
{
	if (b_high) {
		// Attach USB Device
		udc_attach();
	}else{
		// Detach USB Device
		udc_detach();
	}
}


/**
 * \mainpage ASF USB Device DFU
 *
 * \section intro Introduction
 * This application is the official Atmel USB DFU bootloader for AT32UC3.
 *
 * The guide of this bootloader is proposed in the following application note
 * "AVR32806-AVR UC3 USB DFU Bootloader version 1.1.0 and higher".
 *
 * \section files Application Files
 * The specific files of application are:
 * - main.c: the main file to start clock and USB DFU Device.
 * - sysclk_auto.c: specific system clock management to support automaticaly
 * detection of external oscillator
 * - intc.c: specific INTC driver optimized to save code
 * - specific linker script to store bootloader @0 instead of @0x2000.
 */


