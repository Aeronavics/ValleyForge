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

/********************************************************************************************************************************
 *
 *  FILE: 			servo.cpp
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Sam Dirks
 *
 *  DATE CREATED:	13-11-2015
 *
 *	Functionality to provide servo operation.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// Define target specific register addresses.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

typedef struct
{
	uint16_t compare_register;
	Tc_oc_channel_mode tc_oc_channel_mode;
} Next_settings;

class Servo_classes_template
{
	public:
		// Functions
		
		virtual Next_settings get_next_settings();
		
		// Fields
		
	protected:
		// Functions
		
		// Fields
		
	private:
		// Functions
		
		Servo_classes_template(void); // Poisoned
		
		void operator =(Servo_classes_template const&);	// Poisoned.
		// Fields
		
};

/**
 * Private, target specific implementation class for public Ppm_input_helper class.
 */
class Ppm_input_helper_imp : public Servo_classes_template
{
	public:

		Ppm_input_helper_imp(Tc_number tc_number);

		~Ppm_input_helper_imp(void);

		Servo_command_status initialise(Tc_ic_channel tc_ic_channel, uint8_t number_channels, uint16_t frame_seperation_blank_time, bool invert);
		
		Servo_command_status start();
		
		Servo_command_status stop();
		
		Servo_command_status register_callback(IsrHandler callback);
		
		uint16_t get_position(uint8_t channel);
		
		void get_positions(uint16_t* positions);	

	private:

		// Functions.

		Ppm_input_helper_imp(void) = delete;	// Poisoned.

		Ppm_input_helper_imp(Ppm_input_helper_imp*) = delete;

		Ppm_input_helper_imp operator =(Ppm_input_helper_imp const&) = delete;	// Poisoned.

		// Fields.
		
		Tc timer;
};

/**
 * Private, target specific implementation class for public Ppm_output_helper_imp class.
 */
class Ppm_output_helper_imp : public Servo_classes_template
{
	public:

		Ppm_output_helper_imp(Tc_number tc_number);

		~Ppm_output_helper_imp(void);

		Servo_command_status initialise(Tc_oc_channel tc_oc_channel, uint8_t number_channels, uint16_t frame_length, bool invert);
		
		Servo_command_status start();
		
		Servo_command_status stop();
		
		void set_position(uint8_t channel, uint16_t position);
		
		void set_positions(uint16_t* positions);

	private:

		// Functions.

		Ppm_output_helper_imp(void) = delete;	// Poisoned.

		Ppm_output_helper_imp(Ppm_output_helper_imp*) = delete;

		Ppm_output_helper_imp operator =(Ppm_output_helper_imp const&) = delete;	// Poisoned.

		// Fields.
		
		Tc timer;
};

/**
 * Private, target specific implementation class for public Pwm_input_helper_imp class.
 */
class Pwm_input_helper_imp : public Servo_classes_template
{
	public:

		Pwm_input_helper_imp(Tc_number tc_number);

		~Pwm_input_helper_imp(void);

		Servo_command_status initialise(Tc_ic_channel tc_ic_channel, bool invert);
		
		Servo_command_status start(void);
		
		Servo_command_status stop(void);
		
		Servo_command_status register_callback(IsrHandler callback);
		
		uint16_t get_position(void);
		
	private:

		// Functions.

		Pwm_input_helper_imp(void) = delete;	// Poisoned.

		Pwm_input_helper_imp(Pwm_input_helper_imp*) = delete;

		Pwm_input_helper_imp operator =(Pwm_input_helper_imp const&) = delete;	// Poisoned.

		// Fields.
		
		Tc timer;
};

/**
 * Private, target specific implementation class for public Pwm_output_helper_imp class.
 */
class Pwm_output_helper_imp : public Servo_classes_template
{
	public:

		Pwm_output_helper_imp(Tc_number tc_number);

		~Pwm_output_helper_imp(void);

		Servo_command_status initialise(Tc_oc_channel tc_oc_channel, uint16_t frame_length, bool invert);
		
		Servo_command_status start(void);
		
		Servo_command_status stop(void);
		
		void set_position(uint16_t position);

	private:

		// Functions.

		Pwm_output_helper_imp(void) = delete;	// Poisoned.

		Pwm_output_helper_imp(Pwm_input_helper_imp*) = delete;

		Pwm_output_helper_imp operator =(Pwm_output_helper_imp const&) = delete;	// Poisoned.

		// Fields.
		
		Tc timer;
		Tc_oc_channel channel;
		
