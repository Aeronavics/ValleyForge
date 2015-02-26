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
 *  FILE: 			i2c.cpp
 *
 *  LIBRARY:		I2C
 *
 *  AUTHOR: 		Kevin Gong
 *
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

#include <avr/io.h>


#include <avr_magic/avr_magic.hpp>
#include <avr/interrupt.h>
#include "i2c_platform.hpp"

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

struct TWI_bus
{
  volatile uint8_t TWI_MT_buf[TWI_BUFFER_SIZE];       // TWI master transmitter data buffer.
  volatile uint8_t TWI_MR_sla_adr;                     // TWI master receiver requires a variable to hold target address.
  volatile uint8_t* TWI_MR_data_ptr;                   // TWI master receiver saves the data straight to the user data array.
  volatile uint8_t TWI_ST_buf[TWI_BUFFER_SIZE];        // TWI slave transmitter buffer.
  volatile uint8_t TWI_SR_buf[TWI_BUFFER_SIZE];        // TWI slave receiver buffer.

  volatile bool TWI_gen_call;
  volatile bool TWI_data_in_ST_buf;
  volatile bool TWI_data_in_SR_buf;

  uint8_t own_adr;
  I2C_mode TWI_current_mode;
  volatile uint8_t TWI_msg_size;
  volatile uint8_t TWI_status_reg;
};

// DECLARE IMPORTED GLOBAL VARIABLES.

// DEFINE PRIVATE CLASSES.

/**
 * A Class that provides device specific implementation class for I2C.
 */
class I2C_imp
{
	public:

 		// Methods.

		I2C_return_status enable(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed, uint8_t slave_adr);

		void disable(void);

    void wait_twi();

 		I2C_return_status master_transmit(uint8_t slave_adr, uint8_t* data, uint8_t msg_size);

 		I2C_return_status master_receive(uint8_t slave_adr, uint8_t* data, uint8_t msg_size);

    I2C_return_status slave_transmit(uint8_t* data, uint8_t msg_size);

    I2C_return_status slave_receive(uint8_t* data);


	private:

    		// Functions

    		I2C_imp operator = (I2C_imp const&) = delete;

    		// Fields

};

// DECLARE PRIVATE GLOBAL VARIABLES.

I2C_imp i2c_imp;

TWI_bus TWI_data;

volatile bool TWI_bus_available;

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
    imp = &i2c_imp;
}

I2C::~I2C()
{
	return;
}

I2C_return_status I2C::enable(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed, uint8_t slave_adr)
{
  	return (imp->enable(cpu_speed, scl_speed, slave_adr));
}

void I2C::disable(void)
{
 	return (imp->disable());
}

void I2C::wait_I2C()
{
    return (imp->wait_twi());
}

I2C_return_status I2C::master_transmit(uint8_t slave_adr, uint8_t* data, uint8_t msg_size)
{
  	return (imp->master_transmit(slave_adr, data, msg_size));
}

I2C_return_status I2C::master_receive(uint8_t slave_adr, uint8_t* data, uint8_t msg_size)
{
  	return (imp->master_receive(slave_adr, data, msg_size));
}

I2C_return_status I2C::slave_transmit(uint8_t* data, uint8_t msg_size)
{
    return (imp->slave_transmit(data, msg_size));
}

I2C_return_status I2C::slave_receive(uint8_t* data)
{
    return (imp->slave_receive(data));
}


/****************************************************************************/
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTION (METHODS).

/**
 * I2C_imp private class functions
 **/

