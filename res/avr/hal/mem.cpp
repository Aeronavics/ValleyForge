/********************************************************************************************************************************
 *
 *  FILE: 		mem.cpp
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	14-12-2011
 *
 *	Description Provides functionality for accessing the non-volatile EEPROM memory contained on target microcontrollers.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "mem.h"

// INCLUDE REQUIRED HEADER FILES.
#include <avr/eeprom.h>

// DEFINE PRIVATE MACROS.

#if defined (__AVR_ATmega2560__)
#	define EEPROM_END_ADDRESS	0x0FFF
#elif defined (__AVR_ATmega64M1__)
#	define EEPROM_END_ADDRESS	0x07FF
#elif defined (__AVR_AT90CAN128__)
#	define EEPROM_END_ADDRESS	0x0FFF
#endif

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

/**
 * Write to an EEPROM memory address
 * 
 *
 * @param  dst		16 bit EEPROM destination address
 * @param  data		A pointer to the start of the data to be stored
 * @param  length	The number of bytes to be stored
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */
mem_return mem::write_mem(uint16_t dst, void* data, uint16_t length)
{
	/*Perform check to see if memory address is out of range of EEPROM*/
	if (dst > EEPROM_END_ADDRESS)
	{
		//return 'memory start out of bounds'
		return ADDRESS_OUT_OF_BOUNDS;
	}
	else if ((dst + length) > EEPROM_END_ADDRESS)
	{
		//return length over reaches end of memory
		return PROCESS_ERROR;
	}
	
	/*Write to EEPROM with the eeprom_write_block() function*/
	eeprom_busy_wait();
	eeprom_write_block(data, (void *)dst, length);
	eeprom_busy_wait();
	
	return MEM_SUCCESS;	//For now
}

/**
 * Read from an EEPROM memory address
 * 
 *
 * @param  src		16 bit EEPROM source address
 * @param  dst		A pointer to the start of the destination where the data will be stored
 * @param  length	The number of bytes to be read
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */
mem_return mem::read_mem(uint16_t src, void* dst, uint16_t length)
{
	/*Perform check to see if memory address is out of range of EEPROM*/
	if (src > EEPROM_END_ADDRESS)
	{
		//return 'memory start out of bounds'
		return ADDRESS_OUT_OF_BOUNDS;
	}
	else if (src > (EEPROM_END_ADDRESS - length))
	{
		//return length over reaches end of memory
		return PROCESS_ERROR;
	}
	
	/*Read from EEPROM with the eeprom_read_block() function*/
	eeprom_busy_wait();
	eeprom_read_block(dst, (void *)src, length);
	eeprom_busy_wait();
	
	return MEM_SUCCESS;	//For now
}

/**
 * Copy from one EEPROM memory location to another
 * 
 *
 * @param  src		16 bit EEPROM source address
 * @param  dst		16 bit EEPROM destination address
 * @param  length	The number of bytes to be copied
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */		
mem_return mem::cpy_mem(uint16_t src, uint16_t dst, uint16_t length)
{
	/*Perform check to see if memory address is out of range of EEPROM*/
	if ((dst > EEPROM_END_ADDRESS) || (src > EEPROM_END_ADDRESS))
	{
		//return 'memory start out of bounds'
		return ADDRESS_OUT_OF_BOUNDS;
	}
	else if (((dst + length) > EEPROM_END_ADDRESS) || ((src + length) > EEPROM_END_ADDRESS))
	{
		//return length over reaches end of memory
		return PROCESS_ERROR;
	}
	
	/*Initialise a buffer to read some of the transferral data from*/
	uint8_t ram_buffer[length];
		
	/*Read from EEPROM source location into a temp. buffer with the eeprom_read_block() function*/
	eeprom_busy_wait();
	eeprom_read_block(&ram_buffer[0], (void *)src, length);
	eeprom_busy_wait();
			
	/*Write to EEPROM source location from the destination location with the eeprom_write_block() function*/
	eeprom_busy_wait();
	eeprom_write_block((void *)dst, (void *)src, length);
	eeprom_busy_wait();
	
	/*Write from the temporary buffer into destination location*/
	eeprom_busy_wait();
	eeprom_write_block(&ram_buffer[0], (void *)dst, length);
	eeprom_busy_wait();
	
	return MEM_SUCCESS;	//For now	
}

/**
 * Clear a section of EEPROM memory
 * 
 *
 * @param  address	16 bit EEPROM memory address to clear from
 * @param  length	The number of bytes to be cleared
 * @return uint8_t 	Result, 0 for success, various other numbers refer to error codes, such as memory out of bounds.
 */		
mem_return mem::clear_mem(uint16_t address, uint16_t length)
{
	/*Perform check to see if memory address is out of range of EEPROM*/
	if (address > EEPROM_END_ADDRESS)
	{
		//return 'memory start out of bounds'
		return ADDRESS_OUT_OF_BOUNDS;
	}
	else if ((address + length) > EEPROM_END_ADDRESS)
	{
		//return length over reaches end of memory
		return PROCESS_ERROR;
	}
	
	//Read the EEPROM byte to see if it is 'cleared' or not
	uint16_t i;
	for ( i = 0; i < length; i++)
	{
		//Read the EEPROM byte to see if it is 'cleared' or not - if cleared, the byte will be 0xFF
		eeprom_busy_wait();
		if (eeprom_read_byte((const uint8_t *)(address + i)) != 0xFF)
		{
			eeprom_busy_wait();//If not 'cleared'...clear it.
			eeprom_write_byte((uint8_t *)(address + i), 0xFF);
		}
		eeprom_busy_wait();
	}
		
	return MEM_SUCCESS;	//For now
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