		uint16_t frame_length;
		uint16_t position;
		bool invert;
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

// Ppm_input_helper
/**************************************************************************************************/

Ppm_input_helper::Ppm_input_helper(Ppm_input_helper_imp* implementation)
{
	// Attach implementation
	imp = implementation;
}

Ppm_input_helper::Ppm_input_helper(Tc_number tc_number)
{
	// TODO - class initialisation
	
	static Ppm_input_helper_imp ppm_input(tc_number);
	imp = &ppm_input;
}

Ppm_input_helper::~Ppm_input_helper(void)
{
	return;
}

Servo_command_status Ppm_input_helper::initialise(Tc_ic_channel tc_ic_channel, uint8_t number_channels, uint16_t frame_seperation_blank_time, bool invert)
{
	return imp->initialise(tc_ic_channel, number_channels, frame_seperation_blank_time, invert);
}

Servo_command_status Ppm_input_helper::start(void)
{
	return imp->start();
}

Servo_command_status Ppm_input_helper::stop(void)
{
	return imp->stop();
}

Servo_command_status Ppm_input_helper::register_callback(IsrHandler callback)
{
	return imp->register_callback(callback);
}

uint16_t Ppm_input_helper::get_position(uint8_t channel)
{
	return imp->get_position(channel);
}

void Ppm_input_helper::get_positions(uint16_t* positions)
{
	imp->get_positions(positions);
}

// Ppm_output_helper
/**************************************************************************************************/

Ppm_output_helper::Ppm_output_helper(Ppm_output_helper_imp* implementation)
{
	// Attach implementation
	imp = implementation;
}

Ppm_output_helper::Ppm_output_helper(Tc_number tc_number)
{
	// TODO - class initialisation
	
	static Ppm_output_helper_imp ppm_output(tc_number);
	imp = &ppm_output;
}

Ppm_output_helper::~Ppm_output_helper()
{
	return;
}

Servo_command_status Ppm_output_helper::initialise(Tc_oc_channel tc_oc_channel, uint8_t number_channels, uint16_t frame_length, bool invert)
{
	return imp->initialise(tc_oc_channel, number_channels, frame_length, invert);
}

Servo_command_status Ppm_output_helper::start(void)
{
	return imp->start();
}

Servo_command_status Ppm_output_helper::stop(void)
{
	return imp->stop();
}

void Ppm_output_helper::set_position(uint8_t channel, uint16_t position)
{
	imp->set_position(channel, position);
}

void Ppm_output_helper::set_positions(uint16_t* positions)
{
	imp->set_positions(positions);
}

// Pwm_input_helper
/**************************************************************************************************/

Pwm_input_helper::Pwm_input_helper(Pwm_input_helper_imp* implementation)
{
	// Attach implementation
	imp = implementation;
}

Pwm_input_helper::Pwm_input_helper(Tc_number tc_number)
{
	static Pwm_input_helper_imp pwm_input(tc_number);
	imp = &pwm_input;
}

Servo_command_status Pwm_input_helper::initialise(Tc_ic_channel tc_ic_channel, bool invert)
{
	return imp->initialise(tc_ic_channel, invert);
}

Servo_command_status Pwm_input_helper::start(void)
{
	return imp->start();
}

Servo_command_status Pwm_input_helper::stop(void)
{
	return imp->stop();
}

Servo_command_status Pwm_input_helper::register_callback(IsrHandler callback)
{
	return imp->register_callback(callback);
}

uint16_t Pwm_input_helper::get_position(void)
{
	return imp->get_position();
}

// Pwm_output_helper
/**************************************************************************************************/

Pwm_output_helper::Pwm_output_helper(Pwm_output_helper_imp* implementation)
{
	// Attach implementation
	
	imp = implementation;
}

Pwm_output_helper::Pwm_output_helper(Tc_number tc_number)
{
	static Pwm_output_helper_imp pwm_output(tc_number);
	imp = &pwm_output;
}

Servo_command_status Pwm_output_helper::initialise(Tc_oc_channel tc_oc_channel, uint16_t frame_length, bool invert)
{
	return imp->initialise(tc_oc_channel, frame_length, invert);
}

Servo_command_status Pwm_output_helper::start(void)
{
	return imp->start();
}

Servo_command_status Pwm_output_helper::stop(void)
{
	return imp->stop();
}

void Pwm_output_helper::set_position(uint16_t position)
{
	imp->set_position(position);
}

/**************************************************************************************************/
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).

// Ppm_input_helper_imp
/**************************************************************************************************/

Ppm_input_helper_imp::Ppm_input_helper_imp(Tc_number tc_number) :
	timer(tc_number)
{
	// TODO - class inititalisation
}

