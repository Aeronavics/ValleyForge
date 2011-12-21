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
 *	This header file defines the interface for plug-in modules to the AVR bootloader.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __BOOTLOADER_MODULE_H__
#define __BOOTLOADER_MODULE_H__

// INCLUDE REQUIRED HEADER FILES.

// Include boolean data types.
#include <stdbool.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

class bootloader_module
{
	public:

		// Functions.
	
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
 		 *	Indicates whether the module is ready to start the application.
		 *
		 *	TAKES:		Nothing.
		 *
		 *	RETURNS:	True if the bootloader should start the application code.
		 */
		virtual bool application_ready(void) = 0;

	private:
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__BOOTLOADER_MODULE_H__*/

// ALL DONE.
