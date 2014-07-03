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

/********************************************************************************************************************************
 *
 *  FILE: 		tc.cpp
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	15-12-2011
 *
 *	Functionality to provide implementation for timer/counters in AVR architecture devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/io.h>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// Define target specific register addresses.

#if defined (__AVR_ATmega2560__)
	// Timer/Counter 0.
	#	define TIMSK0_ADDRESS		0x6E
	#	define TCNT0_ADDRESS		0x36
	#	define OCR0B_ADDRESS		0x28
	#	define OCR0A_ADDRESS		0x27
	#	define TCCR0B_ADDRESS		0x25
	#	define TCCR0A_ADDRESS		0x24

	// Timer/Counter 1.
	#	define OCR1C_ADDRESS		0x8C
	#	define OCR1B_ADDRESS		0x8A
	#	define OCR1A_ADDRESS		0x88
	#	define TCNT1_ADDRESS		0x84
	#	define TCCR1B_ADDRESS		0x81
	#	define TCCR1A_ADDRESS		0x80
	#	define TIMSK1_ADDRESS		0x6F

	// Timer/Counter 2.
	#	define OCR2B_ADDRESS		0xB4
	#	define OCR2A_ADDRESS		0xB3
	#	define TCNT2_ADDRESS		0xB2
	#	define TCCR2B_ADDRESS		0xB1
	#	define TCCR2A_ADDRESS		0xB0
	#	define TIMSK2_ADDRESS		0x70

	// Timer/Counter 3.
	#	define OCR3C_ADDRESS		0x9C
	#	define OCR3B_ADDRESS		0x9A
	#	define OCR3A_ADDRESS		0x98
	#	define TCNT3_ADDRESS		0x94
	#	define TCCR3B_ADDRESS		0x91
	#	define TCCR3A_ADDRESS		0x90
	#	define TIMSK3_ADDRESS		0x71

	// Timer/Counter 4.
	#	define OCR4C_ADDRESS		0xAC
	#	define OCR4B_ADDRESS		0xAA
	#	define OCR4A_ADDRESS		0xA8
	#	define TCNT4_ADDRESS		0xA4
	#	define TCCR4B_ADDRESS		0xA1
	#	define TCCR4A_ADDRESS		0xA0
	#	define TIMSK4_ADDRESS		0x72

	// Timer/Counter 5.
	#	define OCR5C_ADDRESS		0x12C
	#	define OCR5B_ADDRESS		0x12A
	#	define OCR5A_ADDRESS		0x128
	#	define TCNT5_ADDRESS		0x124
	#	define TCCR5B_ADDRESS		0x121
	#	define TCCR5A_ADDRESS		0x120
	#	define TIMSK5_ADDRESS		0x73

	// Input Capture Registers.
	#	define ICR1_ADDRESS		0x86
	#	define ICR3_ADDRESS		0x96
	#	define ICR4_ADDRESS		0xA6
	#	define ICR5_ADDRESS		0x126

	// TCCRnB generic bits.
	#	define ICNC_BIT			7
	#	define ICES_BIT			6
	#	define WGM3_BIT			4
	#	define WGM2_BIT			3
	#	define CS2_BIT			2
	#	define CS1_BIT			1
	#	define CS0_BIT			0

	// TCCRnA generic bits.
	#	define COMA1_BIT		7
	#	define COMA0_BIT		6
	#	define COMB1_BIT		5
	#	define COMB0_BIT		4
	#	define COMC1_BIT		3
	#	define COMC0_BIT		2
	#	define WGM1_BIT			1
	#	define WGM0_BIT			0

	#	define COM_BIT_OFFSET	2

	// TIMSKn generic bits.
	#	define ICIE_BIT			5
	#	define OCIEC_BIT		3
	#	define OCIEB_BIT		2
	#	define OCIEA_BIT		1
	#	define TOIE_BIT			0

	// Timer/Counter Peripheral Pin Addresses and Associated Constants.
	#	define TC0_OC_A_PORT		PORT_B
	#	define TC0_OC_A_PIN		PIN_7
	#	define TC0_OC_B_PORT		PORT_G
	#	define TC0_OC_B_PIN		PIN_5

	#	define TC1_OC_A_PORT		PORT_B
	#	define TC1_OC_A_PIN		PIN_5
	#	define TC1_OC_B_PORT		PORT_B
	#	define TC1_OC_B_PIN		PIN_6
	#	define TC1_OC_C_PORT		PORT_B
	#	define TC1_OC_C_PIN		PIN_7
	#	define TC1_IC_A_PORT		PORT_D
	#	define TC1_IC_A_PIN		PIN_4

	#	define TC2_OC_A_PORT		PORT_B
	#	define TC2_OC_A_PIN		PIN_4
	#	define TC2_OC_B_PORT		PORT_H
	#	define TC2_OC_B_PIN		PIN_6

	#	define TC3_OC_A_PORT		PORT_E
	#	define TC3_OC_A_PIN		PIN_3
	#	define TC3_OC_B_PORT		PORT_E
	#	define TC3_OC_B_PIN		PIN_4
	#	define TC3_OC_C_PORT		PORT_E
	#	define TC3_OC_C_PIN		PIN_5
	#	define TC3_IC_A_PORT		PORT_E
	#	define TC3_IC_A_PIN		PIN_7

	#	define TC4_OC_A_PORT		PORT_H
	#	define TC4_OC_A_PIN		PIN_3
	#	define TC4_OC_B_PORT		PORT_H
	#	define TC4_OC_B_PIN		PIN_4
	#	define TC4_OC_C_PORT		PORT_H
	#	define TC4_OC_C_PIN		PIN_5
	#	define TC4_IC_A_PORT		PORT_L
	#	define TC4_IC_A_PIN		PIN_0

	#	define TC5_OC_A_PORT		PORT_L
	#	define TC5_OC_A_PIN		PIN_3
	#	define TC5_OC_B_PORT		PORT_L
	#	define TC5_OC_B_PIN		PIN_4
	#	define TC5_OC_C_PORT		PORT_L
	#	define TC5_OC_C_PIN		PIN_5
	#	define TC5_IC_A_PORT		PORT_L
	#	define TC5_IC_A_PIN		PIN_1

	#	define MAX_TIMER_PINS		4
	#	define IC_CHANNEL_OFFSET	3
	#	define TC_OC_CHANNEL_A		0
	#	define TC_OC_CHANNEL_B		1
	#	define TC_OC_CHANNEL_C		2
	#	define TC_IC_CHANNEL_A		3

	// Interrupt Pointer Array values and offsets.
	#	define NUM_TIMER0_INTERRUPTS	3
	#	define TIMER0_OFFSET		0
	#	define NUM_TIMER1_INTERRUPTS	5
	#	define TIMER1_OFFSET		3
	#	define NUM_TIMER2_INTERRUPTS	3
	#	define TIMER2_OFFSET		8
	#	define NUM_TIMER3_INTERRUPTS	5
	#	define TIMER3_OFFSET		11
	#	define NUM_TIMER4_INTERRUPTS	5
	#	define TIMER4_OFFSET		16
	#	define NUM_TIMER5_INTERRUPTS	5
	#	define TIMER5_OFFSET		21
	#	define NUM_TIMER_INTERRUPTS	(NUM_TIMER0_INTERRUPTS + NUM_TIMER1_INTERRUPTS + NUM_TIMER2_INTERRUPTS + NUM_TIMER3_INTERRUPTS + NUM_TIMER4_INTERRUPTS + NUM_TIMER5_INTERRUPTS)

	// Definitions required for Port Directionality Control.
	#	define PORT_REGISTER_MULTIPLIER		0x03
	#	define LOWER_REGISTER_PORT_OFFSET	0x01
	#	define HIGHER_REGISTER_PORT_OFFSET	0xEC
#else
	#error "No support for this target."
#endif

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

/**
 * Private, target specific implementation class for public Tc class.
 */
class Tc_imp
{
	public:
		
		// Methods - These methods should generally correspond to methods of the public class Tc.

		Tc_imp(Tc_number timer, Tc_timer_size size);
		
		~Tc_imp(void);

		Tc_command_status initialise(void);

		void enable_interrupts(void);
	    
		void disable_interrupts(void);

		Tc_command_status set_rate(Tc_rate rate);

		Tc_command_status load_timer_value(Tc_value value);

		Tc_value get_timer_value(void);

		Tc_command_status start(void);

		Tc_command_status stop(void);

		Tc_command_status enable_tov_interrupt(void (*callback)(void));

		Tc_command_status disable_tov_interrupt(void);

		Tc_command_status enable_oc(Tc_oc_mode mode);

		Tc_command_status enable_oc_channel(Tc_oc_channel channel, Tc_oc_channel_mode mode);

		Tc_command_status enable_oc_interrupt(Tc_oc_channel channel, void (*callback)(void));

		Tc_command_status disable_oc_interrupt(Tc_oc_channel channel);

		Tc_command_status set_ocR(Tc_oc_channel channel, Tc_value value);

		Tc_value get_ocR(Tc_oc_channel channel);

