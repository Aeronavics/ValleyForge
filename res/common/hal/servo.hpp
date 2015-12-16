// Copyright (C) 2015  Aeronavics Ltd
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
 *  @file		servo.hpp
 *  A header file for the Servo Module of the HAL. Implements Servo functionality.
 *
 *  @brief
 *  A class for the Servo Module of the HAL. Implements servo functionality.
 *
 *  @author   	Sam Dirks
 *
 *  @date		13-11-2015
 *
 *  @section 		Licence
 *
 * Copyright (C) 2015  Aeronavics Ltd
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
 * This is the header file which matches servo.cpp
 * Implements various functions relating to servo operation through the use of system timers.
 */

#pragma once

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the hal library.
#include "hal/hal.hpp"
#include "hal/tc.hpp"
#include "hal/tc_platform.hpp"

// Include the gpio functionality for tying pins with PWM and input capture.
#include "hal/gpio.hpp"
//IO_pin_address address({PORT_D, PIN_6});
//Gpio_pin testpin(address);

// DEFINE PRIVATE MACROS.
#define MAX_PPM_CHANNELS 12

// FORWARD DEFINE PRIVATE PROTOTYPES

class Ppm_input_helper_imp;
class Ppm_output_helper_imp;
class Pwm_input_helper_imp;
class Pwm_output_helper_imp;

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum Servo_command_status {SERVO_CMD_ACK, SERVO_CMD_NAK};

// DEFINE PUBLIC CLASSES.

class Ppm_input_helper
{
	public:
		// Functions
		/**
		 * Create Ppm_input_helper instance that provides ppm input functionality on a timer input capture pin.
		 *
		 * @param Tc_number The timer which to use to output the ppm signal.
		 * @param Tc_ic_channel The input capture channel to use for the ppm signal.
		 */
		Ppm_input_helper(Tc_number tc_number, Tc_ic_channel tc_ic_channel);
	
		/**
		 * Initialise the timer system for ppm input.
		 * 
		 * @param size_t The number of channels in the ppm input stream. This must be less than or equal too MAX_PPM_CHANNELS defined above.
		 * @param bool Input an inverted ppm signal, _-_-__ normal, -_-_-- inverted.
		 */
		Servo_command_status initialise(size_t number_channels, uint16_t min_frame_seperation_time, bool invert);
		
		/**
		 * Start the ppm input.
		 *
		 * Global interrupts must be enabled for the ppm to be input.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status start(void);
		
		/**
		 * Stop the ppm output.
		 * If not started between frames the first result taken will be incorrect.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status stop(void);
		
		/**
		 * Register a callback that is called when ever a new ppm frame is received.
		 *
		 * @param Callback The callback will be called with a void pointer to a uint16_t array containing the values of each of the channels in microseconds, the length of the array is the number of channles passed into the initialise function.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status register_callback(Callback callback);
		
		/**
		 * Remove link to the callback so that it is no longer called.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status remove_callback(void);
		
		/**
		 *	Get the current position of the given channel in microseconds.
		 *
		 * @param size_t The channel of which to get the position of
		 * @return uint16_t The position of the channel in microseconds. 0 will be returned until a valid input is received.
		 */
		uint16_t get_position(size_t channel);
		
		/**
		 * Get the positions of all channels in microseconds.
		 * 
		 * @param uint16_t* A pointer to an array which to fill with the positions of all channels. Value of positions will be 0 until valid input has been received.
		 * @return Nothing.
		 */
		void get_positions(uint16_t* positions);
	
		// Fields
	
	private:
		// Functions
		Ppm_input_helper(void) = delete;  // Poisoned
		Ppm_input_helper(Ppm_input_helper*) = delete;  // Poisoned
		Ppm_input_helper(Ppm_input_helper_imp*);
		Ppm_input_helper operator = (Ppm_input_helper const&) = delete;  // Poisoned
		
		// Fields
		
		// Pointer to the target specific implementation of the Ppm_input
		Ppm_input_helper_imp* imp;
};

class Ppm_output_helper
{
	public:
		// Functions
		/**
		 * Create Ppm_output_helper instance that provides ppm output functionality on a timer output pin.
		 *
		 * @param Tc_number The timer which to use to output the ppm signal.
		 * @param Tc_oc_channel The output channel to use for the ppm signal.
		 */
		Ppm_output_helper(Tc_number tc_number, Tc_oc_channel tc_oc_channel);
		
		/**
		 * Initialise the timer system for ppm output.
		 * 
		 * @param size_t The number of channels to send in the output ppm stream.
		 * @param uint16_t The length of the ppm frame in microseconds.
		 * @param bool Output an inverted ppm signal, _-_-__ normal, -_-_-- inverted.
		 */
		Servo_command_status initialise(size_t number_channels, uint16_t frame_length, bool invert);
		
