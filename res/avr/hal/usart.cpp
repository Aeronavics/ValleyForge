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
	int16_t UDR_address;
	int16_t UCSRA_address;
	int16_t UCSRB_address;
	int16_t UCSRC_address;
	int16_t UBRR_address;
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

		Usart_imp(Usart_channel channel);
		
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

 		// TODO - Might need to be some fields here.
};

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

	#ifdef __AVR_ATmega2560__
		// We create a static instance of the implementation class for each USART/UART peripheral.
		static Usart_imp usart_imp_0 = Usart_imp(USART_0);
		static Usart_imp usart_imp_1 = Usart_imp(USART_1);
		static Usart_imp usart_imp_2 = Usart_imp(USART_2);
		static Usart_imp usart_imp_3 = Usart_imp(USART_3);

		switch (channel)
		{
			case USART_0:
				// Return a new interface class, attached to the corresponding implementation.
				return Usart(&usart_imp_0);

			case USART_1:
				// Return a new interface class, attached to the corresponding implementation.
				return Usart(&usart_imp_1);

			case USART_2:
				// Return a new interface class, attached to the corresponding implementation.
				return Usart(&usart_imp_2);

			case USART_3:
				// Return a new interface class, attached to the corresponding implementation.
				return Usart(&usart_imp_3);
		}

	#elif __AVR_AT90CAN128__

	#else
		#error "No HAL USART library implementation for this configuration."
	#endif
	
	// *** TARGET AGNOSTIC.

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

Usart_imp::Usart_imp(Usart_channel channel)
{
	// TODO - This.
	return;
}
		
Usart_imp::~Usart_imp(void)
{
	// TODO - This.
	return;
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
	return 0;
}

