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
 *  @file		options.hpp
 *  A header file for the command line option parser.
 * 
 * 
 *  @author 		Paul Davey
 *
 *  @date		26-11-2012
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
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

// INCLUDE REQUIRED HEADER FILES.

#include <getopt.h>
#include <string>

#include "comm.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class Options
{
public:

	
	// Functions.
	Options();
	~Options();
	
	bool read_from_args(int argc, char* argv[]);
	void print_usage();
	
	const char* get_input_file();
	Comm_module* get_comms_module();
	Params get_comms_params();
	size_t get_memory_size();
	size_t get_page_size();
	uint32_t get_signature();

	
private:
	// Functions.

	
	
	//Fields.
	const char* input_file;
	const char* comms_module;
	const char* comms_params;
	const char* memory_size;
	const char* page_size;
	const char* signature;
};
 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*__OPTIONS_H__*/

//ALL DONE.