		/**
		 * Start the ppm output.
		 *
		 * Global interrupts must be enabled for the ppm to output. Also at least one call to set_positions(uint16_t* positions)
		 * must be made to set a valid output value before the pwm signal will output.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status start();
		
		
		/**
		 * Stop the ppm output.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status stop();
		
		/**
		 * Set the position of one channel of the ppm output.
		 *
		 * @param size_t The channel number of the channel to set the position of.
		 * @param uint16_t The position in microseconds to set the channel to.
		 * @return Nothing.
		 */
		void set_position(size_t channel, uint16_t position);
		
		/**
		 * Set the positiond of all channels of the ppm output.
		 *
		 * @param uint16_t* A pointer to an array containing positions in microseconds for all channels.
		 * @return Nothing.
		 */
		void set_positions(uint16_t* positions);
		
		// Fields
		
	private:
		// Functions
		
		Ppm_output_helper(void) = delete;  // Poisoned
		Ppm_output_helper(Ppm_output_helper*) = delete;  // Poisoned
		Ppm_output_helper(Ppm_output_helper_imp*);
		Ppm_output_helper operator = (Ppm_output_helper const&) = delete;  // Poisoned
		
		// Fields
		
		// Pointer to the target specific implementation of the Ppm_output
		Ppm_output_helper_imp* imp;
};

class Pwm_input_helper
{
	public:
		// Functions
		
		/**
		 * Create Pwm_input_helper instance that provides pwm input functionality on a timer input capture pin.
		 *
		 * @param Tc_number The timer which to use to capture the pwm signal.
		 * @param Tc_ic_channel The input capture channel to use for the pwm signal.
		 */
		Pwm_input_helper(Tc_number tc_number, Tc_ic_channel tc_ic_channel);
		
		/**
		 * Initialise the timer system for pwm input.
		 * 
		 * @param bool Recieve an inverted pwm signal, _-___ normal, -_--- inverted.
		 */
		Servo_command_status initialise(bool invert);
		
		/**
		 * Start the pwm input.
		 *
		 * Global interrupts must be enabled for the pwm to output.
		 * If started during the pulse of an pwm input the first reading will be incorrect.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status start(void);
		
		/**
		 * Stop the pwm input.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status stop(void);
		
		/**
		 * Register a callback that is called when ever a new pwm pulse width is received.
		 *
		 * @param Callback The callback will be called with a void pointer to a uint16_t value containing the new pulse widths in microseconds.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status register_callback(Callback callback);
		
		/**
		 * Remove link to the callback so that it is no longer called.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status remove_callback(void);
		
		/**
		 *	Get the current pulse width of the pwm input signal in microseconds.
		 *
		 * @param Nothing.
		 * @return uint16_t the width of the input pwm pulse in microseconds. 0 will be returned until valid input has been received.
		 */
		uint16_t get_position(void);
		
		// Fields
		
	private:
		// Functions
		
		Pwm_input_helper(void) = delete;  // Poisoned
		Pwm_input_helper(Pwm_input_helper*) = delete;  // Poisoned
		Pwm_input_helper(Pwm_input_helper_imp*);
		Pwm_input_helper operator = (Pwm_input_helper const&) = delete;  // Poisoned
		
		// Fields
		
		// Pointer to the target specific implementation of the Pwm_input
		Pwm_input_helper_imp* imp;
};

class Pwm_output_helper
{
	public:
		// Functions
		
		/**
		 * Create Pwm_output_helper instance that provides pwm output functionality.
		 *
		 * @param Tc_number The timer which to use to output the pwm signal.
		 * @param Tc_oc_channel The Tc channel on which to output the pwm signal.
		 */
		Pwm_output_helper(Tc_number tc_number, Tc_oc_channel tc_oc_channel);
		
		/**
		 * Initialise the timer system for pwm output.
		 *
		 * @param uint16_t The framelength in microseconds.
		 * @param bool Whether the waveform is inverted. _-___ normal, -_--- inverted.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status initialise(uint16_t frame_length, bool invert);
		
		/**
		 * Start the pwm output.
		 *
		 * Global interrupts must be enabled for the pwm to output. Also at least one call to set_position(uint16_t position)
		 * must be made to set a valid output value before the pwm signal will output.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status start();
		
		/**
		 * Stop the pwm output.
		 *
		 * @param Nothing.
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful.
		 */
		Servo_command_status stop();
		
		/**
		 * Set the position of the output.
		 *
		 * @param The position to output in microseconds.
		 * @return Nothing.
		 */
		void set_position(uint16_t position);
		
		// Fields
		
	private:
		// Functions
		
		Pwm_output_helper(void) = delete;  // Poisoned
		Pwm_output_helper(Pwm_output_helper*) = delete;  // Poisoned
		Pwm_output_helper(Pwm_output_helper_imp*);
		Pwm_output_helper operator = (Pwm_output_helper const&) = delete;  // Poisoned

		// Fields
		
		// The target specific implementation of the Pwm_output
		Pwm_output_helper_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

// ALL DONE.