		Tc_command_status enable_ic(Tc_ic_channel channel, Tc_ic_mode mode);

		Tc_command_status enable_ic_interrupt(Tc_ic_channel channel, void (*ISRptr)(void));

		Tc_command_status disable_ic_interrupt(Tc_ic_channel channel);

		Tc_command_status set_icR(Tc_ic_channel channel, Tc_value value);

		Tc_value get_icR(Tc_ic_channel channel);

	private:
		// Functions.
		
		Tc_imp(void) = delete;	// Poisoned.

		Tc_imp(Tc_imp*) = delete;

		Tc_imp operator =(Tc_imp const&) = delete;	// Poisoned.

		// Fields.

		Tc_number timer_number;

		Tc_timer_size timer_size;
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

Tc::Tc(Tc_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	
	// All done.
	return;
}

Tc::Tc(Tc_number timer)
{
	// *** TARGET CONFIGURATION SPECIFIC.

	#ifdef __AVR_ATmega2560__

		// We create a static implementation for each of the timer peripherals.
		static Tc_imp tc_0(TC_0, TC_8BIT);
		static Tc_imp tc_1(TC_1, TC_8BIT);
		static Tc_imp tc_2(TC_2, TC_16BIT);
		static Tc_imp tc_3(TC_3, TC_16BIT);
		static Tc_imp tc_4(TC_4, TC_16BIT);
		static Tc_imp tc_5(TC_5, TC_16BIT);

		// Attach this object to the appropriate implementation.
		switch (timer)
		{
			case TC_0:
				imp = &tc_0;
				break;

			case TC_1:
				imp = &tc_1;
				break;

			case TC_2:
				imp = &tc_2;
				break;

			case TC_3:
				imp = &tc_3;
				break;

			case TC_4:
				imp = &tc_4;
				break;

			case TC_5:
				imp = &tc_5;
				break;

			default:
				// If we end up here, something terrible has happened.
				imp = NULL;
				break;
		}

	#else
		#error "No implementation for this target."
	#endif

	// *** TARGET AGNOSTIC.

	// All done.
	return;	
}
		
Tc::~Tc(void)
{
	// *** TARGET CONFIGURATION SPECIFIC.

	// TODO - This.

	// *** TARGET AGNOSTIC.

	// All done.
	return;
}

Tc_command_status Tc::initialise(void)
{
	return imp->initialise();
}

void Tc::enable_interrupts(void)
{
	return imp->enable_interrupts();
}
	    
void Tc::disable_interrupts(void)
{
	return imp->disable_interrupts();
}
		
Tc_command_status Tc::set_rate(Tc_rate rate)
{
	return imp->set_rate(rate);
}
		
Tc_command_status Tc::load_timer_value(Tc_value value)
{
	return imp->load_timer_value(value);
}
		
Tc_value Tc::get_timer_value(void)
{
	return imp->get_timer_value();
}
		
Tc_command_status Tc::start(void)
{
	return imp->start();
}
		
Tc_command_status Tc::stop(void)
{
	return imp->stop();
}

Tc_command_status Tc::enable_tov_interrupt(void (*callback)(void))
{
	return imp->enable_tov_interrupt(callback);
}
		
Tc_command_status Tc::disable_tov_interrupt(void)
{
	return imp->disable_tov_interrupt();
}
		
Tc_command_status Tc::enable_oc(Tc_oc_mode mode)
{
	return imp->enable_oc(mode);
}
		
Tc_command_status Tc::enable_oc_channel(Tc_oc_channel channel, Tc_oc_channel_mode mode)
{
	return imp->enable_oc_channel(channel, mode);
}

Tc_command_status Tc::enable_oc_interrupt(Tc_oc_channel channel, void (*callback)(void))
{
	return imp->enable_oc_interrupt(channel, callback);
}
		
Tc_command_status Tc::disable_oc_interrupt(Tc_oc_channel channel)
{
	return imp->disable_oc_interrupt(channel);
}

Tc_command_status Tc::set_ocR(Tc_oc_channel channel, Tc_value value)
{
	return imp->set_ocR(channel, value);
}

Tc_value Tc::get_ocR(Tc_oc_channel channel)
{
	return imp->get_ocR(channel);
}
		
Tc_command_status Tc::enable_ic(Tc_ic_channel channel, Tc_ic_mode mode)
{
	return imp->enable_ic(channel, mode);
}

Tc_command_status Tc::enable_ic_interrupt(Tc_ic_channel channel, void (*callback)(void))
{
	return imp->enable_ic_interrupt(channel, callback);
}
		
Tc_command_status Tc::disable_ic_interrupt(Tc_ic_channel channel)
{
	return imp->disable_ic_interrupt(channel);
}

Tc_command_status Tc::set_icR(Tc_ic_channel channel, Tc_value value)
{
	return imp->set_icR(channel, value);
}

Tc_value Tc::get_icR(Tc_ic_channel channel)
{
	return imp->get_icR(channel);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).

Tc_imp::Tc_imp(Tc_number timer, Tc_timer_size size)
{
	// Record which peripheral we are abstracting.
	timer_number = timer;

	// Record what register size this timer uses.
	timer_size = size;

	// All done.
	return;
}
		
Tc_imp::~Tc_imp(void)
{
	// All done.
	return;
}

Tc_command_status Tc_imp::initialise(void)
{
	// TODO - This.

	return TC_CMD_NAK;
}

void Tc_imp::enable_interrupts(void)
{
	// TODO - This.
}
	    
void Tc_imp::disable_interrupts(void)
{
	// TODO - This.
}
		
Tc_command_status Tc_imp::set_rate(Tc_rate rate)
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::load_timer_value(Tc_value value)
{
	// Check if the value is the correct size.
	if (value.type != timer_size)
	{
		// The value doesn't fit into this sort of timer.
		return TC_CMD_NAK;
	}

	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_value Tc_imp::get_timer_value(void)
{
	// TODO - This.

	return Tc_value::from_uint8(0);
}
		
Tc_command_status Tc_imp::start(void)
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::stop(void)
{
	// TODO - This.

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::enable_tov_interrupt(void (*callback)(void))
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::disable_tov_interrupt(void)
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::enable_oc(Tc_oc_mode mode)
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::enable_oc_channel(Tc_oc_channel channel, Tc_oc_channel_mode mode)
{
	// TODO - This.

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::enable_oc_interrupt(Tc_oc_channel channel, void (*callback)(void))
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::disable_oc_interrupt(Tc_oc_channel channel)
{
	// TODO - This.

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::set_ocR(Tc_oc_channel channel, Tc_value value)
{
	// Check if the value is the correct size.
	if (value.type != timer_size)
	{
		// The value doesn't fit into this sort of timer.
		return TC_CMD_NAK;
	}

	// TODO - This.

	return TC_CMD_NAK;
}

Tc_value Tc_imp::get_ocR(Tc_oc_channel channel)
{
	// TODO - This.

	return Tc_value::from_uint8(0);
}
		
Tc_command_status Tc_imp::enable_ic(Tc_ic_channel channel, Tc_ic_mode mode)
{
	// TODO - This.

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::enable_ic_interrupt(Tc_ic_channel channel, void (*callback)(void))
{
	// TODO - This.

	return TC_CMD_NAK;
}
		
Tc_command_status Tc_imp::disable_ic_interrupt(Tc_ic_channel channel)
{
	// TODO - This.

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::set_icR(Tc_ic_channel channel, Tc_value value)
{
	// Check if the value is the correct size.
	if (value.type != timer_size)
	{
		// The value doesn't fit into this sort of timer.
		return TC_CMD_NAK;
	}
	
	// TODO - This.

	return TC_CMD_NAK;
}

Tc_value Tc_imp::get_icR(Tc_ic_channel channel)
{
	// TODO - This.

	return Tc_value::from_uint8(0);
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// TODO - This.










































// /* Array of user ISRs for timer interrupts. */
// void (*timerInterrupts[NUM_TIMER_INTERRUPTS])(void) = {NULL};

// /* Create an array of timer implementation. */
// timer_imp timer_imps[NUM_TIMERS];

// /* Variable to indicate whether timer_imps[] has been initialised yet */
// bool initialised_timers;

// /*Enumerated list of timer interrupts for use in accessing the appropriate function pointer from the function pointer array*/
// enum timer_interrupts {TIMER0_COMPA_int, TIMER0_COMPB_int, TIMER0_OVF_int, TIMER1_CAPT_int, TIMER1_COMPA_int, TIMER1_COMPB_int, TIMER1_COMPC_int, TIMER1_OVF_int, TIMER2_COMPA_int, TIMER2_COMPB_int, TIMER2_OVF_int, TIMER3_CAPT_int, TIMER3_COMPA_int, TIMER3_COMPB_int, TIMER3_COMPC_int, TIMER3_OVF_int, TIMER4_CAPT_int, TIMER4_COMPA_int, TIMER4_COMPB_int, TIMER4_COMPC_int, TIMER4_OVF_int, TIMER5_CAPT_int, TIMER5_COMPA_int, TIMER5_COMPB_int, TIMER5_COMPC_int, TIMER5_OVF_int};



// /**
// * Allows a process to request access to a timer and manages the semaphore
// * indicating whether access has been granted or not.
// *
// * @param  timerNumber	Which timer is required.
// * @return A timer instance.
// */
// timer timer::grab(tc_number timerNumber)
// {
//   /* TODO add possible semaphore functionality in here*/
  
//   /* Check to make sure the timers have been initialised */
//   if  (!initialised_timers)
//   {
//     /* Go and initialise them */
//     for (uint8_t i = 0; i < NUM_TIMERS; i++)
//     {
//       timer_imps[i].timer_id = (tc_number)i;
//     }
    
//     /* Assign the implementation semaphore pointers to their associated peripheral pins */
//     /* Timer/Counter 0 */ /* TODO: break out into a seperate initialisation function */
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_CHANNEL_A].address.port = TC0_OC_A_PORT;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_CHANNEL_A].address.pin = TC0_OC_A_PIN;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_CHANNEL_A].s = &semaphores[(int8_t)TC0_OC_A_PORT][(int8_t)TC0_OC_A_PIN];
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_CHANNEL_B].address.port = TC0_OC_B_PORT;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_CHANNEL_B].address.pin = TC0_OC_B_PIN;
//     timer_imps[(int8_t)TC_0].timer_pins[TC_OC_CHANNEL_B].s = &semaphores[(int8_t)TC0_OC_B_PORT][(int8_t)TC0_OC_B_PIN];
    
//     /* Timer/Counter 1 */
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_A].address.port = TC1_OC_A_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_A].address.pin = TC1_OC_A_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_A].s = &semaphores[(int8_t)TC1_OC_A_PORT][(int8_t)TC1_OC_A_PIN];
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_B].address.port = TC1_OC_B_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_B].address.pin = TC1_OC_B_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_B].s = &semaphores[(int8_t)TC1_OC_B_PORT][(int8_t)TC1_OC_B_PIN];
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_C].address.port = TC1_OC_C_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_C].address.pin = TC1_OC_C_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC1_OC_C_PORT][(int8_t)TC1_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_1].timer_pins[TC_IC_CHANNEL_A].address.port = TC1_IC_A_PORT;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_IC_CHANNEL_A].address.pin = TC1_IC_A_PIN;
//     timer_imps[(int8_t)TC_1].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC1_IC_A_PORT][(int8_t)TC1_IC_A_PIN];
    
