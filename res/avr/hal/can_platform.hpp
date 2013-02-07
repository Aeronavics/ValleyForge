// Copyright (C) 2013  Unison Networks Ltd
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
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file		can_platform.hpp
 *  A header file for the AVR platform specific types for the CAN Module of the HAL.
 * 
 *  @brief 
 *  This is the header file which implements various public types and enums that will differ between platforms for the can module.
 * 
 *  @author		Paul Davey
 *
 *  @date		7-02-2013
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2013  Unison Networks Ltd
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
 *
 * These are the public enums and types that are specific to the AVR platform.
 */

// Only include this header file once.
#ifndef __CAN_PLATFORM_H__
#define __CAN_PLATFORM_H__

// INCLUDE REQUIRED HEADER FILES.

#include <stdint.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// AVRs have only one CAN interface.
enum Can_number {CAN_0};

// The ATMega64M1 has only 6 message objects, this would be #ifdef'd for the at90can128 which has 15.
enum Can_object { OBJ0, OBJ1, OBJ2, OBJ3, OBJ4, OBJ5 };

// Same thing here, each message object has a filter.
enum Can_filter { FILTER0, FILTER1, FILTER2, FILTER3, FILTER4, FILTER5 };

// This needs to be defined to hold the relevent data for a filter on this platform, on the AVR this is a 32 bit ID and a 32 bit mask,
// with defined bit positions for the extended frame flag and the remote transmit flag.
struct Can_filter_data
{
	uint32_t id;
	uint32_t mask;
}

// This needs to be defined to hold the specific status for message objects on this platform, this will likely have a common field for if a message is waiting in it and whether it is a transmit or receive object.
struct Can_obj_status;

// This needs to be defined to hold the specific status for the AVR CAN controller.
struct Can_status;


// FORWARD DEFINE PRIVATE PROTOTYPES.


// DEFINE PUBLIC CLASSES.


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__CAN_PLATFORM_H__*/

// ALL DONE.
