/********************************************************************************************************************************
 *
 *  FILE: 		avr_magic.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	22-12-2011
 *
 *	Performs some magic, neccesary because C++ support by avr-gcc is not complete.
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

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