//     /* Timer/Counter 2 */
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_CHANNEL_A].address.port = TC2_OC_A_PORT;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_CHANNEL_A].address.pin = TC2_OC_A_PIN;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_CHANNEL_A].s = &semaphores[(int8_t)TC2_OC_A_PORT][(int8_t)TC2_OC_A_PIN];
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_CHANNEL_B].address.port = TC2_OC_B_PORT;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_CHANNEL_B].address.pin = TC2_OC_B_PIN;
//     timer_imps[(int8_t)TC_2].timer_pins[TC_OC_CHANNEL_B].s = &semaphores[(int8_t)TC2_OC_B_PORT][(int8_t)TC2_OC_B_PIN];
    
//      /* Timer/Counter 3 */
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_A].address.port = TC3_OC_A_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_A].address.pin = TC3_OC_A_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_A].s = &semaphores[(int8_t)TC3_OC_A_PORT][(int8_t)TC3_OC_A_PIN];
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_B].address.port = TC3_OC_B_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_B].address.pin = TC3_OC_B_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_B].s = &semaphores[(int8_t)TC3_OC_B_PORT][(int8_t)TC3_OC_B_PIN];
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_C].address.port = TC3_OC_C_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_C].address.pin = TC3_OC_C_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC3_OC_C_PORT][(int8_t)TC3_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_3].timer_pins[TC_IC_CHANNEL_A].address.port = TC3_IC_A_PORT;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_IC_CHANNEL_A].address.pin = TC3_IC_A_PIN;
//     timer_imps[(int8_t)TC_3].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC3_IC_A_PORT][(int8_t)TC3_IC_A_PIN];
    
//     /* Timer/Counter 4 */
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_A].address.port = TC4_OC_A_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_A].address.pin = TC4_OC_A_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_A].s = &semaphores[(int8_t)TC4_OC_A_PORT][(int8_t)TC4_OC_A_PIN];
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_B].address.port = TC4_OC_B_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_B].address.pin = TC4_OC_B_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_B].s = &semaphores[(int8_t)TC4_OC_B_PORT][(int8_t)TC4_OC_B_PIN];
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_C].address.port = TC4_OC_C_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_C].address.pin = TC4_OC_C_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC4_OC_C_PORT][(int8_t)TC4_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_4].timer_pins[TC_IC_CHANNEL_A].address.port = TC4_IC_A_PORT;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_IC_CHANNEL_A].address.pin = TC4_IC_A_PIN;
//     timer_imps[(int8_t)TC_4].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC4_IC_A_PORT][(int8_t)TC4_IC_A_PIN];
    
//     /* Timer/Counter 5 */
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_A].address.port = TC5_OC_A_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_A].address.pin = TC5_OC_A_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_A].s = &semaphores[(int8_t)TC5_OC_A_PORT][(int8_t)TC5_OC_A_PIN];
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_B].address.port = TC5_OC_B_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_B].address.pin = TC5_OC_B_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_B].s = &semaphores[(int8_t)TC5_OC_B_PORT][(int8_t)TC5_OC_B_PIN];
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_C].address.port = TC5_OC_C_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_C].address.pin = TC5_OC_C_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_OC_CHANNEL_C].s = &semaphores[(int8_t)TC5_OC_C_PORT][(int8_t)TC5_OC_C_PIN];
    
//     timer_imps[(int8_t)TC_5].timer_pins[TC_IC_CHANNEL_A].address.port = TC5_IC_A_PORT;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_IC_CHANNEL_A].address.pin = TC5_IC_A_PIN;
//     timer_imps[(int8_t)TC_5].timer_pins[TC_IC_CHANNEL_A].s = &semaphores[(int8_t)TC5_IC_A_PORT][(int8_t)TC5_IC_A_PIN];    
    
//     initialised_timers = true;
//   }
  
//   /* Set the local field 'imp' pointer to point to the specific
//    * implementation of timer_imp */
//   return timer(&timer_imps[timerNumber]);
// }

// // IMPLEMENT PRIVATE FUNCTIONS.

// timer::timer(timer_imp* implementation)
// {
//   /*attach the timer implementation*/
//   imp = implementation;
// }

// /**
// * Sets the timer rate by selecting the clk src and prescaler.
// * 
// * Store the timer number, prescalar and clock settings into fields
// * within the implementation.
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::set_rate(timer_rate rate)
// {
//   /* Check the rate (i.e prescalar) is compatible with the timer chosen */
//   switch (timer_id)
//   {
//     case TC_0:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK0_ADDRESS;
//       registerTable.TCCRB_address = TCCR0B_ADDRESS;
//       registerTable.TCCRA_address = TCCR0A_ADDRESS;
//       registerTable.OCRB_address = OCR0B_ADDRESS;
//       registerTable.OCRA_address = OCR0A_ADDRESS;
//       registerTable.TCNT_address = TCNT0_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_8_BIT;

//       break;
//     }
//     case TC_1:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK1_ADDRESS;
//       registerTable.TCCRB_address = TCCR1B_ADDRESS;
//       registerTable.TCCRA_address = TCCR1A_ADDRESS;
//       registerTable.OCRC_address = OCR1C_ADDRESS;
//       registerTable.OCRB_address = OCR1B_ADDRESS;
//       registerTable.OCRA_address = OCR1A_ADDRESS;
//       registerTable.ICR_address = ICR1_ADDRESS;
//       registerTable.TCNT_address = TCNT1_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//     case TC_2:
//     {
//       /* No invalid settings */
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK2_ADDRESS;
//       registerTable.TCCRB_address = TCCR2B_ADDRESS;
//       registerTable.TCCRA_address = TCCR2A_ADDRESS;
//       registerTable.OCRB_address = OCR2B_ADDRESS;
//       registerTable.OCRA_address = OCR2A_ADDRESS;
//       registerTable.TCNT_address = TCNT2_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_8_BIT;

//       break;
//     }
//     case TC_3:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK3_ADDRESS;
//       registerTable.TCCRB_address = TCCR3B_ADDRESS;
//       registerTable.TCCRA_address = TCCR3A_ADDRESS;
//       registerTable.OCRC_address = OCR3C_ADDRESS;
//       registerTable.OCRB_address = OCR3B_ADDRESS;
//       registerTable.OCRA_address = OCR3A_ADDRESS;
//       registerTable.ICR_address = ICR3_ADDRESS;
//       registerTable.TCNT_address = TCNT3_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//     case TC_4:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK4_ADDRESS;
//       registerTable.TCCRB_address = TCCR4B_ADDRESS;
//       registerTable.TCCRA_address = TCCR4A_ADDRESS;
//       registerTable.OCRC_address = OCR4C_ADDRESS;
//       registerTable.OCRB_address = OCR4B_ADDRESS;
//       registerTable.OCRA_address = OCR4A_ADDRESS;
//       registerTable.ICR_address = ICR4_ADDRESS;
//       registerTable.TCNT_address = TCNT4_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//     case TC_5:
//     {
//       if ((rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128))
//       {
// 	return -1;
//       }
      
