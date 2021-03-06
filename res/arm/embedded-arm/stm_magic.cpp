// Copyright (C) 2017  Aeronavics Ltd
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
 *  FILE: 		stm_magic.cpp
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Anton Slooten
 *
 *  DATE CREATED:	29-2-2017
 *
 *	Performs some magic
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// DEFINE CONSTANTS

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

void* operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void* ptr)
{
	free(ptr);
}

int __cxa_guard_acquire(__guard* g)
{
	return ! *(char*) (g);
}

void __cxa_guard_release(__guard* g)
{
	*(char*) g = 1;

	// All done.
	return;
}

void __cxa_guard_abort(__guard*) 
{
	// All done.
	return;
}

void __cxa_pure_virtual(void)
{
	// All done.
	return;
}
void _sbrk(void)
{
	// All done.
	return;
}
int __dso_handle(void)
{
	// All done.
	return 1;
}
int atexit(void (*callback)(void))
{
	// NOTE - This function does not actually do anything.

	// Return non-zero to indicate the function failed.
	return 1;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
