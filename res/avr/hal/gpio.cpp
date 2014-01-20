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
 *	This is the implementation for gpio for the atmega2560, atmega64M1 and AT90CAN128.
 *  All very similar except atmega64M1 is missing 4 external interrupt pins and AT90CAN128
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

// We need definition for the new and delete operators so we can use the heap.
#include "avr_magic/avr_magic.hpp"

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

		/**
		 * Creates a new instance of Gpio_pin_imp, abstracting the GPIO pin at the specified address.
		 *
		 * @param address The IO address of the pin to abstract.
		 * @return Nothing.
		 */
		Gpio_pin_imp(IO_pin_address pin_address)
		{
			address = pin_address;
		
			// All done.
			return;
		}

		/**
		 * Sets the pin to an input or output.
		 *
		 * @param mode 	Set to INPUT or OUTPUT.
		 * @return Zero for success, non-zero for failure.
		 * 
		 */
		Gpio_io_status set_mode(Gpio_mode mode);

		/**
		 * Reads the value of the GPIO pin and returns it.
		 * 
		 * @param Nothing.
		 * @return The current state of the IO pin.
		 */
		Gpio_input_state read(void);
		
		/**
		 * Writes the value provided to the pin.
		 * 
		 * @param  value	The state to set the GPIO pin to.
		 * @return Nothing.
		 */
		void write(Gpio_output_state value);
		
		/** 
		 * Initialise an interrupt for the pin in the specified mode and attach the specified function as the corresponding ISR.
		 *
		 * NOTE - Calling this function automatically sets the pin to an input.
		 *
		 * @param  mode		Type of GPIO interupt to enable.
 		 * @param  func_pt	Pointer to ISR function that is to be attached to the interrupt.
		 * @return Zero for success, non-zero for failure.
		 */
		Gpio_interrupt_status enable_interrupt(Gpio_interrupt_mode mode, void (*func_pt)(void));
		
		/**
		 * Disable an interrupt for the pin.
		 *
		 * @param  Nothing.
		 * @return Zero for success, non-zero for failure.
		 */
		Gpio_interrupt_status disable_interrupt(void);
		
	  	// Fields.

	 	IO_pin_address address;
};

// DECLARE PRIVATE GLOBAL VARIABLES.

volatile static voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

Gpio_pin::~Gpio_pin(void)
{
	// Delete the implementation.
	delete imp;

	// All done.
	return;
}

Gpio_pin::Gpio_pin(Gpio_pin_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

Gpio_io_status Gpio_pin::set_mode(Gpio_mode mode)
{
	return (imp->set_mode(mode));
}

void Gpio_pin::write(Gpio_output_state value)
{
	return (imp->write(value));
}

Gpio_input_state Gpio_pin::read(void)
{
	return (imp->read());
}

Gpio_pin Gpio_pin::grab(IO_pin_address address)
{
	// Allocate an implementation for the address.
	Gpio_pin_imp* imp = new Gpio_pin_imp(address);

	// TODO - At the moment, we're just assuming this works.  If it doesn't, we're in major trouble.

	// Create a new GPIO pin using this implementation.
	return Gpio_pin(imp);
}

Gpio_interrupt_status Gpio_pin::enable_interrupt(Gpio_interrupt_mode mode, void (*user_ISR)(void))
{
      return imp->enable_interrupt(mode, user_ISR); 
}

Gpio_interrupt_status Gpio_pin::disable_interrupt(void)
{
      return imp->disable_interrupt();  
}

// IMPLEMENT PRIVATE FUNCTIONS.

// DECLARE ISRs

// Each ISR calls the user specified function, by invoking the function pointer in the array of function pointers.

// This offset is here because the interrupts are enumerated, not in the same order as the function array. This is because the number of interrupts changes with architecture.

SIGNAL(INT0_vect) {
	if(intFunc[EINT_0 - INT_DIFF_OFFSET]) 
		intFunc[EINT_0 - INT_DIFF_OFFSET]();
}

SIGNAL(INT1_vect) {
	if(intFunc[EINT_1 - INT_DIFF_OFFSET])
		intFunc[EINT_1 - INT_DIFF_OFFSET]();
}

SIGNAL(INT2_vect) {
	if(intFunc[EINT_2 - INT_DIFF_OFFSET])
		intFunc[EINT_2 - INT_DIFF_OFFSET]();
}

SIGNAL(INT3_vect) {
	if(intFunc[EINT_3 - INT_DIFF_OFFSET])
		intFunc[EINT_3 - INT_DIFF_OFFSET]();
}

#if (defined(__AVR_ATmega2560__)) || (defined(__AVR_AT90CAN128__))
SIGNAL(INT4_vect) {
	if(intFunc[EINT_4 - INT_DIFF_OFFSET])
		intFunc[EINT_4 - INT_DIFF_OFFSET]();
}

SIGNAL(INT5_vect) {
	if(intFunc[EINT_5 - INT_DIFF_OFFSET])
		intFunc[EINT_5 - INT_DIFF_OFFSET]();
}

SIGNAL(INT6_vect) {
	if(intFunc[EINT_6 - INT_DIFF_OFFSET])
		intFunc[EINT_6 - INT_DIFF_OFFSET]();
}

SIGNAL(INT7_vect) {
	if(intFunc[EINT_7 - INT_DIFF_OFFSET])
		intFunc[EINT_7 - INT_DIFF_OFFSET]();
}
#endif

#if defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega2560__)
SIGNAL(PCINT0_vect) {
	if(intFunc[PCINT_0])
		intFunc[PCINT_0]();
}

SIGNAL(PCINT1_vect) {
	if(intFunc[PCINT_1])
		intFunc[PCINT_1]();
}

SIGNAL(PCINT2_vect) {
	if(intFunc[PCINT_2])
		intFunc[PCINT_2]();
}
#endif

/* ********************** Gpio_pin_imp methods ********************** */ 

Gpio_io_status Gpio_pin_imp::set_mode(Gpio_mode mode)
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
	
	#elif defined (__AVR_AT90CAN128__) || (__AVR_ATmega64M1__)
		_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) & ~(1 << address.pin) ) | (wmode?(1 << address.pin):0);
	#else
		#error "No GPIO mode set implemented for this configuration"
	#endif
	
	if (mode == GPIO_INPUT_FL)
	{
		write(GPIO_O_LOW);		//write to PORTx to enable pull up
	} 
	
	// All done.	
	return GPIO_SUCCESS;
}
		
