/********************************************************************************************************************************
 *
 *  FILE: 		bootloader_module_isp.h
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	21-12-2011
 *
 *	Matching header file for bootloader_module_isp.c.  Provides a bootloader_module which only supports regular ISP
 *	programming, i.e. doesn't do anything.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __BOOTLOADER_MODULE_ISP_H__
#define __BOOTLOADER_MODULE_ISP_H__

// INCLUDE REQUIRED HEADER FILES.

#include "bootloader_module.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

class bootloader_module_isp : public bootloader_module
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
		virtual void init(void);

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
		virtual void exit();

	private:
};

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__BOOTLOADER_MODULE_ISP_H__*/

// ALL DONE.
