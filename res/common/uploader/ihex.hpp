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
#ifndef IHEX_H_
#define IHEX_H_

// INCLUDE REQUIRED HEADER FILES.

#include <stdint.h>
#include <string>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class IHexRecord
{
public:

	enum e_type
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
	IHexRecord();
	IHexRecord( std::string& line);
	IHexRecord( const IHexRecord & other);
	~IHexRecord();
	
	
	bool isValid();
	bool validateChecksum();
	
	uint8_t* getData();
	size_t getLength();
	
	uint16_t getAddress();
	
	e_type getType();
	
	void describe(std::string& str);
	
	
private:
	// Functions.
	bool parse(std::string& line);
	
	//Fields.
	uint8_t* data;
	size_t length;
	e_type type;
	uint16_t address;
	bool valid;
	uint8_t checksum;
};

 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*IHEX_H_*/
