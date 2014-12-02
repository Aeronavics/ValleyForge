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
 *  FILE: 		Usart.cpp	
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 * 
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	17-01-2012
 *
 *	Functionality to provide implementation for USART/UART in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal/hal.hpp"
#include "hal/gpio.hpp"
#include "hal/usart.hpp"

// DEFINE PRIVATE MACROS.

#if defined(USE_USART_LIN) && defined(USE_USART0)
	// NOTE - The LIN-USART is defined as channel USART_0.
	//  I don't think there are any chips that have both available.
	#error "USART0 conflicts with LIN-USART peripheral"
#endif

// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

// A structure containing the register definitions for a single USART channel.
typedef struct
{
	volatile uint8_t* UDR;
	volatile uint8_t* UCSRA;
	volatile uint8_t* UCSRB;
	volatile uint8_t* UCSRC;
	volatile uint16_t* UBRR;
} Usart_registers;

 // A structure to contain the IO pin addresses representing the peripheral pins for a single USART channel.
typedef struct
{
	IO_pin_address tx_address;
	IO_pin_address rx_address;
	IO_pin_address xck_address;
} Usart_pins;

/**
 * Private, target specific implementation class for public Usart class.
 */
class Usart_imp
{
public:

	// Methods - These methods should generally correspond to methods of the public class Usart.

	Usart_imp(Usart_channel channel, Usart_pins pins, Usart_registers registers)
		: channel(channel), pins(pins), registers(registers) { }

	~Usart_imp(void) { }

	// Called whenever someone binds to this instance
	void bind(void);

	// Called whenever someone is finished with this instance
	void unbind(void);


	void enable(void);

	void disable(void);


	Usart_config_status configure(Usart_setup_mode mode, Usart_baud_rate baud_rate, uint8_t data_bits = 8, Usart_parity parity = USART_PARITY_NONE, uint8_t stop_bits = 1);


	bool transmitter_ready(void);

	bool receiver_has_data(void);


	Usart_io_status transmit_byte(uint8_t data);

	Usart_io_status transmit_byte_async(uint8_t data);

	Usart_io_status transmit_buffer(uint8_t* data, size_t size);

	Usart_io_status transmit_buffer_async(uint8_t* data, size_t size, usarttx_callback_t cb_done = NULL);

	Usart_io_status transmit_string(char *data, size_t max_len);

	Usart_io_status transmit_string_async(char *data, size_t max_len, usarttx_callback_t cb_done = NULL);


	int16_t receive_byte(void);

	int16_t receive_byte_async(void);


	Usart_io_status receive_buffer(uint8_t *buffer, size_t size);

	Usart_io_status receive_buffer_async(uint8_t *buffer, size_t size, usartrx_callback_t received);

	Usart_io_status receive_string(char *buffer, size_t max_len, size_t* actual_size = NULL);

	Usart_io_status receive_string_async(char *buffer, size_t max_len, usartrx_callback_t received);


	void enable_interrupts(void);

	void disable_interrupts(void);

	Usart_int_status attach_interrupt(Usart_interrupt_type interrupt, callback_t callback);

	Usart_int_status detach_interrupt(Usart_interrupt_type interrupt);

	Usart_error_type get_errors(void);

	void usart_clear_errors(void);





	Usart_config_status set_mode(Usart_setup_mode mode);

	Usart_config_status set_framing(uint8_t data_bits, Usart_parity parity, uint8_t stop_bits);

	Usart_config_status set_baud_rate(Usart_baud_rate baud_rate);


	// Fields

	Usart_setup_mode mode;


	Usart_channel channel;

	Usart_pins pins;

	Usart_registers registers;


	callback_t tx_isr;
	callback_t rx_isr;
	callback_t udre_isr;

private:

	// Methods

	Usart_imp(void);	// Poisoned.

	Usart_imp(Usart_imp*);	// Poisoned.

};

// DECLARE PRIVATE GLOBAL VARIABLES.

// NOTE - Because the ISRs need to access the usart implementation instances,
//  we need to store pointers to them here.
// These pointers are populated the first time Usart::bind() is called.

