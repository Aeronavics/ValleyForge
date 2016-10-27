// Copyright (C) 2016  Aeronavics Ltd
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
 *  @author			Sam Dirks
 *
 *
 *  @date			8-1-2016
 *
 *  @section 		Licence
 *
 * Copyright (C) 2016  Aeronavics Ltd
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
#pragma once

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

#include <stddef.h>
#include <stdint.h>

#include "hal/hal.hpp"
#include "hal/target_config.hpp"
#include "hal/gpio.hpp"

// FORWARD DEFINE PRIVATE PROTOTYPES.

class I2c_imp;

// DEFINE PUBLIC CLASSES, TYPES AND ENUMERATIONS.

#define I2C_BUFFER_SIZE 20

#define CLK_TO_HZ 10000

enum I2c_clk_speed
{
	I2C_10kHz = 1,
	I2C_100kHz = 10,
	I2C_400kHz = 40
};

enum I2c_command_status {I2C_CMD_ACK, I2C_CMD_NAK, I2C_CMD_BUSY, I2C_CMD_IMMUTABLE};

enum I2c_gc_mode {I2C_GC_ENABLED, I2C_GC_DISABLED};

enum I2c_mode
{
	I2C_IDLE,                 // The I2C interface is idle
	I2C_MASTER_TRANSMITTING,  // The I2C interface is transmitting as master
	I2C_MASTER_RECEIVING,     // The I2C interface is receiving as master
	I2C_SLAVE_TRANSMITTING,   // The I2C interface is transmitting as slave
	I2C_SLAVE_RECEIVING,      // The I2C interface is receiving as slave
	I2C_SLAVE_RECEIVING_GC    // The I2C interface is receiving as slave address as general call
};

enum I2c_pullup_state {I2C_PULLUP_ENABLED, I2C_PULLUP_DISABLED};

enum I2c_address_type {I2C_7BIT_ADDRESS, I2C_10BIT_ADDRESS};

struct I2c_address
{
	I2c_address_type type;

	union
	{
		uint8_t addr_7bit;
		uint16_t addr_10bit;
	} address;

	static I2c_address from_7bit(uint8_t addr)
	{
		I2c_address _address;

		_address.type = I2C_7BIT_ADDRESS;
		_address.address.addr_7bit = addr & 0x7F;

		// All done.
		return _address;
	}

	static I2c_address from_10bit(uint16_t addr)
	{
		I2c_address _address;

		_address.type = I2C_10BIT_ADDRESS;
		_address.address.addr_10bit = addr & 0x03FF;

		// All done.
		return _address;
	}
};

enum I2c_event
{
	I2C_BUS_ERROR,
	I2C_ARB_LOST,
	I2C_MASTER_TX_SLA_NAK,
	I2C_MASTER_TX_COMPLETE,
	I2C_MASTER_TX_DATA_NAK,
	I2C_MASTER_RX_SLA_NAK,
	I2C_MASTER_RX_COMPLETE,
	I2C_SLAVE_RX_BUF_FULL,
	I2C_SLAVE_RX_GC_BUF_FULL,
	I2C_SLAVE_RX_COMPLETE,
	I2C_SLAVE_RC_GC_COMPLETE,
	I2C_SLAVE_TX_COMPLETE,
	I2C_SLAVE_TX_COMPLETE_OVR
};

struct I2c_context
{
	I2c_event event;
	void* context; // context for the event.
};

/**
 * @class
 *
 * This class implements various functions relating to operating a I2C interface.
 *
 */
class I2c
{
	public:

		// Functions.

		/**
		 * Create I2C instance abstracting the specified I2C hardware peripheral.
		 */
		I2c(I2c_number i2c_number);

		/**
		 * Called when I2C instance goes out of scope
		 */
		~I2c(void);
		
		/**
		 * Initialise the I2C interface. The initialised state has the slave disabled.
		 *
		 * @param clk_speed    The I2C clock frequency to use.
		 * @param slave_adr    The slave address to assign to this interface.
		 * @param callback     The callback to use to handle completion of I2C operation notifications.
		 // NOTE - The i2c bus has the clock held low until after the callback returns.
		 * @return   Success or Failure response.
		 */
		I2c_command_status initialise(I2c_clk_speed clk_speed, I2c_address slave_addr, Callback callback);
		
