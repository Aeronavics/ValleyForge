// Only include this header file once.
#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the general bootloader module header file.
#include "bootloader_module.hpp"

// Include the bootloader information sharing struct type.
#include "application_interface_module_constants_can.hpp"

// Include the specific bootloader module header file.
#include "bootloader_module_can.hpp"

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


#endif /*__BOOTLOADER_H__*/

// ALL DONE.