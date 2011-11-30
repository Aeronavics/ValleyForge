/**
 * \file
 *
 * \brief Common Sensor Service Compass Calibration Example
 *
 * \mainpage
 *
 * \section intro Introduction
 *
 * This application performs a multi-step manual calibration on a compass
 * (magnetometer) sensor device.  The device must be physically manipulated 
 * during the calibration process, between individual steps.  The user 
 * presses the button on the processor board to move to the next calibration 
 * step.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/avr">Atmel AVR</A>.\n
 * Support and FAQ: http://support.atmel.no/
 *
 * \section License
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

#include <stdio.h>

#include <board.h>
#include <led.h>

#include <sensors/sensor.h>


// Switch and LED definitions

#if UC3
#  define SWITCH_PRESSED  (gpio_get_pin_value (GPIO_PUSH_BUTTON_0) ==     \
				           GPIO_PUSH_BUTTON_0_PRESSED)
#elif XMEGA
#  define SWITCH_PRESSED  (ioport_get_value (GPIO_PUSH_BUTTON_0) == false)
#endif

#if (BOARD==UC3_L0_XPLAINED)
#  define NUM_BLINK_LEDS (4)
#  define ALL_LEDS       (LED1 | LED2 | LED3 | LED4)   
									// don't blink LED0 (shared GPIO)
#  define PROMPT_LED     LED4       // blink while waiting for user input
   static const uint32_t led_array[NUM_BLINK_LEDS] = {LED1, LED2, LED3, LED4};

#else
#  define NUM_BLINK_LEDS   (4)
#  define ALL_LEDS         (LED0 | LED1 | LED2 | LED3)
#  define PROMPT_LED       LED0     // blink while waiting for user input
   static const uint32_t led_array[NUM_BLINK_LEDS] = {LED0, LED1, LED2, LED3};

#endif

#define LOOP_DELAY_MSEC 100         // main loop delay value (msec)
#define BLINK_DELAY     0xF000      // prompt blink delay loop count


void prompt_user(char *prompt_string);

/*! \brief User prompt routine
 *
 * This routine prompts the user to press the button and then waits
 * for him to do so.
 *
 * \return  Nothing.
 */
void prompt_user(char *prompt_string)
{
	volatile int     delay;

	// Output prompt string

	printf("%s\r\n", prompt_string);

	// Wait for user to push button before continuing

	LED_Off(ALL_LEDS);                  // turn all LED's off

	while ( ! SWITCH_PRESSED) {

		// Just blink LED until button is pushed

		LED_Toggle(PROMPT_LED);
		
		for (delay = 0; delay < BLINK_DELAY; delay++)
			{;}                         // do nothing
	}

	LED_Off(PROMPT_LED);               // leave LED off 

	while (SWITCH_PRESSED)
		{;}                             // wait until button is released

	return;
}

/*! \brief Compass / magnetometer calibration application
 *
 * This application illustrates the use of the sensor_calibrate() function
 * for compass/magnetometer calibration.  It prompts the user (via serial 
 * output) to manipulate the sensor board and press a button to continue.
 *
 * The calibration process is used to correct for fixed magnetic forces 
 * present on the board where the compass is mounted.  If uncorrected, these 
 * fixed forces will prevent accurate measurement of the actual external 
 * magnetic forces (e.g. magnetic North).
 *
 * The calibration sequence requires three steps.  During each step, the
 * board is placed in a specific orientation, and the user presses the button
 * on the board to trigger a compass sensor reading.
 *
 * The three orientations are:
 *   -#  Board lying flat (on a table, for example).
 *   -#  Board rotated 180 degrees (end-for-end), still lying flat.
 *   -#  Board flipped (inverted) so that the opposite side is facing up.
 *
 * After Step 3 is completed, the calibration values for the sensor are
 * calculated and are written to non-volatile (flash) memory on the
 * microcontroller.  These values will continue to be used for future
 * compass heading readings.
 *
 * \return  Nothing.
 */
int main(void)
{
	sensor_t        compass_dev;    // compass/magnetometer device
	sensor_data_t   compass_data;   // compass data
	int             led_num = 0;


	// Initialize hardware & sensor interfaces

	sensor_platform_init();

	LED_On(ALL_LEDS);              // turn all LED's on


	// Wait for user to press button to start

	prompt_user("Press button to start");       // text might not be seen

	// Attach descriptor and initialize the compass device

	sensor_attach(&compass_dev, SENSOR_TYPE_COMPASS, 0, 0);

	// Set sensor data output formats (for display after calibration complete)

	compass_data.scaled = true;


	// Perform calibration sequence

	// Step 1
	prompt_user("Lay board flat & press button");
	(void) sensor_calibrate(&compass_dev, MANUAL_CALIBRATE, 1, NULL);     

	// Step 2
	prompt_user("Rotate 180 degrees & press button");
	(void) sensor_calibrate(&compass_dev, MANUAL_CALIBRATE, 2, NULL);

	// Step 3
	prompt_user("Flip board & press button");
	if ( sensor_calibrate(&compass_dev, MANUAL_CALIBRATE, 3, NULL) != true) {
		if (compass_dev.err == SENSOR_ERR_IO) {
			printf ("Calibration failure: write error\n\r");
		} else {
			printf ("Unknown error while calibrating device\n\r");
		}
		return -1;		// error exit
	}

		
	/* Once the calibration is complete, the magnetic heading is continuously
	 * calculated and displayed.
	 */

	while (true) {

		// Change LED display

		LED_Toggle(led_array [led_num++]);
		if (led_num >= NUM_BLINK_LEDS)
			led_num = 0;


		// Sample compass and display heading values

		sensor_get_heading(&compass_dev,  &compass_data);

		printf("Direction = %d, Inclination = %d, Strength = %d uT\r\n", 
				(int) compass_data.heading.direction, 
				(int) compass_data.heading.inclination,
				(int) compass_data.heading.strength);
		
		mdelay(LOOP_DELAY_MSEC);
	}

	return 0;
}