I2C_return_status I2C_imp::enable(CPU_CLK_speed cpu_speed, I2C_SCL_speed scl_speed, uint8_t slave_adr)
{
    if (cpu_speed / scl_speed < MAX_SCL_CPU_RATIO)
  	{
    		return I2C_ERROR;
  	}

    TWI_data.TWI_gen_call = false;
    TWI_data.TWI_data_in_ST_buf = false;
    TWI_data.TWI_data_in_SR_buf = false;

    TWI_data.own_adr = slave_adr;

  	TWSR &= (~(1 << TWPS0) & ~(1 << TWPS1));         // prescaler value is always 0 (or prescale of 1)
    TWDR = 0xFF;             // Default content
    TWAR = (slave_adr << 1);

    #ifdef __AVR_ATmega2560__
    TWAMR = 0x00;             // no address mask.
    #endif

    TWI_bus_available == true;         // Signal that TWI bus is now available.

  	switch (cpu_speed)
  	{
    		case CPU_1MHz:
    		{
      			switch (scl_speed)
      			{
                case I2C_10kHz:
                {
                    TWBR = 0x0B;
                    break;
                }
                case I2C_100kHz:
                {
                    return I2C_ERROR;   // Not available at this CPU speed
                }
                case I2C_400kHz:
                {
                    return I2C_ERROR;
                }
                default:
                {
                    return I2C_ERROR;
                }
      			}

            TWCR = (1<<TWEN)|        // Enable TWI-interface and release TWI pins.
                (1<<TWIE)|(1<<TWINT)|
                (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO);
      			return I2C_SUCCESS;
    		}
    		case CPU_8MHz:
    		{
      			switch (scl_speed)
      			{
                case I2C_10kHz:
                {
                    TWBR = 0x62;
                    break;
                }
                case I2C_100kHz:
                {
                    TWBR = 0x08;
                    break;
                }
                case I2C_400kHz:
                {
                    return I2C_ERROR;
                }
                default:
                {
                    return I2C_ERROR;
                }
      			}

            TWCR = (1<<TWEN)|
                (1<<TWIE)|(1<<TWINT)|
                (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO);
      			return I2C_SUCCESS;
    		}
    		case CPU_16MHz:
    		{
      			switch (scl_speed)
      			{
                case I2C_10kHz:
                {
                    TWBR = 0xC6;
                    break;
                }
                case I2C_100kHz:
                {
                    TWBR = 0x12;
                    break;
                }
                case I2C_400kHz:
                {
                    TWBR = 0x03;
                    break;
                }
                default:
                {
                    return I2C_ERROR;
                }
      			}

            TWCR = (1<<TWEN)|
                (1<<TWIE)|(1<<TWINT)|
                (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO);
      			return I2C_SUCCESS;
    		}
    		default:
    		{
      			return I2C_ERROR;
    		}
  	}
  	return I2C_ERROR;
}

void I2C_imp::disable(void)
{
  	TWCR = (0<<TWEN)|(0<<TWIE)|(0<<TWINT);        // Disable TWI-interface and release TWI pins.

  	return;
}

void  I2C_imp::wait_twi()
{
    while (TWCR & (1<<TWIE));
}

I2C_return_status I2C_imp::master_transmit(uint8_t slave_adr, uint8_t* data, uint8_t msg_size)
{
    while (TWI_bus_available == false);

    if (slave_adr != TWI_data.own_adr)
    {
        TWI_data.TWI_current_mode = I2C_MT;

        uint8_t foo;

        slave_adr = ((slave_adr << 1) | WRITE);
        TWI_data.TWI_msg_size = msg_size;
        TWI_data.TWI_MT_buf[0] = slave_adr;

        for (foo = 1 ; foo <= msg_size ; foo++)
        {
            TWI_data.TWI_MT_buf[foo] = *data;
            data++;
        }

        // send START signal
        TWCR = TWCR_START;

        return I2C_SUCCESS;
    }
    else
    {
        TWI_data.TWI_status_reg = TWSR;
        return I2C_ERROR;
    }

    TWI_data.TWI_status_reg = TWSR;
    return I2C_ERROR;
}

I2C_return_status I2C_imp::master_receive(uint8_t slave_adr, uint8_t* data, uint8_t msg_size)
{
    while (TWI_bus_available == false);

    if (slave_adr != TWI_data.own_adr)
    {
        TWI_data.TWI_current_mode = I2C_MR;

        slave_adr = ((slave_adr << 1) | READ);
        TWI_data.TWI_msg_size = msg_size;
        TWI_data.TWI_MR_sla_adr = slave_adr;

        TWI_data.TWI_MR_data_ptr = data;

        TWCR = TWCR_START;

        return I2C_SUCCESS;
    }
    else
    {
        TWI_data.TWI_status_reg = TWSR;
        return I2C_ERROR;
    }
    TWI_data.TWI_status_reg = TWSR;
    return I2C_ERROR;
}

