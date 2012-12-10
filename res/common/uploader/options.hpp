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
#ifndef OPTIONS_H_
#define OPTIONS_H_

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
	
	bool readFromArgs(int argc, char* argv[]);
	void printUsage();
	
	const char* getInputFile();
	CommModule* getCommsModule();
	Params getCommsParams();
	size_t getMemorySize();
	size_t getPageSize();

	
private:
	// Functions.

	
	
	//Fields.
	const char* inputFile;
	const char* commsModule;
	const char* commsParams;
	const char* memorySize;
	const char* pageSize;
};
 
// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.
 
#endif /*OPTIONS_H_*/
