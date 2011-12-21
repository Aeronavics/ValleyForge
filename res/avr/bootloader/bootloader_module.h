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

// DEFINE PREPROCESSOR MACROS.

#define PAGE_SIZE		256

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

struct firmware_page
{
	bool ready_to_flash;
	uint32_t page;
	uint8_t current_byte;
	uint8_t data[PAGE_SIZE];
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
		virtual ~bootloader_module(void) = 0;

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

	private:
};

// DECLARE PUBLIC GLOBAL VARIABLES.

volatile firmware_page buffer;

volatile uint32_t current_page = 0;

volatile bool firmware_finished = false;
volatile bool firmware_available = false;

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__BOOTLOADER_MODULE_H__*/

// ALL DONE.
