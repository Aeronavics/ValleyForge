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
 *  @file		ihex.hpp
 *  A header file for the Intel Hex reader. Contains functionality for 
 *  reading Intel Hex format files.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		19-11-2012
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
#ifndef __IHEX_H__
#define __IHEX_H__

// INCLUDE REQUIRED HEADER FILES.

#include <stdint.h>
#include <string>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class Ihex_record
{
public:

	enum Type
	{
		DATA = 0,
		END_OF_FILE,
		EXTENDED_SEG_ADDR,
		START_SEG_ADDR,
		EXTENDED_LINEAR_ADDR,
		START_LINEAR_ADDR,
		INVALID
	};
	 
	// Functions.
	Ihex_record();
	Ihex_record( std::string& line);
	Ihex_record( const Ihex_record & other);
	~Ihex_record();
	
	
	bool is_valid();
	bool validate_checksum();
	
	uint8_t* get_data();
	size_t get_length();
	
	uint16_t get_address();
	
	Type get_type();
	
	void describe(std::string& str);
	
	
private:
	// Functions.
	bool parse(std::string& line);
	
	//Fields.
	uint8_t* data;
	size_t length;
	Type type;
	uint16_t address;
	bool valid;
	uint8_t checksum;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__IHEX_H__*/

//ALL DONE.

