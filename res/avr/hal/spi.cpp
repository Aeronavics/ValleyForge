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
#include <hal/gpio.hpp>

#include "hal/spi.hpp"

#ifdef USE_SPI_USART
	#include <hal/usart.hpp>
#endif

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

	virtual void enable(void)
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

	virtual void disable(void)
	{
		// Would it make sense to disable the GPIO pins here?

		bit_write(SPCR, SPE, 0);	// Disable transceiver
		bit_write(SPCR, SPIE, 0);	// Disable interrupt
	}

	virtual Spi_config_status configure(Spi_setup_mode setup_mode, Spi_data_mode data_mode, Spi_frame_format frame_format)
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

	virtual Spi_config_status set_mode(Spi_setup_mode mode)
	{
		switch (mode)
		{
			case SPI_MASTER:
			{
				bit_write(SPCR, MSTR, 1); // Master mode
				break;
			};

			case SPI_SLAVE:
			{
				bit_write(SPCR, MSTR, 0); // Slave mode
				break;
			};

			default:
				return SPI_CFG_FAILED;
		}

		this->setup_mode = mode;

		return SPI_CFG_SUCCESS;
	}

	virtual Spi_config_status set_data_config(Spi_data_mode data_mode, Spi_frame_format frame_format)
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
		// The AVR supports 8 bit data and LSB/MSB-first data configuration.

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

	virtual Spi_config_status set_speed(int16_t divider)
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

	virtual Spi_config_status set_slave_select(Spi_slave_select_mode mode, IO_pin_address software_ss_pin)
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

	virtual int16_t transfer(uint8_t tx_data)
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

	virtual Spi_io_status transfer_async(uint8_t tx_data, uint8_t *rx_data = NULL, spi_data_callback_t done = NULL)
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

	virtual Spi_io_status transfer_buffer(uint8_t *tx_data, uint8_t *rx_data, size_t size)
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

	virtual Spi_io_status transfer_buffer_async(uint8_t *tx_data, uint8_t *rx_data, size_t size, spi_data_callback_t done = NULL)
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

	virtual bool transfer_busy(void)
	{
		// The SPI module is currently shifting data.
		// rx_data is not yet valid, and tx_data cannot be written.

		return (bit_read(SPSR, SPIF) == 0) || (async.active);
	}

	virtual Spi_io_status get_status(void)
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

protected:

	// Methods

	Spi_imp(void);	// Poisoned.

	Spi_imp(Usart_imp*);	// Poisoned.
};


#ifdef USE_SPI_USART

typedef struct
{
	volatile uint8_t* UDR;
	volatile uint8_t* UCSRA;
	volatile uint8_t* UCSRB;
	volatile uint8_t* UCSRC;
	volatile uint16_t* UBRR;
} Usart_registers;

/**
 * Class to implement the functionality required for USART-based SPI (MSPIM).
 * See the ATmega2560 datasheet for more info.
 *
 * Unfortunately there seems to be no easy way to share functionality
 * with the Usart_imp class.
 */
class Usartspi_imp : public Spi_imp
{
public:
	Usartspi_imp(Spi_channel channel, Spi_pins pins, Usart_registers registers)
		: Spi_imp(channel, pins)
	{ }

	~Usartspi_imp() { }

	bool enabled(void) const
	{
		return (bit_read(*registers.UCSRB, TXEN_BIT) || bit_read(*registers.UCSRB, RXEN_BIT));
	}

	bool usart_inuse(void)
	{
		// Check if the peripheral is currently configured for USART mode
		bool mspim_mode = reg_read(*registers.UCSRC, UMSEL0_BIT, 2) == 0b11;
		return (enabled() && !mspim_mode);
	}

	void enable(void)
	{
		*registers.UBRR = 0;

		// Configure XCK as output, for master mode
		Gpio_pin xck = Gpio_pin(pins.sck);
		xck.set_mode(GPIO_OUTPUT_PP);

		// Enable the transceivers
		bit_write(*registers.UCSRB, TXEN_BIT, 1);
		bit_write(*registers.UCSRB, RXEN_BIT, 1);

		// NOTE - UBRR cannot be set until AFTER the peripheral is enabled
		*registers.UBRR = this->ubrr;
	}

