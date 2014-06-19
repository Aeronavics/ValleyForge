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
 *  FILE: 		gpio.c
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Edwin Hayes, Zac Frank
 *
 *  DATE CREATED:	7-12-2011
 *
 *	This is the implementation for gpio for the ATmega2560, ATmega64M1/C1 and AT90CAN128.
 *  All very similar except ATmega64M1/C1 is missing 4 external interrupt pins and AT90CAN128
 *  is missing the PCINT pins
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.
#include "hal/target_config.hpp"

#include <avr/interrupt.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <stdio.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

/* Offset constants that facilitate access to the particular GPIO registers (DDRx, PORTx, PINx) */
enum port_offset	{P_READ, P_MODE, P_WRITE};

// DECLARE IMPORTED GLOBAL VARIABLES.

// DEFINE PRIVATE CLASSES.

/**
 * A Class that provides device specific implementation for the functions for Gpio_pin.
 *
 */
class Gpio_pin_imp
{
	public:

		// Methods.

		Gpio_io_status set_mode(IO_pin_address address, Gpio_mode mode);

		Gpio_input_state read(IO_pin_address address);
		
		Gpio_io_status write(IO_pin_address address, Gpio_output_state value);
		
		Gpio_interrupt_status enable_interrupt(IO_pin_address address, Gpio_interrupt_mode mode, void (*func_pt)(void));
		
		Gpio_interrupt_status disable_interrupt(IO_pin_address address);
		
		Gpio_mode pin_modes[NUM_PORTS][NUM_PINS];
};

// DECLARE PRIVATE GLOBAL VARIABLES.

volatile static voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];

Gpio_pin_imp gpio_pin_imp;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

Gpio_pin::Gpio_pin(Gpio_pin_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

Gpio_io_status Gpio_pin::set_mode(Gpio_mode mode)
{
	return (imp->set_mode(pin_address, mode));
}

Gpio_io_status Gpio_pin::write(Gpio_output_state value)
{
	return (imp->write(pin_address, value));
}

Gpio_input_state Gpio_pin::read(void)
{
	return (imp->read(pin_address));
}

Gpio_pin::Gpio_pin(IO_pin_address address)
{
	// Attach the implementation.
	imp = &gpio_pin_imp;
	pin_address = address;

	// All done.
	return;
}

Gpio_pin::~Gpio_pin()
{
	// All done.
	return;
}

Gpio_interrupt_status Gpio_pin::enable_interrupt(Gpio_interrupt_mode mode, void (*user_ISR)(void))
{
      return imp->enable_interrupt(pin_address, mode, user_ISR); 
}

Gpio_interrupt_status Gpio_pin::disable_interrupt(void)
{
      return imp->disable_interrupt(pin_address);  
}

// IMPLEMENT PRIVATE FUNCTIONS.

// DECLARE ISRs

// Each ISR calls the user specified function, by invoking the function pointer in the array of function pointers.

// This offset is here because the interrupts are enumerated, not in the same order as the function array. This is because the number of interrupts changes with architecture.

SIGNAL(INT0_vect) {
	if(intFunc[EINT_0]) 
	{
		intFunc[EINT_0]();
	}
}

SIGNAL(INT1_vect) {
	if(intFunc[EINT_1])
	{
		intFunc[EINT_1]();
	}
}

SIGNAL(INT2_vect) {
	if(intFunc[EINT_2])
	{
		intFunc[EINT_2]();
	}
}

SIGNAL(INT3_vect) {
	if(intFunc[EINT_3])
	{
		intFunc[EINT_3]();
	}
}

#if (defined(__AVR_ATmega2560__)) || (defined(__AVR_AT90CAN128__))
SIGNAL(INT4_vect) {
	if(intFunc[EINT_4])
	{
		intFunc[EINT_4]();
	}
}

SIGNAL(INT5_vect) {
	if(intFunc[EINT_5])
	{
		intFunc[EINT_5]();
	}
}

SIGNAL(INT6_vect) {
	if(intFunc[EINT_6])
	{
		intFunc[EINT_6]();
	}
}

SIGNAL(INT7_vect) {
	if(intFunc[EINT_7])
	{
		intFunc[EINT_7]();
	}
}
#endif

#if defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__) || defined(__AVR_ATmega2560__)
SIGNAL(PCINT0_vect) {
	if(intFunc[PCINT_0])
	{
		intFunc[PCINT_0]();
	}
}

SIGNAL(PCINT1_vect) {
	if(intFunc[PCINT_1])
	{
		intFunc[PCINT_1]();
	}
}

SIGNAL(PCINT2_vect) {
	if(intFunc[PCINT_2])
	{
		intFunc[PCINT_2]();
	}
}
#endif

/* ********************** Gpio_pin_imp methods ********************** */ 

Gpio_io_status Gpio_pin_imp::set_mode(IO_pin_address address, Gpio_mode mode)
{	
	uint8_t wmode;
	if (mode == GPIO_INPUT_FL)
	{
		wmode = GPIO_INPUT_PU;	//DDR pin can only be written high (1) or low (0)
	} 
	else
	{
		wmode = mode;
	}

	
	#if defined(__AVR_ATmega2560__)			
	if ( address.port >= PORT_H )
	{
		_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_MODE) = (_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_MODE) & ~(1 << address.pin) ) | (wmode?(1 << address.pin):0);
	}
	else
	{
		// Set/clear data direction register pin.
		_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) & ~(1 << address.pin) ) | (wmode?(1 << address.pin):0);
	}
	
	#elif defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
		_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) & ~(1 << address.pin) ) | (wmode?(1 << address.pin):0);
	#else
		#error "No GPIO mode set implemented for this configuration"
	#endif
	
	if (mode == GPIO_INPUT_FL)
	{
		write(address, GPIO_O_LOW);		//write low to PORTx to disable pull up
	} 
	
	pin_modes[address.port][address.pin] = mode;
	
	// All done.	
	return GPIO_SUCCESS;
}
		
