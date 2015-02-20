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
 *  AUTHOR: 		Paul Bowler and Kevin Gong
 *
 *  DATE CREATED:	09-12-2014
 *
 *	Functionality to provide implementation for timer/counters in AVR architecture devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include "tc_platform.hpp"
#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// Define target specific register addresses.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

struct Tc_registerTable
{
	volatile uint8_t* TIMSK_ADDRESS;
	volatile uint8_t* TCCR_A_ADDRESS;
	volatile uint8_t* TCCR_B_ADDRESS;
	volatile uint8_t* TCCR_C_ADDRESS;
	volatile uint16_t* ICR_ADDRESS;

	union
	{
		volatile uint16_t* as_16bit;
		volatile uint8_t* as_8bit;
	} OCR_A_ADDRESS;

	union
	{
		volatile uint16_t* as_16bit;
		volatile uint8_t* as_8bit;
	} OCR_B_ADDRESS;

	union
	{
		volatile uint16_t* as_16bit;
		volatile uint8_t* as_8bit;
	} OCR_C_ADDRESS;

	union
	{
		volatile uint16_t* as_16bit;
		volatile uint8_t* as_8bit;
	} TCNT_ADDRESS;
};

/**
 * Private, target specific implementation class for public Tc class.
 */
class Tc_imp
{
	public:

		Tc_imp(Tc_number timer, Tc_timer_size size, Tc_registerTable registers);

		~Tc_imp(void);

		Tc_command_status initialise(void);

		void enable_interrupts(void);

		void disable_interrupts(void);

		Tc_command_status set_rate(Tc_rate rate);

		Tc_command_status load_timer_value(Tc_value value);

		Tc_value get_timer_value(void);

		Tc_command_status start(void);

		Tc_command_status stop(void);

		Tc_command_status enable_tov_interrupt(IsrHandler callback);

		Tc_command_status disable_tov_interrupt(void);

		Tc_command_status enable_oc(Tc_oc_mode mode);

		Tc_command_status enable_oc_channel(Tc_oc_channel channel, Tc_oc_channel_mode mode);

		Tc_command_status enable_oc_interrupt(Tc_oc_channel channel, IsrHandler callback);

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

		Tc_registerTable imp_register_table;

		Tc_rate imp_rate;

    Tc_oc_mode waveform_mode;

		Tc_pins pin_address [MAX_TIMER_PINS] = {};
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// /* Array of user ISRs for timer interrupts. */
void (*timerInterrupts[NUM_TIMER_INTERRUPTS])(void) = {NULL};

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.
Tc_command_status start_8bit_timers (Tc_number tc_number, Tc_rate rate, Tc_registerTable table) //
{
	if (tc_number == TC_0)
	{
		switch(rate.pre)       // Set the timer/counter prescaler according to the user input
	   {
		   case TC_PRE_1 :
		   {
				*table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
				*table.TCCR_B_ADDRESS |= (1 << CS0_BIT);
				#ifdef __AVR_AT90CAN128__
				*table.TCCR_A_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
				*table.TCCR_A_ADDRESS |= (1 << CS0_BIT);
				#endif
				return TC_CMD_ACK;
		   }
		   case TC_PRE_8 :
		   {
				*table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
				*table.TCCR_B_ADDRESS |= (1 << CS1_BIT);
				#ifdef __AVR_AT90CAN128__
				*table.TCCR_A_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
				*table.TCCR_A_ADDRESS |= (1 << CS1_BIT);
				#endif
				return TC_CMD_ACK;
		   }
		   case TC_PRE_32 :
		   {
				return TC_CMD_NAK;
		   }
		   case TC_PRE_64 :
		   {
			   *table.TCCR_B_ADDRESS &= ~(1 << CS2_BIT);
			   *table.TCCR_B_ADDRESS |= ((1 << CS1_BIT) | (1 << CS0_BIT));
			   #ifdef __AVR_AT90CAN128__
			   *table.TCCR_A_ADDRESS &= ~(1 << CS2_BIT);
			   *table.TCCR_A_ADDRESS |= ((1 << CS1_BIT) | (1 << CS0_BIT));
			   #endif
			   return TC_CMD_ACK;
		   }
		   case TC_PRE_128 :
		   {
				return TC_CMD_NAK;
		   }
		   case TC_PRE_256 :
		   {
			   *table.TCCR_B_ADDRESS &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			   *table.TCCR_B_ADDRESS |= ((1 << CS2_BIT));
			   #ifdef __AVR_AT90CAN128__
			   *table.TCCR_A_ADDRESS &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			   *table.TCCR_A_ADDRESS |= ((1 << CS2_BIT));
			   #endif
			   return TC_CMD_ACK;
		   }
		   case TC_PRE_1024:
		   {
			   *table.TCCR_B_ADDRESS &= ~(1 << CS1_BIT);
			   *table.TCCR_B_ADDRESS |= ((1 << CS2_BIT) | (1 << CS0_BIT));
			   #ifdef __AVR_AT90CAN128__
			   *table.TCCR_A_ADDRESS &= ~(1 << CS1_BIT);
			   *table.TCCR_A_ADDRESS |= ((1 << CS2_BIT) | (1 << CS0_BIT));
			   #endif
			   return TC_CMD_ACK;
		   }
		   default :
				return TC_CMD_NAK;
		}
	}
	#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
	else if (tc_number == TC_2)
	{
		switch(rate.pre)
	   {
		   case TC_PRE_1 :
		   {
				*table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
				*table.TCCR_B_ADDRESS |= (1 << CS0_BIT);
				#ifdef __AVR_AT90CAN128__
				*table.TCCR_A_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
				*table.TCCR_A_ADDRESS |= (1 << CS0_BIT);
				#endif
				return TC_CMD_ACK;
		   }
		   case TC_PRE_8 :
		   {
				*table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
				*table.TCCR_B_ADDRESS |= (1 << CS1_BIT);
				#ifdef __AVR_AT90CAN128__
				*table.TCCR_A_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
				*table.TCCR_A_ADDRESS |= (1 << CS1_BIT);
				#endif
				return TC_CMD_ACK;
		   }
		   case TC_PRE_32 :
		   {
			  	*table.TCCR_B_ADDRESS &= ~(1 << CS2_BIT);
			  	*table.TCCR_B_ADDRESS |= (1 << CS1_BIT);
			  	#ifdef __AVR_AT90CAN128__
			  	*table.TCCR_A_ADDRESS &= ~(1 << CS2_BIT);
			  	*table.TCCR_A_ADDRESS |= (1 << CS1_BIT);
				#endif
				return TC_CMD_ACK;
		   }
		   case TC_PRE_64 :
		   {
			   	*table.TCCR_B_ADDRESS &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			   	*table.TCCR_B_ADDRESS |= (1 << CS2_BIT);
			   	#ifdef __AVR_AT90CAN128__
			   	*table.TCCR_A_ADDRESS &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			   	*table.TCCR_A_ADDRESS |= (1 << CS2_BIT);
				#endif
			   	return TC_CMD_ACK;
		   }
		   case TC_PRE_128 :
		   {
			   	*table.TCCR_B_ADDRESS &= ~(1 << CS1_BIT);
			   	*table.TCCR_B_ADDRESS |= ((1 << CS2_BIT) | (1 << CS0_BIT));
				#ifdef __AVR_AT90CAN128__
			   	*table.TCCR_A_ADDRESS &= ~(1 << CS1_BIT);
			   	*table.TCCR_A_ADDRESS |= ((1 << CS2_BIT) | (1 << CS0_BIT));
				#endif
				return TC_CMD_ACK;
		   }
		   case TC_PRE_256 :
		   {
			   	*table.TCCR_B_ADDRESS &= ~(1 << CS0_BIT);
			   	*table.TCCR_B_ADDRESS |= ((1 << CS2_BIT) | (1 << CS1_BIT));
			   	#ifdef __AVR_AT90CAN128__
			   	*table.TCCR_A_ADDRESS &= ~(1 << CS0_BIT);
			   	*table.TCCR_A_ADDRESS |= ((1 << CS2_BIT) | (1 << CS1_BIT));
				#endif
			   	return TC_CMD_ACK;
		   }
		   	case TC_PRE_1024:
		   	{
			   	*table.TCCR_B_ADDRESS |= ((1 << CS2_BIT) | (1 << CS1_BIT) | (1 << CS0_BIT));
			   	#ifdef __AVR_AT90CAN128__
			   	*table.TCCR_A_ADDRESS |= ((1 << CS2_BIT) | (1 << CS1_BIT) | (1 << CS0_BIT));
				#endif
			   	return TC_CMD_ACK;
		   	}
		   	default :
		   	{
		   		return TC_CMD_NAK;
		   	}
		}
	}
	#endif
	return TC_CMD_NAK;
}

Tc_command_status start_16bit_timers (Tc_rate rate, Tc_registerTable table)
{
	switch(rate.pre)
	{
		case TC_PRE_1:
		{
			*table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT));
			*table.TCCR_B_ADDRESS |= (1 << CS0_BIT);
			return TC_CMD_ACK;
		}
		case TC_PRE_8:
		{
			*table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS0_BIT));
			*table.TCCR_B_ADDRESS |= (1 << CS1_BIT);
			return TC_CMD_ACK;
		}
		case TC_PRE_32:
		{
		  	return TC_CMD_NAK;
		}
		case TC_PRE_64:
		{
			*table.TCCR_B_ADDRESS &= ~(1 << CS2_BIT);
			*table.TCCR_B_ADDRESS |= ((1 << CS1_BIT) | (1 << CS0_BIT));
			return TC_CMD_ACK;
		}
		case TC_PRE_128:
		{
		  	return TC_CMD_NAK;
		}
		case TC_PRE_256:
		{
		  	*table.TCCR_B_ADDRESS &= (~(1 << CS1_BIT) & ~(1 << CS0_BIT));
		  	*table.TCCR_B_ADDRESS |= ((1 << CS2_BIT));
		  	return TC_CMD_ACK;
		}
		case TC_PRE_1024:
		{
		  	*table.TCCR_B_ADDRESS &= ~(1 << CS1_BIT);
		  	*table.TCCR_B_ADDRESS |= ((1 << CS2_BIT) | (1 << CS0_BIT));
		  	return TC_CMD_ACK;
		}
		default:
		{
			return TC_CMD_NAK;
		} /*Not a valid prescalar*/
	}
}

