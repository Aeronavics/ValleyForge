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
 *	Functionality to provide servo operation for avr microprocessors.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

#define MIDPOINT 1500



// Define target specific register addresses.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

class Servo_classes_template
{
	public:
		// Functions
		
		virtual void callback(Servo_int_type servo_int_type);
		
		// Fields
		
	protected:
		// Functions
		
		// Fields
		
	private:
		// Functions
		
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

		Servo_command_status initialise(Tc_ic_channel tc_ic_channel, size_t number_channels, uint16_t frame_seperation_blank_time, bool invert);
		
		Servo_command_status start();
		
		Servo_command_status stop();
		
		Servo_command_status register_callback(IsrHandler callback);
		
		uint16_t get_position(size_t channel);
		
		void get_positions(uint16_t* positions);

		void callback(Servo_int_type servo_int_type);		

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

		Servo_command_status initialise(Tc_oc_channel tc_oc_channel, size_t number_channels, uint16_t frame_length, bool invert);
		
		Servo_command_status start();
		
		Servo_command_status stop();
		
		void set_position(size_t channel, uint16_t position);
		
		void set_positions(uint16_t* positions);
		
		void callback(Servo_int_type servo_int_type);

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
		
		void callback(Servo_int_type servo_int_type);
		
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

		Pwm_output_helper_imp(Tc_number tc_number, Tc_oc_channel tc_oc_channel);

		~Pwm_output_helper_imp(void);

		Servo_command_status initialise(uint16_t frame_length, bool invert);
		
		Servo_command_status start(void);
		
		Servo_command_status stop(void);
		
		void set_position(uint16_t pos);
		
		void callback(Servo_int_type servo_int_type);

	private:

		// Functions.

		Pwm_output_helper_imp(void) = delete;	// Poisoned.

		Pwm_output_helper_imp(Pwm_input_helper_imp*) = delete;

		Pwm_output_helper_imp operator =(Pwm_output_helper_imp const&) = delete;	// Poisoned.

		// Fields.
		
		Tc timer;
		Tc_number timer_number;
		Tc_oc_channel channel;
		Servo_int_type compare_int;
		
		uint16_t overflows_required;
		Servo_state servo_state;
		uint16_t frame_length;
		uint16_t position;
		bool invert;
};

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

void Servo_T0_OVF_handler(void);
void Servo_T0_OC_A_handler(void);
void Servo_T0_OC_B_handler(void);
void Servo_T1_OVF_handler(void);
void Servo_T1_OC_A_handler(void);
void Servo_T1_OC_B_handler(void);
void Servo_T1_IC_A_handler(void);
void Servo_T2_OVF_handler(void);
void Servo_T2_OC_A_handler(void);
void Servo_T2_OC_B_handler(void);

uint32_t Servo_us_to_counts(uint16_t us);

uint16_t Servo_num_overflows_required(uint32_t current_timer_counts, uint32_t counts_to_event, Tc_number tc_number);

// DECLARE PRIVATE GLOBAL VARIABLES.

#if defined(__AVR_ATmega328__)
void (*servo_interrupts[NUM_TIMERS][SERVO_TIMER_MAX_INTERRUPTS])(void) = {{Servo_T0_OC_A_handler, Servo_T0_OC_B_handler, NULL, Servo_T0_OVF_handler},
                                                                          {Servo_T1_OC_A_handler, Servo_T1_OC_B_handler, Servo_T1_IC_A_handler, Servo_T1_OVF_handler},
                                                                          {Servo_T2_OC_A_handler, Servo_T2_OC_B_handler, NULL, Servo_T2_OVF_handler}};
#endif

Servo_classes_template* servo_compare_callback_classes[NUM_TIMERS][SERVO_TIMER_MAX_CHANNELS] = {NULL};
Servo_classes_template* servo_ovf_callback_classes[NUM_TIMERS][SERVO_TIMER_MAX_CHANNELS] = {NULL};

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

Servo_command_status Ppm_input_helper::initialise(Tc_ic_channel tc_ic_channel, size_t number_channels, uint16_t frame_seperation_blank_time, bool invert)
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

uint16_t Ppm_input_helper::get_position(size_t channel)
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

Servo_command_status Ppm_output_helper::initialise(Tc_oc_channel tc_oc_channel, size_t number_channels, uint16_t frame_length, bool invert)
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

void Ppm_output_helper::set_position(size_t channel, uint16_t position)
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