Gpio_io_status Gpio_pin_imp::write (IO_pin_address address, Gpio_output_state value)
{
	if (pin_modes[address.port][address.pin] == GPIO_INPUT_PU || pin_modes[address.port][address.pin] == GPIO_INPUT_FL)
	{
		return GPIO_ERROR;
	}
	
	/* Set/clear port register register pin */
	if (value == GPIO_O_TOGGLE)
	{
		#if defined(__AVR_ATmega2560__)		
		if ( address.port >= PORT_H )
		{
			// Toggle value.
			_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) = (_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) & ~(1 << address.pin) ) | ~(_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE));
		}
		else
		{
			// Toggle value.
			_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | ~(_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE));
		}
		#elif defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
			// Toggle value.
			_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | ~(_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE));
		#else
			#error "No GPIO toggle implemented for this configuration"
		#endif
	}
	else
	{
		#if defined(__AVR_ATmega2560__)	
		if ( address.port >= PORT_H )
		{
			// Set or Clear pin on port.
			_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) = (_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) & ~(1 << address.pin) ) | (value ? (1 << address.pin) : (pin_t) GPIO_O_LOW);
		}
		else
		{
			// Set or Clear pin on port.
			_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = ( _SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | (value ? (1 << address.pin) : (pin_t) GPIO_O_LOW);
		}
		#elif defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
			// Set or Clear pin on port.
			_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = ( _SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | (value ? (1 << address.pin) : (pin_t) GPIO_O_LOW);
		#else
			#error "No GPIO write implemented for this configuration"
		#endif
	}

	// All done.
	return GPIO_SUCCESS;
}
		
Gpio_input_state Gpio_pin_imp::read(IO_pin_address address)
{
	#if defined(__AVR_ATmega2560__)		
	if ( address.port >= PORT_H )
	{
		// Read and return pin.
		return ((_SFR_MEM8((address.port * PORT_MULTIPLIER) + P_OFFSET + P_READ) & (1 << address.pin)) ? GPIO_I_LOW : GPIO_I_HIGH);
	}
	else
	{
		// Read and return pin.
		return ((_SFR_IO8((address.port * PORT_MULTIPLIER) + P_READ) & (1 << address.pin)) ? GPIO_I_LOW : GPIO_I_HIGH);
	}
	#elif defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
		return ((_SFR_IO8((address.port * PORT_MULTIPLIER) + P_READ) & (1 << address.pin)) ? GPIO_I_LOW : GPIO_I_HIGH);
	#else
		#error "No GPIO read implemented for this configuration"
	#endif 
}
				
