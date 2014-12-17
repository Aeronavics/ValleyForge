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
 *  @file
 *  Provides useful bit-manipulation routines for accessing and modifying variables.
 *  Usually the macros will compile down into someting efficient.
 *
 *  @author		Jared Sanson
 *
 *  @date		17-12-2014
 *
 *  @section Licence
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
 */

#ifndef __BITTWIDDLING_H__
#define __BITTWIDDLING_H__

/* Bit Twiddling */
// For best performance only constants should be used for value/bit/bitwidth parameters.

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


#endif // __BITTWIDDLING_H__
