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
 *	Provides an implementation of binary semaphores, used to control access to peripherals.  NOTE - These semaphores are
 *	TOTALLY NOT THREADSAFE at the moment.  This is a totally simplistic implementation, for starters, anyone can vacate a
 *	semaphore, even if they aren't the one holding it!
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

		semaphore()
		{
			// Initially the semaphore is free.
			is_free = true;
		}

		bool procure(void)
		{
			// Check if the semaphore is free.
			if (is_free)
			{
				// Claim the semaphore and return true.
				is_free = false;
				return true;
			}
			else return false;
		}

		bool procure_spin(void)
		{
			// Wait until the semaphore becomes free.
			while (!is_free);

			// Claim the semaphore and return true.
			is_free = false;
			return true;
		}

		void vacate(void)
		{
			// The semaphore is now free.
			is_free = true;
			
			// All done.
			return;
		}

	private:

		// Fields.

		volatile bool is_free;
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__SEMAPHORE_H__*/

// ALL DONE.
