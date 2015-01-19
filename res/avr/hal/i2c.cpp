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

    I2C_return_status initialise(I2C_bit_rate bitrate, I2C_prescaler pre_scaler);

		I2C_return_status start();

		I2C_return_status stop();

    I2C_return_status transmit(tx_type *data);

    I2C_return_status receive(tx_type *data);

    I2C_status_code_t transceiver_busy();

	private:

    // Functions

    I2C_imp(void) = delete;

    I2C_imp(I2C_imp) = delete;

    I2C_imp operator = (I2C_imp const&) = delete;

    // Fields

		I2C_mode mode;

		I2C_prescaler pre_scaler;

    I2C_bit_rate bit_rate;

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

I2C_return_status I2C::initialise(I2C_bit_rate bitrate, I2C_prescaler pre_scaler)
{
  return (imp->initialise(bitrate, pre_scaler));
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

I2C_status_code_t I2C::transceiver_busy()
{
  return (imp->transceiver_busy());
}

/****************************************************************************/
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTION (METHODS).

/**
 * I2C_imp private class functions
 **/

void I2C_imp::enable()
{
  // TODO - this
  return;
}

void I2C_imp::disable(void)
{
  // TODO - this
  return;
}

I2C_return_status I2C_imp::initialise(I2C_bit_rate bitrate, I2C_prescaler pre_scaler)
{
  // TODO - this
  return I2C_ERROR;
}

I2C_return_status I2C_imp::start()
{
  // TODO - this
  return I2C_ERROR;
}

I2C_return_status I2C_imp::stop()
{
  // TODO - this
  return I2C_ERROR;
}

I2C_return_status I2C_imp::transmit(tx_type *data)
{
  // TODO - this
  return I2C_ERROR;
}

I2C_return_status I2C_imp::receive(tx_type *data)
{
  // TODO - this
  return I2C_ERROR;
}

I2C_status_code_t I2C_imp::transceiver_busy()
{
  // TODO - this
  return I2C_ERROR;
}
