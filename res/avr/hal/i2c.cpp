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
 *	Description here.
 *
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES

#include "i2c_platform.hpp"

#include <avr/io.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE IMPORTED GLOBAL VARIABLES.

// DEFINE PRIVATE CLASSES.


/**
 * A Class that provides device specific implementation class for I2C.
 */
class I2C_imp
{
	public:

 		// Methods.

		void enable(void);

		void disable(void);

 		I2C_return_status initialise(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed);

		I2C_return_status start();

		I2C_return_status stop();

 		I2C_return_status transmit(tx_type *data);

 		I2C_return_status receive(tx_type *data);

 		I2C_status_code transceiver_busy();

	private:

    		// Functions

    		// I2C_imp(void) = delete;

    		// I2C_imp(I2C_imp*) = delete;

    		I2C_imp operator = (I2C_imp const&) = delete;

    		// Fields

		I2C_mode mode;

};

// DECLARE PRIVATE GLOBAL VARIABLES.

I2C_imp i2c_imp;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

I2C::I2C(I2C_imp* implementation)
{
  	// Attach the implementation to the instance.
  	imp = implementation;

  	// All done.
  	return;
}

I2C::I2C()
{
	// Attach the implementation.
	imp = &i2c_imp;

	// All done.
	return;
}

I2C::~I2C()
{
	return;
}

void I2C::enable(void)
{
  	return (imp->enable());
}

void I2C::disable(void)
{
 	return (imp->disable());
}

I2C_return_status I2C::initialise(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed)
{
  	return (imp->initialise(cpu_speed, scl_speed));
}

I2C_return_status I2C::start()
{
  	return (imp->start());
}

I2C_return_status I2C::stop()
{
  	return (imp->stop());
}

I2C_return_status I2C::transmit(tx_type *data)
{
  	return (imp->transmit(data));
}

I2C_return_status I2C::receive(tx_type *data)
{
  	return (imp->receive(data));
}

I2C_status_code I2C::transceiver_busy()
{
  	return (imp->transceiver_busy());
}

/****************************************************************************/
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void wait_twi_int(void)
{
  while (!(TWCR & (1 << TWINT)))
    ;
}

// IMPLEMENT PRIVATE CLASS FUNCTION (METHODS).

/**
 * I2C_imp private class functions
 **/

void I2C_imp::enable()
{
  	// TODO - this

   	TWCR = (1<<TWEN)|        // Enable TWI-interface and release TWI pins.
        	(0<<TWIE)|(0<<TWINT)|        // Disable Interupt.
         	(0<<TWEA)|(0<<TWSTA)|(0<<TWSTO);        // No Signal requests.

  	return;
}

void I2C_imp::disable(void)
{
  	// TODO - this

  	TWCR = (0<<TWEN)|(0<<TWIE)|(0<<TWINT);        // Disable TWI-interface and release TWI pins.

  	return;
}

I2C_return_status I2C_imp::initialise(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed)
{
  	// TODO - This
  	TWSR &= (~(1 << TWPS0) & ~(1 << TWPS1));         // prescaler value is always 0 (or prescale 1)

  	if (cpu_speed / scl_speed <16)
  	{
    		return I2C_ERROR;
  	}

  	switch (cpu_speed)
  	{
    		case CPU_1MHz:
    		{
      			switch (scl_speed)
      			{
        			case I2C_10kHz:
        			{
          				TWBR = 0x0B;
          				return I2C_SUCCESS;
        			}
        			case I2C_100kHz:
        			{
          				break;   // Not available at this CPU speed
        			}
        			case I2C_400kHz:
        			{
          				break;   // Not available at this CPU speed
        			}
        			default:
        			{
          				break;
        			}
      			}
      			return I2C_ERROR;
    		}		
    		case CPU_8MHz:
    		{
      			switch (scl_speed)
      			{
        			case I2C_10kHz:
        			{
          				TWBR = 0x62;
          				return I2C_SUCCESS;
        			}
        			case I2C_100kHz:
        			{
          				TWBR = 0x08;
          				return I2C_SUCCESS;
        			}
        			case I2C_400kHz:
        			{
          				break;   // Not available at this CPU speed
        			}
        			default:
        			{
          				break;
        			}
      			}
      			return I2C_ERROR;
    		}
    		case CPU_16MHz:
    		{
      			switch (scl_speed)
      			{
        			case I2C_10kHz:
        			{
          				TWBR = 0xC6;
          				return I2C_SUCCESS;
        			}
        			case I2C_100kHz:
        			{
          				TWBR = 0x12;
          				return I2C_SUCCESS;
        			}
        			case I2C_400kHz:
        			{
          				TWBR = 0x03;
          				return I2C_SUCCESS;
        			}
        			default:
        			{
          				break;
        			}
      			}
      			return I2C_ERROR;
    		}
    		default:
    		{
      			return I2C_ERROR;
    		}
  	}
}

