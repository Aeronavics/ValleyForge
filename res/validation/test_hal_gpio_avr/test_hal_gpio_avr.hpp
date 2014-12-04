// Copyright (C) 2014  Unison Networks Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


/********************************************************************************************************************************
 *
 *  FILE:               test_hal_gpio_avr.hpp
 *
 *  SUB-SYSTEM:         HAL Validation
 *
 *  COMPONENT:          test_hal_gpio_avr
 *
 *  TARGET:             ATmega64C1
 *
 *  PLATFORM:           BareMetal
 *
 *  AUTHOR:             Ben O'Brien
 *
 *  DATE CREATED:       26-11-2014
 *
 *	This is the header file which matches test_hal_gpio_avr.cpp...
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __TEST_HAL_GPIO_AVR_H__
#define __TEST_HAL_GPIO_AVR_H__

// REQUIRED INTERFACE HEADER FILES.
#include "hal/hal.hpp"
#include "hal/gpio.hpp"

// IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// PUBLIC MACROS.

#define ERROR_POSITION_NO_ERORR -1
#define TEST_CURRENT_STATE 0

#define NUM_PINS 8
#define NUM_BUTTONS 8
#define NUM_LEDS 8


#if defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
	#define BUTTON_PORT PORT_C
	#define LED_PORT PORT_B
#elif defined(__AVR_AT90CAN128__)
	#define BUTTON_PORT PORT_C
	#define LED_PORT PORT_B
#elif defined(__AVR_ATmega2560__)
	#define LED_PORT PORT_C
	#define BUTTON_PORT PORT_B
#endif


enum program_state_t
{
	PROG_DEFAULT = 0,
	INTERRUPTS_ENABLED = 0x1,
};

// DECLARE PUBLIC GLOBAL VARIABLES.
volatile uint16_t current_state = PROG_DEFAULT;
bool interrupts_on = false;
// PUBLIC STATIC FUNCTION PROTOTYPES.


/**
 * ISR that attached to the button pins, and is active when interrupts are toggled on by the user.
 *
 * @param Nothing.
 * @return Nothing.
 */
void on_button_press(void);


/**
 * Displays an 8-bit number on the array of LEDs in Big-Endian form, where 1 is represented by light, and 0 is darkness.
 *
 * @param  number			The number to be displayed.
 * @param  display_LEDs		An array that holds references to each of the LED pins, making use of the Gpio_pin type
 * 							defined in gpio
 * @param  num_LEDs			The length of the display_LEDs array
 * @return Nothing.
 */
void display_number_as_binary(int8_t number, Gpio_pin** display_LEDs, uint8_t num_LEDs);


/**
 * Gets the current or previous state of the button.
 *
 * @param  button_number	The number of the button, from 0 to 7.
 * @param  index			The index is used to select the (n-index)th state, when n is the index of the current state (0).
 * @subsection Example
 *
 * @code
 * get_button_state(BUTTON_1, 1); //gets the value of the button before the most recent update to its state.
 * @endcode
 * 
 * @return Gpio_output_state (GPIO_O_LOW, GPIO_O_HIGH).
 */
int8_t get_button_state(uint8_t button_number, uint8_t index);
bool is_button_pressed(uint8_t button_number);
bool is_button_released(uint8_t button_number);
bool is_button_down(uint8_t button_number);

/**
 * Used to update the state of a given button
 *
 * @param  button_number
 * @return Nothing.
 */
int8_t update_button(uint8_t button_number);


/**
 * Used to update the state of an LED
 *
 * @param  led_number
 * @return Nothing.
 */
int8_t update_LED(uint8_t led_number);


/**
 * Sets the state of an LED, without updating the pin.
 *
 * @param  led_number
 * @subsection Example
 * 
 * @code - To turn on an LED
 * set_LED_state(1, GPIO_O_LOW);
 * update_LED(1);
 * @endcode
 * 
 * @return Nothing.
 */
int8_t set_LED_state(uint8_t led_number, int8_t state);


/**
 * Gets the current or previous state of the LED.
 *
 * @param  button_number	The number of the button, from 0 to 7.
 * @param  index			The index is used to select the (n-index)th state, when n is the index of the current state (0).
 * @subsection Example
 *
 * @code
 * get_button_state(BUTTON_1, 1); //gets the value of the button before the most recent update to its state.
 * @endcode
 * 
 * @return Gpio_output_state (GPIO_O_LOW, GPIO_O_HIGH).
 */
bool get_LED_state(uint8_t led_number, uint8_t index);


/**
 *
 * @param  nothing.
 * @return 
 */
int main(void);


#endif // __TEST_HAL_GPIO_AVR_H__

// ALL DONE.
