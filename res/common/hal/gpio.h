/********************************************************************************************************************************
 *
 *  FILE: 		gpio.h
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	7-12-2011
 *
 *	This is the header file which matches gpio.c.  Implements general IO operations for GPIO pins.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __GPIO_H__
#define __GPIO_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>


// Include the semaphore library that someone is gonna create.
#include "semaphore.h"

// Include the hal library.
#include "hal/hal.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

class gpio_pin_imp;

// DEFINE PUBLIC CLASSES.

enum gpio_mode {INPUT, OUTPUT};

enum gpio_output_state {O_LOW, O_HIGH, O_TOGGLE};

enum gpio_input_state {I_LOW, I_HIGH, I_ERROR=-1};

struct gpio_pin_address
{
	port_t port;
	pin_t pin;
};

class gpio_pin
{
	public:
		// Functions.

		/**

		 * Gets run whenever the instance of class gpio_pin goes out of scope.
		 * Vacates the semaphore, allowing the pin to be allocated elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~gpio_pin(void);
		
		/**
		 * Sets the pin to input or output. 
		 * 
		 * @param  mode	Set to INPUT or OUTPUT.
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_mode(gpio_mode mode);
				
		/**
		 * Read the value of the gpio pin and return it
		 *
		 * @param Nothing.
		 * @return LOW (0), HIGH (1), or ERROR (-1).
		 */
		gpio_input_state read(void);
		
		/**
		 * Writes the value provided to the pin
		 *
		 * @param  value	HIGH(1), LOW(0) or TOGGLE(2).
		 * @return Nothing.
		 */
		int8_t write(gpio_output_state value);
		
		/** 
		 * Initialise an interrupt for the associated pin in the specified mode
		 * and attach the ISR function pointer provided to the interrupt.
		 *
		 * @param  mode		Any number of interrupt types (RISING_EDGE, FALLING_EDGE, BLOCKING, NON_BLOCKING).
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return 0 for success, -1 for error.
		 */
		int8_t init_interrupt(uint8_t mode, void* func_pt(void));

		/**
		 * Initialise an interrupt for the associated pin.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void enable_interrupt(void);
		
		/**

		 * Disable an interrupt for the associated pin.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void disable_interrupt(void);
		
		/**
		 * Checks to see whether or not the GPIO pin implementation pointer is null or not.
		 *
		 * @param  Nothing.
		 * @return True if the implementation pointer is not NULL, false otherwise.
		 */
		bool is_valid(void);
		
		/** 
		 * Allows access to the GPIO pin to be relinquished and assumed elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request access to a gpio pin and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  gpio_pin_address	Address of the GPIO pin requested.
		 * @return A gpio_pin instance.
		 */
		static gpio_pin grab(gpio_pin_address);

	private:
		// Functions.
		
		gpio_pin(void);	// Poisoned.

		gpio_pin(gpio_pin_imp*);

		gpio_pin operator =(gpio_pin const&);	// Poisoned.

		// Fields.

		/**
		* Pointer to the machine specific implementation of the GPIO pin.
		*/
		gpio_pin_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__GPIO_H__*/

// ALL DONE.
