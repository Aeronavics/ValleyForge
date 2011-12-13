/********************************************************************************************************************************
 *
 *  FILE: 			mem.h
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Zac Frank
 *
 *  DATE CREATED:	13-12-2011
 *
 *	This is the header file which matches mem.c. Provides functionality for writing and reading to EEPROM memory.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __MEM_H__
#define __MEM_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the common HAL stuff.
#include "hal.h"

/**
		 * Write to a memory address
		 * 
		 *
		 * @param  dst		32 bit destination address
		 * @param  dst_type enumeration showing type of memory written to (EEPROM, FLASH, FUSE_BITS)
		 * @param  data		A pointer to the start of the data to be stored
		 * @param  length	The number of bytes to be stored
		 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
		 */
uint8_t writeMem(uint32_t dst, uint8_t dst_type, void* data, uint16_t length);

/**
		 * Read from memory address
		 * 
		 *
		 * @param  src		32 bit memory source address
		 * @param  src_type enumeration showing type of memory read from (EEPROM, FLASH, FUSE_BITS)
		 * @param  dst		A pointer to the start of the destination where the data will be stored
		 * @param  length	The number of bytes to be read
		 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
		 */
uint8_t readMem(uint32_t src, uint8_t src_type, void* dst, uint16_t length);

/**
		 *Copy from one memory address to another
		 * 
		 *
		 * @param  src		32 bit memory source address
		 * @param  src_type enumeration showing type of memory read from (EEPROM, FLASH, FUSE_BITS)
		 * @param  dst		32 bit destination address
		 * @param  dst_type enumeration showing type of memory written to (EEPROM, FLASH, FUSE_BITS)
		 * @param  length	The number of bytes to be copied
		 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
		 */		
uint8_t cpyMem(uint32_t src,uint8_t src_type, uint32_t dst, uint32_t dst_type, uint16_t length);

/**
		 * Clear a section of memory (set bits to one)
		 * 
		 *
		 * @param  address	32 bit memory address
		 * @param  add_type enumeration showing type of memory to be cleared (EEPROM, FLASH, FUSE_BITS)
		 * @param  length	The number of bytes to be cleared
		 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
		 */		
uint8_t clearMem(uint32_t address,uint8_t add_type, uint16_t length);


#endif /*__MEM_H__*/

// ALL DONE.