//       /* Populate the Timer/Counter register address fields here */
//       registerTable.TIMSK_address = TIMSK5_ADDRESS;
//       registerTable.TCCRB_address = TCCR5B_ADDRESS;
//       registerTable.TCCRA_address = TCCR5A_ADDRESS;
//       registerTable.OCRC_address = OCR5C_ADDRESS;
//       registerTable.OCRB_address = OCR5B_ADDRESS;
//       registerTable.OCRA_address = OCR5A_ADDRESS;
//       registerTable.ICR_address = ICR5_ADDRESS;
//       registerTable.TCNT_address = TCNT5_ADDRESS;
      
//       /* Set which timer type it is */
//       timerType = TIMER_16_BIT;
      
//       break;
//     }
//   }
//   /*Preserve the clock and prescalar settings within the implementation fields if code makes it this far*/
//   preserved_rate = rate;
    
//   return 0;	/* Exit success	*/
// }

// /**
// * Loads the timer with a value.
// *
// * @param value		The value the timer register will have.
// * @return 0 for success, -1 for error.
// */
// template <typename T>
// int8_t timer_imp::load_timer_value(T value)
// {
//   if (timerType == TIMER_16_BIT)
//   {
//     _SFR_MEM16(registerTable.TCNT_address) = value;
//   }
//   else if (registerTable.TCNT_address > 0x60)
//   {
//     _SFR_MEM8(registerTable.TCNT_address) = value;
//   }
//   else
//   {
//     _SFR_IO8(registerTable.TCNT_address) = value;
//   }
  
//  return 0;
// }

// /**
// * Gets the value of the timer register.
// *
// * @return T 	The timer value
// */
// template <typename T>
// T timer_imp::get_timer_value(void)
// {
//   if (timerType == TIMER_16_BIT)
//   {
//     return(_SFR_MEM16(registerTable.TCNT_address));
//   }
//   else if (registerTable.TCNT_address > 0x60)
//   {
//     return(_SFR_MEM8(registerTable.TCNT_address));
//   }
//   else
//   {
//     return(_SFR_IO8(registerTable.TCNT_address));
//   }
// }

// /**
// * Starts the timer.
// *
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::start(void)
// {
//   /*Switch which registers are edited based on the timer number*/
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//       /*edit the TCCR0A and TCCR0B registers*/
//       start_timer0(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_1:
//     {
//       /*edit the TCCR1A and TCCR1B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_2:
//     {
//       /*edit the TCCR2A and TCCR2B registers*/
//       start_timer2(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_3:
//     {
//       /*edit the TCCR3A and TCCR3B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_4:
//     {
//       /*edit the TCCR4A and TCCR4B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//     case TC_5:
//     {
//       /*edit the TCCR5A and TCCR5B registers*/
//       start_16bit_timer(preserved_rate, &registerTable);
//       break;
//     }
//   }
//   return 0;	//How to return -1 in case of an error?
// }

// /**
// * Stops the timer.
// *
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::stop(void)
// {
//   if (registerTable.TCNT_address > 0x60)
//   {
//     _SFR_MEM8(registerTable.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
//   }
//   else
//   {
//     _SFR_IO8(registerTable.TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
//   }
  
//   return 0;
// }

// /**
// * Enables the overflow interrupt on this timer
// *
// * @param  ISRptr		A pointer to the ISR that will be called when this interrupt is generated.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_tov_interrupt(void (*ISRptr)(void))
// {
//     /* Set the TCCRnA and TCCRnB WGMn2:0 bits to 0 for normal operation where the timer/counter
//     * counting direction is always incremented from 0x00(00) to 0xFF(FF) (16-bit implementation)
//     * and the TOVn flag is set when the counter is reset to 0x00(00).
//     *	
//     * Set the appropriate registers depending on which timer/counter implementation
//     * is for.
//     * 
//     * In addition, place the user-provided ISR into the appropriate position of the timerInterrupts
//     * ISR
//     * 
//     * 
//     */
  
//   if (registerTable.TCCRA_address > 0x60)
//   {
//     _SFR_IO8(registerTable.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_IO8(registerTable.TCCRB_address) &= ~(1 << WGM2_BIT);
//   }
//   else
//   {
//     _SFR_MEM8(registerTable.TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(registerTable.TCCRB_address) &= ~(1 << WGM2_BIT);
//   }
//   _SFR_MEM8(registerTable.TIMSK_address) |= (1 << TOIE_BIT);
  
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//       timerInterrupts[TIMER0_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_1:
//     {
//       timerInterrupts[TIMER1_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_2:
//     {
//       timerInterrupts[TIMER2_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_3:
//     {
//       timerInterrupts[TIMER3_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_4:
//     {
//       timerInterrupts[TIMER4_OVF_int] = ISRptr;
//       break;
//     }
//     case TC_5:
//     {
//       timerInterrupts[TIMER5_OVF_int] = ISRptr;
//       break;
//     }
//   }  
//   return 0;
// }

// /**
// * Disables the overflow interrupt on this timer
// *
// * @param  Nothing.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::disable_tov_interrupt(void)
// {
//   /*
//    * To disable the timer overflow interrupt
//    * clear the TOIEn bit in the TIMSKn register
//    */
//   _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << TOIE_BIT);
  
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER0_OVF_int] = NULL;
//       break;
//     }
//     case TC_1:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER1_OVF_int] = NULL;
//       break;
//     }
//     case TC_2:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER2_OVF_int] = NULL;
//       break;
//     }
//     case TC_3:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER3_OVF_int] = NULL;
//       break;
//     }
//     case TC_4:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER4_OVF_int] = NULL;
//       break;
//     }
//     case TC_5:
//     {
//       /*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
//       timerInterrupts[TIMER5_OVF_int] = NULL;
//       break;
//     }
//   }    
//   return 0;
// }

// /**
// * Enables output compare mode for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode
// * operation for Timer/Counter implemented.
// *
// * @param mode			Which mode the OC channel should be set to.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_oc(tc_oc_mode mode)
// {
//   /* Switch the process of enabling output compare interrupts depending on which timer
//    * has been initialised.
//    */
//   switch(timer_id)
//   {
//     case TC_0:
//     { 
//       enable_oc_8bit(mode, &registerTable);
//       break;
//     }
//     case TC_1:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     case TC_2:
//     {
//       enable_oc_8bit(mode, &registerTable);
//       break;
//     }
//     case TC_3:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     case TC_4:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     case TC_5:
//     {
//       enable_oc_16bit(mode, &registerTable);
//       break;
//     }
//     default:	/* No more timers available, return an error. */
//     {
//       return -1;
//     }
//   } 
//   return 0;	/*Should never get here*/
// }

// /**
// * Enables output channel attached to each Timer/Counter for the specified OC channel.  If mode to set to 'OC_NONE', then disables OC mode
// * operation for Timer/Counter implemented.
// *
// * @param mode			Which mode the OC channel should be set to.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_oc_channel(tc_oc_channel channel, tc_oc_channel_mode mode)
// {
//   /*
//    * Switch action to be peformed on register depending on which mode is provided
//    * for function.
//    * 
//    * Note: Process of setting and clearing bits is as follows. Register TCCRnA is structured as below
//    * 	7	  6	   5	    4	     3		2
//    * ------------------------------------------------------------
//    * | COMnA1 | COMnA0 | COMnB1 | COMnB0 | COMnC1* | COMnC0* | etc.
//    * ------------------------------------------------------------ 
//    * (* - Only relevant on 16-bit timers)
//    * 
//    * Thus, to generalise the setting and clearing of bits; COMnA1 or COMnA0 are used in conjunction
//    * with a 'COM_BIT_OFFSET' (2 in this case) and the tc_oc_channel value as a multiplier to set the exact
//    * bit(s) required.
//    */

// if (mode == OC_CHANNEL_MODE_0)	/* COMnX1:0 bits set to 0x00 */
// {
//   if (registerTable.TCCRA_address > 0x60)
//   {
//     _SFR_MEM8(registerTable.TCCRA_address) &= (~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) & ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
//   }
//   else
//   {
//     _SFR_IO8(registerTable.TCCRA_address) &= (~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) & ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
//   }
  
//   /* Vacate the associated GPIO semaphore */
//   timer_pins[(int8_t)channel].s->vacate();
// }
// /* Attempt to procure the semaphore for the GPIO pin required prior to setting the output bits */
// else if (timer_pins[(int8_t)channel].s->procure())
// {
//   switch (mode)
//   {
//     case OC_CHANNEL_MODE_1:	/* COMnX1:0 bits set to 0x01 */
//     {
//       if (registerTable.TCCRA_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.TCCRA_address) &= ~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_MEM8(registerTable.TCCRA_address) |= (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.TCCRA_address) &= ~(1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_IO8(registerTable.TCCRA_address) |= (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
//       }
      
