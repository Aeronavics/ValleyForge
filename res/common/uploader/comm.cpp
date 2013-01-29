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
 *  FILE: 		comm.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Comm Modules
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	27-11-2012
 *
 *	Implementation of the common function for the abstract Communication Module
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "comm.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

std::string Device_info::get_name()
{
	return name;
}

void Device_info::set_name(std::string new_name)
{
	name = new_name;
}

uint32_t Device_info::get_signature()
{
	return signature;
}

void Device_info::set_signature(uint32_t new_signature)
{
	signature = new_signature;
}

uint8_t Device_info::get_version_minor()
{
	return version_minor;
}

void Device_info::set_version_minor(uint8_t new_version)
{
	version_minor = new_version;
}

uint8_t Device_info::get_version_major()
{
	return version_major;
}

void Device_info::set_version_major(uint8_t new_version)
{
	version_major = new_version;
}


Comm_module::Comm_module(std::string name)
{
	if (get_registry().find(name) == get_registry().end())
	{
		get_registry().insert(std::pair<std::string,Comm_module*>(name, this));
	}
}

Comm_module::~Comm_module()
{
	//Do nothing by default here.
}

Comm_module_registry& Comm_module::get_registry()
{
	if (the_registry == NULL)
	{
		the_registry = new Comm_module_registry;
	}
	return *the_registry;
}

// IMPLEMENT PRIVATE FUNCTIONS.

Comm_module_registry* Comm_module::the_registry = NULL;

//ALL DONE.
