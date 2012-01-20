/********************************************************************************************************************************
 *
 *  FILE: 		usart.h
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	17-01-2012
 *
 *	This is the header file which matches usart.cpp.  Implements various functions relating to USART/UART initialisation, transmission
 * 	and receiving of data.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __USART_H__
#define __USART_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the standard C++ definitions.
#include <stddef.h>

// Include the semaphore library
#include "semaphore.h"

// Include the hal library.
#include "hal/hal.h"

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum usart_number {USART_0, USART_1, USART_2, USART_3};

enum usart_setup_mode {ASYNCHRONOUS_USART, SYNCHRONOUS_USART, MASTER_SPI};

//enum parity_option {DISABLED, EVEN_PARITY, ODD_PARITY};
enum parity_option {N, E, O};

//enum stop_bit_option {ONE_BIT, TWO_BITS};

//enum character_size {FIVE_BITS, SIX_BITS, SEVEN_BITS, EIGHT_BITS};

enum clock_polarity_option {OPTION_1, OPTION_2};

enum usart_interrupt_types {USART_RX, USART_TX, USART_UDRE};

typedef uint16_t baud_rate;

// FORWARD DEFINE PRIVATE PROTOTYPES.

class usart_imp;

// DEFINE PUBLIC CLASSES.

class usart
{
	public:
		// Functions.
		
		/**
		 * Initialises and sets the mode of the USART according to the options provided to it.
		 * 
		 * @param  mode		USART setup mode to be applied during initialisation
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_mode(usart_setup_mode mode);
		
		/**
		 * Configures the serial format to be used for the USART.
		 *
		 * @param size		Character size to be used in serial format
		 * @param parityType	Type of parity to use for format ('DISABLED' for no parity)
		 * @param numberBits	Number of stop bits in frame
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_frame(uint8_t size, parity_option parityType, uint8_t numberBits);
		
		/**
		 * Applies the desired Baud rate for USART communication.
		 *
		 * @param rate	Desired Baud rate to use for communication.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t set_baud_rate(baud_rate rate);
		 
		 /**
		 * Sets the clock polarity for USART communication. (Only applies in Synchronous operation!)
		 *
		 * @param option 	Clock polarity option provided.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t set_clock_polarity(clock_polarity_option option);
		 
		 /**
		 * Doubles the USART transmission speed. (only applies in Asynchronous mode!)
		 *
		 * @param value		Value to set the USART Double mode to. True to set it, false to clear it.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t double_usart_speed(bool value);
		 
		 /**
		 * Indicates whether or not the USART data buffer is empty or not at the time of checking.
		 *
		 * @param void.
		 * @return boolean variable that is true if buffer is empty, false otherwise.
		 */
		 bool buffer_is_empty(void);
		 
		 /**
		 * Transmits one byte via the configured USART connection.
		 *
		 * @param data		Byte to be transmitted via the USART
		 * @return 0 for success, -1 for error.
		 */
		 int8_t transmit_byte(uint8_t data);
		 
		 /**
		 * Indicates whether the transmission is complete, i.e no new data
		 * exists in the transmit buffer.
		 *
		 * @param void.
		 * @return boolean variable that is true if transmission is complete, false otherwise.
		 */
		 bool transmission_complete(void);
		 
		 /**
		 * Indicates whether the receive is complete, i.e unread data
		 * exists in the receive buffer.
		 *
		 * @param void.
		 * @return boolean variable that is true if receive is complete, false otherwise.
		 */
		 bool receive_complete(void);
		 
		/**
		* Transmits one byte via the configured USART connection. Function only returns
		* when there is unread data in the input buffer.
		*
		* @param void.
		* @return The received byte.
		*/
		uint8_t receive_byte(void);
		 
		 /**
		 * Enables an interrupt to be be associated with a USART connection.
		 *
		 * @param interrupt		One of the possible interrupt types that are available.
		 * @param ISRptr		Pointer to the user-defined ISR.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t enable_interrupt(usart_interrupt_types interrupt, void (*ISRptr)(void));
		 
		 /**
		 * Enables an interrupt to be be associated with a USART connection.
		 *
		 * @param interrupt		Which interrupt to disable.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t disable_interrupt(usart_interrupt_types interrupt);
		 
		 //TODO read receiver error codes

		/**
		 * Function to free the USART instance when it goes out of scope.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		 ~usart(void);

		/** 
		 * Allows access to the USART to be relinquished and reused elsewhere.
		 *
		 * @param  Nothing.
		 * @return Nothing.
		 */
		void vacate(void);
		
		/**
		 * Allows a process to request access to a USART instance and manages the semaphore
		 * indicating whether access has been granted or not.
		 *
		 * @param  usartNumber	The number of a USART that is desired.
		 * @return A usart instance.
		 */
		static usart grab(usart_number usartNumber);

	private:
		// Functions.
		
		usart(void);	// Poisoned.

		usart(usart_imp*);

		usart operator =(usart const&);	// Poisoned.

		// Fields.

		/**
		* Pointer to the machine specific implementation of the timer.
		*/
		usart_imp* imp;
};


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__USART_H__*/

// ALL DONE.
