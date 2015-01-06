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
 *  @file		spi.h
 *  A header file for the SPI Module of the HAL. SPI communication.
 * 
 *  @brief 
 *  This is the header file which matches spi.cpp.  Implements various functions relating to SPIinitialisation, transmission
 *  and receiving of data.
 * 
 *  @author		Paul Bowler
 *
 *  @date		25-01-2012
 * 
 *  @section 		Licence
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
 *  @section Description
 *
 * A class for the SPI module of the HAL. Implements various functions relating to SPI 
 *  initialisation, transmission and receiving of data.
 */

// Only include this header file once.
#ifndef __SPI_H__
#define __SPI_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal/hal.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

//enum Spi_data_direction {SPI_2LINE_FULL_DUPLEX, SPI_2LINE_RX, SPI_1LINE_RX, SPI_1LINE_TX};
//enum Spi_status {SPI_BUSY, SPI_OVERRUN, SPI_MODEFAULT, SPI_CRCERR, SPI_UNDERRUN, SPI_CHSIDE, SPI_TXE, SPI_RXNE};

// SPI configuration operation status.
enum Spi_config_status {SPI_CFG_SUCCESS = 0, SPI_CFG_IMMUTABLE = -1, SPI_CFG_FAILED = -2};

// SPI IO operation status.
enum Spi_io_status {SPI_IO_SUCCESS = 0, SPI_IO_FAILED = -1, SPI_IO_BUSY = -3, SPI_IO_OVERRUN = -4, SPI_IO_CRCERR = -5, SPI_IO_UNDERRUN = -6};

// SPI interrupt configuration status
enum Spi_int_status {SPI_INT_SUCCESS = 0, SPI_INT_EXISTS = -1, SPI_INT_NOINT = -2, SPI_INT_FAILED = -3};


// Specifies master/slave mode
enum Spi_setup_mode
{
	SPI_MASTER,
	SPI_SLAVE,
};

// Specifies polarity of Clock/Data signals
enum Spi_data_mode
{
	SPI_MODE_0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3
};


enum Spi_interrupt_type
{
	SPI_INT_TRANSFER_COMPLETE,	// The transfer has completed
};

enum Spi_slave_select_mode
{
	SPI_SS_NONE,		// Do not use SS pin. You must do it yourself
	SPI_SS_HARDWARE, 	// Use hardware SS pin automatically
	SPI_SS_SOFTWARE,	// Use the provided SS pin automatically
};

enum Spi_frame_format;

/**
 * Available SPI clock dividers are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *		enum Spi_clock_divider {SPI_DIV_1, SPI_DIV_2};
 *
 */

typedef void (*Spi_Data_Callback)(void *p, Spi_io_status status);

// FORWARD DEFINE PRIVATE PROTOTYPES.

class Spi_imp;

// DEFINE PUBLIC CLASSES.

/**
 * @class Spi
 * 
 * Implements various functions relating to SPI initialisation, transmission
 * and receiving of data.
 * 
 */
class Spi
{
public:

	/**
	 * Binds the interface with a SPI hardware peripheral.
	 */
	static Spi bind(Spi_channel channel);

	/**
	 * Destructor
	 */
	~Spi(void);

	/**
	 * Enable SPI hardware.
	 */
	void enable(void);

	/**
	 * Disable transmitter/receiver hardware.
	 * Called automatically by unbind()
	 */
	void disable(void);

	/**
	 * Configures the SPI transceiver.
	 * Calls set_mode(), set_data_config(), and enable()
	 *
	 * @param TODO
	 */
	Spi_config_status configure(Spi_setup_mode setup_mode, Spi_data_mode data_mode, Spi_frame_format frame_format);


	/**
	 * Configures the operating mode (master, slave)
	 *
	 * @param  mode	 		Operating mode to set the SPI to
	 * @return 				The status of the operation
	 */
	Spi_config_status set_mode(Spi_setup_mode mode);

	/**
	 * Configures the data format and SPI data mode.
	 *
	 * @param  mode			The data operating mode (clock and data polarity)
	 * @param  frame_format The format of the data frames (MSB/LSB first, number of bits)
	 * @return 				The status of the operation
	 */
	Spi_config_status set_data_config(Spi_data_mode data_mode, Spi_frame_format frame_format);

	/**
	 * Configures the speed of the SPI module
	 *
	 * @param  speed		The speed of the SPI output (target dependant, only valid in master mode)
	 * @return 				The status of the operation
	 */
	Spi_config_status set_speed(int16_t speed);
	Spi_config_status set_speed(Spi_clock_divider divider);

	/**
	 * Configures slave select (SS) pin functionality,
	 * if available on the chip.
	 *
	 * SPI must be configured for master mode!
	 *
	 * @param  mode			The slave select operating mode
	 * @return 				The status of the operation
	 */
	Spi_config_status set_slave_select(Spi_slave_select_mode mode, IO_pin_address software_ss_pin = {});

