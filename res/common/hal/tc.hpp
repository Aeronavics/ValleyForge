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
 *  @file		tc.hpp
 *  A header file for the Timer/Counter Module of the HAL. Implements common timer functionality.
 *
 *  @brief
 *  A class for the Timer/Counter Module of the HAL. Implements common timer functionality.
 *
 *  @authro   Kevin Gong
 *  @author 	Zac Frank
 *  @author		Paul Bowler
 *
 *  @date		13-01-2014
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
 */

// Only include this header file once.
#ifndef __TC_H__
#define __TC_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
//#include <stddef.h>

// Include the hal library.
#include "hal/hal.hpp"

// Include the gpio functionality for tying pins with PWM and input capture.
#include "hal/gpio.hpp"

// FORWARD DEFINE PRIVATE PROTOTYPES.

class Tc_imp;

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum Tc_command_status {TC_CMD_ACK, TC_CMD_NAK};
enum Tc_timer_size {TC_16BIT, TC_8BIT};

struct Tc_rate
{
	Tc_clk_src src; // enumerate with TC_SRC_INT; which means INTernal Source clock
						 // the other option would be an EXTernal source clock
	Tc_prescalar pre;
};

struct Tc_value
{
	Tc_timer_size type;

	union
	{
		uint8_t as_8bit;
		uint16_t as_16bit;
	} value;

	static Tc_value from_uint8(uint8_t v)
	{
		Tc_value register_value;

		register_value.type = TC_8BIT;
		register_value.value.as_8bit = v;

		// All done.
		return register_value;
	}

	static Tc_value from_uint16(uint16_t v)
	{
		Tc_value register_value;

		register_value.type = TC_16BIT;
		register_value.value.as_16bit = v;

		// All done.
		return register_value;
	}
};

struct Tc_pins
{
	IO_pin_address address;
};

// DEFINE PUBLIC CLASSES.

/**
 * @class
 * This class implements various functions relating to timer/counters, including input capture and output compare functionality (and hence PWM).
 *
 * NOTE - Because timer/counter peripheral architectures differ significantly between targets, the timer/counter abstraction provided by the HAL is somewhat simplified,
 *        and may not expose all the functionality available in a specific peripheral.
 *
 * NOTE - The width of the timer register changes across targets; the target specific typedef Tc_value is sized to correspond with the width of the timer register on
 *        each supported target.  Be aware that this means timer overflow may occur at significantly different values across targets.
 */

class Tc
{
	public:
		// Functions.

		/**
		 * Create Tc instance abstracting the specified timer/counter hardware peripheral.
		 */
		Tc(Tc_number timer);

		/**
		 * Called when Tc instance goes out of scope
		 */
		~Tc(void);

		/**
		 * Initializes peripheral for first use.
		 *
		 * @param     Nothing.
		 * @return    TC_CMD_ACK if the peripheral was successfully initialised, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status initialise(void);

		/**
		 * Master interrupt enable; enable interrupts for all sources in this timer/counter peripheral.
		 *
	   * @param	    Nothing.
		 * @return    Nothing.
		 */
		void re_enable_interrupts(void);

		/**
		 * Master interrupt disable; disable interrupts for all sources in this timer/counter peripheral.
		 *
		 * @param	    Nothing.
		 * @return    Nothing.
		 */
		void disable_interrupts(void);

		/**
		 * Sets the timer rate by selecting the clk src and prescaler.
		 *
		 * @param    Tc_rate	            Settings for clock source and prescaler.
		 * @return   Tc_command_status    TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status set_rate(Tc_rate rate);

		/**
		 * Loads the timer with a value.
		 *
		 * @param     value		            The value the timer register will have.
		 * @return    Tc_command_status   TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status load_timer_value(Tc_value value);

		/**
		 * Gets the value of the timer register.
		 *
		 * @param     Nothing.
		 * @return    The timer value.
		 */
		Tc_value get_timer_value(void);