Tc_command_status enable_oc_8bit (Tc_number tc_number, Tc_oc_mode mode, Tc_registerTable table)
{
	switch (mode)
	{
		case TC_OC_NONE : // clears any waveform generation mode WGM2:0 = 0, TOP = 0xFF
		{
      /* Disable the output compare interrupt */
			*table.TIMSK_ADDRESS = 0x00;   // disable all interrupts

			#ifndef __AVR_AT90CAN128__
			if (tc_number == TC_0)
			{
				*table.TCCR_A_ADDRESS &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
				*table.TCCR_B_ADDRESS &= (~(1 << WGM2_BIT));
			}
			#elif defined (__AVR_ATmega2560__)
			else if (tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
				*table.TCCR_B_ADDRESS &= (~(1 << WGM2_BIT));
			}
			#endif

			#ifdef __AVR_AT90CAN128__
			if (tc_number == TC_0 || tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= (~(1 << WGM1_8BIT_BIT) & ~(1 << WGM0_8BIT_BIT));
			}
			#endif

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_1 :  // PWM, Phase Correct mode WGM2:0 = 1, TOP = 0xFF
		{
			#ifndef __AVR_AT90CAN128__
			if (tc_number == TC_0)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
        *table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);
        *table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			}
			#elif defined (__AVR_ATmega2560__)
			else if (tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
        *table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);
        *table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			}
			#endif

			#ifdef __AVR_AT90CAN128__
			if (tc_number == TC_0 || tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM1_8BIT_BIT);
				*table.TCCR_A_ADDRESS |= (1 << WGM0_8BIT_BIT);
			}
			#endif

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_2 :   // Clear Timer on Compare Match mode, WGM2:0 = 2, TOP = OCRnA
		{
			#ifndef __AVR_AT90CAN128__
			if (tc_number == TC_0)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM0_BIT);
				*table.TCCR_A_ADDRESS |= (1 << WGM1_BIT);
				*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			}
			#elif defined (__AVR_ATmega2560__)
			else if (tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM0_BIT);
				*table.TCCR_A_ADDRESS |= (1 << WGM1_BIT);
				*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			}
			#endif

			#ifdef __AVR_AT90CAN128__
			if (tc_number == TC_0 || tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM0_8BIT_BIT);
				*table.TCCR_A_ADDRESS |= (1 << WGM1_8BIT_BIT);
			}
			#endif

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_3 : // Fast PWM, WGM2:0 = 3, TOP = 0xFF
		{
			#ifndef __AVR_AT90CAN128__
			if (tc_number == TC_0)
			{
				/* Set WGMn2:0 bits to 0x03 for Fast PWM mode, where TOP = 0xFF */
				*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
				*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			}
			#elif defined (__AVR_ATmega2560__)
			else if (tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
				*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			}
			#endif

			#ifdef __AVR_AT90CAN128__
			if (tc_number == TC_0 || tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS |= ((1 << WGM1_8BIT_BIT) | (1 << WGM0_8BIT_BIT));
			}
			#endif

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_4 : // Reserved
		{
			return TC_CMD_NAK;
		}
		case TC_OC_MODE_5 : // PWM, Phase Correct operation mode, WGM2:0 = 5, TOP = OCRnA
		{
			#ifndef __AVR_AT90CAN128__
			if (tc_number == TC_0)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
				*table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);
				*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);
			}
			#elif defined (__AVR_ATmega2560__)
			else if (tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
				*table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);
				*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);
			}

			return TC_CMD_ACK;
			#endif
			#ifdef __AVR_AT90CAN128__
			return TC_CMD_NAK;
			#endif
		}
		case TC_OC_MODE_6 : // Reserved
		{
			return TC_CMD_NAK;
		}
		case TC_OC_MODE_7 : // Fast PWM, WGM2:0 = 7, TOP = OCRnA
		{
			#ifndef __AVR_AT90CAN128__
			if (tc_number == TC_0)
			{
				*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
				*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);
			}
			#elif defined (__AVR_ATmega2560__)
			else if (tc_number == TC_2)
			{
				*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
				*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);
			}

			return TC_CMD_ACK;
			#endif
			#ifdef __AVR_AT90CAN128__
			return TC_CMD_NAK;
			#endif
		}
		default :
		{
			return TC_CMD_NAK;
		}

	}
	return TC_CMD_NAK;
}
Tc_command_status enable_oc_16bit(Tc_oc_mode mode, Tc_registerTable table) //
{
	switch (mode)
	{
		case TC_OC_NONE : // Normal Operation, clears any waveform generation mode WGM2:0 = 0, TOP = 0xFFFF/ 0xFF
		{
      /* Disable the output compare interrupts */
      *table.TIMSK_ADDRESS = 0x00;

			/* Reset the timer counter mode back to NORMAL */
			*table.TCCR_A_ADDRESS &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
			*table.TCCR_B_ADDRESS &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_1 : // PWM 8-bit, Phase Correct mode WGM2:0 = 1, TOP = 0xFFFF/ 0xFF
		{
      *table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
			*table.TCCR_B_ADDRESS &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
			*table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_2 : // PWM 9-bit, Phase Correct mode WGM2:0 = 2, TOP = 0x01FF
		{
      *table.TCCR_A_ADDRESS &= ~(1 << WGM0_BIT);
			*table.TCCR_B_ADDRESS &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
			*table.TCCR_A_ADDRESS |= (1 << WGM1_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_3 : // PWM 10-bit, Phase Correct mode WGM2:0 = 3, TOP = 0x03FF
		{
      *table.TCCR_B_ADDRESS &= (~(1 << WGM3_BIT) & ~(1 << WGM2_BIT));
			*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_4 : // Clear Timer on Compare match mode, WGM2:0 = 4, TOP = OCRnA
		{
      *table.TCCR_A_ADDRESS &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
			*table.TCCR_B_ADDRESS &= ~(1 << WGM3_BIT);
			*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_5 : // Fast PWM 8-bit, WGM2:0 = 5, TOP = 0x00FF
		{
      *table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
			*table.TCCR_B_ADDRESS &= ~(1 << WGM3_BIT);
			*table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);
			*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_6 : // Fast PWM 9-bit, WGM2:0 = 6, TOP = 0x01FF
		{
      *table.TCCR_A_ADDRESS &= ~(1 << WGM0_BIT);
			*table.TCCR_B_ADDRESS &= ~(1 << WGM3_BIT);
			*table.TCCR_A_ADDRESS |= (1 << WGM1_BIT);
			*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_7 : // Fast PWM 10-bit, WGM2:0 = 7, TOP = 0x03FF
		{
      *table.TCCR_B_ADDRESS &= ~(1 << WGM3_BIT);
			*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));
			*table.TCCR_B_ADDRESS |= (1 << WGM2_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_8 : // PWM, Phase and Frequency Correct mode WGM2:0 = 8, TOP = ICRn
		{
      *table.TCCR_A_ADDRESS &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
			*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			*table.TCCR_B_ADDRESS |= (1 << WGM3_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_9 : // PWM, Phase and Frequency Correct mode WGM2:0 = 9, TOP = OCRnA
		{
      *table.TCCR_A_ADDRESS &= ~(1 << WGM1_BIT);
			*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			*table.TCCR_A_ADDRESS |= (1 << WGM0_BIT);
      *table.TCCR_B_ADDRESS |= (1 << WGM3_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_10 : // PWM, Phase Correct mode WGM2:0 = 10, TOP = ICRn
		{
      *table.TCCR_A_ADDRESS &= ~(1 << WGM0_BIT);
			*table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			*table.TCCR_B_ADDRESS |= (1 << WGM3_BIT);
			*table.TCCR_A_ADDRESS |= (1 << WGM1_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_11 : // PWM, Phase Correct mode WGM2:0 = 11, TOP = OCRnA
		{
      *table.TCCR_B_ADDRESS &= ~(1 << WGM2_BIT);
			*table.TCCR_B_ADDRESS |= (1 << WGM3_BIT);
			*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_12 : // Clear Timer on Compare match mode, WGM2:0 = 12, TOP = ICRnA
		{
      *table.TCCR_A_ADDRESS &= (~(1 << WGM1_BIT) & ~(1 << WGM0_BIT));
			*table.TCCR_B_ADDRESS |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_13 : // Reserved
		{
			return TC_CMD_NAK;
		}
		case TC_OC_MODE_14 : // Fast PWM, WGM2:0 = 14, TOP = ICRn
		{
      *table.TCCR_A_ADDRESS &= (1 << WGM0_BIT);
			*table.TCCR_B_ADDRESS |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
			*table.TCCR_A_ADDRESS |= (1 << WGM1_BIT);

			return TC_CMD_ACK;
		}
		case TC_OC_MODE_15 : // Fast PWM, WGM2:0 = 15, TOP = OCRnA
		{
			*table.TCCR_B_ADDRESS |= ((1 << WGM3_BIT) | (1 << WGM2_BIT));
			*table.TCCR_A_ADDRESS |= ((1 << WGM1_BIT) | (1 << WGM0_BIT));

			return TC_CMD_ACK;
		}
		default : // something went seriously wrong
		{
			return TC_CMD_NAK;
		}
	}
	return TC_CMD_NAK;
}

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

// Tc public function implementation

Tc::Tc(Tc_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

Tc::Tc(Tc_number timer)
{
	switch (timer)
	{
		case TC_0:
		{
			static Tc_registerTable imp_register_table;

			// Initialize the register addresses.
			imp_register_table.TIMSK_ADDRESS = &TIMSK0_ADDRESS;
			imp_register_table.TCCR_A_ADDRESS = &TCCR0A_ADDRESS;

			#ifndef __AVR_AT90CAN128__
			imp_register_table.TCCR_B_ADDRESS = &TCCR0B_ADDRESS;
			#endif

			imp_register_table.OCR_A_ADDRESS.as_8bit = &OCR0A_ADDRESS;
			imp_register_table.OCR_B_ADDRESS.as_8bit = &OCR0B_ADDRESS;
			imp_register_table.TCNT_ADDRESS.as_8bit = &TCNT0_ADDRESS;

			static Tc_imp tc_0(TC_0, TC_8BIT, imp_register_table);
			imp = &tc_0;

			break;
		}
		case TC_1:
		{
			static Tc_registerTable imp_register_table;

			imp_register_table.TIMSK_ADDRESS = &TIMSK1_ADDRESS;
			imp_register_table.TCCR_A_ADDRESS = &TCCR1A_ADDRESS;
			imp_register_table.TCCR_B_ADDRESS = &TCCR1B_ADDRESS;
			imp_register_table.TCCR_C_ADDRESS = &TCCR1C_ADDRESS;
			imp_register_table.OCR_A_ADDRESS.as_16bit = &OCR1A_ADDRESS;
			imp_register_table.OCR_B_ADDRESS.as_16bit = &OCR1B_ADDRESS;
			imp_register_table.OCR_C_ADDRESS.as_16bit = &OCR1C_ADDRESS;
			imp_register_table.ICR_ADDRESS = &ICR1_ADDRESS;
			imp_register_table.TCNT_ADDRESS.as_16bit = &TCNT1_ADDRESS;

			static Tc_imp tc_1(TC_1, TC_16BIT, imp_register_table);
			imp = &tc_1;

			break;
		}
		#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
		case TC_2:
		{
			static Tc_registerTable imp_register_table;


			imp_register_table.TIMSK_ADDRESS = &TIMSK2_ADDRESS;
			imp_register_table.TCCR_A_ADDRESS = &TCCR2A_ADDRESS;

			#ifndef __AVR_AT90CAN128__
			imp_register_table.TCCR_B_ADDRESS = &TCCR2B_ADDRESS;
			#endif

			imp_register_table.OCR_A_ADDRESS.as_8bit = &OCR2A_ADDRESS;
			imp_register_table.OCR_B_ADDRESS.as_8bit = &OCR2B_ADDRESS;
			imp_register_table.TCNT_ADDRESS.as_8bit = &TCNT2_ADDRESS;

			static Tc_imp tc_2(TC_2, TC_8BIT, imp_register_table);
			imp = &tc_2;

			break;
		}
		case TC_3:
		{
			static Tc_registerTable imp_register_table;

			imp_register_table.TIMSK_ADDRESS = &TIMSK3_ADDRESS;
			imp_register_table.TCCR_A_ADDRESS = &TCCR3A_ADDRESS;
			imp_register_table.TCCR_B_ADDRESS = &TCCR3B_ADDRESS;
			imp_register_table.OCR_A_ADDRESS.as_16bit = &OCR3A_ADDRESS;
			imp_register_table.OCR_B_ADDRESS.as_16bit = &OCR3B_ADDRESS;
			imp_register_table.OCR_C_ADDRESS.as_16bit = &OCR3C_ADDRESS;
			imp_register_table.ICR_ADDRESS = &ICR3_ADDRESS;
			imp_register_table.TCNT_ADDRESS.as_16bit = &TCNT3_ADDRESS;

			static Tc_imp tc_3(TC_3, TC_16BIT, imp_register_table);
			imp = &tc_3;

			break;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
			static Tc_registerTable imp_register_table;

			imp_register_table.TIMSK_ADDRESS = &TIMSK4_ADDRESS;
			imp_register_table.TCCR_A_ADDRESS = &TCCR4A_ADDRESS;
			imp_register_table.TCCR_B_ADDRESS = &TCCR4B_ADDRESS;
			imp_register_table.OCR_A_ADDRESS.as_16bit = &OCR4A_ADDRESS;
			imp_register_table.OCR_B_ADDRESS.as_16bit = &OCR4B_ADDRESS;
			imp_register_table.OCR_C_ADDRESS.as_16bit = &OCR4C_ADDRESS;
			imp_register_table.ICR_ADDRESS = &ICR4_ADDRESS;
			imp_register_table.TCNT_ADDRESS.as_16bit = &TCNT4_ADDRESS;

			static Tc_imp tc_4(TC_4, TC_16BIT, imp_register_table);
			imp = &tc_4;

			break;
		}
		case TC_5:
		{
			static Tc_registerTable imp_register_table;

			imp_register_table.TIMSK_ADDRESS = &TIMSK5_ADDRESS;
			imp_register_table.TCCR_A_ADDRESS = &TCCR5A_ADDRESS;
			imp_register_table.TCCR_B_ADDRESS = &TCCR5B_ADDRESS;
			imp_register_table.OCR_A_ADDRESS.as_16bit = &OCR5A_ADDRESS;
			imp_register_table.OCR_B_ADDRESS.as_16bit = &OCR5B_ADDRESS;
			imp_register_table.OCR_C_ADDRESS.as_16bit = &OCR5C_ADDRESS;
			imp_register_table.ICR_ADDRESS = &ICR5_ADDRESS;
			imp_register_table.TCNT_ADDRESS.as_16bit = &TCNT5_ADDRESS;

			static Tc_imp tc_5(TC_5, TC_16BIT, imp_register_table);
			imp = &tc_5;

			break;
		}
		#endif
		default:
		{
			// If we end up here, something terrible has happened.
			imp = NULL;
			break;
		}
	}

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

Tc_command_status Tc::enable_tov_interrupt(IsrHandler callback)
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

Tc_command_status Tc::enable_oc_interrupt(Tc_oc_channel channel, IsrHandler callback)
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

Tc_command_status Tc::enable_ic_interrupt(Tc_ic_channel channel, IsrHandler callback)
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

/**************************************************************************************************/
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).


/**
 * Tc_imp private class functions
 **/
Tc_imp::Tc_imp(Tc_number timer, Tc_timer_size size,  Tc_registerTable registers)
{
	// Record which peripheral we are abstracting.
	timer_number = timer;

	// Record what register size this timer uses.
	timer_size = size;

	imp_register_table = registers;

	// All done.
	return;
}

Tc_imp::~Tc_imp(void)
{
	return;
}

Tc_command_status Tc_imp::initialise(void) //
{
  // Map the output/ input compare pins of the Timer/counter.
	#ifdef __AVR_ATmega2560__
	switch (timer_number)
	{
		case TC_0 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC0_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC0_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC0_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC0_OC_B_PIN;

			return TC_CMD_ACK;
		}
		case TC_1 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC1_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC1_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC1_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC1_OC_B_PIN;
			pin_address[TC_OC_CHANNEL_C].address.port = TC1_OC_C_PORT;
			pin_address[TC_OC_CHANNEL_C].address.pin = TC1_OC_C_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC1_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC1_IC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_2 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC2_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC2_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC2_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC2_OC_B_PIN;

			return TC_CMD_ACK;
		}
		case TC_3 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC3_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC3_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC3_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC3_OC_B_PIN;
			pin_address[TC_OC_CHANNEL_C].address.port = TC3_OC_C_PORT;
			pin_address[TC_OC_CHANNEL_C].address.pin = TC3_OC_C_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC3_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC3_IC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_4 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC4_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC4_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC4_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC4_OC_B_PIN;
			pin_address[TC_OC_CHANNEL_C].address.port = TC4_OC_C_PORT;
			pin_address[TC_OC_CHANNEL_C].address.pin = TC4_OC_C_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC4_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC4_IC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_5 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC5_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC5_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC5_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC5_OC_B_PIN;
			pin_address[TC_OC_CHANNEL_C].address.port = TC5_OC_C_PORT;
			pin_address[TC_OC_CHANNEL_C].address.pin = TC5_OC_C_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC5_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC5_IC_A_PIN;

			return TC_CMD_ACK;
		}
	}

	#elif defined (__AVR_AT90CAN128__)

	switch (timer_number)
	{
		case TC_0 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC0_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC0_OC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_1 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC1_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC1_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC1_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC1_OC_B_PIN;
			pin_address[TC_OC_CHANNEL_C].address.port = TC1_OC_C_PORT;
			pin_address[TC_OC_CHANNEL_C].address.pin = TC1_OC_C_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC1_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC1_IC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_2 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC2_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC2_OC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_3 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC3_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC3_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC3_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC3_OC_B_PIN;
			pin_address[TC_OC_CHANNEL_C].address.port = TC3_OC_C_PORT;
			pin_address[TC_OC_CHANNEL_C].address.pin = TC3_OC_C_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC3_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC3_IC_A_PIN;

			return TC_CMD_ACK;
		}
		default :
		{
			return TC_CMD_NAK;
		}
	}

	#elif defined (__AVR_ATmega64M1__) || defined (__AVR_ATmega64C1__)

	switch (timer_number)
	{
		case TC_0 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC0_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC0_OC_A_PIN;

			return TC_CMD_ACK;
		}
		case TC_1 :
		{
			pin_address[TC_OC_CHANNEL_A].address.port = TC1_OC_A_PORT;
			pin_address[TC_OC_CHANNEL_A].address.pin = TC1_OC_A_PIN;
			pin_address[TC_OC_CHANNEL_B].address.port = TC1_OC_B_PORT;
			pin_address[TC_OC_CHANNEL_B].address.pin = TC1_OC_B_PIN;
			pin_address[TC_IC_CHANNEL_A].address.port = TC1_IC_A_PORT;
			pin_address[TC_IC_CHANNEL_A].address.pin = TC1_IC_A_PIN;
			pin_address[TC_IC_CHANNEL_B].address.port = TC1_IC_B_PORT;
			pin_address[TC_IC_CHANNEL_B].address.pin = TC1_IC_B_PIN;

			return TC_CMD_ACK;
		}
		default :
		{
			return TC_CMD_NAK;
		}
	}

	#endif

	return TC_CMD_NAK;

	// All done
}

void Tc_imp::enable_interrupts(void)
{
	// TODO - This.

	/**
	*
  * Seems pointless to have a master interrupt function of the TC.
  * Would make sense to have a master disable all TC interrupts though.
  *
  * A master interrupt function.
	*
	**/
}

void Tc_imp::disable_interrupts(void)
{
	// TODO - This.

  // Takes away all TC interrupts.

  *imp_register_table.TIMSK_ADDRESS = 0x00;
	// NOTE	-	Style change required. Keep the different MCUs in separate chunks of code
	switch(timer_number)
	{
	 	case TC_0:
	 	{
        #ifdef __AVR_AT90CAN128__
        timerInterrupts[TIMER0_COMP_int] = NULL;
        #else
        timerInterrupts[TIMER0_COMPA_int] = NULL;
        timerInterrupts[TIMER0_COMPB_int] = NULL;
        #endif

	   		/*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
	   		timerInterrupts[TIMER0_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	case TC_1:
	 	{
        timerInterrupts[TIMER1_COMPA_int] = NULL;
        timerInterrupts[TIMER1_COMPB_int] = NULL;
        #if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
        timerInterrupts[TIMER1_COMPC_int] = NULL;
        #endif
        timerInterrupts[TIMER1_CAPT_int] = NULL;
	  		timerInterrupts[TIMER1_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
	 	case TC_2:
	 	{
        #ifdef __AVR_AT90CAN128__
        timerInterrupts[TIMER2_COMP_int] = NULL;
        #elif defined (__AVR_ATmega2560__)
        timerInterrupts[TIMER2_COMPA_int] = NULL;
        timerInterrupts[TIMER2_COMPB_int] = NULL;
        #endif
	   		timerInterrupts[TIMER2_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	case TC_3:
	 	{
        timerInterrupts[TIMER3_COMPA_int] = NULL;
        timerInterrupts[TIMER3_COMPB_int] = NULL;
        timerInterrupts[TIMER3_COMPC_int] = NULL;
        timerInterrupts[TIMER3_CAPT_int] = NULL;
	   		timerInterrupts[TIMER3_OVF_int] = NULL;
	   		return TC_CMD_ACK;
		}
		#endif
		#ifdef __AVR_ATmega2560__
	 	case TC_4:
	 	{
        timerInterrupts[TIMER4_COMPA_int] = NULL;
        timerInterrupts[TIMER4_COMPB_int] = NULL;
        timerInterrupts[TIMER4_COMPC_int] = NULL;
        timerInterrupts[TIMER4_CAPT_int] = NULL;
	   		timerInterrupts[TIMER4_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	case TC_5:
	 	{
        timerInterrupts[TIMER5_COMPA_int] = NULL;
        timerInterrupts[TIMER5_COMPB_int] = NULL;
        timerInterrupts[TIMER5_COMPC_int] = NULL;
        timerInterrupts[TIMER5_CAPT_int] = NULL;
	   		timerInterrupts[TIMER5_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	#endif
	 	default :
	 	{
	 		return TC_CMD_NAK;
	 	}
	}
}

Tc_command_status Tc_imp::set_rate(Tc_rate rate)
{
	switch (timer_number)
	{
		case TC_0:
		{
			// These prescalers are only available to the asynchronous TC
			if ( (rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128) )
			{
				return TC_CMD_NAK;
			}
			imp_rate.pre = rate.pre;
			imp_rate.src = TC_SRC_INT;
			return TC_CMD_ACK;
		}
		case TC_1:
		{
			if ( (rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128) )
			{
				return TC_CMD_NAK;
			}
			imp_rate.pre = rate.pre;
			imp_rate.src = TC_SRC_INT;
			return TC_CMD_ACK;
		}
		#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
		case TC_2:
		{
			imp_rate.pre = rate.pre;
			imp_rate.src = TC_SRC_INT;
			return TC_CMD_ACK;
		}
		case TC_3:
		{
			if ( (rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128) )
			{
				return TC_CMD_NAK;
			}
			imp_rate.pre = rate.pre;
			imp_rate.src = TC_SRC_INT;
			return TC_CMD_ACK;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
			if ( (rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128) )
			{
				return TC_CMD_NAK;
			}
			imp_rate.pre = rate.pre;
			imp_rate.src = TC_SRC_INT;
			return TC_CMD_ACK;
		}
		case TC_5:
		{
			if ( (rate.pre == TC_PRE_32) || (rate.pre == TC_PRE_128) )
			{
				return TC_CMD_NAK;
			}
			imp_rate.pre = rate.pre;
			imp_rate.src = TC_SRC_INT;
			return TC_CMD_ACK;
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}

	// All done
}

Tc_command_status Tc_imp::load_timer_value(Tc_value value)
{
	switch (timer_number) // Loads the user assigned value into the TC counter register
	{
		case TC_0:
		{
			*imp_register_table.TCNT_ADDRESS.as_8bit = value.value.as_8bit;
			return TC_CMD_ACK;
		}
		case TC_1:
		{
			*imp_register_table.TCNT_ADDRESS.as_16bit = value.value.as_16bit;
			return TC_CMD_ACK;
		}

		#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
		case TC_2:
		{
			*imp_register_table.TCNT_ADDRESS.as_8bit = value.value.as_8bit;
			return TC_CMD_ACK;
		}
		case TC_3:
		{
			*imp_register_table.TCNT_ADDRESS.as_16bit = value.value.as_16bit;
			return TC_CMD_ACK;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
			*imp_register_table.TCNT_ADDRESS.as_16bit = value.value.as_16bit;
			return TC_CMD_ACK;
		}
		case TC_5:
		{
			*imp_register_table.TCNT_ADDRESS.as_16bit = value.value.as_16bit;
			return TC_CMD_ACK;
		}
		#endif
		default:
		{
			return TC_CMD_NAK;
		}
	}
	return TC_CMD_NAK;

	// All Done
}

Tc_value Tc_imp::get_timer_value(void)
{
	switch (timer_number) // Grabs the content of the user defined TC counter register.
	{
		case TC_0:
		{
			return Tc_value::from_uint8(*imp_register_table.TCNT_ADDRESS.as_8bit);
		}
		case TC_1:
		{
			return Tc_value::from_uint16(*imp_register_table.TCNT_ADDRESS.as_16bit);
		}

		#if defined  (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
		case TC_2:
		{
			return Tc_value::from_uint8(*imp_register_table.TCNT_ADDRESS.as_8bit);
		}
		case TC_3:
		{
			return Tc_value::from_uint16(*imp_register_table.TCNT_ADDRESS.as_16bit);
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
			return Tc_value::from_uint16(*imp_register_table.TCNT_ADDRESS.as_16bit);
		}
		case TC_5:
		{
			return Tc_value::from_uint16(*imp_register_table.TCNT_ADDRESS.as_16bit);
		}
		#endif
		default:
		{
			return Tc_value::from_uint8(0);
		}
	}
	return Tc_value::from_uint8(0);

	// All done
}

Tc_command_status Tc_imp::start(void)
{
   switch(timer_size)
   {
	 	case TC_16BIT:
	 	{
	     /*edit the TCCR0B registers for the 16bit Timer/Counters */
		   	if (imp_rate.src == TC_SRC_INT)
		   	{
				    return start_16bit_timers(imp_rate, imp_register_table);
			  }
			  else
        {} // if we ever have an external clock source
	 	}
	 	case TC_8BIT:
	 	{
	     /*edit the TCCRA or TCCRB registers for the 8bit Timer/Counters */
		   	if (imp_rate.src == TC_SRC_INT)
		   	{
            return start_8bit_timers(timer_number, imp_rate, imp_register_table);
        }
        else
        {} // if we ever have an external clock source
    }
	}
	return TC_CMD_NAK;

	// All done
}

Tc_command_status Tc_imp::stop(void)
{
	#ifndef __AVR_AT90CAN128__
	*imp_register_table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
	return TC_CMD_ACK;

	#endif
	#ifdef __AVR_AT90CAN128__
	switch (timer_number)
	{
		case TC_0 :
		{
			*imp_register_table.TCCR_A_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			return TC_CMD_ACK;
		}
		case TC_1 :
		{
			*imp_register_table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			return TC_CMD_ACK;
		}
		case TC_2 :
		{
			*imp_register_table.TCCR_A_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			return TC_CMD_ACK;
		}
		case TC_3 :
		{
			*imp_register_table.TCCR_B_ADDRESS &= (~(1 << CS2_BIT) & ~(1 << CS1_BIT) & ~(1 << CS0_BIT));
			return TC_CMD_ACK;
		}
		default :
		{
			return TC_CMD_NAK;
		}
	}
	#endif
	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::enable_tov_interrupt(IsrHandler callback)
{
   	switch(timer_number)
  	{
		case TC_0:
		{
			timerInterrupts[TIMER0_OVF_int] = callback;
			*imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
			return TC_CMD_ACK;
		}
		case TC_1:
		{
			timerInterrupts[TIMER1_OVF_int] = callback;
			*imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
			return TC_CMD_ACK;
		}
		#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
		case TC_2:
		{
			timerInterrupts[TIMER2_OVF_int] = callback;
			*imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
			return TC_CMD_ACK;
		}
		case TC_3:
		{
			timerInterrupts[TIMER3_OVF_int] = callback;
			*imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
			return TC_CMD_ACK;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
			timerInterrupts[TIMER4_OVF_int] = callback;
			*imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
			return TC_CMD_ACK;
		}
		case TC_5:
		{
			timerInterrupts[TIMER5_OVF_int] = callback;
			*imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
			return TC_CMD_ACK;
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}
	return TC_CMD_NAK;

	// All done
}

Tc_command_status Tc_imp::disable_tov_interrupt(void)
{
	*imp_register_table.TIMSK_ADDRESS &= ~(1 << TOIE_BIT);
	switch(timer_number)
	{
	 	case TC_0:
	 	{
	   		/*replace ISR pointer in timerInterrupts array with NULL to prevent an ISR firing (just in case)*/
	   		timerInterrupts[TIMER0_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	case TC_1:
	 	{
	  		timerInterrupts[TIMER1_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
	 	case TC_2:
	 	{
	   		timerInterrupts[TIMER2_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	case TC_3:
	 	{
	   		timerInterrupts[TIMER3_OVF_int] = NULL;
	   		return TC_CMD_ACK;
		}
		#endif
		#ifdef __AVR_ATmega2560__
	 	case TC_4:
	 	{
	   		timerInterrupts[TIMER4_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	case TC_5:
	 	{
	   		timerInterrupts[TIMER5_OVF_int] = NULL;
	   		return TC_CMD_ACK;
	 	}
	 	#endif
	 	default :
	 	{
	 		return TC_CMD_NAK;
	 	}
	}
	return TC_CMD_NAK;
	// All done
}

Tc_command_status Tc_imp::enable_oc(Tc_oc_mode mode)
{
  waveform_mode = mode;

  // I need to enable TOV and OCnx interrupt pins here, where appropriate

	switch (timer_size)
	{
		case TC_16BIT :
		{
			if (enable_oc_16bit(mode, imp_register_table) == TC_CMD_NAK)
      {
        return TC_CMD_NAK;
      }
      if (mode != TC_OC_MODE_13 || mode != TC_OC_MODE_12 || mode != TC_OC_MODE_4 || mode != TC_OC_NONE)
      {
        *imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
        return TC_CMD_ACK;
      }
		}
		case TC_8BIT :
		{
			if (enable_oc_8bit(timer_number, mode, imp_register_table) == TC_CMD_NAK)
      {
        return TC_CMD_NAK;
      }
      if (mode % 2 == 1) // PWM modes require Timer Overflow Interrupt mask to be enabled.
      {
        *imp_register_table.TIMSK_ADDRESS |= (1 << TOIE_BIT);
        return TC_CMD_ACK;
      }
		}
		default :
		{
			return TC_CMD_NAK;
		}
	}
}

Tc_command_status Tc_imp::enable_oc_channel(Tc_oc_channel channel, Tc_oc_channel_mode mode)
{
  Gpio_pin pins(pin_address[channel].address);
  if (pins.set_mode(GPIO_OUTPUT_PP) == GPIO_ERROR)
  {
    return TC_CMD_NAK;
  }

	#ifdef __AVR_AT90CAN128__
	switch (mode)
	{
		case TC_OC_CHANNEL_MODE_0 : // Normal Port Operation mode (Pins disconnected)
		{
      *imp_register_table.TIMSK_ADDRESS = 0x00; // make sure all interrupts are disabled

			if (timer_number != TC_0 || timer_number != TC_2)
			{
				*imp_register_table.TCCR_A_ADDRESS &= (~(1 << ( COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) & ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
			}
			else if (timer_number == TC_0 || timer_number == TC_2)
			{
				if (channel != TC_OC_A)
				{
					return TC_CMD_NAK;
				}
				*imp_register_table.TCCR_A_ADDRESS &= (~(1 << COMA1_8BIT_BIT) & ~(1 << COMA0_8BIT_BIT));
			}
			return TC_CMD_ACK;
		}
		case TC_OC_CHANNEL_MODE_1 :
		{
			if (timer_number != TC_0 || timer_number != TC_2)
			{
				*imp_register_table.TCCR_A_ADDRESS &= ~( 1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
				*imp_register_table.TCCR_A_ADDRESS |= (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
			}
			else if (timer_number == TC_0 || timer_number == TC_2)
			{
				if (channel != TC_OC_A)
				{
					return TC_CMD_NAK;
				}
				*imp_register_table.TCCR_A_ADDRESS &= ~(1 << COMA1_8BIT_BIT);
				*imp_register_table.TCCR_A_ADDRESS |= (1 << COMA0_8BIT_BIT);
			}

			return TC_CMD_ACK;
		}
		case TC_OC_CHANNEL_MODE_2 :
		{
			if (timer_number != TC_0 || timer_number != TC_2)
			{
				*imp_register_table.TCCR_A_ADDRESS |= (1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
				*imp_register_table.TCCR_A_ADDRESS &= ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
			}
			else if (timer_number == TC_0 || timer_number == TC_2)
			{
				if (channel != TC_OC_A)
				{
					return TC_CMD_NAK;
				}
				*imp_register_table.TCCR_A_ADDRESS |= (1 << COMA1_8BIT_BIT);
				*imp_register_table.TCCR_A_ADDRESS &= ~(1 << COMA0_8BIT_BIT);
			}
			return TC_CMD_ACK;
		}
		case TC_OC_CHANNEL_MODE_3 :
		{
			if (timer_number != TC_0 || timer_number != TC_2)
			{
				*imp_register_table.TCCR_A_ADDRESS |= ((1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) | (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
			}
			else if (timer_number == TC_0 || timer_number == TC_2)
			{
				if (channel != TC_OC_A)
				{
					return TC_CMD_NAK;
				}
				*imp_register_table.TCCR_A_ADDRESS |= ((1 << COMA1_8BIT_BIT) | (1 << COMA0_8BIT_BIT));
			}

			return TC_CMD_ACK;
		}
		default :
		{
			return TC_CMD_NAK;
		}
	}

	#else
	switch (mode)
	{
		case TC_OC_CHANNEL_MODE_0 :
		{
			*imp_register_table.TCCR_A_ADDRESS &= (~(1 << ( COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) & ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
			return TC_CMD_ACK;
		}
		case TC_OC_CHANNEL_MODE_1 :
		{
			*imp_register_table.TCCR_A_ADDRESS &= ~( 1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
			*imp_register_table.TCCR_A_ADDRESS |= (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
			return TC_CMD_ACK;
		}
		case TC_OC_CHANNEL_MODE_2 :
		{
			*imp_register_table.TCCR_A_ADDRESS |= (1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel));
			*imp_register_table.TCCR_A_ADDRESS &= ~(1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel));
			return TC_CMD_ACK;
		}
		case TC_OC_CHANNEL_MODE_3 :
		{
			*imp_register_table.TCCR_A_ADDRESS |= ((1 << (COMA1_BIT - COM_BIT_OFFSET * (int8_t)channel)) | (1 << (COMA0_BIT - COM_BIT_OFFSET * (int8_t)channel)));
			return TC_CMD_ACK;
		}
		default :
		{
			return TC_CMD_NAK;
		}
	}
	#endif
	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::enable_oc_interrupt(Tc_oc_channel channel, IsrHandler callback)
{
	switch (timer_number)
	{
		case TC_0:
		{
			switch (channel)
			{
				case TC_OC_A:
				{
					#ifdef __AVR_AT90CAN128__
					timerInterrupts[TIMER0_COMP_int] = callback;
					#else
					timerInterrupts[TIMER0_COMPA_int] = callback;
					#endif
					break;
				}
				case TC_OC_B:
				{
					#ifdef __AVR_AT90CAN128__
					return TC_CMD_NAK;
					#else
					timerInterrupts[TIMER0_COMPB_int] = callback;
					#endif
					break;
				}
				#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
				case TC_OC_C :
				{
					return TC_CMD_NAK;
				}
				#endif
				default:
				{
					return TC_CMD_NAK;
				}
			}
			break;
		}
		case TC_1:
		{
			switch (channel)
			{
				case TC_OC_A:
				{
					timerInterrupts[TIMER1_COMPA_int] = callback;
					break;
				}
				case TC_OC_B:
				{
					timerInterrupts[TIMER1_COMPB_int] = callback;
					break;
				}
				#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
				case TC_OC_C:
				{
					timerInterrupts[TIMER1_COMPC_int] = callback;
					break;
				}
				#endif
				default :
				{
					return TC_CMD_NAK;
				}
			}
			break;
		}
		#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
		case TC_2:
		{
			switch (channel)
			{
				case TC_OC_A:
				{
					#ifdef __AVR_AT90CAN128__
					timerInterrupts[TIMER2_COMP_int] = callback;
					#else
					timerInterrupts[TIMER2_COMPA_int] = callback;
					#endif
					break;
				}
				case TC_OC_B:
				{
					#ifdef __AVR_ATmega2560__
					timerInterrupts[TIMER2_COMPB_int] = callback;
					#elif defined (__AVR_AT90CAN128__)
					return TC_CMD_NAK;
					#endif
					break;
				}
				case TC_OC_C:
				{
					return TC_CMD_NAK;
				}
				default:
				{
					return TC_CMD_NAK;
				}
			}
			break;
		}
		case TC_3:
		{
			switch (channel)
			{
				case TC_OC_A:
				{
					timerInterrupts[TIMER3_COMPA_int] = callback;
					break;
				}
				case TC_OC_B:
				{
					timerInterrupts[TIMER3_COMPB_int] = callback;
					break;
				}
				case TC_OC_C:
				{
					timerInterrupts[TIMER3_COMPC_int] = callback;
					break;
				}
				default :
				{
					return TC_CMD_NAK;
				}
			}
			break;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
			switch (channel)
			{
				case TC_OC_A:
				{
					timerInterrupts[TIMER4_COMPA_int] = callback;
					break;
				}
				case TC_OC_B:
				{
					timerInterrupts[TIMER4_COMPB_int] = callback;
					break;
				}
				case TC_OC_C:
				{
					timerInterrupts[TIMER4_COMPC_int] = callback;
					break;
				}
				default :
				{
					return TC_CMD_NAK;
				}
			}
			break;
		}
		case TC_5:
		{
			switch (channel)
			{
				case TC_OC_A:
				{
					timerInterrupts[TIMER5_COMPA_int] = callback;
					break;
				}
				case TC_OC_B:
				{
					timerInterrupts[TIMER5_COMPB_int] = callback;
					break;
				}
				case TC_OC_C:
				{
					timerInterrupts[TIMER5_COMPC_int] = callback;
					break;
				}
				default :
				{
					return TC_CMD_NAK;
				}
			}
			break;
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}

	/*
   * Switch ON the output compare interrupt to enable based on which channel is provided
   */
  if (channel == TC_OC_A)
	{
		*imp_register_table.TIMSK_ADDRESS |= (1 << OCIEA_BIT);
		return TC_CMD_ACK;
	}
	else if(channel == TC_OC_B)
	{
		*imp_register_table.TIMSK_ADDRESS |= (1 << OCIEB_BIT);
		return TC_CMD_ACK;
	}
	#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
	else if (channel == TC_OC_C)
	{
		*imp_register_table.TIMSK_ADDRESS |= (1 << OCIEC_BIT);
		return TC_CMD_ACK;
	}
	#endif

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::disable_oc_interrupt(Tc_oc_channel channel)
{
  *imp_register_table.TIMSK_ADDRESS &= ~(1 << TOIE_BIT);

  	switch (channel)
  	{
    	case TC_OC_A:
    	{
      		*imp_register_table.TIMSK_ADDRESS &= ~(1 << OCIEA_BIT);
      		break;
    	}
    	case TC_OC_B:
    	{
      		*imp_register_table.TIMSK_ADDRESS &= ~(1 << OCIEB_BIT);
      		break;
    	}
    	#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
    	case TC_OC_C:
    	{
      		*imp_register_table.TIMSK_ADDRESS &= ~(1 << OCIEC_BIT);
      		break;
    	}
    	#endif
    	default :
    	{
    		return TC_CMD_NAK;
    	}
  	}

    switch (timer_number)
    {
    	case TC_0 :
    	{
    		switch (channel)
    		{
    			case TC_OC_A :
    			{
    				#ifdef __AVR_AT90CAN128__
    				timerInterrupts[TIMER0_COMP_int] = NULL;
    				#else
    				timerInterrupts[TIMER0_COMPA_int] = NULL;
    				#endif
    				break;
    			}
    			case TC_OC_B :
    			{
    				#ifdef __AVR_AT90CAN128__
    				return TC_CMD_NAK;
    				#else
    				timerInterrupts[TIMER0_COMPB_int] = NULL;
    				break;
    				#endif
    			}
    			#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
    			case TC_OC_C :
    			{
    				return TC_CMD_NAK;
    			}
    			#endif
    			default :
    			{
    				return TC_CMD_NAK;
    			}
    		}
    		break;
    	}
    	case TC_1 :
    	{
    		switch (channel)
    		{
    			case TC_OC_A :
    			{
    				 timerInterrupts[TIMER1_COMPA_int] = NULL;
    				 break;
    			}
    			case TC_OC_B :
    			{
    				timerInterrupts[TIMER1_COMPB_int] = NULL;
    				break;
    			}
    			#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
    			case TC_OC_C :
    			{
    				timerInterrupts[TIMER1_COMPC_int] = NULL;
    				break;
    			}
    			#endif
    			default :
    			{
    				return TC_CMD_NAK;
    			}
    		}
    		break;
    	}
    	#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
    	case TC_2 :
    	{
    		switch (channel)
    		{
    			case TC_OC_A :
    			{
    				#ifdef __AVR_AT90CAN128__
    				timerInterrupts[TIMER2_COMP_int] = NULL;
    				#elif defined (__AVR_ATmega2560__)
    				timerInterrupts[TIMER2_COMPA_int] = NULL;
    				break;
    				#endif
    			}
    			case TC_OC_B :
    			{
    				#ifdef __AVR_AT90CAN128__
    				return TC_CMD_NAK;
    				#elif defined (__AVR_ATmega2560__)
    				timerInterrupts[TIMER2_COMPB_int] = NULL;
    				break;
    				#endif
    			}
    			case TC_OC_C :
    			{
    				return TC_CMD_NAK;
    			}
    			default :
    			{
    				return TC_CMD_NAK;
    			}
    		}
    		break;
    	}
    	case TC_3 :
    	{
    		switch (channel)
    		{
    			case TC_OC_A :
    			{
    				timerInterrupts[TIMER3_COMPA_int] = NULL;
    				break;
    			}
    			case TC_OC_B :
    			{
    				timerInterrupts[TIMER3_COMPB_int] = NULL;
    				break;
    			}
    			case TC_OC_C :
    			{
    				timerInterrupts[TIMER3_COMPC_int] = NULL;
    				break;
    			}
    			default :
    			{
    				return TC_CMD_NAK;
    			}
    		}
    		break;
    	}
    	#endif

    	#ifdef __AVR_ATmega2560__
    	case TC_4 :
    	{
    		switch (channel)
    		{
    			case TC_OC_A :
    			{
    				timerInterrupts[TIMER4_COMPA_int] = NULL;
    				break;
    			}
    			case TC_OC_B :
    			{
    				timerInterrupts[TIMER4_COMPB_int] = NULL;
    				break;
    			}
    			case TC_OC_C :
    			{
    				timerInterrupts[TIMER4_COMPC_int] = NULL;
    				break;
    			}
    			default :
    			{
    				return TC_CMD_NAK;
    			}
    		}
    		break;
    	}
    	case TC_5 :
    	{
    		switch (channel)
    		{
    			case TC_OC_A :
    			{
    				timerInterrupts[TIMER5_COMPA_int] = NULL;
    				break;
    			}
    			case TC_OC_B :
    			{
    				timerInterrupts[TIMER5_COMPB_int] = NULL;
    				break;
    			}
    			case TC_OC_C :
    			{
    				timerInterrupts[TIMER5_COMPC_int] = NULL;
    				break;
    			}
    			default :
    			{
    				return TC_CMD_NAK;
    			}
    		}
    		break;
    	}
    	#endif
    	default :
    	{
    		return TC_CMD_NAK;
    	}
    }
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

	switch (timer_number)
	{
		case TC_0 :
		{
			if (channel == TC_OC_A)
			{
				*imp_register_table.OCR_A_ADDRESS.as_8bit = value.value.as_8bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_B)
			{
				#ifdef __AVR_AT90CAN128__
				return TC_CMD_NAK;

				#else
				*imp_register_table.OCR_B_ADDRESS.as_8bit = value.value.as_8bit;
				return TC_CMD_ACK;
				#endif

			}
			#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
			else if (channel == TC_OC_C)
			{
				return TC_CMD_NAK;
			}
			#endif
		}
		case TC_1 :
		{
			if (channel == TC_OC_A)
			{
				*imp_register_table.OCR_A_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_B)
			{
				*imp_register_table.OCR_B_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
			else if (channel == TC_OC_C)
			{
				*imp_register_table.OCR_C_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			#endif
		}
		#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
		case TC_2 :
		{
			if (channel == TC_OC_A)
			{
				*imp_register_table.OCR_A_ADDRESS.as_8bit = value.value.as_8bit;
				return TC_CMD_ACK;
			}
			#ifdef __AVR_ATmega2560__
			else if (channel == TC_OC_B)
			{
				*imp_register_table.OCR_B_ADDRESS.as_8bit = value.value.as_8bit;
				return TC_CMD_ACK;
			}
			#endif
		}
		case TC_3 :
		{
			if (channel == TC_OC_A)
			{
				*imp_register_table.OCR_A_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_B)
			{
				*imp_register_table.OCR_B_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_C)
			{
				*imp_register_table.OCR_C_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4 :
		{
			if (channel == TC_OC_A)
			{
				*imp_register_table.OCR_A_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_B)
			{
				*imp_register_table.OCR_B_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_C)
			{
				*imp_register_table.OCR_C_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
		}
		case TC_5 :
		{
			if (channel == TC_OC_A)
			{
				*imp_register_table.OCR_A_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_B)
			{
				*imp_register_table.OCR_B_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
			else if (channel == TC_OC_C)
			{
				*imp_register_table.OCR_C_ADDRESS.as_16bit = value.value.as_16bit;
				return TC_CMD_ACK;
			}
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}
	return TC_CMD_NAK;
}

Tc_value Tc_imp::get_ocR(Tc_oc_channel channel)
{
	switch (timer_number)
	{
		case TC_0 :
		{
			if (channel == TC_OC_A)
			{
				return Tc_value::from_uint8(*imp_register_table.OCR_A_ADDRESS.as_8bit);
			}
			else if (channel == TC_OC_B)
			{
				#ifdef __AVR_AT90CAN128__
				return Tc_value::from_uint8(0);

				#else
				return Tc_value::from_uint8(*imp_register_table.OCR_B_ADDRESS.as_8bit);
				#endif

			}
			#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
			else if (channel == TC_OC_C)
			{
				return Tc_value::from_uint8(0);
			}
			#endif
		}
		case TC_1 :
		{
			if (channel == TC_OC_A)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_A_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_B)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_B_ADDRESS.as_16bit);
			}
			#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
			else if (channel == TC_OC_C)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_C_ADDRESS.as_16bit);
			}
			#endif
		}
		#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
		case TC_2 :
		{
			if (channel == TC_OC_A)
			{
				return Tc_value::from_uint8(*imp_register_table.OCR_A_ADDRESS.as_8bit);
			}
			#ifdef __AVR_ATmega2560__
			else if (channel == TC_OC_B)
			{
				return Tc_value::from_uint8(*imp_register_table.OCR_B_ADDRESS.as_8bit);
			}
			#endif
		}
		case TC_3 :
		{
			if (channel == TC_OC_A)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_A_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_B)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_B_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_C)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_C_ADDRESS.as_16bit);
			}
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4 :
		{
			if (channel == TC_OC_A)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_A_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_B)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_B_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_C)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_C_ADDRESS.as_16bit);
			}
		}
		case TC_5 :
		{
			if (channel == TC_OC_A)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_A_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_B)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_B_ADDRESS.as_16bit);
			}
			else if (channel == TC_OC_C)
			{
				return Tc_value::from_uint16(*imp_register_table.OCR_C_ADDRESS.as_16bit);
			}
		}
		#endif
		default :
		{
			return Tc_value::from_uint8(0);
		}
	}
}

Tc_command_status Tc_imp::enable_ic(Tc_ic_channel channel, Tc_ic_mode mode)
{
	if (timer_size == TC_8BIT)
	{
		return TC_CMD_NAK;
	}

	#if defined (__AVR_ATmega64M1__) || defined (__AVR_ATmega64C1__)
	if (pin_address[(int8_t)channel].address.port <= PORT_D)
    {
      	_SFR_IO8(pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.pin));
    }

	#elif defined (__AVR_AT90CAN128__)
    if (pin_address[(int8_t)channel].address.port <= PORT_G)
    {
      	_SFR_IO8(pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.pin));
    }

    #elif defined (__AVR_ATmega2560__)
    if (pin_address[(int8_t)channel].address.port <= PORT_G)
    {
      	_SFR_IO8(pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + LOWER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.pin));
    }
    else
    {
      	_SFR_MEM8(pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.port * PORT_REGISTER_MULTIPLIER + HIGHER_REGISTER_PORT_OFFSET) &= ~(1 << ((int8_t)pin_address[(int8_t)channel + IC_CHANNEL_OFFSET].address.pin));
    }
    #endif

	switch (channel)
	{
		case TC_IC_A :
		{
			switch (mode)
			{
				case TC_IC_NONE :
				{
					// disabling the Input Capture Unit.

					// disable the interrupts, zero ICNC and ICES, and zero the ICRn register
					// *imp_register_table.TCCR_B_ADDRESS &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));
				}
				case TC_IC_MODE_1 :		// No Noise Canceler, falling edge used as trigger
				{
				    *imp_register_table.TCCR_B_ADDRESS &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));
					return TC_CMD_ACK;
				}
				case TC_IC_MODE_2 :		// No Noise Canceler, rising edge used as trigger
				{
					*imp_register_table.TCCR_B_ADDRESS |= (1 << ICES_BIT);
					*imp_register_table.TCCR_B_ADDRESS &= ~(1 << ICNC_BIT);
					return TC_CMD_ACK;
				}
				case TC_IC_MODE_3 :		// Noise Canceler activated, falling edge.
				{
					*imp_register_table.TCCR_B_ADDRESS |= (1 << ICNC_BIT);
					*imp_register_table.TCCR_B_ADDRESS &= ~(1 << ICES_BIT);
					return TC_CMD_ACK;
				}
				case TC_IC_MODE_4 :		// Noise Canceler activated, rising edge.
				{
					*imp_register_table.TCCR_B_ADDRESS |= ((1 << ICES_BIT) | (1 << ICNC_BIT));
					return TC_CMD_ACK;
				}
				default :
				{
					return TC_CMD_NAK;
				}
			}
		}
		#if defined (__AVR_ATmega64M1__) || defined (__AVR_ATmega64C1__)
		case TC_IC_B:
		{
			switch (mode)
			{
				case TC_IC_NONE :
				{
					// disabling the Input Capture Unit.

					// disable the interrupts, zero ICNC and ICES, and zero the ICRn register
					// *imp_register_table.TCCR_B_ADDRESS &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));
				}
				case TC_IC_MODE_1 :		// No Noise Canceler, falling edge used as trigger
				{
				    *imp_register_table.TCCR_B_ADDRESS &= (~(1 << ICNC_BIT) & ~(1 << ICES_BIT));
					return TC_CMD_ACK;
				}
				case TC_IC_MODE_2 :		// No Noise Canceler, rising edge used as trigger
				{
					*imp_register_table.TCCR_B_ADDRESS |= (1 << ICES_BIT);
					*imp_register_table.TCCR_B_ADDRESS &= ~(1 << ICNC_BIT);
					return TC_CMD_ACK;
				}
				case TC_IC_MODE_3 :		// Noise Canceler activated, falling edge.
				{
					*imp_register_table.TCCR_B_ADDRESS |= (1 << ICNC_BIT);
					*imp_register_table.TCCR_B_ADDRESS &= ~(1 << ICES_BIT);
					return TC_CMD_ACK;
				}
				case TC_IC_MODE_4 :		// Noise Canceler activated, rising edge.
				{
					*imp_register_table.TCCR_B_ADDRESS |= ((1 << ICES_BIT) | (1 << ICNC_BIT));
					return TC_CMD_ACK;
				}
				default :
				{
					return TC_CMD_NAK;
				}
			}
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}

	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::enable_ic_interrupt(Tc_ic_channel channel, IsrHandler callback)
{
	switch (timer_number)
	{
		case TC_0:
		{
			return TC_CMD_NAK;
		}
		case TC_1:
		{
		  	timerInterrupts[TIMER1_CAPT_int] = callback;
		  	break;
		}
		#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
		case TC_2:
		{
			return TC_CMD_NAK;
		}
		case TC_3:
		{
		  	timerInterrupts[TIMER3_CAPT_int] = callback;
		  	break;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
		  	timerInterrupts[TIMER4_CAPT_int] = callback;
		  	break;
		}
		case TC_5:
		{
		  	timerInterrupts[TIMER5_CAPT_int] = callback;
		  	break;
		}
		#endif
		default:
		{
			return TC_CMD_NAK;
		}
	}

	switch (channel)
	{
		case TC_IC_A:
		{
		  /* Set the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
		  	*imp_register_table.TIMSK_ADDRESS |= (1 << ICIE_BIT);

		  	return TC_CMD_ACK;
		}
		#if defined (__AVR_ATmega64C1__) || defined (__AVR_ATmega64M1__)
		case TC_IC_B:
		{
			*imp_register_table.TIMSK_ADDRESS |= (1 << ICIE_BIT);
			return TC_CMD_ACK;
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}
	return TC_CMD_NAK;
}

Tc_command_status Tc_imp::disable_ic_interrupt(Tc_ic_channel channel)
{
	switch (channel)
	{
		case TC_IC_A:
		{
		  	/* Clear the Input Capture Interrupt Enable bit (ICIEn) in the TIMSKn register */
		  	*imp_register_table.TIMSK_ADDRESS &= ~(1 << ICIE_BIT);

		  	break;
		}
		#if defined (__AVR_ATmega64C1__) || defined (__AVR_ATmega64M1__)
		case TC_IC_B:
		{
			*imp_register_table.TIMSK_ADDRESS &= ~(1 << ICIE_BIT);
			break;
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}

	switch (timer_number)
	{
		case TC_0:
		{
			return TC_CMD_NAK;
		}
		case TC_1:
		{
		  	timerInterrupts[TIMER1_CAPT_int] = NULL;
		  	return TC_CMD_ACK;
		}
		#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
		case TC_2:
		{
			return TC_CMD_NAK;
		}
		case TC_3:
		{
		  	timerInterrupts[TIMER3_CAPT_int] = NULL;
		  	return TC_CMD_ACK;
		}
		#endif
		#ifdef __AVR_ATmega2560__
		case TC_4:
		{
		  	timerInterrupts[TIMER4_CAPT_int] = NULL;
		  	return TC_CMD_ACK;
		}
		case TC_5:
		{
		  	timerInterrupts[TIMER5_CAPT_int] = NULL;
		  	return TC_CMD_ACK;
		}
		#endif
		default:
		{
		  	return TC_CMD_NAK;
		}
	}
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

	switch (channel)
	{
		case TC_IC_A:
		{
			*imp_register_table.ICR_ADDRESS = value.value.as_16bit;
		}
		#if defined (__AVR_ATmega64C1__) || defined (__AVR_ATmega64M1__)
		case TC_IC_B:
		{
			*imp_register_table.ICR_ADDRESS = value.value.as_16bit;
		}
		#endif
		default :
		{
			return TC_CMD_NAK;
		}
	}
	return TC_CMD_NAK;
}

Tc_value Tc_imp::get_icR(Tc_ic_channel channel)
{
	switch (channel)
	{
		case TC_IC_A:
		{
	  		return Tc_value::from_uint16(*imp_register_table.ICR_ADDRESS);
		}
		#if defined (__AVR_ATmega64C1__) || defined (__AVR_ATmega64M1__)
		case TC_IC_B:
		{
			return Tc_value::from_uint16(*imp_register_table.ICR_ADDRESS);
		}
		#endif
		default :
		{
			return Tc_value::from_uint8(0);
		}
	}
	return Tc_value::from_uint8(0);
}


// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// /** IMPLEMENT ISR POINTERS
//  *
//  * Each timer interrupt type is tied to a relevant interrupt vector. These are associated
//  * with the user ISRs by way of the function pointer array timerInterrupts[]. Here the
//  * ISRs are declared and the user ISR is called if the appropriate element of the function
//  * pointer array is non NULL.
//  */
 ISR(TIMER0_OVF_vect)
 {
   if (timerInterrupts[TIMER0_OVF_int])
     timerInterrupts[TIMER0_OVF_int]();
 }

#ifndef __AVR_AT90CAN128__
 ISR(TIMER0_COMPA_vect)
 {
   if (timerInterrupts[TIMER0_COMPA_int])
     timerInterrupts[TIMER0_COMPA_int]();
 }

 ISR(TIMER0_COMPB_vect)
 {
   if (timerInterrupts[TIMER0_COMPB_int])
     timerInterrupts[TIMER0_COMPB_int]();
 }
#endif

 ISR(TIMER1_OVF_vect)
 {
   if (timerInterrupts[TIMER1_OVF_int])
     timerInterrupts[TIMER1_OVF_int]();
 }

 ISR(TIMER1_COMPA_vect)
 {
   if (timerInterrupts[TIMER1_COMPA_int])
     timerInterrupts[TIMER1_COMPA_int]();
 }

 ISR(TIMER1_COMPB_vect)
 {
   if (timerInterrupts[TIMER1_COMPB_int])
     timerInterrupts[TIMER1_COMPB_int]();
 }

 ISR(TIMER1_CAPT_vect)
 {
   if (timerInterrupts[TIMER1_CAPT_int])
     timerInterrupts[TIMER1_CAPT_int]();
 }

#if defined (__AVR_AT90CAN128__) || defined (__AVR_ATmega2560__)
 ISR(TIMER1_COMPC_vect)
 {
   if (timerInterrupts[TIMER1_COMPC_int])
     timerInterrupts[TIMER1_COMPC_int]();
 }
#endif

 #ifdef __AVR_AT90CAN128__
 ISR(TIMER0_COMP_vect)
 {
   if (timerInterrupts[TIMER0_COMP_int])
     timerInterrupts[TIMER0_COMP_int]();
 }

 ISR(TIMER2_COMP_vect)
 {
   if (timerInterrupts[TIMER2_COMP_int])
	 timerInterrupts[TIMER2_COMP_int]();
 }
 #endif

#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
 ISR(TIMER2_OVF_vect)
 {
   if (timerInterrupts[TIMER2_OVF_int])
     timerInterrupts[TIMER2_OVF_int]();
 }

 ISR(TIMER3_CAPT_vect)
 {
   if (timerInterrupts[TIMER3_CAPT_int])
     timerInterrupts[TIMER3_CAPT_int]();
 }

 ISR(TIMER3_COMPA_vect)
 {
   if (timerInterrupts[TIMER3_COMPA_int])
     timerInterrupts[TIMER3_COMPA_int]();
 }

 ISR(TIMER3_COMPB_vect)
 {
   if (timerInterrupts[TIMER3_COMPB_int])
     timerInterrupts[TIMER3_COMPB_int]();
 }

 ISR(TIMER3_COMPC_vect)
 {
   if (timerInterrupts[TIMER3_COMPC_int])
     timerInterrupts[TIMER3_COMPC_int]();
 }

 ISR(TIMER3_OVF_vect)
 {
   if (timerInterrupts[TIMER3_OVF_int])
     timerInterrupts[TIMER3_OVF_int]();
 }
#endif

#ifdef __AVR_ATmega2560__
 ISR(TIMER2_COMPA_vect)
 {
   if (timerInterrupts[TIMER2_COMPA_int])
     timerInterrupts[TIMER2_COMPA_int]();
 }

  ISR(TIMER2_COMPB_vect)
 {
   if (timerInterrupts[TIMER2_COMPB_int])
     timerInterrupts[TIMER2_COMPB_int]();
 }

 ISR(TIMER4_CAPT_vect)
 {
   if (timerInterrupts[TIMER4_CAPT_int])
     timerInterrupts[TIMER4_CAPT_int]();
 }

 ISR(TIMER4_COMPA_vect)
 {
   if (timerInterrupts[TIMER4_COMPA_int])
     timerInterrupts[TIMER4_COMPA_int]();
 }

 ISR(TIMER4_COMPB_vect)
 {
   if (timerInterrupts[TIMER4_COMPB_int])
     timerInterrupts[TIMER4_COMPB_int]();
 }

 ISR(TIMER4_COMPC_vect)
 {
   if (timerInterrupts[TIMER4_COMPC_int])
     timerInterrupts[TIMER4_COMPC_int]();
 }

 ISR(TIMER4_OVF_vect)
 {
   if (timerInterrupts[TIMER4_OVF_int])
     timerInterrupts[TIMER4_OVF_int]();
 }

 ISR(TIMER5_CAPT_vect)
 {
   if (timerInterrupts[TIMER5_CAPT_int])
     timerInterrupts[TIMER5_CAPT_int]();
 }

 ISR(TIMER5_COMPA_vect)
 {
   if (timerInterrupts[TIMER5_COMPA_int])
     timerInterrupts[TIMER5_COMPA_int]();
 }

 ISR(TIMER5_COMPB_vect)
 {
   if (timerInterrupts[TIMER5_COMPB_int])
     timerInterrupts[TIMER5_COMPB_int]();
 }

 ISR(TIMER5_COMPC_vect)
 {
   if (timerInterrupts[TIMER5_COMPC_int])
     timerInterrupts[TIMER5_COMPC_int]();
 }

 ISR(TIMER5_OVF_vect)
 {
   if (timerInterrupts[TIMER5_OVF_int])
     timerInterrupts[TIMER5_OVF_int]();
 }
#endif
