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
 *	This is the header file which matches tc.c.  Implements various functions relating to timers, input capture and output
 *	compare functionality (and hence PWM).
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

enum timer_input_state {SUCCESS, NO_RES, PIN_TAKEN};

enum tc_number {TC_0, TC_1, TC_2, TC_3};

enum tc_oc_channel {TC_OC_A, TC_OC_B, TC_OC_C};

enum tc_oc_mode {OC_NONE, OC_MODE_1, OC_MODE_2, OC_MODE_3};

enum tc_ic_channel {TC_IC_A};

enum tc_ic_mode {IC_NONE, IC_MODE_1, IC_MODE_2, IC_MODE_3};

enum tc_clk_src {INT};

enum tc_prescaler {TC_PRE_1, TC_PRE_2, TC_PRE_4, TC_PRE_8};

struct timer_rate
{
	tc_clk_src src;
	tc_prescaler pre;
};

// FORWARD DEFINE PRIVATE PROTOTYPES.

class timer_imp;

// DEFINE PUBLIC CLASSES.

class timer
{
	public:
		// Functions.
		
		/**
		 * Sets the timer rate by selecting the clk src and prescaler.
		 * 
		 * @param  timer_rate	Settings for clock source and prescaler.
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_rate(timer_rate rate);
		
		/**
		 * Loads the timer with a value.
		 *
		 * @param value		The value the timer register will have.
		 * @return 0 for success, -1 for error.
		 */
		template <typename T>
		int8_t load_timer_value(T value);
		
		/**
		 * Gets the value of the timer register.
		 *
		 * @param Nothing.
		 * @return T 	The timer value
		 */
		template <typename T>
		T get_timer_value(void);
		
		/**
		 * Starts the timer.
		 *
		 * @param Nothing
		 * @return 0 for success, -1 for error.
		 */
		uint8_t start(void);
		
		/**
		 * Stops the timer.
		 *
		 * @param Nothing
		 * @return 0 for success, -1 for error.
		 */
		uint8_t stop(void);

		/**
		 * Enables the overflow interrupt on this timer
		 *
		 * @param  ISR		A pointer to the ISR that will be called when this interrupt is generated.
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_tov_interrupt(void* ISR(void));
		
		/**
		 * Disables the overflow interrupt on this timer
		 *
		 * @param  Nothing.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_tov_interrupt(void);
		
		/**
		 * Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disable OC mode
		 * operation for the specified channel.
		 *
		 * @param channel		Which OC channel should be enabled.
		 * @param mode			Which mode the OC channel should be set to.
		 */
		int8_t enable_oc(tc_oc_channel channel, tc_oc_mode mode);

		/**
		 * Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
		 * enable OC mode itself.
		 *
		 * @param  channel		Which channel register to interrupt on.
		 * @param  ISR			A pointer to the ISR that is called when this interrupt is generated.
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_oc_interrupt(tc_oc_channel channel, void* ISR(void));
		
		/**
		 * Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
		 * OC mode operation itself.
		 *
		 * @param channel		Which channel register to disable the interrupt on.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_oc_interrupt(tc_oc_channel channel);

		/**
		 * Sets the channel value for output compare.
		 *
		 * @param channel	Which channel to set the OC value for.
		 * @param value		The value where when the timer reaches it, something will happen.
		 * @return 0 for success, -1 for error.
		 */
		template <typename T>
		uint8_t set_ocR(tc_oc_channel channel, T value);

		/**
		 * Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
		 * operation for the specified channel.
		 *
		 * @param channel		Which IC channel should be enabled.
		 * @param mode			Which mode the IC channel should be set to.
		 */
		int8_t enable_ic(tc_ic_channel channel, tc_ic_mode mode);

		/**
		 * Enables the input compare interrupt on this timer
		 *
		 * @param  channel		Which channel register to interrupt on.
		 * @param  ISR			A pointer to the ISR that is called when this interrupt is generated.  
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_ic_interrupt(uint8_t channel, void* ISR(void));
		
		/**
		 * Disables the input compare interrupt on this timer
		 *
		 * @param channel		Which channel register to disable the interrupt on.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_ic_interrupt(uint8_t channel);
		
		/**
		 * Reads the current input capture register value for the specified channel.
		 *
		 * @param channel	Which channel to read the IC value from.
		 * @return The IC register value.
		 */
		template <typename T>
		T set_ocR(tc_oc_channel channel);

		/**
		 * Gets run whenever the instance of class timer goes out of scope.
		 * Vacates the semaphore, allowing the timer to be allocated elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~timer(void);

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
		 * @param  timer	Which timer is required.
		 * @return A timer instance.
		 */
		static timer grab(tc_number timer);

	private:
		// Functions.
		
		timer(void);	// Poisoned.

		timer(timer_imp*);

		timer operator =(timer const&);	// Poisoned.

		// Fields.

		/**
		* Pointer to the machine specific implementation of the timer.
		*/
		timer_imp* imp;
};


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__TC_H__*/

// ALL DONE.