Gpio_interrupt_status Gpio_pin_imp::enable_interrupt(IO_pin_address address, Gpio_interrupt_mode mode, void (*userFunc)(void))
{
	Gpio_interrupt_status ret_code;
	
	#if defined(__AVR_ATmega2560__)
		/* Determine the type of interrupt this pin can use. EINT_x pins supports custom events as specified by the  
		 * 'mode' argument whereas PCINT_x pins does not */
		 
		switch (PC_INT[address.port][address.pin])
		{
			case PCINT_0:
				PCICR |= (1 << PCINT_0);
				PCMSK0 = (1 << address.pin);
				break;
			case PCINT_1:
				PCICR |= (1 << PCINT_1);
				PCMSK1 = (address.port == PORT_J) ? (1 << (address.pin - 1)) : (1 << address.pin);
				break;
			case PCINT_2:
				PCICR |= (1 << PCINT_2);
				PCMSK0 = (1 << address.pin);
				break;
			case EINT_0:
				// Set the mode of interrupt, between falling edge, rising edge, any edge and low level.
				EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
				// Enable the interrupt.
				EIMSK |= (1 << INT0);
				break;
			case EINT_1:
				EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
				EIMSK |= (1 << INT1);
				break;
			case EINT_2:
				EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
				EIMSK |= (1 << INT2);
				break;
			case EINT_3:
				EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
				EIMSK |= (1 << INT3);
				break;
			case EINT_4:
				EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
				EIMSK |= (1 << INT4);
				break;
			case EINT_5:
				EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
				EIMSK |= (1 << INT5);
				break;
			case EINT_6:
				EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
				EIMSK |= (1 << INT6);
				break;
			case EINT_7:
				EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
				EIMSK |= (1 << INT7);
				break;
			default:
				// The Given pin does not have an interrupt available to it.
				return GPIO_INT_OUT_OF_RANGE;
		}
		
		//determine appropriate return condition
		if (intFunc[PC_INT[address.port][address.pin]] == userFunc)
		{
			ret_code = GPIO_INT_ALREADY_DONE;
		}
		else if (intFunc[PC_INT[address.port][address.pin]])
		{
			ret_code = GPIO_INT_ALREADY_TAKEN;
		}
		else
		{
			ret_code = GPIO_INT_SUCCESS;
		}
		
		// Attach the callback.
		intFunc[PC_INT[address.port][address.pin]] = (voidFuncPtr) userFunc;
		
	#elif defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
	// Provisions for ATmega64M1/C1: Due to non-existence of port A, port_t types must be decremented by 1
	
		switch (PC_INT[address.port-1][address.pin])
		{
			case PCINT_0:
				PCICR |= (1 << PCINT_0);
				PCMSK0 = (1 << address.pin);
				break;
			case PCINT_1:
				PCICR |= (1 << PCINT_1);
				PCMSK1 = (1 << address.pin);
				break;
			case PCINT_2:
				PCICR |= (1 << PCINT_2);
				PCMSK0 = (1 << address.pin);
				break;
			case EINT_0:
				EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
				EIMSK |= (1 << INT0);
				break;
			case EINT_1:
				EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
				EIMSK |= (1 << INT1);
				break;
			case EINT_2:
				EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
				EIMSK |= (1 << INT2);
				break;
			case EINT_3:
				EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
				EIMSK |= (1 << INT3);
				break;	
			default:
				return GPIO_INT_OUT_OF_RANGE;	
		}	
		
		if (intFunc[PC_INT[address.port-1][address.pin]] == userFunc)
		{
			ret_code = GPIO_INT_ALREADY_DONE;
		}
		else if (intFunc[PC_INT[address.port-1][address.pin]]) 
		{
			ret_code = GPIO_INT_ALREADY_TAKEN;
		}
		else
		{
			ret_code = GPIO_INT_SUCCESS;
		}
		intFunc[PC_INT[address.port-1][address.pin]] = (voidFuncPtr) userFunc;
	
	#elif defined(__AVR_AT90CAN128__)
		// Provisions for AT90CAN128: No PCINT interrupts
		
		switch ((uint8_t)PC_INT[address.port][address.pin]) 
		{
			case EINT_0:
				EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
				EIMSK |= (1 << INT0);
				break;
			case EINT_1:
				EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
				EIMSK |= (1 << INT1);
				break;
			case EINT_2:
				EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
				EIMSK |= (1 << INT2);
				break;
			case EINT_3:
				EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
				EIMSK |= (1 << INT3);
				break;
			case EINT_4:
				EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
				EIMSK |= (1 << INT4);
				break;
			case EINT_5:
				EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
				EIMSK |= (1 << INT5);
				break;
			case EINT_6:
				EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
				EIMSK |= (1 << INT6);
				break;
			case EINT_7:
				EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
				EIMSK |= (1 << INT7);
				break;
			default:
				// The Given pin does not have an interrupt available to it.
				return GPIO_INT_OUT_OF_RANGE;
		}     
		
		if (intFunc[PC_INT[address.port][address.pin]] == userFunc)
		{
			ret_code = GPIO_INT_ALREADY_DONE;
		}
		else if (intFunc[PC_INT[address.port][address.pin]])
		{
			ret_code = GPIO_INT_ALREADY_TAKEN;
		}
		else
		{
			ret_code = GPIO_INT_SUCCESS;
		}
		intFunc[PC_INT[address.port][address.pin]] = (voidFuncPtr) userFunc; 	  
		
	#else
		#error "No GPIO interrupt enable implemented for this configuration"
	#endif
	
	return ret_code;
}

