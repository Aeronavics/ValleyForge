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
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	07-01-2014
 *
 *	This is the implementation for gpio for the STM32F10x series micro-controllers
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

#include <stdio.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.
GPIO_TypeDef* port_addresses[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};	//correspond the GPIO register address to the IO_pin_address port field value

// DECLARE IMPORTED GLOBAL VARIABLES.

/**
 * A Class that implements the functions for gpio
 * One instance for each pin.
 * Reads, writes, and sets direction of pins
 */
class Gpio_pin_imp
{
	public:

		// Functions.
		/**
		 * Sets the direction of the pin
		 * by manipulating the data direction register
		 * 
		 * @param mode	the direction (INPUT=0,OUTPUT=1)
		 * @return return code representing whether operation was successful
		 */
		Gpio_io_status set_mode(IO_pin_address address, Gpio_mode mode);

		/**
		 * Writes to the pin attached to the implementation
		 * 
		 * @param value	sets the pin to (O_LOW, O_HIGH, or O_TOGGLE)
		 * @return return code representing whether operation was successful
		 */
		Gpio_io_status write (IO_pin_address address, Gpio_output_state value);

		/**
		 * Reads the pin attached to the implementation
		 * 
		 * @param Nothing.
		 * @return state of the pin
		 */
		Gpio_input_state read (IO_pin_address address);
		
		/**
		 * Attaches an interrupt to the pin and enables said interrupt.
		 * 
		 * @param *userFunc	A pointer to the user's ISR
		 * @param mode		What kind of interrupt (INT_LOW_LEVEL, INT_ANY_EDGE, INT_FALLING_EDGE, INT_RISING_EDGE) (only valid for the EXTINT pins)
		 * @return inter_return_t return code
		 */
		Gpio_io_status enable_interrupt(IO_pin_address address, void (*userFunc)(void), Gpio_interrupt_mode mode);
		
		/**
		 * Detaches the interrupt from the pin and disables said interrupt.
		 * 
		 * @return return code representing whether operation was successful
		 */
		Gpio_io_status disable_interrupt(IO_pin_address address);
		
	  // Fields.
		Gpio_mode pin_modes[NUM_PORTS][NUM_PINS];
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// Implementation class.
Gpio_pin_imp gpio_pin_imp;

// IMPLEMENT PUBLIC FUNCTIONS.
// See gpio.h for descriptions of these functions.

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
	return imp->write(pin_address, value);
}

Gpio_input_state Gpio_pin::read(void)
{
	return (imp->read(pin_address));
}

Gpio_pin Gpio_pin::grab(IO_pin_address address)
{
	RCC->APB2ENR |= (1<<(address.port + 2));	//enable peripheral clock

	Gpio_pin new_gpio_pin = Gpio_pin(&gpio_pin_imp);
	new_gpio_pin.pin_address = address;
	return new_gpio_pin;
}

// DECLARE ISRs

// Each ISR calls the user specified function, by invoking the function pointer in the array of function pointers.
// This offset is here because the interrupts are enumerated, not in the same order as the function array. This is because the number of interrupts changes with architecture.
// TODO
/* ****************************************************************** */

Gpio_io_status Gpio_pin_imp::set_mode(IO_pin_address address, Gpio_mode mode)
{
	GPIO_TypeDef* port_address = port_addresses[address.port];
	
	/* Determine value to write to CRL or CRH */
	uint32_t CNFy, MODEy;
	if (mode == GPIO_INPUT_FL || mode == GPIO_INPUT_PD || mode == GPIO_INPUT_PU || mode == GPIO_INPUT_ANALOG) 
	{
		MODEy = 0b00;
		if (mode == GPIO_INPUT_FL)
		{
			//floating
			CNFy = 0b01;
		}
		else if (mode == GPIO_INPUT_ANALOG)
		{
			CNFy = 0b00; 
		}
		else
		{
			//pull up or down is specified on BSRR register
			CNFy = 0b10;
		}
	}
	else if (mode == GPIO_OUTPUT_OD || mode == GPIO_OUTPUT_PP || mode == GPIO_AF_PP)
	{
		MODEy = 0b11;	//output max speed 50MHz
		if (mode == GPIO_OUTPUT_PP)
		{
			//push-pull
			CNFy = 0b00;
		}
		else if (mode == GPIO_OUTPUT_OD)
		{
			//open drain
			CNFy = 0b01;
		}
		else if (mode == GPIO_AF_PP)
		{
			//alternate function push pull
			CNFy = 0b10;
		}
	}

	/* Write to control register */
	//copy value from selected register
	uint32_t tempreg;
	if (address.pin < 8)
	{
		tempreg = port_address->CRL;
	}
	else 
	{
		tempreg = port_address->CRH;
	}
	
	uint8_t CR_offset = (address.pin % 8) * 4;	//CR represents 8 pins with 4 bits for each pin
	//make sure the bits that are going to be set are 0 before being set 
	tempreg &= ~(0b1111<<CR_offset);
	
	//create the final value for the whole register
	tempreg |= ((CNFy << (CR_offset+2)) | (MODEy << (CR_offset)));
	
	//write to the selected register
	if (address.pin < 8)
	{
		port_address->CRL = tempreg;
	}
	else 
	{
		port_address->CRH = tempreg;
	}
	
	/* if pull-up/down specified, write to BSRR register to set it or BRR
	 * register to reset accordingly */
	if (mode == GPIO_INPUT_PD)
	{
		port_address->BRR |= (1 << address.pin);		
	}
	else if (mode == GPIO_INPUT_PU)
	{
		port_address->BSRR |= (1 << address.pin);
	}
	pin_modes[address.port][address.pin] = mode;	//cache the mode
	return GPIO_SUCCESS;	//mode setup successful
}

Gpio_input_state Gpio_pin_imp::read(IO_pin_address address)
{
	GPIO_TypeDef* port_address = port_addresses[address.port];
	
	if (pin_modes[address.port][address.pin] == GPIO_OUTPUT_OD || pin_modes[address.port][address.pin] == GPIO_OUTPUT_PP)
	{
		return GPIO_I_ERROR;	//can't read from output pin
	}

	if ((port_address->IDR) & (1<<address.pin))
	{
		return GPIO_I_HIGH;
	}
	else 
	{
		return GPIO_I_LOW;
	}
}

Gpio_io_status Gpio_pin_imp::write(IO_pin_address address, Gpio_output_state value)
{
	GPIO_TypeDef* port_address = port_addresses[address.port];
	
	if (pin_modes[address.port][address.pin] == GPIO_INPUT_FL || pin_modes[address.port][address.pin] == GPIO_INPUT_PD || pin_modes[address.port][address.pin] == GPIO_INPUT_PU)
	{
		return GPIO_ERROR;	//can't write to input pin
	}
	
	switch(value)
	{
		case(GPIO_O_LOW): 
			port_address->ODR &= ~(1<<address.pin);
			break;
		case(GPIO_O_HIGH): 
			port_address->ODR |= (1<<address.pin);
			break;
		case(GPIO_O_TOGGLE): 
			port_address->ODR ^= (1<<address.pin);
			break;
		default:
			return GPIO_ERROR;
	}

	return GPIO_SUCCESS;		
}
