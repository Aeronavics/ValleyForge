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

/********************************************************************************************************************************
 *
 *  FILE: 			i2c.cpp
 *
 *  LIBRARY:		I2C
 *
 *  AUTHOR: 		Sam Dirks
 *
 *
 *  DATE CREATED:	8-1-2016
 *
 * @section Description
 *
 * The AVR implementation for the I2C HAL library.
 *
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include <avr/io.h>
#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>
#include "i2c_platform.hpp"
#include <util/delay.h>

// DEFINE PRIVATE MACROS.

#define MINIMUM_MASTER_RECEIVE_LENGTH 1

// DEFINE PRIVATE TYPES AND STRUCTS.
volatile uint8_t i2c_buf_index;
volatile I2c_context i2c_context;
volatile uint8_t TWCR_tmp;
volatile bool tx_blocking_complete; 
volatile bool rx_blocking_complete; //used as a way of blocking the operation untill the expected data is received.
// The following status codes can be found in TWSR (the status register), depending on certain conditions. The condition required for each of these
// status codes to be displayed is summarised to the right of each definition.
enum I2c_status_code
{
	// Master-specific codes ---------------------------------------------------------------------------------------------------------------------------
	NO_INFO_TWINT_NOT_SET = 0xf8, // Meaning: The TWINT flag is not set, so no relevant information is available
	BUS_ERROR = 0x00,             // A bus error has occurred during a Two-wire Serial Bus transfer.
	                              // From the data sheet: a bus error occurs
	TWI_START = 0x08,             // A START condition has been transmitted
	TWI_REP_START = 0x10,         // A repeated START condition has been transmitted
	TWI_ARB_LOST = 0x38,          // Arbitration lost in SLA+W OR data bytes (master-transmitter)
	                              // OR Arbitration lost in SLA+R or NOT ACK bit (master-receiver)

	// Master Transmitter
	MT_SLA_ACK = 0x18,	// SLA+W has been transmitted. ACK has been received.
	MT_SLA_NAK = 0x20,	// SLA+W has been transmitted. NOT ACK has been received.
	MT_DATA_ACK = 0x28,	// Data byte has been transmitted. ACK has been received.
	MT_DATA_NAK = 0x30,	// Data byte has been transmitted. NOT ACK has been received.

	// Master Receiver
	MR_SLA_ACK = 0x40,	// SLA+R has been transmitted, ACK has been received
	MR_SLA_NAK = 0x48,	// SLA+R has been transmitted; NOT ACK has been received
	MR_DATA_ACK = 0x50,	// Data byte has been received; ACK has been returned
	MR_DATA_NAK = 0x58,	// Data byte has been received; NOT ACK has been returned

	// Slave-specific codes ---------------------------------------------------------------------------------------------------------------------------

	// Slave Receiver
	SR_SLA_ACK = 0x60,	    //  Own SLA+W has been received; ACK has been returned
	S_LOST_ARB_1 = 0x68,	//  Arbitration lost in SLA+R/W as master; own SLA+W has been received; ACK has been returned
	SR_GEN_ACK = 0x70,	    //  General call address has been received; ACK has been returned
	S_LOST_ARB_2 = 0x78,	//  Arbitration lost in SLA+R/W as master; General call address has been received; ACK has been returned
	SR_ADR_DATA_ACK = 0x80,	//  Previously addressed with own SLA+W; data has been received; ACK has been returned
	SR_ADR_DATA_NAK = 0x88,	//  Previously addressed with own SLA+W; data has been received; NOT ACK has been returned
	SR_GEN_DATA_ACK = 0x90,	//  Previously addressed with general call; data has been received; ACK has been returned
	SR_GEN_DATA_NAK = 0x98,	//  Previously addressed with general call; data has been received; NOT ACK has been returned
	SR_STOP_RESTART = 0xA0,	//  A STOP condition or repeated START condition has been received while still addressed as slave

	// Slave Transmitter
	ST_SLA_ACK = 0xA8,	         //  Own SLA+R has been received; ACK has been returned
	S_LOST_ARB_3 = 0xB0,         //  Arbitration lost in SLA+R/W as master; own SLA+R has been received; ACK has been returned
	ST_DATA_ACK = 0xB8,          //  Data byte in TWDR has been transmitted; ACK has been received
	ST_DATA_NAK = 0xC0,          //  Data byte in TWDR has been transmitted; NOT ACK has been received
	ST_DATA_ACK_LAST_BYTE = 0xC8 //  Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
};

enum I2c_master_operation
{
	I2C_MASTER_TRANSMIT,
	I2C_MASTER_RECEIVE,
	I2C_MASTER_TRANSMIT_RECEIVE
};

struct I2c_interface
{
	volatile bool slave_enabled;
	volatile I2c_mode current_mode;
	I2c_address own_addr;
	
	volatile bool master_active;
	volatile I2c_master_operation master_operation;
	volatile bool slave_active;
	
	volatile uint8_t mt_sla_w;
	volatile uint8_t mt_msg_size;
	volatile uint8_t my_buf[I2C_BUFFER_SIZE]; // I2C master transmitter data buffer.
	
	volatile uint8_t mr_sla_r;
	volatile uint8_t mr_msg_size;
	volatile uint8_t* mr_data_ptr;            // I2C master receiver saves the data straight to the user data array.
	
	volatile bool data_in_st_buf;
	volatile uint8_t st_msg_size;
	volatile uint8_t st_buf[I2C_BUFFER_SIZE]; // I2C slave transmitter buffer.
	
	volatile uint8_t sr_msg_size;
	volatile uint8_t sr_buf[I2C_BUFFER_SIZE]; // I2C slave receiver buffer.
	volatile bool sr_buf_read;
	
	volatile uint8_t sr_gc_msg_size;
	volatile uint8_t sr_gc_buf[I2C_BUFFER_SIZE]; // I2C slave receiver general call buffer.
	volatile bool sr_gc_buf_read;
	volatile bool sr_gc;
};

// DECLARE IMPORTED GLOBAL VARIABLES.

// DEFINE PRIVATE CLASSES.

/**
 * A Class that provides device specific implementation class for I2C.
 */
