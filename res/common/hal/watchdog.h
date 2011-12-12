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
 *	This is the header file which matches watchdog.c...
 * 
 ********************************************************************************************************************************/ 
 
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal.h"



class watchdog
{
	public:
		// Functions.
		/**
		 * watchdog destructor
		 *
		 * Gets run whenever the instance of class gpio_pin goes out of scope.
		 * Does nothing
		 *
		 * @param  none
		 * @return no return
		 */
		 ~watchdog(void);
		
		/**
		 * Pat the Dog
		 *
		 * Resets the watchdog timer so it doesn't overflow and
		 * trigger a system reset
		 * 
		 * @param  none
		 * @return void
		 */
		static void pat(void);
				
		/**
		 * Enable the Watchdog
		 *
		 * Sets the timeout of the watchdog timer
		 * and enables it
		 * 
		 * @param time_out	One of 10 possible different values for the timeout value of the watchdog
		 * (WDTO_15MS  	WDTO_30MS  WDTO_60MS  WDTO_120MS  WDTO_250MS WDTO_500MS	WDTO_1S  WDTO_2S  WDTO_4S  WDTO_8S)
		 * @return void
		 */
		static void enable(uint8_t time);
		
		/**
		 * Disable the Watchdog
		 *
		 * 
		 * Disables the watchdog timer
		 *
		 * @param  none
		 * @return void
		 */
		static void disable(void);
		
	private:
		// Functions.
		
		watchdog(void);	// Poisoned.

		watchdog operator =(watchdog const&);	// Poisoned.

};