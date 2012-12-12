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
 *  FILE: 		bootloader_module_isp.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	21-12-2011
 *
 *	Provides a bootloader module which only supports regular ISP programming, i.e. doesn't do anything.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_isp::~bootloader_module_isp()
{
	// All done.
	return;
}

void bootloader_module_isp::init(void)
{
	// TODO - This.

	// For the moment, we just tell the bootloader to run the application right away.
	firmware_finished = true;

	// All done.
	return;
}

void bootloader_module_isp::exit(void)
{
	// TODO - This.

	// All done.
	return;
}


// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
