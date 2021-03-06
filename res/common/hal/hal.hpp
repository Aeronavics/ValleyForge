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
 *  @addtogroup		hal	Hardware Abstraction Library
 *
 *  @file 		
 *  Sets up the hal, defines types and enumerations, and regulates semaphores. This is the header file which matches hal.c.  
 *  It provides important common functionality required to allow using the ValleyForge HAL.
 *
 *  @addtogroup		hal	Hardware Abstraction Library
 *
 *  @author		Edwin Hayes
 *
 *  @date		11-12-2011
 *
 *  @section Licence
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
 *  @section Description
 *  In order to use the Hardware Abstraction Library, some aspects need to be set up beforehand. There are also some
 *  functions that are relevant to all modules, such as global interrupts, and are therefore placed in this separate
 *  hal.hpp header file.
 * 
 *  @section Example
 * 
 *  @code
 *  #include "hal/hal.hpp"
 *  #include "hal/gpio.hpp"
 * 
 *  init_hal();
 * 
 *  int_on();
 *  
 *  gpio_pin_address my_pin_address;
 *  my_pin_address.port = PORT_B;
 *  my_pin_address.pin = PIN_5;
 *  gpio_pin my_pin = gpio_pin::grab(my_pin_address);
 *  if (my_pin.is_valid())
 *  {
 *  	my_pin.set_mode(OUTPUT);
 *  	my_pin.write(HIGH);
 *  }
 *  @endcode 
 */

/**
 * @mainpage
 * 
 * Welcome to the ValleyForge Doxygen Documentation.
 *
 * TODO - Fix me!
 */

// Only include this header file once.
#ifndef __HAL_H__
#define __HAL_H__

// INCLUDE REQUIRED HEADER FILES.
#include "target_config.hpp"	// Include target specific configuration.

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// DEFINE PUBLIC MACROS.

#define F_CPU <<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>000000UL


// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// General structure for handling IO pin addresses.
struct IO_pin_address
{
	port_t port;
	pin_t pin;
};

// Macro for convenience. Usage:
//   IO_pin_address pinaddr = _IOADDR(PORT_A, PIN_0);
#define _IOADDR(port, pin) ((IO_pin_address){port, pin})

// Generic ISR callback
typedef void (*IsrHandler)(void);

// Preferred callback type - Callbacks should always have a way to pass in user data
typedef void (*Callback)(void *context);

// INCLUDE REQUIRED HEADER FILES THAT DEPEND ON TYPES DEFINED HERE.

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

/**
 * Enables global interrupts.
 *
 * @param Nothing.
 * @return Nothing.
 */
void int_on(void);

/**
 * Disables global interrupts.
 *
 * @param Nothing.
 * @return State of interrupts prior to disabling.
 */
bool int_off(void);

#define nop() asm volatile ("nop")

#endif /*__HAL_H__*/

// ALL DONE.
