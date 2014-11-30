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
 *  @file		Usart.h
 *  A header file for the USART Module of the HAL. USART communication.
 * 
 *  @brief 
 *  A class for the USART module of the HAL. Implements various functions relating to USART/UART 
 *  initialisation, transmission and receiving of data.
 * 
 *  @author		Paul Bowler
 *
 *  @date		17-01-2012
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
 * A class for the USART module of the HAL. Implements various functions relating to USART/UART 
 *  initialisation, transmission and receiving of data.
 * 
 * @section Example
 * @code
 * uint8_t my_data[100];
 * int i = 100
 * 
 * // Get the chosen USART channel
 * Usart my_usart = Usart::grab(USART_0);
 * 
 * // Set the USART for Asynchronous mode
 * my_usart.set_mode(USART_MODE_ASYNCHRONOUS);
 * 
 * // Set up USART for 9600 Baud, 8N1
 * my_usart.set_baud_rate(9600);
 * 
 * my_usart.set_frame(8,n,1);
 * 
 * while (i--)
 * {
 * 	if (my_usart.receive_complete())
 *      {
 * 		my_data[i-1] = my_usart.receive_byte();
 *      }
 * }
 * @endcode
 */

// Only include this header file once.
#ifndef __USART_H__
#define __USART_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the hal library.
#include "hal/hal.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

// USART configuration operation status.
enum Usart_config_status {USART_CFG_SUCCESS = 0, USART_CFG_IMMUTABLE = -1, USART_CFG_FAILED = -2};

// USART IO operation status.
enum Usart_io_status {USART_IO_SUCCESS = 0, USART_IO_FAILED = -1, USART_IO_NODMA = -2, USART_IO_DMABUSY = -3};

// USART interrupt configuration status
enum Usart_int_status {USART_INT_SUCCESS = 0, USART_INT_EXISTS = -1, USART_INT_NOINT = -2, USART_INT_FAILED = -3};

/**
 * Available USART channels are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *		enum Usart_channel {USART_0, USART_1};
 *
 */

/**
 * Available USART modes are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *		enum Usart_setup_mode {USART_MODE_ASYNCHRONOUS, USART_MODE_SYNCHRONOUS, USART_MODE_MASTERSPI};
 *
 */

/**
 * Available Master SPI bit orders are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *		enum Usart_mspim_bit_order {USART_MSPIM_MSB_FIRST, USART_MSPIM_LSB_FIRST};
 *
 */

/**
 * Available Master SPI sub-modes are defined in the target specific configuration header.  This takes the form of an enum similar to that shown below.
 *
 *		enum Usart_mspim_mode {USART_MSPI_MODE_0, USART_MSPI_MODE_1, USART_MSPI_MODE_2, USART_MSPI_MODE_3};
 *
 */

// TODO - A bunch of these probably also need to be moved into the target specific configuration file.

enum Usart_parity {USART_PARITY_NONE, USART_PARITY_EVEN, USART_PARITY_ODD, USART_PARITY_MARK, USART_PARITY_SPACE};

enum Usart_clock_polarity {USART_CLOCK_NORMAL, USART_CLOCK_INVERTED};

//enum Usart_interrupt_type {USART_INT_RX, USART_INT_TX, USART_INT_UDRE};

// NOTE - Not all these interrupts may be supported by the target
enum Usart_interrupt_type {
	USART_INT_RX_COMPLETE,
	//USART_INT_TX_COMPLETE, //AVR32
	USART_INT_RX_OVERFLOW_ERROR,
	USART_INT_RX_FRAMING_ERROR,
	USART_INT_RX_PARITY_ERROR,
};

// NOTE - Not all these error codes may be supported by the target
enum Usart_error_type {
	USART_ERR_NONE,
	USART_ERR_FRAME=-1,
	USART_ERR_DATA_OVERRUN=-2,
	USART_ERR_PARITY=-3
};

typedef uint16_t Usart_baud_rate;

typedef void(*usartrx_callback_t)(Usart_io_status, uint8_t* buffer, size_t received_bytes);
typedef void(*usarttx_callback_t)(Usart_io_status);

// FORWARD DEFINE PRIVATE PROTOTYPES.

class Usart_imp;

// DEFINE PUBLIC CLASSES.

/**
 * @class
 * A class for the USART module of the HAL. Implements various functions relating to USART/UART initialisation, transmission and receiving of data.
 */
class Usart
{
	friend class Usart_imp;

	public:
		// Methods.
		
		/**
		 * Binds the interface with a USART hardware peripheral.
		 */
		static Usart bind(Usart_channel channel);
		
