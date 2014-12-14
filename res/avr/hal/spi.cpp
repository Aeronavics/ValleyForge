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

/********************************************************************************************************************************
 *
 *  FILE: 		spi.cpp
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	24-01-2012
 *
 *	Functionality to provide implementation for SPI in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/io.h>
#include <avr/interrupt.h>

#include "hal/spi.hpp"

// DEFINE PRIVATE MACROS.

// DEFINE DEVICE PARTICULAR REGISTER ADDRESSES

/*
 * Structure to contain the GPIO pin addresses that represent the peripheral pins for all the SPI channels.
 */
typedef struct SPI_PINS {
	IO_pin_address miso_address;
	IO_pin_address mosi_address;
	IO_pin_address sck_address;
	IO_pin_address ss_address;
} Spi_pins;

// DECLARE IMPORTED GLOBAL VARIABLES

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
* Initialises the SPI implementation instances and codes the required
* register addresses and GPIO locations.
*
* @param void.
* @return void.
*/
void initialise_SPI(void);

// DEFINE PRIVATE TYPES AND STRUCTS.

/**
 * Class to implement the functionality
 * required for the SPI.
 */
class Spi_imp
{
public:

	Spi_imp(Spi_channel channel, Spi_pins pins);

	~Spi_imp();

	Spi_config_status set_mode(Spi_setup_mode mode);

	Spi_config_status set_data_config(Spi_data_mode mode, Spi_bit_order bit_order, Spi_frame_format frame_format);

	Spi_config_status set_speed(int16_t speed);

	Spi_config_status set_slave_select(Spi_slave_select_mode mode);

	Spi_io_status transfer(uint8_t tx_data, uint8_t *rx_data = NULL);

	Spi_io_status transfer_async(uint8_t tx_data, uint8_t *rx_data = NULL, spi_data_callback_t done = NULL);

	Spi_io_status transfer_buffer(uint8_t *tx_data, uint8_t *rx_data, size_t size);

	Spi_io_status transfer_buffer_async(uint8_t *tx_block, uint8_t *rx_block, size_t size, spi_data_callback_t done = NULL);

	bool transfer_busy(void);

	Spi_io_status get_status(void);

	void enable_interrupts(void);

	void disable_interrupts(void);

	Spi_int_status attach_interrupt(Spi_interrupt_type interrupt, callback_t callback);

	Spi_int_status detach_interrupt(Spi_interrupt_type interrupt);

	// Public Fields

	Spi_channel channel;

	/**
	 * Collection to contain the GPIO addresses which are to be attached to the SPI isntance.
	 */
	Spi_pins pins;

	//Private functions & Fields
private:


};

/**
 * Class to implement the functionality
 * required for USART-based SPI.
 */
/*class Usartspi_imp : public Spi_imp
{
public:
	Usartspi_imp();

	~Usartspi_imp();
};*/

// DECLARE PRIVATE GLOBAL VARIABLES.

static Spi_imp spi_imp = Spi_imp(SPI_0,
	(Spi_pins){
		.miso_address={.port=SPI0_MISO_PORT, .pin=SPI0_MISO_PIN},
		.mosi_address={.port=SPI0_MOSI_PORT, .pin=SPI0_MOSI_PIN},
		.sck_address={.port=SPI0_SCK_PORT, .pin=SPI0_SCK_PIN},
#if defined(SPIO_SS_PORT) && defined(SPIO_SS_PIN)
		.ss_address={.port=SPI0_SS_PORT, .pin=SPI0_SS_PIN},
#endif
	}
);

/* Array of user ISRs for SPI interrupts */
callback_t spi_interrupts[NUM_SPI_INTERRUPTS];


/* Variable to indicate whether usart_spi[] has been initialised yet */
bool initialised_spi;

/* Enumerated list of SPI interrupts for use in accessing the appropriate function pointer from the function pointer array */
enum spi_interrupts
{
	SPI_STC_int
};

// IMPLEMENT PUBLIC FUNCTIONS.

Spi::Spi(Spi_imp *implementation)
{
	imp = implementation;
}

Spi::~Spi()
{
	// Some targets need to make calls to imp when falling out of scope, AVR doesn't, so do nothing.
}

Spi Spi::bind(Spi_channel channel)
{
	switch (channel)
	{
		case SPI_0:
			return Spi(static_cast<Spi_imp*>(NULL));
	}

	// If we make it to here, then something has gone very wrong (like the user maliciously cast an invalid value into a channel number).

	// Loop forever, which hopefully reboots the micro so we have a chance to recover.
	while (true)
	{
		// Consider the bad life choices that have led us to this point.
	}

	return Spi(static_cast<Spi_imp*>(NULL));
}

Spi_config_status Spi::set_mode(Spi_setup_mode mode)
{
	return imp->set_mode(mode);
}

Spi_config_status Spi::set_data_config(Spi_data_mode mode, Spi_bit_order bit_order, Spi_frame_format frame_format)
{
	return imp->set_data_config(mode, bit_order, frame_format);
}

Spi_config_status Spi::set_speed(int16_t speed)
{
	return imp->set_speed(speed);
}

Spi_config_status Spi::set_slave_select(Spi_slave_select_mode mode)
{
	return imp->set_slave_select(mode);
}