		/**
		 * Starts the timer.
		 *
		 * @param     Nothing
		 * @return    TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status start(void);

		/**
		 * Stops the timer.
		 *
		 * @param     Nothing
		 * @return    TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status stop(void);

		/**
		 * Enables the overflow interrupt on this timer
		 *
		 * @param     callback		The handler for this interrupt event.s
		 * @return                TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status enable_tov_interrupt(IsrHandler callback);

		/**
		 * Disables the overflow interrupt on this timer
		 *
		 * @param     Nothing.
		 * @return    TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status disable_tov_interrupt(void);

		/**
		 * Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode operation.
		 *
		 * NOTE - There are variety of significantly different methods in which an output compare peripheral may operate; these different permutations are captured by
		 *		  HAL abstration through different output compare 'modes'.  These modes may change significantly across targets.
		 *
		 * @param     mode			Which mode the OC channel should be set to.
		 * @return    TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status enable_oc(Tc_oc_mode mode);

		/**
		 * Enables output channel attached to each timer/counter for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode operation for this channel.
		 *
		 * @param     channel		Which of the channels to activate
		 * @param     mode			Which mode the OC channel should be set to.
		 * @return    TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status enable_oc_channel(Tc_oc_channel channel, Tc_oc_channel_mode mode);

		/**
		 * Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually enable OC mode itself.
		 *
		 * @param     channel		Which channel register to interrupt on.
		 * @param     callback	The handler for this interrupt event.
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status enable_oc_interrupt(Tc_oc_channel channel, IsrHandler callback);

		/**
		 * Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the OC mode operation itself.
		 *
		 * @param     channel		Which channel register to disable the interrupt on.
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status disable_oc_interrupt(Tc_oc_channel channel);

		/**
		 * Sets the channel value for output compare.
		 *
		 * NOTE - The function of the output compare register may change depending on which OC or IC mode the peripheral is configured into.  For instance, a particular
		 *        OC mode may use the value of OCR (the output compare register for the channel) for comparison against timer value to determine when an output compare
		 *        match event occurs; but in another mode, output match may occur when the timer overflows, and the OCR value may instead determine some other
		 *		  characteristic such as output waveform generation shape.
		 *
		 * @param     channel	  Which channel to set the OC value for.
		 * @param     value		  Usually, the value which, when the timer reaches, causes an output compare match event.
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status set_ocR(Tc_oc_channel channel, Tc_value value);

		/**
		 * Reads the current output compare register value for the specified channel.
		 *
     * @param     channel	  Which channel to read the OCR value from.
		 * @return              The OC register value.
		 */
		Tc_value get_ocR(Tc_oc_channel channel);

		/**
		 * Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
		 * operation for the specified channel.
		 *
		 * @param     channel		Which IC channel should be enabled.
		 * @param     mode			Which mode the IC channel should be set to.
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status enable_ic(Tc_ic_channel channel, Tc_ic_mode mode);

		/**
		 * Enables the input compare interrupt on this timer
		 *
		 * @param     channel		Which channel register to interrupt on.
		 * @param     callback	A pointer to the ISR that is called when this interrupt is generated. Of form &myISR
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status enable_ic_interrupt(Tc_ic_channel channel, IsrHandler callback);

		/**
		 * Disables the input compare interrupt on this timer
		 *
		 * @param     channel		Which channel register to disable the interrupt on.
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status disable_ic_interrupt(Tc_ic_channel channel);

		/**
		 * Sets the channel value for input capture.
		 *
		 * NOTE - The function of the input capture register may change depending on which OC or IC mode the peripheral is configured into.  For instance, whilst in input
		 *	      capture mode, ICR (the input capture register of the channel) usually contains the timer value at which a input capture event occurred, and is read by
		 *        application code;  but whilst in some particular output compare mode, the value of ICR may be set to determine the TOP value for the timer.
		 *
		 * @param     channel	  Which channel to set the IC value for.
		 * @param     value		  Usually, the value which is recorded when an input capture event occurs.
		 * @return              TC_CMD_ACK if the operation was successful, or TC_CMD_NAK if the operation failed.
		 */
		Tc_command_status set_icR(Tc_ic_channel channel, Tc_value value);

		/**
		 * Reads the current input capture register value for the specified channel.
		 *
		 * @param     channel	  Which channel to read the ICR value from.
		 * @return              The IC register value.
		 */
		Tc_value get_icR(Tc_ic_channel channel);

	private:

		// Functions.
		Tc(void) = delete;	// Poisoned.
		Tc(Tc*) = delete;  // Poisoned.
		Tc(Tc_imp*);
		Tc operator =(Tc const&) = delete;	// Poisoned.

		// Fields.

		// Pointer to the target specific implementation of the timer/counter.
		Tc_imp* imp;

};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__TC_H__*/

// ALL DONE.

