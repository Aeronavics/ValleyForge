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
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "bittwiddling.h"

#include <stdio.h>
#include <hal/hal.hpp>
#include <hal/gpio.hpp>
#include <io.h>

// Don't need a an imp class here.
class Gpio_pin_imp { };


// The currently configured mode for all GPIO pins
static Gpio_mode pin_modes[NUM_PORTS][NUM_PINS];

// Store the GPIO base addresses for each GPIO port
static uint32_t gpio_base_addresses[NUM_PORTS] = { GPIO_PORTA_BASE, GPIO_PORTB_BASE, GPIO_PORTC_BASE, GPIO_PORTD_BASE, GPIO_PORTE_BASE, GPIO_PORTF_BASE, GPIO_PORTH_BASE };



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
	// The GPIO clock must be enabled before anything can be configured!
	if (!bit_read(SYSCTL_RCGC2_R, pin_address.port))
	{
		// Enable the GPIO peripheral clock, and wait at least 3 clock cycles
		bit_set(SYSCTL_RCGC2_R, pin_address.port);

		// TODO: Wait 3 clock cycles
	}

	// The provided mode can contain multiple options (bitwise ORed together)
	Gpio_mode pin_mode = (mode & 0x000F);
	unsigned int drive_mode = (mode & 0x00F0);	// Drive strength
	unsigned int extra_mode = (mode & 0x0F00); 	// Pull down/up, etc.

	// The register offsets can be computed from the GPIO base address
	uint32_t gpio_base = gpio_base_addresses[pin_address.port];

	// Pin function registers
	volatile uint32_t *dir = (volatile uint32_t *)(gpio_base + GPIO_O_DIR);			// Direction (0:Input, 1:Output)
	volatile uint32_t *afsel = (volatile uint32_t *)(gpio_base + GPIO_O_AFSEL);		// Alternate function (0:GPIO, 1:Alternate)

	// Output drive strength registers
	volatile uint32_t *dr2r = (volatile uint32_t *)(gpio_base + GPIO_O_DR2R);		// 1: Use 2mA drive strength
	volatile uint32_t *dr4r = (volatile uint32_t *)(gpio_base + GPIO_O_DR4R);		// 1: Use 4mA drive strength
	volatile uint32_t *dr8r = (volatile uint32_t *)(gpio_base + GPIO_O_DR8R);		// 1: Use 8mA drive strength
	volatile uint32_t *slr = (volatile uint32_t *)(gpio_base + GPIO_O_SLR);			// 1: Use slew-rate limiting

	// Pin type registers
	volatile uint32_t *odr = (volatile uint32_t *)(gpio_base + GPIO_O_ODR);			// Open-drain (0: Push-pull output, 1: Open-drain output)
	volatile uint32_t *pur = (volatile uint32_t *)(gpio_base + GPIO_O_PUR);			// Pull-up resistor (0: Disabled, 1: Enabled)
	volatile uint32_t *pdr = (volatile uint32_t *)(gpio_base + GPIO_O_PDR);			// Pull-down resistor (0: Disabled, 1: Enabled)
	volatile uint32_t *den = (volatile uint32_t *)(gpio_base + GPIO_O_DEN);			// Digital mode (0: Analog, 1: Digital)


	switch (pin_mode)
	{
		// Push-pull output
		case GPIO_OUTPUT:
		{
			bit_write(*den, pin_address.pin, 1);
			bit_write(*dir, pin_address.pin, 1);
			bit_write(*afsel, pin_address.pin, 0);
			break;
		};

		// Open-drain output
		case GPIO_OUTPUT_OPENDRAIN:
		{
			bit_write(*den, pin_address.pin, 1);
			bit_write(*dir, pin_address.pin, 1);
			bit_write(*afsel, pin_address.pin, 0);
			extra_mode |= GPIO_FLAG_OPENDRAIN;		// Force open-drain
			break;
		};

		// Digital input
		case GPIO_INPUT:
		{
			bit_write(*den, pin_address.pin, 1);
			bit_write(*dir, pin_address.pin, 0);
			bit_write(*afsel, pin_address.pin, 0);
			break;
		};

		// Analog input
		case GPIO_INPUT_ANALOG:
		{
			bit_write(*den, pin_address.pin, 0);
			bit_write(*dir, pin_address.pin, 0);
			bit_write(*afsel, pin_address.pin, 0);

			bit_write(*odr, pin_address.pin, 0);
			bit_write(*pur, pin_address.pin, 0);
			bit_write(*pdr, pin_address.pin, 0);
			break;
		};

		// Hardware peripheral function
		case GPIO_HWFUNC:
		{
			// In order to enable peripheral functions on a pin, GPIO_HWFUNC must be used.
			// In HW mode the pin direction does not need to be set,
			// but additional flags can still be used depending on the peripheral (eg. open-drain for I2C)
			bit_write(*den, pin_address.pin, 1);
			bit_write(*afsel, pin_address.pin, 1);
			break;
		};

		default:
			return GPIO_ERROR;
	}


	// Set pull-up/pull-down/open-drain (digital only!)
	if (pin_mode != GPIO_INPUT_ANALOG)
	{
		// TODO - I think both can be enabled at the same time?
		bit_write(*pur, pin_address.pin, (extra_mode & GPIO_FLAG_PULLUP) ? 1 : 0);
		bit_write(*pdr, pin_address.pin, (extra_mode & GPIO_FLAG_PULLDOWN) ? 1 : 0);
		bit_write(*odr, pin_address.pin, (extra_mode & GPIO_FLAG_OPENDRAIN) ? 1 : 0);
	}


	// Set output drive current (output only!)
	if (pin_mode == GPIO_OUTPUT || pin_mode == GPIO_OUTPUT_OPENDRAIN || pin_mode == GPIO_HWFUNC)
	{
		switch (drive_mode)
		{
			case GPIO_FLAG_DRIVE_2MA:
			{
				bit_write(*dr2r, pin_address.pin, 1);
				bit_write(*slr, pin_address.pin, 0);
				break;
			};

			case GPIO_FLAG_DRIVE_4MA:
			{
				bit_write(*dr4r, pin_address.pin, 1);
				bit_write(*slr, pin_address.pin, 0);
				break;
			};

			case GPIO_FLAG_DRIVE_8MA:
			{
				bit_write(*dr8r, pin_address.pin, 1);
				bit_write(*slr, pin_address.pin, 0);
				break;
			};

			case GPIO_FLAG_DRIVE_8MA_SC:
			{
				bit_write(*dr8r, pin_address.pin, 1);
				bit_write(*slr, pin_address.pin, 1);
				break;
			};
		}
	}

	// Set the global pin mode
	// Note that the extra flags are not stored in this.
	pin_modes[pin_address.port][pin_address.pin] = pin_mode;
}

