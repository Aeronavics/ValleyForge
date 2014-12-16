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
	GPIO_OUTPUT,		// Push-pull output
	GPIO_INPUT,			// Digital input

	GPIO_INPUT_PD,		// Input with pull-down enabled
	GPIO_INPUT_PU,		// Input with pull-up enabled
	GPIO_OUTPUT_OD,		// Open-drain output
	GPIO_INPUT_AN,		// Analog input
};

// Drive modes
#define GPIO_DRIVE_2MA 0 // TODO
#define GPIO_DRIVE_4MA 0
#define GPIO_DRIVE_8MA 0
#define GPIO_DRIVE_LIMIT_SLEW 0


#endif // __TARGET_CONFIG_H__