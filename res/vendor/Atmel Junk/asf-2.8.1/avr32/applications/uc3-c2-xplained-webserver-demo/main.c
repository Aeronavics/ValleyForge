/**
 * \file
 *
 * \brief AVR UC3-C2-Xplained Webserver Demo
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

/*! \mainpage
 * \section intro Introduction
 * This is the documentation for UC3-C2-Xplained Webserver demo running 
 * on the UC3-C2-Xplained development kit.
 * - Step 1: Plug a USB cable from the USB connector to one of the PC’s
 *   USB ports. This provide power and USB serial communication port.
 * - Step 2: Open a serial terminal PC application with serial configuration 
 *   (57600 Bps/8 bits/no stop bit)
 * - Step 3: Plug an ethernet cable between the ethernet connector of the 
 *   UC3-C2-Xplained board and the PC's ethernet card (DHCP Configuration should
 *   be enabled on PC). Once the IP adress is attributed, it is displayed on 
 *   the serial terminal PC 
 *   application.
 * - Step 4: Open a webbrowser and type the attributed IP address.
 * - Step 5: A webpage is then displayed and can light on/off the board leds.
 * \section files Main Files
 * - main.c: Main File;
 *
 *  \section MAC address config
 *  The board MAC address should be writen before running the program into the
 *  flash user page at addresses: 0x808001f0-0x808001f6; If the MAC address was 
 *  not written there before running the program, it will be written with the 
 *  default MAC address: 00-04-25-1C-A0-01.

 * \section compilinfo Compilation Information
 * This software is written for GNU GCC for AVR32 and for IAR Embedded Workbench
 * for Atmel AVR32. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All AVR32 AT32UC3C devices can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - UC3_C2_Xplained evaluation kit;
 * - CPU clock: 48 MHz;
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 */

// Environment include files.
#include <stdlib.h>
#include <string.h>

// Scheduler include files.
#include "FreeRTOS.h"
#include "task.h"

// Demo file headers.
#include "ethernet.h"
#include "netif/etharp.h"
#include "gpio.h"
#include "displayTask.h"
#include "sysclk.h"

// Priority definitions for most of the tasks in the demo application.
#define mainLED_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define mainETH_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define display_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )

/**
 * \fn     main
 * \brief  start the software here
 *         1) Configure system clock of the board.
 *         2) Start Display Task management.
 *         3) Start Ethernet Task management.
 *         4) Start FreeRTOS.
 * \return 0, which should never occur.
 * 
 */
int main( void )
{  
	// 1) Configure system clock.
	sysclk_init(); 

	// 2) Start Display Task management.
	vDisplay_Start(display_TASK_PRIORITY);
        
	// 3) Start Ethernet Task management.
	vStartEthernetTaskLauncher( configMAX_PRIORITIES );

	// 4) Start FreeRTOS.
	vTaskStartScheduler();

	/*
         * Will only reach here if there was insufficient memory to create the 
         * idle task.
         */
	return 0;
}
