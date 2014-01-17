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
 *  FILE: 		hal.c
 *
 *  LIBRARY:		hal
 *
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	06-01-2014
 *
 *	Provides important common functionality required to allow using the ValleyForge HAL.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include "io.h"

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

static bool int_flag;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

void int_on(void)
{
	// Turn on NVIC.
	asm volatile ("cpsie i");
}

void int_off(void)
{
	// Turn off NVIC.
	asm volatile ("cpsid i");
}

void int_restore(void)
{
	// TODO - At the moment, this just turns on interrupts.
	asm volatile ("cpsie i");
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