void Gpio_pin_imp::write (Gpio_output_state value)
{
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
		#elif defined (__AVR_AT90CAN128__) || (__AVR_ATmega64M1__)
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
		#elif defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__)
			// Set or Clear pin on port.
			_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = ( _SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | (value ? (1 << address.pin) : (pin_t) GPIO_O_LOW);
		#else
			#error "No GPIO write implemented for this configuration"
		#endif
	}

	// All done.
	return;
}
		
Gpio_input_state Gpio_pin_imp::read(void)
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
	#elif defined(__AVR_AT90CAN128__) || defined(__AVR_ATmega64M1__)
		return ((_SFR_IO8((address.port * PORT_MULTIPLIER) + P_READ) & (1 << address.pin)) ? GPIO_I_LOW : GPIO_I_HIGH);
	#else
		#error "No GPIO read implemented for this configuration"
	#endif 
}
				
Gpio_interrupt_status Gpio_pin_imp::enable_interrupt(Gpio_interrupt_mode mode, void (*userFunc)(void))
{
	
	// If target has PCINT pins, check to see if pin is a on a PCINT bank
	#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega64M1__)
	if( ( PC_INT[address.port][address.pin] >= PCINT_0 )  && ( PC_INT[address.port][address.pin] < NUM_BANKS ) ) 
	{
		// Change the value in the function pointer array to that given by the user.
		intFunc[PC_INT[address.port][address.pin]] = (voidFuncPtr) userFunc;

		// Check which PCINT bank it is on, and set interrupt accordingly.
		switch ((uint8_t)PC_INT[address.port][address.pin]) 
		{
			case PCINT_0:
				PCICR |= (1 << PCINT_0);
				PCMSK0 = (1 << address.pin);
				break;
			
			case PCINT_1:
				PCICR |= (1 << PCINT_1);
				#if defined(__AVR_ATmega2560__)
				// Mostly the pins' position on the interrupt bank matches their position on their port, however pins PORTJ(0-6) match mask bits PCIE1(1-7).
				PCMSK1 = (address.port == PORT_J) ? (1 << (address.pin - 1)) : (1 << address.pin);
				#elif defined(__AVR_ATmega64M1__) || defined(__AVR_AT90CAN128__)
				PCMSK1 = (1 << address.pin);
				#else
					#error "No PCINT1 defined for this configuration"
				#endif
				break;
			case PCINT_2:
				PCICR |= (1 << PCINT_2);
				PCMSK0 = (1 << address.pin);
				break;
		}
	}
	#else
		#warning "PCINT GPIO interrupts no implemented for this configuration"
	#endif
 
	// All targets have EINT pins, check to see if the pin is one of the special EINT pins
	if (( PC_INT[address.port][address.pin] >= EINT_0)  && ( PC_INT[address.port][address.pin] < (EINT_0 + EXT_INT_SIZE ) ) )
	{ 
		// Configure the interrupt mode (trigger on low input, any change, rising  edge, or falling edge).  The mode constants were chosen to correspond
		// to the configuration bits in the hardware register, so we simply shift the mode into place.
			  
		// Enable the interrupt.
		intFunc[PC_INT[address.port][address.pin] - INT_DIFF_OFFSET] = (voidFuncPtr) userFunc;  
		switch ((uint8_t)PC_INT[address.port][address.pin]) 
		{
		#if defined (__AVR_ATmega2560__) || defined(__AVR_AT90CAN128__)
			case EINT_0:
				// Set the mode of interrupt.
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
				
		#elif defined(__AVR_ATmega64M1__)
			case EINT_0:
				// Set the mode of interrupt.
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
			default:
				// The Given pin does not have an interrupt available to it.
				return GPIO_INT_OUT_OF_RANGE;
		#else
			#error "EINT GPIO interrupts not implemented for this configuration."
		#endif
		}     
	}	  
	
	// All done.
	return GPIO_INT_SUCCESS;		  
}

Gpio_interrupt_status Gpio_pin_imp::disable_interrupt(void) 
{
	// If target has PCINT pins, check to see if pin is a on a PCINT bank
	#if defined (__AVR_ATmega2560__) || defined (__AVR_ATmega64M1__)
	if ((PC_INT[address.port][address.pin] >= PCINT_0)  && (PC_INT[address.port][address.pin] < NUM_BANKS)) 
	{
		// If semaphore is taken.
		switch ((uint8_t) PC_INT[address.port][address.pin]) 
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
		switch ((uint8_t)PC_INT[address.port][address.pin]) 
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
				
		#elif defined (__AVR_ATmega64M1__)
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
		intFunc[PC_INT[address.port][address.pin] - INT_DIFF_OFFSET] = NULL;
	}

	// All done.
	return GPIO_INT_SUCCESS;
}

// ALL DONE.

