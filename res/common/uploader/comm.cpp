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

std::string DeviceInfo::getName()
{
	return name;
}

void DeviceInfo::setName(std::string newName)
{
	name = newName;
}

uint32_t DeviceInfo::getSignature()
{
	return signature;
}

void DeviceInfo::setSignature(uint32_t newSignature)
{
	signature = newSignature;
}

uint8_t DeviceInfo::getVersionMinor()
{
	return versionMinor;
}

void DeviceInfo::setVersionMinor(uint8_t newVersion)
{
	versionMinor = newVersion;
}

uint8_t DeviceInfo::getVersionMajor()
{
	return versionMajor;
}

void DeviceInfo::setVersionMajor(uint8_t newVersion)
{
	versionMajor = newVersion;
}


CommModule::CommModule(std::string name)
{
	if (getRegistry().find(name) == getRegistry().end())
	{
		getRegistry().insert(std::pair<std::string,CommModule*>(name, this));
	}
}

CommModule::~CommModule()
{

}

CommModuleRegistry& CommModule::getRegistry()
{
	if (theRegistry == NULL)
	{
		theRegistry = new CommModuleRegistry;
	}
	return *theRegistry;
}

// IMPLEMENT PRIVATE FUNCTIONS.

CommModuleRegistry* CommModule::theRegistry = NULL;