//       break;
//     }
//     case OC_CHANNEL_MODE_2:	/* COMnX1:0 bits set to 0x02 */
//     {
//       if (registerTable.TCCRA_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.TCCRA_address) |= (1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_MEM8(registerTable.TCCRA_address) &= ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));

//       }
//       else
//       {
// 	_SFR_IO8(registerTable.TCCRA_address) |= (1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
// 	_SFR_IO8(registerTable.TCCRA_address) &= ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
//       }
      
//       break;
//     }
//     case OC_CHANNEL_MODE_3:	/* COMnX1:0 bits set to 0x03 */
//     {
//       if (timer_pins[(int8_t)channel].s->procure())
//       {
// 	if (registerTable.TCCRA_address > 0x60)
// 	{
// 	  _SFR_MEM8(registerTable.TCCRA_address) |= ((1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) | (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
// 	}
// 	else
// 	{
// 	  _SFR_IO8(registerTable.TCCRA_address) |= ((1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) | (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
// 	}
//       }
      
//       break;
//     }
//     default:
//       return -1;
//   }    
//   /* 
//    * Set the acquired GPIO pin as an OUTPUT 
//    */
//   if (timer_pins[(int8_t)channel].address.port < PORT_H)
//   {
//     _SFR_IO8(timer_pins[(int8_t)channel].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) |= (1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//   }
//   else
//   {
//     _SFR_MEM8(timer_pins[(int8_t)channel].address.port * PORT_REGISTER_MULTIPLIER + HIGHER_REGISTER_PORT_OFFSET) |= (1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//   }

// }
// else
// {
//   return -1;
// }
	
// return 0;
// }

// /**
// * Enables the output compare interrupt for the specified OC channel.  Note that this doesn't actually
// * enable OC mode itself.
// *
// * @param  channel		Which channel register to interrupt on.
// * @param  ISRptr			A pointer to the ISR that is called when this interrupt is generated.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_oc_interrupt(tc_oc_channel channel, void (*ISRptr)(void))
// {
//   /*
//    * Save the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */
//   switch (timer_id)
//   {
//     case TC_0:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER0_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER0_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	default:
// 	{
// 	  return -1;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_1:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER1_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER1_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER1_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_2:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER2_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER2_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	default:
// 	{
// 	  return -1;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_3:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER3_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER3_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER3_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_4:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER4_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER4_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER4_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//     case TC_5:
//     {
//       switch (channel)
//       {
// 	case TC_OC_A:
// 	{
// 	  timerInterrupts[TIMER5_COMPA_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_B:
// 	{
// 	  timerInterrupts[TIMER5_COMPB_int] = ISRptr;
// 	  break;
// 	}
// 	case TC_OC_C:
// 	{
// 	  timerInterrupts[TIMER5_COMPC_int] = ISRptr;
// 	  break;
// 	}
//       }
//       break;
//     }
//   }  
  
//   /* 
//    * Switch which output compare interrupt to enable based on which channel is provided
//    */
//   switch (channel)
//   {
//     case TC_OC_A:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << OCIEA_BIT);
//       break;
//     }
//     case TC_OC_B:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << OCIEB_BIT);
//       break;
//     }
//     case TC_OC_C:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << OCIEC_BIT);
//       break;
//     }
//   }
  
//   return 0;
// }

// /**
// * Disables the output compare interrupt on this timer.  Note that this doesn't actually disable the
// * OC mode operation itself.
// *
// * @param channel		Which channel register to disable the interrupt on.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::disable_oc_interrupt(tc_oc_channel channel)
// {
//   /*
//    * Clear the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */ 
//   switch(timer_id)
//   {
//     case TC_0:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER0_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER0_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_1:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER1_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER1_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_2:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER2_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER2_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_3:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER3_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER3_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_C:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER3_COMPC_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_4:
//     {
//      /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER4_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER4_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_C:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER4_COMPC_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//     case TC_5:
//     {
//        /* Switch which channel is modified based on the channel provided
//       */
//      switch(channel)
//      {
//        case TC_OC_A:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER5_COMPA_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_B:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER5_COMPB_int] = NULL;
	 
// 	 break;
//        }
//        case TC_OC_C:
//        {
// 	 /* Store the NULL function pointer in the appropriate element within the function pointer array */
// 	 timerInterrupts[TIMER5_COMPC_int] = NULL;
	 
// 	 break;
//        }
//        default:		/* Not a valid channel for this timer */
// 	 return -1;
//      }	 
//       break;
//     }
//   }
  
//   /* Switch the process of disabling output compare interrupts depending on which timer is used for
//    * implementation
//    */
//   switch (channel)
//   {
//     case TC_OC_A:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << OCIEA_BIT);
//       break;
//     }
//     case TC_OC_B:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << OCIEB_BIT);
//       break;
//     }
//     case TC_OC_C:
//     {
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << OCIEC_BIT);
//       break;
//     }
//   }
  
//   return 0; 
// }

// /**
// * Sets the channel value for output compare.
// *
// * @param channel	Which channel to set the OC value for.
// * @param value		The value where when the timer reaches it, something will happen.
// * @return 0 for success, -1 for error.
// */
// template <typename T>
// int8_t timer_imp::set_ocR(tc_oc_channel channel, T value)
// {
//   switch(channel)
//   {
//     case TC_OC_A:
//     {
//       /* Write to the OCRnX register to set the output compare value */
//       if (timerType == TIMER_16_BIT)
//       {
// 	_SFR_MEM16(registerTable.OCRA_address) = value;
//       }
//       else if (registerTable.OCRA_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.OCRA_address) = value;
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.OCRA_address) = value;
//       }
      
//       break;
//     }
//     case TC_OC_B:
//     {
//       /* Write to the OCRnX register to set the output compare value */
//       if (timerType == TIMER_16_BIT)
//       {
// 	_SFR_MEM16(registerTable.OCRB_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM16(registerTable.OCRA_address) == 0x0000)
// // 	{
// // 	  _SFR_MEM16(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else if (registerTable.OCRB_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.OCRB_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_MEM8(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.OCRB_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_IO8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_IO8(registerTable.OCRA_address) = value;
// // 	}
//       }
      
//       break;
//     }
//     case TC_OC_C:	/* TODO: Prevent user from writing to TC_OC_C if using a counter that only has two channels. */
//     {
//       /* Write to the OCRnX register to set the output compare value */
//       if (timerType == TIMER_16_BIT)
//       {
// // 	_SFR_MEM16(registerTable.OCRC_address) = value;
// // 	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM16(registerTable.OCRA_address) == 0x0000)
// // 	{
// // 	  _SFR_MEM16(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else if (registerTable.OCRC_address > 0x60)
//       {
// 	_SFR_MEM8(registerTable.OCRC_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_MEM8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_MEM8(registerTable.OCRA_address) = value;
// // 	}
//       }
//       else
//       {
// 	_SFR_IO8(registerTable.OCRC_address) = value;
	
// // 	/* NOTE: TOP in CTC mode is defined as OCRnA, therefore, if 
// // 	* OCR0A has not been initialised, set it to 0CRnB to allow the compare
// // 	* with Channel B to take place. If user has already set OCRnA to less than
// // 	* OCRnB, problems may ensue.
// // 	*/
// // 	if (_SFR_IO8(registerTable.OCRA_address) == 0x00)
// // 	{
// // 	  _SFR_IO8(registerTable.OCRA_address) = value;
// // 	}
//       }
      
//       break;
//     }
//     default:		/* Not a valid channel for this timer */
//       return -1;
//   }

//   return 0;   
// }

// /**
// * Sets the channel value for output compare when TOP is equal to the ICRn register.
// *
// * @param channel	Which channel to set the OC value for.
// * @param value		The value where when the timer reaches it, something will happen.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::set_icR(tc_oc_channel channel, uint16_t value)
// {
//   _SFR_MEM16(registerTable.ICR_address) = value;
  
//   return 0;
// }

// /**
// * Enables input capture mode for the specified IC channel.  If mode to set to 'IC_NONE', then disable IC mode
// * operation for the specified channel.
// *
// * @param channel		Which IC channel should be enabled.
// * @param mode			Which mode the IC channel should be set to.
// */
// int8_t timer_imp::enable_ic(tc_ic_channel channel, tc_ic_mode mode)
// {
//   /*
//    * Switch which mode is enabled on the input capture unit by the value
//    * given to the function
//    */
//   /* Attempt to procure the required GPIO semaphore first */
//   if (timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].s->procure())
//   {
//     switch(channel)
//     {
//       case TC_IC_A:
//       {
// 	/* Switch depending on which mode is supplied */
// 	switch(mode)
// 	{
// 	  case IC_NONE:
// 	  {
// 	    /* Any disabling code for IC goes here */
// 	    break;
// 	  }
// 	  case IC_MODE_1:	/* Rising edge and input noise cancellation enabled */
// 	  {
// 	    /* Set the ICESn bit in TCCRnB for rising edge detection & the ICNCn bit in the same register for noise cancellation */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_MEM8(registerTable.TCCRB_address) |= ((1 << ICES_BIT) | (1 << ICNC_BIT));
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) |= ((1 << ICES_BIT) | (1 << ICNC_BIT));
// 	    }
	    
