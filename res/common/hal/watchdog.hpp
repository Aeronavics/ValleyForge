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

/**
 *  @addtogroup		hal
 *
 *  @file 		watchdog.h
 *  Allows control over the processor watchdog timer.
 * 
 *  @author		Zac Frank
 *
 *  @date		12-12-2011
 * 
 *  @brief
 *  This is the header file which matches watchdog.c.  Allows control over the processor watchdog timer.
 * 
 *  @section Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  @class Watchdog
 *  The watchdog timer is a hardware timer which automatically triggers a CPU reset if it overflows.  When active, the watchdog must be periodically 'pat' (resetting the timer) by
 *  application code, to avoid a CPU reset.  Use of the watchdog allows an embedded system to reset automatically if it becomes trapped in an endless loop, or suffers some other
 *  error which prevents it from reaching the part of the code which would normally pat the watchdog.
 *
 *  This is an abstract class which provides functionality for controlling the watchdog timer.  Since devices usually only have a single watchdog timer, operations on the timer are
 *  accessed via static methods.
 *
 *  @section Example
 *  The following example shows enabling the watchdog timer, the patting it to avoid a watchdog strike.
 *
 *  @code
 *  #include "hal/watchdog.hpp"
 *
 *  int main(void)
 *  {
 *      Watchdog::enable(WDTO_1S);
 *
 *      while (1)
 *      {
 *          Watchdog::pat();
 *      }
 *
 *      return 0;
 *  }
 *  @endcode
 * 
 */ 

// Only include this header file once.
#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal/hal.hpp"

// DEFINE PUBLIC MACROS.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// Available watchdog timeout periods are hardware specific.
#if defined (__AVR_ATmega2560___)
	enum Watchdog_timeout
	{
		WDTO_15MS,
		WDTO_30MS,
		WDTO_60MS,
		WDTO_120MS,
		WDTO_250MS,
		WDTO_500MS,
		WDTO_1S,
		WDTO_2S,
		WDTO_4S,
		WDTO_8S
	};
#elif defined (__AVR__)
	enum Watchdog_timeout
	{
		WDTO_15MS,
		WDTO_30MS,
		WDTO_60MS,
		WDTO_120MS,
		WDTO_250MS,
		WDTO_500MS,
		WDTO_1S,
		WDTO_2S
	};
#else
	#error "No watchdog timeout definitions for this configuration."
#endif

// DECLARE PUBLIC GLOBAL VARIABLES.

// FORWARD DEFINE PRIVATE PROTOTYPES.

// DEFINE PUBLIC CLASSES.

class Watchdog
{
	public:
		// Functions.

		/**
		 * Gets run whenever the instance of class Watchdog goes out of scope.  This is never called, since the Watchdog class cannot be instantiated.
		 *
		 * @param Nothing.
		 * @return Nothing.
		 */
		 ~Watchdog(void);
		
		/**
		 * Reset the watchdog timer, preventing a watchdog strike.
		 *
		 * @param Nothing.
		 * @return Nothing.
		 */
		static void pat(void);
				
		/**
		 * Set the timeout of the watchdog timer and start the watchdog running.
		 * 
		 * @param timeout	The timeout period the watchdog timer should select.
		 * @return Nothing.
		 */
		static void enable(Watchdog_timeout timeout);
		
		/** 
		 * Disable the watchdog timer.
		 *
		 * @param Nothing.
		 * @return Nothing.
		 */
		static void disable(void);
		
	private:
		// Functions.
		
		Watchdog(void);	// Poisoned.

		Watchdog operator =(Watchdog const&);	// Poisoned.
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__WATCHDOG_H__*/

// ALL DONE.