		/**
		 * Called when USART instance goes out of scope
		 */
		~Usart(void);

		/**
		 * Initialises the USART and configures the operating mode as specified.
		 * 
		 * @param  mode			Operating mode to set the USART to.
		 * @return 				The status of the operation
		 */
		Usart_config_status set_mode(Usart_setup_mode mode);
		
		/**
		 * Configures the serial data format to be used for the USART as specified.
		 *
		 * @param data_bits		Number of bits to be used for transmitting data (typically 8 bits)
		 * @param parity		Type of parity to use.
		 * @param start_bits 	Number of start bits in frame.
		 * @param stop_bits		Number of stop bits in frame.
		 * @return				The status of the operation
		 */
		Usart_config_status set_frame(uint8_t data_bits, Usart_parity parity, uint8_t start_bits, uint8_t stop_bits);
		
		/**
		 * Configures the desired Baud rate for USART communication.
		 *
		 * @param rate			Desired Baud rate to use for communication.
		 * @return 				The status of the operation
		 */
		Usart_config_status set_baud_rate(Usart_baud_rate rate);
		
		/**
		 * Indicates whether the USART transmitter is ready to transmit data
		 * (ie. not currently transmitting anything)
		 */
		bool transmitter_ready(void);

		/**
		 * Indicates whether the USART receiver has a byte available to read.
		 * Only guarantees at least one byte is available, no more.
		 */
		bool receiver_has_data(void);

		/**
		 * Transmit a byte of data via the configured USART connection, blocking until the
		 * transfer has completed.
		 *
		 * @param data			Byte to be transmitted via the USART
		 * @return 				The status of the operation
		 */
		Usart_io_status transmit_byte(uint8_t data);

		/**
		 * Transmit a byte of data asynchronously via the configured USART connection.
		 * This method returns immediately.
		 *
		 * This method assumes the UART is ready, and returns immediately.
		 * Use transmitter_ready() to determine when it is safe to call this method.
		 *
		 * @param data			Byte to be transmitted via the USART
		 * @return 				The status of the operation
		 */
		Usart_io_status transmit_byte_async(uint8_t data);

		/**
		 * Transmits a block of data via the configured USART connection, blocking until the
		 * transfer has completed.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.
		 *
		 * @param buffer		Pointer to the block of data to be transmitted
		 * @param size			The size of the block of data, in bytes
		 * @return				The status of the operation
		 */
		Usart_io_status transmit_buffer(uint8_t* data, size_t size);

		/**
		 * Transmits a block of data asynchronously via the configured USART connection.
		 * This method returns immediately.
		 *
		 * This method assumes the UART is ready, and returns immediately.
		 * Use transmitter_ready() to determine when it is safe to call this method.
		 *
		 * NOTE - This function could potentially use DMA or hardware FIFOs to increase speed.
		 *
		 * @param buffer		Pointer to the block of data to be transmitted
		 * @param size			The size of the block of data, in bytes
		 * @param cb_done		Optional callback to be executed when the buffer has been fully transmitted, or an error has occurred.
		 * 						Callback must have the following signature:
		 * 							void callback(Usart_io_status status);
		 * @return 				The status of the operation
		 */
		Usart_io_status transmit_buffer_async(uint8_t* buffer, size_t size, usarttx_callback_t cb_done = NULL);

		/**
		 * Transmits a null-terminated string of variable length up to max_len bytes, via the
		 * configured USART connection, blocking until the transfer has completed.
		 *
		 * @param string		A null-terminated string
		 * @param max_len		Maximum number of bytes to send
		 * @return				The status of the operation
		 */
		Usart_io_status transmit_string(char *string, size_t max_len);

		/**
		 * Transmits a null-terminated string of variable length up to max_len bytes, asynchronously via
		 * the configured USART connection.
		 *
		 * This method assumes the UART is ready, and returns immediately.
		 * Use transmitter_ready() to determine when it is safe to call this method.
		 *
		 * @param string		A null-terminated string
		 * @param max_len		Maximum number of bytes to send
		 * @param cb_done		Optional callback to be executed when the buffer has been fully transmitted, or an error has occurred.
		 * 						Callback must have the following signature:
		 * 							void callback(Usart_io_status status);
		 * @return				The status of the operation
		 */
		Usart_io_status transmit_string_async(char *string, size_t max_len, usarttx_callback_t cb_done = NULL);

