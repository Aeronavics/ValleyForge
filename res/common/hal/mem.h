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
 *  Revised 14-12-2011 by Paul Bowler to remove options to read/write/copy to/from flash. Also removed unwarranted
 *  references to fuse-bits.
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

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

/*Enumerated list of error returns. 
* ADDRESS_OUT_OF_BOUNDS : 	the provided source or destination address is out of bounds of EEPROM
* PROCESS_ERROR :	the copy/read/write/clear process overreaches the limits of EEPROM
*/
enum mem_return {MEM_SUCCESS, ADDRESS_OUT_OF_BOUNDS = 1, PROCESS_ERROR};

/**
 * Write to an EEPROM memory address
 * 
 *
 * @param  dst		16 bit EEPROM destination address
 * @param  data		A pointer to the start of the data to be stored
 * @param  length	The number of bytes to be stored
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */
mem_return write_mem(uint16_t dst, void* data, uint16_t length);

/**
 * Read from an EEPROM memory address
 * 
 *
 * @param  src		16 bit EEPROM source address
 * @param  dst		A pointer to the start of the destination where the data will be stored
 * @param  length	The number of bytes to be read
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */
mem_return read_mem(uint16_t src, void* dst, uint16_t length);

/**
 * Copy from one EEPROM memory location to another
 * 
 *
 * @param  src		16 bit EEPROM source address
 * @param  dst		16 bit EEPROM destination address
 * @param  length	The number of bytes to be copied
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */		
mem_return cpy_mem(uint16_t src, uint16_t dst, uint16_t length);

/**
 * Clear a section of EEPROM memory
 * 
 *
 * @param  address	16 bit memory address
 * @param  length	The number of bytes to be cleared
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */		
mem_return clear_mem(uint16_t address, uint16_t length);


#endif /*__MEM_H__*/

// ALL DONE.
