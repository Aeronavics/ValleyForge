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

#include "bootloader_module.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

class bootloader_module_isp : public bootloader_module
{
	public:

		// Functions.
	
		/**
		 *	Destroys the module when it goes out of scope.  Not that this DOESN'T exit the module properly, so the exit function
		 *	still needs to be called.
		 *	
		 */
		virtual ~bootloader_module_isp();

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