		/**
		 * Read a byte from the receive buffer, blocking if not yet available.
		 *
		 * Equivalent to
		 * 	while (!usart.receiver_has_data()) { }
		 * 	return usart.receive_byte_async();
		 *
		 * @return The received byte, or an error status code.
		 */
		int16_t receive_byte(void);

		/**
		 * Read a byte from the receive buffer if available.
		 * Returns immediately, use receiver_has_data() to determine if data is available.
		 *
		 * @return The received byte, or an error status code.
		 */
		int16_t receive_byte_async(void);

		/**
		 * Receives a block of data via the configured USART connection into the
		 * provided buffer, blocking until all bytes have been received.
		 * Ensure the provided buffer has enough bytes to avoid buffer overflows.
		 *
		 * @param data			A pointer to a buffer to store the received data
		 * @param size			The number of bytes to receive
		 * @return 				The status of the operation
		 */
		Usart_io_status receive_buffer(uint8_t *data, size_t size);

		/**
		 * Receives a block of data via the configured USART connection into the
	 	 * provided buffer, blocking until all bytes have been received.
		 * Ensure the provided buffer has enough bytes to avoid buffer overflows.
		 *
		 * NOTE - This function could potentially use DMA or hardware FIFOs to increase speed.
		 *
		 * @param data			A pointer to a buffer to store the received data
		 * @param size			The number of bytes to receive
		 * @param cb_done		Optional callback to be executed when the buffer has been fully received, or an error has occurred.
		 * 						Callback must have the following signature:
		 * 							void callback(Usart_io_status status, uint8_t *rx_data, size_t received_bytes);
		 * @return 				The status of the operation
		 */
		Usart_io_status receive_buffer_async(uint8_t *data, size_t size, usartrx_callback_t cb_done);

		/**
		 * Receives a NULL-terminated string, up to max_len bytes, blocking until all bytes have been received.
		 * Ensure the provided buffer has at least max_len bytes to avoid buffer overflows.
		 *
		 * @param string		A pointer to a buffer to store the null-terminated string
		 * @param max_len		Maximum size of string to receive, in bytes (to prevent buffer overflows)
		 * @param actual_size	Optional, updated with the number of actual bytes received (including the NULL char)
		 * @return 				The status of the operation
		 */
		Usart_io_status receive_string(char *buffer, size_t max_len, size_t *actual_size = NULL);

		/**
		 * Receives a NULL-terminated string, up to max_size bytes, calling the provided callback when all bytes have been received.
		 * Ensure the receiving buffer has enough bytes to avoid buffer overflows.
		 *
		 * @param string		A pointer to a buffer to store the null-terminated string
		 * @param max_len		Maximum size of string to receive, in bytes (to prevent buffer overflows)
		 * @param cb_done		Optional callback to be executed when a string has been fully received, or an error has occurred.
		 * 						Callback must have the following signature:
		 * 							void callback(Usart_io_status status, uint8_t *rx_data, size_t received_bytes);
		 * @return				The status of the operation
		 */
		Usart_io_status receive_string_async(char *buffer, size_t max_len, usartrx_callback_t cb_done);

		/**
		 * Enable interrupt generation by this USART channel.
		 */
		void enable_interrupts(void);

		/**
		 * Disable interrupt generation by this USART channel.
		 */
		void disable_interrupts(void);

		/**
		 * Attaches an interrupt handler to a particular interrupt event source associated with this USART channel.
		 * Enables an interrupt to be be associated with a USART connection.
		 *
		 * @param interrupt		One of the possible interrupt sources that are available.
		 * @param ISRptr		Pointer to the user-defined ISR.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_int_status attach_interrupt(Usart_interrupt_type interrupt, callback_t callback);

		/**
		 * Detaches an interrupt handler from a particular interrupt event source associated with this USART channel.
		 *
		 * @param interrupt		One of the possible interrupt sources that are available.
		 * @return 0 for success, -1 for error.
		 */
		Usart_int_status detach_interrupt(Usart_interrupt_type interrupt);
		 
		/**
		 * Returns whether an error has occured with the USART transfer.
		 *
		 * @return error The current USART error status i.e the status of the last USART transfer.
		 */
		Usart_error_type usart_error(void);

		/**
		 * Clear all errors
		 *
		 * @return Nothing.
		 */
		void usart_clear_errors(void);

	private:

		// Methods.
		
		Usart(void);	// Poisoned.

		Usart(Usart*);	// Poisoned.

		Usart(Usart_imp*);

		Usart operator =(Usart const&);	// Poisoned.

		// Fields.

		Usart_imp* imp;
};

// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__USART_H__*/

// ALL DONE.
