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
#include "io.h"

// DEFINE PRIVATE MACROS.
typedef enum
{ 
	GPIO_Mode_AIN = 0x0,
	GPIO_Mode_IN_FLOATING = 0x04,
	GPIO_Mode_IPD = 0x28,
	GPIO_Mode_IPU = 0x48,
	GPIO_Mode_Out_OD = 0x14,
	GPIO_Mode_Out_PP = 0x10,
	GPIO_Mode_AF_OD = 0x1C,
	GPIO_Mode_AF_PP = 0x18
} GPIOMode_TypeDef;

typedef enum
{ 
	GPIO_Speed_10MHz = 1,
	GPIO_Speed_2MHz, 
	GPIO_Speed_50MHz
} GPIOSpeed_TypeDef;

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

/* ****************************************************************** */

int8_t gpio_pin_imp::set_mode(gpio_mode mode)
{
	/* Check to see if parameters are right size */
	if (address.port >= NUM_PORTS) 
	{
		/* Parameter is wrong size*/
		return -1;
	}
	
	uint32_t currentmode = 0x00, current_pin = 0x00, pinpos = 0x00, pos=0x00;
	uint32_t tmpreg = 0x00, pinmask = 0x00;
	
	//GPIO Mode configuration for output	
	switch (mode) 
	{
		case(OUTPUT_OD):
			currentmode = ((uint32_t) GPIO_Mode_Out_OD) & ((uint32_t) 0x0F);
			currentmode |= (uint32_t) GPIO_Speed_50MHz;
			break;
		case(OUTPUT_PP):
			currentmode = ((uint32_t) GPIO_Mode_Out_PP) & ((uint32_t) 0x0F);
			currentmode |= (uint32_t) GPIO_Speed_50MHz;
			break;
		case(OUTPUT):
			currentmode = ((uint32_t) GPIO_Mode_Out_PP) & ((uint32_t) 0x0F);
			currentmode |= (uint32_t) GPIO_Speed_50MHz;
			break;
		default:
			break;
	}
	
	//GPIO CRL Configuration for pin 0-8
	if (address.pin < PIN_8)
	{
		tmpreg = port_address->CRL;
		for (pinpos=0x00; pinpos < 0x08; pinpos++)
		{
			pos = ((uint32_t) 0x01) << pinpos;
			/* Get the port pins position */
			currentpin = (1<<address.pin) & pos;
			
			if (currentpin == pos)
			{
				pos = pinpos << 2;
				/* Clear the corresponding low control register bits */
				pinmask = ((uint32_t) 0x0F) << pos;
				tmpreg &= ~pinmask;
				
				/* Write the mode configuration in the corresponding bits */
				tmpreg |= (currentmode << pos);
				
				/* Reset the corresponding ODR bit */
				switch (mode)
				{
					case(INPUT_PD):	//reset ODR bit for pull down
						port_address->BRR = (((uint32_t) 0x01) << pinpos);
						break;
					case(INPUT_PU):	//set ODR but for pull up
						port_address->BSRR = (((uint32_t) 0x01) << pinpos);
						break;
					default:
						break;
				}
			}
		}		
		port_address->CRL = tmpreg;
		tmpreg = 0;
	}
	
	//GPIO CRH Configuration for pin 8-16
	if (address.pin >= PIN_8)
	{
		tmpgreg = port_address->CRH;
		for (pinpos = 0x00; pinpos < 0x08; pinpos++)
		{
			pos = (((uint32_t) 0x01) << (pinpos + 0x08));
			/* Get the port pin's position*/
			currentpin = ((1<<address.pin) & pos);
			if (currentpin == pos)
			{
				pos = pinpos << 2;
				/* Clear the corresponding high control register bits */
				pinmask = ((uint32_t) 0x0F) << pos;
				tmpreg &= ~pinmask;
				
				/* Write the mode configuration in the corresponding bits */
				tmpreg |= (currentmode << pos);
				
				/* Reset the corresponding ODR bit */
				switch (mode)
				{
					case (INPUT_PD): //reset ODR bit for pull down
						port_address->BRR = (((uint32_t) 0x01) << (pinpos + 0x08));
						break;
					case (INPUT_PU): //set ODR but for pull up
						port_address->BSRR = (((uint32_t) 0x01) << (pinpos + 0x08));
						break;
					default:
						break;
				}
			}
		}
		port_address->CRH = tmpreg;
	}
	
	this->mode = mode;
	return 0;
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
		port_address->ODR |= ((uint32_t) (1<<address.pin));
	}
	else if (value == O_HIGH)
	{
		port_address->ODR &= ~(((uint32_t) (1<<address.pin)));
	}
	else if (value == O_TOGGLE) 
	{
		port_address->ODR ^= (((uint32_t) (1<<address.pin)));				
	}
	return 0;		
}

