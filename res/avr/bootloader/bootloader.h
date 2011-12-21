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
#include "bootloader_module.h"

// Include the specific bootloader module we want to use.
#include "<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>.h"

// Include the AVR Boot Library.
#include <avr/boot.h>

// Include boolean data types.
#include <stdbool.h>

// Include the HAL libraries we use.
#include "hal/hal.h"
#include "hal/gpio.h"
#include "hal/mem.h"
#include "hal/watchdog.h"
#include "hal/tc.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

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
void boot_mark_clean(void);

/**
 *	Marks the 'application run' indicatro in EEPROM to signal that the bootloader should NOT start the application on the next CPU reset.
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
void boot_mark_dirty(void);

#endif /*__BOOTLOADER_H__*/

// ALL DONE.
