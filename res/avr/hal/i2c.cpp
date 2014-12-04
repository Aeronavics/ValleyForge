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

/********************************************************************************************************************************
 *
 *  FILE: 			i2c.c
 *
 *  LIBRARY:		I2C
 *
 *  AUTHOR: 		Ben O'Brien, loosely based on Unison UAV CAN-bus code by Paul Davey & George Xian.
 * 					Documentation based on AT90CAN128 data sheet Rev. 7679H–CAN–08/08, by ATMEL
 *
 *  DATE CREATED:	1-12-2014
 *
 *	An I2C interface for the ATmega8 - 16AU and AT90CAN128. 
 * 
 * 	AT90CAN128 implementation is currently being implemented. No ATmega8 - 16AU support exists at this point.
 * 	TODO: ATmega8 - 16AU implementation
 *
 ********************************************************************************************************************************/
 
// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include "i2c_platform.hpp"

//---------------------------------------------------------------------------------------------------------
// Support Functions
//---------------------------------------------------------------------------------------------------------
void i2c_set_register(uint8_t address, uint8_t mask, uint8_t pin_config); //TODO - Fix addressing
// TODO: Reimplement bit setting functions referring to GPIO



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//I2C_imp Class Definition
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
 * Private, target specific implementation class for public I2C class.
 */
class I2C_imp
{
	public:
		void enable(void);
		void disable(void);
		I2C_return_status set_mode(I2C_mode_t new_mode);
		I2C_status_code_t get_status();
		I2C_return_status write(uint8_t write_value);
		I2C_return_status start(uint8_t address);
		I2C_return_status stop();
		void set_prescaler(I2C_prescaler_value_t new_pre_scaler);
		void set_bitrate_divider(uint8_t new_bitrate_divider);
		
		
		// TODO - Functions below 
		I2C_return_status read(uint8_t write_value); // Would this be better with an address specified as well?
		I2C_return_status repeat_start();
		
	private:
		I2C_mode_t mode;
		I2C_prescaler_value_t pre_scaler;
		uint8_t bitrate_divider;
};

// Declaring an instance of the I2c_imp class, to be used by instances of the I2C class
I2C_imp I2C_implementation;


void I2C_imp::enable(void)
{
	TWCR = ((1<<TWEN) | (1<<TWSTA));

//	i2c_set_bit(TWCR, TWEN, 1);	// Set the interrupt bit, TWIE, in the TWCR register to true
	//i2c_set_bit(TWCR, TWINT, 0);	// Set the interrupt bit, TWIE, in the TWCR register to true
}

// Sets the Clock Line (SCL) prescaler. 
// Valid inputs are TW_PRESCALER_1, TW_PRESCALER_4, TW_PRESCALER_16, TW_PRESCALER_64
void I2C_imp::set_prescaler(I2C_prescaler_value_t new_pre_scaler)
{
	pre_scaler = new_pre_scaler;
	TWSR = (TWSR | pre_scaler & 0x3) | (TWSR & 0xf8);
}

void I2C_imp::set_bitrate_divider(uint8_t new_bitrate_divider)
{
	bitrate_divider = 0xff & new_bitrate_divider;
	TWBR = bitrate_divider;
}

void I2C_imp::disable(void)
{
	i2c_set_bit(TWCR, TWEN, 0);	// Set the interrupt bit, TWIE, in the TWCR register to true
}

I2C_return_status I2C_imp::set_mode(I2C_mode_t new_mode, bool enable_general_call_recognition = false)
{
	// TODO - handle mode negotiation
	// Default to slave receiver
	
	if(new_mode & I2C_SLAVE)
	{
		// TODO - Replace 0x00 with variable that denotes the device's own slave address
		if(enable_general_call_recognition)
		{
			// Enables the general call address response
			TWAR = 0x00 | 0x01; 
		} else 
		{
			TWAR = 0x00 & ^0x01;
		}

		TWCR = (1 << TWEA) | (1 << TWEN);
		
		// Waits until addressed by its own slave address (or the general call address if enabled)
		while(!(TWCR & (1<< TWINT)))
		{
			continue;
		}
		
		
		// Check the data direction bit. If 0 (write) SR (Slave Reciever) mode is enabled.
		// If 1, ST (Slave Transmitter) mode is enabled.
		// Slave receiver or transmitter modes may also be entered if arbitration is lost while in the master mode
		
		// Status code is used to determine appropriate software action (see Table 18-5 and 18-6 in the 
	} 
	mode = new_mode;
	
	return (I2C_SUCCESS);
}

I2C_return_status I2C_imp::start(uint8_t address)
{
	// Set Relevant flags
	TWCR = I2C_COMMAND_START;
	
	//TODO: replace with interrupts in interrupt mode
	// Busy wait until TWINT is set
	while(!i2c_get_bit(TWCR, TWINT))
	{
		continue;
	}
	
	uint8_t status = get_status();
	// If the start send was succesful, proceed
	if(status == MT_START || status == MT_REPEATED_START)
	{
		return (I2C_SUCCESS);
	} else
	{
		return (I2C_ERROR);
	}
}


