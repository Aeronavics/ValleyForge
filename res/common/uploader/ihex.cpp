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
 *  FILE: 		ihex.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Intel Hex reader
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	19-11-2012
 *
 *	Implementation of Intel Hex format reader.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "ihex.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.


#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>



// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

bool parse_record_type(std::string& temp, Ihex_record::Type& type);
std::string type_to_string(Ihex_record::Type type);

// IMPLEMENT PUBLIC FUNCTIONS.

Ihex_record::Ihex_record() :
	data(0),
	length(0),
	type(INVALID),
	address(0),
	valid(false)
{
	//Nothing to do here.
}

Ihex_record::Ihex_record( std::string& line) :
	data(0),
	length(0),
	type(INVALID),
	address(0),
	valid(false)
{
	if (parse(line) && validate_checksum())
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
}

Ihex_record::Ihex_record( const Ihex_record & other) :
	length(other.length),
	type(other.type),
	address(other.address),
	valid(other.valid)
{
	if (length > 0)
	{
		data = new uint8_t[length];
		for (size_t i = 0; i < length; i++)
		{
			data[i] = other.data[i];
		}
	}
}

Ihex_record::~Ihex_record()
{
	delete [] data;
	data = 0;
}
	
bool Ihex_record::is_valid()
{
	return valid;
}
bool Ihex_record::validate_checksum()
{
	uint8_t temp_checksum = (uint8_t)length;
	temp_checksum += (uint8_t)type;
	temp_checksum += (uint8_t)(address & 0x0FF);
	temp_checksum += (uint8_t)((address & 0x0FF00) >> 8);
	for (size_t i = 0; i < length; i++)
	{
		temp_checksum += data[i];
	}
	temp_checksum = -temp_checksum;
	//~ std::cerr << "Checksum Check: " << (long) temp_checksum << std::endl;
	return temp_checksum == checksum;
}

uint8_t* Ihex_record::get_data()
{
	return data;
}
size_t Ihex_record::get_length()
{
	return length;
}

uint16_t Ihex_record::get_address()
{
	return address;
}

Ihex_record::Type Ihex_record::get_type()
{
	return type;
}

void Ihex_record::describe(std::string& str)
{
	std::ostringstream out;
	out << "Length: " << length << ", ";
	out << "Address: " << address << ", ";
	out << "Type: " << type_to_string(type) << ", ";
	out << "Data: ";
	char buf[3];
	for ( size_t i = 0; i < length; i++ )
	{
		snprintf(buf, 3, "%02X", data[i]);
		buf[2] = '\0';
		out << buf << ((i < (length-1)) ? " " : "");
	}
	snprintf(buf, 3, "%02X", checksum);
	buf[2] = '\0';
	out << ", Checksum: " << buf;
	out << ", Valid: " << (is_valid() ? "Yes" : "No");
	str.append(out.str());
}

// IMPLEMENT PRIVATE FUNCTIONS.

