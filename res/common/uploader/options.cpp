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
 *  FILE: 		options.cpp
 *
 *  SUB-SYSTEM:		flashing tools
 *
 *  COMPONENT:		Memory Map
 *
 *  AUTHOR: 		Paul Davey
 *
 *  DATE CREATED:	26-11-2012
 *
 *	Implementation of the command line option parser.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "options.hpp"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <iostream>
#include <stdlib.h>
#include <stdint.h>

// DEFINE PRIVATE MACROS.

#define NUMBER_OF_LONGOPTS 6

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DECLARE PRIVATE GLOBAL VARIABLES.

static ::option longopts[NUMBER_OF_LONGOPTS + 1] =
{
	{ "input-file", 1, NULL, 'f'},
	{ "communication-module", 1, NULL, 'c'},
	{ "communication-params", 1, NULL, 'C'},
	{ "memory-size", 1, NULL, 's'},
	{ "page-size", 1, NULL, 'p'},
	{ "target-signature", 1, NULL, 'S'},
	{0, 0, 0, 0}
};

static std::string shortopts = "f:c:s:C:p:S:";

// DEFINE PRIVATE FUNCTION PROTOTYPES.

size_t parseMemorySize(const char* memorySize);
Params parseCommsParams(std::string commsParams);
bool parseKeyVal(std::string section, std::string& key, std::string& value);
std::string substringFromRange(std::string string, size_t begin, size_t end);

// IMPLEMENT PUBLIC FUNCTIONS.

Options::Options() :
	inputFile(NULL),
	commsModule(NULL),
	memorySize(NULL)
{
}

Options::~Options()
{
}

bool Options::readFromArgs(int argc, char* argv[])
{
	bool haveOpts = true;
	bool haveInFile = false;
	bool haveCommsModule = false;
	bool haveCommsParams = false;
	bool haveMemorySize = false;
	bool havePageSize = false;
	bool haveSignature = false;
	int optIndex = -1;
	while (haveOpts)
	{
		int c = getopt_long(argc, argv, shortopts.c_str(), longopts, &optIndex);
		haveOpts = c != -1;
		
		switch (c)
		{
			case 'f':
				inputFile = optarg;
				haveInFile = true;
				break;
			case 'c':
				commsModule = optarg;
				haveCommsModule = true;
				break;
			case 'C':
				commsParams = optarg;
				haveCommsParams = true;
				break;
			case 's':
				memorySize = optarg;
				haveMemorySize = true;
				break;
			case 'p':
				pageSize = optarg;
				havePageSize = true;
				break;
			case 'S':
				signature = optarg;
				haveSignature = true;
				break;
			default:
				
				break;
		}
	}
	if (!(haveInFile && haveMemorySize && havePageSize && haveCommsModule && haveSignature))
	{
		return false;
	}
	return true;
}

void Options::printUsage()
{
	std::cerr << "Usage: uploader -f file.hex -s memorySize -c commsModule -C comsparams -p pagesize -S signature" << std::endl;
	std::cerr << "       comsparams is of the form name=val:name=val... " << std::endl;
}

const char* Options::getInputFile()
{
	return inputFile;
}

CommModule* Options::getCommsModule()
{
	CommModuleRegistry& registry = CommModule::getRegistry();
	CommModuleRegistry::iterator it = registry.find(commsModule);
	if (it == registry.end())
	{
		return NULL;
	}
	return (*it).second;
}

Params Options::getCommsParams()
{
	return parseCommsParams(commsParams);
}

size_t Options::getMemorySize()
{
	return parseMemorySize(memorySize);
}

size_t Options::getPageSize()
{
	return parseMemorySize(pageSize);
}

uint32_t Options::getSignature()
{
	std::string signatureStr = signature;
	char *end;
	uint32_t signatureInt = strtoul(signatureStr.c_str(), &end, 0);
	if ((end - signatureStr.c_str()) != signatureStr.length())
	{
		std::cerr << "Signature value not recognised." << std::endl;
		return 0;
	}
	return signatureInt;
}

// IMPLEMENT PRIVATE FUNCTIONS.

size_t parseMemorySize(const char*memorySize)
{
	if (memorySize == NULL)
	{
		return 0;
	}
	std::string memorySizeString = memorySize;
	size_t length = memorySizeString.length();
	char* end = 0;
	size_t size = strtol(memorySize, &end, 10);
	if ((size_t)(end - memorySize) != length)
	{
		switch (*end)
		{
			case 'm':
			case 'M':
				size *= 1024*1024;
				break;
			case 'k':
			case 'K':
				size *= 1024;
				break;
			default:
				std::cerr << "Unrecognised size suffix: " << (*end) << std::endl;
				return 0;
				break;
		}
	}
	
	return size;
}

Params parseCommsParams(std::string commsParams)
{
	//Parse the : separated list of key=value pairs into a map containing the key=value pairs.
	std::string key;
	std::string value;
	Params params;
	size_t pos = 0;
	size_t end = 0;
	params.clear();
	do
	{
		end = commsParams.find(':', pos);
		std::string section = substringFromRange( commsParams, pos, end);
		if ( parseKeyVal(section, key, value) )
		{
			//~ std::cerr << "Key: " << key << " Value: " << value << std::endl;
			params[key] = value;
		}
		pos = (end == std::string::npos) ? std::string::npos : end+1;
	}
	while (pos != std::string::npos);
	
	return params;
}

bool parseKeyVal(std::string section, std::string& key, std::string& value)
{
	size_t pos = section.find('=');
	if ( pos != std::string::npos)
	{
		key = section.substr(0, pos);
		pos += 1;
		value = section.substr(pos);
		return true;
	}
	return false;
}

std::string substringFromRange(std::string string, size_t begin, size_t end)
{
	std::string::iterator first = string.begin() + begin;
	std::string::iterator second;
	if (end != std::string::npos)
	{
		second = string.begin() + end;
	}
	else
	{
		second = string.end();
	}
	return std::string(first, second);
}