		/**
		 * Set the state of the internal pullups.
		 *
		 * @param    pullup_state     The state to which to set the pullups.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status set_internal_pullup(I2c_pullup_state pullup_state);
		
		/**
		 * Get the status of the I2C interface.
		 *
		 * @return   The status of the I2C interface.
		 */
		I2c_mode get_i2c_status(void);

		/**
		 * Enable slave operation when the interface is next enters idle state.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status enable_slave(void);
		
		/**
		 * Disable slave operation when the interface is next enters idle state.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status disable_slave(void);
		
		/**
		 * Enable or disable the general call handling with general call mode. On disabling if a general
		 * call receive is in progress it will be allowed to conclude.
		 *
		 * @param    gc_mode The general call mode to use, enable or disable.
		 * @return   Success or Failure response.
		 */
		I2c_command_status set_general_call_mode(I2c_gc_mode gc_mode);
		
		/**
		 * The controller waits until the bus is free then becomes the master controller and transmits
		 * a message to a desired slave controller.
		 * This is a non blocking function.
		 *
		 * @param    slave_adr    The slave to transmit to.
		 * @param    data         Pointer to the array that contains bytes of message.
		 * @param    msg_size     Number of bytes to send.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status master_transmit(I2c_address slave_addr, uint8_t* data, uint8_t msg_size);
		I2c_command_status master_transmit_blocking(I2c_address slave_addr, uint8_t* data, uint8_t msg_size);

		/**
		 * The controller waits until the bus is free then becomes the master controller and requests
		 * data bytes from a slave controller.
		 * This is a non blocking function.
		 *
		 * @param    slave_adr    The slave to receive from.
		 * @param    data         Pointer to the the array to receive the bytes of message into.
		 * @param    msg_size     Number of bytes to receive.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status master_receive(I2c_address slave_addr, uint8_t* data, uint8_t msg_size);

		/**
		 * The controller waits until the bus is free then becomes the master transmitter to send bytes 
		 * to the slave followed by a repeated start becoming the master receiver to receive bytes from
		 * the slave.
		 * This is a non blocking function.
		 *
		 * @param    slave_adr      The slave to send to and receive from.
		 * @param    tx_data        Pointer to the the array that contains bytes of message to send.
		 * @param    tx_msg_size    Number of bytes to send.
		 * @param    rx_data        Pointer to the the array to receive the bytes of message into.
		 * @param    rx_msg_size    Number of bytes to receive.
		 *
		 * @return Success or Failure response.
		 */
		I2c_command_status master_transmit_receive(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size);
		I2c_command_status master_transmit_receive_blocking(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size);
		
		/**
		 * As a slave controller store data into a buffer where the data will be
		 * transmitted on a request from a master controller. Will not overwite 
		 * the transmit buffer if alreay transmitting as slave.
		 *
		 * @param    data                 The data to be stored in the I2C buffer.
		 * @param    msg_size             Number of bytes to save.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status slave_transmit(uint8_t* data, uint8_t msg_size);

		/**
		 * As a slave controller, the I2C receive buffer is checked to see if any data has been
		 * received. If there is data then it is copied into an array. Will prevent new data from
		 * being received while the buffer is being read.
		 *
		 * @param    data     Location where the data should be stored.
		 * @param    msg_size The number of bytes received. This is a return value.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status slave_receive(uint8_t* data, uint8_t* msg_size);

		
		/**
		 * As a slave controller, the I2C general call receive buffer is checked to see if any data has been
		 * received. If there is data, then it is stored in an array. Will prevent new data from
		 * being received while the buffer is being read.
		 *
		 * @param    data     Location where the data should be stored.
		 * @param    msg_size The number of bytes received. This is a return value.
		 *
		 * @return   Success or Failure response.
		 */
		I2c_command_status slave_receive_general_call(uint8_t* data, uint8_t* msg_size);

	private:

		// Methods.
		
		I2c(void) = delete;	// Poisoned.
		I2c(I2c*) = delete;  // Poisoned.
		I2c(I2c_imp*);
		I2c operator =(I2c const&) = delete;	// Poisoned.

		// Fields.

		I2c_imp* imp;

};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

// ALL DONE.