class I2c_imp
{
	public:

		// Methods.
		
		I2c_imp(I2c_number i2c_number);
		
		I2c_command_status initialise(I2c_clk_speed clk_speed, I2c_address slave_addr, Callback callback);
		
		I2c_command_status set_internal_pullup(I2c_pullup_state pullup_state);
		
		I2c_mode get_i2c_status(void);
		
		I2c_command_status enable_slave(void);
		
		I2c_command_status disable_slave(void);
		
		I2c_command_status set_general_call_mode(I2c_gc_mode gc_mode);

		I2c_command_status master_transmit(I2c_address slave_addr, uint8_t* data, uint8_t msg_size);
		I2c_command_status master_transmit_blocking(I2c_address slave_addr, uint8_t* data, uint8_t msg_size);
		
		I2c_command_status master_receive(I2c_address slave_addr, uint8_t* data, uint8_t msg_size);
		
		I2c_command_status master_transmit_receive(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size);
		I2c_command_status master_transmit_receive_blocking(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size);

		I2c_command_status slave_transmit(uint8_t* data, uint8_t msg_size);
		
		I2c_command_status slave_receive(uint8_t* data, uint8_t* msg_size);
		
		I2c_command_status slave_receive_general_call(uint8_t* data, uint8_t* msg_size);

	private:
	
		// Functions

		I2c_imp operator = (I2c_imp const&) = delete;
		
		// Fields
		
		Gpio_pin sda_pin;
		Gpio_pin scl_pin;
};

// DECLARE PRIVATE GLOBAL VARIABLES.

static I2c_interface i2c_interface; // One need one global instance of global interface information as there is only 1 I2C interface on target avr processors.

Callback i2c_callback; // The callback to allow I2C to notify the user program of events.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

I2c::I2c(I2c_imp* implementation)
{
  	// Attach the implementation to the instance.
  	imp = implementation;

  	// All done.
  	return;
}

I2c::I2c(I2c_number i2c_number)
{
	static I2c_imp i2c_imp(i2c_number);
    imp = &i2c_imp;
}

I2c::~I2c()
{
	return;
}

I2c_command_status I2c::initialise(I2c_clk_speed clk_speed, I2c_address slave_adr, Callback callback)
{
	return imp->initialise(clk_speed, slave_adr, callback);
}

I2c_command_status I2c::set_internal_pullup(I2c_pullup_state pullup_state)
{
	return imp->set_internal_pullup(pullup_state);
}

I2c_mode I2c::get_i2c_status(void)
{
	return imp->get_i2c_status();
}

I2c_command_status I2c::enable_slave(void)
{
	return imp->enable_slave();
}

I2c_command_status I2c::disable_slave(void)
{
	return imp->disable_slave();
}

I2c_command_status I2c::set_general_call_mode(I2c_gc_mode gc_mode)
{
	return imp->set_general_call_mode(gc_mode);
}

I2c_command_status I2c::master_transmit(I2c_address slave_addr, uint8_t* data, uint8_t msg_size)
{
	return imp->master_transmit(slave_addr, data, msg_size);
}
I2c_command_status I2c::master_transmit_blocking(I2c_address slave_addr, uint8_t* data, uint8_t msg_size)
{
	return imp->master_transmit_blocking(slave_addr, data, msg_size);
}

I2c_command_status I2c::master_receive(I2c_address slave_addr, uint8_t* data, uint8_t msg_size)
{
	return imp->master_receive(slave_addr, data, msg_size);
}

I2c_command_status I2c::master_transmit_receive(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size)
{
	return imp->master_transmit_receive(slave_addr, tx_data, tx_msg_size, rx_data, rx_msg_size);
}

I2c_command_status I2c::master_transmit_receive_blocking(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size)
{
	return imp->master_transmit_receive_blocking(slave_addr, tx_data, tx_msg_size, rx_data, rx_msg_size);
}

I2c_command_status I2c::slave_transmit(uint8_t* data, uint8_t msg_size)
{
	return imp->slave_transmit(data, msg_size);
}

