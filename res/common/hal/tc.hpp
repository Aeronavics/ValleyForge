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
 *
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		tc.h
 *  A header file for the Timer/Counter Module of the HAL. Implements common timer functionality.
 * 
 *  @brief 
 *  A class for the Timer/Counter Module of the HAL. Implements common timer functionality.
 * 
 *  @author 		Zac Frank
 *  @author		Paul Bowler
 *
 *  @date		13-12-2011
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
 *  @section Description
 *
 * This is the header file which matches tc.cpp  
 * Implements various functions relating to timers, input capture and output
 * compare functionality (and hence PWM).
 * Not all timer functionality is accessible through this module, as specifications
 * between different architectures and models varies significantly.
 * 
 * @section Example
 * @code
 * #include "tc.h"
 * 
 * uint8_t duty = 256/2; 		// 50 %
 * 
 * // Get the chosen timer
 * timer my_timer = timer::grab(TC_0);
 * 
 * // Set the timer to be run off the internal oscillator, with a prescalar of 1024
 * my_timer.set_rate(INT,TC_PRE_1024)
 * 
 * // Set up Output Compare unit on Channel A for Fast PWM
 * my_timer.enable_oc(TC_OC_A, OC_MODE_3);
 * 
 * // Set duty cycle
 * my_timer.set_ocR<uint8_t>(TC_OC_A,duty);
 * 
 * // Start the timer
 * my_timer.start();
 * 
 * @endcode
 */

// Only include this header file once.
#ifndef __TC_H__
#define __TC_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the gpio functionality for tying pins with PWM and input capture.
#include "gpio.hpp"

// Include the semaphore library
#include "semaphore.hpp"

// Include the hal library.
#include "hal/hal.hpp"

// FORWARD DEFINE PRIVATE PROTOTYPES.

class timer_imp;

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum timer_input_state {SUCCESS, NO_RES, PIN_TAKEN};

enum tc_number {TC_0, TC_1, TC_2, TC_3, TC_4, TC_5};

enum tc_oc_channel {TC_OC_A, TC_OC_B, TC_OC_C};

enum tc_oc_mode {OC_NONE, OC_MODE_1, OC_MODE_2, OC_MODE_3, OC_MODE_4, OC_MODE_5, OC_MODE_6, OC_MODE_7, OC_MODE_8, OC_MODE_9, OC_MODE_10, OC_MODE_11, OC_MODE_12, OC_MODE_13, OC_MODE_14, OC_MODE_15};

enum tc_oc_channel_mode {OC_CHANNEL_MODE_0, OC_CHANNEL_MODE_1, OC_CHANNEL_MODE_2, OC_CHANNEL_MODE_3};

enum tc_ic_channel {TC_IC_A};

enum tc_ic_mode {IC_NONE, IC_MODE_1, IC_MODE_2, IC_MODE_3, IC_MODE_4};

enum tc_clk_src {INT};

enum tc_prescalar {TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024};

struct timer_rate
{
	tc_clk_src src;
	tc_prescalar pre;
};

// FORWARD DEFINE PRIVATE PROTOTYPES.

class timer_imp;

// DEFINE PUBLIC CLASSES.

/**
 * @class
 * This class implements various functions relating to timers, input capture and output
 * compare functionality (and hence PWM).
 * Not all timer functionality is accessible through this module, as specifications
 * between different architectures and models varies significantly.
 */
class timer
{
	public:
		// Functions.
		
		/**
		 * Sets the timer rate by selecting the clk src and prescaler.
		 * 
		 * @param  timer_rate	Settings for clock source and prescaler.
		 * Possible Values for src: 	  	INT
		 * Possible Values for prescalar: 	{TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024}
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_rate(timer_rate rate);
		
		/**
		 * Loads the timer with a value.
		 *
		 * @param value		The value the timer register will have. Make sure the value type matches up with the size of the timer.
		 * @return 0 for success, -1 for error.
		 */
		template <typename T>
		int8_t load_timer_value(T value);
		
		/**
		 * Gets the value of the timer register. Make sure that you assign the return to a variable of type equivalent
		 * to that of the timer register size.
		 *
		 * @param Nothing.
		 * @return T 	The timer value. Make sure that you assign this to a variable of type equivalent
		 * to that of the timer register size.
		 */
		template <typename T>
		T get_timer_value(void);
		
		/**
		 * Starts the timer.
		 *
		 * @param Nothing
		 * @return 0 for success, -1 for error.
		 */
		int8_t start(void);
		
		/**
		 * Stops the timer.
		 *
		 * @param Nothing
		 * @return 0 for success, -1 for error.
		 */
		int8_t stop(void);

