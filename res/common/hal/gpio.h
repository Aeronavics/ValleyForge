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
<<<<<<< HEAD
 *	This is the header file which matches gpio.c. Provides general IO functionality for GPIO pins.
=======
 *	This is the header file which matches gpio.c.  Implements general IO operations for GPIO pins.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
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

<<<<<<< HEAD
// Include the common HAL stuff.
#include "hal.h"
=======
// Include the semaphore library that someone is gonna create.
#include "semaphore.h"

// Include the hal library.
#include "hal/hal.h"
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35

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
<<<<<<< HEAD
		 * Gets run whenever the instance of the class goes out of scope.
=======
		 * Gets run whenever the instance of class gpio_pin goes out of scope.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
		 * Vacates the semaphore, allowing the pin to be allocated elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~gpio_pin(void);
		
		/**
		 * Sets the pin to input or output. 
		 * 
<<<<<<< HEAD
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
=======
		 * @param  mode	Set to INPUT or OUTPUT.
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_mode(uint8_t mode);
				
		/**
		 * Read the value of the gpio pin and return it
		 *
		 * @param Nothing.
		 * @return LOW (0), HIGH (1), or ERROR (-1).
		 */
		int8_t read(void);
		
		/**
		 * Writes the value provided to the pin
		 *
		 * @param  value	HIGH(1), LOW(0) or TOGGLE(2).
		 * @return Nothing.
		 */
		int8_t write(uint8_t value);
		
		/** 
		 * Initialise an interrupt for the associated pin in the specified mode
		 * and attach the ISR function pointer provided to the interrupt.
		 *
		 * @param  mode		Any number of interrupt types (RISING_EDGE, FALLING_EDGE, BLOCKING, NON_BLOCKING).
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return 0 for success, -1 for error.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
		 */
		int8_t init_interrupt(uint8_t mode, void* func_pt(void));

		/**
<<<<<<< HEAD
		 * Enable interrupts for the associated pin.
=======
		 * Initialise an interrupt for the associated pin.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void enable_interrupt(void);
		
		/**
<<<<<<< HEAD
		 * Disable interrupts for the associated pin.
=======
		 * Disable an interrupt for the associated pin.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void disable_interrupt(void);
		
		/**
		 * Checks to see whether or not the GPIO pin implementation pointer is null or not.
		 *
		 * @param  Nothing.
<<<<<<< HEAD
		 * @return Boolean value that is true if the implementation pointer is not NULL, false otherwise.
		 */
		bool is_valid(void);
		
		/**
		 * When called, allows access to the gpio pin to be relinquished and 
		 * assumed elsewhere.
=======
		 * @return True if the implementation pointer is not NULL, false otherwise.
		 */
		bool is_valid(void);
		
		/** 
		 * Allows access to the GPIO pin to be relinquished and assumed elsewhere.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request access to a gpio pin and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
<<<<<<< HEAD
		 * @param  gpio_pin_address Address of the GPIO pin requested.
=======
		 * @param  gpio_pin_address	Address of the GPIO pin requested.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
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
<<<<<<< HEAD
		* Pointer to the specific implementation of the gpio pin.
=======
		* Pointer to the machine specific implementation of the GPIO pin.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35
		*/
		gpio_pin_imp* imp;
};

<<<<<<< HEAD
// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.
=======
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
>>>>>>> a7f11408e2fb7335ef192775185aaa9a4b70cd35

#endif /*__GPIO_H__*/

// ALL DONE.