Pwm_output_helper::Pwm_output_helper(Tc_number tc_number, Tc_oc_channel tc_oc_channel)
{
	// All implementation combinations possible, set definitions for supported harware combinations
	#if defined (__AVR_ATmega328__)
	static Pwm_output_helper_imp pwm_output_TC_0_OC_A(TC_0, TC_OC_A);
	static Pwm_output_helper_imp pwm_output_TC_0_OC_B(TC_0, TC_OC_B);
	static Pwm_output_helper_imp pwm_output_TC_1_OC_A(TC_1, TC_OC_A);
	static Pwm_output_helper_imp pwm_output_TC_1_OC_B(TC_1, TC_OC_B);
	static Pwm_output_helper_imp pwm_output_TC_2_OC_A(TC_2, TC_OC_A);
	static Pwm_output_helper_imp pwm_output_TC_2_OC_B(TC_2, TC_OC_B);
	
	switch (tc_number)
	{
		case TC_0:
			switch (tc_oc_channel)
			{
				case TC_OC_A:
					imp = &pwm_output_TC_0_OC_A;
					break;
				case TC_OC_B:
					imp = &pwm_output_TC_0_OC_B;
					break;
			}
			break;
		case TC_1:
			switch (tc_oc_channel)
			{
				case TC_OC_A:
					imp = &pwm_output_TC_1_OC_A;
					break;
				case TC_OC_B:
					imp = &pwm_output_TC_1_OC_B;
					break;
			}
			break;
		case TC_2:
			switch (tc_oc_channel)
			{
				case TC_OC_A:
					imp = &pwm_output_TC_2_OC_A;
					break;
				case TC_OC_B:
					imp = &pwm_output_TC_2_OC_B;
					break;
			}
			break;
	}
	#endif
}

Servo_command_status Pwm_output_helper::initialise(uint16_t frame_length, bool invert)
{
	return imp->initialise(frame_length, invert);
}

Servo_command_status Pwm_output_helper::start(void)
{
	return imp->start();
}

Servo_command_status Pwm_output_helper::stop(void)
{
	return imp->stop();
}

void Pwm_output_helper::set_position(uint16_t pos)
{
	imp->set_position(pos);
}

/**************************************************************************************************/
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

/**
 * Convert a time in microseconds to timer counts
 * 
 * @param The microseconds to convert to timer counts
 * @return The number of timer counts
 */
uint32_t Servo_us_to_counts(uint16_t us)
{
	// using integer operations for speed. Need to do in several stages to prevent overflow
	uint32_t counts;
	counts = F_CPU / 1000 / SERVO_PRE_DEVISOR;
	counts *= us;
	counts /= 1000;
	
	return counts;
}

/**
 * Calculate the number of overflows required before the next event
 *
 * @param The current timer counts
 * @param The number of counts until the next event.
 * @param The Tc_number of the timer being used.
 * @return The number of overflows before the next event.
 */
uint16_t Servo_num_overflows_required(uint32_t current_timer_counts, uint32_t counts_to_event, Tc_number tc_number)
{
	uint8_t shift_to_overflows = Timer_size[tc_number];
	
	uint16_t overflows = ((uint32_t)current_timer_counts + (uint32_t)counts_to_event) >> shift_to_overflows;
	
	return overflows;
}

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

Servo_command_status Ppm_input_helper_imp::initialise(Tc_ic_channel tc_ic_channel, size_t number_channels, uint16_t frame_seperation_blank_time, bool invert)
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

uint16_t Ppm_input_helper_imp::get_position(size_t channel)
{
	// TODO - return the position value the given channel
	
	return 0;
}

void Ppm_input_helper_imp::get_positions(uint16_t* positions)
{
	// TODO - fill the array values with the values of all channels
}

