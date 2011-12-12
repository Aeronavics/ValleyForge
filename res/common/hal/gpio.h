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
 *	This is the header file which matches gpio.c. Provides general IO functionality for GPIO pins.
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

// Include the common HAL stuff.
#include "hal.h"

// FORWARD DEFINE PRIVATE TYPES.

class gpio_pin_imp;	// Not defined here.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

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
		 * Gets run whenever the instance of the class goes out of scope.
		 * Vacates the semaphore, allowing the pin to be allocated elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~gpio_pin(void);
		
		/**
		 * Sets the pin to input or output. 
		 * 
		 * @param  mode set to INPUT or OUTPUT
		 * @return 0 for success, -1 for error
		 */
		uint8_t set_mode(gpio_mode mode);
				
		/**
		 * Reads the value of the GPIO pin and returns it.
		 *
		 * @param Nothing.
		 * @return LOW (0), HIGH (1), or ERROR (-1)
		 */
		gpio_input_state read(void);
		
		/**
		 * Writes the value provided to the GPIO pin.
		 *
		 * @param  value	HIGH(1), LOW(0) or TOGGLE(2) 
		 * @return Nothing.
		 */
		void write(gpio_output_state value);
		
		/**
		 * Initialise an interrupt for the associated pin in the specified mode
		 * and attach the ISR function pointer provided to the interrupt.
		 *
		 * @param  mode	Any number of interrupt types (RISING_EDGE, FALLING_EDGE, BLOCKING, NON_BLOCKING).
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return 0 for success, -1 for error
		 */
		int8_t init_interrupt(uint8_t mode, void* func_pt(void));

		/**
		 * Enable interrupts for the associated pin.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void enable_interrupt(void);
		
		/**
		 * Disable interrupts for the associated pin.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void disable_interrupt(void);
		
		/**
		 * Check to see if the pin has been properly assigned.
		 *
		 * @param  Nothing.
		 * @return Boolean value that is true if the implementation pointer is not NULL, false otherwise.
		 */
		bool is_valid(void);
		
		/**
		 * When called, allows access to the gpio pin to be relinquished and 
		 * assumed elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request access to a gpio pin and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  gpio_pin_address Address of the GPIO pin requested.
		 * @return A gpio_pin instance.
		 */
		static gpio_pin grab(gpio_pin_address);

	private:
		// Functions.
		
		gpio_pin(void);	// Poisoned.

		gpio_pin(gpio_pin_imp*);	// Poisoned.

		gpio_pin operator =(gpio_pin const&);	// Poisoned.

		// Fields.

		/**
		* Pointer to the specific implementation of the gpio pin.
		*/
		gpio_pin_imp* imp;
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__GPIO_H__*/

// ALL DONE.
