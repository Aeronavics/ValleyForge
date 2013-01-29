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
 * Copyright (C) 2012  Unison Networks Ltd
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
#ifndef __MEMORY_H__
#define __MEMORY_H__

// INCLUDE REQUIRED HEADER FILES.

#include <stdint.h>
#include <string>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class Memory_map
{
public:

	enum Allocated_flag
	{
		UNALLOCATED = 0,
		ALLOCATED
	};
	
	enum Type_flag
	{
		EEPROM = 0,
		FLASH,
		RAM
	};
	
	// Functions.
	Memory_map( size_t size, Type_flag type );
	virtual ~Memory_map();
	
	uint8_t* get_memory();
	Allocated_flag* get_allocated_map();
	Type_flag get_type();
	size_t get_size();
	
	bool find_last_allocated_page(size_t page_size, size_t& page_start_address);
	
	virtual bool read_from_ihex_file( std::string filename );
	//Reads from a file, must determine the filetype itself, mostly here for possible extension by subclasses.
	//The implementation here will just call the hexfile reading function above if the filename ends in .hex.
	virtual bool read_from_file( std::string filename);
	
private:
	// Functions.
	//Make the object not default constructable or assignable.
	Memory_map();
	Memory_map( const Memory_map & other);
	Memory_map& operator= ( const Memory_map& other );
	
	
	//Fields.
	uint8_t* memory;
	Allocated_flag* allocated_map;
	Type_flag type;
	size_t size;

};
 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__MEMORY_H__*/

//ALL DONE.