Gpio_input_state Gpio_pin::read(void)
{
	// Check we're not reading an output
	Gpio_mode mode = pin_modes[pin_address.port][pin_address.pin];
	if (mode != GPIO_INPUT && mode != GPIO_INPUT_ANALOG)
		return GPIO_I_ERROR;

	uint32_t gpio_base = gpio_base_addresses[pin_address.port];

	// Use special mask-addressing to access the pin value (see the datasheet)
	return (HWREG(gpio_base + (GPIO_O_DATA + (pin_address.pin << 2))) != 0) ?
		GPIO_I_HIGH : GPIO_I_LOW;
}

Gpio_io_status Gpio_pin::write(Gpio_output_state value)
{
	// Check we're not writing an input
	Gpio_mode mode = pin_modes[pin_address.port][pin_address.pin];
	if (mode != GPIO_OUTPUT && mode != GPIO_OUTPUT_OPENDRAIN)
		return GPIO_ERROR;

	uint32_t gpio_base = gpio_base_addresses[pin_address.port];

	if (value == GPIO_O_TOGGLE)
	{
		HWREG(gpio_base + (GPIO_O_DATA + (pin_address.pin << 2))) = ~HWREG(pin_address.port + (GPIO_O_DATA + (pin_address.pin << 2)));
	}
	else
	{
		HWREG(gpio_base + (GPIO_O_DATA + (pin_address.pin << 2))) = (value & 1);  // &1 for safety.
	}

	return GPIO_SUCCESS;
}

Gpio_interrupt_status Gpio_pin::enable_interrupt(Gpio_interrupt_mode mode, void (*func_pt)())
{
	// TODO - Implement interrupts
	return GPIO_INT_OUT_OF_RANGE;
}

Gpio_interrupt_status Gpio_pin::disable_interrupt(void)
{
	// TODO - Implement interrupts
	return GPIO_INT_OUT_OF_RANGE;
}


