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

#include <stddef.h>
#include <stdint.h>

#include "hal/hal.hpp"
#include "hal/target_config.hpp"

// FORWARD DEFINE PRIVATE PROTOTYPES.

class I2C_imp;

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

enum I2C_mode
{
	I2C_MASTER = 0x0,
	I2C_SLAVE = 0x1,
	I2C_TRANSMITTER = 0x2,
	I2C_RECEIVER = 0x4
};

enum CPU_CLK_speed
{
  CPU_1MHz = 100,     // No external pull-up required at this bus speed.
  CPU_8MHz = 800,
  CPU_16MHz = 1600
};

enum I2C_SCL_speed
{
  I2C_10kHz = 1,     // No external pull-up required at this bus speed.
  I2C_100kHz = 10,
  I2C_400kHz = 40
};

enum I2C_send_condition_t
{
	I2C_START,
	I2C_STOP,
	I2C_REPEATED_START
};

enum SLA_adr
{
  SLA0_ADR = 0x01,
  SLA1_ADR = 0x02,
  SLA2_ADR = 0x03
};

enum I2C_return_status
{
  I2C_SUCCESS = 0x01,
  I2C_ERROR = 0x00
};

// The following status codes can be found in TWSR (the status register), depending on certain conditions. The condition required for each of these
// status codes to be displayed is summarised to the right of each definition.
enum I2C_status_code
{
	// Master-specific codes ---------------------------------------------------------------------------------------------------------------------------
	NO_INFO_TWINT_NOT_SET				= 0xf8,	// Meaning: The TWINT flag is not set, so no relevant information is available
	BUS_ERROR							= 0x00,	// A bus error has occurred during a Two-wire Serial Bus transfer.
												// From the data sheet: a bus error occurs

	// Transmission
	MT_START 							= 0x08,	// A START condition has been transmitted
	MT_REPEAT_START 					= 0x10,	// A repeated START condition has been transmitted
	MT_SLA_ACK 							= 0x18,	// SLA+W has been transmitted. ACK has been received.
	MT_SLA_NAK 						= 0x20,	// SLA+W has been transmitted. NOT ACK has been received.
	MT_DATA_ACK 						= 0x28,	// Data byte has been transmitted. ACK has been received.
	MT_DATA_NAK 						= 0x30,	// Data byte has been transmitted. NOT ACK has been received.

	// Transmission or Reception
	MTR_LOST_ARB 						= 0x38,	// Arbitration lost in SLA+W OR data bytes (master-transmitter)
												// OR Arbitration lost in SLA+R or NOT ACK bit (master-receiver)
	// Reception
	MR_SLA_ACK 							= 0x40,	// SLA+R has been transmitted, ACK has been received
	MR_SLA_NAK 						= 0x48,	// SLA+R has been transmitted; NOT ACK has been received
	MR_DATA_ACK 						= 0x50,	// Data byte has been received; ACK has been returned
	MR_DATA_NAK 						= 0x58,	// Data byte has been received; NOT ACK has been returned

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
	S_SENT_LAST_BYTE_SENT_ACK 			= 0xC8, 	// Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received

  // Kevins made up debugging codes
  SOMETHING_WENT_WRONG        = 0xD0
};

struct tx_type
{
	uint8_t slave_adr;				//Slave address and W/R byte
	uint8_t bytes;						//Number of bytes to send or
											//receive
	uint8_t *data_ptr;				//Pointer to the bytes to send
};

/**
 * @class
 *
 * This class implements various functions relating to operating a I2C interface.
 *
 */
class I2C
{
	public:

    // Functions.

    /**
     * Create I2C instance abstracting the specified I2C hardware peripheral.
     */
		I2C();

    /**
     * Called when I2C instance goes out of scope
     */
		~I2C(void);

    /**
     * Enables the I2C/TWI interface by setting the enable bit in the control register.
     */
		void enable(void);

    /**
     * Disables the I2C/TWI register by un setting the enable bit in the control register.
     */
		void disable(void);

    /**
     * Initialise the parameters for I2C use.
     *
     * @param    I2C_bit_rate    The bitrate of the I2C/TWI interface.
     *           I2C_prescalar    Prescale value of I2C/TWI interface.
     */
		I2C_return_status initialise(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed);

    /**
     * Send START signal of I2C.
     */
		void start();

    /**
     * Send STOP signal of I2C.
     */
		void stop();

    /**
     * Set the mode of I2C.
     *
     * @param    I2C_mode    A selection of operating modes for the device I2C.
     *
     */
		I2C_status_code transmit(tx_type *data);

    /**
     * Set the slave mode for I2C.
     *
     * @param    I2C_mode    A selection of operating modes for the device I2C.
     *
     */
		I2C_status_code receive(tx_type *data);

    /**
     * Check if the I2C Interrupt Service Routine is busy.
     */
		I2C_status_code transceiver_busy();

	private:

		// Methods.

		// I2C(void) = delete;	// Poisoned.

		// I2C(I2C*) = delete;	// Poisoned.

		I2C(I2C_imp*);

		//I2C operator = (I2C const&) = delete;	// Poisoned.

		// Fields.

		I2C_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__I2C_H__*/

// ALL DONE.