// 	    break;
// 	  }
// 	  case IC_MODE_2:	/* Rising edge and input noise cancellation disabled */
// 	  {
// 	    /* Set the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_MEM8(registerTable.TCCRB_address) |= (1 << ICES_BIT); 
// 	      _SFR_MEM8(registerTable.TCCRB_address) &= ~(1 << ICNC_BIT);		  
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) |= (1 << ICES_BIT); 
// 	      _SFR_IO8(registerTable.TCCRB_address) &= ~(1 << ICNC_BIT);	  
// 	    }
	    
// 	    break;
// 	  }
// 	  case IC_MODE_3:	/* Falling edge and input noise cancellation enabled */
// 	  {
// 	    /* Clear the ICESn bit in TCCRnB for falling edge detection & set the ICNCn bit in the same register for noise cancellation */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_MEM8(registerTable.TCCRB_address) |= (1 << ICNC_BIT);
// 	      _SFR_MEM8(registerTable.TCCRB_address) &= ~(1 << ICES_BIT);	  
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) |= (1 << ICNC_BIT);
// 	      _SFR_IO8(registerTable.TCCRB_address) &= ~(1 << ICES_BIT);
// 	    }
	  
// 	    break;
// 	  }
// 	  case IC_MODE_4:	/* Falling edge and input noise cancellation disabled */
// 	  {
// 	    /* Clear the ICESn bit in TCCRnB for rising edge detection & clear the ICNCn bit in the same register for noise cancellation disabling */
// 	    if (registerTable.TCCRB_address > 0x60)
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));	  
// 	    }
// 	    else
// 	    {
// 	      _SFR_IO8(registerTable.TCCRB_address) &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));	  
// 	    }
	    
// 	    break;
// 	  }
// 	  default:	/* Invalid mode for timer */
// 	    return -1;
// 	}
// 	break;
//       }
//       /* Any more IC channels go here*/
//     }  
    
//     /* 
//      * Set the acquired GPIO pin as an INPUT 
//      */
//     if (timer_pins[(int8_t)channel].address.port < PORT_H)
//     {
//       _SFR_IO8(timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//     }
//     else
//     {
//       _SFR_MEM8(timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + HIGHER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)timer_pins[(int8_t)channel].address.pin));
//     }
  
//     return 0;
//   }
//   else
//     return -1;
// }

// /**
// * Enables the input compare interrupt on this timer
// *
// * @param  channel		Which channel register to interrupt on.
// * @param  ISRptr			A pointer to the ISR that is called when this interrupt is generated.  
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::enable_ic_interrupt(tc_ic_channel channel, void (*ISRptr)(void))
// {
//   /*
//    * Save the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */
//   switch (timer_id)
//   {
//     case TC_1:
//     {
//       timerInterrupts[TIMER1_CAPT_int] = ISRptr;
//       break;
//     }
//     case TC_3:
//     {
//       timerInterrupts[TIMER3_CAPT_int] = ISRptr;
//       break;
//     }
//     case TC_4:
//     {
//       timerInterrupts[TIMER4_CAPT_int] = ISRptr;
//       break;
//     }
//     case TC_5:
//     {
//       timerInterrupts[TIMER5_CAPT_int] = ISRptr;
//       break;
//     }
//     default:
//     {
//       return -1;
//       break;
//     }
//   }
 
//   /* 
//    *Switch depending on which channel is supplied 
//    */
//   switch (channel)
//   {
//     case TC_IC_A:
//     {
//       /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
//       _SFR_MEM8(registerTable.TIMSK_address) |= (1 << ICIE_BIT);
         
//       break;
//     }
//     /* TODO: more channels go here if needed */
//   }
  
//   return 0;    
// }

// /**
// * Disables the input compare interrupt on this timer
// *
// * @param channel		Which channel register to disable the interrupt on.
// * @return 0 for success, -1 for error.
// */
// int8_t timer_imp::disable_ic_interrupt(tc_ic_channel channel)
// {
//   /*
//    * Clear the ISR pointer in the appropriate element of the function pointer array
//    * depending on which timer has been implemented and channel provided.
//    */
//   switch (timer_id)
//   {
//     case TC_1:
//     {
//       timerInterrupts[TIMER1_CAPT_int] = NULL;
//       break;
//     }
//     case TC_3:
//     {
//       timerInterrupts[TIMER3_CAPT_int] = NULL;
//       break;
//     }
//     case TC_4:
//     {
//       timerInterrupts[TIMER4_CAPT_int] = NULL;
//       break;
//     }
//     case TC_5:
//     {
//       timerInterrupts[TIMER5_CAPT_int] = NULL;
//       break;
//     }
//     default:
//     {
//       return -1;
//       break;
//     }
//   }
  
//   /* 
//    * Switch depending on which channel is supplied 
//    */
//   switch (channel)
//   {
//     case TC_IC_A:
//     {
//       /* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
//       _SFR_MEM8(registerTable.TIMSK_address) &= ~(1 << ICIE_BIT);
         
//       break;
//     }
//     /* TODO: more channels go here if needed */
//   }
  
//   /*
//    * Vacate the GPIO semaphore gathered
//    */
//   timer_pins[(int8_t)channel + IC_CHANNEL_OFFSET].s->vacate();
  
//  return 0;  
// }

// /**
// * Reads the current input capture register value for the specified channel.
// *
// * @param channel	Which channel to read the IC value from.
// * @return The IC register value.
// */
// template <typename T>
// T timer_imp::get_icR(tc_ic_channel channel)
// {
//   /* Switch which channel to read */
//   switch (channel)
//   {
//     case TC_IC_A:
//     {
//       return (_SFR_MEM16(registerTable.ICR_address));
//       break;
//     }
//   }
    
//  return 0;
// }

// /** 
// * Obtains the peripheral pin which the Timer/Counter requires.
// *
// * @param  address	The address of the GPIO pin required.
// * @return Pointer to a GPIO pin implementation.
// */
// // gpio_pin* timer_imp::grabPeripheralPin(gpio_pin_address address)
// // {
// //   return (&(gpio_pin::grab(address)));
// // }

// /**
// * Starts Timer 0 by manipulating the TCCR0A & TCCR0B registers
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @param  table		Table register addresses for particular Timer/Counter.
// * @return 0 if valid prescalar and clock are supplied, otherwise -1
// */
// int8_t start_timer0(timer_rate rate, Register_address_table *table)
// {
//   /*Edit the registers according to whether an internal/external clock is selected
//    * and which prescaler is chosen*/
//   switch(rate.src)
//   {
//     case INT:	//internal clock
//     {
//       switch(rate.pre)
//       {
// 	case TC_PRE_1:	//Prescalar = 1
// 	{
// 	  _SFR_IO8(table->TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
// 	  _SFR_IO8(table->TCCRB_address) |= (1 << CS0_BIT);	  
// 	  break;
// 	}
// 	case TC_PRE_8:	//Prescalar = 8
// 	{
// 	  _SFR_IO8(table->TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_IO8(table->TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_64:	//Prescalar = 64
// 	{
//   	  _SFR_IO8(table->TCCRB_address) &= ~(1 << CS2_BIT);
// 	  _SFR_IO8(table->TCCRB_address) |= ((1 << CS1_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	case TC_PRE_256:	//Prescalar = 256
// 	{
//   	  _SFR_IO8(table->TCCRB_address) &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_IO8(table->TCCRB_address) |= ((1 << CS2_BIT));
// 	  break;
// 	}
// 	case TC_PRE_1024:	//Prescalar = 1024
// 	{
//   	  _SFR_IO8(table->TCCRB_address) &= ~(1 << CS1_BIT);
// 	  _SFR_IO8(table->TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	default: /*Not a valid prescalar*/
// 	  return -1;
//       }
//       break;
//     }
//     /* If external clocks are ever an option add it here*/
//   }
//   return 0;	/*Valid clock and prescalar*/
// }

// /**
// * Starts the 16-bit Timer/Counters by manipulating the TCCR0B registers
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @param  table		Table register addresses for particular Timer/Counter.
// * @return 0 if valid prescalar and clock are supplied, otherwise -1
// */
// int8_t start_16bit_timer(timer_rate rate, Register_address_table *table)
// {
//   /*Edit the registers according to whether an internal/external clock is selected
//    * and which prescaler is chosen*/
//   switch(rate.src)
//   {
//     case INT:	//internal clock
//     {
//       switch(rate.pre)
//       {
// 	case TC_PRE_1:	//Prescalar = 1
// 	{
//  	  _SFR_MEM8(table->TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
// 	  _SFR_MEM8(table->TCCRB_address) |= (1 << CS0_BIT);
// 	  break;
// 	}
// 	case TC_PRE_8:	//Prescalar = 8
// 	{
//  	  _SFR_MEM8(table->TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table->TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_64:	//Prescalar = 64
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= ~(1 << CS2_BIT);
// 	  _SFR_MEM8(table->TCCRB_address) |= ((1 << CS1_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	case TC_PRE_256:	//Prescalar = 256
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table->TCCRB_address) |= ((1 << CS2_BIT));
// 	  break;
// 	}
// 	case TC_PRE_1024:	//Prescalar = 1024
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= ~(1 << CS1_BIT);
// 	  _SFR_MEM8(table->TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
//       default: /*Not a valid prescalar*/
// 	  return -1;
//       }
//       break;
//     }
//     /* TODO: If external clocks are ever an option add it here*/
//   }
//   return 0;	/*Valid clock and prescalar*/
// }