I2C_return_status I2C_imp::start()
{
 	// TODO - this
  	TWCR = (1<<TWEN)|                             // TWI Interface enabled.
         	(0<<TWIE)|(1<<TWINT)|                  // Enable TWI Interupt and clear the flag.
         	(0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|       // Initiate a START condition.
         	(0<<TWWC);

  	wait_twi_int();

  	if ((TWSR != MT_START) && (TWSR != MT_REPEAT_START))
  	{
    		return I2C_ERROR;
  	}

  	return I2C_SUCCESS;
}

I2C_return_status I2C_imp::stop()
{
  	// TODO - this
  	// Needs to do a check if the last transfer was successful.

  	TWCR = ((1<<TWEN)+(1<<TWINT)+(1<<TWSTO));//Send STOP condition

  	return I2C_SUCCESS;
}

I2C_return_status I2C_imp::transmit(tx_type *data)
{
	unsigned char* temp = data->data_ptr + data->bytes;
  	if ((~data->slave_adr & 0x01))
  	{
      		return I2C_ERROR;
  	}

  	if (data->slave_adr != OWN_ADR)
  	{
    		if (start() == I2C_SUCCESS)
    		{
      			wait_twi_int();

      			TWDR = data->slave_adr;
      			TWCR = ((1<<TWINT)+(1<<TWEN));

      			wait_twi_int();

      			if ((TWSR != MT_SLA_ACK)&&(TWSR != MR_SLA_ACK))
      			{
        			return I2C_ERROR;
      			}
    		}
    		while (data->data_ptr < temp)
    		{
      			wait_twi_int();

      			TWDR = *data->data_ptr;
      			TWCR = ((1<<TWINT)+(1<<TWEN));

      			wait_twi_int();

      			if(TWSR != MT_DATA_ACK)
      			{
        			return I2C_ERROR;
      			}
      			data->data_ptr++;
    		}
    		stop();
  	}
  	return I2C_SUCCESS;
}

I2C_return_status I2C_imp::receive(tx_type *data)
{
  	// TODO - this
  	unsigned char* temp = data->data_ptr + data->bytes;

  	if (!(data->slave_adr & READ))
  	{
      		return I2C_ERROR;
  	}

  	if (data->slave_adr != OWN_ADR)
  	{
    		if (start() == I2C_SUCCESS)
    		{
      			wait_twi_int();

      			TWDR = data->slave_adr;
      			TWCR = ((1<<TWINT)+(1<<TWEN));

      			wait_twi_int();

      			if ((TWSR != MT_SLA_ACK)&&(TWSR != MR_SLA_ACK))
      			{
        			return I2C_ERROR;
      			}
    		}
    		while (data->data_ptr < temp)
    		{
      			wait_twi_int();

      			// if there are more data to receive, send an ACK to the the slave
      			if (data->data_ptr <= temp)
      			{
        			TWCR = ((1<<TWINT)+(1<<TWEA)+(1<<TWEN));
      			}
      			else
      			{
        			TWCR = ((1<<TWINT)+(1<<TWEN));
      			}

      			wait_twi_int();

      			*data->data_ptr = TWDR;

      			if(((TWSR == MR_DATA_NACK)&&(data->data_ptr == temp))||(TWSR == MR_DATA_ACK))
      			{
        			stop();
        			return I2C_SUCCESS;
      			}
      			data->data_ptr++;
    		}				
  	}
  	return I2C_ERROR;
}

I2C_status_code I2C_imp::transceiver_busy()
{
  	// TODO - this
  	return BUS_ERROR;
}
