/**
 * \file
 *
 * \brief PWMA example driver for AVR32 UC3.
 *
 * This file provides an example for the PWMA on AVR32 UC3 devices.
 *
 * \page License
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
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

/**
 * \mainpage
 *
 * \section intro Introduction
 * This application provides an example usage of the PWMA module on UC3
 * products. This example shows how to configure a PWMA and output it on a
 * GPIO.
 *
 * <b>Operating mode</b>:\n Check the used PWMA pin with an oscilloscope, you
 * should see a PWM square wave with varying duty-cycle.
 * - On \b UC3-L0 Xplained, the pin is connected to the red color on the
 *   RGB-LED, showing a cycling fade-out effect.
 * - On \b UC3L-EK, the PWMA-pin is connected to LED0.
 *
 * \section files Main Files
 * - pwma.c: PWMA driver;
 * - pwma.h: PWMA driver header file;
 * - pwma_example.c: PWMA example application.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC for AVR32 and IAR Systems compiler
 * for AVR32. Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All AVR32 devices with a PWMA module can be used. This example has been
 * tested with the following setup:
 * - UC3-L0 Xplained
 * - UC3L-EK
 *
 * \section setupinfo Setup Information
 * CPU speed: <i>Internal 120MHz RC oscillator set to run at 15MHz</i>.
 *
 * \section contactinfo Contact Info
 * For more info about Atmel AVR32 visit
 * <A href="http://www.atmel.com/products/AVR32/" >Atmel AVR32</A>\n
 * Support and FAQ: http://support.atmel.no/
 */
#include <avr32/io.h>
#include "gpio.h"
#include "pwma.h"
#include "delay.h"
#include "genclk.h"
#include "sysclk.h"
#include "conf_pwma_example.h"

#if !defined(EXAMPLE_PWMA_PIN) || !defined(EXAMPLE_PWMA_FUNCTION) || \
	!defined(EXAMPLE_PWMA_CHANNEL_ID)
# error Example PWM configuration is missing or bad, check conf_pwma_example.h
#endif

/**
 * \brief Main function. Execution starts here.
 *
 * Sets up the PWM module and PWM output, and runs forever cycling through an
 * varying PWM duty cycle pattern.
 */
int main(void)
{
	struct genclk_config gcfg;
	uint8_t duty = 0;

	board_init();
	/**
	 * \note the call to sysclk_init() will disable all non-vital
	 * peripheral clocks, except for the peripheral clocks explicitly
	 * enabled in conf_clock.h.
	 */
	sysclk_init();

	/**
	 * Start generic clock 3 for the PWM module running at half the clock
	 * speed of the CPU clock.
	 */
	genclk_config_defaults(&gcfg, AVR32_PM_GCLK_GCLK3);
	genclk_config_set_source(&gcfg, GENCLK_SRC_CLK_CPU);
	genclk_config_set_divider(&gcfg, 2);
	genclk_enable(&gcfg, AVR32_PM_GCLK_GCLK3);

	/**
	 * Configure the PWM channel with a TOP of 255 and a starting duty
	 * cycle of 0.
	 */
	pwma_config_and_enable(&AVR32_PWMA,
			(1 << EXAMPLE_PWMA_CHANNEL_ID), 255, 0);

	/* Enable the PWMA output on the example PWM pin. */
	gpio_enable_module_pin(EXAMPLE_PWMA_PIN, EXAMPLE_PWMA_FUNCTION);

	/* Initialize the delay routine by providing the CPU clock speed. */
	delay_init(sysclk_get_cpu_hz());

	for (;;) {
		/**
		 * First set a new duty cycle value to the PWM channel, then
		 * increment the duty cycle by one. Since the duty variable is
		 * an uint8_t type it will wrap around at 255 and go to zero.
		 */
		pwma_set_channels_value(&AVR32_PWMA,
				(1 << EXAMPLE_PWMA_CHANNEL_ID), duty++);

		/**
		 * Busy-wait the CPU for a short instance so that the PWM duty
		 * cycle change is visual on the LED wired to the PWMA channel.
		 */
		delay_ms(10);
	}
}
