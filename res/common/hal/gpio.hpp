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

// TODO - Probably need target specific options for settings such as open-drain.

// GPIO pin mode.
enum Gpio_mode {GPIO_INPUT, GPIO_OUTPUT};

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
		 * Gets run whenever the instance of class Gpio_pin goes out of scope.
		 *
		 * @param Nothing.
		 * @return Nothing.
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
		 * @return Zero for success, non-zero for failure.
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
		 * if (my_pin.read() == HIGH)
		 * {
		 * 	my_pin.write(LOW);
		 * } 
		 * @endcode
		 *
		 * @param  value	The state to set the GPIO pin to.
		 * @return Nothing.
		 */
		void write(Gpio_output_state value);
		
		// TODO - Is this true?  Does the pin automatically become an input?  If so, how do you configure pull-ups?

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
		 * @param  mode		Any number of interrupt types (RISING_EDGE, FALLING_EDGE, BLOCKING, NON_BLOCKING).
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return Zero for success, non-zero for failure.
		 */
		Gpio_interrupt_status enable_interrupt(Gpio_interrupt_mode mode, void (*func_pt)(void));
		
		/**
		 * Disable an interrupt for the pin.
		 *
		 * @param  Nothing.
		 * @return Zero for success, non-zero for failure.
		 */
		Gpio_interrupt_status disable_interrupt(void);
		
		/**
		 * Checks to see whether or not the GPIO pin implementation pointer is null or not. Use this after using gpio_pin_grab to see if the pin grab
		 * was successful or not.
		 * 
		 * @subsection Example
		 *
		 * @code
		 * Gpio_pin my_pin = Gpio_pin::grab(my_pin_address);
		 * if (my_pin.is_valid())
		 * {
		 * 	my_pin.write(HIGH);
		 * }
		 * @endcode
		 * 
		 * @param Nothing.
		 * @return True if this is a valid GPIO pin, false otherwise.
		 */
		bool is_valid(void);
		
		/**
		 * Creates a Gpio_pin instance for a specific GPIO pin.
		 *
		 * @subsection Example
		 *
		 * @code
		 * gpio_pin_address my_pin_address;
		 * my_pin_address.port = PORT_B;
		 * my_pin_address.pin = PIN_5;
		 *
		 * gpio_pin my_pin = gpio_pin::grab(my_pin_address);
		 * if (my_pin.is_valid())
		 * {
		 * 	my_pin.write(HIGH);
		 * }
		 * @endcode
		 *
		 * @param  address	Address of the GPIO pin.
		 * @return A Gpio_pin instance corresponding to the specified IO pin.
		 */
		static Gpio_pin grab(IO_pin_address address);

	private:
		// Functions.
		
		Gpio_pin(void);	// Poisoned.

		Gpio_pin(Gpio_pin_imp*);

		Gpio_pin operator =(Gpio_pin const&);	// Poisoned.

		// Fields.

		/*
		* Pointer to the target specific implementation of the GPIO pin.
		*/
		Gpio_pin_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__GPIO_H__*/

// ALL DONE.
