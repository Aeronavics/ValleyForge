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

// DEFINE PRIVATE MACROS.

// SELECT NAMESPACES.

// DEFINE PRIVATE CLASSES, TYPES AND ENUMERATIONS.

// A structure containing the register definitions for a single USART channel.
typedef struct
{
	int16_t UDR;
	int16_t UCSRA;
	int16_t UCSRB;
	int16_t UCSRC;
	int16_t UBRR;
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

		Usart_imp(Usart_channel channel, Usart_pins pins, Usart_registers registers);
		
		~Usart_imp(void);

		Usart_config_status set_mode(Usart_setup_mode mode);

		Usart_config_status set_frame(uint8_t data_bits, Usart_parity parity, uint8_t start_bits, uint8_t stop_bits);
		
		Usart_config_status set_baud_rate(Usart_baud_rate rate);

		
		bool transmitter_ready(void);

		bool receiver_has_data(void);


		Usart_io_status transmit_byte(uint8_t data);

		Usart_io_status transmit_byte_blocking(uint8_t data);

		Usart_io_status transmit_buffer(uint8_t* data, size_t num_elements, usarttx_callback_t cb_done = NULL);

		Usart_io_status transmit_buffer_blocking(uint8_t* data, size_t num_elements);

		Usart_io_status transmit_string(uint8_t *data, usarttx_callback_t cb_done = NULL);

		Usart_io_status transmit_string_blocking(uint8_t *data);

		 
		int16_t receive_byte(void);

		int16_t receive_byte_blocking(void);

		Usart_io_status receive_buffer(uint8_t *buffer, size_t size, usartrx_callback_t received);

		Usart_io_status receive_buffer_blocking(uint8_t *buffer, size_t size);

		Usart_io_status receive_string(char *string, size_t max_size, usartrx_callback_t received);

		Usart_io_status receive_string_blocking(uint8_t *buffer, size_t size, size_t* actual_size = NULL);

		
		void enable_interrupts(void);

		void disable_interrupts(void);

		Usart_int_status attach_interrupt(Usart_interrupt_type interrupt, void(*callback)(void));

		Usart_int_status detach_interrupt(Usart_interrupt_type interrupt);
		 
		Usart_error_type usart_error(void);

		void usart_clear_errors(void);

 	private:

 		// Methods.

 		Usart_imp(void);	// Poisoned.

 		Usart_imp(Usart_imp*);	// Poisoned.

 		// Fields.

 		Usart_channel channel;

		Usart_pins pins;

		Usart_registers registers;
};

// Generic register definitions

// NOTE - Instead of hard-coding specific AVR chips,
// we use constants defined in <target_config.hpp> to specify which
// peripherals are present, and which channel corresponds to each peripheral.

#if defined(USE_USART0)
static Usart_imp usart_imp_0 = Usart_imp(USE_USART0, // Channel
	{
		// Pins are defined in <target_config.hpp>
		.tx_address={.port=USART0_TX_PORT, .pin=USART0_TX_PIN},
		.rx_address={.port=USART0_RX_PORT, .pin=USART0_RX_PIN},
		.xck_address={.port=USART0_XCK_PORT, .pin=USART0_XCK_PIN}
	},
	{
		// Registers are defined in <avr/io.h>
		.UDR = _SFR_MEM_ADDR(UDR0),
		.UCSRA = _SFR_MEM_ADDR(UCSR0A),
		.UCSRB = _SFR_MEM_ADDR(UCSR0B),
		.UCSRC = _SFR_MEM_ADDR(UCSR0C),
		.UBRR = _SFR_MEM_ADDR(UBRR0)
	}
);
#endif

#if defined(USE_USART1)
static Usart_imp usart_imp_1 = Usart_imp(USE_USART1, // Channel
	{
		// Pins are defined in <target_config.hpp>
		.tx_address={.port=USART1_TX_PORT, .pin=USART1_TX_PIN},
		.rx_address={.port=USART1_RX_PORT, .pin=USART1_RX_PIN},
		.xck_address={.port=USART1_XCK_PORT, .pin=USART1_XCK_PIN}
	},
	{
		// Registers are defined in <avr/io.h>
		.UDR = _SFR_MEM_ADDR(UDR1),
		.UCSRA = _SFR_MEM_ADDR(UCSR1A),
		.UCSRB = _SFR_MEM_ADDR(UCSR1B),
		.UCSRC = _SFR_MEM_ADDR(UCSR1C),
		.UBRR = _SFR_MEM_ADDR(UBRR1)
	}
);
#endif

