// Copyright (C) 2012 Unison Networks Ltd
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

#include <fstream>
#include <iostream>


#include "ihex.hpp"

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.


// IMPLEMENT PUBLIC FUNCTIONS.

Memory_map::Memory_map(size_t size, Memory_map::Type_flag type) :
memory(new uint8_t[size]),
allocated_map(new Memory_map::Allocated_flag[size]),
type(type),
size(size)
{
	//Nothing to do here.
}

Memory_map::~Memory_map()
{
	delete [] memory;
	delete [] allocated_map;
}

uint8_t* Memory_map::get_memory()
{
	return memory;
}

Memory_map::Allocated_flag* Memory_map::get_allocated_map()
{
	return allocated_map;
}

Memory_map::Type_flag Memory_map::get_type()
{
	return type;
}

size_t Memory_map::get_size()
{
	return size;
}


bool Memory_map::find_last_allocated_page(size_t pageSize, size_t& pageStartAddress)
{
	int64_t tempAddress = -1;
	for (size_t pageAddress = 0; pageAddress < size; pageAddress += pageSize)
	{
		if (allocated_map[pageAddress] == ALLOCATED)
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


bool Memory_map::read_from_ihex_file( std::string filename )
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
			Ihex_record record(line);
			if (record.is_valid())
			{
				switch (record.get_type())
				{
					case Ihex_record::DATA:
						if (baseaddr + record.get_length() >= size)
						{
							line.clear();
							record.describe(line);
							std::cerr << "Data outside of available memory (" << lineNumber << ") " << line << std::endl;
							return false;
						}
						nextaddr = baseaddr + record.get_address();
						for (size_t i = 0; i < record.get_length(); i++)
						{
							if (nextaddr + i >= size)
							{
								line.clear();
								record.describe(line);
								std::cerr << "Data outside of available memory (" << lineNumber << ") " << line << std::endl;
								return false;
							}
							memory[nextaddr + i] = record.get_data()[i];
							allocated_map[nextaddr + i] = ALLOCATED;
						}
						break;
						
					case Ihex_record::END_OF_FILE:
						return true;
						break;
					
					case Ihex_record::EXTENDED_SEG_ADDR:
						if (record.get_length() != 2 || record.get_address() != 0)
						{
							line.clear();
							record.describe(line);
							std::cerr << "Invalid extended segment address record encountered (" << lineNumber << ") " << line << std::endl;
							return false;
						}
						baseaddr = ((record.get_data()[0] << 8) | record.get_data()[1] ) << 4;
						if ( baseaddr >= size)
						{
							std::cerr << "Address specified outside of available memory (" << lineNumber << ") " << baseaddr << std::endl;
							return false;
						}
						break;
					
					case Ihex_record::EXTENDED_LINEAR_ADDR:
						if (record.get_length() != 2 || record.get_address() != 0)
						{
							line.clear();
							record.describe(line);
							std::cerr << "Invalid extended linear address record encountered (" << lineNumber << ") " << line << std::endl;
							return false;
						}
						baseaddr = ((record.get_data()[0] << 8) | record.get_data()[1] ) << 16;
						if ( baseaddr >= size)
						{
							std::cerr << "Address specified outside of available memory (" << lineNumber << ") " << baseaddr << std::endl;
							return false;
						}
						break;
						
					case Ihex_record::START_SEG_ADDR:
					case Ihex_record::START_LINEAR_ADDR:
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

bool Memory_map::read_from_file( std::string filename)
{
	size_t length = filename.length();
	if (length >= 4 )
	{
		std::string extension = filename.substr(length-4, 4);
		if (extension == ".hex")
		{
			return read_from_ihex_file(filename);
		}
	}
	return false;
}

// IMPLEMENT PRIVATE FUNCTIONS.


//ALL DONE.
