// Copyright (C) 2012  Unison Networks Ltd
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
 *  FILE: 		cannetworkinterface.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		CAN Interface
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	5-12-2012
 *
 *	Implementation of the common functions for the abstract CAN Network Interface
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "cannetworkinterface.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

CAN_message::CAN_message() :
	id(0),
	length(0)
{
	for (size_t i = 0; i < 8; i++)
	{
		this->data[i] = 0;
	}
}

CAN_message::CAN_message( uint32_t id, size_t length, uint8_t* data) :
	id(id),
	length(length)
{
	for (size_t i = 0; i < length; i++)
	{
		this->data[i] = data[i];
	}
}
	
const uint8_t* CAN_message::get_data() const
{
	return &data[0];
}

size_t CAN_message::get_length() const
{
	return length;
}

uint32_t CAN_message::get_id() const
{
	return id;
}

void CAN_message::set_length(size_t new_length)
{
	length = new_length;
}

void CAN_message::set_id(uint32_t new_id)
{
	id = new_id;
}

uint8_t* CAN_message::get_content()
{
	return &data[0];
}



CAN_network_interface::CAN_network_interface()
{

}

CAN_network_interface::~CAN_network_interface()
{

}

bool CAN_network_interface::set_filter( uint32_t id, Action act)
{
	if (act == INCLUDE)
	{
		inclusion_filter.insert(id);
	}
	else
	{
		exclusion_filter.insert(id);
	}
	return true;
}

bool CAN_network_interface::set_filter_mode( Mode m)
{
	filter_mode = m;
	return true;
}

bool CAN_network_interface::remove_filter( uint32_t id)
{
	inclusion_filter.erase(id);
	exclusion_filter.erase(id);
	return true;
}

bool CAN_network_interface::clear_filter()
{
	inclusion_filter.clear();
	exclusion_filter.clear();
	return true;
}

bool CAN_network_interface::filter(uint32_t id)
{	
	switch (filter_mode)
	{
	case INCLUDE_ALL:
		return true;
		break;
	case EXCLUDE_ALL_BUT_FILTER:
		return inclusion_filter.find(id) != inclusion_filter.end();
		break;
	case INCLUDE_ALL_BUT_FILTER:
		return exclusion_filter.find(id) != exclusion_filter.end();
		break;
	default:
		return false;
		break;
	}
}


// IMPLEMENT PRIVATE FUNCTIONS.


//ALL DONE.