#ifdef USE_USART0
static Usart_imp *usart0_imp = NULL;
#endif

#ifdef USE_USART1
static Usart_imp *usart1_imp = NULL;
#endif

#ifdef USE_USART2
static Usart_imp *usart2_imp = NULL;
#endif

#ifdef USE_USART3
static Usart_imp *usart3_imp = NULL;
#endif

#ifdef USE_USART_LIN
// TODO
#endif

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

// Usart.

Usart::Usart(Usart_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;
	imp->bind();
}

Usart Usart::bind(Usart_channel channel)
{
	// Acquire access to the implementation instance.
	// TODO: What do we do if this fails, or if someone has already binded to the instance??


	// NOTE - Instead of hard-coding specific AVR chips,
	// we use constants defined in <target_config.hpp> to specify which
	// peripherals are present, and which channel corresponds to each peripheral.

	// NOTE - By defining static variables in here, the instances aren't
	// instantiated until required, thus saving valuable memory.

	// TODO - Check thread-safety of this. It is only guaranteed to be thread-safe under C++11??

	switch (channel)
	{

#if defined(USE_USART0) // Most AVR chips have a USART 0
		case USE_USART0:
		{
			static Usart_imp imp = Usart_imp(
				USE_USART0, // Channel
				(Usart_pins) {
					// Pins are defined in <target_config.hpp>
					.tx_address  = _IOADDR(USART0_TX_PORT, USART0_TX_PIN),
					.rx_address  = _IOADDR(USART0_RX_PORT, USART0_RX_PIN),
					.xck_address = _IOADDR(USART0_XCK_PORT, USART0_XCK_PIN)
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
			usart0_imp = &imp;
			return Usart(&imp);
		}
#endif

#if defined(USE_USART1) // Some AVR chips have multiple USARTs
		case USE_USART1:
		{
			static Usart_imp imp = Usart_imp(
				USE_USART1, // Channel
				(Usart_pins) {
					// Pins are defined in <target_config.hpp>
					.tx_address  = _IOADDR(USART1_TX_PORT, USART1_TX_PIN),
					.rx_address  = _IOADDR(USART1_RX_PORT, USART1_RX_PIN),
					.xck_address = _IOADDR(USART1_XCK_PORT, USART1_XCK_PIN)
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
			usart1_imp = &imp;
			return Usart(&imp);
		}
#endif

#if defined(USE_USART2)
		case USE_USART2:
		{
			static Usart_imp imp = Usart_imp(
				USE_USART2, // Channel
				(Usart_pins) {
					// Pins are defined in <target_config.hpp>
					.tx_address  = _IOADDR(USART2_TX_PORT, USART2_TX_PIN),
					.rx_address  = _IOADDR(USART2_RX_PORT, USART2_RX_PIN),
					.xck_address = _IOADDR(USART2_XCK_PORT, USART2_XCK_PIN)
				},
				(Usart_registers) {
					// Registers are defined in <avr/io.h>
					.UDR	= &UDR2,
					.UCSRA	= &UCSR2A,
					.UCSRB	= &UCSR2B,
					.UCSRC	= &UCSR2C,
					.UBRR	= &UBRR2
				}
			);
			usart2_imp = &imp;
			return Usart(&imp);
		}
#endif

#if defined(USE_USART3)
		case USE_USART3:
		{
			static Usart_imp imp = Usart_imp(
				USE_USART3, // Channel
				(Usart_pins) {
					// Pins are defined in <target_config.hpp>
					.tx_address  = _IOADDR(USART3_TX_PORT, USART3_TX_PIN),
					.rx_address  = _IOADDR(USART3_RX_PORT, USART3_RX_PIN),
					.xck_address = _IOADDR(USART3_XCK_PORT, USART3_XCK_PIN)
				},
				(Usart_registers) {
					// Registers are defined in <avr/io.h>
					.UDR	= &UDR3,
					.UCSRA	= &UCSR3A,
					.UCSRB	= &UCSR3B,
					.UCSRC	= &UCSR3C,
					.UBRR	= &UBRR3
				}
			);
			usart3_imp = &imp;
			return Usart(&imp);
		}
#endif

#if defined(USE_USART_LIN) // ATmega32M1/C1 chips only have LIN
		#error USART-LIN not yet implemented!

		case USE_USART_LIN:
		{
			//TODO - Create Usart_lin_imp class descended from Usart_imp class
			// NOTE the use of 'Usart_lin_imp' instead of 'Usart_imp' : It is a completely different implementation!
			static Usart_lin_imp imp = Usart_lin_imp(
				USE_USART_LIN, // Channel
				(Usart_pins) {
					// Pins are defined in <target_config.hpp>
					.tx_address  = _IOADDR(USARTLIN_TX_PORT, USARTLIN_TX_PIN),
					.rx_address  = _IOADDR(USARTLIN_RX_PORT, USARTLIN_RX_PIN),
					.xck_address = _IOADDR(USARTLIN_XCK_PORT, USARTLIN_XCK_PIN)
				}
			);
			usart_lin_imp = &imp;
			return Usart(&imp);
		}
#endif

	} // end-switch

	// If we make it to here, then something has gone very wrong (like the user maliciously cast an invalid value into a channel number).

	// Loop forever, which hopefully reboots the micro so we have a chance to recover.
	while (true)
	{
		// Consider the bad life choices that have led us to this point.
	}

	// We'll never get here.
	return Usart(static_cast<Usart_imp*>(NULL));
}

Usart::~Usart(void)
{
	imp->unbind();
}

void Usart::unbind()
{
	// Relinquish access to the implemenation instance.
	imp->unbind();
}

void Usart::enable()
{
	imp->enable();
}

void Usart::disable()
{
	imp->disable();
}

Usart_config_status Usart::configure(Usart_setup_mode mode, Usart_baud_rate baud_rate, uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	return imp->configure(mode, baud_rate, data_bits, parity, stop_bits);
}

bool Usart::transmitter_ready()
{
	return imp->transmitter_ready();
}

bool Usart::receiver_has_data()
{
	return imp->receiver_has_data();
}

Usart_io_status Usart::transmit_byte(uint8_t data)
{
	return imp->transmit_byte(data);
}

Usart_io_status Usart::transmit_byte_async(uint8_t data)
{
	return imp->transmit_byte_async(data);
}

Usart_io_status Usart::transmit_buffer(uint8_t *data, size_t size)
{
	return imp->transmit_buffer(data, size);
}

Usart_io_status Usart::transmit_buffer_async(uint8_t *data, size_t size, usarttx_callback_t cb_done)
{
	return imp->transmit_buffer_async(data, size, cb_done);
}

Usart_io_status Usart::transmit_string(char *data, size_t max_len)
{
	return imp->transmit_string(data, max_len);
}

Usart_io_status Usart::transmit_string_async(char *data, size_t max_len, usarttx_callback_t cb_done)
{
	return imp->transmit_string_async(data, max_len, cb_done);
}

int16_t Usart::receive_byte(void)
{
	return imp->receive_byte();
}

int16_t Usart::receive_byte_async(void)
{
	return imp->receive_byte_async();
}

Usart_io_status Usart::receive_buffer(uint8_t *data, size_t size)
{
	return imp->receive_buffer(data, size);
}

Usart_io_status Usart::receive_buffer_async(uint8_t *data, size_t size, usartrx_callback_t cb_done)
{
	return imp->receive_buffer_async(data, size, cb_done);
}

Usart_io_status Usart::receive_string(char *buffer, size_t max_len, size_t *actual_size)
{
	return imp->receive_string(buffer, max_len, actual_size);
}

Usart_io_status Usart::receive_string_async(char *string, size_t max_len, usartrx_callback_t cb_done)
{
	return imp->receive_string_async(string, max_len, cb_done);
}

void Usart::enable_interrupts()
{
	imp->enable_interrupts();
}

void Usart::disable_interrupts()
{
	imp->enable_interrupts();
}

Usart_int_status Usart::attach_interrupt(Usart_interrupt_type type, callback_t callback)
{
	return imp->attach_interrupt(type, callback);
}

Usart_int_status Usart::detach_interrupt(Usart_interrupt_type type)
{
	return imp->detach_interrupt(type);
}

Usart_error_type Usart::usart_error(void)
{
	return imp->get_errors();
}

void Usart::usart_clear_errors()
{
	imp->get_errors();
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).

// Usart.

void Usart_imp::bind(void)
{
	// Enable the peripheral, if required

	// Acquire access to the pins, and configure them as required.
	// TODO - How can we dynamically bind GPIO pins??

	disable(); // Start disabled, so the module can be configured safely
}

void Usart_imp::unbind(void)
{
	disable();

	// Relinquish access to the GPIO pins
	//pins.tx.unbind(); // TODO
}

void Usart_imp::enable(void)
{
	// Enable transceiver hardware
	*registers.UCSRB |= _BV(RXEN_BIT) | _BV(TXEN_BIT);
}

void Usart_imp::disable(void)
{
	// Disable transceiver hardware
	*registers.UCSRB &= ~(_BV(RXEN_BIT) | _BV(TXEN_BIT));

	// NOTE - Transmitter is not disabled instantly.
	//  It will continue finishing any current transmission before disabling.

	// Disabling the receiver also flushes the UDR receive buffer.
}


Usart_config_status Usart_imp::configure(Usart_setup_mode mode, Usart_baud_rate baud_rate, uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	Usart_config_status result = USART_CFG_FAILED;

	// Disable tx/rx before configuring
	disable();

	// Set the operating mode (Async/Sync)
	result = set_mode(mode);
	if (result != USART_CFG_SUCCESS)
		return result;

	// Configure the framing
	result = set_framing(data_bits, parity, stop_bits);
	if (result != USART_CFG_SUCCESS)
		return result;

	// Configure the baud rate
	result = set_baud_rate(baud_rate);
	if (result != USART_CFG_SUCCESS)
		return result;

	// Enable tx/rx
	enable();

	return USART_CFG_SUCCESS;
}

Usart_config_status Usart_imp::set_mode(Usart_setup_mode mode)
{
	switch (mode)
	{
		case USART_MODE_ASYNCHRONOUS:
		case USART_MODE_ASYNCHRONOUS_DOUBLESPEED:
		{
			// UMSEL<1:0> = 0b00 (Asynchronous mode)
			*registers.UCSRC =
				(*registers.UCSRC & ~UMSEL_MASK) | (0b00 << UMSEL0_BIT);

			// Enable double-speed mode
			if (mode == USART_MODE_ASYNCHRONOUS_DOUBLESPEED)
				*registers.UCSRA |= _BV(U2X_BIT);

			break;
		}

		case USART_MODE_SYNCHRONOUS_MASTER:
		case USART_MODE_SYNCHRONOUS_SLAVE:
		{
			// UMSEL<1:0> = 0b01 (Synchronous mode)
			*registers.UCSRC =
				(*registers.UCSRC & ~UMSEL_MASK) | (0b01 << UMSEL0_BIT);

			// For synchronous mode, clear the double USART transmission speed bit
			*registers.UCSRA &= ~_BV(U2X_BIT);

			// Configure the GPIO
			// TODO - Avoid having to instantiate the pin every time we want to use it!
			Gpio_pin xck(pins.xck_address);

			// Master/slave is defined by the direction of the XCK pin
			if (mode == USART_MODE_SYNCHRONOUS_MASTER)
				xck.set_mode(GPIO_OUTPUT_PP);
			else
				xck.set_mode(GPIO_INPUT_FL);

			break;
		}

		// Unsupported configuration
		default:
			return USART_CFG_INVALID_MODE;
	}
	Usart_imp::mode = mode;

	return USART_CFG_SUCCESS;
}

Usart_config_status Usart_imp::set_framing(uint8_t data_bits, Usart_parity parity, uint8_t stop_bits)
{
	// Data bits
	if ((data_bits < 5) || (data_bits > 9))
		return USART_CFG_INVALID_DATA_BITS;

	if (data_bits == 9)
	{
		// UCSZ = 0b100
		*registers.UCSRB |= _BV(UCSZ2_BIT);
		*registers.UCSRC &= ~(_BV(UCSZ1_BIT) | _BV(UCSZ0_BIT));
	}
	else // (data_bits <= 8)
	{
		// UCSZ = 0b0xx
		uint8_t ucsz = (data_bits - 5);

		*registers.UCSRB &= ~_BV(UCSZ2_BIT); // regular mode
		*registers.UCSRC =
			(*registers.UCSRC & ~(_BV(UCSZ1_BIT) | _BV(UCSZ0_BIT)))
			| (ucsz << UCSZ0_BIT);
	}

	// Parity
	uint8_t upm;
	switch (parity)
	{
		case USART_PARITY_EVEN:
			upm = 0b10u;
			break;

		case USART_PARITY_ODD:
			upm = 0b11u;
			break;

		case USART_PARITY_NONE:
			upm = 0b00u;
			break;

		default: // Unsupported parity mode
			return USART_CFG_INVALID_PARITY;
	}
	*registers.UCSRC =
		(*registers.UCSRC & ~(_BV(UPM1_BIT) | _BV(UPM0_BIT)))
		| (upm << UPM0_BIT);

	// Stop bits
	switch (stop_bits)
	{
		case 1:
			*registers.UCSRC &= ~_BV(USBS_BIT);
			break;

		case 2:
			*registers.UCSRC |= _BV(USBS_BIT);
			break;

		default: // Invalid number of stop bits
			return USART_CFG_INVALID_STOP_BITS;
	}

	return USART_CFG_SUCCESS;
}

Usart_config_status Usart_imp::set_baud_rate(Usart_baud_rate baud_rate)
{
	// Calculate the Baud value required for the user provided Baud rate
	// Baud value = F_CPU			- 1
	// 		     --------------------
	// 		     (User_Baud_rate * K)
	//
	// Where K varies depending on which mode the USART is set to.
	//
	// Asynchronous mode (U2Xn = 0)	K = 16
	// Asynchronous mode (U2Xn = 1)	K = 8
	// Synchronous Master mode		K = 2

	uint32_t K;

	if (mode == USART_MODE_ASYNCHRONOUS)
		K = 16UL;
	else if (mode == USART_MODE_ASYNCHRONOUS_DOUBLESPEED)
		K = 8UL;
	else if (mode == USART_MODE_SYNCHRONOUS_MASTER || mode == USART_MODE_SYNCHRONOUS_SLAVE)
		K = 2UL;
	else
		return USART_CFG_INVALID_MODE;

	// Set the UBBR value according to the equation above
	*registers.UBRR = (((F_CPU / (baud_rate * K))) - 1); // TODO - Possible overflow here

	// TODO - Range checking of baud rate values

	return USART_CFG_SUCCESS;
}

bool Usart_imp::transmitter_ready(void)
{
	// Check if we're ready to transmit more data
	return ((*registers.UCSRA & _BV(UDRE_BIT)) != 0);
}

bool Usart_imp::receiver_has_data(void)
{
	return (*registers.UCSRA & _BV(RXC_BIT)) != 0;
}

Usart_io_status Usart_imp::transmit_byte(uint8_t data)
{
	while (!transmitter_ready())
	{
		// Wait for transmit buffer to be empty
	}

	// 9 bit mode
	if (*registers.UCSRB & _BV(UCSZ2_BIT))
	{
		uint8_t bit8 = 0; // TODO - How to feed in the 9th bit?
		*registers.UCSRB = (*registers.UCSRB & ~_BV(TXB8_BIT)) | bit8;
	}

	*registers.UDR = data;

	// We don't need to wait for it to finish, since the next time
	// this function is called it will wait until the TX buffer is free again.

	//while (((*registers.UCSRA & _BV(TXC_BIT)) == 0)) {}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_byte_async(uint8_t data)
{
	if (transmitter_ready())
	{
		// 9 bit mode
		if (*registers.UCSRB & _BV(UCSZ2_BIT))
		{
			uint8_t bit8 = 0; // TODO - How to feed in the 9th bit?
			*registers.UCSRB = (*registers.UCSRB & ~_BV(TXB8_BIT)) | bit8;
		}

		*registers.UDR = data;

		return USART_IO_SUCCESS;
	}
	else
	{
		return USART_IO_BUSY;
	}
}

Usart_io_status Usart_imp::transmit_buffer(uint8_t *data, size_t size)
{
	if (!transmitter_ready())
		return USART_IO_BUSY;

	for (size_t i = 0; i < size; i++)
	{
		transmit_byte(*data++);
	}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_buffer_async(uint8_t *data, size_t size, usarttx_callback_t cb_done)
{
	// TODO - This.

	// Store *data and size in the instance
	// Store the callback
	// Configure ISR state machine or DMA to start sending the data

	// If using DMA, configure interrupt?
	// If using ISR state machine, it should call the callback when it is finished.

	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::transmit_string(char *string, size_t max_len)
{
	if (!transmitter_ready())
		return USART_IO_BUSY;

	while (*string)
	{
		transmit_byte((uint8_t)*string++);
	}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::transmit_string_async(char *string, size_t max_len, usarttx_callback_t cb_done)
{
	// TODO - This.

	// Store *string and max_len in the instance
	// Store the callback

	// If using DMA, we need to compute the actual length of the string
	//size_t string_len = strlen(string);
	// otherwise, the ISR state machine will just send bytes until it
	// finds the null character or reaches max_len.

	return USART_IO_FAILED;
}

int16_t Usart_imp::receive_byte(void)
{
	while (!receiver_has_data())
	{
		// Wait for data
	}

	// Errors must be read before UDR
	Usart_error_type error = get_errors();
	if (error != USART_ERR_NONE)
		return error;

	// 9 bit mode
	if (*registers.UCSRB & _BV(UCSZ2_BIT))
	{
		uint8_t bit8 = (*registers.UCSRB & _BV(RXB8_BIT)) >> RXB8_BIT;
		return (bit8 << 8) | (*registers.UDR);
	}

	return *registers.UDR;
}

int16_t Usart_imp::receive_byte_async(void)
{
	if (receiver_has_data())
	{
		// Errors must be read before UDR
		Usart_error_type error = get_errors();
		if (error != USART_ERR_NONE)
			return error;

		// 9 bit mode
		if (*registers.UCSRB & _BV(UCSZ2_BIT))
		{
			uint8_t bit8 = (*registers.UCSRB & _BV(RXB8_BIT)) >> RXB8_BIT;
			return (bit8 << 8) | (*registers.UDR);
		}

		return *registers.UDR;
	}
	else
		return USART_IO_NODATA;
}

Usart_io_status Usart_imp::receive_buffer(uint8_t *buffer, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		*buffer = (uint8_t)receive_byte();
		buffer++;
	}

	return USART_IO_SUCCESS;
}

Usart_io_status Usart_imp::receive_buffer_async(uint8_t *buffer, size_t size, usartrx_callback_t cb_done)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::receive_string(char *buffer, size_t max_len, size_t *actual_size)
{
	size_t i = 0;
	char c;

	// Provide room for a null terminator
	max_len -= 1;

	// Read characters until a null char is received or we reach max_len chars.
	do
	{
		c = (char)receive_byte();
		*buffer = c;
		buffer++;
		i++;
	}
	while ((i < max_len) && (c != '\0'));

	// Check to see if we've reached the maximum allowable string length
	if (i == max_len)
	{
		*buffer = '\0'; // Force null termination
		return USART_IO_STRING_TRUNCATED;
	}

	return USART_IO_SUCCESS;
};

Usart_io_status Usart_imp::receive_string_async(char *string, size_t max_len, usartrx_callback_t cb_done)
{
	// TODO - This.
	return USART_IO_FAILED;
}
		
void Usart_imp::enable_interrupts(void)
{
	if (tx_isr != NULL)
		*registers.UCSRB |= _BV(TXCIE_BIT);

	if (rx_isr != NULL)
		*registers.UCSRB |= _BV(RXCIE_BIT);

	// TODO - Does it make sense to re-enable UDRIE?
	if (udre_isr != NULL)
		*registers.UCSRB |= _BV(UDRIE_BIT);
}

void Usart_imp::disable_interrupts(void)
{
	if (tx_isr != NULL)
		*registers.UCSRB &= ~_BV(TXCIE_BIT);

	if (rx_isr != NULL)
		*registers.UCSRB &= ~_BV(RXCIE_BIT);

	if (udre_isr != NULL)
		*registers.UCSRB &= ~_BV(UDRIE_BIT);
}

Usart_int_status Usart_imp::attach_interrupt(Usart_interrupt_type type, callback_t callback)
{
	switch (type)
	{
		case USART_INT_TX_COMPLETE:
		{
			if (tx_isr != NULL)
				return USART_INT_INUSE;

			tx_isr = callback;
			*registers.UCSRB |= _BV(TXCIE_BIT);

			break;
		};

		case USART_INT_RX_COMPLETE:
		{
			if (rx_isr != NULL)
				return USART_INT_INUSE;

			rx_isr = callback;
			*registers.UCSRB |= _BV(RXCIE_BIT);

			break;
		};

		case USART_INT_TX_READY:
		{
			if (udre_isr != NULL)
				return USART_INT_INUSE;

			udre_isr = callback;
			*registers.UCSRB |= _BV(UDRIE_BIT);
			// TODO - Setting UDRIE actually triggers the interrupt according to the datasheet ??
			//  so we should delay setting this until we actually require it.

			break;
		};

		// Unsupported interrupt type
		default:
			return USART_INT_FAILED;
	}

	return USART_INT_SUCCESS;
}

Usart_int_status Usart_imp::detach_interrupt(Usart_interrupt_type type)
{
	// Make sure to disable interrupts before we go modifying the ISR pointers!
	cli();

	switch (type)
	{
		case USART_INT_TX_COMPLETE:
		{
			// NOTE - No need to check if it's already cleared.
			tx_isr = NULL;
			*registers.UCSRB &= ~_BV(TXCIE_BIT);
			break;
		};

		case USART_INT_RX_COMPLETE:
		{
			rx_isr = NULL;
			*registers.UCSRB &= ~_BV(RXCIE_BIT);
			break;
		};

		case USART_INT_TX_READY:
		{
			udre_isr = NULL;
			*registers.UCSRB &= ~_BV(UDRIE_BIT);
			break;
		};

		// Unsupported interrupt type
		default:
		{
			sei();
			return USART_INT_FAILED;
		}
	}

	sei();
	return USART_INT_SUCCESS;
}
		 
Usart_error_type Usart_imp::get_errors(void)
{
	if ((*registers.UCSRA & _BV(FE_BIT)) != 0)
		return USART_ERR_FRAME;
	if ((*registers.UCSRA & _BV(DOR_BIT)) != 0)
		return USART_ERR_DATA_OVERRUN;
	if ((*registers.UCSRA & _BV(UPE_BIT)) != 0)
		return USART_ERR_PARITY;

	return USART_ERR_NONE;
}

void Usart_imp::usart_clear_errors()
{
	// TODO - This.
}


/** Declare the ISRptrs
 * 
 * Each USART interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs which are contained within the specific USART implementation.
 *
 * Note that the usartX_imp pointers are guaranteed to be non-NULL because the ISRs
 * are not enabled until after the pointer has been set. (see: Usart::bind() and Usart::attach_interrupt())
 * */

#ifdef USE_USART0
ISR(USART0_RX_vect)
{
	// The RXC flag is automatically cleared when UDR is read

	// TODO - Process async RX data here

	if (usart0_imp->rx_isr)
		usart0_imp->rx_isr();
	
	// Clear the RXC flag in UCSRA as a safeguard
	UCSR0A &= _BV(RXC_BIT);
}

ISR(USART0_TX_vect)
{
	// This interrupt is triggered only when the transmission is complete
	// and there is no new data to be sent

	if (usart0_imp->tx_isr)
		usart0_imp->tx_isr();

	// TXC flag is cleared automatically
}

ISR(USART0_UDRE_vect)
{
	// This interrupt must either load more data into UDR,
	// or disable the ISR, otherwise it will keep getting called!

	bool finished = true;

	// TODO - Process async TX data here

	// Call the user ISR, which can be used to load more data into UDR.
	// The callback should return a bool, which should be set to true
	// when the user has no more data to send.
	if (usart0_imp->udre_isr)
	{
		finished = (bool)usart0_imp->udre_isr();
	}

	// Disable the ISR when there is no more data to be sent
	if (finished)
	{
		UCSR0B &= ~_BV(UDRIE_BIT);
	}
}
#endif

#ifdef USE_USART1
ISR(USART1_RX_vect)
{
	// The RXC flag is automatically cleared when UDR is read

	// TODO - Process async RX data here

	if (usart1_imp->rx_isr)
		usart1_imp->rx_isr();
	
	// Clear the RXC flag in UCSRA as a safeguard
	UCSR1A &= _BV(RXC_BIT);
}

ISR(USART1_TX_vect)
{
	// This interrupt is triggered only when the transmission is complete
	// and there is no new data to be sent

	if (usart1_imp->tx_isr)
		usart1_imp->tx_isr();

	// TXC flag is cleared automatically
}

ISR(USART1_UDRE_vect)
{
	// This interrupt must either load more data into UDR,
	// or disable the ISR, otherwise it will keep getting called!

	bool finished = true;

	// TODO - Process async TX data here

	// Call the user ISR, which can be used to load more data into UDR.
	// The callback should return a bool, which should be set to true
	// when the user has no more data to send.
	if (usart1_imp->udre_isr)
	{
		finished = (bool)usart1_imp->udre_isr();
	}

	// Disable the ISR when there is no more data to be sent
	if (finished)
	{
		UCSR1B &= ~_BV(UDRIE_BIT);
	}
}
#endif

#ifdef USE_USART2
ISR(USART2_RX_vect)
{
	// The RXC flag is automatically cleared when UDR is read

	// TODO - Process async RX data here

	if (usart2_imp->rx_isr)
		usart2_imp->rx_isr();
	
	// Clear the RXC flag in UCSRA as a safeguard
	UCSR2A &= _BV(RXC_BIT);
}

ISR(USART2_TX_vect)
{
	// This interrupt is triggered only when the transmission is complete
	// and there is no new data to be sent

	if (usart2_imp->tx_isr)
		usart2_imp->tx_isr();

	// TXC flag is cleared automatically
}

ISR(USART2_UDRE_vect)
{
	// This interrupt must either load more data into UDR,
	// or disable the ISR, otherwise it will keep getting called!

	bool finished = true;

	// TODO - Process async TX data here

	// Call the user ISR, which can be used to load more data into UDR.
	// The callback should return a bool, which should be set to true
	// when the user has no more data to send.
	if (usart2_imp->udre_isr)
	{
		finished = (bool)usart2_imp->udre_isr();
	}

	// Disable the ISR when there is no more data to be sent
	if (finished)
	{
		UCSR2B &= ~_BV(UDRIE_BIT);
	}
}
#endif

#ifdef USE_USART3
ISR(USART3_RX_vect)
{
	// The RXC flag is automatically cleared when UDR is read

	// TODO - Process async RX data here

	if (usart3_imp->rx_isr)
		usart3_imp->rx_isr();
	
	// Clear the RXC flag in UCSRA as a safeguard
	UCSR3A &= _BV(RXC_BIT);
}

ISR(USART3_TX_vect)
{
	// This interrupt is triggered only when the transmission is complete
	// and there is no new data to be sent

	if (usart3_imp->tx_isr)
		usart3_imp->tx_isr();

	// TXC flag is cleared automatically
}

ISR(USART3_UDRE_vect)
{
	// This interrupt must either load more data into UDR,
	// or disable the ISR, otherwise it will keep getting called!

	bool finished = true;

	// TODO - Process async TX data here

	// Call the user ISR, which can be used to load more data into UDR.
	// The callback should return a bool, which should be set to true
	// when the user has no more data to send.
	if (usart3_imp->udre_isr)
	{
		finished = (bool)usart3_imp->udre_isr();
	}

	// Disable the ISR when there is no more data to be sent
	if (finished)
	{
		UCSR3B &= ~_BV(UDRIE_BIT);
	}
}
#endif

#ifdef USE_USART_LIN
// TODO - Which interrupts does the LIN module support?
#endif

// ALL DONE.