void Ppm_input_helper_imp::callback(Servo_int_type servo_int_type)
{
	// TODO - handle a timer interrupt callback
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

Servo_command_status Ppm_output_helper_imp::initialise(Tc_oc_channel tc_oc_channel, size_t number_channels, uint16_t frame_length, bool invert)
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

void Ppm_output_helper_imp::set_position(size_t channel, uint16_t position)
{
	// TODO - set the position value of the given channel
}

void Ppm_output_helper_imp::set_positions(uint16_t* positions)
{
	// TODO - return all position values
}

void Ppm_output_helper_imp::callback(Servo_int_type servo_int_type)
{
	// TODO - handle a timer interrupt callback
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

void Pwm_input_helper_imp::callback(Servo_int_type servo_int_type)
{
	// TODO - handle a timer interrupt callback
}

// Pwm_output_helper_imp
/**************************************************************************************************/

Pwm_output_helper_imp::Pwm_output_helper_imp(Tc_number tc_number, Tc_oc_channel tc_oc_channel) :
	timer(tc_number)
{
	// TODO - class inititalisation
	timer_number = tc_number;
	channel = tc_oc_channel;
}

Pwm_output_helper_imp::~Pwm_output_helper_imp(void)
{
	// TODO - class cleanup
}

Servo_command_status Pwm_output_helper_imp::initialise(uint16_t frame, bool inv)
{
	// TODO - initialise the implementation for PWM output
	// store settings
	frame_length = frame;
	invert = inv;
	
	position = MIDPOINT; // set position to a safe value
	overflows_required = 0;
	
	// associate the channel with the callback interrupt designator
	switch (channel)
	{
		case TC_OC_A:
			compare_int = SERVO_OC_A;
			break;
		case TC_OC_B:
			compare_int = SERVO_OC_B;
			break;
		default:
			return SERVO_CMD_NAK;
			break;
	}
	
	servo_state = SERVO_LOW;
	
	// set the timer value as the correct type for the timer
	Tc_value tc_value;
	#if defined(__AVR_ATmega328__)
	if (timer_number == TC_0 || timer_number == TC_2)
	{
		tc_value = Tc_value::from_uint8(Servo_us_to_counts(frame_length));
		invert = !invert; // invert for correct operation on 8 bit timers. TODO - understand why this is needed and fix.
	}
	else
	{
		tc_value = Tc_value::from_uint16(Servo_us_to_counts(frame_length));
	}
	#endif
	
	if (timer.initialise() == TC_CMD_ACK &&
	    timer.set_rate({SERVO_TC_CLK, SERVO_TC_PRE}) == TC_CMD_ACK &&
	    timer.enable_oc(SERVO_OC_MODE) == TC_CMD_ACK &&
	    timer.enable_oc_channel(channel, SERVO_SET) == TC_CMD_ACK &&
	    timer.set_ocR(channel, tc_value) == TC_CMD_ACK &&
	    timer.enable_oc_interrupt(channel, servo_interrupts[timer_number][compare_int]) == TC_CMD_ACK &&
	    timer.enable_tov_interrupt(servo_interrupts[timer_number][SERVO_OVF]) == TC_CMD_ACK)
	{
		servo_compare_callback_classes[timer_number][compare_int] = this;
		servo_ovf_callback_classes[timer_number][compare_int] = this;
		
		return SERVO_CMD_ACK;
	}
	
	return SERVO_CMD_NAK;
}

Servo_command_status Pwm_output_helper_imp::start(void)
{
	if (timer.start() == TC_CMD_ACK)
		return SERVO_CMD_ACK;
	else
		return SERVO_CMD_NAK;
}

Servo_command_status Pwm_output_helper_imp::stop(void)
{
	// TODO - testing -- requires the disabling of interrupts to allow other servos to run
	timer.disable_oc_interrupt(channel);
	
	servo_compare_callback_classes[timer_number][compare_int] = NULL;
	servo_ovf_callback_classes[timer_number][compare_int] = NULL;
	
	for (int i = 0; i < NUM_TIMERS; i++)
	{
		for (int j = 0; j < SERVO_TIMER_MAX_CHANNELS; j++)
		{
			if (servo_ovf_callback_classes[i][j])
			{
				return SERVO_CMD_ACK;
			}
		}
	}
	
	if (timer.stop() == TC_CMD_ACK)
		return SERVO_CMD_ACK;
	else
		return SERVO_CMD_NAK;
}

void  Pwm_output_helper_imp::set_position(uint16_t pos)
{
	// TODO - testing
	position = pos;
}

void Pwm_output_helper_imp::callback(Servo_int_type servo_int_type)
{
	// TODO - handle a timer interrupt callback
	
	if (servo_int_type == compare_int && overflows_required == 0)
	{
		uint16_t timer_value = 0;
		uint16_t counts_to_event = 0;
		Tc_value tc_value;
		
		switch (servo_state)
			{
				case SERVO_LOW:
				
					#if defined(__AVR_ATmega328__)
					if (timer_number == TC_0 || timer_number == TC_2)
					{
						timer_value = timer.get_timer_value().value.as_8bit;
					}
					else
					{
						timer_value = timer.get_timer_value().value.as_16bit;
					}
					#endif
					
					counts_to_event = Servo_us_to_counts(position);
					overflows_required = Servo_num_overflows_required(timer_value, counts_to_event, timer_number);
					
					#if defined(__AVR_ATmega328__)
					if (timer_number == TC_0 || timer_number == TC_2)
					{
						tc_value = Tc_value::from_uint8(timer_value + counts_to_event);
					}
					else
					{
						tc_value = Tc_value::from_uint16(timer_value + counts_to_event);
					}
					#endif
					
					timer.set_ocR(channel, tc_value);
					if (invert)
						timer.enable_oc_channel(channel, SERVO_SET);
					else
						timer.enable_oc_channel(channel, SERVO_CLEAR);
					
					servo_state = SERVO_HIGH;
					break;
					
				case SERVO_HIGH:
				
					#if defined(__AVR_ATmega328__)
					if (timer_number == TC_0 || timer_number == TC_2)
					{
						timer_value = timer.get_timer_value().value.as_8bit;
					}
					else
					{
						timer_value = timer.get_timer_value().value.as_16bit;
					}
					#endif
					
					counts_to_event = Servo_us_to_counts(frame_length - position);
					overflows_required = Servo_num_overflows_required(timer_value, counts_to_event, timer_number);
					
					#if defined(__AVR_ATmega328__)
					if (timer_number == TC_0 || timer_number == TC_2)
					{
						tc_value = Tc_value::from_uint8(timer_value + counts_to_event);
					}
					else
					{
						tc_value = Tc_value::from_uint16(timer_value + counts_to_event);
					}
					#endif
					
					timer.set_ocR(channel, tc_value);
					if (invert)
						timer.enable_oc_channel(channel, SERVO_CLEAR);
					else
						timer.enable_oc_channel(channel, SERVO_SET);
					
					servo_state = SERVO_LOW;
					break;
					
				default:
					break;
			}
	}
	else if (servo_int_type == SERVO_OVF)
	{
		if (overflows_required > 0)
		{
			overflows_required--;
		}
	}
	
}

// IMPLEMENT CALLBACK HANDLERS

// These callback handlers will call the callback handler of Servo_classes_template for those stored in servo_classes

#if defined(__AVR_ATmega328__)
void Servo_T0_OVF_handler(void)
{
	// loop through all possible classes with a callback
	for (int i = 0; i < SERVO_TIMER_MAX_CHANNELS; i++)
	{
		if (servo_ovf_callback_classes[TC_0][i])
			servo_ovf_callback_classes[TC_0][i]->callback(SERVO_OVF);
	}
}

void Servo_T0_OC_A_handler(void)
{
	if (servo_compare_callback_classes[TC_0][SERVO_OC_A])
		servo_compare_callback_classes[TC_0][SERVO_OC_A]->callback(SERVO_OC_A);
}

void Servo_T0_OC_B_handler(void)
{
	if (servo_compare_callback_classes[TC_0][SERVO_OC_B])
		servo_compare_callback_classes[TC_0][SERVO_OC_B]->callback(SERVO_OC_B);
}

void Servo_T1_OVF_handler(void)
{
	// loop through all possible classes with a callback
	for (int i = 0; i < SERVO_TIMER_MAX_CHANNELS; i++)
	{
		if (servo_ovf_callback_classes[TC_1][i])
			servo_ovf_callback_classes[TC_1][i]->callback(SERVO_OVF);
	}
}

void Servo_T1_OC_A_handler(void)
{
	if (servo_compare_callback_classes[TC_1][SERVO_OC_A])
		servo_compare_callback_classes[TC_1][SERVO_OC_A]->callback(SERVO_OC_A);
}

void Servo_T1_OC_B_handler(void)
{
	if (servo_compare_callback_classes[TC_1][SERVO_OC_B])
		servo_compare_callback_classes[TC_1][SERVO_OC_B]->callback(SERVO_OC_B);
}

void Servo_T1_IC_A_handler(void)
{
	if (servo_compare_callback_classes[TC_1][SERVO_IC_A])
		servo_compare_callback_classes[TC_1][SERVO_IC_A]->callback(SERVO_IC_A);
}

void Servo_T2_OVF_handler(void)
{
	// loop through all possible classes with a callback
	for (int i = 0; i < SERVO_TIMER_MAX_CHANNELS; i++)
	{
		if (servo_ovf_callback_classes[TC_2][i])
			servo_ovf_callback_classes[TC_2][i]->callback(SERVO_OVF);
	}
}

void Servo_T2_OC_A_handler(void)
{
	if (servo_compare_callback_classes[TC_2][SERVO_OC_A])
		servo_compare_callback_classes[TC_2][SERVO_OC_A]->callback(SERVO_OC_A);
}

void Servo_T2_OC_B_handler(void)
{
	if (servo_compare_callback_classes[TC_2][SERVO_OC_B])
		servo_compare_callback_classes[TC_2][SERVO_OC_B]->callback(SERVO_OC_B);
}

#endif

// ALL DONE.