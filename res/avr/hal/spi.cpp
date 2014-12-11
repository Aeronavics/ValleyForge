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
 *  AUTHOR: 		Jared Sanson
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
#include <hal/usart.hpp>
#include <hal/gpio.hpp>

#include "hal/spi.hpp"

// DEFINE PRIVATE MACROS.

// DEFINE DEVICE PARTICULAR REGISTER ADDRESSES

/*
 * Structure to contain the GPIO pin addresses that represent the peripheral pins for all the SPI channels.
 */
typedef struct SPI_PINS {
	IO_pin_address miso;
	IO_pin_address mosi;
	IO_pin_address sck;
	IO_pin_address ss;
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

	Spi_imp(Spi_channel channel, Spi_pins pins)
		: channel(channel), pins(pins)
	{
		this->stc_isr = NULL;
		this->stc_isr_enabled = false;

		this->ss_pin = pins.ss;
		this->ss_mode = SPI_SS_NONE;
	}

	~Spi_imp() { }

	void bind(void)
	{
		disable(); // Start disabled, so the module can be configured
	}

	void unbind(void)
	{
		disable();
	}

	void enable(void)
	{
		Gpio_pin mosi(pins.mosi);
		Gpio_pin miso(pins.miso);
		Gpio_pin sck(pins.sck);
		Gpio_pin ss(pins.ss);

		// Enable GPIO inputs depending on master/slave mode
		if (this->setup_mode == SPI_MASTER)
		{
			mosi.set_mode(GPIO_OUTPUT_PP);
			miso.set_mode(GPIO_INPUT_FL);
			sck.set_mode(GPIO_OUTPUT_PP);

			// NOTE - You should not configure SS as an input in master mode.
			// If it's an input and it's pulled low, the SPI peripheral
			// switches to slave mode and generates an interrupt.
			// For more information see the chip's datasheet.
			ss.set_mode(GPIO_OUTPUT_PP);
		}
		else // SPI_SLAVE
		{
			mosi.set_mode(GPIO_INPUT_FL);
			miso.set_mode(GPIO_OUTPUT_PP);
			sck.set_mode(GPIO_INPUT_FL);

			// NOTE: SS must be pulled low before the SPI module will shift any data!!
			ss.set_mode(GPIO_INPUT_FL);

			// NOTE: If SS is pulled high, then MISO is overridden to be an input.
			// This reverts back to output when SS is pulled low.
		}

		bit_write(SPCR, SPE, 1);	// Enable transceiver
		bit_write(SPCR, SPIE, 1);	// Enable interrupt
	}

	void disable(void)
	{
		// Would it make sense to disable the GPIO pins here?

		bit_write(SPCR, SPE, 0);	// Disable transceiver
		bit_write(SPCR, SPIE, 0);	// Disable interrupt
	}

	Spi_config_status configure(Spi_setup_mode setup_mode, Spi_data_mode data_mode, Spi_frame_format frame_format)
	{
		Spi_config_status result;

		disable();

		// Set Master/Slave mode
		result = set_mode(setup_mode);
		if (result != SPI_CFG_SUCCESS)
			return result;

		// Set data format
		result = set_data_config(data_mode, frame_format);
		if (result != SPI_CFG_SUCCESS)
			return result;

		enable();

		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_mode(Spi_setup_mode mode)
	{
		if (mode == SPI_MASTER)
		{
			bit_write(SPCR, MSTR, 1); // Master mode
		}
		else // SPI_SLAVE
		{
			bit_write(SPCR, MSTR, 0); // Slave mode
		}

		this->setup_mode = mode;

		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_data_config(Spi_data_mode data_mode, Spi_frame_format frame_format)
	{
		// Configure the data/clock polarity (data mode)
		// The operating modes 0 to 3 represent standard operating modes of SPI,
		// formed by different combinations of CPOL and CPHA.
		switch (data_mode)
		{
			case SPI_MODE_0:
			{
				// Sample on leading-rising edge
				bit_write(SPCR, CPOL, 0);	// Non-inverted clock
				bit_write(SPCR, CPHA, 0);	// Sample on leading edge
				break;
			};

			case SPI_MODE_1:
			{
				// Sample on trailing-falling edge
				bit_write(SPCR, CPOL, 0);	// Non-inverted clock
				bit_write(SPCR, CPHA, 1);	// Sample on leading edge
				break;
			};

			case SPI_MODE_2:
			{
				// Sample on leading-falling edge
				bit_write(SPCR, CPOL, 1);	// Inverted clock
				bit_write(SPCR, CPHA, 0);	// Sample on trailing edge
				break;
			};

			case SPI_MODE_3:
			{
				// Sample on trailing-rising edge
				bit_write(SPCR, CPOL, 1);	// Inverted clock
				bit_write(SPCR, CPHA, 1);	// Sample on trailing edge
				break;
			};

			default:
				return SPI_CFG_FAILED;
		}

		// Configure the frame format.
		// The AVR supports 8/16 bit data and LSB/MSB-first data configuration.


		switch (frame_format)
		{
			case SPI_MSB_FIRST:
			{
				bit_write(SPCR, DORD, 0);
				break;
			}

			case SPI_LSB_FIRST:
			{
				bit_write(SPCR, DORD, 1);
				break;
			}

			default:
				return SPI_CFG_FAILED;
		}


		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_speed(int16_t divider)
	{
		// The AVR only supports a fixed number of SPI speeds,
		// defined in the enum Spi_clock_speed as clock postscaler settings.
		// Thus, the SPI speed is dependant on the divider and clock frequency.

		if (divider > 0b111)
			return SPI_CFG_FAILED; // Unsupported clock divider

		bit_write(SPSR, SPI2X, (divider & 0b100));
		reg_write(SPCR, SPR0, 2, (divider & 0b011));

		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_slave_select(Spi_slave_select_mode mode, IO_pin_address software_ss_pin)
	{
		// NOTE: This is only applicable in master mode

		this->ss_mode = mode;

		switch (mode)
		{
			// Use the SS pin defined by target_config.hpp
			case SPI_SS_HARDWARE:
			{
				this->ss_pin = this->pins.ss;
				break;
			};

			// Use the provided SS pin
			case SPI_SS_SOFTWARE:
			{
				// NOTE: The user must configure this pin as an input.
				this->ss_pin = software_ss_pin;
				break;
			};

			// Don't use an SS pin
			case SPI_SS_NONE:
				break;

			default:
				return SPI_CFG_FAILED;
		}

		return SPI_CFG_SUCCESS;
	}

	int16_t transfer(uint8_t tx_data)
	{
		// Master: Should initiate a transfer and block until fully shifted (and rx_data is valid)
		// Slave: Should block until the remote master shifts in enough data (and tx_data is fully shifted out)

		// Safety net (in case an async transfer was initiated beforehand)
		while (transfer_busy())
		{
			// Wait
		}

		set_ss(true); // Pull SS low

		SPDR = tx_data;

		while (transfer_busy())
		{
			// Wait
		}

		set_ss(false);

		return SPDR;
	}

	Spi_io_status transfer_async(uint8_t tx_data, uint8_t *rx_data = NULL, spi_data_callback_t done = NULL)
	{
		// Master: Should initiate a transfer and return immediately, calling done callback when rx_data is valid.
		// Slave: Should tell the transceiver that we're expecting some data, and it should call the done callback when data is received

		if (transfer_busy())
			return SPI_IO_BUSY;

		// Tell async handler we're expecting one byte
		async.index = 0;
		async.size = 1;
		async.rx_data = rx_data;
		async.tx_data = NULL;
		async.cb_done = done;
		async.active = true;

		set_ss(true); // The interrupt will reset this

		// Start the transfer
		SPDR = tx_data;

		return SPI_IO_SUCCESS;
	}

	Spi_io_status transfer_buffer(uint8_t *tx_data, uint8_t *rx_data, size_t size)
	{
		if (tx_data == NULL)
			return SPI_IO_FAILED;

		// Safety net (in case an async transfer was initiated beforehand)
		while (transfer_busy())
		{
			// Wait
		}

		set_ss(true);

		// In master mode, this will transfer 'size' bytes.
		// In slave mode, this will wait for the master to transfer 'size' bytes.
		for (size_t i = 0; i < size; i++)
		{
			SPDR = *tx_data++;

			while (transfer_busy())
			{
				// Wait
			}

			uint8_t rx = SPDR;

			if (rx_data != NULL)
			{
				*rx_data++ = (uint8_t)rx;
			}
		}

		set_ss(false);

		return SPI_IO_SUCCESS;
	}

	Spi_io_status transfer_buffer_async(uint8_t *tx_data, uint8_t *rx_data, size_t size, spi_data_callback_t done = NULL)
	{
		if (size == 0)
			return SPI_IO_FAILED;

		if (transfer_busy())
			return SPI_IO_BUSY;

		// Tell async handler we're expecting one byte
		async.index = 0;
		async.size = size;
		async.rx_data = rx_data;
		async.tx_data = tx_data;
		async.cb_done = done;
		async.active = true;

		set_ss(true); // The interrupt will reset this

		// Start the transfer
		SPDR = tx_data[0];

		return SPI_IO_SUCCESS;
	}

	bool transfer_busy(void)
	{
		// The SPI module is currently shifting data.
		// rx_data is not yet valid, and tx_data cannot be written.

		return (bit_read(SPSR, SPIF) == 0) || (async.active);
	}

	Spi_io_status get_status(void)
	{
		return SPI_IO_FAILED;
	}

	void enable_interrupts(void)
	{
		if (stc_isr != NULL)
			stc_isr_enabled = true;
	}

	void disable_interrupts(void)
	{
		stc_isr_enabled = false;
	}

	Spi_int_status attach_interrupt(Spi_interrupt_type interrupt, callback_t callback)
	{
		return SPI_INT_FAILED;
	}

	Spi_int_status detach_interrupt(Spi_interrupt_type interrupt)
	{
		return SPI_INT_FAILED;
	}

public: // Public Fields

	Spi_channel channel;

	/**
	 * Collection to contain the GPIO addresses which are to be attached to the SPI isntance.
	 */
	Spi_pins pins;

	Spi_setup_mode setup_mode;

	Spi_slave_select_mode ss_mode;
	IO_pin_address ss_pin;

	void set_ss(bool ss_enabled)
	{
		if ((setup_mode == SPI_MASTER) && (ss_mode != SPI_SS_NONE))
		{
			Gpio_pin ss(this->ss_pin);
			ss.write(ss_enabled ? GPIO_O_LOW : GPIO_O_HIGH); // Inverting
		}
	}

public: // Asynchronous Interrupt Handling

	callback_t stc_isr;
	bool stc_isr_enabled;

	void isr_transfer_complete()
	{
		if (async.active)
		{
			uint8_t rx = SPDR; // Clear the RX buffer

			// Receive
			if (async.rx_data != NULL)
			{
				async.rx_data[async.index] = rx;
			}

			async.index++;

			if (async.index >= async.size)
			{
				// Finished transferring bytes

				async.active = false;

				set_ss(false);

				if (async.cb_done != NULL)
					async.cb_done(SPI_IO_SUCCESS, async.rx_data, async.size);
			}
			else if (async.tx_data != NULL)
			{
				// Still more data to transmit
				SPDR = async.tx_data[async.index];
			}
		}
		else
		{
			// Not currently processing any async communications
			if (stc_isr != NULL && stc_isr_enabled)
				stc_isr();
		}
	}


	struct
	{
		bool active;

		uint8_t *tx_data;
		uint8_t *rx_data;
		size_t size;
		size_t index;

		spi_data_callback_t cb_done;
	} async;

	// async mode : rx_byte, buffer
	// callback : function pointer
	// *data : one or more bytes
	// active : bool
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

// NOTE - As far as I'm aware, AVRs have only one main SPI module.
//  However other SPIs may be available through the USART on some chips.

static Spi_imp spi_imp = Spi_imp(
	SPI_0,
	(Spi_pins) {
		.miso = _IOADDR(SPI0_MISO_PORT, SPI0_MISO_PIN),
		.mosi = _IOADDR(SPI0_MOSI_PORT, SPI0_MOSI_PIN),
		.sck  = _IOADDR(SPI0_SCK_PORT, SPI0_SCK_PIN),
		.ss   = _IOADDR(SPI0_SS_PORT, SPI0_SS_PIN),
	}
);

// TODO - USART-SPI

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
			return Spi(&spi_imp);
	}

	// If we make it to here, then something has gone very wrong (like the user maliciously cast an invalid value into a channel number).

	// Loop forever, which hopefully reboots the micro so we have a chance to recover.
	while (true)
	{
		// Consider the bad life choices that have led us to this point.
	}

	return Spi(static_cast<Spi_imp*>(NULL));
}

Spi_config_status Spi::configure(Spi_setup_mode setup_mode, Spi_data_mode data_mode, Spi_frame_format frame_format)
{
	return imp->configure(setup_mode, data_mode, frame_format);
}

Spi_config_status Spi::set_mode(Spi_setup_mode mode)
{
	return imp->set_mode(mode);
}

Spi_config_status Spi::set_data_config(Spi_data_mode data_mode, Spi_frame_format frame_format)
{
	return imp->set_data_config(data_mode, frame_format);
}

Spi_config_status Spi::set_speed(int16_t speed)
{
	return imp->set_speed(speed);
}

Spi_config_status Spi::set_slave_select(Spi_slave_select_mode mode, IO_pin_address software_ss_pin)
{
	return imp->set_slave_select(mode, software_ss_pin);
}

int16_t Spi::transfer(uint8_t tx_data)
{
	return imp->transfer(tx_data);
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

bool Spi::transfer_busy(void)
{
	return imp->transfer_busy();
}

Spi_io_status Spi::get_status(void)
{
	return imp->get_status();
}

void Spi::enable_interrupts(void)
{
	imp->enable_interrupts();
}

void Spi::disable_interrupts(void)
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




// Interrupts

ISR(SPI_STC_vect)
{
	spi_imp.isr_transfer_complete();
}

//TODO - How do we share the USART-SPI interrupts from the USART module??

// ALL DONE.
