// Copyright (C) 2011  Unison Networks Ltd
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

/**
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file
 *  Provides functionality for writing to and reading from individual GPIO pins.
 * 
 *  @author 		Edwin Hayes
 *
 *  @date		7-12-2011
 *
 *  @brief 
 *  A class that abstracts GPIO peripherals. Each instance allows control of a single GPIO pin.
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 * 
 *  @section Example
 *  This code shows configuring a GPIO pin for both input and output, as well as configuring a edge triggered interrupt on a GPIO input.
 *
 *  @code
 *  #include "hal/gpio.hpp"
 *
 *  int main(void)
 *  {
 *      gpio_pin_address my_pin_address;
 *      my_pin_address.port = PORT_B;
 *      my_pin_address.pin = PIN_5;
 *
 *      gpio_pin my_pin = gpio_pin::grab(my_pin_address);
 * 	my_pin.set_mode(OUTPUT);
 * 	my_pin.write(HIGH);
 * 	my_pin.set_mode(INPUT);
 * 	if (my_pin.read() == HIGH)
 * 	{
 *          my_pin.enable_interrupt(RISING_EDGE, &myISR);
 * 	}
 *  }
 * 
 *  void myISR()
 *  {
 *  	do_something();
 *  }
 *  @endcode
 *
 */

// Only include this header file once.
#ifndef __GPIO_H__
#define __GPIO_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal/hal.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

typedef void (*voidFuncPtr)(void);

/* Available GPIO pin modes are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *	enum Gpio_mode {GPIO_INPUT, GPIO_INPUT_PU, GPIO_OUTPUT, GPIO_OUTPUT_OD};
 *
 */

// GPIO IO pin state.
enum Gpio_output_state {GPIO_O_LOW, GPIO_O_HIGH, GPIO_O_TOGGLE, GPIO_O_ERROR = -1};
enum Gpio_input_state {GPIO_I_LOW, GPIO_I_HIGH, GPIO_I_ERROR = -1};

// GPIO IO operation status.
enum Gpio_io_status {GPIO_SUCCESS, GPIO_ERROR};

// GPIO interrupt modes.
enum Gpio_interrupt_mode {GPIO_INT_LOW_LEVEL, GPIO_INT_ANY_EDGE, GPIO_INT_FALLING_EDGE, GPIO_INT_RISING_EDGE};

// GPIO interrupt configuration status.
enum Gpio_interrupt_status {GPIO_INT_SUCCESS, GPIO_INT_ALREADY_DONE, GPIO_INT_ALREADY_TAKEN = -1, GPIO_INT_OUT_OF_RANGE = -2};

// FORWARD DEFINE PRIVATE PROTOTYPES.

class Gpio_pin_imp;

// DEFINE PUBLIC CLASSES.

/**
 * @class
 * Abstracts a single GPIO pin, allowing control of IO functions.  GPIO pins can generally be configured as both input and output devices, and may support interrupt triggering,
 * configurable pull-ups, or other more complicated functionality. 
 * 
 */
class Gpio_pin
{
	public:
		// Functions.

		/**
		 * Creates a Gpio_pin instance for a specific GPIO pin.
		 *
		 * @subsection Example
		 *
		 * @code
		 * IO_pin_address my_pin_address;
		 * my_pin_address.port = PORT_B;
		 * my_pin_address.pin = PIN_5;
		 *
		 * Gpio_pin mypin = Gpio_pin(my_pin_address);
		 * @endcode
		 *
		 * @param	address	Address of the GPIO pin.
		 * @return	A Gpio_pin instance corresponding to the specified IO pin.
		 */
		 Gpio_pin(IO_pin_address address);

		/**
		 * Called when Gpio_pin instance goes out of scope
		 */
		~Gpio_pin(void);
		
		/**
		 * Sets the pin to an input or output.
		 *
		 * @subsection	Example
		 *
		 * @code
		 * set_mode(INPUT); 
		 * @endcode
		 *
		 * @param  mode 	Set to INPUT or OUTPUT.
		 * @return Return code representing whether operation was successful
		 * 
		 */
		Gpio_io_status set_mode(Gpio_mode mode);
				
		/**
		 * Reads the value of the GPIO pin and returns it.
		 * 
		 * @subsection Example
		 *
		 * @code
		 * if (my_pin.read() == GPIO_I_HIGH)
		 * {
		 * 	my_pin.write(GPIO_O_LOW);
		 * }
		 * @endcode
		 * 
		 * @param Nothing.
		 * @return The current state of the IO pin.
		 */
		Gpio_input_state read(void);
		
		/**
		 * Writes the value provided to the pin.
		 * 
		 * @subsection Example
		 *
		 * @code
		 * if (my_pin.read() == GPIO_O_HIGH)
		 * {
		 * 	my_pin.write(GPIO_O_LOW);
		 * } 
		 * @endcode
		 *
		 * @param  value	The state to set the GPIO pin to.
		 * @return Return code representing whether operation was successful
		 */
		Gpio_io_status write(Gpio_output_state value);

		/** 
		 * Initialise an interrupt for the pin in the specified mode and attach the specified function as the corresponding ISR.
		 *
		 * NOTE - Calling this function automatically sets the pin to an input.
		 * 
		 * @subsection Example
		 *
		 * @code
		 * if (my_pin.enable_interrupt(GPIO_INT_RISING_EDGE, &myISR) == GPIO_INT_SUCCESS)
		 * {
		 * 	runMyThings();
		 * }
		 * else
		 * {
		 * 	giveUp();
		 * }
		 * @endcode
		 *
		 * @param  mode		Any number of interrupt types (GPIO_INT_LOW_LEVEL, GPIO_INT_ANY_EDGE, GPIO_INT_FALLING_EDGE, GPIO_INT_RISING_EDGE).
 		 * @param  callback	Pointer to ISR function that is to be attached to the interrupt.
		 * @return Return code representing whether operation was successful
		 */
		Gpio_interrupt_status enable_interrupt(Gpio_interrupt_mode mode, IsrHandler callback);
		
		/**
		 * Disable an interrupt for the pin.
		 *
		 * @param  Nothing.
		 * @return Return code representing whether operation was successful
		 */
		Gpio_interrupt_status disable_interrupt(void);

	private:
		// Functions.
		
		Gpio_pin(void);	// Poisoned.

		Gpio_pin(Gpio_pin_imp*);

		Gpio_pin operator =(Gpio_pin const&);	// Poisoned.

		// Fields.

		// Pointer to the target specific implementation of the GPIO pin.
		Gpio_pin_imp* imp;
		
		// Address of the GPIO pin this instance interfaces
		IO_pin_address pin_address;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__GPIO_H__*/

// ALL DONE.