Gpio_interrupt_status Gpio_pin_imp::disable_interrupt(IO_pin_address address) 
{
	// If target has PCINT pins, check to see if pin is a on a PCINT bank
	#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
	if ((PC_INT[address.port][address.pin] >= PCINT_0)  && (PC_INT[address.port][address.pin] < NUM_BANKS)) 
	{
		switch (PC_INT[address.port][address.pin]) 
		{
			case PCINT_0:
				// Disable the interrupt.
				PCICR &= ~(1 << PCINT_0);
				// Clear the mask register so that all pins are disabled.
				PCMSK0 = 0;
				break;
			case PCINT_1:
				PCICR &= ~(1 << PCINT_1);
				PCMSK0 = 0;
				break;
		    case PCINT_2:
				PCICR &= ~(1 << PCINT_2);
				PCMSK0 = 0;
				break;
			default:
				break;
		}
		
		// Detach user's callback from the actual ISR.			
		intFunc[PC_INT[address.port][address.pin]] = NULL;
	}
	#else
		#warning "PCINT GPIO interrupts not implemented for this configuration"
	#endif
	
	// All targets have EINT pins, check to see if the pin is one of the special EINT pins which is easy to disable
	if ((PC_INT[address.port][address.pin] >= EINT_0)  && (PC_INT[address.port][address.pin] < (EINT_0 + EXT_INT_SIZE )))
	{
		switch (PC_INT[address.port][address.pin]) 
		{
		#if defined (__AVR_ATmega2560__) || defined(__AVR_AT90CAN128__)
			case EINT_0:
				// Mask the interrupt so it doesn't fire anymore, i.e put a zero in the mask register.
				EIMSK &= ~(1 << INT0);
				break;
			case EINT_1:
				EIMSK &= ~(1 << INT1);
				break;
			case EINT_2:
				EIMSK &= ~(1 << INT2);
				break;
			case EINT_3:
				EIMSK &= ~(1 << INT3);
				break;
			case EINT_4:
				EIMSK &= ~(1 << INT4);
				break;
			case EINT_5:
				EIMSK &= ~(1 << INT5);
				break;
			case EINT_6:
				EIMSK &= ~(1 << INT6);
				break;
			case EINT_7:
				EIMSK &= ~(1 << INT7);
				break;
			default:
				return GPIO_INT_OUT_OF_RANGE;
				
		#elif defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
			case EINT_0:
				// Mask the interrupt so it doesn't fire anymore, i.e put a zero in the mask register.
				EIMSK &= ~(1 << INT0);
				break;
			case EINT_1:
				EIMSK &= ~(1 << INT1);
				break;
			case EINT_2:
				EIMSK &= ~(1 << INT2);
				break;
			case EINT_3:
				EIMSK &= ~(1 << INT3);		
			default:
				return GPIO_INT_OUT_OF_RANGE;
				
		#else
			#error "GPIO interrupts not implemented for this configuration."
		#endif
		}

		// Detach user's callback from the actual ISR.
		intFunc[PC_INT[address.port][address.pin]] = NULL;
	}

	// All done.
	return GPIO_INT_SUCCESS;
}

// ALL DONE.