#if defined(USE_USART2)
static Usart_imp usart_imp_2 = Usart_imp(USE_USART2, // Channel
	{
		// Pins are defined in <target_config.hpp>
		.tx_address={.port=USART2_TX_PORT, .pin=USART2_TX_PIN},
		.rx_address={.port=USART2_RX_PORT, .pin=USART2_RX_PIN},
		.xck_address={.port=USART2_XCK_PORT, .pin=USART2_XCK_PIN}
	},
	{
		// Registers are defined in <avr/io.h>
		.UDR = _SFR_MEM_ADDR(UDR2),
		.UCSRA = _SFR_MEM_ADDR(UCSR2A),
		.UCSRB = _SFR_MEM_ADDR(UCSR2B),
		.UCSRC = _SFR_MEM_ADDR(UCSR2C),
		.UBRR = _SFR_MEM_ADDR(UBRR2)
	}
);
#endif

#if defined(USE_USART3)
static Usart_imp usart_imp_3 = Usart_imp(USE_USART3, // Channel
	{
		// Pins are defined in <target_config.hpp>
		.tx_address={.port=USART3_TX_PORT, .pin=USART3_TX_PIN},
		.rx_address={.port=USART3_RX_PORT, .pin=USART3_RX_PIN},
		.xck_address={.port=USART3_XCK_PORT, .pin=USART3_XCK_PIN}
	},
	{
		// Registers are defined in <avr/io.h>
		.UDR = _SFR_MEM_ADDR(UDR3),
		.UCSRA = _SFR_MEM_ADDR(UCSR3A),
		.UCSRB = _SFR_MEM_ADDR(UCSR3B),
		.UCSRC = _SFR_MEM_ADDR(UCSR3C),
		.UBRR = _SFR_MEM_ADDR(UBRR3)
	}
);
#endif

#if defined(USE_USART_LIN)
//TODO - Create Usart_lin_imp class descended from Usart_imp class
// NOTE the use of 'Usart_lin_imp' instead of 'Usart_imp' : It is a completely different implementation!
static Usart_lin_imp usart_imp_lin = Usart_lin_imp(USE_USART_LIN, // Channel
	{
		// Pins are defined in <target_config.hpp>
		.tx_address={.port=USARTLIN_TX_PORT, .pin=USARTLIN_TX_PIN},
		.rx_address={.port=USARTLIN_RX_PORT, .pin=USARTLIN_RX_PIN},
		.xck_address={.port=USARTLIN_XCK_PORT, .pin=USARTLIN_XCK_PIN}
	},
	{
		// Registers are defined in <avr/io.h>
		//TODO - LIN registers
	}
);
#endif

#if defined(USE_USART_LIN) && defined(USE_USART0)
	// NOTE - The LIN-USART is defined as channel USART_0.
	//  I don't think there are any chips that have both available.
	#error "USART0 conflicts with LIN-USART peripheral"
#endif


// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE STATIC FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

// IMPLEMENT PUBLIC CLASS FUNCTIONS (METHODS).

// Usart.

