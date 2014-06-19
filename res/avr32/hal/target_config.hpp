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

/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file		target_config.hpp
 * Provides definitions for to be used in implementations.
 * 
 * @author 		Zac Frank
 *
 * @date		15-12-2011
 *  
 * @section Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
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
 * This contains device specific definitions for AVR32. Information such as timer size, interrupt
 * specifications and so on are defined here.
 */

// Only include this header file once.
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// DEFINITIONS WHICH ARE SPECIFIC TO INDIVIDUAL MCU TYPES.

#if defined (__AT32UC3C0512C__)
	#define NUM_PORTS		4
	#	define NUM_PINS			32
	
	#	define T0_SIZE			16
	#	define T0_PWM			1
	#	define T0_OC			2
	#	define T0_IC			2
	#	define T0_AS			0
	#	define T0_REV			1

	#	define T1_SIZE			16
	#	define T1_PWM			1
	#	define T1_OC			2
	#	define T1_IC			2
	#	define T1_AS			0
	#	define T1_REV			1

	#	define T2_SIZE			16
	#	define T2_PWM			1
	#	define T2_OC			2
	#	define T2_IC			2
	#	define T2_AS			0
	#	define T2_REV			1

	#	define T3_SIZE			32
	#	define T3_PWM			1
	#	define T3_OC			2
	#	define T3_IC			0
	#	define T3_AS			1
	#	define T3_REV			0

	#	define T4_SIZE			0
	#	define T5_SIZE			0

#else
	#error "No peripheral definition for this configuration."
#endif

// DEFINITIONS WHICH ARE COMMON TO ALL AVR32 ARCHITECTURE TARGETS.

#define TOTAL_PINS			(NUM_PORTS * PINS_PER_PORT)

#endif /*__TARGET_CONFIG_H__*/