I2C_return_status I2C_imp::slave_transmit(uint8_t* data, uint8_t msg_size)
{
    uint8_t foo;

    TWI_data.TWI_current_mode = I2C_ST;

    for (foo = 0 ; foo < msg_size ; foo++)
    {
        TWI_data.TWI_ST_buf[foo] = *data;
        data++;
    }
    TWI_data.TWI_msg_size = msg_size;

    TWI_data.TWI_data_in_ST_buf = true;

    TWCR = TWCR_DATA_ACK;

    return I2C_SUCCESS;
}

I2C_return_status I2C_imp::slave_receive(uint8_t* data)
{
    uint8_t bar;

    TWI_data.TWI_current_mode = I2C_SR;

    if (TWI_data.TWI_data_in_SR_buf == true)
    {
        for (bar = 0; bar < TWI_data.TWI_msg_size; bar++)
        {
            *data = TWI_data.TWI_SR_buf[bar];
            data++;
        }

        TWI_data.TWI_data_in_SR_buf = false;

        return I2C_SUCCESS;
    }
    else
    {
        return I2C_ERROR;
    }

    return I2C_ERROR;
}


//
/////////////////////////////  Interrupt Vectors  /////////////////////////////

volatile uint8_t TWI_buf_ptr;

ISR(TWI_vect)
{

  switch (TWSR)
  {
      /////////////////////// General TWI statuses ///////////////////////
      case NO_INFO_TWINT_NOT_SET:
      case BUS_ERROR:
      case TWI_START:
      {
          TWI_bus_available = false;
          TWI_buf_ptr = 0;

          switch (TWI_data.TWI_current_mode)
          {
              case I2C_MT:
              {
                  TWDR = TWI_data.TWI_MT_buf[TWI_buf_ptr++];
                  TWCR = TWCR_DATA_ACK;
                  break;
              }
              case I2C_MR:
              {
                  TWDR = TWI_data.TWI_MR_sla_adr;
                  TWCR = TWCR_DATA_ACK;
                  break;
              }
              default:
              {
                  break;
              }
          }
          break;
      }
      case TWI_REP_START:
      {
          TWI_bus_available = false;
          TWI_buf_ptr = 0;

          switch (TWI_data.TWI_current_mode)
          {
              case I2C_MT:
              {
                  TWDR = TWI_data.TWI_MT_buf[TWI_buf_ptr++];
                  TWCR = TWCR_DATA_ACK;
                  break;
              }
              case I2C_MR:
              {
                  TWDR = TWI_data.TWI_MR_sla_adr;
                  TWCR = TWCR_DATA_ACK;
                  break;
              }
              default:
              {
                  break;
              }
          }
          break;
      }
    case TWI_ARB_LOST:
    {
        TWCR = TWCR_STOP;
        break;
    }
    /////////////////////// Master Transmitter statuses ///////////////////////
    case MT_SLA_ACK:
    {
        TWDR = TWI_data.TWI_MT_buf[TWI_buf_ptr++];
        TWCR = TWCR_DATA_ACK;
        break;
    }
    case MT_SLA_NAK:
    {
        TWI_bus_available = true;
        TWCR = TWCR_STOP;
        break;
    }
    case MT_DATA_ACK:
    {
        if (TWI_buf_ptr <= (TWI_data.TWI_msg_size))
        {
            TWDR = TWI_data.TWI_MT_buf[TWI_buf_ptr++];
            TWCR = TWCR_DATA_ACK;
        }
        else
        {
            TWCR = TWCR_STOP;
            TWI_bus_available = true;
        }
        break;
    }
    case MT_DATA_NAK:
    {
        TWCR = TWCR_STOP;
        TWI_bus_available = true;
        break;
    }
    /////////////////////// Master Receiver statuses ///////////////////////
    case MR_SLA_ACK:
    {
        TWCR = TWCR_DATA_ACK;
        break;
    }
    case MR_SLA_NAK:
    {
        // TODO - this

        // Byte sent but Not Acknowledged.
        //
        // Could try to resend byte or attempt to restart communications.

        TWCR = TWCR_STOP;
        TWI_bus_available = true;
        break;
    }
    case MR_DATA_ACK:
    {
        if (TWI_buf_ptr < (TWI_data.TWI_msg_size - 2)) // have to pre-emptively know that the next byte will be the last
        {
            *TWI_data.TWI_MR_data_ptr = TWDR;
            TWI_data.TWI_MR_data_ptr++;
            TWI_buf_ptr++;
            TWCR = TWCR_DATA_ACK;
        }
        else                                           // Last byte is saved with TWEA Not set.
        {
            *TWI_data.TWI_MR_data_ptr = TWDR;
            TWCR = TWCR_DATA_NAK;
        }
        break;
    }
    case MR_DATA_NAK:
    {
        // Confirmation that the last byte has been transmitted.

        TWCR = TWCR_STOP;
        TWI_bus_available = true;
        break;
    }
    /////////////////////// Slave Receiver ///////////////////////
    case SR_SLA_ACK:
    {
        TWI_buf_ptr = 0;
        TWI_bus_available = false;

        TWCR = TWCR_DATA_ACK;
        break;
    }
    case S_LOST_ARB_1:
    case SR_GEN_ACK:
    {
        // untested
        TWI_buf_ptr = 0;
        TWI_data.TWI_gen_call = true;
        TWI_bus_available = false;

        TWCR = TWCR_DATA_ACK;
        break;
    }
    case S_LOST_ARB_2:
    case SR_ADR_DATA_ACK:
    {
        TWI_data.TWI_SR_buf[TWI_buf_ptr++] = TWDR;
        TWI_data.TWI_data_in_SR_buf = true;
        TWI_data.TWI_msg_size = TWI_buf_ptr;

        TWCR = TWCR_DATA_ACK;
        break;
    }
    case SR_ADR_DATA_NAK:
    case SR_GEN_DATA_ACK:
    {
        // untested
        TWI_data.TWI_SR_buf[TWI_buf_ptr++] = TWDR;

        TWCR = TWCR_DATA_ACK;
        break;
    }
    case SR_GEN_DATA_NAK:
    case SR_STOP_RESTART:
    {
        TWI_bus_available = true;

        TWCR = TWCR_DATA_ACK;

        break;
    }
    /////////////////////// Slave Transmitter ///////////////////////
    case ST_SLA_ACK:
    {
        TWI_buf_ptr = 0;
        TWI_bus_available = false;

        TWDR = TWI_data.TWI_ST_buf[TWI_buf_ptr++];

        TWCR = TWCR_DATA_ACK;
        break;
    }
    case S_LOST_ARB_3:
    case ST_DATA_ACK:
    {
        if (TWI_buf_ptr < (TWI_data.TWI_msg_size - 1))     // Pre-emtively know the next byte is the last
        {
            TWDR = TWI_data.TWI_ST_buf[TWI_buf_ptr++];

            TWCR = TWCR_DATA_ACK;
        }
        else
        {
            TWDR = TWI_data.TWI_ST_buf[TWI_buf_ptr];

            TWCR = TWCR_DATA_NAK;
        }
        break;
    }
    case ST_DATA_NAK:
    {
        TWI_data.TWI_data_in_ST_buf = false;
        TWI_bus_available = true;

        TWCR = TWCR_DATA_ACK;

        break;
    }
    case ST_DATA_ACK_LAST_BYTE:
    {
        TWI_data.TWI_data_in_ST_buf = false;
        TWI_bus_available = true;

        TWCR = TWCR_DATA_ACK;
        break;
    }
    default :
    {
        break;
    }
  }
}

