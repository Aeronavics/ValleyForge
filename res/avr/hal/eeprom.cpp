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
 *  FILE: 		eeprom.cpp
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	14-12-2011
 *
 *	Provides functionality for accessing the non-volatile EEPROM memory contained on target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/eeprom.h>

// DEFINE PRIVATE MACROS.

// Maximum size of EEPROM on this device.
#if defined(__AVR_ATmega2560__)
	#define EEPROM_END_ADDRESS	0x0FFF
#elif defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
	#define EEPROM_END_ADDRESS	0x07FF
#elif defined(__AVR_AT90CAN128__)
	#define EEPROM_END_ADDRESS	0x0FFF
#else
	#error "EEPROM address limits not configured."
#endif

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

Eeprom_command_status Eeprom::write(Eeprom_address dst, uint8_t* data, uint16_t length)
{
	// Check specified address is within range.
	if (dst > EEPROM_END_ADDRESS)
	{
		// Address is out of bounds.
		return EEPROM_ERROR_OOB;
	}
	else if ((dst + length) > EEPROM_END_ADDRESS)
	{
		// Length of data doesn't fit into EEPROM.
		return EEPROM_ERROR_OOB;
	}
	
	// Write to EEPROM with the corresponding AVR library function.
	eeprom_busy_wait();
	eeprom_write_block(data, (void*) dst, length);
	eeprom_busy_wait();
	
	// Report the operation was successful.
	return EEPROM_SUCCESS;
}

Eeprom_command_status Eeprom::read(Eeprom_address src, uint8_t* data, uint16_t length)
{
	// Check specified address is within range.
	if (src > EEPROM_END_ADDRESS)
	{
		// Address is out of bounds.
		return EEPROM_ERROR_OOB;
	}
	else if (src > (EEPROM_END_ADDRESS - length))
	{
		// Length of data doesn't fit into EEPROM.
		return EEPROM_ERROR_OOB;
	}
	
	// Read from EEPROM with the corresponding AVR library function.
	eeprom_busy_wait();
	eeprom_read_block(data, (void*) src, length);
	eeprom_busy_wait();
	
	// Report the operation was successful.
	return EEPROM_SUCCESS;
}
	
Eeprom_command_status Eeprom::copy(Eeprom_address src, Eeprom_address dst, uint16_t length)
{
	// Check specified address is within range.
	if ((dst > EEPROM_END_ADDRESS) || (src > EEPROM_END_ADDRESS))
	{
		// Address is out of bounds.
		return EEPROM_ERROR_OOB;
	}
	else if (((dst + length) > EEPROM_END_ADDRESS) || ((src + length) > EEPROM_END_ADDRESS))
	{
		// Length of data doesn't fit into EEPROM.
		return EEPROM_ERROR_OOB;
	}
	
	// Initialise a buffer store data whilst it is copied.
	uint8_t buffer[length];
		
	// Read from EEPROM into buffer.
	eeprom_busy_wait();
	eeprom_read_block(buffer, (void*) src, length);
	eeprom_busy_wait();
	
	// Write from the buffer into the EEPROM.
	eeprom_busy_wait();
	eeprom_write_block(buffer, (void*) dst, length);
	eeprom_busy_wait();

	// Report the operation was successful.
	return EEPROM_SUCCESS;
}
	
Eeprom_command_status Eeprom::erase(Eeprom_address address, uint16_t length)
{
	// Check specified address is within range.
	if (address > EEPROM_END_ADDRESS)
	{
		// Address is out of bounds.
		return EEPROM_ERROR_OOB;
	}
	else if ((address + length) > EEPROM_END_ADDRESS)
	{
		// Length of data doesn't fit into EEPROM.
		return EEPROM_ERROR_OOB;
	}
	
	// Iterate over each byte to be erased.
	for (; address <= (address + length); address++)
	{
		// Check to see if the byte need to be erased (writing is slow, so we only erase if we have to).
		eeprom_busy_wait();
		if (eeprom_read_byte((const uint8_t*) (address)) != 0xFF)
		{	
			// The byte needs to be erased.
			eeprom_busy_wait();
			eeprom_write_byte((uint8_t *)(address), 0xFF);
		}
		eeprom_busy_wait();
	}
	
	// Report the operation was successful.
	return EEPROM_SUCCESS;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