bool Ihex_record::parse(std::string& line)
{
	int offset = 0;
	//Check the line start code;
	if (line[0] != ':' || line.length() < 11)
	{
		return false;
	}
	offset++;
	char* end;
	//Get the length of the data which is the next two chars.
	std::string temp = line.substr(offset,2);
	offset += 2;
	
	//~ std::cerr << "Length field: " << temp << std::endl;
	
	//Parse the length into an integer in base 16.
	unsigned long temp_length = strtoul(temp.c_str(), &end, 16);
	
	//~ std::cerr << "Length parsed: " << tempLength << std::endl;
	
	//Check if the whole length was not parsed.
	if (end != temp.c_str() + 2)
	{
		return false;
	}
	length = temp_length;
	//Check if the line is long enough to contain the data.
	if (line.length() < length+11)
	{
		return false;
	}
	//Get the address which is the next four chars.
	temp = line.substr(offset,4);
	offset += 4;
	
	//~ std::cerr << "Address field: " << temp << std::endl;
	
	//Parse the address into an integer in base 16.
	unsigned long temp_address = strtoul(temp.c_str(), &end, 16);
	
	//~ std::cerr << "Address parsed: " << tempAddress << std::endl;
	
	//Check if an invalid address was parsed or the whole string was not parsed.
	if (end != temp.c_str() + 4 || temp_address > 0xFFFF)
	{
		return false;
	}
	address = (uint16_t)temp_address;
	//Get the record type which is the next two chars.
	temp = line.substr(offset,2);
	offset += 2;
	
	//~ std::cerr << "Type field: " << temp << std::endl;
	
	//Parse the record type into a type enum.
	if (!parse_record_type(temp, type))
	{
		type = INVALID;
		return false;
	}
	
	//~ std::cerr << "Type parsed: " << typeToString(type) << std::endl;
	
	//Acquire the data from the record.
	if (length > 0)
	{
		data = new uint8_t[length];
	}
	for (size_t i = 0; i < length; i++)
	{
		//Get the next byte of data.
		std::string temp = line.substr(offset,2);
		offset += 2;
		//Parse the data into an integer in base 16.
		unsigned long temp_data = strtoul(temp.c_str(), &end, 16);
		//The whole length was not parsed or was an invalid byte value.
		if (end != temp.c_str() + 2 || temp_data > 0xFF)
		{
			return false;
		}
		data[i] = (uint8_t)temp_data;
	}
	//Get the checksum from the last two bytes of the string.
	temp = line.substr(offset, 2);
	offset += 2;
	
	//~ std::cerr << "Checksum field: " << temp << std::endl;
	
	//Parse the checksum into a signed integer in base 16.
	unsigned long temp_check = strtoul(temp.c_str(), &end, 16);
	
	//~ std::cerr << "Checksum parsed: " << temp_check << std::endl;
	
	//Check if the whole length was not parsed.
	if (end != temp.c_str() + 2 || temp_check > 0xFF)
	{
		return false;
	}
	
	checksum = static_cast<uint8_t>(temp_check);
	
	//~ std::cerr << "Checksum: " << (long)checksum << std::endl;
	
	if (!validate_checksum())
	{
		return false;
	}
	
	//~ std::cerr << "Checksum: " << (long)checksum << std::endl;
	
	valid = true;
	return true;
}

bool parse_record_type(std::string& temp, Ihex_record::Type& type)
{
	char* end;
	//Parse the type code into an integer in base 16.
	unsigned long temp_type = strtoul(temp.c_str(), &end, 16);
	//The whole length was not parsed or the returned value was not a byte value.
	if (end != temp.c_str() + 2 || temp_type > 0xFF)
	{
		return false;
	}
	switch (temp_type)
	{
		case 0:
			type = Ihex_record::DATA;
			break;
		case 1:
			type = Ihex_record::END_OF_FILE;
			break;
		case 2:
			type = Ihex_record::EXTENDED_SEG_ADDR;
			break;
		case 3:
			type = Ihex_record::START_SEG_ADDR;
			break;
		case 4:
			type = Ihex_record::EXTENDED_LINEAR_ADDR;
			break;
		case 5:
			type = Ihex_record::START_LINEAR_ADDR;
			break;
		default:
			type = Ihex_record::INVALID;
			break;
	}
	return true;
}

std::string type_to_string(Ihex_record::Type type)
{
	switch( type )
	{
		case Ihex_record::DATA:
			return "Data";
			break;
		case Ihex_record::END_OF_FILE:
			return "End of File";
			break;
		case Ihex_record::EXTENDED_SEG_ADDR:
			return "Extended Segment Address";
			break;
		case Ihex_record::START_SEG_ADDR:
			return "Start Segment Address";
			break;
		case Ihex_record::EXTENDED_LINEAR_ADDR:
			return "Extended Linear Address";
			break;
		case Ihex_record::START_LINEAR_ADDR:
			return "Start Linear Address";
			break;
		case Ihex_record::INVALID:
			return "Invalid";
			break;
		default:
			return "Unkown Record Type";
			break;
	}
}

//ALL DONE.
