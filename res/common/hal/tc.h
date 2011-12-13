/********************************************************************************************************************************
 *
 *  FILE: 			tc.h
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Zac Frank
 *
 *  DATE CREATED:	13-12-2011
 *
 *	This is the header file which matches tc.c.  Implements various functions relating to Timers, input capture compare, and PWM.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __TC_H__
#define __TC_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the gpio functionality for tying pins with PWM and input compare.

#include "gpio.h"

// Include the semaphore library that someone is gonna create.
#include "semaphore.h"

// Include the hal library.
#include "hal/hal.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

class timer_imp;

// DEFINE PUBLIC CLASSES.

enum timer_input_state {SUCCESS, NO_RES, PIN_TAKEN};


class timer
{
	public:
		// Functions.

		/**

		 * Gets run whenever the instance of class timer goes out of scope.
		 * Vacates the semaphore, allowing the timer to be allocated elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~timer(void);
		
		/**
		 * Sets the timer rate by selecting the clk src and prescalar 
		 * 
		 * @param  timer_speed		Probably an enumeration referring to a possible combination of source and prescalar
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_rate(uint8_t timer_speed);
				
		/**
		 * Loads the timer with a value. This is the 8-bit timer version
		 *
		 * @param tvalue		The value the timer register will have.
		 * @return 0 for success, -1 for error.
		 */
		int8_t load_timer_value(uint8_t tvalue);
		
		/**
		 * Loads the timer with a value. This is the 16-bit timer version
		 *
		 * @param tvalue		The value the timer register will have.
		 * @return 0 for success, -1 for error.
		 */
		int8_t load_timer_value(uint16_t tvalue);
		
		/**
		 * Loads the timer with a value. This is the 32-bit timer version
		 *
		 * @param tvalue		The value the timer register will have.
		 * @return 0 for success, -1 for error.
		 */
		int8_t load_timer_value(uint32_t tvalue);
		
		/**
		 * Enables the overflow interrupt on this timer
		 *
		 * @param  ISR		A point to the ISR that will be called when this interrupt is generated.
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_of_interrupt(void* ISR);
		
		/**
		 * Disables the overflow interrupt on this timer
		 *
		 * @param  Nothing.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_of_interrupt(void);
		
		/**
		 * Enables the output compare interrupt on this timer
		 *
		 * @param  channel		Which channel register to interrupt on.
		 * @param  ISR			A pointer to the ISR that is called when this interrupt is generated.
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_oc_interrupt(uint8_t channel, void* ISR);
		
		/**
		 * Disables the output compare interrupt on this timer
		 *
		 * @param channel		Which channel register to disable the interrupt on.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_oc_interrupt(uint8_t channel);
		/**
		 * Enables the input compare interrupt on this timer
		 *
		 * @param  channel		Which channel register to interrupt on.
		 * @param  ISR			A pointer to the ISR that is called when this interrupt is generated.  
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_ic_interrupt(uint8_t channel, void* ISR);
		
		/**
		 * Disables the input compare interrupt on this timer
		 *
		 * @param channel		Which channel register to disable the interrupt on.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_ic_interrupt(uint8_t channel);
		
		/**
		 * Gets the value of the timer register (8-bit timer version)
		 *
		 * @param Nothing.
		 * @return uint8_t 	The timer value
		 */
		uint8_t get_timer_value(void);
		
		/**
		 * Gets the value of the timer register (16-bit timer version)
		 *
		 * @param Nothing.
		 * @return uint16_t 	The timer value
		 */
		uint16_t get_timer_value(void);
		
		/**
		 * Gets the value of the timer register (32-bit timer version)
		 *
		 * @param Nothing.
		 * @return uint32_t 	The timer value
		 */
		uint32_t get_timer_value(void);
		
		/**
		 * Sets the channel value for output compare (8-bit version).
		 *
		 * @param value		The value where when the timer reaches it, something will happen.
		 * @return 0 for success, -1 for error.
		 */
		uint8_t set_ocR(uint8_t value);
		
		/**
		 * Sets the channel value for output compare (16-bit version).
		 *
		 * @param value		The value where when the timer reaches it, something will happen.
		 * @return 0 for success, -1 for error.
		 */
		uint8_t set_ocR(uint16_t value);
		
		/**
		 * Sets the channel value for output compare (32-bit version).
		 *
		 * @param value		The value where when the timer reaches it, something will happen.
		 * @return 0 for success, -1 for error.
		 */
		uint8_t set_ocR(uint32_t value);
		
		/**
		 * Starts the timer
		 *
		 * @param Nothing
		 * @return 0 for success, -1 for error.
		 */
		uint8_t start(void);
		
		/**
		 * Stops the timer
		 *
		 * @param Nothing
		 * @return 0 for success, -1 for error.
		 */
		uint8_t stop(void);
		
		/** 
		 * Allows access to the timer to be relinquished and assumed elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request access to a timer and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  size		What size timer is required (8, 16 bit)
		 * @param  type		Wether it n
		 * @return A periodic_interrupt instance.
		 */
		static timer grab(uint8_t timer_number);

	private:
		// Functions.
		
		periodic_interrupt(void);	// Poisoned.

		periodic_interrupt(timer_imp*); 	// Poisoned

		periodic_interrupt operator =(periodic_interrupt const&);	// Poisoned.

		// Fields.

		/**
		* Pointer to the machine specific implementation of the timer.
		*/
		timer_imp* imp;
};


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__TC_H__*/

// ALL DONE.
