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


// DECLARE IMPORTED GLOBAL VARIABLES.
extern semaphore semaphores[NUM_PORTS][NUM_PINS];
extern semaphore pc_int_sem[NUM_BANKS];

/**
 * A Class that implements the functions for gpio
 * One instance for each pin.
 * Reads, writes, and sets direction of pins
 */
class gpio_pin_imp
{
	public:

		// Functions.
		/**
		 * Sets the direction of the pin
		 * by manipulating the data direction register
		 * 
		 * @param mode	the direction (INPUT=0,OUTPUT=1)
		 * @return gpio_input_state error code
		 */
		int8_t set_mode(gpio_mode mode);

		/**
		 * Writes to the pin attached to the implementation
		 * 
		 * @param value	sets the pin to (O_LOW, O_HIGH, or O_TOGGLE)
		 * @return int8_t error code
		 */
		int8_t write (gpio_output_state value);

		/**
		 * Reads the pin attached to the implementation
		 * 
		 * @param Nothing.
		 * @return int8_t error code
		 */
		gpio_input_state read (void);
		
		/**
		 * Attaches an interrupt to the pin and enables said interrupt.
		 * 
		 * @param address	The gpio pin address in terms of port and pin
		 * @param *userFunc	A pointer to the user's ISR
		 * @param mode		What kind of interrupt (INT_LOW_LEVEL, INT_ANY_EDGE, INT_FALLING_EDGE, INT_RISING_EDGE) (only valid for the EXTINT pins)
		 * @return inter_return_t return code
		 */
		inter_return_t attach_interrupt(void (*userFunc)(void), interrupt_mode mode);
		
		/**
		 * Detaches the interrupt from the pin and disables said interrupt.
		 * 
		 * @param address	The gpio pin address in terms of port and pin
		 * @return inter_return_t return code
		 */
		inter_return_t disable_interrupt(void);
		
	  // Fields.
		gpio_pin_address address;
		gpio_mode mode;
	  
		GPIO_TypeDef* port_address;		//used in hardware addressing
		
