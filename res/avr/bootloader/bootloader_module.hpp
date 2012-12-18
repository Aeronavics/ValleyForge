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
 *  FILE: 		bootloader_module.h
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	5-12-2011
 *
 *	This header file defines the interface for plug-in modules to the Modular AVR Bootloader.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __BOOTLOADER_MODULE_H__
#define __BOOTLOADER_MODULE_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// Include boolean data types.
#include <stdbool.h>
#include <avr/io.h>

// DEFINE PREPROCESSOR MACROS.

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// Time in milliseconds between calls of event_periodic() for the bootloader module.
const uint16_t MODULE_EVENT_PERIOD = 10;

struct firmware_page
{
	bool ready_to_flash;
	bool ready_to_read_flash;
	uint32_t page;
	uint16_t current_byte;
	uint8_t data[SPM_PAGESIZE];
	uint16_t code_length;
};

class bootloader_module
{
	public:		
		// Functions.
	
		/**
		 *	Destroys the module when it goes out of scope.
		 *	
		 *	NOTE - This needs to be virtual so that the default destructor of any derived classes is always used.
		 */
		virtual ~bootloader_module() = 0;

		/**
		 *	Starts up the module; initialize whatever peripherals are required, configures interrupts, etc.
		 *
		 *	NOTE - There is no reporting of whether the initialization was successful.  Bootloader code is assumed to ALWAYS work.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void init(void) = 0;

		/**
		 *	Shuts down the module; deactivate whatever peripherals were used, etc.
		 *
		 *	NOTE - The module must deactivate EVERYTHING it uses, so that the application code starts in a predictable state.
		 *
		 *	NOTE - There is no reporting of whether the shutdown was successful.  Bootloader code is assumed to ALWAYS work.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void exit() = 0;

		/**
		 *	Performs functionality which must be executed every cycle of the bootloader mainloop.
		 *
		 *	NOTE - Flash pages received asynchronously will not be written to flash if this blocks continuously.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void event_idle() = 0;

		/**
		 *	Performs functionality which must be executed on a periodic basis.  The function will be called with a period defined by the const
		 *	value MODULE_EVENT_PERIOD.
		 *
		 *	NOTE - This function is called from an ISR.  It must not block for extended periods.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	Nothing.
		 */
		virtual void event_periodic() = 0;

	private:
};

// DECLARE PUBLIC GLOBAL VARIABLES.

extern firmware_page buffer;
extern firmware_page read_buffer;

// DEFINE PUBLIC FUNCTION PROTOTYPES.

// NOTE - These functions are implemented in bootloader.cpp, but do not have definitions in bootloader.hpp, since they should only be used by bootloader modules.

/**
 *	Commands the bootloader shell to reboot the microcontroller.  The bootloader will remain resident after the restart.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	This function will NEVER return.
 */
void reboot_to_bootloader(void);

/**
 *	Commands the bootloader shell to reboot the microcontroller.  The bootloader will NOT remain resident after the restart.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	This function will NEVER return.
 */
void reboot_to_application(void);

/**
 *	Commands the bootloader shell to start the application code as normal (without a CPU reset first).
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	This function will NEVER return.
 */
void start_application(void);

/**
 *	Enables or disables the timeout period after which the bootloader will start the application code.  This should be used when the module first
 *	receives some communication from a host trying to upload firmware, so that the upload operation can be completed without the bootloader shell timing out.
 *	The module might still want to keep some kind of internal timeout though, in the event that communications with the host drops out?
 *
 *	TAKES:		A flag indicating if the bootloader timeout should be enabled or disabled.
 *
 *	RETURNS:	Nothing.
 */
void set_bootloader_timeout(bool enable);

#endif /*__BOOTLOADER_MODULE_H__*/

// ALL DONE.
