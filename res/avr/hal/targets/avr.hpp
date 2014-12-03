// Copyright (C) 2014  Unison Networks Ltd
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
 * @addtogroup		hal	Hardware Abstraction Library
 *
 * @file		atmega64c1.hpp
 * Provides common target configuration for all AVR chips
 *
 *
 * @author 		Jared Sanson
 *
 * @date		28/11/2014
 *
 * @section Licence
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
 * @brief
 * This contains device specific definitions for AVR architecture targets. Information such as timer size, interrupt specifications and so on are defined here.
 */

// Only include this header file once.
#ifndef __TARGET_AVR_H__
#define __TARGET_AVR_H__

/* Generic Types */
typedef int(*callback_t)(void);

/* Macros */

#define TOTAL_PINS	(NUM_PORTS * PINS_PER_PORT)

/* GPIO */

// GPIO pin modes.  AVR devices have an optional pull-up on inputs, with all outputs operating push-pull.
enum Gpio_mode {GPIO_INPUT_PU, GPIO_OUTPUT_PP, GPIO_INPUT_FL};

/* EEPROM */

// EEPROM address (width).
typedef uint16_t Eeprom_address;

/* USART */

// Generic bit addresses for register manipulation.
// NOTE - These are also defined in <avr/io.h>, but the naming varies slightly among chips

// UCSRnA Register.
#define RXC_BIT				7
#define TXC_BIT				6
#define UDRE_BIT			5
#define FE_BIT				4
#define DOR_BIT				3
#define UPE_BIT				2
#define U2X_BIT				1
#define MPCM_BIT			0

// UCSRnB Register.
#define RXCIE_BIT			7
#define TXCIE_BIT			6
#define UDRIE_BIT			5
#define RXEN_BIT			4
#define TXEN_BIT			3
#define UCSZ2_BIT			2
#define RXB8_BIT			1
#define TXB8_BIT			0

// UCSRnC Register.
#define UMSEL1_BIT			7  // Only relevant for chips that support SPI mode
#define UMSEL0_BIT			6
#define UPM1_BIT			5
#define UPM0_BIT			4
#define USBS_BIT			3
#define UCSZ1_BIT			2
#define UCSZ0_BIT			1
#define UCPOL_BIT			0

#define UMSEL_MASK (_BV(UMSEL1_BIT) | _BV(UMSEL0_BIT))

// UCSRnC Register (when in Master SPI Mode).
#define UDORD_BIT			2
#define UCPHA_BIT			1

enum Usart_interrupt_type
{
	USART_INT_TX_COMPLETE,	// The TX transmission is complete
	USART_INT_RX_COMPLETE, 	// A byte of data has been received
	USART_INT_TX_READY		// The TX is ready to send more data
};

/* SPI */

enum Spi_setup_mode {SPI_MASTER, SPI_SLAVE};

// Specifies polarity of Clock/Data signals
enum Spi_data_mode {SPI_MODE_0, SPI_MODE_1, SPI_MODE_2, SPI_MODE_3};

// Specifies bit ordering
enum Spi_bit_order {MSB_FIRST, LSB_FIRST};

// Specifies how many bits to send per frame
enum Spi_frame_format {SPI_8BIT, SPI_16BIT};

enum Spi_clock_divider {SPI_DIV_2, SPI_DIV_4, SPI_DIV_8, SPI_DIV_16, SPI_DIV_32, SPI_DIV_64, SPI_DIV_128};

enum Spi_interrupt_types {SPI_STC};

enum Spi_slave_select_mode {SPI_SOFTWARE_SS, SPI_HARDWARE_SS};


#endif /*__TARGET_AVR_H__*/