	/**
	 * Shift one byte through the SPI, blocking until the transfer has completed.
	 * In slave mode, this function will block until the master device clocks
	 * one byte of data through the interface.
	 *
	 * rx_data is optional. If NULL, received data will be discarded.
	 *
	 * @warning				Method blocks until one byte of data is clocked through the interface
	 * @param tx_data 		Byte to be transmitted
	 * @param rx_data 		Optional pointer to a variable which will be updated with the received byte
	 * @return 				The status of the operation
	 */
	Spi_io_status transfer(uint8_t tx_data, uint8_t *rx_data = nullptr);

	/**
	 * Shift one byte through the SPI asynchronously in the background.
	 * Ensure transfer_busy() is false before calling!
	 * The function returns immediately.
	 *
	 * rx_data is optional. If NULL, received data will be discarded.
	 * the done callback is also optional, and will be executed when the transfer is completed.
	 *
	 * @param tx_data 		Byte to be transmitted
	 * @param rx_data 		Optional pointer to a variable which will be updated with the received byte
	 * @param done 			Optional callback to be executed when the transmission is completed
	 * 						Callback must have the following signature:
	 * 							void callback(void *context, Spi_io_status status);
	 * @param context		Pointer to user data to be passed to the callback. Optional.
	 * @return 				The status of the operation
	 */
	Spi_io_status transfer_async(uint8_t tx_data, uint8_t *rx_data = nullptr, Spi_Data_Callback done = nullptr, void *context = nullptr);

	/**
	 * Shift a chunk of data through the SPI, blocking until the transfer has completed.
	 * Both buffers must have at least 'size' bytes allocated!
	 * In slave mode, this function will block until the master device clocks
	 * 'size' bytes through the interface.
	 *
	 * rx_data is optional. If NULL, received data will be discarded.
	 *
	 * @warning				Method blocks until 'size' bytes are clocked through the interface
	 * @param size 			The number of bytes to transfer
	 * @param tx_data 		Buffer to be transmitted
	 * @param rx_data 		Optional buffer to store received data to
	 * @return 				The status of the operation
	 */
	Spi_io_status transfer_buffer(size_t size, uint8_t *tx_data, uint8_t *rx_data = nullptr);

	/**
	 * Shift a chunk of data through the SPI, asynchronously.
	 * Both buffers must have at least 'size' bytes allocated!
	 * The function returns immediately.
	 *
	 * rx_data is optional. If NULL, received data will be discarded.
	 * the done callback is also optional, and will be executed when the transfer is completed.
	 *
	 * @param size 			The number of bytes to transfer
	 * @param tx_data 		Buffer to be transmitted
	 * @param rx_data 		Optional buffer to store received data to
	 * @param done 			Optional callback to be executed when the transmission is completed.
	 * 						Callback must have the following signature:
	 * 							void callback(void *context, Spi_io_status status);
	 * @param context		Pointer to user data to be passed to the callback. Optional.
	 * @return 				The status of the operation
	 */
	Spi_io_status transfer_buffer_async(size_t size, uint8_t *tx_data, uint8_t *rx_data = nullptr, Spi_Data_Callback done = nullptr, void *context = nullptr);

	/**
	 * Indicates whether the SPI is currently transferring something
	 *
	 * @return boolean 		true if the SPI is busy and you shouldn't use any transfer() functions!
	 */
	bool transfer_busy(void);

	/**
	 * Returns the current status of the SPI buffer.
	 * Also returned by transfer() operations
	 *
	 * @return 				status of the SPI module
	 */
	Spi_io_status get_status(void);

	/**
	 * Enable interrupt generation by this SPI channel.
	 */
	void enable_interrupts(void);

	/**
	 * Disable interrupt generation by this SPI channel.
	 */
	void disable_interrupts(void);

	/**
	 * Attaches an interrupt handler to a particular interrupt event source associated with this SPI channel.
	 * Enables an interrupt to be be associated with a SPI connection.
	 *
	 * @param interrupt		One of the possible interrupt sources that are available.
	 * @param callback		Pointer to the user-defined ISR. Accepts one void* parameter
	 * @param context		Pointer to user data to be passed to the callback. Optional.
	 * @return 				The status of the operation
	 */
	Spi_int_status attach_interrupt(Spi_interrupt_type interrupt, Callback callback, void *context = nullptr);

	/**
	 * Detaches an interrupt handler from a particular interrupt event source associated with this SPI channel.
	 *
	 * @param interrupt		One of the possible interrupt sources that are available.
	 * @return 0 for success, -1 for error.
	 */
	Spi_int_status detach_interrupt(Spi_interrupt_type interrupt);

private:
	// Functions.

	Spi(void);	// Poisoned.

	Spi(Spi_imp*);

	Spi operator =(Spi const&);	// Poisoned.

	// Fields.
	/**
	* Pointer to the machine specific implementation of the SPI.
	*/
	Spi_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__SPI_H__*/

// ALL DONE.