Usart::Usart(Usart_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

Usart::~Usart(void)
{
	// Some targets need to make calls to imp when falling out of scope, AVR doesn't, so do nothing.

	// All done.
	return;
}

Usart Usart::bind(Usart_channel channel)
{
	// *** TARGET CONFIGURATION SPECIFIC.

	// *** TARGET AGNOSTIC.

	switch (channel)
	{
		// ATmega32M1/C1 chips
		#ifdef USE_USART_LIN
		case USE_USART_LIN:
			return Usart(&usart_imp_lin);
		#endif

		// Most AVR chips
		#ifdef USE_USART0
		case USE_USART0:
			return Usart(&usart_imp_0);
		#endif

		// Some AVR chips have extra USARTs
		#ifdef USE_USART1
		case USE_USART1:
			return Usart(&usart_imp_1);
		#endif

		#ifdef USE_USART2
		case USE_USART2:
			return Usart(&usart_imp_2);
		#endif

		#ifdef USE_USART3
		case USE_USART3:
			return Usart(&usart_imp_3);
		#endif
	}

	// If we make it to here, then something has gone very wrong (like the user maliciously cast an invalid value into a channel number).

	// Loop forever, which hopefully reboots the micro so we have a chance to recover.
	while (true)
	{
		// Consider the bad life choices that have led us to this point.
	}


	// We''ll never get here.
	return Usart(static_cast<Usart_imp*>(NULL));
}

Usart_config_status Usart::set_mode(Usart_setup_mode mode)
{
	return imp->set_mode(mode);
}

Usart_config_status Usart::set_frame(uint8_t data_bits, Usart_parity parity, uint8_t start_bits, uint8_t stop_bits)
{
	return imp->set_frame(data_bits, parity, start_bits, stop_bits);
}

Usart_config_status Usart::set_baud_rate(Usart_baud_rate rate)
{
	return imp->set_baud_rate(rate);
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

Usart_io_status Usart::transmit_byte_blocking(uint8_t data)
{
	return imp->transmit_byte_blocking(data);
}

Usart_io_status Usart::transmit_buffer(uint8_t *data, size_t num_elements, usarttx_callback_t cb_done)
{
	return imp->transmit_buffer(data, num_elements, cb_done);
}

Usart_io_status Usart::transmit_buffer_blocking(uint8_t *data, size_t num_elements)
{
	return imp->transmit_buffer_blocking(data, num_elements);
}

Usart_io_status Usart::transmit_string(uint8_t *data, usarttx_callback_t cb_done)
{
	return imp->transmit_string(data, cb_done);
}

Usart_io_status Usart::transmit_string_blocking(uint8_t *data)
{
	return imp->transmit_string_blocking(data);
}

int16_t Usart::receive_byte(void)
{
	return imp->receive_byte();
}

int16_t Usart::receive_byte_blocking(void)
{
	return imp->receive_byte_blocking();
}

Usart_io_status Usart::receive_buffer(uint8_t *buffer, size_t size, usartrx_callback_t cb_done)
{
	return imp->receive_buffer(buffer, size, cb_done);
}

Usart_io_status Usart::receive_buffer_blocking(uint8_t *buffer, size_t size)
{
	return imp->receive_buffer_blocking(buffer, size);
}

Usart_io_status Usart::receive_string(char *string, size_t max_size, usartrx_callback_t cb_done)
{
	return imp->receive_string(string, max_size, cb_done);
}

void Usart::enable_interrupts()
{
	imp->enable_interrupts();
}

void Usart::disable_interrupts()
{
	imp->enable_interrupts();
}

Usart_int_status Usart::attach_interrupt(Usart_interrupt_type interrupt, void (*callback)(void))
{
	return imp->attach_interrupt(interrupt, callback);
}

Usart_int_status Usart::detach_interrupt(Usart_interrupt_type interrupt)
{
	return imp->detach_interrupt(interrupt);
}

Usart_error_type Usart::usart_error(void)
{
	return imp->usart_error();
}

void Usart::usart_clear_errors()
{
	imp->usart_error();
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS.

// IMPLEMENT PRIVATE CLASS FUNCTIONS (METHODS).

// Usart.

Usart_imp::Usart_imp(Usart_channel channel, Usart_pins pins, Usart_registers registers)
{
	this->channel = channel;
	this->pins = pins;
	this->registers = registers;
}
		
Usart_imp::~Usart_imp(void)
{
	// Clean up
}

Usart_config_status Usart_imp::set_mode(Usart_setup_mode mode)
{
	// TODO - This.
	return USART_CFG_FAILED;
}

Usart_config_status Usart_imp::set_frame(uint8_t data_bits, Usart_parity parity, uint8_t start_bits, uint8_t stop_bits)
{
	// TODO - This.
	return USART_CFG_FAILED;
}
	
Usart_config_status Usart_imp::set_baud_rate(Usart_baud_rate rate)
{
	// TODO - This.
	return USART_CFG_FAILED;
}

bool Usart_imp::transmitter_ready()
{
	// TODO - This.
	return false;
}

bool Usart_imp::receiver_has_data()
{
	// TODO - This.
	return false;
}

Usart_io_status Usart_imp::transmit_byte(uint8_t data)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::transmit_byte_blocking(uint8_t data)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::transmit_buffer(uint8_t *data, size_t num_elements, usarttx_callback_t cb_done)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::transmit_buffer_blocking(uint8_t *data, size_t num_elements)
{
	// TODO - This.
	return USART_IO_FAILED;
}
		 
Usart_io_status Usart_imp::transmit_string(uint8_t *data, usarttx_callback_t cb_done)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::transmit_string_blocking(uint8_t *data)
{
	// TODO - This.
	return USART_IO_FAILED;
}

int16_t Usart_imp::receive_byte(void)
{
	// TODO - This.
	return -1;
}

int16_t Usart_imp::receive_byte_blocking()
{
	while (!receiver_has_data())
	{
		// Wait for data
	}

	return receive_byte();
}

Usart_io_status Usart_imp::receive_buffer(uint8_t *buffer, size_t size, usartrx_callback_t cb_done)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::receive_buffer_blocking(uint8_t *buffer, size_t size)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::receive_string(char *string, size_t max_size, usartrx_callback_t cb_done)
{
	// TODO - This.
	return USART_IO_FAILED;
}

Usart_io_status Usart_imp::receive_string_blocking(uint8_t *buffer, size_t size, size_t *actual_size)
{
	// TODO - This.
	return USART_IO_FAILED;
}
		
void Usart_imp::enable_interrupts(void)
{
	// TODO - This.
	return;
}

void Usart_imp::disable_interrupts(void)
{
	// TODO - This.
	return;
}

Usart_int_status Usart_imp::attach_interrupt(Usart_interrupt_type interrupt, isr_callback_t callback)
{
	// TODO - This.
	return USART_INT_FAILED;
}

Usart_int_status Usart_imp::Usart_imp::detach_interrupt(Usart_interrupt_type interrupt)
{
	// TODO - This.
	return USART_INT_FAILED;
}
		 
Usart_error_type Usart_imp::usart_error(void)
{
	// TODO - This.
	return USART_ERR_NONE;
}

void Usart_imp::usart_clear_errors()
{
	// TODO - This.
}


/** Declare the ISRptrs
 * 
 * Each USART interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs by way of the function pointer array usartInterrupts[]. Here the
 * ISRs are declared and the user ISR is called if the appropriate element of the function
 * pointer array is non NULL.*/

#ifdef USE_UART0
ISR(USART0_RX_vect)
{
	// Clear the RXCn flag in UCSRnA as a safeguard
	UCSR0A &= (1 << RXC0);

//	if (usartInterrupts[USART0_RX_int])
//		usartInterrupts[USART0_RX_int]();
}

ISR(USART0_TX_vect)
{
//	if (usartInterrupts[USART0_TX_int])
//		usartInterrupts[USART0_TX_int]();
}

ISR(USART0_UDRE_vect)
{
//	if (usartInterrupts[USART0_UDRE_int])
//		usartInterrupts[USART0_UDRE_int]();
}
#endif

#ifdef USE_UART1
ISR(USART1_RX_vect)
{
	// Clear the RXCn flag in UCSRnA as a safeguard
	UCSR1A &= (1 << RXC1);

//	if (usartInterrupts[USART1_RX_int])
//		usartInterrupts[USART1_RX_int]();
}

ISR(USART1_TX_vect)
{
//	if (usartInterrupts[USART1_TX_int])
//		usartInterrupts[USART1_TX_int]();
}

ISR(USART1_UDRE_vect)
{
//	if (usartInterrupts[USART1_UDRE_int])
//		usartInterrupts[USART1_UDRE_int]();
}
#endif

#ifdef USE_UART2
ISR(USART2_RX_vect)
{
	// Clear the RXCn flag in UCSRnA as a safeguard
	UCSR2A &= (1 << RXC2);

//	if (usartInterrupts[USART2_RX_int])
//		usartInterrupts[USART2_RX_int]();
}

ISR(USART2_TX_vect)
{
//	if (usartInterrupts[USART2_TX_int])
//		usartInterrupts[USART2_TX_int]();
}

ISR(USART2_UDRE_vect)
{
//	if (usartInterrupts[USART2_UDRE_int])
//		usartInterrupts[USART2_UDRE_int]();
}
#endif

#ifdef USE_UART3
ISR(USART3_RX_vect)
{
	// Clear the RXCn flag in UCSRnA as a safeguard
	UCSR3A &= (1 << RXC3);

//	if (usartInterrupts[USART3_RX_int])
//		usartInterrupts[USART3_RX_int]();
}

ISR(USART3_TX_vect)
{
//	if (usartInterrupts[USART3_TX_int])
//		usartInterrupts[USART3_TX_int]();
}

ISR(USART3_UDRE_vect)
{
//	if (usartInterrupts[USART3_UDRE_int])
//		usartInterrupts[USART3_UDRE_int]();
}
#endif


// ALL DONE.
