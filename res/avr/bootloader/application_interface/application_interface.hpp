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

#include "application_interface_module_constants_can.hpp" // TODO -"<<<TC_INSERTS_H_MODULE_FILE_NAME_HERE>>>"
#include "application_interface_constants.hpp" 

// Include the dummy header file for the bootloader trampoline.
#include "bootloader_trampoline.hs"

#if defined (__AVR_ATmega2560__)
	#define BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS 0x01000// TODO - <<<TC_INSERTS_BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS_HERE>>>
	#define SHARED_FUNCTION_1 BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS
	#define SHARED_FUNCTION_2 (BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS + 0x4)
	#define SHARED_FUNCTION_3 (BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS + 0x8)
	#define SHARED_FUNCTION_4 (BOOTLOADER_TRAMPOLINE_TABLE_BASE_ADDRESS + 0xC)
	
#else
	#define SHARED_FUNCTION_TABLE_BASE_ADDRESS 0x1FFDE// TODO - <<<TC_INSERTS_SHARED_FUNCTION_TABLE_BASE_ADDRESS_HERE>>>
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
static __inline__ void boot_mark_clean_app(void)
{ ((function_pointer2) (SHARED_FUNCTION_1/2))(); }

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
{ ((function_pointer3) (SHARED_FUNCTION_3/2))(bootloader_information); }

/**
 *	Stores bootloader module information in struct that.
 *
 *	TAKES: 		bootloader_module_information		struct that bootloader module information is stored.
 *
 *	RETURNS: 	Nothing.
 */
static __inline__ void get_bootloader_module_information_app(Shared_bootloader_module_constants* bootloader_module_information)
{ ((function_pointer4) (SHARED_FUNCTION_4/2))(bootloader_module_information); }

