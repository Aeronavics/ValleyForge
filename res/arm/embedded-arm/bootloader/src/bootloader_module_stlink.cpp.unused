// Copyright (C) 2013  Unison Networks Ltd
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
 *  FILE: 		bootloader_module_stlink.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	21-12-2011
 *
 *	Provides a bootloader module which only supports regular stlink programming, i.e. doesn't do anything.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "bootloader_module_stlink.hpp"

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

bootloader_module_stlink::~bootloader_module_stlink()
{
	// All done.
	return;
}

void bootloader_module_stlink::init(void)
{
	// There is nothing to set up, since this module doesn't do anything.

	// All done.
	return;
}

void bootloader_module_stlink::exit(void)
{
	// There is nothing to undo, since this module doesn't do anything.

	// All done.
	return;
}

void bootloader_module_stlink::event_idle(void)
{
	// Start the application code immediately.
	#warning This function is defined in bootloader.cpp, but there's no reference to it here.
	// start_application();

	// We will never reach here.
	return;
}

void bootloader_module_stlink::event_periodic(void)
{
	// All done.
	return;
}

void get_bootloader_module_information(Shared_bootloader_module_constants* bootloader_module_information)
{
	bootloader_module_information->nothing = 0x00;
	
	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
