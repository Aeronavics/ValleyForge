/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file ******************************************************************
 *
 * \brief Management of the USB device CDC task.
 *
 * This file manages the USB device CDC task.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices with a USB module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ***************************************************************************/

/* Copyright (c) 2009 - 2011 Atmel Corporation. All rights reserved.
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

//_____  I N C L U D E S ___________________________________________________

#include "usart.h"

#include "conf_usb.h"
#include "power_clocks_lib.h"
#include "print_funcs.h"
#include "cdc_example.h"


#if USB_DEVICE_FEATURE == true


#include "usb_drv.h"
#include "gpio.h"
#include "intc.h"
#include "usb_descriptors.h"
#include "usb_standard_request.h"
#include "device_cdc_task.h"
#include "uart_usb_lib.h"
#include "cycle_counter.h"
#include "fifo.h"


//_____ M A C R O S ________________________________________________________


//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________

static volatile U16  sof_cnt;

extern pcl_freq_param_t pcl_freq_param;

#define USART_IRQ           DBG_USART_IRQ
#define USART_RX_BUFFER     64 // Unit is in characters.

static fifo_desc_t   fifo_desc_usart;
static uint8_t       fifo_rx[USART_RX_BUFFER];


#if (defined __GNUC__) && (defined __AVR32__)
	__attribute__((__interrupt__))
#elif (defined __ICCAVR32__)
	__interrupt
#endif
static void int_handler_usart(void)
{
	if (DBG_USART->csr & AVR32_USART_RXRDY_MASK) {
		U8 i, status;
		i = (DBG_USART->rhr & AVR32_USART_RHR_RXCHR_MASK) >> AVR32_USART_RHR_RXCHR_OFFSET;
		status = fifo_push_uint8(&fifo_desc_usart, i);
		if (status == FIFO_ERROR_OVERFLOW) {
			// error
			gpio_clr_gpio_pin(AVR32_PIN_PA20);
			gpio_clr_gpio_pin(AVR32_PIN_PA21);
		}
	}
}



//!
//! @brief This function initializes the hardware/software resources
//! required for device CDC task.
//!
void device_cdc_task_init(void)
{
	sof_cnt   =0 ;
	uart_usb_init();

	fifo_init(&fifo_desc_usart, &fifo_rx, USART_RX_BUFFER);

	// Register the USART interrupt handler to the interrupt controller.
	// Highest priority is required for the USART, since we do not want to loose
	// any characters.
	Disable_global_interrupt();
	INTC_register_interrupt(&int_handler_usart, USART_IRQ, AVR32_INTC_INT3);
	Enable_global_interrupt();

	// Clear all leds.
	gpio_set_gpio_pin(AVR32_PIN_PA20);
	gpio_set_gpio_pin(AVR32_PIN_PA21);

#if USB_HOST_FEATURE == true
	// If both device and host features are enabled, check if device mode is engaged
	// (accessing the USB registers of a non-engaged mode, even with load operations,
	// may corrupt USB FIFO data).
	if (Is_usb_device())
#endif  // USB_HOST_FEATURE == true
		Usb_enable_sof_interrupt();
}


//!
//! @brief Entry point of the device CDC task management
//!
void device_cdc_task(void)
{
	U8 c;
	int status;
	static bool b_startup=true;
	static U8   startup_state=0;

	if (Is_usb_vbus_low()) {
		U32 i;
		volatile avr32_pm_t *pm = &AVR32_PM;
		gpio_set_gpio_pin(AVR32_PIN_PA20);
		gpio_set_gpio_pin(AVR32_PIN_PA21);
		for (i=0 ; i<2 ; i++) {
			gpio_tgl_gpio_pin(AVR32_PIN_PA20);
			cpu_delay_ms(100, pcl_freq_param.cpu_f);
		}

		pm->AWEN.usb_waken = 1;
		SLEEP(AVR32_PM_SMODE_STOP);
		pm->AWEN.usb_waken = 0;

		b_startup = true;
		startup_state = 0;

		for (i=0 ; i<2 ; i++) {
			gpio_tgl_gpio_pin(AVR32_PIN_PA21);
			cpu_delay_ms(100, pcl_freq_param.cpu_f);
		}
	}

	// First, check the device enumeration state
	if (!Is_device_enumerated()) return;

	if (b_startup) {
		if (startup_state == 0) {
			// Initialize usart comm
			init_dbg_rs232(FOSC0);
			gpio_enable_pin_pull_up(DBG_USART_RX_PIN);

			gpio_clr_gpio_pin(AVR32_PIN_PA20);
		}
		else if (startup_state == 1) gpio_clr_gpio_pin(AVR32_PIN_PA21);
		else if (startup_state == 2) gpio_set_gpio_pin(AVR32_PIN_PA20);
		else if (startup_state == 3) gpio_set_gpio_pin(AVR32_PIN_PA21);
		else if (startup_state == 4) gpio_clr_gpio_pin(AVR32_PIN_PA20);
		else if (startup_state == 5) gpio_clr_gpio_pin(AVR32_PIN_PA21);
		else if (startup_state == 6) gpio_set_gpio_pin(AVR32_PIN_PA20);
		else if (startup_state == 7) gpio_set_gpio_pin(AVR32_PIN_PA21);
		else if (startup_state == 8) b_startup=false;
		startup_state++;
		cpu_delay_ms(100, FOSC0);
	}

	if (sof_cnt >= NB_MS_BEFORE_FLUSH) { //Flush buffer in Timeout
		sof_cnt=0;
		uart_usb_flush();
	}

	if (fifo_get_used_size(&fifo_desc_usart)) { // Something on USART ?
		if (uart_usb_tx_ready()) { // "USART"-USB free ?
			status = fifo_pull_uint8(&fifo_desc_usart, &c);
			if (status == FIFO_OK) {
				uart_usb_putchar(c); // Loop back, USART to USB
				gpio_tgl_gpio_pin(AVR32_PIN_PA20);
			}
		}
	}

	if (uart_usb_test_hit()) { // Something received from the USB ?
		if (usart_tx_ready(DBG_USART)) { // USART free ?
			c = uart_usb_getchar();
			usart_write_char(DBG_USART, c); // loop back USB to USART
			gpio_tgl_gpio_pin(AVR32_PIN_PA21);
		}
	}
}


//!
//! @brief usb_sof_action
//!
//! This function increments the sof_cnt counter each time
//! the USB Start-of-Frame interrupt subroutine is executed (1 ms).
//! Useful to manage time delays
//!
void usb_sof_action(void)
{
	sof_cnt++;
}

#endif  // USB_DEVICE_FEATURE == true