I2C_return_status I2C_imp::stop()
{
	if(mode == I2C_MASTER_TRANSMITTER)
	{
		TWCR = I2C_COMMAND_STOP;
	}
	return (I2C_SUCCESS);
}

//TWSR Bit Functions
I2C_status_code_t I2C_imp::get_status()
{
	//Returns the 5bit status value, found in the upper part of the status register
	return((I2C_status_code_t)(TWSR & 0xf8));
}


/* POSSIBLE TODO: Make the data sending queue based
 * 
 * */


I2C_return_status I2C_imp::write_MT(uint8_t write_value)
{
	// Sends a start condition
	if(start(0x00) == I2C_ERROR) 
	{
		return (I2C_ERROR);
	}
	
	TWDR = write_value;
	
	//Set relevant flags in the control register
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	//TODO: replace with interrupts in interrupt mode
	//Wait until TWINT is set
	while(!(TWCR & (1<< TWINT)))
	{
		continue;
	}
	
	// Error checking
	uint8_t ic2_status = get_status();
	if((ic2_status == MT_SLA_ACK) || (ic2_status == MT_DATA_ACK))
	{
		return (I2C_SUCCESS);
	} else
	{
		return (I2C_ERROR);
	}
}


// Sets up a stream on MR. MR should inform 
I2C_return_status I2C_imp::read_MR(uint8_t sla_r, uint8_t* read_bytes, uint8_t num_read_bytes_to_read)
{
	//ASSUMES MR
	//TODO: Account for scenarios where the user wants to change from MR to another state
	
	// Sends a start condition
	if(start(sla_r) == I2C_ERROR) // TODO: is sla_r correct???
	{
		return (I2C_ERROR);
	}
	
	//Entering MR mode by transmitting SLA+R
	TWDR = sla_r;
	
	//Clearing TWINT to continue the transfer
	TWCR = (1 << TWINT) | (1 << TWEN);
	
	//TODO: replace with interrupts in interrupt mode
	//Wait until TWINT is set
	while(!(TWCR & (1<< TWINT)))
	{
		continue;
	}
	
	uint8_t ic2_status = get_status();
	
	// If the transfer was succesful
	if(ic2_status == M_SLA_P_R_SENT_ACK)
	{
		return (I2C_SUCCESS);
	} else
	{
		return (I2C_ERROR);
	}
	
	uint8_t num_bytes_read = 0;
	
	for(uint8_t i = 0; i < num_read_bytes_to_read; i++(
	{
		while(!(TWCR & (1<< TWINT)))
		{
			continue;
		}
		*(read_bytes++) = TWDR;
	}
	TWCR &= ^(1 << TWSTA);
	//TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	
	//Writing a repeated start condition (could also be a stop condition if desired)
	if(start(sla_r) == I2C_ERROR) // TODO: is sla_r correct???
	{
		return (I2C_ERROR);
	}
	
	return (I2C_SUCCESS);
}





//---------------------------------------------------------------------------------------------------------
// I2C Class Implementation
//
// The purpose of this class is to separate the implentation of the I2C library from each instance of the
// class. This enables more efficient use of memory. It also ensures that the TWI hardware is accessed 
// through a single interface.
//---------------------------------------------------------------------------------------------------------
I2C::I2C(I2C_mode_t new_mode)
{
	implementation = &I2C_implementation;
	implementation->set_mode(new_mode);
	TWCR = 0;
	// All done.
	return;
}

// I2C Destructor
I2C::~I2C()
{
	// All done.
	return;
}

// SEE I2C_imp::enable();
void I2C::enable()
{
	implementation->enable();
}

// SEE I2C_imp::set_prescaler(I2C_prescaler_value_t new_pre_scaler);
void I2C::set_prescaler(I2C_prescaler_value_t new_pre_scaler)
{
	implementation->set_prescaler(new_pre_scaler);
}

// SEE I2C_imp::set_bitrate_divider(I2C_prescaler_value_t new_bitrate_divider);
// Sets the Clock Line (SCL) prescaler. 
// Valid inputs are TW_PRESCALER_1, TW_PRESCALER_4, TW_PRESCALER_16, TW_PRESCALER_64
void I2C::set_bitrate_divider(uint8_t new_bitrate_divider)
{
	implementation->set_bitrate_divider(new_bitrate_divider);
}

// SEE I2C_imp::disable();
void I2C::disable()
{
	implementation->disable();
}

// SEE I2C_imp::set_mode(I2C_mode_t new_mode);
I2C_return_status I2C::set_mode(I2C_mode_t new_mode)
{
	return (implementation->set_mode(new_mode));
}

// SEE I2C_imp::get_status();
I2C_return_status I2C::write(uint8_t write_value)
{
	return (implementation->write(write_value));
}

// SEE I2C_imp::get_status();
I2C_status_code_t I2C::get_status()
{
	return (implementation->get_status());
}


// SEE I2C_imp::start();
I2C_return_status I2C::start(uint8_t address)
{
	return (implementation->start(address));
}

// SEE I2C_imp::stop();
I2C_return_status I2C::stop()
{
	return (implementation->stop());
}
