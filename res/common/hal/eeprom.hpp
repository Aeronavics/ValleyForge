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

/**
 *  @addtogroup		hal
 * 
 *  @file
 *  This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.
 * 
 *  @author 		Zac Frank
 *
 *  @date		13-12-2011
 *  
 *  @brief
 *  This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.
 *
 *  @section Licence
 * 
 * Copyright (C) 2011  Unison Networks Ltd
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  @class mem
 *  This is an abstract class that provides functionality for writing to, reading from, and clearing EEPROM memory.  EEPROM memory on embedded devices is typically used for
 *  storing configuration or state data across power cycles or other reset events.
 *
 *  In this implementation, data is written in byte sized blocks.  No initialisation is required prior to performing read or write operations.  EEPROM operations are quite
 *  slow; functions are blocking whilst performing read and write operations.
 * 
 *  @section Example
 *  This code shows writing a block of eight bytes to EEPROM, then reading the same block back into a buffer.
 * 
 *  @code
 *  #include "eeprom.h"
 *
 *  int main(void)
 *  { 
 *      uint16_t my_eeprom_address = 0x0EF0;
 *      uint8_t my_first_data[8] = {1,2,3,4,5,6,7,8};
 *      uint8_t my_second_data[8];
 * 
 *      eeprom::write(my_eeprom_address, my_first_data, 8);
 * 
 *      eeprom::read(my_eeprom_address, my_second_data, 8);
 *
 *      return 0;
 *  }
 *  @endcode
 *
 */

// Only include this header file once.
#ifndef __EEPROM_H__
#define __EEPROM_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the common HAL stuff.
#include "hal/hal.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// IO operation return values. 
enum eeprom_return {EEPROM_SUCCESS, EEPROM_ERROR_OOB = 1, EEPROM_ERROR_PROCESS};

class eeprom
{

    public:
		// Methods.

		/**
		* Write data to an EEPROM address.
		*
		* NOTE - This function blocks with interrupts disabled during EEPROM IO operations, which may take multiple ms.
		*
		* @param  dst		EEPROM destination address.
		* @param  data		Buffer containing the data to be written.
		* @param  length	The number of bytes to be written.
		* @return Result status; zero for success, or non-zero indicating an error.
		*/
		static eeprom_return write(uint16_t dst, uint8_t* data, uint16_t length);

		/**
		* Read data from an EEPROM address.
		*
		* NOTE - This function blocks with interrupts disabled during EEPROM IO operations, which may take multiple ms.
		*
		* @param  src		EEPROM source address.
		* @param  data		Buffer to read the data into.
		* @param  length	The number of bytes to be read.
		* @return Result status; zero for success, or non-zero indicating an error.
		*/
		static eeprom_return read(uint16_t src, uint8_t* data, uint16_t length);

		/**
		* Copy one block of EEPROM memory to another.
		*
		* NOTE - This function blocks with interrupts disabled during EEPROM IO operations, which may take multiple ms.
		*
		* @param  src		EEPROM source address.
		* @param  dst		EEPROM destination address.
		* @param  length	The number of bytes to be copied.
		* @return Result status; zero for success, or non-zero indicating an error.
		*/		
		static eeprom_return copy(uint16_t src, uint16_t dst, uint16_t length);

		/**
		* Erase a section of EEPROM memory. This sets the specified bytes to 0xFF (since erasing an EEPROM bit generally results in a logical one).
		*
		* NOTE - This function blocks with interrupts disabled during EEPROM IO operations, which may take multiple ms.
		* 
		* @param  address	EEPROM address to erase.
		* @param  length	The number of bytes to be erased.
		* @return Result status; zero for success, or non-zero indicating an error.
		*/		
		static eeprom_return erase(uint16_t address, uint16_t length);

    private:
		// Methods.
		
		eeprom(void);	// Poisoned.

		eeprom operator =(eeprom const&);	// Poisoned.
};
#endif /*__EEPROM_H__*/

// ALL DONE.
