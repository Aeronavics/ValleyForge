/********************************************************************************************************************************
 *
 *  FILE: 			watchdog.h
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Zac Frank
 *
 *  DATE CREATED:	12-12-2011
 *
 *	This is the header file which matches watchdog.c.  Allows control over the processor watchdog timer.
 * 
 ********************************************************************************************************************************/ 

// Only include this header file once.
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal/hal.h"

// DEFINE PUBLIC MACROS.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum wdt_timeout {WDTO_15MS, WDTO_30MS, WDTO_60MS, WDTO_120MS, WDTO_250MS, WDTO_500MS, WDTO_1S, WDTO_2S, WDTO_4S, WDTO_8S};

// DECLARE PUBLIC GLOBAL VARIABLES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class watchdog
{
	public:
		// Functions.

		/**
		 * Gets run whenever the instance of class gpio_pin goes out of scope.
		 * Does nothing, since the watchdog class cannot be instantiated.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~watchdog(void);
		
		/**
		 * Resets the watchdog timer so it doesn't overflow and trigger a system reset.
		 * 
		 * @param  Nothing.
		 * @return Nothing.
		 */
		static void pat(void);
				
		/**
		 * Sets the timeout of the watchdog timer and starts the watchdog running.
		 * 
		 * @param time_out	One of 10 possible different values for the timeout value of the watchdog
		 * @return Nothing.
		 */
		static void enable(wdt_timeout time_out);
		
		/** 
		 * Disables the watchdog timer.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		static void disable(void);
		
	private:
		// Functions.
		
		watchdog(void);	// Poisoned.

		watchdog operator =(watchdog const&);	// Poisoned.
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__WATCHDOG_H__*/

// ALL DONE.