// /**
// * Starts Timer 0 by manipulating the TCCR0A & TCCR0B registers
// * 
// * @param  timer_rate	Settings for clock source and prescaler.
// * @param  table		Table register addresses for particular Timer/Counter.
// * @return 0 if valid prescalar and clock are supplied, otherwise -1
// */
// int8_t start_timer2(timer_rate rate, Register_address_table *table)
// {
//   /*Edit the registers according to whether an internal/external clock is selected
//    * and which prescaler is chosen*/
//   switch(rate.src)
//   {
//     case INT:	//internal clock
//     {
//       switch(rate.pre)
//       {
// 	case TC_PRE_1:	//Prescalar = 1
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
// 	  _SFR_MEM8(table->TCCRB_address) |= (1 << CS0_BIT);
// 	  break;
// 	}
// 	case TC_PRE_8:	//Prescalar = 8
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table->TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_32:	//Prescalar = 32
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= ~(1 << CS2_BIT);
// 	  _SFR_MEM8(table->TCCRB_address) |= (1 << CS1_BIT);
// 	  break;
// 	}
// 	case TC_PRE_64:	//Prescalar = 64
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
// 	  _SFR_MEM8(table->TCCRB_address) |= (1 << CS2_BIT);
// 	  break;
// 	}
// 	case TC_PRE_128:	//Prescalar = 128
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= ~(1 << CS1_BIT);
// 	  _SFR_MEM8(table->TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
// 	case TC_PRE_256:	//Prescalar = 256
// 	{
//   	  _SFR_MEM8(table->TCCRB_address) &= ~(1 << CS0_BIT);
// 	  _SFR_MEM8(table->TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS1_BIT));
// 	  break;
// 	}
// 	case TC_PRE_1024:	//Prescalar = 1024
// 	{
//  	  _SFR_MEM8(table->TCCRB_address) |= ((1 << CS2_BIT) | (1 << CS1_BIT) | (1 << CS0_BIT));
// 	  break;
// 	}
//       default: /*Not a valid prescalar*/
// 	  return -1;
//       }
//       break;
//     }
//     /* If external clocks are ever an option add it here*/
//   }
//   return 0;	/*Valid clock and prescalar*/
// }

// /**
// * Enables Output Compare operation on 8-bit Timer/Counters.
// * 
// * @param mode			Which mode the OC channel should be set to.
// * @param table			Table of addresses for the particular Timer/Counter registers
// * @return 0 if successful, -1 otherwise.
// */
// int8_t enable_oc_8bit(tc_oc_mode mode, Register_address_table *table)
// {
//   switch(mode)
//   {
//     case OC_NONE:	/* Reset the Timer/Counter to NORMAL mode */
//     {
//       if (table->TCCRA_address > 0x60)
//       {
// 	/* Set the WGMn2:0 bits to 0x00 for NORMAL mode */
// 	_SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
// 	_SFR_MEM8(table->TCCRB_address) &= (~(1 << WGM2_BIT));
//       }
//       else
//       {
// 	/* Set the WGMn2:0 bits to 0x00 for NORMAL mode */
// 	_SFR_IO8(table->TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
// 	_SFR_IO8(table->TCCRB_address) &= (~(1 << WGM2_BIT));
//       }
//        /* Disable the output compare interrupt */
//       _SFR_MEM8(table->TIMSK_address) &= ~(1 << OCIEA_BIT);
      
//       break;
//     }	  	  
//     case OC_MODE_1:	/* PWM Phase Correct, where TOP = 0xFF */
//     {
//       if (table->TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x01 for PWM Phase Correct mode, where TOP = 0xFF */
// 	_SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_MEM8(table->TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);	
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x01 for PWM Phase Correct mode, where TOP = 0xFF */
// 	_SFR_IO8(table->TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_IO8(table->TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_IO8(table->TCCRB_address) &= ~(1 << WGM2_BIT);	
//       }
      
//       break;
//     }
//     case OC_MODE_2:	/* Clear timer on compare (CTC) mode, where TOP = OCRnA */
//     {
//       if (table->TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x02 for Clear timer on compare (CTC) mode, where TOP = OCRnA */
// 	_SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM0_BIT);
// 	_SFR_MEM8(table->TCCRA_address) |= (1 << WGM1_BIT);
// 	_SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);	
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x02 for Clear timer on compare (CTC) mode, where TOP = OCRnA */
// 	_SFR_IO8(table->TCCRA_address) &= ~(1 << WGM0_BIT);
// 	_SFR_IO8(table->TCCRA_address) |= (1 << WGM1_BIT);
// 	_SFR_IO8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
//       }
      
//       break;
//     }
//     case OC_MODE_3:	/* Fast PWM mode, where TOP = 0xFF */
//     {
//       if (table->TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x03 for Fast PWM mode, where TOP = 0xFF */
// 	_SFR_MEM8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x03 for Fast PWM mode, where TOP = 0xFF */
// 	_SFR_IO8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_IO8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
//       }
	      
//       break;
//     }
//     /* Mode 4 reserved */
//     case OC_MODE_5:	/* PWM Phase Correct mode, where TOP = OCRnA */
//     {
//       if (table->TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x05 for PWM Phase Correct mode, where TOP = OCRnA */
// 	_SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_MEM8(table->TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_MEM8(table->TCCRB_address) |= (1 << WGM2_BIT);
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x05 for PWM Phase Correct mode, where TOP = OCRnA */
// 	_SFR_IO8(table->TCCRA_address) &= ~(1 << WGM1_BIT);
// 	_SFR_IO8(table->TCCRA_address) |= (1 << WGM0_BIT);
// 	_SFR_IO8(table->TCCRB_address) |= (1 << WGM2_BIT);
//       }
	      
//       break;
//     }
//     /* Mode 6 reserved */
//     case OC_MODE_7:	/* Fast PWM mode, where TOP = OCRnA */
//     {
//       if (table->TCCRA_address > 0x60)
//       {
// 	/* Set WGMn2:0 bits to 0x07 for Fast PWM mode, where TOP = OCRnA */
// 	_SFR_MEM8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_MEM8(table->TCCRB_address) |= (1 << WGM2_BIT);
//       }
//       else
//       {
// 	/* Set WGMn2:0 bits to 0x07 for Fast PWM mode, where TOP = OCRnA */
// 	_SFR_IO8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
// 	_SFR_IO8(table->TCCRB_address) |= (1 << WGM2_BIT);
//       }
	      
//       break;
//     }
//     default:	/* To handle all other modes not included in the 8-bit timers */
//       return -1;
//       break;
    
//     /* More modes in here if necessary */
//   }

// return 0;

// }

// /**
// * Enables Output Compare operation on 8-bit Timer/Counters.
// * 
// * @param mode			Which mode the OC channel should be set to.
// * @param table			Table of addresses for the particular Timer/Counter registers
// * @return 0 if successful, -1 otherwise.
// */
// int8_t enable_oc_16bit(tc_oc_mode mode, Register_address_table *table)
// {  
//   /* Switch the process of enabling output compare mode depending on which mode is chosen and
//   * provided to function.
//   */
//   switch(mode)
//   {
//   case OC_NONE:
//   {
//     /* Reset the timer counter mode back to NORMAL */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(table->TCCRB_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
//     /* Disable the output compare operation */
//     _SFR_MEM8(table->TIMSK_address) &= ~(1 << OCIEA_BIT);
//     /* Disconnect the output pin to allow for normal operation */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << COMA1_BIT) & ~(1 << COMA0_BIT));
//     break;
//   }
//   case OC_MODE_1:	/* PWM, Phase Correct, 8-bit */
//   {
//     /* Set WGMn3:0 bits to 0x01 for Phase Correct mode with TOP = 0x00FF (8-bit) */
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM0_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT) & ~(1 << WGM1_BIT));
    	    
//     break;
//   }
//   case OC_MODE_2:	/* PWM, Phase Correct, 9-bit */
//   {
//     /* Set WGMn3:0 bits to 0x02 for Phase Correct mode with TOP = 0x01FF (9-bit) */
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM1_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT) & ~(1 << WGM0_BIT));
    	    
//     break;
//   }
//   case OC_MODE_3:	/* PWM, Phase Correct, 10-bit */
//   {
//     /* Set WGMn3:0 bits to 0x03 for Phase Correct mode with TOP = 0x03FF (10-bit) */
//     _SFR_MEM8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
    	    
