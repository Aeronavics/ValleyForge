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

/* SPI */

// Configuration stuff specific to the AVR family of chips

enum Spi_frame_format
{
	SPI_MSB_FIRST,
	SPI_LSB_FIRST,
};

enum Spi_clock_divider
{
	// SPI2X, SPR1, SPR0
	SPI_DIV_2 = 0b100,
	SPI_DIV_4 = 0b000,
	SPI_DIV_8 = 0b101,
	SPI_DIV_16 = 0b001,
	SPI_DIV_32 = 0b110,
	SPI_DIV_64 = 0b111,
	SPI_DIV_128 = 0b011
};


/* AVR Bit Twiddling */
// For best performance only constants should be used for value/bit/bitwidth parameters.
// NOTE: These will usually compile down to efficient instructions, even if they look complex!

// Create a bitmask for the given number of bits
// eg. _bitmask(3) -> 0b00000111
#define _bitmask(bitwidth) ((1<<(bitwidth))-1)

// Set a single bit (Set to 1)
// bit_set(PORTB, 2)
// Equivalent to bit_write(reg, bit, 1)
#define bit_set(reg, bit) ((reg) |= (1<<(bit)))

// Clear a single bit (Set to 0)
// bit_clear(PORTB, 2)
// Equivalent to bit_write(reg, bit, 0)
#define bit_clear(reg, bit) ((reg) &= ~(1<<(bit)))

// Toggle a single bit
// bit_toggle(PORTB, 2)
#define bit_toggle(reg, bit) ((reg) ^= (1<<(bit)))

// Write a single bit
// bit_write(PORTB, 2, my_bool)
#define bit_write(reg, bit, value) ((reg) = ( (reg) & ~(1<<(bit)) ) | (((value)&1)<<(bit)))

// Read the state of a single bit
// if (bit_read(PORTB, 2)) { ... }
#define bit_read(reg, bit) (((reg) & (1<<(bit))) >> (bit))

/**
 * Write a set of bits to a register/variable
 * Usage:
 * 	reg_write(UCSRC, UMSEL0_BIT, 2, 0b01);
 * Expands to:
 * 	UCSRC = (UCSRC & ~(0b11 << UMSEL0_BIT)) | ((0b01 & 0b11) << UMSEL0_BIT)
 * Equivalent to:
 *  UCSRC = (UCSRC & 0b00111111) | 0b01000000
 */
#define reg_write(reg, lsb, bitwidth, value) ( (reg) = ( (reg) & ~(_bitmask(bitwidth)<<(lsb)) ) | ( (((value)&_bitmask(bitwidth))<<(lsb)) ))

/**
 * Read a set of bits from a register/variable
 * Usage:
 * 	uint8_t value = reg_read(UCSRC, UMSEL0_BIT, 2)
 * Expands to:
 * 	uint8_t value = (UCSRC >> UMSEL0_BIT) & 0b11;
 */
#define reg_read(reg, lsb, bitwidth) ( ((reg) >> (lsb)) & _bitmask(bitwidth) )

#endif /*__TARGET_AVR_H__*/


