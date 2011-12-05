/**
 * \file
 *
 * \brief CDC Application Main functions
 *
 * Copyright (C) 2009 Atmel Corporation. All rights reserved.
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
#include "gpio.h"
#include "sysclk.h"
#include "sleepmgr.h"
#include "conf_usb.h"
#include "udd.h"
#include "udc.h"
#include "udi_cdc.h"
#include "ui.h"
#include "uart.h"

#define  MAIN_BUF_PATTERN_SIZE	(256)

static volatile bool main_b_cdc_enable = false;
static volatile bool main_b_com_open = false;

static void main_cdc_open(bool b_enable);

COMPILER_WORD_ALIGNED uint8_t buf_pattern[MAIN_BUF_PATTERN_SIZE];

/*! \brief Main function. Execution starts here.
 */
int main(void)
{	
	uint16_t i;
			
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	sysclk_init();
	board_init();
	ui_init();
	ui_powerdown();

	// Start USB stack to authorize VBus monitoring
	udc_start();

	if (!udc_include_vbus_monitoring()) {
		// VBUS monitoring is not available on this product
		// thereby VBUS has to be considered as present
		main_vbus_action(true);
	}
	// The main loop manages only the power mode
	// because the USB management is done by interrupt
	while (true) {

		sleepmgr_enter_sleep();
		
		if (main_b_cdc_enable) {
			if (ui_authorize_test()) {

				// Test Putc performance
				while(ui_authorize_test()) {
					udi_cdc_putc('A');
					udi_cdc_putc('t');
					udi_cdc_putc('m');
					udi_cdc_putc('e');
					udi_cdc_putc('l');
					udi_cdc_putc('.');
					udi_cdc_putc('\r');
					udi_cdc_putc('\n');
				}

				// Wait to start next step
				while(!ui_authorize_test());

				// Test Getc performance
				main_cdc_open(false);
				while(ui_authorize_test()) {
					if (udi_cdc_is_rx_ready()) {
						udi_cdc_getc();
					}
				}
				main_cdc_open(true);

				// Fill buffer with a pattern
				for (i=0; i<MAIN_BUF_PATTERN_SIZE; ) {
					buf_pattern[i++]='A';
					buf_pattern[i++]='t';
					buf_pattern[i++]='m';
					buf_pattern[i++]='e';
					buf_pattern[i++]='l';
					buf_pattern[i++]='.';
					buf_pattern[i++]='\r';
					buf_pattern[i++]='\n';
				}

				// Wait to start next step
				while(!ui_authorize_test());

				// Test Write buffer performance
				while(ui_authorize_test()) {
				 	udi_cdc_write_buf((int*)buf_pattern, MAIN_BUF_PATTERN_SIZE);
				}

				// Wait to start next step
				while(!ui_authorize_test());

				// Test Read Buffer performance
				main_cdc_open(false);
				while(ui_authorize_test()) {
					if (udi_cdc_is_rx_ready()) {
				 		udi_cdc_read_buf((int*)buf_pattern, MAIN_BUF_PATTERN_SIZE);
					}
				}
				main_cdc_open(true);
			}
		}
	}
}

void main_vbus_action(bool b_high)
{
	if (b_high) {
		// Attach USB Device
		udc_attach();
	} else {
		// VBUS not present
		udc_detach();
	}
}

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!main_b_cdc_enable)
		return;
	ui_process(udd_get_frame_number());
}

bool main_cdc_enable(void)
{
	main_b_cdc_enable = true;
	// Open port
	main_cdc_open(true);
	return true;
}

void main_cdc_disable(void)
{
	main_b_cdc_enable = false;
	// Close communication
	main_cdc_open(false);
}


void main_cdc_set_dtr(bool b_enable)
{
	if (b_enable) {
		ui_com_open();
	}else{
		ui_com_close();
	}
}

static void main_cdc_open(bool b_enable)
{
	if (b_enable && !main_b_com_open) {
		// Open communication
		main_b_com_open = true;
		uart_open();
	}
	if (!b_enable && main_b_com_open) {
		// Close communication
		main_b_com_open = false;
		uart_close();
	}
}


/**
 * \mainpage ASF USB Device CDC
 *
 * \section intro Introduction
 * This example shows how to implement a USB Device CDC
 * on AVR products with USB module.
 * The application note AVR4907 provides more information
 * about this implementation.
 *
 * \section desc Description of the Communication Device Class (CDC)
 * The Communication Device Class (CDC) is a general-purpose way to enable all
 * types of communications on the Universal Serial Bus (USB).
 * This class makes it possible to connect communication devices such as 
 * digital telephones or analog modems, as well as networking devices 
 * like ADSL or Cable modems.
 * While a CDC device enables the implementation of quite complex devices,
 * it can also be used as a very simple method for communication on the USB.
 * For example, a CDC device can appear as a virtual COM port, which greatly 
 * simplifies application development on the host side.
 *
 * \section startup Startup
 * The example is a bridge between a USART from the main MCU
 * and the USB CDC interface. In addition, the example allows to measure the maximum speed
 * of the solution (Device CDC & host application).
 *
 * In this exmaple, we will use a PC as a USB host:
 * it connects to the USB and to the USART board connector.
 * - Connect the USART peripheral to the USART interface of the board.
 * - Connect the application to a USB host (e.g. a PC) 
 *   with a mini-B (embedded side) to A (PC host side) cable.
 * The application will behave as a virtual COM (see Windows Device Manager).
 * - Open a hyperterminal on both COM ports (RS232 and Virtual COM)
 * - Select the same configuration for both COM ports up to 115200 baud.
 * - Type a character in one hyperterminal and it will echo in the other.
 *
 * \section test_performance Measure maximum rate
 * To measure the maximum rate under test mode:
 * - Connect the application to a USB host (e.g. a PC) 
 * - Run host application in reception
 *   Note: On Lunix O.S., it is recommended to disable echo, this allows the 
 *   highest tranfer rate.
 *         stty --file=/dev/ttyACM0 -echo
 *         cat /dev/ttyACM0 | pv -r > /dev/null
 * - Press test button to start transfer CDC to host via udi_cdc_putc()
 * - Release test button to stop test
 * - Press test button to start transfer host to CDC via udi_cdc_getc()
 * - Send data via host application
 * - Release test button to stop test
 * - Press test button to start transfer CDC to host via udi_cdc_write_buf()
 * - Release test button to stop test
 * - Press test button to start transfer host to CDC via udi_cdc_read_buf()
 * - Send data via host application
 * - Release test button to stop test
 *
 * \note
 * On the first connection of the board on the PC,
 * the operating system will detect a new peripheral:
 * - This will open a new hardware installation window.
 * - Choose "No, not this time" to connect to Windows Update for this installation
 * - click "Next"
 * - When requested to search the INF file, browse to the same folder of this main.c file.
 * - click "Next"
 *
 * \copydoc UI 
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB Device stack and CDC modules:
 *   <br>services/usb/
 *   <br>services/usb/udc/
 *   <br>services/usb/class/cdc/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *      <br>
 *    - uart_uc3.c,
 *      <br>implementation of RS232 bridge for uc3 parts
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (leds,buttons...)
 */