		semaphore* s;	
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// One implementation for each pin.
gpio_pin_imp gpio_pin_imps[NUM_PORTS][NUM_PINS];

// To show whether we have carrried out the initialisation yet.
bool done_init;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

void gpio_init(void);

// IMPLEMENT PUBLIC FUNCTIONS.
// See gpio.h for descriptions of these functions.
gpio_pin::~gpio_pin(void)
{
	// Make sure we have vacated the semaphore before we go out of scope.
	vacate();

	// All done.
	return;
}

gpio_pin::gpio_pin(gpio_pin_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

int8_t gpio_pin::set_mode(gpio_mode mode)
{
	return (imp->set_mode(mode));
}

int8_t gpio_pin::write(gpio_output_state value)
{
	return (imp->write(value));
}

gpio_input_state gpio_pin::read(void)
{
	return (imp->read());
}

bool gpio_pin::is_valid(void)
{
	return (imp != NULL);
}

void gpio_pin::vacate(void)
{
	// Check if we're already vacated, since there shouldn't be an error if you vacate twice.
	if (imp != NULL)
	{		
		// We haven't vacated yet, so vacate the semaphore.
		imp->s->vacate();
	}

	// Break the link to the implementation.
	imp = NULL;

	// The gpio_pin is now useless.
	
	// All done.
	return;
}

gpio_pin gpio_pin::grab(gpio_pin_address address)
{
	// Check if the GPIO stuff has been initialized.
	if (!done_init)
	{
		// Initialize the GPIO stuff.
		gpio_init();
	}

	// Try to procure the semaphore.
	if (gpio_pin_imps[address.port][address.pin].s->procure())
	{
		// We got the semaphore!
		return gpio_pin(&gpio_pin_imps[address.port][address.pin]);
	}
	else
	{
		// Procuring the semaphore failed, so the pin is already in use.
		return NULL;
	}
}

// IMPLEMENT PRIVATE FUNCTIONS.

void gpio_init(void)
{
	// Attach the gpio pin implementations to the semaphores which control the corresponding pins.
	for (uint8_t i=0; i<NUM_PORTS; i++)
	{
		for (uint8_t j=0; j<NUM_PINS; j++)
		{
			// Attach the semaphores to those in the pin implementations.
			gpio_pin_imps[i][j].s = &semaphores[i][j];
			gpio_pin_imps[i][j].address.port = (port_t)i;
			gpio_pin_imps[i][j].address.pin = (pin_t)j;
			
			// Add a field representing the actual address of the register
			gpio_pin_imps[i][j].port_address = (GPIO_TypeDef *) (GPIOA_BASE + 0x400*i);
		}
	}

	// We don't need to do this again.
	done_init = true;

	// All done.
	return;
}

// DECLARE ISRs

// Each ISR calls the user specified function, by invoking the function pointer in the array of function pointers.
// This offset is here because the interrupts are enumerated, not in the same order as the function array. This is because the number of interrupts changes with architecture.
// TODO
/* ****************************************************************** */

int8_t gpio_pin_imp::set_mode(gpio_mode mode)
{
	/* Check to see if parameters are right size */
	if (address.port >= NUM_PORTS) 
	{
		//Parameter is wrong size
		return -1;
	}
	
	/* Enable the GPIO port */
	RCC->APB2ENR |= (1<<(address.port + 2));
	
	/* Determine value to write to CRL or CRH */
	uint32_t CNFy, MODEy;
	if (mode == INPUT || mode == INPUT_PD || mode == INPUT_PU) 
	{
		MODEy = 0b00;
		if (mode == INPUT)
		{
			//unspecified becomes floating
			CNFy = 0b01;
		}
		else
		{
			//pull up or down is specified on BSRR register
			CNFy = 0b10;
		}
	}
	else if (mode == OUTPUT || mode == OUTPUT_OD || mode == OUTPUT_PP)
	{
		MODEy = 0b11;	//output max speed
		if (mode == OUTPUT || mode == OUTPUT_PP)
		{
			//unspecified becomes push-pull
			CNFy = 0b00;
		}
		else
		{
			//open drain
			CNFy = 0b01;
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
	
	uint8_t CR_offset = (address.pin % 8) * 4;	//CR has 4 bits for each pin
	//make sure the bits that are going to be set are 0 before being set 
	tempreg &= ~((uint32_t) (0b1111<<CR_offset));
	
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
	if (mode == INPUT_PD)
	{
		port_address->BRR |= (1 << address.pin);		
	}
	else if (mode == INPUT_PU)
	{
		port_address->BSRR |= (1 << address.pin);
	}
	return 0;	//mode setup successful
}

gpio_input_state gpio_pin_imp::read(void)
{
	if (address.port >= NUM_PORTS) 
	{
		/* Parameter is wrong size*/
		return I_ERROR;
	}
	
	if (mode == INPUT || mode == INPUT_PD || mode == INPUT_PU)
	{
		if (((uint16_t) port_address->IDR) & (1<<address.pin))
		{
			return I_HIGH;
		}
		else 
		{
			return I_LOW;
		}
	}
	else 
	{
		return I_ERROR;
	}
}

int8_t gpio_pin_imp::write(gpio_output_state value)
{
	if (address.port >= NUM_PORTS)
	{
		/* Parameter is wrong size*/
		return O_ERROR;
	}
	
	if (value == O_LOW)
	{
		port_address->ODR &= ~((uint32_t) (1<<address.pin));
	}
	else if (value == O_HIGH)
	{
		port_address->ODR |= (((uint32_t) (1<<address.pin)));
	}
	else if (value == O_TOGGLE) 
	{
		port_address->ODR ^= (((uint32_t) (1<<address.pin)));				
	}
	return 0;		
}



