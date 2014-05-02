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
 *  FILE: 		watchdog.c
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	14-12-2011
 *
 *	Provides functionality for controlling the watchdog timer in AVR targets.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/wdt.h>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

Watchdog::~Watchdog(void)
{
	// The Watchdog class is abstract, so there is nothing to be done.

	// All done.
	return;
}

void Watchdog::pat(void)
{
	// Reset the watchdog timer using the AVR watchdog library.
	wdt_reset();

	// All done.
	return;
}

void Watchdog::enable(Watchdog_timeout time_out)
{	
	// Initialise the watchdog timer using the AVR watchdog library.
	wdt_enable(time_out);
	
	// All done.
	return;
}

void Watchdog::disable(void)
{
	// Disable the watchdog timer using the AVR watchdog library.
	wdt_disable();

	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
