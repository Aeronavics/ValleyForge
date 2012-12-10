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
 * 
 *  @file		comm.hpp
 *  A header file for the abstract base class for comms modules.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		27-11-2012
 * 
 *  @section 		Licence
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
 */
 
//Only include header once.
#ifndef COMM_H_
#define COMM_H_

// INCLUDE REQUIRED HEADER FILES.

#include <map>
#include <string>
#include <stdint.h>

#include "util.hpp"

#include "memory.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

class CommModule;

typedef std::map<std::string, CommModule*> CommModuleRegistry;

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

/**
 *  Class to hold the info gotten about the device, such as signatures, bootloader versions and names.
 */
class DeviceInfo
{
public:
	
	// Functions.
	
	std::string getName();
	void setName(std::string newName);
	uint32_t getSignature();
	void setSignature(uint32_t newSignature);
	
private:
	
	// Functions.
	
	// Fields.
	std::string name;
	uint32_t signature;
};

/**
 * This is the abstract base class for all communication modules.
 * This defines the interface needed to be able to program a microcontroller.
 * 
 * Subclasses of this will implement these methods according to how the specific communication method requires the operations to be performed.
 * 
 */
class CommModule
{
public:

	// Functions.
	CommModule(std::string name);
	virtual ~CommModule()=0;
	
	virtual bool init(Params params)=0;
	virtual bool connectToDevice()=0;
	
	virtual bool getDeviceInfo( DeviceInfo& info)=0;
	
	virtual bool writePage(MemoryMap& source, size_t size, size_t address)=0;
	virtual bool verifyPage(MemoryMap& expected, size_t size, size_t address)=0;
	virtual bool readPage(MemoryMap& destination, size_t size, size_t address)=0;
	
	virtual bool resetDevice(bool runApplication)=0;
	
	static CommModuleRegistry& getRegistry();
	
	
private:
	// Functions.
	
	//Fields.
	static CommModuleRegistry* theRegistry;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*COMM_H_*/
