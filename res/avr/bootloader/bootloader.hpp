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

// Include the specific bootloader module we want to use.
#include "<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>.hpp"

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// Include the AVR Boot Library.
#include <avr/boot.h>

// Include boolean data types.
#include <stdbool.h>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// Struct type to hold all of the variables that can be shared
typedef struct{
	void* shut_down_state_mem;
	uint16_t clean_flag;
	uint16_t bootloader_version;
}shared_bootloader_variables;

// Functions pointers
typedef void (*function_pointer1)(void*);
typedef void (*function_pointer2)(void*,uint16_t);
typedef shared_bootloader_variables* (*function_pointer3)(void);
typedef bool (*function_pointer4)(void*,uint16_t);


// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.

int main(void);

// TODO - Some crazy magic with the toolchain is required here, so that these functions are visible from userland.

/**
 *	Marks the 'application run' indicator in EEPROM to signal that the bootloader should start the application on the next CPU reset.
 *
 *	This should usually be called only when the application code is shut down cleanly.
 *
 *	Blocks until EEPROM IO operations are completed.
 *
 *	TAKES: 		Nothing.
 *
 *	RETURNS: 	Nothing.
 */
void boot_mark_clean(void* mem_address, uint16_t flag);

/**
 *	Marks the 'application run' indicator in EEPROM to signal that the bootloader should NOT start the application on the next CPU reset.
 *	
 *	This is the default state, so usually indicates to the boot loader that the application code crashed without shutting down cleanly.
 *	Alternatively, this function may be called deliberately to force the bootloader to check for new application firmware to download.
 *
 *	Blocks until EEPROM IO operations are completed.
 *
 *	TAKES: 		Nothing.
 *
 *	RETURNS: 	Nothing.
 */
void boot_mark_dirty(void* mem_address);


shared_bootloader_variables* get_bootloader_information(void);


// Avoid name mangling
extern "C" void boot_mark_clean_BL(void* arg1, uint16_t arg2){
	boot_mark_clean(arg1,arg2);
}
 
extern "C" void boot_mark_dirty_BL(void* arg1){
	boot_mark_dirty(arg1);
}

extern "C" shared_bootloader_variables* get_bootloader_information_BL(void){
	return get_bootloader_information();
}

#endif /*__BOOTLOADER_H__*/

// ALL DONE.
