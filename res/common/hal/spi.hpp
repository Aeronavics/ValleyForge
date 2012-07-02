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

// Include the semaphore library
#include "semaphore.hpp"

// Include the hal library.
#include "hal/hal.hpp"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum spi_number {SPI_0};

enum spi_configuration {SPI_MASTER, SPI_SLAVE};

enum spi_bit_order {MSB_FIRST, LSB_FIRST};

enum spi_mode {SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3};

enum spi_clock_divider {SPI_DIV_2, SPI_DIV_4, SPI_DIV_8, SPI_DIV_16, SPI_DIV_32, SPI_DIV_64, SPI_DIV_128};

enum spi_interrupt_types {SPI_STC};

// FORWARD DEFINE PRIVATE PROTOTYPES.

class spi_imp;
class spi_slave_imp;

// DEFINE PUBLIC CLASSES.

/**
 * @class spi
 * 
 * Implements various functions relating to SPIinitialisation, transmission
 * and receiving of data.
 * 
 */
class spi
{
	public:
		// Functions.
		
		/**
		 * Initialises the SPI interface with the desired Master/Slave parameters and configures the
		 * relevant GPIO.
		 * 
		 * @param  configuration	Configuration for SPI interface (master/slave)
		 * @return 0 for success, -1 for error.
		 */
		int8_t initialise(spi_configuration configuration);
		
		/**
		 * Initialises the SPI interface with the desired data mode.
		 * Options relate to the combinations of clock polarity & phase
		 * settings.
		 * 
		 * @param  mode			SPI mode to apply to the interface
		 * @return 0 for success, -1 for error.
		 */		
		int8_t set_data_mode(spi_mode mode);
		
		/**
		 * Initialises the SPI interface with the desired bit order.
		 * Interface can either move the Most-Significant-Bit (MSB) first, or else
		 * the Least-Significant-Bit (LSB).
		 * 
		 * @param  order		Required data order (MSB first or LSB first)
		 * @return 0 for success, -1 for error.
		 */		
		int8_t set_bit_order(spi_bit_order order);
		
		/**
		 * Sets the clock divider to be used for the SPI interface.
		 *
		 * @param divider		A clock divider from one of the enumerated options.
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_clock_divider(spi_clock_divider divider);
		
		/**
		 * Enables an interrupt to be be associated with a SPI connection.
		 *
		 * @param interrupt		One of the possible interrupt types that are available.
		 * @param ISRptr		Pointer to the user-defined ISR.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t enable_interrupt(spi_interrupt_types interrupt, void (*ISRptr)(void));
		 
		/**
		 * Enables an interrupt to be be un-associated with a SPI connection.
		 *
		 * @param interrupt		Which interrupt to disable.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t disable_interrupt(spi_interrupt_types interrupt);
		 
		 /**
		 * Transfers a byte and receives a byte via the SPI connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param data		Byte to transfer via SPI.
		 * @return Byte received.
		 */
		 uint8_t transfer(uint8_t data);
		 
		 /**
		 * Transfers an array and receives an array of predetermined size via the SPI connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param TXdata		Pointer to the array that is to be transmitted.
		 * @param RXdata		Pointer to an array where data may be received to.
		 * @param numberElements	Number of elements in the arrays (assumed to be the same).
		 * @return Nothing.
		 */
		 void transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements);	
		 
		 /**
		 * Transfers a block of data and receives data via the SPI connection.
		 * Note, this function relies on using DMA or similar to achieve 'non-blocking' operation.
		 *
		 * @param TXdata		Pointer to the array that is to be transmitted.
		 * @param RXdata		Pointer to an array where data may be received to.
		 * @param numberElements	Number of elements in the arrays (assumed to be the same).
		 * @return Nothing.
		 */
		 void dma_transfer(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements);
		
		 /**
		 * Function to free the SPI instance when it goes out of scope.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~spi(void);

		 /** 
		 * Allows access to the SPI to be relinquished and reused elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 void disable(void);
		
		/**
		 * Allows a process to request access to a SPI instance and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  spiNumber	The number of a SPI that is desired.
		 * @return A SPI instance.
		 */
		static spi grab(spi_number spiNumber);

	private:
		// Functions.
		
		spi(void);	// Poisoned.

		spi(spi_imp*);

		spi operator =(spi const&);	// Poisoned.

		// Fields.

		/**
		* Pointer to the machine specific implementation of the SPI.
		*/
		spi_imp* imp;
};

/* 
 * Class to represent a slave SPI device attached to the target.
 */
class spi_slave 
{
	public:
		// Functions
		/**
		 * Function to select the associated SPI Slave device and transfer data to/from it.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 void enable(void);
		
		/**
		 * Function to deselect the associated SPI Slave device.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 void disable(void);

		/** 
		 * Allows access to the SPI Slave to be relinquished and reused elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request attachment of a SPI Slave and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  slaveAddress		The GPIO address of the slave select (SS') pin that is to be attached.
		 * @return A SPI slave instance.
		 */
		static spi_slave attach(gpio_pin_address slaveAddress);
		
		/**
		 * Function to free the SPI slave instance when it goes out of scope.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~spi_slave(void);
		
	private:
		// Functions.
		
		spi_slave(void);	// Poisoned.
		
		spi_slave(spi_slave_imp*);

		spi_slave operator =(spi_slave const&);	// Poisoned.

		// Fields.
		
		/**
		* Pointer to the machine specific implementation of the SPI Slave.
		*/
		spi_slave_imp* imp;
};
	  


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__SPI_H__*/

// ALL DONE.