int16_t Usart_imp::receive_byte_blocking()
{
	// TODO - This.
	return 0;
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


























































/*

// DECLARE PRIVATE GLOBAL VARIABLES.

// Array of user ISRs for USART interrupts 
void (*usartInterrupts[NUM_USART_INTERRUPTS])(void) = {NULL};

// Create an array of USART implementations 
Usart_imp Usart_imps[NUM_USART_CHANNELS];

//* Variable to indicate whether Usart_imps[] has been initialised yet 
bool initialised_usart;

//* Enumerated list of Usart interrupts for use in accessing the appropriate function pointer from the function pointer array 
enum usart_interrupts {USART0_RX_int, USART0_TX_int, USART0_UDRE_int, USART1_RX_int, USART1_TX_int, USART1_UDRE_int, USART2_RX_int, USART2_TX_int, USART2_UDRE_int, USART3_RX_int, USART3_TX_int, USART3_UDRE_int};

int8_t Usart_imp::set_mode(usart_setup_mode mode)
{
  //* Temporarily disable global interrupts during initialisation of USART 
  cli();
  
  // Switch which mode to set the USART up for, depending on what is provided 
  switch (mode)
  {
    case USART_MODE_ASYNCHRONOUS:
    {
      //* Set UMSELn1:0 bits to 0x00 
      _SFR_MEM8(registerTable.UCSRC_address) &= (~(1 << UMSEL1_BIT) & ~(1 << UMSEL0_BIT));
      
      break;
    }
    case USART_MODE_SYNCHRONOUS:
    {
      //* Set UMSELn1:0 bits to 0x01 
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UMSEL1_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UMSEL0_BIT);
      
      //* For compatibility with future devices, clear the UDREn bit in the UCSRAn register whenever UCSRAn is being written to (source: datasheet) 
      _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << UDRE_BIT);
      //* For synchronous mode, write the Double USART transmission speed bit to zero 
      _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << U2X_BIT);
      
      break;
    }
    case USART_MODE_MASTERSPI:
    {
      //* Check to make sure that the semaphore of the required XCKn pin is available in order to facilitate MSPIM 
      if (Usart_imps[(int8_t)usartNumber].usartPinCollection.xck_s->procure())
      {
	//* Set UMSELn1:0 bits to 0x03 
	_SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UMSEL1_BIT) | (1 << UMSEL0_BIT));
	
	//* Set the XCKn pin to an output for Master mode 
	if (Usart_imps[(int8_t)usartNumber].usartPinCollection.xck_address.port >= PORT_H)
	  _SFR_MEM8((Usart_imps[(int8_t)usartNumber].usartPinCollection.xck_address.port * PORT_MULTIPLIER) + P_OFFSET + P_MODE) |= (1 << Usart_imps[(int8_t)usartNumber].usartPinCollection.xck_address.pin);
	else
	  _SFR_IO8((Usart_imps[(int8_t)usartNumber].usartPinCollection.xck_address.port * PORT_MULTIPLIER) + P_MODE) |= (1 << Usart_imps[(int8_t)usartNumber].usartPinCollection.xck_address.pin);
      }
      else
      {
	//* Re-enable global interrupts 
	sei();
	return -1; //* XCKn pin not available 
      }
      
      break;
    }
    default:	//* return -1 for all other invalid settings 
    {
      //* Re-enable global interrupts 
      sei();
      return -1; 
    }
  }
  
  //* Turn on the transmission and reception hardware circuitry 
  _SFR_MEM8(registerTable.UCSRB_address) |= ((1 << RXEN_BIT) | (1 <<TXEN_BIT));
  
  //* Save the set mode within the implementation 
  setMode = mode;
  
  //* Re-enable global interrupts 
  sei();
  
  return 0;
}

/**
* Sets the mode of the connection when in Master SPI Mode
* 
* @param  mode		SPI mode to apply to connection.
* @return 0 for success, -1 for error.

int8_t Usart_imp::set_spi_mode(Usart_mspim_mode mode)
{
  /* Safeguard check to ensure the USART connection has been initialised in MSPIM 
  if (setMode == USART_MODE_MASTERSPI)
  {
    /* Manipulate the appropriate registers based on which mode is given to function 
    switch (mode)
    {
      case USART_MSPI_MODE_0:
      {
	/* Set the UCPOLn and UCPHAn bits to 0 in the UCSRnC register 
	_SFR_MEM8(registerTable.UCSRC_address) &= ~((1 << UCPOL_BIT) & ~(1 << UCPHA_BIT));
	
	break;
      }
      case USART_MSPI_MODE_1:
      {
	/* Set the UCPOLn and UCPHAn bits to 0 and 1 (respectively) in the UCSRnC register 
	_SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCPOL_BIT);
	_SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCPHA_BIT);
	
	break;
      }
      case USART_MSPI_MODE_2:
      {
	/* Set the UCPOLn and UCPHAn bits to 1 and 0 (respectively) in the UCSRnC register 
	_SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCPHA_BIT);
	_SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCPOL_BIT);
	
	break;
      }
      case USART_MSPI_MODE_3:
      {
	/* Set the UCPOLn and UCPHAn bits to 1 in the UCSRnC register 
	_SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UCPOL_BIT) | (1 << UCPHA_BIT));
	
	break;
      }
    }
    
    return 0;
  }
  else
    return -1; /* USART not set to MSPIM 
}


/**
* Configures the serial format to be used for the USART.
*
* @param size		Character size to be used in serial format
* @param parityType	Type of parity to use for format ('DISABLED' for no parity)
* @param numberBits	Number of stop bits in frame
* @return 0 for success, -1 for error.

int8_t Usart_imp::set_frame(uint8_t size, Usart_parity parityType, uint8_t numberBits)
{
  /*
   * Switch which frame size to choose depending on which value is provided
   
  switch (size)
  {
    case 5:
    {
      /* Set the UCSZn2:0 bits to 0x00 
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) &= (~(1 << UCSZ1_BIT) & ~(1 << UCSZ0_BIT));
      
      break;
    }
    case 6:
    {
      /* Set the UCSZn2:0 bits to 0x01 
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCSZ1_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCSZ0_BIT);
      
      break;
    }
    case 7:
    {
      /* Set the UCSZn2:0 bits to 0x02 
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCSZ0_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCSZ1_BIT);
      
      break;
    }
    case 8:
    {
      /* Set the UCSZn2:0 bits to 0x03 
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UCSZ1_BIT) | (1 << UCSZ0_BIT));
      
      break;
    }
    default:	/* All other invalid cases return -1 
      return -1;
  }
  
  /*
   * Switch which parity option to apply depending on what is provided.
   
  switch (parityType)
  {
    case N:
    {
      /* Set the UPMn bits to 0x00 
      _SFR_MEM8(registerTable.UCSRC_address) &= (~(1 << UPM1_BIT) & ~(1 << UPM0_BIT));
      
      break;
    }
    case E:
    {
      /* Set the UPMn bits to 0x02 
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UPM0_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UPM1_BIT);
      
      break;
    }
    case O:
    {
      /* Set the UPMn bits to 0x03 
      _SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UPM0_BIT) | (1 << UPM1_BIT));
      
      break;
    }
    default:	/* All other invalid options 
      return -1;
  }
  
  /*
   * Switch which stop bit option to use depending on what is provided
   
  switch (numberBits)
  {
    case 1:
    {
      /* Set the USBSn bit to 0x00 
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << USBS_BIT);
      
      break;
    }
    case 2:
    {
      /* Set the USBSn bit to 0x01 
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << USBS_BIT);
      
      break;
    }
    default:	/* All other invalid options 
      return -1;
  } 
  
  return 0;
    
}

/**
* Function for setting the bit order of the data frame when hardware is configured in Master SPI mode.
*
* @param order		Bit order option, either MSB or LSB first.
* @return 0 for success, -1 for error.

int8_t Usart_imp::set_spi_bit_order(Usart_mspim_bit_order order)
{
  /* Safeguard check to ensure the USART connection has been initialised in MSPIM 
  if (setMode == USART_MODE_MASTERSPI)
  {
    /* Manipulate the appropriate registers based on which mode is given to function 
    switch (order)
    {
      case USART_MSPIM_MSB_FIRST:
      {
	/* Set the UCDORDn bit to 0 in the UCSRnC register 
	_SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UDORD_BIT);
	
	break;
      }
      case USART_MSPIM_LSB_FIRST:
      {
	/* Set the UCDORDn bit to 1 in the UCSRnC register 
	_SFR_MEM8(registerTable.UCSRC_address) |= (1 << UDORD_BIT);
	
	break;
      }
    }    
    return 0;
  }
  else
    return -1; /* USART not set to MSPIM 
}

/**
* Applies the desired Baud rate for USART communication.
*
* @param rate	Desired Baud rate to use for communication.
* @return 0 for success, -1 for error.

int8_t Usart_imp::set_baud_rate(Usart_baud_rate rate)
{
  /* Calculate the Baud value required for the user provided Baud rate 
   *	Baud value = F_CPU			- 1
   * 		     --------------------
   * 		     (User_Baud_rate * K)
   * 
   * Where K varies depending on which mode the USART is set to.
   * 
   * Asynchronous mode (U2Xn = 0)	K = 16
   * Asynchronous mode (U2Xn = 1)	K = 8
   * Synchronous Master mode		K = 2
   
  
  uint32_t K;
  
  /* Check to see if Asynchronus mode (U2Xn set) is applied 
  if ((setMode == USART_MODE_ASYNCHRONOUS) && ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << U2X_BIT)) == 0))
    K = 16UL;
  /* Check to see if if Asynchronus mode (U2Xn cleared) is applied 
  else if ((setMode == USART_MODE_ASYNCHRONOUS) && ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << U2X_BIT)) == 1))
    K = 8UL;
  /* Check to see if Synchronous Master mode is applied 
  else
    K = 2UL;
  
  /* Set the UBBR value according to the equation above 
  _SFR_MEM16(registerTable.UBRR_address) = (((F_CPU / (rate * K))) - 1);
  
  return 0;
}

/**
* Doubles the USART transmission speed. (only applies in Asynchronous mode!)
*
* @param value		Value to set the USART Double mode to. True to set it, false to clear it.
* @return 0 for success, -1 for error.

int8_t Usart_imp::double_usart_speed(bool value)
{
  /* For compatibility with future devices, clear the UDREn bit in the UCSRAn register whenever UCSRAn is being written to (source: datasheet) 
  _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << UDRE_BIT);
  
  if (value)	/* Enable U2X mode 
    _SFR_MEM8(registerTable.UCSRA_address) |= (1 << U2X_BIT);
  else		/* Disable U2X mode 
    _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << U2X_BIT);

  return 0;
}

/**
* Indicates whether or not the USART data buffer is available or not at the time of checking.
*
* @param void.
* @return boolean variable that is true if buffer is available, false otherwise.

bool Usart_imp::buffer_is_available(void)
{
  if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << UDRE_BIT)) == 1)
    return true;
  else
    return false;
}

/**
* Transmits one byte via the configured USART connection.
*
* @param data		Byte to be transmitted via the USART
* @return 0 for success, -1 for error.

int8_t Usart_imp::transmit_byte(uint8_t data)
{
   /* Wait for the UDRn register to be free 
  while ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << UDRE_BIT)) == 0) {};
  
  /* Copy the the data byte to transmit into the USART buffer 
  _SFR_MEM8(registerTable.UDR_address) = data;
  
  return 0;
}

/**
* Transmits a null terminated string of data via the configured USART connection.
*
* @param data		Pointer to data that is to be transmitted via the USART.
* @return 0 for success, -1 for error.

int8_t Usart_imp::transmit_string(uint8_t *data)
{
  while (*data)
  {
    transmit_byte(*data++);
  }
  
  return 0;
}

/**
* Transmits an array of data via the configured USART connection.
*
* @param data		Pointer to data that is to be transmitted via the USART.
* @param elements	Number of elements within the array to transmit.
* @return 0 for success, -1 for error.

int8_t Usart_imp::transmit_array(uint8_t *data, int8_t elements)
{
  for (int8_t i = 0; i < elements; i++)
  {
    transmit_byte(*data++);
  }
  
  return 0;
}

/**
* Transfers one byte via the configured USART MSPIM connection.
*
* @param data		Byte to be transmitted via the USART
* @return contents of receive buffer.

uint8_t Usart_imp::spi_transfer_byte(uint8_t data)
{
  /* Safeguard check to ensure instance is configured in MSPIM 
  if (setMode == USART_MODE_MASTERSPI)
  {
    /* Wait for the UDRn register to be free 
    while ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << UDRE_BIT)) == 0) {};
  
    /* Copy the the data byte to transmit into the USART buffer 
    _SFR_MEM8(registerTable.UDR_address) = data;
    
    /* Wait for the data to be received 
    while ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << RXC_BIT)) == 0) {};
    
    /* return the data from the buffer 
    return (_SFR_MEM8(registerTable.UDR_address));
  }
  else
    return 0;	/* Not configured in MSPIM 
}

/**
* Transfers an array via the configured USART MSPIM connection.
*
* @param TXdata		Pointer to the array to be transmitted via the USART.
* @param RXdata		Pointer to a place in memory where an array can be received via the USART.
* @param numberElements	Number of elements in the arrays (assumed to be the same).
* @return void.

void Usart_imp::spi_transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
  for (int8_t i = 0; i < numberElements; i++)
  {
    *RXdata = spi_transfer_byte(*TXdata);
    
    TXdata++;
    RXdata++;
  }
}

/**
* Transfers a block of data and receives data via the SPI connection.
* Note, this function relies on using DMA or similar to achieve 'non-blocking' operation.
*
* @param TXdata		Pointer to the array that is to be transmitted.
* @param RXdata		Pointer to an array where data may be received to.
* @param numberElements	Number of elements in the arrays (assumed to be the same).
* @return void.

void Usart_imp::spi_dma_transfer(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
  /* TODO Initialise the DMA controller for SPI 
  
  /* TODO Provide the data to transmit ad the location of the received byte 
  
}

/**
* Indicates whether the transmission is complete, i.e no new data
* exists in the transmit buffer.
*
* @param void.
* @return boolean variable that is true if transmission is complete, false otherwise.

bool Usart_imp::transmission_complete(void)
{
  if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << TXC_BIT)) > 0)
    return true;
  else
    return false;
}

/**
* Indicates whether the receive is complete, i.e unread data
* exists in the receive buffer.
*
* @param void.
* @return boolean variable that is true if receive is complete, false otherwise.

bool Usart_imp::receive_complete(void)
{
  if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << RXC_BIT)) > 0)
    return true;
  else
    return false;
}

/**
* Returns the contents of the USART receive buffer.
*
* @param void.
* @return The received byte.

uint8_t Usart_imp::receive_byte(void)
{
  /* Check to make sure there is new unread data in the receive buffer 
  while ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << RXC_BIT)) == 0) {};
	
  /* Return the contents of the receive buffer 
  return (_SFR_MEM8(registerTable.UDR_address));
}

/**
* Receives an array of uint8_t values.
*
* @param array		Pointer to the location in memory where the array can be returned to.
* @param elements	Number of elements to return.
* @return The received byte.

void Usart_imp::receive_array(uint8_t *array, int8_t elements)
{
  for (int8_t i = 0; i < elements; i++)
  {
    *array = receive_byte();
    array++;
  }
}

/**
* Enables an interrupt to be be associated with a USART connection.
*
* @param interrupt		One of the possible interrupt types that are available.
* @param ISRptr		Pointer to the user-defined ISR.
* @return 0 for success, -1 for error.

int8_t Usart_imp::enable_interrupt(Usart_interrupt_type interrupt, void (*ISRptr)(void))
{  
  /* Place the user interrupt function pointer into the appropriate element of the function pointer array 
  usartInterrupts[(NUM_USART_CHANNELS * (int8_t)usartNumber) + (int8_t)interrupt] = ISRptr;  
  
  /* Set the interrupt bit in the UCSRnB register 
  switch (interrupt)
  {
    case USART_INT_RX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) |= (1 << RXCIE_BIT);
      
      break;
    }
    case USART_INT_TX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) |= (1 << TXCIE_BIT);
      
      break;
    }
    case USART_INT_UDRE:
    {
      _SFR_MEM8(registerTable.UCSRB_address) |= (1 << UDRIE_BIT);
      
      break;
    }
  }
  
  return 0;
}

/**
* Enables an interrupt to be be associated with a USART connection.
*
* @param interrupt		Which interrupt to disable.
* @return 0 for success, -1 for error.

int8_t Usart_imp::disable_interrupt(Usart_interrupt_type interrupt)
{
  /* Clear the user interrupt function pointer in the appropriate element of the function pointer array 
  usartInterrupts[(NUM_USART_CHANNELS * (int8_t)usartNumber) + (int8_t)interrupt] = NULL; 
  
  /* Set the interrupt bit in the UCSRnB register 
  switch (interrupt)
  {
    case USART_INT_RX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << RXCIE_BIT);
      
      break;
    }
    case USART_INT_TX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << TXCIE_BIT);
      
      break;
    }
    case USART_INT_UDRE:
    {
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UDRIE_BIT);
      
      break;
    }
  }
  
  return 0;
}

/**
* Function indicates whether an error as occured with the USART transfer.
* This can include Frame Errors, Data OverRun incidents and Parity Erros.
*
* @param void.
* @return error type. This can be one of USART_ERR_NONE, USART_ERR_FRAME, USART_ERR_DATA_OVERRUN, USART_ERR_PARITY

Usart_error_type Usart_imp::usart_error(void)
{
  if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << FE_BIT)) == 16)
    return USART_ERR_FRAME;
  else if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << DOR_BIT)) == 8)
    return USART_ERR_DATA_OVERRUN;
  else if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << UPE_BIT)) == 4)
    return USART_ERR_PARITY;
  else
  return USART_ERR_NONE;
}

// IMPLEMENT EXTRANEOUS FUNCTIONS
/**
* Initialises the USART implementation instances and codes the required
* register addresses, semaphore addresses and GPIO locations.
*
* @param void.
* @return void.

void initialise_USARTs(void)
{
  /* Initialise each USART with its particular USART number 
  for (uint8_t i = 0; i < NUM_USART_CHANNELS; i++)
  {
    Usart_imps[i].usartNumber = (Usart_channel)i;
  }
  
  /* Assign the addresses of the register locations 
  Usart_imps[(int8_t)USART_0].registerTable.UDR_address = UDR0_ADDRESS;
  Usart_imps[(int8_t)USART_0].registerTable.UCSRA_address = UCSR0A_ADDRESS;
  Usart_imps[(int8_t)USART_0].registerTable.UCSRB_address = UCSR0B_ADDRESS;
  Usart_imps[(int8_t)USART_0].registerTable.UBRR_address = UBRR0_ADDRESS;
  
  Usart_imps[(int8_t)USART_1].registerTable.UDR_address = UDR1_ADDRESS;
  Usart_imps[(int8_t)USART_1].registerTable.UCSRA_address = UCSR1A_ADDRESS;
  Usart_imps[(int8_t)USART_1].registerTable.UCSRB_address = UCSR1B_ADDRESS;
  Usart_imps[(int8_t)USART_1].registerTable.UBRR_address = UBRR1_ADDRESS;
  
  Usart_imps[(int8_t)USART_2].registerTable.UDR_address = UDR2_ADDRESS;
  Usart_imps[(int8_t)USART_2].registerTable.UCSRA_address = UCSR2A_ADDRESS;
  Usart_imps[(int8_t)USART_2].registerTable.UCSRB_address = UCSR2B_ADDRESS;
  Usart_imps[(int8_t)USART_2].registerTable.UBRR_address = UBRR2_ADDRESS;
  
  Usart_imps[(int8_t)USART_3].registerTable.UDR_address = UDR3_ADDRESS;
  Usart_imps[(int8_t)USART_3].registerTable.UCSRA_address = UCSR3A_ADDRESS;
  Usart_imps[(int8_t)USART_3].registerTable.UCSRB_address = UCSR3B_ADDRESS;
  Usart_imps[(int8_t)USART_3].registerTable.UBRR_address = UBRR3_ADDRESS;
  
  /* Assign the GPIO addresses and semaphore addresses for each USART instance 
  Usart_imps[(int8_t)USART_0].usartPinCollection.tx_address.port = USART0_TX_PORT;
  Usart_imps[(int8_t)USART_0].usartPinCollection.tx_address.pin = USART0_TX_PIN;
  Usart_imps[(int8_t)USART_0].usartPinCollection.tx_s = &semaphores[(int8_t)USART0_TX_PORT][(int8_t)USART0_TX_PIN];
  
  Usart_imps[(int8_t)USART_0].usartPinCollection.rx_address.port = USART0_RX_PORT;
  Usart_imps[(int8_t)USART_0].usartPinCollection.rx_address.pin = USART0_RX_PIN;
  Usart_imps[(int8_t)USART_0].usartPinCollection.rx_s = &semaphores[(int8_t)USART0_RX_PORT][(int8_t)USART0_RX_PIN];
  
  Usart_imps[(int8_t)USART_0].usartPinCollection.xck_address.port = USART0_XCK_PORT;
  Usart_imps[(int8_t)USART_0].usartPinCollection.xck_address.pin = USART0_XCK_PIN;
  Usart_imps[(int8_t)USART_0].usartPinCollection.xck_s = &semaphores[(int8_t)USART0_XCK_PORT][(int8_t)USART0_XCK_PIN];
  
  Usart_imps[(int8_t)USART_1].usartPinCollection.tx_address.port = USART1_TX_PORT;
  Usart_imps[(int8_t)USART_1].usartPinCollection.tx_address.pin = USART1_TX_PIN;
  Usart_imps[(int8_t)USART_1].usartPinCollection.tx_s = &semaphores[(int8_t)USART1_TX_PORT][(int8_t)USART1_TX_PIN];
  
  Usart_imps[(int8_t)USART_1].usartPinCollection.rx_address.port = USART1_RX_PORT;
  Usart_imps[(int8_t)USART_1].usartPinCollection.rx_address.pin = USART1_RX_PIN;
  Usart_imps[(int8_t)USART_1].usartPinCollection.rx_s = &semaphores[(int8_t)USART1_RX_PORT][(int8_t)USART1_RX_PIN];
  
  Usart_imps[(int8_t)USART_1].usartPinCollection.xck_address.port = USART1_XCK_PORT;
  Usart_imps[(int8_t)USART_1].usartPinCollection.xck_address.pin = USART1_XCK_PIN;
  Usart_imps[(int8_t)USART_1].usartPinCollection.xck_s = &semaphores[(int8_t)USART1_XCK_PORT][(int8_t)USART1_XCK_PIN];
  
  Usart_imps[(int8_t)USART_2].usartPinCollection.tx_address.port = USART2_TX_PORT;
  Usart_imps[(int8_t)USART_2].usartPinCollection.tx_address.pin = USART2_TX_PIN;
  Usart_imps[(int8_t)USART_2].usartPinCollection.tx_s = &semaphores[(int8_t)USART2_TX_PORT][(int8_t)USART2_TX_PIN];
  
  Usart_imps[(int8_t)USART_2].usartPinCollection.rx_address.port = USART2_RX_PORT;
  Usart_imps[(int8_t)USART_2].usartPinCollection.rx_address.pin = USART2_RX_PIN;
  Usart_imps[(int8_t)USART_2].usartPinCollection.rx_s = &semaphores[(int8_t)USART2_RX_PORT][(int8_t)USART2_RX_PIN];
  
  Usart_imps[(int8_t)USART_2].usartPinCollection.xck_address.port = USART2_XCK_PORT;
  Usart_imps[(int8_t)USART_2].usartPinCollection.xck_address.pin = USART2_XCK_PIN;
  Usart_imps[(int8_t)USART_2].usartPinCollection.xck_s = &semaphores[(int8_t)USART2_XCK_PORT][(int8_t)USART2_XCK_PIN];
  
  Usart_imps[(int8_t)USART_3].usartPinCollection.tx_address.port = USART3_TX_PORT;
  Usart_imps[(int8_t)USART_3].usartPinCollection.tx_address.pin = USART3_TX_PIN;
  Usart_imps[(int8_t)USART_3].usartPinCollection.tx_s = &semaphores[(int8_t)USART3_TX_PORT][(int8_t)USART3_TX_PIN];
  
  Usart_imps[(int8_t)USART_3].usartPinCollection.rx_address.port = USART3_RX_PORT;
  Usart_imps[(int8_t)USART_3].usartPinCollection.rx_address.pin = USART3_RX_PIN;
  Usart_imps[(int8_t)USART_3].usartPinCollection.rx_s = &semaphores[(int8_t)USART3_RX_PORT][(int8_t)USART3_RX_PIN];
  
  Usart_imps[(int8_t)USART_3].usartPinCollection.xck_address.port = USART3_XCK_PORT;
  Usart_imps[(int8_t)USART_3].usartPinCollection.xck_address.pin = USART3_XCK_PIN;
  Usart_imps[(int8_t)USART_3].usartPinCollection.xck_s = &semaphores[(int8_t)USART3_XCK_PORT][(int8_t)USART3_XCK_PIN];
}


/** Declare the ISRptrs
 * 
 * Each USART interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs by way of the function pointer array usartInterrupts[]. Here the
 * ISRs are declared and the user ISR is called if the appropriate element of the function
 * pointer array is non NULL.
 

ISR(USART0_RX_vect)
{
  /* Clear the RXCn flag in UCSRnA as a safeguard 
  UCSR0A &= (1 << RXC0);
    
  if (usartInterrupts[USART0_RX_int])  
    usartInterrupts[USART0_RX_int]();
}

ISR(USART0_TX_vect)
{
  if (usartInterrupts[USART0_TX_int])
    usartInterrupts[USART0_TX_int]();
}

ISR(USART0_UDRE_vect)
{
  if (usartInterrupts[USART0_UDRE_int])
    usartInterrupts[USART0_UDRE_int]();
}

ISR(USART1_RX_vect)
{
  /* Clear the RXCn flag in UCSRnA as a safeguard 
  UCSR1A &= (1 << RXC1);
    
  if (usartInterrupts[USART1_RX_int])  
    usartInterrupts[USART1_RX_int]();
}

ISR(USART1_TX_vect)
{
  if (usartInterrupts[USART1_TX_int])
    usartInterrupts[USART1_TX_int]();
}

ISR(USART1_UDRE_vect)
{
  if (usartInterrupts[USART1_UDRE_int])
    usartInterrupts[USART1_UDRE_int]();
}

ISR(USART2_RX_vect)
{
  /* Clear the RXCn flag in UCSRnA as a safeguard 
  UCSR2A &= (1 << RXC2);
    
  if (usartInterrupts[USART2_RX_int])  
    usartInterrupts[USART2_RX_int]();
}

ISR(USART2_TX_vect)
{
  if (usartInterrupts[USART2_TX_int])
    usartInterrupts[USART2_TX_int]();
}

ISR(USART2_UDRE_vect)
{
  if (usartInterrupts[USART2_UDRE_int])
    usartInterrupts[USART2_UDRE_int]();
}

ISR(USART3_RX_vect)
{
  /* Clear the RXCn flag in UCSRnA as a safeguard 
  UCSR3A &= (1 << RXC3);
    
  if (usartInterrupts[USART3_RX_int])  
    usartInterrupts[USART3_RX_int]();
}

ISR(USART3_TX_vect)
{
  if (usartInterrupts[USART3_TX_int])
    usartInterrupts[USART3_TX_int]();
}

ISR(USART3_UDRE_vect)
{
  if (usartInterrupts[USART3_UDRE_int])
    usartInterrupts[USART3_UDRE_int]();
}
*/

// ALL DONE.