I2c_command_status I2c::slave_receive(uint8_t* data, uint8_t* msg_size)
{
	return imp->slave_receive(data, msg_size);
}

I2c_command_status I2c::slave_receive_general_call(uint8_t* data, uint8_t* msg_size)
{
	return imp->slave_receive(data, msg_size);
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTION (METHODS).

I2c_imp::I2c_imp(I2c_number i2c_number) :
	sda_pin(IO_pin_address({I2C_SDA_PORT, I2C_SDA_PIN})),
	scl_pin(IO_pin_address({I2C_SCL_PORT, I2C_SCL_PIN}))
{
	
}

I2c_command_status I2c_imp::initialise(I2c_clk_speed clk_speed, I2c_address slave_addr, Callback callback)
{
	TWCR &= (~(1<<TWEN)); // Ensure interface is disabled before configuring
	
	// Set the clock rate
	if (F_CPU / ((uint32_t)clk_speed * (uint32_t)CLK_TO_HZ) <= MIN_SCL_CPU_RATIO)
	{
		return I2C_CMD_NAK; // CPU clock rate is too low for SCL frequency
	}
  	TWSR &= (~(1 << TWPS0) & ~(1 << TWPS1)); // prescaler value is always 0 (or prescale of 1)
	TWBR = (F_CPU / ((uint32_t)clk_speed * (uint32_t)CLK_TO_HZ) - 16) / 2; // Integer devision will ensure SCL <= F_CPU / 16

    TWDR = 0xFF; // Default content
	
	if (slave_addr.type != I2C_7BIT_ADDRESS)
	{
		return I2C_CMD_NAK; // AVR only supports 7 bit addresses
	}
    TWAR = (slave_addr.address.addr_7bit << 1);
    #ifndef __AVR_AT90CAN128__
	TWAMR = 0x00; // no address mask.
	#endif
	i2c_interface.own_addr = slave_addr;

	i2c_callback = callback;
	
	// Initialise the I2C pins
	sda_pin.set_mode(GPIO_INPUT_FL);
	scl_pin.set_mode(GPIO_INPUT_FL);
	
	i2c_interface.slave_enabled = false;
	i2c_interface.master_active = false;
	i2c_interface.slave_active = false;
	
	i2c_interface.data_in_st_buf = false;
	i2c_interface.sr_gc = false;
	i2c_interface.sr_buf_read = false;
	i2c_interface.sr_gc_buf_read = false;
	
	i2c_interface.current_mode = I2C_IDLE;
	
	// Set all message sizes to 0;
	i2c_interface.mt_msg_size = 0;
	i2c_interface.mr_msg_size = 0;
	i2c_interface.st_msg_size = 0;
	i2c_interface.sr_msg_size = 0;
	i2c_interface.sr_gc_msg_size = 0;
	
	
	TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT); // Enable I2C-interface and release I2C pins.
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::set_internal_pullup(I2c_pullup_state pullup_state)
{
	switch (pullup_state)
	{
		case I2C_PULLUP_ENABLED:
		{
			sda_pin.set_mode(GPIO_INPUT_PU);
			scl_pin.set_mode(GPIO_INPUT_PU);
			return I2C_CMD_ACK;
		}
		case I2C_PULLUP_DISABLED:
		{
			sda_pin.set_mode(GPIO_INPUT_FL);
			scl_pin.set_mode(GPIO_INPUT_FL);
			return I2C_CMD_ACK;
		}
		default:
		{
			return I2C_CMD_NAK;
		}
	}
	
	// We should never reach here
	return I2C_CMD_NAK;
}

I2c_mode I2c_imp::get_i2c_status(void)
{
	return i2c_interface.current_mode;
}

I2c_command_status I2c_imp::enable_slave(void)
{
	if (i2c_interface.slave_enabled == false)
	{
		// This has to be done atomically to prevent the I2C harware from leaving the idle state while changing TWCR.
		cli();
		if (i2c_interface.current_mode == I2C_IDLE)
		{
			if (i2c_interface.master_active)
			{
				// If the master is active and I2C is in idle mode it is waitng for a start condition so leave set.
				TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA) | (1<<TWSTA);
			}
			else
			{
				TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
			}
		}
		i2c_interface.slave_enabled = true;
		sei();
	}
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::disable_slave(void)
{
	if (i2c_interface.slave_enabled == true)
	{
		// This has to be done atomically to prevent the I2C harware from leaving the idle state while changing TWCR.
		cli();
		if (i2c_interface.current_mode == I2C_IDLE)
		{
			if (i2c_interface.master_active)
			{
				// If the master is active and I2C is in idle mode it is waitng for a start condition so leave set.
				TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWSTA);
			}
			else
			{
				TWCR = (1<<TWEN) | (1<<TWIE);
			}
		}
		i2c_interface.slave_enabled = false;
		sei();
	}
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::set_general_call_mode(I2c_gc_mode gc_mode)
{
	switch (gc_mode)
	{
		case I2C_GC_ENABLED:
		{
			TWAR |= (1<<TWGCE);
			return I2C_CMD_ACK;
		}
		case I2C_GC_DISABLED:
		{
			TWAR &= ~(1<<TWGCE);
			return I2C_CMD_ACK;
		}
		default:
		{
			return I2C_CMD_NAK;
		}
	}
	
	// We Should never reach here.
	return I2C_CMD_NAK;
}

I2c_command_status I2c_imp::master_transmit(I2c_address slave_addr, uint8_t* data, uint8_t msg_size)
{
	if (i2c_interface.master_active)
	{
		return I2C_CMD_BUSY; // Master is currently in use.
	}
	
	
	// Address must be 7bits
	if (slave_addr.type != I2C_7BIT_ADDRESS)
	{
		return I2C_CMD_NAK;
	}
	
	if (slave_addr.address.addr_7bit != i2c_interface.own_addr.address.addr_7bit)
	{
		i2c_interface.mt_sla_w = (slave_addr.address.addr_7bit << 1) | WRITE;
		
		i2c_interface.mt_msg_size = msg_size;
		
		for (uint8_t i = 0; i < msg_size; i++)
		{
			i2c_interface.my_buf[i] = *data;
			data++;
		}
	}
	else
	{
		return I2C_CMD_NAK;
	}
	
	// If the slave is active leave it to complete its operation, it will start the master operation there after.
	// Must be done atomically to prevent a state change while configuing the master to start at the next opportunity.
	cli();
	i2c_interface.master_active = true;
	i2c_interface.master_operation = I2C_MASTER_TRANSMIT;
	if (i2c_interface.slave_active == false)
	{
		if (i2c_interface.slave_enabled)
		{
			TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA) | (1<<TWSTA);
		}
		else
		{
			TWCR = (1<<TWEN) | (1<<TWIE) | (0<<TWEA) | (1<<TWSTA);
		}
	}
	sei();
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::master_transmit_blocking(I2c_address slave_addr, uint8_t* data, uint8_t msg_size){
	tx_blocking_complete = false;	
	I2c_command_status status;
	uint8_t i =0;
	do
	{
		status =  master_transmit(slave_addr, data, msg_size);
		i++;
		if(i > 100) //if it is still not free - just ignore it and return.
 			return I2C_CMD_BUSY;
		_delay_us(10);
	}
	while (I2C_CMD_BUSY == status);
	i =0;
	while(!tx_blocking_complete){
		i++;
		if(i > 100)
 			break;
		_delay_us(10);
		
	}
	return status;
}


I2c_command_status I2c_imp::master_receive(I2c_address slave_addr, uint8_t* data, uint8_t msg_size)
{
	if (i2c_interface.master_active)
	{
		return I2C_CMD_BUSY; // Master is currently in use.
	}
	
	
	// Address must be 7bits and minimum master receive message length is 1 due to hardware limitations.
	if (slave_addr.type != I2C_7BIT_ADDRESS || msg_size < MINIMUM_MASTER_RECEIVE_LENGTH)
	{
		return I2C_CMD_NAK;
	}
	
	if (slave_addr.address.addr_7bit != i2c_interface.own_addr.address.addr_7bit)
	{
		i2c_interface.mr_sla_r = (slave_addr.address.addr_7bit << 1) | READ;
		
		i2c_interface.mr_msg_size = msg_size;			
		
		i2c_interface.mr_data_ptr = data;
	}
	else
	{
		return I2C_CMD_NAK;
	}
	
	// If the slave is active leave it to complete its operation, it will start the master operation there after.
	// Must be done atomically to prevent a state change while configuing the master to start at the next opportunity.
	cli();
	i2c_interface.master_active = true;
	i2c_interface.master_operation = I2C_MASTER_RECEIVE;
	if (!i2c_interface.slave_active)
	{
		if (i2c_interface.slave_enabled)
		{
			TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA) | (1<<TWSTA);
		}
		else
		{
			TWCR = (1<<TWEN) | (1<<TWIE) | (0<<TWEA) | (1<<TWSTA);
		}
	}
	sei();
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::master_transmit_receive(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size)
{
	if (i2c_interface.master_active)
	{
		return I2C_CMD_BUSY; // Master is currently in use.
	}
	
	// Address must be 7bits and minimum master receive message length is 1.
	if (slave_addr.type != I2C_7BIT_ADDRESS || rx_msg_size < MINIMUM_MASTER_RECEIVE_LENGTH)
	{
		return I2C_CMD_NAK;
	}
	
	if (slave_addr.address.addr_7bit != i2c_interface.own_addr.address.addr_7bit)
	{
		i2c_interface.mt_sla_w = (slave_addr.address.addr_7bit << 1) | WRITE;
		
		i2c_interface.mt_msg_size = tx_msg_size;
		
		for (uint8_t i = 0; i < tx_msg_size; i++)
		{
			i2c_interface.my_buf[i] = *tx_data;
			tx_data++;
		}
		
		i2c_interface.mr_sla_r = (slave_addr.address.addr_7bit << 1) | READ;
		
		i2c_interface.mr_msg_size = rx_msg_size;
		
		i2c_interface.mr_data_ptr = rx_data;
	}
	else
	{
		return I2C_CMD_NAK;
	}
	
	// If the slave is active leave it to complete its operation, it will start the master operation there after.
	// Must be done atomically to prevent a state change while configuing the master to start at the next opportunity.
	cli();
	i2c_interface.master_active = true;
	i2c_interface.master_operation = I2C_MASTER_TRANSMIT_RECEIVE;
	if (!i2c_interface.slave_active)
	{
		if (i2c_interface.slave_enabled)
		{
			TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA) | (1<<TWSTA);
		}
		else
		{
			TWCR = (1<<TWEN) | (1<<TWIE) | (0<<TWEA) | (1<<TWSTA);
		}
	}
	sei();
	
	return I2C_CMD_ACK;
}
I2c_command_status I2c_imp::master_transmit_receive_blocking(I2c_address slave_addr, uint8_t* tx_data, uint8_t tx_msg_size, uint8_t* rx_data, uint8_t rx_msg_size)
{
	rx_blocking_complete = false;
	I2c_command_status t;
	uint32_t i = 0;
	do{
		t = master_transmit_receive(slave_addr, tx_data, tx_msg_size, rx_data, rx_msg_size);
		i++;
		if(i > 100) //if it is still not free - just ignore it and return.
 			return I2C_CMD_BUSY;
		_delay_us(10);
	}
	while(t == I2C_CMD_BUSY);//wait for the line to be free, then transmit
	//wait for the received bits to be, well, received todo: add error states in here too
	i = 0;
	while(!rx_blocking_complete){
		i++;
		if(i > 100)
 			break;
		_delay_us(10);
	}

	return t;
	
}
I2c_command_status I2c_imp::slave_transmit(uint8_t* data, uint8_t msg_size)
{
	// Prevent data from being transmit while the buffer is being changed
	cli();
	if (i2c_interface.current_mode == I2C_SLAVE_TRANSMITTING)
	{
		sei();
		return I2C_CMD_BUSY;
	}
	i2c_interface.data_in_st_buf = false;
	sei();
	
	
	i2c_interface.st_msg_size = msg_size;
	
	for (int i = 0; i < msg_size; i++)
	{
		i2c_interface.st_buf[i] = *data;
		data++;
	}
	
	i2c_interface.data_in_st_buf = true;
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::slave_receive(uint8_t* data, uint8_t* msg_size)
{
	// Prevent data from being received while the buffer is being read. This causes the slave to NAK all incomming data bytes.
	cli();
	if (i2c_interface.current_mode == I2C_SLAVE_RECEIVING)
	{
		sei();
		return I2C_CMD_BUSY;
	}
	i2c_interface.sr_buf_read = true;
	sei();
	
	*msg_size = i2c_interface.sr_msg_size;
	for (int i = 0; i < i2c_interface.sr_msg_size; i++)
	{
		*data = i2c_interface.sr_buf[i];
		data++;
	}
	
	i2c_interface.sr_msg_size = 0;
	i2c_interface.sr_buf_read = false;
	
	return I2C_CMD_ACK;
}

I2c_command_status I2c_imp::slave_receive_general_call(uint8_t* data, uint8_t* msg_size)
{
	// Prevent data from being received while the buffer is being read. This causes the slave to NAK all incomming data bytes.
	cli();
	if (i2c_interface.current_mode == I2C_SLAVE_RECEIVING_GC)
	{
		sei();
		return I2C_CMD_BUSY;
	}
	i2c_interface.sr_gc_buf_read = true;
	sei();
	
	*msg_size = i2c_interface.sr_gc_msg_size;
	for (int i = 0; i < i2c_interface.sr_gc_msg_size; i++)
	{
		*data = i2c_interface.sr_gc_buf[i];
		data++;
	}
	
	i2c_interface.sr_gc_msg_size = 0;
	i2c_interface.sr_gc_buf_read = false;
	
	return I2C_CMD_ACK;
}

//
/////////////////////////////  Interrupt Vectors  /////////////////////////////



ISR(TWI_vect)
{
	//test_pin_1.write(GPIO_O_TOGGLE);
	switch (TWSR)
	{
		/////////////////////// General TWI statuses ///////////////////////
		case NO_INFO_TWINT_NOT_SET:
		{
			// No action required.
			break;
		}
		case BUS_ERROR:
		{
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_BUS_ERROR;
			i2c_interface.master_active = false;
			i2c_interface.slave_active = false;
			i2c_callback((void*)&i2c_context);
			
			// Release the bus and set slave mode.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWSTO);
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			tx_blocking_complete = true;
			rx_blocking_complete = true;
			break;
		}
		case TWI_START:
		{
			i2c_buf_index = 0;

			if (i2c_interface.master_operation == I2C_MASTER_TRANSMIT || i2c_interface.master_operation == I2C_MASTER_TRANSMIT_RECEIVE)
			{
				TWDR = i2c_interface.mt_sla_w;
				if (i2c_interface.slave_enabled)
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA);
				}
				else
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT);
				}
				i2c_interface.current_mode = I2C_MASTER_TRANSMITTING;
			}
			else
			{
				TWDR = i2c_interface.mr_sla_r;
				if (i2c_interface.slave_enabled)
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA);
				}
				else
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT);
				}
				i2c_interface.current_mode = I2C_MASTER_RECEIVING;
			}
			break;
		}
		case TWI_REP_START:
		{
			i2c_buf_index = 0;

			// NOTE - ordinarially a master transmit receive operation would not start here however it can occur when started immediately after concluding a master operation before the stop is sent.
			if (i2c_interface.master_operation == I2C_MASTER_TRANSMIT || i2c_interface.master_operation == I2C_MASTER_TRANSMIT_RECEIVE)
			{
				TWDR = i2c_interface.mt_sla_w;
				if (i2c_interface.slave_enabled)
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA);
				}
				else
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT);
				}
				i2c_interface.current_mode = I2C_MASTER_TRANSMITTING;
			}
			else
			{
				TWDR = i2c_interface.mr_sla_r;
				if (i2c_interface.slave_enabled)
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA);
				}
				else
				{
					TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWINT);
				}
				i2c_interface.current_mode = I2C_MASTER_RECEIVING;
			}
			
			break;
		}
		case TWI_ARB_LOST:
		{
			i2c_interface.current_mode = I2C_IDLE;
			i2c_interface.master_active = false;
			i2c_context.event = I2C_ARB_LOST;
			i2c_callback((void*)&i2c_context);
			
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWSTO);
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			tx_blocking_complete = true;
			rx_blocking_complete = true;
			break;
		}
		/////////////////////// Master Transmitter statuses ///////////////////////
		case MT_SLA_ACK:
		{
			if (i2c_interface.mt_msg_size == 0)
			{
				// Stop after SLA ACK if 0 bytes are to be written, this is for SMBus support.
				i2c_interface.current_mode = I2C_IDLE;
				i2c_context.event = I2C_MASTER_TX_COMPLETE;
				i2c_callback((void*)&i2c_context);
				i2c_interface.master_active = false;
				
				TWCR_tmp = (1<<TWEN) | (1<<TWIE);
				if (i2c_interface.slave_enabled)
				{
					TWCR_tmp |= (1<<TWEA);
				}
				else
				{
					TWCR_tmp &= ~(1<<TWEA);
				}
				TWCR_tmp |= (1<<TWSTO);
				TWCR_tmp |= (1<<TWINT);
				TWCR = TWCR_tmp;
				tx_blocking_complete = true;
			}
			else
			{
				TWDR = i2c_interface.my_buf[i2c_buf_index++];
				TWCR = TWCR_DATA_ACK;				
			}
			break;
		}
		case MT_SLA_NAK:
		{
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_MASTER_TX_SLA_NAK;
			i2c_callback((void*)&i2c_context);
			i2c_interface.master_active = false;
			
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWSTO);
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			tx_blocking_complete = true;
			break;
		}
		case MT_DATA_ACK:
		{
			if (i2c_buf_index < (i2c_interface.mt_msg_size))
			{
				TWDR = i2c_interface.my_buf[i2c_buf_index++];
				TWCR = TWCR_DATA_ACK;
			}
			else
			{
				if (i2c_interface.master_operation == I2C_MASTER_TRANSMIT_RECEIVE)
				{
					i2c_interface.master_operation = I2C_MASTER_RECEIVE;
					
					TWCR = TWCR_START;
				}
				else
				{					
					i2c_interface.current_mode = I2C_IDLE;
					i2c_context.event = I2C_MASTER_TX_COMPLETE;
					i2c_callback((void*)&i2c_context);
					i2c_interface.master_active = false;
					
					TWCR_tmp = (1<<TWEN) | (1<<TWIE);
					if (i2c_interface.slave_enabled)
					{
						TWCR_tmp |= (1<<TWEA);
					}
					else
					{
						TWCR_tmp &= ~(1<<TWEA);
					}
					TWCR_tmp |= (1<<TWSTO);
					TWCR_tmp |= (1<<TWINT);
					TWCR = TWCR_tmp;
					tx_blocking_complete = true;
				}
			}
			break;
		}
		case MT_DATA_NAK:
		{
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_MASTER_TX_DATA_NAK;
			i2c_context.context = (void*)&i2c_buf_index;
			i2c_callback((void*)&i2c_context);
			i2c_interface.master_active = false;
			
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWSTO);
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			tx_blocking_complete = true;
			break;
		}
		/////////////////////// Master Receiver statuses ///////////////////////
		case MR_SLA_ACK:
		{
			// NOTE - Due to harware limitations it is not possible to make a 0 byte read.
			switch (i2c_interface.mr_msg_size)
			{
				case 1: //WHY WAS THIS 1?!~?!?!
				{
					TWCR = TWCR_DATA_NAK;
					break;
				}
				default:
				{
					TWCR = TWCR_DATA_ACK;
					break;
				}
			}
			break;
		}
		case MR_SLA_NAK:
		{
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_MASTER_RX_SLA_NAK;
			i2c_callback((void*)&i2c_context);
			
			i2c_interface.master_active = false;
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWSTO);
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			rx_blocking_complete = true;
			break;
		}
		case MR_DATA_ACK:
		{
			if (i2c_buf_index < (i2c_interface.mr_msg_size - 2)) // Have to pre-emptively know that the next byte will be the last
			{
				*i2c_interface.mr_data_ptr = TWDR;
				i2c_interface.mr_data_ptr++;
				i2c_buf_index++;
				TWCR = TWCR_DATA_ACK;
			}
			else                                           // Last byte is saved with TWEA Not set.
			{
				*i2c_interface.mr_data_ptr = TWDR;
				i2c_interface.mr_data_ptr++;
				i2c_buf_index++;
				TWCR = TWCR_DATA_NAK;
			}
			break;
		}
		case MR_DATA_NAK:
		{
			*i2c_interface.mr_data_ptr = TWDR;
			
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_MASTER_RX_COMPLETE;
			i2c_callback((void*)&i2c_context);
			i2c_interface.master_active = false;
			
			// Confirmation that the last byte has been transmitted.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWSTO);
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			rx_blocking_complete = true;
			break;
		}
		/////////////////////// Slave Receiver ///////////////////////
		case SR_SLA_ACK:
		{
			// Addressed as slave start receiving data.
			i2c_buf_index = 0;
			i2c_interface.slave_active = true;
			i2c_interface.sr_gc = false;
			if (i2c_interface.sr_buf_read)
			{
				TWCR = TWCR_DATA_NAK;
			}
			else
			{
				TWCR = TWCR_DATA_ACK;
			}
			i2c_interface.current_mode = I2C_SLAVE_RECEIVING;
			break;
		}
		case S_LOST_ARB_1:
		{
			i2c_context.event = I2C_ARB_LOST;
			i2c_callback((void*)&i2c_context);
			
			// Addressed as slave start receiving data.
			i2c_buf_index = 0;
			i2c_interface.slave_active = true;
			i2c_interface.sr_gc = false;
			if (i2c_interface.sr_buf_read)
			{
				TWCR = TWCR_DATA_NAK;
			}
			else
			{
				TWCR = TWCR_DATA_ACK;
			}
			i2c_interface.current_mode = I2C_SLAVE_RECEIVING;
			break;
		}
		case SR_GEN_ACK:
		{
			// Addressed as slave general call start receiving data.
			i2c_buf_index = 0;
			i2c_interface.slave_active = true;
			i2c_interface.sr_gc = true;
			if (i2c_interface.sr_gc_buf_read)
			{
				TWCR = TWCR_DATA_NAK;
			}
			else
			{
				TWCR = TWCR_DATA_ACK;
			}
			i2c_interface.current_mode = I2C_SLAVE_RECEIVING_GC;
			break;
		}
		case S_LOST_ARB_2:
		{
			i2c_context.event = I2C_ARB_LOST;
			i2c_callback((void*)&i2c_context);
			
			// Addressed as slave general call start receiving data.
			i2c_buf_index = 0;
			i2c_interface.slave_active = true;
			i2c_interface.sr_gc = true;
			if (i2c_interface.sr_gc_buf_read)
			{
				TWCR = TWCR_DATA_NAK;
			}
			else
			{
				TWCR = TWCR_DATA_ACK;
			}
			i2c_interface.current_mode = I2C_SLAVE_RECEIVING_GC;
			break;
		}
		case SR_ADR_DATA_ACK:
		{
			// Nack on filling the buffer or buffer is being read.
			if (i2c_buf_index >= I2C_BUFFER_SIZE - 2) // Must preemtively know the next byte is the last to fit in the buffer.
			{
				i2c_interface.sr_buf[i2c_buf_index++] = TWDR;
				i2c_interface.sr_msg_size++;
				TWCR = TWCR_DATA_NAK;
			}
			else
			{
				// Receive next byte
				i2c_interface.sr_buf[i2c_buf_index++] = TWDR;
				i2c_interface.sr_msg_size++;
				TWCR = TWCR_DATA_ACK;
			}
			break;
		}
		case SR_ADR_DATA_NAK:
		{
			i2c_interface.sr_buf[i2c_buf_index] = TWDR;
			i2c_interface.sr_msg_size;
			
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_SLAVE_RX_BUF_FULL;
			i2c_interface.slave_active = false;
			i2c_context.context = (void*)&i2c_buf_index;
			i2c_callback((void*)&i2c_context);
			
			// Receive buffer has overflowed or buffer is being read.
			// Start master operation if pending and set slave mode.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.master_active)
			{
				TWCR_tmp |= (1<<TWSTA);
			}
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			break;
		}
		case SR_GEN_DATA_ACK:
		{
			// Nack on filling the buffer or buffer is being read.
			if (i2c_buf_index >= I2C_BUFFER_SIZE - 2) // Must preemtively know the next byte is the last to fit in the buffer.
			{
				i2c_interface.sr_gc_buf[i2c_buf_index++] = TWDR;
				i2c_interface.sr_gc_msg_size++;
				TWCR = TWCR_DATA_NAK;
			}
			else
			{
				// Receive next byte
				i2c_interface.sr_gc_buf[i2c_buf_index++] = TWDR;
				i2c_interface.sr_gc_msg_size++;
				TWCR = TWCR_DATA_ACK;
			}
			break;
		}
		case SR_GEN_DATA_NAK:
		{
			i2c_interface.sr_gc_buf[i2c_buf_index++] = TWDR;
			i2c_interface.sr_gc_msg_size++;
			
			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_SLAVE_RX_GC_BUF_FULL;
			i2c_interface.slave_active = false;
			i2c_context.context = (void*)&i2c_buf_index;
			i2c_callback((void*)&i2c_context);
			
			// Receive buffer has overflowed or buffer is being read.
			// Start master operation if pending and set slave mode.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.master_active)
			{
				TWCR_tmp |= (1<<TWSTA);
			}
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			tx_blocking_complete = true;
			rx_blocking_complete = true;
			break;
		}
		case SR_STOP_RESTART:
		{
			i2c_interface.current_mode = I2C_IDLE;
			if (i2c_interface.sr_gc == true)
			{
				i2c_context.event = I2C_SLAVE_RC_GC_COMPLETE;
			}
			else
			{
				i2c_context.event = I2C_SLAVE_RX_COMPLETE;
			}
			i2c_interface.slave_active = false;
			i2c_context.context = (void*)&i2c_buf_index;
			i2c_callback((void*)&i2c_context);
			
			// Master concluded with a stop or repeated start.
			// Start master operation if pending and set slave mode.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.master_active)
			{
				TWCR_tmp |= (1<<TWSTA);
			}
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			tx_blocking_complete = true;
			rx_blocking_complete = true;
			break;
		}
		/////////////////////// Slave Transmitter ///////////////////////
		case ST_SLA_ACK:
		{
			// Addressed as slave to transmit bytes
			i2c_buf_index = 0;

			if (i2c_interface.data_in_st_buf == true)
			{
				if (i2c_interface.st_msg_size > 1)     // Pre-emtively know the next byte is the last
				{
					TWDR = i2c_interface.st_buf[i2c_buf_index++];

					TWCR = TWCR_DATA_ACK;
				}
				else
				{
					TWDR = i2c_interface.st_buf[i2c_buf_index];

					TWCR = TWCR_DATA_NAK;
				}
			}
			else
			{
				TWDR = 0xFF; // Send no data if st buf is empty

				TWCR = TWCR_DATA_NAK;
			}
			
			i2c_interface.current_mode = I2C_SLAVE_TRANSMITTING;
			break;
		}
		case S_LOST_ARB_3:
		{
			i2c_context.event = I2C_ARB_LOST;
			i2c_callback((void*)&i2c_context);
			
			// Addressed as slave to transmit bytes
			i2c_buf_index = 0;

			if (i2c_interface.data_in_st_buf == true)
			{
				if (i2c_buf_index < (i2c_interface.st_msg_size - 1))     // Pre-emtively know the next byte is the last
				{
					TWDR = i2c_interface.st_buf[i2c_buf_index++];

					TWCR = TWCR_DATA_ACK;
				}
				else
				{
					TWDR = i2c_interface.st_buf[i2c_buf_index];

					TWCR = TWCR_DATA_NAK;
				}
			}
			else
			{
				TWDR = 0xFF; // Send no data if st buf is empty

				TWCR = TWCR_DATA_NAK;
			}
			
			i2c_interface.current_mode = I2C_SLAVE_TRANSMITTING;
			break;
		}
		case ST_DATA_ACK:
		{
			if (i2c_buf_index < (i2c_interface.st_msg_size - 1))     // Pre-emtively know the next byte is the last
			{
				TWDR = i2c_interface.st_buf[i2c_buf_index++];

				TWCR = TWCR_DATA_ACK;
			}
			else
			{
				TWDR = i2c_interface.st_buf[i2c_buf_index];

				TWCR = TWCR_DATA_NAK;
			}
			break;
		}
		case ST_DATA_NAK:
		{
			i2c_interface.data_in_st_buf = false;

			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_SLAVE_TX_COMPLETE;
			i2c_interface.slave_active = false;
			i2c_callback((void*)&i2c_context);
			
			// Master concluded with a NAK.
			// Start master operation if pending and set slave mode.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.master_active)
			{
				TWCR_tmp |= (1<<TWSTA);
			}
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			break;
		}
		case ST_DATA_ACK_LAST_BYTE:
		{
			i2c_interface.data_in_st_buf = false;

			i2c_interface.current_mode = I2C_IDLE;
			i2c_context.event = I2C_SLAVE_TX_COMPLETE_OVR;
			i2c_interface.slave_active = false;
			i2c_callback((void*)&i2c_context);
			
			// Laste byte transmitted master acked. Master is asking for more bytes than slave is able to transmit.
			// Start master operation if pending and set slave mode.
			TWCR_tmp = (1<<TWEN) | (1<<TWIE);
			if (i2c_interface.master_active)
			{
				TWCR_tmp |= (1<<TWSTA);
			}
			if (i2c_interface.slave_enabled)
			{
				TWCR_tmp |= (1<<TWEA);
			}
			else
			{
				TWCR_tmp &= ~(1<<TWEA);
			}
			TWCR_tmp |= (1<<TWINT);
			TWCR = TWCR_tmp;
			break;
		}
		default :
		{
			break;
		}
	}
}
