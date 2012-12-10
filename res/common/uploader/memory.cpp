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
 *  FILE: 		memory.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Memory Map
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	19-11-2012
 *
 *	Implementation of a Memory map that can be loaded from an IHex file.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "memory.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <iostream>
#include <fstream>

#include "ihex.hpp"

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.


// IMPLEMENT PUBLIC FUNCTIONS.

MemoryMap::MemoryMap(size_t size, MemoryMap::typeFlag type) :
memory(new uint8_t[size]),
allocatedMap(new MemoryMap::allocatedFlag[size]),
type(type),
size(size)
{
	
}

MemoryMap::~MemoryMap()
{
	delete [] memory;
	delete [] allocatedMap;
}

uint8_t* MemoryMap::getMemory()
{
	return memory;
}

MemoryMap::allocatedFlag* MemoryMap::getAllocatedMap()
{
	return allocatedMap;
}

MemoryMap::typeFlag MemoryMap::getType()
{
	return type;
}

size_t MemoryMap::getSize()
{
	return size;
}


bool MemoryMap::findLastAllocatedPage(size_t pageSize, size_t& pageStartAddress)
{
	int64_t tempAddress = -1;
	for (size_t pageAddress = 0; pageAddress < size; pageAddress += pageSize)
	{
		if (allocatedMap[pageAddress] == ALLOCATED)
		{
			tempAddress = pageAddress;
		}
	}
	if (tempAddress < 0)
	{
		return false;
	}
	pageStartAddress = (size_t) tempAddress;
	return true;
}


bool MemoryMap::readFromIHexFile( std::string filename )
{
	std::ifstream file(filename.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!file.good())
	{
		std::cerr << "Could not open file: " << filename << std::endl;
		return false;
	}
	
	size_t baseaddr = 0;
	size_t nextaddr = 0;
	int lineNumber = 1;
	
	while (!file.eof() && file.good())
	{
		
		std::string line;
		getline(file, line);
		if (file.good())
		{
			IHexRecord record(line);
			if (record.isValid())
			{
				switch (record.getType())
				{
					case IHexRecord::DATA:
						if (baseaddr + record.getLength() >= size)
						{
							line.clear();
							record.describe(line);
							std::cerr << "Data outside of available memory (" << lineNumber << ") " << line << std::endl;
							return false;
						}
						nextaddr = baseaddr + record.getAddress();
						for (size_t i = 0; i < record.getLength(); i++)
						{
							memory[nextaddr + i] = record.getData()[i];
							allocatedMap[nextaddr + i] = ALLOCATED;
						}
						break;
						
					case IHexRecord::END_OF_FILE:
						return true;
						break;
					
					case IHexRecord::EXTENDED_SEG_ADDR:
						if (record.getLength() != 2 || record.getAddress() != 0)
						{
							line.clear();
							record.describe(line);
							std::cerr << "Invalid extended segment address record encountered (" << lineNumber << ") " << line << std::endl;
							return false;
						}
						baseaddr = ((record.getData()[0] << 8) | record.getData()[1] ) << 4;
						if ( baseaddr >= size)
						{
							std::cerr << "Address specified outside of available memory (" << lineNumber << ") " << baseaddr << std::endl;
							return false;
						}
						break;
					
					case IHexRecord::EXTENDED_LINEAR_ADDR:
						if (record.getLength() != 2 || record.getAddress() != 0)
						{
							line.clear();
							record.describe(line);
							std::cerr << "Invalid extended linear address record encountered (" << lineNumber << ") " << line << std::endl;
							return false;
						}
						baseaddr = ((record.getData()[0] << 8) | record.getData()[1] ) << 16;
						if ( baseaddr >= size)
						{
							std::cerr << "Address specified outside of available memory (" << lineNumber << ") " << baseaddr << std::endl;
							return false;
						}
						break;
						
					case IHexRecord::START_SEG_ADDR:
					case IHexRecord::START_LINEAR_ADDR:
						//We do nothing with these apparently, but they still end up in files. TODO: Find out what they are for and if they matter.
						break;
						
					default:
						line.clear();
						record.describe(line);
						std::cerr << "Unknown or invalid record encountered (" << lineNumber << ") " << line << std::endl;
						return false;
						break;
				}
			}
		}
		lineNumber++;
	}
	return true;
}

bool MemoryMap::readFromFile( std::string filename)
{
	size_t length = filename.length();
	if (length >= 4 )
	{
		std::string extension = filename.substr(length-4, 4);
		if (extension == ".hex")
		{
			return readFromIHexFile(filename);
		}
	}
	return false;
}

// IMPLEMENT PRIVATE FUNCTIONS.


