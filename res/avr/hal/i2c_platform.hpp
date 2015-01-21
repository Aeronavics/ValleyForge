// Copyright (C) 2013  Unison Networks Ltd
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
 * -----------------------------------------------------------------------------------------------------
 * @addtogroup		I2C Library
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @file		I2C_platform.hpp
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @brief 		Header file containing platform dependent types and enums for the I2C module.
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @author		Ben O'Brien
 *				Documentation based on AT90CAN128 data sheet Rev. 7679H–CAN–08/08, by ATMEL
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @date		1-12-2014
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @section 	Licence
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
 * -----------------------------------------------------------------------------------------------------
 * -----------------------------------------------------------------------------------------------------
 * @section 	Description
 *
 * [See BRIEF]
 * -----------------------------------------------------------------------------------------------------
 */


#ifndef __I2C_PLATFORM_H__
#define __I2C_PLATFORM_H__

// REQUIRED HEADER FILES.
#include <stdint.h>

#define BASE_AT90_SLA     0xA0
#define BASE_ATMEGA8_SLA     0xB0
#define ENERGY_AT90_SLA     0xC0

#define OWN_ADR     0xD0

#define READ     0
#define WRITE     1


/* ***************** Macros for AVR registers ********************** */
#ifdef __AVR_AT90CAN128__

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// TWO WIRE SERIAL INTERFACE (TWI) REGISTERS
	//(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
	//

	//---------------------------------------------------------------------------------------------------
	//	TWBR 0xB8	// TWI Bit Rate Register - sets the division factor for the bit rate generator
	//---------------------------------------------------------------------------------------------------
	// TWBR should be 10 or higher if TWI operates in master mode
	// CPU Clock Frequency in the slave must be at least 16 times higher than the SCL Frequency
	//***************************************************************************************************
	/*RW*/	#define TWBR7	7
	/*RW*/	#define TWBR6	6
	/*RW*/	#define TWBR5	5
	/*RW*/	#define TWBR4	4
	/*RW*/	#define TWBR3	3
	/*RW*/	#define TWBR2	2
	/*RW*/	#define TWBR1	1
	/*RW*/	#define TWBR0	0

	#define MIN_TWBR_MASTER_MODE 10
	//***************************************************************************************************
	//---------------------------------------------------------------------------------------------------
	//	TWCR 0xBC	// TWI Control Register - Controls the operation of the Two Wire Serial Interface
	//---------------------------------------------------------------------------------------------------
	//***************************************************************************************************
	/*RW*/	#define TWINT 	7		// TWI Interrupt Flag
	/*RW*/	#define TWEA 	6		// TWI Enable Acknowledge Bit
	/*RW*/	#define TWSTA 	5		// TWI START Condition Bit
	/*RW*/	#define TWSTO 	4		// TWI STOP Condition Bit
	/*R*/	#define TWWC 	3		// TWI Write Collision Flag
	/*RW*/	#define TWEN 	2		// TWI Enable Bit
	/*R*/	#define TW_RESERVED 1	// Reserved bit. Must be written zero when TWCR is written
	/*RW*/	#define TWIE 	0		// Interrupt enable bit for TWCR
	//***************************************************************************************************
	//---------------------------------------------------------------------------------------------------
	//	TWSR 0xB9	// TWI Status Register
	//---------------------------------------------------------------------------------------------------
	//***************************************************************************************************
	/*R*/	#define TWS7 	7		// Bits 7 to 3 represent the status of the TWI logic and
	/*R*/	#define TWS6 	6		// the Two-Wire Serial Bus.
	/*R*/	#define TWS5 	5		// "
	/*R*/	#define TWS4 	4		// "
	/*R*/	#define TWS3 	3		// "
	/*R*/	#define TWS_RESERVED 2	// Reserved bit. Always read as zero.
	/*RW*/	#define TWPS1 	1		// TWI Prescaler Bits
	/*RW*/	#define TWPSO 	0		// "

	//***************************************************************************************************
	//---------------------------------------------------------------------------------------------------
	//	TWDR 0xBB	// TWI Data Register - Transmit Mode: 	Contains the next byte to be transmitted.
					// 					 - Receive Mode: 	Contains the last byte receieved.
	//---------------------------------------------------------------------------------------------------
	//***************************************************************************************************
	/*RW*/	#define TWD7	7		// Bits 0 to 7 represent data in the register.
	/*RW*/	#define TWD6	6		// "
	/*RW*/	#define TWD5	5		// "
	/*RW*/	#define TWD4	4		// "
	/*RW*/	#define TWD3	3		// "
	/*RW*/	#define TWD2	2		// "
	/*RW*/	#define TWD1	1		// "
	/*RW*/	#define TWD0	0		// "
	//***************************************************************************************************
	//---------------------------------------------------------------------------------------------------
	//	TWAR 0xBA	// TWI (Slave) Address Register
	//---------------------------------------------------------------------------------------------------
	//***************************************************************************************************
	/*RW*/	#define TWA6 	7		// Bits 7 to 1 represent the slave address.
	/*RW*/	#define TWA5 	6		// "
	/*RW*/	#define TWA4 	5		// "
	/*RW*/	#define TWA3 	4		// "
	/*RW*/	#define TWA2 	3		// "
	/*RW*/	#define TWA1 	2		// "
	/*RW*/	#define TWA0 	1		// "
	/*RW*/	#define TWGCE 	0		// TWI General Call Recognition Enable Bit
	//***************************************************************************************************


#endif

// TODO: get addresses on the power management board

#endif /*__I2C_PLATFORM_H__*/

// ALL DONE.
