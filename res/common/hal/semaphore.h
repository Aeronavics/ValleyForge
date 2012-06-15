/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file		semaphore.h
 * Provides an implementation of binary semaphores, used to control access to peripherals
 * 
 * @author 		Edwin Hayes
 *
 * @date		13-12-2011
 *  
 * @section Licence
 * 
 * LICENCE GOES HERE
 * 
 * @brief
 * Provides an implementation of binary semaphores, used to control access to peripherals.  NOTE - These semaphores are
 * TOTALLY NOT THREADSAFE at the moment.  This is a totally simplistic implementation, for starters, anyone can vacate a
 * semaphore, even if they aren't the one holding it!
 */

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
		/**
		 * Creates a new semaphore and sets it as being free.
		 * @param Nothing
		 * @return Nothing
		 */
		semaphore()
		{
			// Initially the semaphore is free.
			is_free = true;
		}

		/** 
		 * Checks to see if the semaphore's "is_free" state is true. If so, it returns true, then sets
		 * the semaphore to false so that no-one else can use it.
		 * 
		 * @param Nothing
		 * @return a boolean to show whether the procure was successful.
		 */
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

		/**
		 * Waits till the semaphore is free, then procures it
		 * Warning: Uses up clock cycles doing nothing.
		 * 
		 * @param Nothing
		 * @return Once the semaphore becomes free, this will always return true.
		 */
		bool procure_spin(void)
		{
			// Wait until the semaphore becomes free.
			while (!is_free);

			// Claim the semaphore and return true.
			is_free = false;
			return true;
		}

		/** 
		 * Sets the semaphore to be free, meaning another process or peripheral
		 * can procure it
		 * @param Nothing
		 * @return Nothing
		 */
		void vacate(void)
		{
			// The semaphore is now free.
			is_free = true;
			
			// All done.
			return;
		}

	private:

		// Fields.
		// Boolean state variable as to whether the semaphore is free or not.
		volatile bool is_free;
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__SEMAPHORE_H__*/

// ALL DONE.