	void disable(void)
	{
		// NOTE - UBRR must be set to 0 before configuring
		*registers.UBRR = 0;

		// Disable the transceivers
		bit_write(*registers.UCSRB, TXEN_BIT, 0);
		bit_write(*registers.UCSRB, RXEN_BIT, 0);
	}

	Spi_config_status configure(Spi_setup_mode setup_mode, Spi_data_mode data_mode, Spi_frame_format frame_format)
	{
		// Check that we're not already configured for USART mode
		if (usart_inuse())
			return SPI_CFG_FAILED;

		return Spi_imp::configure(setup_mode, data_mode, frame_format);
	}

	Spi_config_status set_mode(Spi_setup_mode mode)
	{
		// MSPIM only supports master mode.
		if (mode != SPI_MASTER)
			return SPI_CFG_FAILED;

		// Check that we're not already configured for USART mode
		if (usart_inuse())
			return SPI_CFG_FAILED;

		reg_write(*registers.UCSRC, UMSEL0_BIT, 2, 0b11); //MSPIM mode (master SPI)

		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_data_config(Spi_data_mode data_mode, Spi_frame_format frame_format)
	{
		switch (data_mode)
		{
			case SPI_MODE_0:
			{
				bit_write(*registers.UCSRC, UCPOL_BIT, 0);
				bit_write(*registers.UCSRC, UCPHA_BIT, 0);
				break;
			};

			case SPI_MODE_1:
			{
				bit_write(*registers.UCSRC, UCPOL_BIT, 0);
				bit_write(*registers.UCSRC, UCPHA_BIT, 1);
				break;
			};

			case SPI_MODE_2:
			{
				bit_write(*registers.UCSRC, UCPOL_BIT, 1);
				bit_write(*registers.UCSRC, UCPHA_BIT, 0);
				break;
			};

			case SPI_MODE_3:
			{
				bit_write(*registers.UCSRC, UCPOL_BIT, 1);
				bit_write(*registers.UCSRC, UCPHA_BIT, 1);
				break;
			};

			default:
				return SPI_CFG_FAILED;
		}

		switch (frame_format)
		{
			case SPI_MSB_FIRST:
			{
				bit_write(*registers.UCSRC, UDORD_BIT, 0);
				break;
			};

			case SPI_LSB_FIRST:
			{
				bit_write(*registers.UCSRC, UDORD_BIT, 1);
				break;
			};

			default:
				return SPI_CFG_FAILED;
		}

		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_speed(int16_t baud_rate)
	{
		// Unlike the hardware SPI peripheral, the MSPIM peripheral supports a configurable baud rate.
		// See Usart_imp::set_baud_rate() for calculations

		uint32_t ubrr = (((uint32_t)F_CPU / (baud_rate * 2)) - 1); // K = 2
		if (ubrr > 65535)
			return SPI_CFG_FAILED;

		if (enabled())
		{
			// UBRR can be set immediately if the module is already enabled
			*registers.UBRR = (uint16_t)ubrr;
		}

		// Otherwise it must be set after the module has been enabled
		this->ubrr = (uint16_t)ubrr;
		return SPI_CFG_SUCCESS;
	}

	Spi_config_status set_slave_select(Spi_slave_select_mode mode, IO_pin_address software_ss_pin)
	{
		// MSPIM doesn't support a hardware SS. It must be user controlled!
		if (mode == SPI_SS_HARDWARE)
			return SPI_CFG_FAILED;

		return Spi_imp::set_slave_select(mode, software_ss_pin);
	}

	int16_t transfer(uint8_t tx_data)
	{
		// TODO
		return -1;
	}

	Spi_io_status transfer_async(uint8_t tx_data, uint8_t *rx_data = NULL, spi_data_callback_t done = NULL)
	{
		// TODO
		return SPI_IO_FAILED;
	}

	Spi_io_status transfer_buffer(uint8_t *tx_data, uint8_t *rx_data, size_t size)
	{
		// TODO
		return SPI_IO_FAILED;
	}

	Spi_io_status transfer_buffer_async(uint8_t *tx_data, uint8_t *rx_data, size_t size, spi_data_callback_t done = NULL)
	{
		// TODO
		return SPI_IO_FAILED;
	}

	bool transfer_busy(void)
	{
		// TODO
		return false;
	}

	Spi_io_status get_status(void)
	{
		// TODO
		return SPI_IO_FAILED;
	}

	// Fields

	Usart_registers registers;

	uint16_t ubrr; // delayed ubrr
};
#endif

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

#ifdef USE_SPI_USART

#ifdef USE_USART0
//extern Usart_imp usart0_imp;
static Usartspi_imp usartspi0_imp = Usartspi_imp(
	USARTSPI_0,
	(Spi_pins) {
		.miso = _IOADDR(USART0_RX_PORT, USART0_RX_PIN),
		.mosi = _IOADDR(USART0_TX_PORT, USART0_TX_PIN),
		.sck  = _IOADDR(USART0_XCK_PORT, USART0_XCK_PIN),
		// No SS pin
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR    = &UDR0,
		.UCSRA  = &UCSR0A,
		.UCSRB  = &UCSR0B,
		.UCSRC  = &UCSR0C,
		.UBRR   = &UBRR0
	}
);
#endif

#ifdef USE_USART1
static Usartspi_imp usartspi1_imp = Usartspi_imp(
	USARTSPI_1,
	(Spi_pins) {
		.miso = _IOADDR(USART1_RX_PORT, USART1_RX_PIN),
		.mosi = _IOADDR(USART1_TX_PORT, USART1_TX_PIN),
		.sck  = _IOADDR(USART1_XCK_PORT, USART1_XCK_PIN),
		// No SS pin
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR    = &UDR1,
		.UCSRA  = &UCSR1A,
		.UCSRB  = &UCSR1B,
		.UCSRC  = &UCSR1C,
		.UBRR   = &UBRR1
	}
);
#endif

#ifdef USE_USART2
static Usartspi_imp usartspi2_imp = Usartspi_imp(
	USARTSPI_2,
	(Spi_pins) {
		.miso = _IOADDR(USART2_RX_PORT, USART2_RX_PIN),
		.mosi = _IOADDR(USART2_TX_PORT, USART2_TX_PIN),
		.sck  = _IOADDR(USART2_XCK_PORT, USART2_XCK_PIN),
		// No SS pin
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR    = &UDR2,
		.UCSRA  = &UCSR2A,
		.UCSRB  = &UCSR2B,
		.UCSRC  = &UCSR2C,
		.UBRR   = &UBRR2
	}
);
#endif

#ifdef USE_USART3
static Usartspi_imp usartspi3_imp = Usartspi_imp(
	USARTSPI_3,
	(Spi_pins) {
		.miso = _IOADDR(USART3_RX_PORT, USART3_RX_PIN),
		.mosi = _IOADDR(USART3_TX_PORT, USART3_TX_PIN),
		.sck  = _IOADDR(USART3_XCK_PORT, USART3_XCK_PIN),
		// No SS pin
	},
	(Usart_registers) {
		// Registers are defined in <avr/io.h>
		.UDR    = &UDR3,
		.UCSRA  = &UCSR3A,
		.UCSRB  = &UCSR3B,
		.UCSRC  = &UCSR3C,
		.UBRR   = &UBRR3
	}
);
#endif

#endif // USE_SPI_USART

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

	#ifdef USE_SPI_USART
		#ifdef USE_USART0
		case USARTSPI_0:
			return Spi(&usartspi0_imp);
		#endif

		#ifdef USE_USART1
		case USARTSPI_1:
			return Spi(&usartspi1_imp);
		#endif

		#ifdef USE_USART2
		case USARTSPI_2:
			return Spi(&usartspi2_imp);
		#endif

		#ifdef USE_USART3
		case USARTSPI_3:
			return Spi(&usartspi3_imp);
		#endif
	#endif

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
