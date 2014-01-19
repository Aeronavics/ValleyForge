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
 * @file		target_config.h
 * Provides definitions for to be used in implementations.
 * 
 * @todo This file should really be split up and put into the implementation folders, not the general ones.
 * 
 * @author 		George Xian
 *
 * @date		08-01-2014T
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
 * This contains device specific definitions for avr. Information such as timer size, interrupt
 * specifications and so on are defined here.
 */
 
// Only include this header file once.
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>


enum int_bank_t {EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15};		//higher number EXTI linked to other functions

/* *** GPIO *** */
#define NUM_PORTS 5
#define NUM_PINS  16

/* *** Timers ** */
#define T1_SIZE   16
#define T1_PWM    4		//need to make sure
#define T1_OC	  4		//need to make sure
#define T1_IC     4		//need to make sure
#define T1_AS	  //TODO
#define T1_REV    //TODO

#define T2_SIZE   16

#define T3_SIZE   16

#define T4_SIZE	  16


#define NUM_BANKS 15 	//need to make sure

#define NUM_16_BIT_TIMERS 	4
#define NUM_TIMERS			NUM_16_BIT_TIMERS

//need to make sure of this interrupt configuration
static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =  {{EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15},	// A
							{EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15},				// B
							{EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15},  	// C
							{EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15},  			// D
							{EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5, EXTI6, EXTI7, EXTI8, EXTI9, EXTI10, EXTI11, EXTI12, EXTI13, EXTI14, EXTI15}};				// E
				

#endif /*__TARGET_CONFIG_H__*/
