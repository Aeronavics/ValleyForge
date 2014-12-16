// Copyright (C) 2014  Unison Networks Ltd
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
 *  AUTHOR: 		Jared Sanson
 *
 *  DATE CREATED:	17-12-2014
 *
 *	This is the implementation for gpio for the LM3S1968 series microcontrollers
 *
 ********************************************************************************************************************************/

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

#include "target_config.hpp"

#include <stdio.h>
#include <hal/hal.hpp>
#include <hal/gpio.hpp>



Gpio_pin::Gpio_pin(IO_pin_address address)
{
	pin_address = address;
}

Gpio_pin::~Gpio_pin()
{
	// Don't need to do anything
}

Gpio_io_status Gpio_pin::set_mode(Gpio_mode mode)
{
	switch (mode)
	{
		case GPIO_OUTPUT:
		{
			break;
		};

		case GPIO_OUTPUT_OD:
		{
			break;
		};

		case GPIO_INPUT:
		{
			break;
		};

		case GPIO_INPUT_PD:
		{
			break;
		};

		case GPIO_INPUT_PU:
		{
			break;
		};

		case GPIO_INPUT_AN:
		{
			break;
		};


		default:
			return GPIO_ERROR;
	}
}

Gpio_input_state Gpio_pin::read(void)
{
	return GPIO_I_ERROR;
}

Gpio_io_status Gpio_pin::write(Gpio_output_state value)
{
	return GPIO_ERROR;
}

Gpio_interrupt_status Gpio_pin::enable_interrupt(Gpio_interrupt_mode mode, void (*func_pt)())
{
	return GPIO_INT_OUT_OF_RANGE;
}

Gpio_interrupt_status Gpio_pin::disable_interrupt(void)
{
	return GPIO_INT_OUT_OF_RANGE;
}


