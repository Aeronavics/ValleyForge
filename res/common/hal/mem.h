/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file
 * This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.
 * 
 * @author 		Zac Frank
 *
 * @date		13-12-2011
 *  
 * @section Licence
 * 
 * LICENCE GOES HERE
 * 
 * @brief
 * This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.
 *
 * @class mem
 * This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.
 * It uses byte sized writing blocks.It does not require any set-up, just use of the static functions provided.
 * EEPROM memory is a memory block that is included in some architectures. It is useful for maintaining memory between resets that
 * can by edited during running of the micro. RAM gets cleared between resets and Flash cannot usually be written to while the program
 * is running.
 * 
 * This is the header file which matches mem.cpp. 
 * 
 * @section Example
 * 
 * @code
 * 
 * #include "mem.h"
 * init_hal();
 * 
 * uint16_t my_eeprom_address = 0x0EF0;		// The EEPROM address to write to.
 * uint8_t my_first_data[8] = {1,2,3,4,5,6,7,8};
 * uint8_t my_second_data[8];
 * 
 * mem::write_mem(my_eeprom_address, (void*) &my_first_data, 8);
 * 
 * mem::read_mem(my_eeprom_address, (void*) &my_second_data, 8);
 *  
 * 
 * @endcode
 * 
 * @section Revisions
 * Revised 14-12-2011 by Paul Bowler to remove options to read/write/copy to/from flash. Also removed unwarranted
 * references to fuse-bits.
 */

// Only include this header file once.
#ifndef __MEM_H__
#define __MEM_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the common HAL stuff.
#include "hal/hal.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

/*Enumerated list of error returns. 
* ADDRESS_OUT_OF_BOUNDS : 	the provided source or destination address is out of bounds of EEPROM
* PROCESS_ERROR :	the copy/read/write/clear process overreaches the limits of EEPROM
*/
enum mem_return {MEM_SUCCESS, ADDRESS_OUT_OF_BOUNDS = 1, PROCESS_ERROR};

/**
 * 
 * @class mem
 * This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.
 * It uses byte sized writing blocks.It does not require any set-up, just use of the static functions provided.
 * EEPROM memory is a memory block that is included in some architectures. It is useful for maintaining memory between resets that
 * can by edited during running of the micro.
 */
class mem
{

    public:
	    

	    /**
	    * This function writes to an EEPROM address. Pass a pointer that points to the data, and tell it
	    * how many bytes you want written, and at which memory location. The implementation of the function should
	    * include the necessary delays to be able to use write and read sequentially. 
	    *
	    * @param  dst	16 bit EEPROM destination address
	    * @param  data	A pointer to the start of the data to be stored
	    * @param  length	The number of bytes to be stored
	    * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
	    */
	    static mem_return write_mem(uint16_t dst, void* data, uint16_t length);

	    /**
	    * This function reads from an EEPROM address. Pass it the EEPROM source memory address, a pointer to your micro's
	    * RAM address, and the number of bytes you want copied.	   
	    *
	    * @param  src		16 bit EEPROM source address
	    * @param  dst		A pointer to the start of the destination where the data will be stored
	    * @param  length		The number of bytes to be read
	    * @return uint8_t 		Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
	    */
	    static mem_return read_mem(uint16_t src, void* dst, uint16_t length);

	    /**
	    * Copies one block of EEPROM memory to another. Specify the two addresses and the number
	    * of bytes to be copied. 
	    *
	    * @param  src	16 bit EEPROM source address. Must be within the range.
	    * @param  dst	16 bit EEPROM destination address. Must be within the range.
	    * @param  length	The number of bytes to be copied.
	    * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
	    */		
	    static mem_return cpy_mem(uint16_t src, uint16_t dst, uint16_t length);

	    /**
	    * Clear a section of EEPROM memory. This sets the specified bytes to zero.
	    * 
	    *
	    * @param  address	16 bit memory address
	    * @param  length	The number of bytes to be cleared
	    * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
	    */		
	    static mem_return clear_mem(uint16_t address, uint16_t length);

    private:
		// Functions.
		
		mem(void);	// Poisoned.

		mem operator =(mem const&);	// Poisoned.
};
#endif /*__MEM_H__*/

// ALL DONE.