Spi_io_status Spi::transfer(uint8_t tx_data, uint8_t *rx_data)
{
	return imp->transfer(tx_data, rx_data);
}

Spi_io_status Spi::transfer_async(uint8_t tx_data, uint8_t *rx_data, spi_data_callback_t done)
{
	return imp->transfer_async(tx_data, rx_data, done);
}

Spi_io_status Spi::transfer_buffer(uint8_t *tx_data, uint8_t *rx_data, size_t size)
{
	return imp->transfer_buffer(tx_data, rx_data, size);
}

Spi_io_status Spi::transfer_buffer_async(uint8_t *tx_block, uint8_t *rx_block, size_t size, spi_data_callback_t done)
{
	return imp->transfer_buffer_async(tx_block, rx_block, size, done);
}

bool Spi::transfer_busy()
{
	return imp->transfer_busy();
}

Spi_io_status Spi::get_status()
{
	return imp->get_status();
}

void Spi::enable_interrupts()
{
	imp->enable_interrupts();
}

void Spi::disable_interrupts()
{
	imp->disable_interrupts();
}

Spi_int_status Spi::attach_interrupt(Spi_interrupt_type interrupt, callback_t callback)
{
	return imp->attach_interrupt(interrupt, callback);
}

Spi_int_status Spi::detach_interrupt(Spi_interrupt_type interrupt)
{
	return imp->detach_interrupt(interrupt);
}


// IMPLEMENT EXTRANEOUS FUNCTIONS
/**
* Initialises the SPI implementation instances and codes the required
* register addresses and GPIO locations.
*
* @param void.
* @return void.
*/
void initialise_SPI(void)
{
	/* Initialise each SPI with its particular SPI number */
//   for (uint8_t i = 0; i < NUM_SPI_CHANNELS; i++)
//   {
//     Spi_imps[i].SpiNumber = (Spi_number)i;
//   }
//
//   /* Assign the addresses of the register locations */
//   Spi_imps[(int8_t)SPI_0].registerTable.SPCR_address = SPCR_ADDRESS;
//   Spi_imps[(int8_t)SPI_0].registerTable.SPSR_address = SPSR_ADDRESS;
//   Spi_imps[(int8_t)SPI_0].registerTable.SPDR_address = SPDR_ADDRESS;
//
//   /* Assign the GPIO addresses for each SPI instance */
//   Spi_imps[(int8_t)SPI_0].SpiPinCollection.MISO_address.port = SPI0_MISO_PORT;
//   Spi_imps[(int8_t)SPI_0].SpiPinCollection.tx_address.pin = SPI0_MISO_PIN;
//
//   etc.
}


Spi_imp::Spi_imp(Spi_channel channel, Spi_pins pins)
{
	this->channel = channel;
	this->pins = pins;
}

Spi_imp::~Spi_imp()
{
	// Clean up
}

Spi_config_status Spi_imp::set_mode(Spi_setup_mode mode)
{
	return SPI_CFG_FAILED;
}

Spi_config_status Spi_imp::set_data_config(Spi_data_mode mode, Spi_bit_order bit_order, Spi_frame_format frame_format)
{
	return SPI_CFG_FAILED;
}

Spi_config_status Spi_imp::set_speed(int16_t speed)
{
	return SPI_CFG_FAILED;
}

Spi_config_status Spi_imp::set_slave_select(Spi_slave_select_mode mode)
{
	return SPI_CFG_FAILED;
}

Spi_io_status Spi_imp::transfer(uint8_t tx_data, uint8_t *rx_data)
{
	return SPI_IO_FAILED;
}

Spi_io_status Spi_imp::transfer_async(uint8_t tx_data, uint8_t *rx_data, spi_data_callback_t done)
{
	return SPI_IO_FAILED;
}

Spi_io_status Spi_imp::transfer_buffer(uint8_t *tx_data, uint8_t *rx_data, size_t size)
{
	return SPI_IO_FAILED;
}

Spi_io_status Spi_imp::transfer_buffer_async(uint8_t *tx_block, uint8_t *rx_block, size_t size, spi_data_callback_t done)
{
	return SPI_IO_FAILED;
}

bool Spi_imp::transfer_busy(void)
{
	return false;
}

Spi_io_status Spi_imp::get_status(void)
{
	return SPI_IO_FAILED;
}

void Spi_imp::enable_interrupts(void)
{

}

void Spi_imp::disable_interrupts(void)
{

}

Spi_int_status Spi_imp::attach_interrupt(Spi_interrupt_type interrupt, callback_t callback)
{
	return SPI_INT_FAILED;
}

Spi_int_status Spi_imp::detach_interrupt(Spi_interrupt_type interrupt)
{
	return SPI_INT_FAILED;
}

/** Declare the ISRptrs
 *
 * Each SPI interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs by way of the function pointer array SpiInterrupts[]. Here the
 * ISRs are declared and the user ISR is called if the appropriate element of the function
 * pointer array is non NULL.
 */

ISR(SPI_STC_vect)
{
	//TODO - Interrupts
//	if (spi_interrupts[SPI_STC_int])
//		spi_interrupts[SPI_STC_int]();
}

//TODO - How do we share the USART-SPI interrupts from the USART module??

// ALL DONE.
