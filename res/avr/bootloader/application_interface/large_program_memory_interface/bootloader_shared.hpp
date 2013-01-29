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
#include "shared_bootloader_module_constants_can.hpp" //"<<<TC_INSERTS_H_MODULE_FILE_NAME_HERE>>>"
#include "shared_bootloader_constants.hpp" 

	// Import type of bootloader

	// Adresses of function within the jumptable
#define TRAMPOLINE_TABLE_BASE_ADDRESS 0x01000//TODO - same address as where linker places it.
#define TRAMPOLINE_FUNCTION_1 TRAMPOLINE_TABLE_BASE_ADDRESS
#define TRAMPOLINE_FUNCTION_2 (TRAMPOLINE_TABLE_BASE_ADDRESS + 0x4)
#define TRAMPOLINE_FUNCTION_3 (TRAMPOLINE_TABLE_BASE_ADDRESS + 0x8)
#define TRAMPOLINE_FUNCTION_4 (TRAMPOLINE_TABLE_BASE_ADDRESS + 0xC)

	// Shared information structs
Shared_bootloader_constants BL_information_struct;
Shared_bootloader_module_constants BL_module_information_struct;

	// Functions pointers
typedef void (*function_pointer1)(void);
typedef void (*function_pointer2)(void);
typedef void (*function_pointer3)(Shared_bootloader_constants*);
typedef void (*function_pointer4)(Shared_bootloader_module_constants*);


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
static inline void boot_mark_clean_app(void)
{ ((function_pointer2) (TRAMPOLINE_FUNCTION_1/2))(); }

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
static inline void boot_mark_dirty_app(void)
{ ((function_pointer1) (TRAMPOLINE_FUNCTION_2/2))(); }

/**
 *	Stores bootloader information in struct that.
 *
 *	TAKES: 		bootloader_information		struct that bootloader information is stored.
 *
 *	RETURNS: 	Nothing.
 */
static inline void get_bootloader_information_app(Shared_bootloader_constants* bootloader_information)
{ ((function_pointer3) (TRAMPOLINE_FUNCTION_3/2))(bootloader_information); }

/**
 *	Stores bootloader module information in struct that.
 *
 *	TAKES: 		bootloader_module_information		struct that bootloader module information is stored.
 *
 *	RETURNS: 	Nothing.
 */
static inline void get_bootloader_module_information_app(Shared_bootloader_module_constants* bootloader_module_information)
{ ((function_pointer4) (TRAMPOLINE_FUNCTION_4/2))(bootloader_module_information); }
