/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief STK600 board initialization.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR
 * - Supported devices:  All AVR UC3 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

/* Copyright (c) 2010 Atmel Corporation. All rights reserved.
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


#include "compiler.h"
#include "stk600_rcuc3l0.h"
#include "conf_board.h"
#include "gpio.h"
#include "board.h"

void board_init(void)
{
#if defined (CONF_BOARD_AT45DBX)
	//DF initialization if required by the application
#endif

	// Configure the pins connected to LEDs as output and set their default
	// initial state to high (LEDs off).
	gpio_configure_pin(LED0_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED1_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED2_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED3_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED4_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED5_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED6_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(LED7_GPIO, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);

	// Configure the pin connected to the WAKE button as input.
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW0, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW1, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW2, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW3, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW4, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW5, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW6, GPIO_DIR_INPUT);
	gpio_configure_pin(GPIO_PUSH_BUTTON_SW7, GPIO_DIR_INPUT);
}
