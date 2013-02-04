// Copyright (C) 2013  Unison Networks Ltd
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
 *  FILE: 		bootloader_shared.hpp
 *
 *  AUTHOR: 		George Wareing
 *
 *  DATE CREATED:	24-1-2012
 *
 *	Header file that shares functions between the application and the bootloader.
 * 	This header file must be #included by application.
 *
 ********************************************************************************************************************************/

#include "application_interface_module_constants_canspi.hpp"// TODO - import the correct file depending on the bootloader #include "<<<TC_INSERTS_H_BOOTLOADER_MODULE_FILE_NAME_HERE>>>"
#include "application_interface_constants.hpp"


#if defined (__AVR_ATmega2560__)
	// Include the dummy header file for the bootloader trampoline.
	#include "bootloader_trampoline.hs"
	
	extern "C" int _bootloader_trampoline;

	// Trampoline required for micorcontrollers with program memory > 128K bytes.
	#define BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS	<<<TC_INSERTS_BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS_HERE>>>
	#define SHARED_FUNCTION_1 ((int)(&_bootloader_trampoline))
	#define SHARED_FUNCTION_2 ((int)(&_bootloader_trampoline) + 0x4)
	#define SHARED_FUNCTION_3 ((int)(&_bootloader_trampoline) + 0x8)
	#define SHARED_FUNCTION_4 ((int)(&_bootloader_trampoline) + 0xC)
	
#else
	#define SHARED_FUNCTION_TABLE_BASE_ADDRESS 			<<<TC_INSERTS_SHARED_FUNCTION_TABLE_BASE_ADDRESS_HERE>>>
	#define SHARED_FUNCTION_1 SHARED_FUNCTION_TABLE_BASE_ADDRESS
	#define SHARED_FUNCTION_2 (SHARED_FUNCTION_TABLE_BASE_ADDRESS + 0x4)
	#define SHARED_FUNCTION_3 (SHARED_FUNCTION_TABLE_BASE_ADDRESS + 0x8)
	#define SHARED_FUNCTION_4 (SHARED_FUNCTION_TABLE_BASE_ADDRESS + 0xC)
	
#endif

	// Shared information structs
Shared_bootloader_constants BL_information_struct;
Shared_bootloader_module_constants BL_module_information_struct;

	// Functions pointers
typedef void (*function_pointer1)(void);
typedef void (*function_pointer2)(Shared_bootloader_constants*);
typedef void (*function_pointer3)(Shared_bootloader_module_constants*);

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
static __inline__ void boot_mark_clean_app(void)
{ ((function_pointer1) (SHARED_FUNCTION_1/2))(); }

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
static __inline__ void boot_mark_dirty_app(void)
{ ((function_pointer1) (SHARED_FUNCTION_2/2))(); }

/**
 *	Stores bootloader information in struct that.
 *
 *	TAKES: 		bootloader_information		struct that bootloader information is stored.
 *
 *	RETURNS: 	Nothing.
 */
static __inline__ void get_bootloader_information_app(Shared_bootloader_constants* bootloader_information)
{ ((function_pointer2) (SHARED_FUNCTION_3/2))(bootloader_information); }

/**
 *	Stores bootloader module information in struct that.
 *
 *	TAKES: 		bootloader_module_information		struct that bootloader module information is stored.
 *
 *	RETURNS: 	Nothing.
 */
static __inline__ void get_bootloader_module_information_app(Shared_bootloader_module_constants* bootloader_module_information)
{ ((function_pointer3) (SHARED_FUNCTION_4/2))(bootloader_module_information); }

