/********************************************************************************************************************************
 *
 *  FILE: 		semaphore.c
 *
 *  LIBRARY:		hal
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	11-12-2011
 *
 *	Provides an implementation of binary semaphores, used to control access to peripherals.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

bool semaphore::procure(void)
{
	// For now, just return false.
	return false;
}

bool semaphore::procure_spin(void)
{
	// For now, just return false.
	return false;
}

void semaphore::vacate(void)
{
	// For now, just return.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
