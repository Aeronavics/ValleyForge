/********************************************************************************************************************************
 *
 *  FILE: 		semaphore.h
 *
 *  LIBRARY:		hal
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	11-12-2011
 *
 *	This is the header file which matches semaphore.c.  It provides an implementation of binary semaphores, used to control
 *	access to peripherals.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// DEFINE PUBLIC MACROS.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

class semaphore
{
	public:
		
		// Functions.

		bool procure(void);

		bool procure_spin(void);

		void vacate(void);
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__SEMAPHORE_H__*/

// ALL DONE.
