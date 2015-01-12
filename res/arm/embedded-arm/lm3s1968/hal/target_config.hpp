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

/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 *
 * @file		target_config.hpp
 * Provides definitions for to be used in implementations.
 *
 * @author 		Jared Sanson
 *
 * @date		17-12-2014
 *
 * @section Licence
 *
 * Copyright (C) 2014  Unison Networks Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @brief
 * This contains device specific definitions for LM3S1968 (Stellaris) devices.
 * Information such as timer size, interrupt specifications and so on are
 * defined here.
 */

#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

#if defined(__LM3S1968__)
	#define NUM_PORTS	8
	#define NUM_PINS	8

	enum int_bank_t {/*TODO*/};
	enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H};
	enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};
#else
	#error "HAL not supported for this target"
#endif




enum Gpio_mode
{
	GPIO_OUTPUT,			// Push-pull output
	GPIO_INPUT,				// Digital input

	GPIO_OUTPUT_OPENDRAIN,	// Open-drain output
	GPIO_INPUT_ANALOG,		// Analog input

	// (INTERNAL USE)
	GPIO_HWFUNC,			// Hardware peripheral override (set automatically by the HAL module)
};

// The above GPIO modes can be combined with the following flags:
// (Using a bitwise OR)
#define GPIO_FLAG_DRIVE_2MA 0x0000 // (Default)
#define GPIO_FLAG_DRIVE_4MA 0x0010
#define GPIO_FLAG_DRIVE_8MA 0x0020
#define GPIO_FLAG_DRIVE_8MA_SC 0x0030 // 8mA slew rate limited

#define GPIO_FLAG_PULLUP	0x0100
#define GPIO_FLAG_PULLDOWN	0x0200
#define GPIO_FLAG_OPENDRAIN 0x0400	// GPIO_OUTPUT only.

// For backwards compatibility
#define GPIO_OUTPUT_PP GPIO_OUTPUT	// PL = Push-pull. ie. regular output
#define GPIO_INPUT_FL GPIO_INPUT	// FL = Floating. ie. regular input


#endif // __TARGET_CONFIG_H__