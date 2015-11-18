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
//#include "hal/gpio.hpp"

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
		Ppm_input_helper(Tc_number tc_number);
		
		~Ppm_input_helper(void);
	
		Servo_command_status initialise(Tc_ic_channel tc_ic_channel, size_t number_channels, uint16_t frame_seperation_blank_time, bool invert);
		
		Servo_command_status start(void);
		
		Servo_command_status stop(void);
		
		Servo_command_status register_callback(IsrHandler callback);
		
		uint16_t get_position(size_t channel);
		
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
		Ppm_output_helper(Tc_number tc_number);
		
		~Ppm_output_helper(void);
		
		Servo_command_status initialise(Tc_oc_channel tc_oc_channel, size_t number_channels, uint16_t frame_length, bool invert);
		
		Servo_command_status start();
		
		Servo_command_status stop();
		
		void set_position(size_t channel, uint16_t position);
		
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
		Pwm_input_helper(Tc_number tc_number);
		
		Servo_command_status initialise(Tc_ic_channel tc_ic_channel, bool invert);
		
		Servo_command_status start(void);
		
		Servo_command_status stop(void);
		
		Servo_command_status register_callback(IsrHandler callback);
		
		uint16_t get_position(void);
		
		// Fields
		
	private:
		// Functions
		
		Pwm_input_helper(void) = delete;  // Poisoned
		Pwm_input_helper(Pwm_input_helper*) = delete;  // Poisoned
		Pwm_input_helper(Pwm_input_helper_imp*);
		Pwm_input_helper operator = (Pwm_input_helper const&) = delete;  // Poisoned
		
		// Fields
		
		// Pointer to the target specific implementation of the Ppm_output
		Pwm_input_helper_imp* imp;
};

class Pwm_output_helper
{
	public:
		// Functions
		
		/**
		 * Create Pwm_output_helper instance that provides pwm output functionality
		 */
		Pwm_output_helper(Tc_number tc_number, Tc_oc_channel tc_oc_channel);
		
		/**
		 * Initialise the timer system used.
		 *
		 * @param Tc_oc_channel The Tc channel being uesed for the pwm output
		 * @param uint16_t The framelength in microseconds
		 * @param bool Whether the waveform is inverted. _-___ normal, -_--- inverted
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful
		 */
		Servo_command_status initialise(uint16_t frame_length, bool invert);
		
		/**
		 * Start the pwm output.
		 *
		 * Global interrupts must be enabled for the pwm to output.
		 *
		 * @param Nothing
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful
		 */
		Servo_command_status start();
		
		/**
		 * Stop the pwm output.
		 *
		 * @param Nothing
		 * @return SERVO_CMD_ACK if successful or SERVO_CMD_NAK if unsuccessful
		 */
		Servo_command_status stop();
		
		/**
		 * Set the position of the output.
		 *
		 * @param The position to output in microseconds
		 * @return Nothing
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
		
		// the target specific implementation of the Ppm_output
		Pwm_output_helper_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

// ALL DONE.