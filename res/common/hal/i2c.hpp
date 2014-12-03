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
 *
 *  @addtogroup		hal Hardware Abstraction Library
 * 
 *  @file			i2c.hpp
 *  A header file for the I2C Module of the HAL.
 * 
 *  @brief 
 *  This is the header file which matches i2c.cpp.  Implements various functions relating to I2C, transmission
 *  and receiving of messages.
 * 
 *  @author			Ben O'Brien, derived from CAN-bus code by Paul Davey & George Xian
 *	 				Documentation based on AT90CAN128 data sheet Rev. 7679H–CAN–08/08, by ATMEL
 * 
 *  @date			1-02-2014
 * 
 *  @section 		Licence
 * 
 * Copyright (C) 2014  Unison Networks Ltd
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
 *  @section Description
 *
 * A class for the I2C module of the HAL. Implements various functions relating to I2C hardware 
 * initialisation, transmission and receiving of data.
 */

// Only include this header file once.
#ifndef __I2C_H__
#define __I2C_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>
#include <stdint.h>

// Include hal library components.
#include "hal/hal.hpp"
#include "hal/target_config.hpp"

class I2C_imp;
// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

class I2C;

enum I2C_mode_t 
{
	I2C_MASTER = 0x0,
	I2C_SLAVE = 0x1,
	I2C_TRANSMITTER = 0x2,
	I2C_RECEIVER = 0x4
};


enum I2C_send_condition_t 
{
	I2C_START,
	I2C_STOP,
	I2C_REPEATED_START
};


enum I2C_return_status {I2C_SUCCESS, I2C_ERROR};

enum I2C_prescaler_value_t 
{
	TW_PRESCALER_1 = 0x0,
	TW_PRESCALER_4 = 0x1,
	TW_PRESCALER_16 = 0x2,
	TW_PRESCALER_64 = 0x3
};


// The following status codes can be found in TWSR (the status register), depending on certain conditions. The condition required for each of these 
// status codes to be displayed is summarised to the right of each definition.
enum I2C_status_code_t 
{
	// Master-specific codes ---------------------------------------------------------------------------------------------------------------------------
	NO_INFO_TWINT_NOT_SET				= 0xf8,	// Meaning: The TWINT flag is not set, so no relevant information is available 
	BUS_ERROR							= 0x00,	// A bus error has occurred during a Two-wire Serial Bus transfer.
												// From the data sheet: a bus error occurs 
	
	// Transmission
	MT_START 							= 0x08,	// A START condition has been transmitted 
	MT_REPEAT_START 					= 0x10,	// A repeated START condition has been transmitted
	MT_SLA_ACK 							= 0x18,	// SLA+W has been transmitted. ACK has been received.
	MT_SLA_NACK 						= 0x20,	// SLA+W has been transmitted. NOT ACK has been received.
	MT_DATA_ACK 						= 0x28,	// Data byte has been transmitted. ACK has been received.
	MT_DATA_NACK 						= 0x30,	// Data byte has been transmitted. NOT ACK has been received.

	// Transmission or Reception
	MTR_LOST_ARB 						= 0x38,	// Arbitration lost in SLA+W OR data bytes (master-transmitter)
												// OR Arbitration lost in SLA+R or NOT ACK bit (master-receiver)
	// Reception
	MR_SLA_ACK 							= 0x40,	// SLA+R has been transmitted, ACK has been received
	MR_SLA_NACK 						= 0x48,	// SLA+R has been transmitted; NOT ACK has been received
	MR_DATA_ACK 						= 0x50,	// Data byte has been received; ACK has been returned
	MR_DATA_NACK 						= 0x58,	// Data byte has been received; NOT ACK has been returned

	// Slave-specific codes ---------------------------------------------------------------------------------------------------------------------------
	
	// Transmission
	S_GOT_OWN_SLA_ACK					= 0x60,	// Own SLA+W has been received; ACK has been returned
	S_LOST_ARB_1						= 0x68,	// Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned
	S_GOT_GEN_CALL_ADD_ACK				= 0x70,	// General call address has been received; ACK has been returned
	S_LOST_ARB_2						= 0x78,	// Arbitration lost in SLA+R/W as master; General call address has been received; ACK has been returned
	S_PREV_ADDR_SLAW_W_DATA_ACK			= 0x80,	// Previously addressed with own SLA+W; data has been received; ACK has been returned
	S_PREV_ADDR_SLAW_W_DATA_NOT_ACK		= 0x88,	// Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
	S_PREV_ADDR_GEN_CALL_DATA_ACK		= 0x90,	// Previously addressed with general call; data has been received; ACK has been returned
	S_PREV_ADDR_GEN_CALL_DATA_NOT_ACK	= 0x98,	// Previously addressed with general call; data has been received; NOT ACK has been returned
	S_STOP_OR_REPEAT_START				= 0xA0,	// A STOP condition or repeated START condition has been received while still addressed as slave
	
	// Reception
	S_SLA_ACK 							= 0xA8,	// Own SLA+R has been received; ACK has been returned 
	S_LOST_ARB_3						= 0xB0,	// Arbitration lost in SLA+R/W as master; own SLA+R has been received; ACK has been returned
	S_SENT_BYTE_ACK 					= 0xB8,	// Data byte in TWDR has been transmitted; ACK has been received
	S_SENT_BYTE_NOT_ACK 				= 0xC0,	// Data byte in TWDR has been transmitted; NOT ACK has been received
	S_SENT_LAST_BYTE_SENT_ACK 			= 0xC8 	// Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
};


#define i2c_get_bit(address, pin) ((address & (1<<pin))>>pin)
#define i2c_set_bit(address, pin, value) {if(((value) & 0x1) == 1) (address) |= (1<<(pin)); else (address) &= ~(1<<(pin));}

#define I2C_COMMAND_START 	(1 << TWINT) | (1 << TWSTA) | (1 << TWEN)
#define I2C_COMMAND_STOP 	(1 << TWINT) | (1 << TWSTO) | (1 << TWEN)


/**
 * Interface class for an I2C controller.
 */
class I2C 
{
	friend class I2C_imp;
	
	public:
	
		/**
		 * I2C Constructor
		 */
		I2C(I2C_mode_t new_mode);
		
		/**
		 * Called when I2C instance goes out of scope
		 */
		~I2C(void);
		
		void enable(void);
		
		void disable(void);
		
		void set_bitrate_divider(uint8_t new_bitrate_divider);
		
		/**
		 * Sets the Clock Line (SCL) prescaler. 
		 * Valid inputs are TW_PRESCALER_1, TW_PRESCALER_4, TW_PRESCALER_16, TW_PRESCALER_64
		 */
		void set_prescaler(I2C_prescaler_value_t new_pre_scaler);
		
		I2C_return_status start(uint8_t addres);
		
		I2C_return_status stop();
		
		I2C_return_status set_mode(I2C_mode_t new_mode);
		
		I2C_status_code_t get_status();
		
		I2C_return_status write(uint8_t write_value);
		
	private:
	
		// Methods.

		I2C(void);	// Poisoned.

		I2C(I2C*);	// Poisoned.

		I2C(I2C_imp*);

		I2C operator =(I2C const&);	// Poisoned.

		// Fields.

		I2C_imp* implementation;
};

#endif /*__I2C_H__*/

// 
// Registers used for testing purposes only
uint8_t test_TWAR = 0x00;
uint8_t test_TWBR = 0x00;
uint8_t test_TWCR = 0x00;
uint8_t test_TWSR = 0x00;
uint8_t test_TWDR = 0x00;
bool is_debug_mode = true;

// ALL DONE.
