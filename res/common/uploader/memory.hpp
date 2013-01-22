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
 *  @file		memory.hpp
 *  A header file for representing a memory map.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		20-11-2012
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
#ifndef MEMORY_H_
#define MEMORY_H_

// INCLUDE REQUIRED HEADER FILES.

#include "stdint.h"
#include <string>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class MemoryMap
{
public:

	enum allocatedFlag
	{
		UNALLOCATED = 0,
		ALLOCATED
	};
	
	enum typeFlag
	{
		EEPROM = 0,
		FLASH,
		RAM
	};
	
	// Functions.
	MemoryMap( size_t size, typeFlag type );
	virtual ~MemoryMap();
	
	uint8_t* getMemory();
	allocatedFlag* getAllocatedMap();
	typeFlag getType();
	size_t getSize();
	
	bool findLastAllocatedPage(size_t pageSize, size_t& pageStartAddress);
	
	virtual bool readFromIHexFile( std::string filename );
	//Reads from a file, must determine the filetype itself, mostly here for possible extension by subclasses.
	//The implementation here will just call the hexfile reading function above if the filename ends in .hex.
	virtual bool readFromFile( std::string filename);
	
private:
	// Functions.
	//Make the object not default constructable or assignable.
	MemoryMap();
	MemoryMap( const MemoryMap & other);
	MemoryMap& operator= ( const MemoryMap& other );
	
	
	//Fields.
	uint8_t* memory;
	allocatedFlag* allocatedMap;
	typeFlag type;
	size_t size;

};
 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*MEMORY_H_*/