//     break;
//   }
//   case OC_MODE_4:	/* Clear timer on Compare (CTC) mode where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x04 for CTC mode where TOP = OCRnA */
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     /* TODO: Move this to the enable_oc_interrupt()! Enable Output Compare Interrupt Match Enable in Timer Interrupt Mask register */
//     _SFR_MEM8(table->TIMSK_address) |= (1 << OCIEA_BIT);
	    
//     break;
//   }
//   case OC_MODE_5:	/* Fast PWM, 8-bit */
//   {
//     /* Set WGMn3:0 bits to 0x05 for Fast PWM mode where TOP = 0x00FF (8-bit) */
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM0_BIT);
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM1_BIT);
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     break;
//   }
//   case OC_MODE_6:	/* Fast PWM, 9-bit */
//   {
//     /* Set WGMn3:0 bits to 0x06 for Fast PWM mode where TOP = 0x01FF (9-bit) */
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM1_BIT);
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM0_BIT);
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     break;
//   }
//   case OC_MODE_7:	/* Fast PWM, 10-bit */
//   {
//     /* Set WGMn3:0 bits to 0x07 for Fast PWM mode where TOP = 0x03FF (10-bit) */
//     _SFR_MEM8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM2_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM3_BIT);
    
//     break;
//   }
//   case OC_MODE_8:	/* PWM, Phase & Frequency Correct where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x08 for PWM, Phase & Frequency Correct mode where TOP = ICRn */
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM3_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_9:	/* PWM, Phase & Frequency Correct where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x09 for PWM, Phase & Frequency Correct mode where TOP = OCRnA */
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM3_BIT);
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM0_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM1_BIT);
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_10:	/* PWM, Phase Correct where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x10 for PWM, Phase Correct mode where TOP = ICRn */
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM3_BIT);
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM1_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= ~(1 << WGM0_BIT);
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_11:	/* PWM, Phase Correct where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x11 for PWM, Phase Correct mode where TOP = OCRnA */
//     _SFR_MEM8(table->TCCRB_address) |= (1 << WGM3_BIT);
//     _SFR_MEM8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRB_address) &= ~(1 << WGM2_BIT);
    
//     break;
//   }
//   case OC_MODE_12:	/* Clear timer on Compare (CTC) mode where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x12 for CTC mode where TOP = ICRn */
//     _SFR_MEM8(table->TCCRB_address) |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
    
//     break;
//   }
//   case OC_MODE_13:	/* Reserved */
//   {
//     /* Reserved */
    
//     break;
//   }
//   case OC_MODE_14:	/* Fast PWM mode, where TOP = ICRn */
//   {
//     /* Set WGMn3:0 bits to 0x14 for Fast PWM mode, where TOP = ICRn */
//     _SFR_MEM8(table->TCCRB_address) |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
//     _SFR_MEM8(table->TCCRA_address) |= (1 << WGM1_BIT);
    
//     /* Clear un-needed bits (safeguard) */
//     _SFR_MEM8(table->TCCRA_address) &= (1 << WGM0_BIT);
    
//     break;
//   }
//   case OC_MODE_15:	/* Fast PWM mode, where TOP = OCRnA */
//   {
//     /* Set WGMn3:0 bits to 0x15 for Fast PWM mode, where TOP = OCRnA */
//     _SFR_MEM8(table->TCCRB_address) |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
//     _SFR_MEM8(table->TCCRA_address) |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
    
//     break;
//   }
//   /* More modes in here if necessary */	
//   }
  
//   return 0;
// }


// /** Declare the ISRptrs
//  * 
//  * Each timer interrupt type is tied to a relevant interrupt vector. These are associated
//  * with the user ISRs by way of the function pointer array timerInterrupts[]. Here the
//  * ISRs are declared and the user ISR is called if the appropriate element of the function
//  * pointer array is non NULL.
//  */

// ISR(TIMER0_COMPA_vect)
// {
//   if (timerInterrupts[TIMER0_COMPA_int])
//     timerInterrupts[TIMER0_COMPA_int]();
// }

// ISR(TIMER0_COMPB_vect)
// {
//   if (timerInterrupts[TIMER0_COMPB_int])
//     timerInterrupts[TIMER0_COMPB_int]();
// }

// ISR(TIMER0_OVF_vect)
// {
//   if (timerInterrupts[TIMER0_OVF_int])
//     timerInterrupts[TIMER0_OVF_int]();
// }

// ISR(TIMER1_CAPT_vect)
// {
//   if (timerInterrupts[TIMER1_CAPT_int])
//     timerInterrupts[TIMER1_CAPT_int]();
// }

// ISR(TIMER1_COMPA_vect)
// {
//   if (timerInterrupts[TIMER1_COMPA_int])
//     timerInterrupts[TIMER1_COMPA_int]();
// }

// ISR(TIMER1_COMPB_vect)
// {
//   if (timerInterrupts[TIMER1_COMPB_int])
//     timerInterrupts[TIMER1_COMPB_int]();
// }

// ISR(TIMER1_COMPC_vect)
// {
//   if (timerInterrupts[TIMER1_COMPC_int])
//     timerInterrupts[TIMER1_COMPC_int]();
// }

// ISR(TIMER1_OVF_vect)
// {
//   if (timerInterrupts[TIMER1_OVF_int])
//     timerInterrupts[TIMER1_OVF_int]();
// }

// /*
//  * To prevent TIMER2_COMPA_vect being referenced by Free RTOS too; exclude the 
//  * reference here if FREE_RTOS is defined
//  */
// #ifndef FREE_RTOS_INC
// ISR(TIMER2_COMPA_vect)
// {
//   if (timerInterrupts[TIMER2_COMPA_int])
//     timerInterrupts[TIMER2_COMPA_int]();
// }
// #endif

// ISR(TIMER2_COMPB_vect)
// {
//   if (timerInterrupts[TIMER2_COMPB_int])
//     timerInterrupts[TIMER2_COMPB_int]();
// }

// ISR(TIMER2_OVF_vect)
// {
//   if (timerInterrupts[TIMER2_OVF_int])
//     timerInterrupts[TIMER2_OVF_int]();
// }

// ISR(TIMER3_CAPT_vect)
// {
//   if (timerInterrupts[TIMER3_CAPT_int])
//     timerInterrupts[TIMER3_CAPT_int]();
// }

// ISR(TIMER3_COMPA_vect)
// {
//   if (timerInterrupts[TIMER3_COMPA_int])
//     timerInterrupts[TIMER3_COMPA_int]();
// }

// ISR(TIMER3_COMPB_vect)
// {
//   if (timerInterrupts[TIMER3_COMPB_int])
//     timerInterrupts[TIMER3_COMPB_int]();
// }

// ISR(TIMER3_COMPC_vect)
// {
//   if (timerInterrupts[TIMER3_COMPC_int])
//     timerInterrupts[TIMER3_COMPC_int]();
// }

// ISR(TIMER3_OVF_vect)
// {
//   if (timerInterrupts[TIMER3_OVF_int])
//     timerInterrupts[TIMER3_OVF_int]();
// }

// ISR(TIMER4_CAPT_vect)
// {
//   if (timerInterrupts[TIMER4_CAPT_int])
//     timerInterrupts[TIMER4_CAPT_int]();
// }

// ISR(TIMER4_COMPA_vect)
// {
//   if (timerInterrupts[TIMER4_COMPA_int])
//     timerInterrupts[TIMER4_COMPA_int]();
// }

// ISR(TIMER4_COMPB_vect)
// {
//   if (timerInterrupts[TIMER4_COMPB_int])
//     timerInterrupts[TIMER4_COMPB_int]();
// }

// ISR(TIMER4_COMPC_vect)
// {
//   if (timerInterrupts[TIMER4_COMPC_int])
//     timerInterrupts[TIMER4_COMPC_int]();
// }

// ISR(TIMER4_OVF_vect)
// {
//   if (timerInterrupts[TIMER4_OVF_int])
//     timerInterrupts[TIMER4_OVF_int]();
// }

// ISR(TIMER5_CAPT_vect)
// {
//   if (timerInterrupts[TIMER5_CAPT_int])
//     timerInterrupts[TIMER5_CAPT_int]();
// }

// ISR(TIMER5_COMPA_vect)
// {
//   if (timerInterrupts[TIMER5_COMPA_int])
//     timerInterrupts[TIMER5_COMPA_int]();
// }

// ISR(TIMER5_COMPB_vect)
// {
//   if (timerInterrupts[TIMER5_COMPB_int])
//     timerInterrupts[TIMER5_COMPB_int]();
// }

// ISR(TIMER5_COMPC_vect)
// {
//   if (timerInterrupts[TIMER5_COMPC_int])
//     timerInterrupts[TIMER5_COMPC_int]();
// }

// ISR(TIMER5_OVF_vect)
// {
//   if (timerInterrupts[TIMER5_OVF_int])
//     timerInterrupts[TIMER5_OVF_int]();
// }

// // ALL DONE.
