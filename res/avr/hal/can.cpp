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

/********************************************************************************************************************************
 *
 *  FILE: 		can.cpp	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	14-11-2012
 *
 *	Functionality to provide implementation for CAN in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

#include <avr/io.h>
#include <avr/interrupt.h>

/********************************************************************************************************************************/
Can_object_mode Can_object::get_mode(void)
{
	
}

bool Can_object::get_multimode(void)
{
	//AVR's MOb's are two way
	return true
}

bool Can_object::set_mode(Can_object_mode mode)
{
	if (mode == CAN_OBJ_TX)
	{
		Can_config_tx();	
	}
	else if (mode == CAN_OBJ_RX)
	{
		Can_config_rx();
	}
}

Can_object_status Can_object::get_status(void)
{
	//TODO
}


/********************************************************************************************************************************/
Can_tree Can::get_tree(void) 
{
	//TODO
}

Can_command_response Can::initialise(Can_rate rate, Can_mode mode)
{
	//TODO
}

void Can::enable_interrupts(void)
{
	//TODO
}

void Can::disable_interrupt(void)
{
	//TODO
}

void Can::attach_interrupt(void) 
{
	//TODO
}

void Can::detach_interrupt(void)
{
	//TODO
}

Can_status Can::get_status(void)
{
	//TODO
}

void Can::transmit(void)
{
	//TODO
}

bool Can::check_ready(Can_object obj)
{
	//TODO
}

Can_message Can::read_object(Can_object obj) 
{
	//TODO
}

Can::~Can(void)
{
	// Make sure we have vacated the semaphore before we go out of scope.
	vacate();
}

void Can::vacate(void) 
{
	//TODO
}


bool done_init = false;
void can_init(void)
{
	done_init = true;
}

Can Can::grab(Can_channel can_channel)
{
	if (!done_init) 
	{
		can_init();
	}
}

Can_tree Can::get_tree(void)
{
	Can_tree
}

