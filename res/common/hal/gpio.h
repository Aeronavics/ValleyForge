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
 *	This is the header file which matches gpio.c...
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
#include "hal.h"

// FORWARD DEFINE PRIVATE TYPES.

class gpio_pin_imp;	// Not defined here.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

struct gpio_pin_address
{
	port_t	port;
	pin_t pin;
};

class gpio_pin
{
	public:
		// Functions.
		/**
		 * gpio_pin destructor
		 *
		 * Gets run whenever the instance of class gpio_pin goes out of scope.
		 * Vacates the semaphore, allowing the pin to be allocated elsewhere.
		 *
		 * @param  none
		 * @return no return
		 */
		 ~gpio_pin(void);
		
		/**
		 * gpio_pin change mode
		 *
		 * Sets the pin to input or output. 
		 * 
		 *
		 * @param  mode set to INPUT or OUTPUT
		 * @return int8_t, 0 for success, -1 for error
		 */
		int8_t pinMode(uint8_t mode);
				
		/**
		 * Read gpio_pin value
		 *
		 * Read the value of the gpio pin and return it
		 *
		 * @param none
		 * @return int8_t, LOW (0), HIGH (1), or ERROR (-1)
		 */
		int8_t pinRead(void);
		
		/**
		 * Write to gpio_pin
		 *
		 * 
		 * Writes the value provided to the pin
		 *
		 * @param  value	HIGH(1), LOW(0) or TOGGLE(2) 
		 * @return no return
		 */
		int8_t pinWrite(uint8_t value);
		
		/**
		 * Initialised an interrupt on the associated pin.
		 *
		 * 
		 * Initialise an interrupt for the associated pin in a certain mode
		 * and attach the ISR function pointer provided to the interrupt.
		 *
		 * @param  mode	Any number of interrupt types (RISING_EDGE, FALLING_EDGE, BLOCKING, NON_BLOCKING)
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return int8_t, 0 for success, -1 for error
		 */
		int8_t initInterrupt(uint8_t mode, (void *)func_pt);

		/**
		 * Enable the initialised interrupt on the associated pin.
		 *
		 * 
		 * Initialise an interrupt for the associated pin.
		 *
		 * @param  none
		 * @return no return
		 */
		void enableInterrupt(void);
		
		/**
		 * Disable the initialised interrupt on the associated pin.
		 *
		 * 
		 * Disable an interrupt for the associated pin.
		 *
		 * @param  none
		 * @return no return
		 */
		void disableInterrupt(void);
		
		/**
		 * Check to see if the pin has been properly assigned.
		 *
		 * 
		 * Checks to see whether or not the gpio pin implementation pointer is
		 * null or not.
		 *
		 * @param  none
		 * @return boolean value that is true if the implementation pointer is not NULL, false otherwise.
		 */
		bool is_valid(void);
		
		/**
		 * Relinquish access to a gpio pin.
		 *
		 * 
		 * When called, allows access to the gpio pin to be relinquished and 
		 * assumed elsewhere.
		 *
		 * @param  none
		 * @return no return
		 */
		void vacate(void);
		
		/**
		 * Request allocation of a gpio pin.
		 *
		 * 
		 * Allows a process to request access to a gpio pin and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  gpio_pin_address	address (struct) of the gpio pin requested.
		 * @return a gpio_pin instance which is non NULL if the allocation was successful.
		 */
		static gpio_pin grab(gpio_pin_address);

	private:
		// Functions.
		
		gpio_pin(void);	// Poisoned.

		gpio_pin(gpio_pin_imp*);	// Poisoned.

		gpio_pin operator =(gpio_pin const&);	// Poisoned.

		// Fields.
		/**
		*
		* Pointer to the specific implementation of the gpio pin.
		*/
		gpio_pin_imp* imp;
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.



#endif /*__GPIO_H__*/

// ALL DONE.
