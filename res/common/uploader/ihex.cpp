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


#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstdio>
#include <iostream>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

bool parseRecordType(std::string& temp, IHexRecord::e_type& type);
std::string typeToString(IHexRecord::e_type type);

// IMPLEMENT PUBLIC FUNCTIONS.

IHexRecord::IHexRecord() :
	data(0),
	length(0),
	type(INVALID),
	address(0),
	valid(false)
{
	
}

IHexRecord::IHexRecord( std::string& line) :
	data(0),
	length(0),
	type(INVALID),
	address(0),
	valid(false)
{
	if (parse(line) && validateChecksum())
	{
		valid = true;
	}
	else
	{
		valid = false;
	}
}

IHexRecord::IHexRecord( const IHexRecord & other) :
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

IHexRecord::~IHexRecord()
{
	delete [] data;
	data = 0;
}
	
bool IHexRecord::isValid()
{
	return valid;
}
bool IHexRecord::validateChecksum()
{
	uint8_t tempChecksum = (uint8_t)length;
	tempChecksum += (uint8_t)type;
	tempChecksum += (uint8_t)(address & 0x0FF);
	tempChecksum += (uint8_t)((address & 0x0FF00) >> 8);
	for (size_t i = 0; i < length; i++)
	{
		tempChecksum += data[i];
	}
	tempChecksum = -tempChecksum;
	//~ std::cerr << "Checksum Check: " << (long) tempChecksum << std::endl;
	return tempChecksum == checksum;
}

uint8_t* IHexRecord::getData()
{
	return data;
}
size_t IHexRecord::getLength()
{
	return length;
}

uint16_t IHexRecord::getAddress()
{
	return address;
}

IHexRecord::e_type IHexRecord::getType()
{
	return type;
}

void IHexRecord::describe(std::string& str)
{
	std::ostringstream out;
	out << "Length: " << length << ", ";
	out << "Address: " << address << ", ";
	out << "Type: " << typeToString(type) << ", ";
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
	out << ", Valid: " << (isValid() ? "Yes" : "No");
	str.append(out.str());
}

// IMPLEMENT PRIVATE FUNCTIONS.

bool IHexRecord::parse(std::string& line)
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
	unsigned long tempLength = strtoul(temp.c_str(), &end, 16);
	
	//~ std::cerr << "Length parsed: " << tempLength << std::endl;
	
	//The whole length was not parsed.
	if (end != temp.c_str() + 2)
	{
		return false;
	}
	length = tempLength;
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
	unsigned long tempAddress = strtoul(temp.c_str(), &end, 16);
	
	//~ std::cerr << "Address parsed: " << tempAddress << std::endl;
	
	//Invalid address was parsed or the whole string was not parsed.
	if (end != temp.c_str() + 4 || tempAddress > 0xFFFF)
	{
		return false;
	}
	address = (uint16_t)tempAddress;
	//Get the record type which is the next two chars.
	temp = line.substr(offset,2);
	offset += 2;
	
	//~ std::cerr << "Type field: " << temp << std::endl;
	
	//Parse the record type into a type enum.
	if (!parseRecordType(temp, type))
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
		unsigned long tempData = strtoul(temp.c_str(), &end, 16);
		//The whole length was not parsed or was an invalid byte value.
		if (end != temp.c_str() + 2 || tempData > 0xFF)
		{
			return false;
		}
		data[i] = (uint8_t)tempData;
	}
	//Get the checksum from the last two bytes of the string.
	temp = line.substr(offset, 2);
	offset += 2;
	
	//~ std::cerr << "Checksum field: " << temp << std::endl;
	
	//Parse the checksum into a signed integer in base 16.
	unsigned long tempCheck = strtoul(temp.c_str(), &end, 16);
	
	//~ std::cerr << "Checksum parsed: " << tempCheck << std::endl;
	
	//The whole length was not parsed.
	if (end != temp.c_str() + 2 || tempCheck > 0xFF)
	{
		return false;
	}
	//long tempChecksum = 0x80 - (long)tempCheck;
	checksum = static_cast<uint8_t>(tempCheck);
	
	//~ std::cerr << "Checksum: " << (long)checksum << std::endl;
	
	if (!validateChecksum())
	{
		return false;
	}
	
	//~ std::cerr << "Checksum: " << (long)checksum << std::endl;
	
	valid = true;
	return true;
}

bool parseRecordType(std::string& temp, IHexRecord::e_type& type)
{
	char* end;
	//Parse the type code into an integer in base 16.
	unsigned long tempType = strtoul(temp.c_str(), &end, 16);
	//The whole length was not parsed or the returned value was not a byte value.
	if (end != temp.c_str() + 2 || tempType > 0xFF)
	{
		return false;
	}
	switch (tempType)
	{
		case 0:
			type = IHexRecord::DATA;
			break;
		case 1:
			type = IHexRecord::END_OF_FILE;
			break;
		case 2:
			type = IHexRecord::EXTENDED_SEG_ADDR;
			break;
		case 3:
			type = IHexRecord::START_SEG_ADDR;
			break;
		case 4:
			type = IHexRecord::EXTENDED_LINEAR_ADDR;
			break;
		case 5:
			type = IHexRecord::START_LINEAR_ADDR;
			break;
		default:
			type = IHexRecord::INVALID;
			break;
	}
	return true;
}

std::string typeToString(IHexRecord::e_type type)
{
	switch( type )
	{
		case IHexRecord::DATA:
			return "Data";
			break;
		case IHexRecord::END_OF_FILE:
			return "End of File";
			break;
		case IHexRecord::EXTENDED_SEG_ADDR:
			return "Extended Segment Address";
			break;
		case IHexRecord::START_SEG_ADDR:
			return "Start Segment Address";
			break;
		case IHexRecord::EXTENDED_LINEAR_ADDR:
			return "Extended Linear Address";
			break;
		case IHexRecord::START_LINEAR_ADDR:
			return "Start Linear Address";
			break;
		case IHexRecord::INVALID:
			return "Invalid";
			break;
		default:
			return "Unkown Record Type";
			break;
	}
}