Ppm_input_helper_imp::~Ppm_input_helper_imp(void)
{
	// TODO - class cleanup
}

Servo_command_status Ppm_input_helper_imp::initialise(Tc_ic_channel tc_ic_channel, uint8_t number_channels, uint16_t frame_seperation_blank_time, bool invert)
{
	// TODO - initialise the implementation for PPM input
	
	return SERVO_CMD_NAK;
}

Servo_command_status Ppm_input_helper_imp::start(void)
{
	// TODO - start the PPM input
	
	return SERVO_CMD_NAK;
}

Servo_command_status Ppm_input_helper_imp::stop(void)
{
	// TODO - stop the PPM input
	
	return SERVO_CMD_NAK;
}

Servo_command_status Ppm_input_helper_imp::register_callback(IsrHandler callback)
{
	// TODO - register a callback for when an input frame is recieved
	
	return SERVO_CMD_NAK;
}

uint16_t Ppm_input_helper_imp::get_position(uint8_t channel)
{
	// TODO - return the position value the given channel
	
	return 0;
}

void Ppm_input_helper_imp::get_positions(uint16_t* positions)
{
	// TODO - fill the array values with the values of all channels
}

// Ppm_output_helper_imp
/**************************************************************************************************/

Ppm_output_helper_imp::Ppm_output_helper_imp(Tc_number tc_number) :
	timer(tc_number)
{
	// TODO - class inititalisation
}

Ppm_output_helper_imp::~Ppm_output_helper_imp()
{
	// TODO - class cleanup
}

Servo_command_status Ppm_output_helper_imp::initialise(Tc_oc_channel tc_oc_channel, uint8_t number_channels, uint16_t frame_length, bool invert)
{
	// TODO - initialise the implementation for PPM input 
	
	return SERVO_CMD_NAK;
}

Servo_command_status  Ppm_output_helper_imp::start(void)
{
	// TODO - start the PPM output
	
	return SERVO_CMD_NAK;
}

Servo_command_status Ppm_output_helper_imp::stop(void)
{
	// TODO - stop the PPM output
	
	return SERVO_CMD_NAK;
}

void Ppm_output_helper_imp::set_position(uint8_t channel, uint16_t position)
{
	// TODO - set the position value of the given channel
}

void Ppm_output_helper_imp::set_positions(uint16_t* positions)
{
	// TODO - return all position values
}

// Pwm_input_helper_imp
/**************************************************************************************************/

Pwm_input_helper_imp::Pwm_input_helper_imp(Tc_number tc_number) :
	timer(tc_number)
{
	// TODO - class inititalisation
}

Pwm_input_helper_imp::~Pwm_input_helper_imp(void)
{
	// TODO - class cleanup
}

Servo_command_status Pwm_input_helper_imp::initialise(Tc_ic_channel tc_ic_channel, bool invert)
{
	// TODO - initialise the implementation for PWM input
	
	return SERVO_CMD_NAK;
}

Servo_command_status Pwm_input_helper_imp::start(void)
{
	// TODO - start the pwm input
	
	return SERVO_CMD_NAK;
}

Servo_command_status Pwm_input_helper_imp::stop(void)
{
	// TODO - stop the pwm input
	
	return SERVO_CMD_NAK;
}

Servo_command_status Pwm_input_helper_imp::register_callback(IsrHandler callback)
{
	// TODO - register callback
	
	return SERVO_CMD_NAK;
}

uint16_t Pwm_input_helper_imp::get_position(void)
{
	// TODO - return the current position
	
	return 0;
}

// Pwm_output_helper_imp
/**************************************************************************************************/

Pwm_output_helper_imp::Pwm_output_helper_imp(Tc_number tc_number) :
	timer(tc_number)
{
	// TODO - class inititalisation
}

Pwm_output_helper_imp::~Pwm_output_helper_imp(void)
{
	// TODO - class cleanup
}

Servo_command_status Pwm_output_helper_imp::initialise(Tc_oc_channel tc_oc_channel, uint16_t frame_length, bool invert)
{
	// TODO - initialise the implementation for PWM output
	
	return SERVO_CMD_NAK;
}

Servo_command_status Pwm_output_helper_imp::start(void)
{
	// TODO - start the PWM output
	
	return SERVO_CMD_NAK;
}

Servo_command_status Pwm_output_helper_imp::stop(void)
{
	// TODO - stop the PWM output
	
	return SERVO_CMD_NAK;
}

void  Pwm_output_helper_imp::set_position(uint16_t position)
{
	// TODO - set the pwm output value
}

// ALL DONE.