		/**
		 * Enables the overflow interrupt on this timer
		 *
		 * @param  ISRptr		A pointer to the ISR that will be called when this interrupt is generated.
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_tov_interrupt(void (*ISRptr)(void));
		
		/**
		 * Disables the overflow interrupt on this timer
		 *
		 * @param  Nothing.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_tov_interrupt(void);
		
		/**
		 * Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode
		 * operation for Timer/Counter implemented.
		 *
		 * @param mode			Which mode the OC channel should be set to.
		 * Options are: {OC_NONE, OC_MODE_1, OC_MODE_2, OC_MODE_3, OC_MODE_4, OC_MODE_5, OC_MODE_6, OC_MODE_7, OC_MODE_8, OC_MODE_9, OC_MODE_10, OC_MODE_11, OC_MODE_12, OC_MODE_13, OC_MODE_14, OC_MODE_15}
		 * To see descriptions for these modes, see the timer section of the wiki page of your target micro: http://ucunison1.canterbury.ac.nz/trac/ValleyForge/wiki .
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_oc(tc_oc_mode mode);
		
		/**
		 * Enables output channel attached to each Timer/Counter for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode
		 * operation for Timer/Counter implemented.
		 *
		 * @param channel		Which of the channels to activate
		 * One of {TC_OC_A, TC_OC_B, TC_OC_C}; (Make sure that this timer has the channel you are choosing)
		 * @param mode			Which mode the OC channel should be set to.
		 * One of {OC_CHANNEL_MODE_0, OC_CHANNEL_MODE_1, OC_CHANNEL_MODE_2, OC_CHANNEL_MODE_3}
		 * To see descriptions for these modes, see the timer section of the wiki page of your target micro: http://ucunison1.canterbury.ac.nz/trac/ValleyForge/wiki .
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_oc_channel(tc_oc_channel channel, tc_oc_channel_mode mode);

		/**
		 * Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
		 * enable OC mode itself.
		 *
		 * @param  channel		Which channel register to interrupt on.
		 * @param  ISRptr		A pointer to the ISR that is called when this interrupt is generated.
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_oc_interrupt(tc_oc_channel channel, void (*ISRptr)(void));
		
		/**
		 * Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
		 * OC mode operation itself.
		 *
		 * @param channel		Which channel register to disable the interrupt on.
		 * One of {TC_OC_A, TC_OC_B, TC_OC_C}; (Make sure that this timer has the channel you are choosing)
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_oc_interrupt(tc_oc_channel channel);

		/**
		 * Sets the channel value for output compare.
		 *
		 * @param channel	Which channel to set the OC value for.
		 * One of {TC_OC_A, TC_OC_B, TC_OC_C}; (Make sure that this timer has the channel you are choosing)
		 * @param value		The value where when the timer reaches it, something will happen.
		 * @return 0 for success, -1 for error.
		 */
		template <typename T>
		int8_t set_ocR(tc_oc_channel channel, T value);
		
		/**
		 * Sets the channel value for output compare when TOP is equal to the ICRn register.
		 *
		 * @param channel	Which channel to set the OC value for.
		 * One of {TC_OC_A, TC_OC_B, TC_OC_C}; (Make sure that this timer has the channel you are choosing)
		 * @param value		The value where when the timer reaches it, something will happen. Make sure that this number fits into the timer size,
		 * i.e. don't put a 16-bit number into an 8-bit timer.
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_icR(tc_oc_channel channel, uint16_t value);
		
		/**
		 * Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
		 * operation for the specified channel.
		 *
		 * @param channel		Which IC channel should be enabled.
		 * Currently can only choose one (TC_IC_A). More may be added if future architecture implementations call for it.
		 * @param mode			Which mode the IC channel should be set to.
		 * One of {IC_NONE, IC_MODE_1, IC_MODE_2, IC_MODE_3, IC_MODE_4}.
		 * To see descriptions for these modes, see the timer section of the wiki page of your target micro: http://ucunison1.canterbury.ac.nz/trac/ValleyForge/wiki .
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_ic(tc_ic_channel channel, tc_ic_mode mode);

		/**
		 * Enables the input compare interrupt on this timer
		 *
		 * @param  channel		Which channel register to interrupt on.
		 * Currently can only choose one (TC_IC_A). More may be added if future architecture implementations call for it.
		 * @param  ISRptr		A pointer to the ISR that is called when this interrupt is generated. Of form &myISR
		 * @return 0 for success, -1 for error.
		 */
		int8_t enable_ic_interrupt(tc_ic_channel channel, void (*ISRptr)(void));
		
		/**
		 * Disables the input compare interrupt on this timer
		 *
		 * @param channel		Which channel register to disable the interrupt on.
		 * Currently can only choose one (TC_IC_A). More may be added if future architecture implementations call for it.
		 * @return 0 for success, -1 for error.
		 */
		int8_t disable_ic_interrupt(tc_ic_channel channel);
		
		/**
		 * Reads the current input capture register value for the specified channel.
		 *
		 * @param channel	Which channel to read the IC value from.
		 * Currently can only choose one (TC_IC_A). More may be added if future architecture implementations call for it.
		 * @return The IC register value. Make sure your variable being assigned is of type uint16_t/uint8_t/uint32_t (depending
		 * on timer bit-size).
		 */
		template <typename T>
		T get_icR(tc_ic_channel channel);

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
		 * indicating whether access has been granted or not. This is the only way (using the HAL)
		 * to gain access to a timer.
		 *
		 * @param  timerNumber	Which timer is required.
		 * @return A timer instance.
		 */
		static timer grab(tc_number timerNumber);

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
