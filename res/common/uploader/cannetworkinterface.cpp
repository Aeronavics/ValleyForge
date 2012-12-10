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

CANMessage::CANMessage() :
	id(0),
	length(0)
{
	for (size_t i = 0; i < 8; i++)
	{
		this->data[i] = 0;
	}
}

CANMessage::CANMessage( uint32_t id, size_t length, uint8_t* data) :
	id(id),
	length(length)
{
	for (size_t i = 0; i < length; i++)
	{
		this->data[i] = data[i];
	}
}
	
const uint8_t* CANMessage::getData() const
{
	return &data[0];
}

size_t CANMessage::getLength() const
{
	return length;
}

uint32_t CANMessage::getId() const
{
	return id;
}

void CANMessage::setLength(size_t newLength)
{
	length = newLength;
}

void CANMessage::setId(uint32_t newId)
{
	id = newId;
}

uint8_t* CANMessage::getContent()
{
	return &data[0];
}



CANNetworkInterface::CANNetworkInterface()
{

}

CANNetworkInterface::~CANNetworkInterface()
{

}

bool CANNetworkInterface::setFilter( uint32_t id, action act)
{
	inclusionFilter.insert(id);
	return true;
}

bool CANNetworkInterface::setFilterMode( mode m)
{
	filterMode = m;
	return true;
}

bool CANNetworkInterface::removeFilter( uint32_t id)
{
	inclusionFilter.erase(id);
	exclusionFilter.erase(id);
	return true;
}

bool CANNetworkInterface::clearFilter()
{
	inclusionFilter.clear();
	exclusionFilter.clear();
	return true;
}

bool CANNetworkInterface::filter(uint32_t id)
{
	if (inclusionFilter.find(id) != inclusionFilter.end())
	{
		return true;
	}
	return false;
}


// IMPLEMENT PRIVATE FUNCTIONS.

