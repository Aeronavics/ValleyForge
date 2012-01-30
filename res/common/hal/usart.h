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

enum mspim_bit_order {MSPIM_MSB_FIRST, MSPIM_LSB_FIRST};

enum mspim_mode {MSPI_MODE_0, MSPI_MODE_1, MSPI_MODE_2, MSPI_MODE_3};

enum parity_option {N, E, O};

enum clock_polarity_option {OPTION_1, OPTION_2};

enum usart_interrupt_types {USART_RX, USART_TX, USART_UDRE};

enum usart_error_types {NONE, FRAME_ERR, DATA_OVERRUN, PARITY_ERR};

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
		* Sets the mode of the connection when in Master SPI Mode
		* 
		* @param  mode		SPI mode to apply to connection.
		* @return 0 for success, -1 for error.
		*/
		int8_t set_spi_mode(mspim_mode mode);
		
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
		 * Function for setting the bit order of the data frame when hardware is configured in Master SPI mode.
		 *
		 * @param order		Bit order option, either MSB or LSB first.
		 * @return 0 for success, -1 for error.
		 */
		int8_t set_bit_order(mspim_bit_order order);
		
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
		 * Indicates whether or not the USART data buffer is available or not at the time of checking.
		 *
		 * @param void.
		 * @return boolean variable that is true if buffer is available, false otherwise.
		 */
		 bool buffer_is_available(void);
		 
		 /**
		 * Transmits one byte via the configured USART connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param data		Byte to be transmitted via the USART
		 * @return 0 for success, -1 for error.
		 */
		 int8_t transmit_byte(uint8_t data);
		 
		 /**
		 * Transmits a null terminated string of data via the configured USART connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param data		Pointer to data that is to be transmitted via the USART.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t transmit_string(uint8_t *data);
		 
		 /**
		 * Transmits an array of data via the configured USART connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param data		Pointer to data that is to be transmitted via the USART.
 		 * @param elements	Number of elements within the array to transmit.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t transmit_array(uint8_t *data, int8_t elements);
		 
		 /**
		 * Transfers one byte via the configured USART MSPIM connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param data		Byte to be transmitted via the USART
		 * @return contents of receive buffer.
		 */
		 uint8_t spi_transfer_byte(uint8_t data);
		 
		 /**
		 * Transfers an array via the configured USART MSPIM connection.
		 * Note, this function 'blocks' until transfer has been completed. 
		 *
		 * @param TXdata		Pointer to the array to be transmitted via the USART.
     		 * @param RXdata		Pointer to a place in memory where an array can be received via the USART.
		 * @param numberElements	Number of elements in the arrays (assumed to be the same).
		 * @return void.
		 */
		 void spi_transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements);
		 
		 /**
		 * Transfers a block of data and receives data via the USART MSPIM connection.
		 * Note, this function relies on using DMA or similar to achieve 'non-blocking' operation.
		 *
		 * @param TXdata		Pointer to the array that is to be transmitted.
		 * @param RXdata		Pointer to an array where data may be received to.
		 * @param numberElements	Number of elements in the arrays (assumed to be the same).
		 * @return void.
		 */
		 void spi_dma_transfer(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements);
		 
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
		* Returns the contents of the USART receive buffer.
		* Note, this function 'blocks' until transfer has been completed. 
		*
		* @param void.
		* @return The received byte.
		*/
		uint8_t receive_byte(void);
		
		/**
		* Receives an array of uint8_t values.
		* Note, this function 'blocks' until transfer has been completed. 
		*
		* @param array		Pointer to the location in memory where the array can be returned to.
		* @param elements	Number of elements to return.
		* @return void.
		*/
		void receive_array(uint8_t *array, int8_t elements);
		
		 /**
		 * Enables an interrupt to be be associated with a USART connection.
		 *
		 * @param interrupt		One of the possible interrupt types that are available.
		 * @param ISRptr		Pointer to the user-defined ISR.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t enable_interrupt(usart_interrupt_types interrupt, void (*ISRptr)(void));
		 
		 /**
		 * Enables an interrupt to be be un-associated with a USART connection.
		 *
		 * @param interrupt		Which interrupt to disable.
		 * @return 0 for success, -1 for error.
		 */
		 int8_t disable_interrupt(usart_interrupt_types interrupt);
		 
		 /**
		 * Function indicates whether an error as occured with the USART transfer.
		 * This can include Frame Errors, Data OverRun incidents and Parity Erros.
		 *
		 * @param void.
		 * @return error type. This can be one of NONE, FRAME_ERR, DATA_OVERRUN, PARITY_ERR
		 */
		 usart_error_types usart_error(void);
		 
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
		* Pointer to the machine specific implementation of the USART.
		*/
		usart_imp* imp;
};


// DEFINE PUBLIC STATIC FUNCTION PROTOTYPES.

#endif /*__USART_H__*/

// ALL DONE.
