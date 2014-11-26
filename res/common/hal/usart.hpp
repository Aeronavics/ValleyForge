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

enum Usart_parity {USART_PARITY_USART_ERR_NONE, USART_PARITY_EVEN, USART_PARITY_ODD};

enum Usart_clock_polarity {USART_CLOCK_NORMAL, USART_CLOCK_INVERTED};

enum Usart_interrupt_type {USART_INT_RX, USART_INT_TX, USART_INT_UDRE};

enum Usart_error_type {USART_ERR_NONE, USART_ERR_FRAME, USART_ERR_DATA_OVERRUN, USART_ERR_PARITY};

typedef uint16_t Usart_baud_rate;

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
		 * Initialises the USART and configures the operating mode as specfied.
		 * 
		 * @param  mode	 Operating mode to set the USART to.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_config_status set_mode(Usart_setup_mode mode);
		
		/**
		* Configures the (sub) mode of the connection when the USART is operating in Master SPI Mode.
		* 
		* @param  mode	SPI mode to apply to connection.
		* @return Zero for success, non-zero for failure.
		*/
		Usart_config_status set_spi_mode(Usart_mspim_mode mode);

		/**
		 * Configures the bit order (endian-ness) of the data frame when hardware is configured in Master SPI mode.
		 *
		 * @param order		Bit order option (endian-ness), either MSB or LSB first.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_config_status set_spi_bit_order(Usart_mspim_bit_order order);
		
		/**
		 * Configures the serial data format to be used for the USART as specified.
		 *
		 * @param size Character size to used.
		 * @param parity Type of parity to use.
		 * @param stop_bits	Number of stop bits in frame.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_config_status set_frame(uint8_t size, Usart_parity parity, uint8_t stop_bits);
		
		/**
		 * Configures the desired Baud rate for USART communication.
		 *
		 * @param rate	Desired Baud rate to use for communication.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_config_status set_baud_rate(Usart_baud_rate rate);
		
		// TODO - This seems target specific: on AVR, the RX and TX registers have the same address, but doubt others are all like this.

		/**
		 * Indicates whether or not the USART data buffer is available or not at the time of checking.
		 *
		 * @param void.
		 * @return boolean variable that is true if buffer is available, false otherwise.
		 */
		bool buffer_is_available(void);
		 
		// TODO - Not sure about the truth to these statements about interrupts remaining enabled.

		/**
		 * Performs a blocking transmission of one byte via the configured USART connection.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.  Interrupts remain enabled.
		 *
		 * @param data		Byte to be transmitted via the USART
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_io_status transmit_byte(uint8_t data);
		 
		/**
		 * Performs a blocking transmission of a null terminated string via the configured USART connection.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.  Interrupts remain enabled.
		 *
		 * @param data		Pointer to data that is to be transmitted via the USART.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_io_status transmit_string(uint8_t *data);
		 
		/**
		 * Transmits an array of data of fixed length via the configured USART connection.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.  Interrupts remain enabled.
		 *
		 * @param data		Pointer to data that is to be transmitted via the USART.
 		 * @param num_elements	Number of elements within the array to transmit.
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_io_status transmit_array(uint8_t* data, size_t num_elements);
		 
		/**
		 * Transfers one byte via the configured USART connection, operating in SPI Master mode.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.  Interrupts remain enabled.
		 *
		 * NOTE - If the USART is not configured for SPI Master mode operation, the method returns zero.
		 *
		 * @param data		Byte to be transmitted via the USART
		 * @return Contents of receive buffer after SPI transfer i.e the byte read in the MISO/RX line.
		 */
		uint8_t spi_transfer_byte(uint8_t data);
		 
		/**
		 * Transfers an array via the configured USART connection, operating in SPI Master mode.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.  Interrupts remain enabled.
		 *
		 * NOTE - If the USART is not configured for SPI Master mode operation, the method does nothing.
		 *
		 * @param tx_data		Pointer to the array to be transmitted via the USART.
     	 * @param rx_data		Pointer to a place in memory where an array can be received via the USART.
		 * @param num_elements	Number of elements in the arrays (assumed to be the same).
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_io_status spi_transfer_array(uint8_t* tx_data, uint8_t* rx_data, size_t num_elements);
		 
		/**
		 * Transfers an array via the configured USART connection, operating in SPI Master mode, using DMA for non-blocking operation.
		 *
		 * NOTE - Just because this function returns success, doesn't mean the actual DMA transfer itself will then fail later on.
		 *
		 * @param tx_data		Pointer to the array that is to be transmitted.
		 * @param rx_data		Pointer to an array where data is to be received into.
		 * @param number_elements	Number of elements in the arrays (assumed to be the same).
		 * @return Zero for success, non-zero for failure.
		 */
		Usart_io_status spi_dma_transfer(uint8_t* tx_data, uint8_t* rx_data, size_t num_elements);
		 
		/**
		 * Indicates whether the transmission is complete, i.e no unsent data remains in the transmit buffer.
		 * 
		 * NOTE - The only time this function will return true is while a DMA transfer is in progress.
		 *
		 * @return True if the transfer is complete, false otherwise.
		 */
		bool transmission_complete(void);
		 
		/**
		 * Indicates whether the receive is complete, i.e unread data exists in the receive buffer.
		 *
		 * @return True if the receive is completed (i.e. there is no unread data), false otherwise.
		 */
		bool receive_complete(void);
		 
		/**
		 * Read the content of the USART receive buffer.
		 *
		 * @param Nothing.
		 * @return The received byte.
		 */
		uint8_t receive_byte(void);
		
		/**
		 * Receives an array of uint8_t values.
		 *
		 * NOTE - This method blocks while USART IO operations are performed.  Interrupts remain enabled.
		 *
		 * @param array		Pointer to the location in memory where the array can be returned to.
		 * @param elements	Number of elements to return.
		 * @return Nothing.
		 */
		void receive_array(uint8_t* array, size_t num_elements);
		
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
		Usart_int_status attach_interrupt(Usart_interrupt_type interrupt, void(*callback)(void));

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
