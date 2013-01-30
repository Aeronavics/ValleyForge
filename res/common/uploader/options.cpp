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

#include <stdint.h>
#include <stdlib.h>


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

size_t parse_memory_size(const char* memory_size);
Params parse_comms_params(std::string comms_params);
bool parse_key_val(std::string section, std::string& key, std::string& value);
std::string substring_from_range(std::string string, size_t begin, size_t end);

// IMPLEMENT PUBLIC FUNCTIONS.

Options::Options() :
	input_file(NULL),
	comms_module(NULL),
	memory_size(NULL)
{
	//Nothing to do here.
}

Options::~Options()
{
	//Nothing to do here.
}

bool Options::read_from_args(int argc, char* argv[])
{
	bool have_opts = true;
	bool have_in_file = false;
	bool have_comms_module = false;
	bool have_comms_params = false;
	bool have_memory_size = false;
	bool have_page_size = false;
	bool have_signature = false;
	int optIndex = -1;
	while (have_opts)
	{
		int c = getopt_long(argc, argv, shortopts.c_str(), longopts, &optIndex);
		have_opts = c != -1;
		
		switch (c)
		{
			case 'f':
				input_file = optarg;
				have_in_file = true;
				break;
			case 'c':
				comms_module = optarg;
				have_comms_module = true;
				break;
			case 'C':
				comms_params = optarg;
				have_comms_params = true;
				break;
			case 's':
				memory_size = optarg;
				have_memory_size = true;
				break;
			case 'p':
				page_size = optarg;
				have_page_size = true;
				break;
			case 'S':
				signature = optarg;
				have_signature = true;
				break;
			default:
				
				break;
		}
	}
	if (!(have_in_file && have_memory_size && have_page_size && have_comms_module && have_signature))
	{
		return false;
	}
	return true;
}

void Options::print_usage()
{
	std::cerr << "Usage: uploader -f file.hex -s memorySize -c commsModule -C comsparams -p pagesize -S signature" << std::endl;
	std::cerr << "       comsparams is of the form name=val:name=val... " << std::endl;
}

const char* Options::get_input_file()
{
	return input_file;
}

Comm_module* Options::get_comms_module()
{
	Comm_module_registry& registry = Comm_module::get_registry();
	Comm_module_registry::iterator it = registry.find(comms_module);
	if (it == registry.end())
	{
		return NULL;
	}
	return (*it).second;
}

Params Options::get_comms_params()
{
	return parse_comms_params(comms_params);
}

size_t Options::get_memory_size()
{
	return parse_memory_size(memory_size);
}

size_t Options::get_page_size()
{
	return parse_memory_size(page_size);
}

uint32_t Options::get_signature()
{
	std::string signature_str = signature;
	char *end;
	uint32_t signature_int = strtoul(signature_str.c_str(), &end, 0);
	if ((end - signature_str.c_str()) != signature_str.length())
	{
		std::cerr << "Signature value not recognised." << std::endl;
		return 0;
	}
	return signature_int;
}

// IMPLEMENT PRIVATE FUNCTIONS.

size_t parse_memory_size(const char*memory_size)
{
	if (memory_size == NULL)
	{
		return 0;
	}
	std::string memory_size_string = memory_size;
	size_t length = memory_size_string.length();
	char* end = 0;
	size_t size = strtol(memory_size, &end, 10);
	if ((size_t)(end - memory_size) != length)
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

Params parse_comms_params(std::string comms_params)
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
		end = comms_params.find(':', pos);
		std::string section = substring_from_range( comms_params, pos, end);
		if ( parse_key_val(section, key, value) )
		{
			//~ std::cerr << "Key: " << key << " Value: " << value << std::endl;
			params[key] = value;
		}
		pos = (end == std::string::npos) ? std::string::npos : end+1;
	}
	while (pos != std::string::npos);
	
	return params;
}

bool parse_key_val(std::string section, std::string& key, std::string& value)
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

std::string substring_from_range(std::string string, size_t begin, size_t end)
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

//ALL DONE.

