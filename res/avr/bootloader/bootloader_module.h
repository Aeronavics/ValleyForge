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

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

/**
 *	Starts up the module; initialize whatever peripherals are required, configures interrupts, etc.
 *
 *	NOTE - There is no reporting of whether the initialization was successful.  Bootloader code is assumed to ALWAYS work.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	Nothing.
 */
void mod_init(void);

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
void mod_exit(void);

/**
 *	Indicates whether the module is ready to start the application.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	True if the bootloader should start the application code.
 */
bool mod_run_application(void);

#endif /*__BOOTLOADER_MODULE_H__*/

// ALL DONE.
