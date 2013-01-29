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
 *  FILE: 		bootloader.h
 *
 *  TARGET:		All AVR Targets.
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	5-12-2011
 *
 *	This is the header file which matches bootloader.c. This is the generic modular bootloader used for AVR targets.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the general bootloader module header file.
#include "bootloader_module.hpp"

// Include the bootloader information sharing struct type.
#include "application_interface/application_interface_constants.hpp"

// Include the specific bootloader module we want to use.
#include "<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>.hpp"

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// Include the AVR Boot Library.
#include <avr/boot.h>

// Include boolean data types.
#include <stdbool.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

int main(void);

/**
 *	Marks the 'application run' indicator in EEPROM to signal that the bootloader should start the application on the next CPU reset.
 *
 *	This should usually be called only when the application code is shut down cleanly.
 *
 *	Blocks until EEPROM IO operations are completed.
 * 
 *  NOTE - This function can be accessed by the application.
 *
 *	TAKES: 		Nothing.
 *
 *	RETURNS: 	Nothing.
 */
void boot_mark_clean(void);

	// NOTE - Avoids using name mangled function name for the shared jumptable
extern "C" void boot_mark_clean_BL(void){
	boot_mark_clean();
}

/**
 *	Marks the 'application run' indicator in EEPROM to signal that the bootloader should NOT start the application on the next CPU reset.
 *	
 *	This is the default state, so usually indicates to the boot loader that the application code crashed without shutting down cleanly.
 *	Alternatively, this function may be called deliberately to force the bootloader to check for new application firmware to download.
 *
 *	Blocks until EEPROM IO operations are completed.
 * 
 *  NOTE - This function can be accessed by the application.
 *
 *	TAKES: 		Nothing.
 *
 *	RETURNS: 	Nothing.
 */
void boot_mark_dirty(void);

	// NOTE - Avoids using name mangled function name for the shared jumptable
extern "C" void boot_mark_dirty_BL(void){
	boot_mark_dirty();
}

/**
 *	Stores bootloader information in struct.
 *
 *	TAKES: 		bootloader_information		struct that bootloader information is stored.
 * 
 *  NOTE - This function can be accessed by the application.
 *
 *	RETURNS: 	Nothing.
 */
void get_bootloader_information(Shared_bootloader_constants* bootloader_information);

	// NOTE - Avoids name mangling for the shared jumptable
extern "C" void get_bootloader_information_BL(Shared_bootloader_constants* arg){
	get_bootloader_information(arg);
}

#endif /*__BOOTLOADER_H__*/

// ALL DONE.
