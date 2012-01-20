/********************************************************************************************************************************
 *
 *  FILE: 		usart.cpp	
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

#include "usart.h"

// INCLUDE SYSTEM HEADER FILES

#include <avr/io.h>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// DEFINE DEVICE PARTICULAR REGISTAR ADDRESSES
#if defined (__AVR_ATmega2560__)

    /* Address locations of registers for USART0 */
#	define UDR0_ADDRESS			0xC6	//MEM8
#	define UBRR0_ADDRESS			0xC4	//MEM16
#	define UCSR0C_ADDRESS			0XC2	//MEM8
#	define UCSR0B_ADDRESS			0xC1	//MEM8
#	define UCSR0A_ADDRESS			0xC0	//MEM8

    /* Address locations of registers for USART1 */
#	define UDR1_ADDRESS			0xCE	//MEM8
#	define UBRR1_ADDRESS			0xCC	//MEM16
#	define UCSR1C_ADDRESS			0xCA	//MEM8
#	define UCSR1B_ADDRESS			0xC9	//MEM8
#	define UCSR1A_ADDRESS			0xC8	//MEM8

    /* Address locations of registers for USART2 */
#	define UDR2_ADDRESS			0xD6	//MEM8
#	define UBRR2_ADDRESS			0xD4	//MEM26
#	define UCSR2C_ADDRESS			0xD2	//MEM8
#	define UCSR2B_ADDRESS			0xD1	//MEM8
#	define UCSR2A_ADDRESS			0xD0	//MEM8

    /* Address locations of registers for USART3 */
#	define UDR3_ADDRESS			0x136	//MEM8
#	define UBRR3_ADDRESS			0x134	//MEM36
#	define UCSR3C_ADDRESS			0x132	//MEM8
#	define UCSR3B_ADDRESS			0x131	//MEM8
#	define UCSR3A_ADDRESS			0x130	//MEM8

    /* Generic bit addresses for register manipulation */
		  /* UCSRnA Register */
#	define RXC_BIT				7
#	define TXC_BIT				6
#	define UDRE_BIT				5
#	define FE_BIT				4
#	define DOR_BIT				3
#	define UPE_BIT				2
#	define U2X_BIT				1
#	define MPCM_BIT				0

		  /* UCSRnB Register */
#	define RXCIE_BIT			7
#	define TXCIE_BIT			6
#	define UDRIE_BIT			5
#	define RXEN_BIT				4
#	define TXEN_BIT				3
#	define UCSZ2_BIT			2
#	define RXB8_BIT				1
#	define TXB8_BIT				0

		  /* UCSRnC Register */
#	define UMSEL1_BIT			7
#	define UMSEL0_BIT			6
#	define UPM1_BIT				5
#	define UPM0_BIT				4
#	define USBS_BIT				3
#	define UCSZ1_BIT			2
#	define UCSZ0_BIT			1
#	define UCPOL_BIT			0

   /* GPIO addresses of transmitter and receiver pins for each USART channel */
#	define USART0_TX_PORT			PORT_E
#	define USART0_TX_PIN			PIN_1
#	define USART0_RX_PORT			PORT_E
#	define USART0_RX_PIN			PIN_0

#	define USART1_TX_PORT			PORT_D
#	define USART1_TX_PIN			PIN_3
#	define USART1_RX_PORT			PORT_D
#	define USART1_RX_PIN			PIN_2

#	define USART2_TX_PORT			PORT_H
#	define USART2_TX_PIN			PIN_1
#	define USART2_RX_PORT			PORT_H
#	define USART2_RX_PIN			PIN_0

#	define USART3_TX_PORT			PORT_J
#	define USART3_TX_PIN			PIN_1
#	define USART3_RX_PORT			PORT_J
#	define USART3_RX_PIN			PIN_0

    /* General preprocessor macros for convenience */
#	define NUM_USART_CHANNELS		4
#	define NUM_CHANNEL_INTERRUPTS		3
#	define NUM_USART_INTERRUPTS		NUM_USART_CHANNELS * NUM_CHANNEL_INTERRUPTS

    /* TODO Temporary - place elsewhere */
#	define F_CPU				8000000L

#endif

/*
 * Structure to contain all the required register addresses that are needed for the Timer/Counter functionality
 */
typedef struct REGISTER_ADDRESS_TABLE {
  int16_t UDR_address;
  int16_t UCSRA_address;
  int16_t UCSRB_address;
  int16_t UCSRC_address;
  int16_t UBRR_address;
} registerAddressTable_t;

/*
 * Structure to contain the GPIO pin addresses and associated semaphores that represent the peripheral pins for all the USART channels.
 */
typedef struct USART_PINS {
  semaphore *tx_s;
  gpio_pin_address tx_address;
  semaphore *rx_s;
  gpio_pin_address rx_address;
} usartPins_t;

// DECLARE IMPORTED GLOBAL VARIABLES
extern semaphore semaphores[NUM_PORTS][NUM_PINS];

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
* Initialises the USART implementation instances and codes the required
* register addresses, semaphore addresses and GPIO locations.
*
* @param void.
* @return void.
*/
void initialise_USARTs(void);

// DEFINE PRIVATE TYPES AND STRUCTS.

/**
 * Class to implement the functionality
 * required for the USART/UART.
 */
class usart_imp
{
    public:
      
	// Functions
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
	
	// Public Fields
	/**
	 * Field to identify each implementation by its associated USART Number.
	 */
	usart_number usartNumber;
	
	/**
	 * Register Address table to store the addresses of the particular USART 
	 * registers when a USART is instantiated and initialised.
	 */
	registerAddressTable_t registerTable;
	
	/**
	 * Collection to contain the GPIO addresses and semaphores associated with
	 * each of the TX/RX GPIO pins which are to be attached to the USART isntance.
	 */
	usartPins_t usartPinCollection;
	
	//Private functions & Fields
  private:
	
	/**
	 * Field to contain the current USART mode that is set by the user
	 */
	usart_setup_mode setMode;
};

// DECLARE PRIVATE GLOBAL VARIABLES.

/* Array of user ISRs for USART interrupts */
void (*usartInterrupts[NUM_USART_INTERRUPTS])(void) = {NULL};

/* Create an array of USART implementations */
usart_imp usart_imps[NUM_USART_CHANNELS];

/* Variable to indicate whether usart_imps[] has been initialised yet */
bool initialised_usart;

/* Enumerated list of usart interrupts for use in accessing the appropriate function pointer from the function pointer array */
enum usart_interrupts {USART0_RX_int, USART0_TX_int, USART0_UDRE_int, USART1_RX_int, USART1_TX_int, USART1_UDRE_int, USART2_RX_int, USART2_TX_int, USART2_UDRE_int, USART3_RX_int, USART3_TX_int, USART3_UDRE_int};

// IMPLEMENT PUBLIC FUNCTIONS.

/**
* Initialises and sets the mode of the USART according to the options provided to it.
* 
* @param  mode		USART setup mode to be applied during initialisation
* @return 0 for success, -1 for error.
*/
int8_t usart::set_mode(usart_setup_mode mode)
{
  return (imp->set_mode(mode));
}

/**
* Configures the serial format to be used for the USART.
*
* @param size		Character size to be used in serial format
* @param parityType	Type of parity to use for format ('DISABLED' for no parity)
* @param numberBits	Number of stop bits in frame
* @return 0 for success, -1 for error.
*/
int8_t usart::set_frame(uint8_t size, parity_option parityType, uint8_t numberBits)
{
  return (imp->set_frame(size, parityType, numberBits));
}

/**
* Applies the desired Baud rate for USART communication.
*
* @param rate	Desired Baud rate to use for communication.
* @return 0 for success, -1 for error.
*/
int8_t usart::set_baud_rate(baud_rate rate)
{
  return (imp->set_baud_rate(rate));
}

/**
* Sets the clock polarity for USART communication. (Only applies in Synchronous operation!)
*
* @param option 	Clock polarity option provided.
* @return 0 for success, -1 for error.
*/
int8_t usart::set_clock_polarity(clock_polarity_option option)
{
  return (imp->set_clock_polarity(option));
}

/**
* Doubles the USART transmission speed. (only applies in Asynchronous mode!)
*
* @param value		Value to set the USART Double mode to. True to set it, false to clear it.
* @return 0 for success, -1 for error.
*/
int8_t usart::double_usart_speed(bool value)
{
  return (imp->double_usart_speed(value));
}

/**
* Indicates whether or not the USART data buffer is empty or not at the time of checking.
*
* @param void.
* @return boolean variable that is true if buffer is empty, false otherwise.
*/
bool usart::buffer_is_empty(void)
{
  return (imp->buffer_is_empty());
}

/**
* Transmits one byte via the configured USART connection.
*
* @param data		Byte to be transmitted via the USART
* @return 0 for success, -1 for error.
*/
int8_t usart::transmit_byte(uint8_t data)
{
  return (imp->transmit_byte(data));
}

/**
* Indicates whether the transmission is complete, i.e no new data
* exists in the transmit buffer.
*
* @param void.
* @return boolean variable that is true if transmission is complete, false otherwise.
*/
bool usart::transmission_complete(void)
{
  return (imp->transmission_complete());
}

/**
* Indicates whether the receive is complete, i.e unread data
* exists in the receive buffer.
*
* @param void.
* @return boolean variable that is true if receive is complete, false otherwise.
*/
bool usart::receive_complete(void)
{
  return (imp->receive_complete());
}

/**
* Transmits one byte via the configured USART connection. Function only returns
* when there is unread data in the input buffer.
*
* @param void.
* @return The received byte.
*/
uint8_t usart::receive_byte(void)
{
  return (imp->receive_byte());
}

/**
* Enables an interrupt to be be associated with a USART connection.
*
* @param interrupt		One of the possible interrupt types that are available.
* @param ISRptr		Pointer to the user-defined ISR.
* @return 0 for success, -1 for error.
*/
int8_t usart::enable_interrupt(usart_interrupt_types interrupt, void (*ISRptr)(void))
{
  return (imp->enable_interrupt(interrupt, ISRptr));
}

/**
* Enables an interrupt to be be associated with a USART connection.
*
* @param interrupt		Which interrupt to disable.
* @return 0 for success, -1 for error.
*/
int8_t usart::disable_interrupt(usart_interrupt_types interrupt)
{
  return (imp->disable_interrupt(interrupt));
}

/**
* Function to free the USART instance when it goes out of scope.
*
* @param  Nothing.
* @return Nothing.
*/
usart::~usart(void)
{
  vacate();
}

/** 
* Allows access to the USART to be relinquished and reused elsewhere.
*
* @param  Nothing.
* @return Nothing.
*/
void usart::vacate(void)
{
  /* No need to vacate if implementation pointer is NULL */
  if (imp != NULL)
  {
    /* Vacate the sempahores to detatch the USART GPIO */
    imp->usartPinCollection.tx_s->vacate();
    imp->usartPinCollection.rx_s->vacate();    
    
    /* Clear the appropriate elements in the function pointer array */
    for (uint8_t i = (NUM_CHANNEL_INTERRUPTS * imp->usartNumber); i < (NUM_CHANNEL_INTERRUPTS * (imp->usartNumber + 1)); i++)
      usartInterrupts[i] = NULL;     
    
    /* Reset the implementation pointer to NULL */
    imp = NULL;
  }
}

/**
* Allows a process to request access to a USART instance and manages the semaphore
* indicating whether access has been granted or not.
*
* @param  usartNumber	The number of a USART that is desired.
* @return A usart instance.
*/
usart usart::grab(usart_number usartNumber)
{
  /* Add possible semaphore functionality here */
  
  /* Initialise USART if it is not already initialised */
  if (!initialised_usart)
  {
    //Initialise USART
    initialise_USARTs();
  }
  
  /* Set the local field 'imp' pointer to point to the specific
   * implementation of timer_imp */
  if (usart_imps[(int8_t)usartNumber].usartPinCollection.tx_s->procure() && usart_imps[(int8_t)usartNumber].usartPinCollection.rx_s->procure())
    return usart(&usart_imps[(int8_t)usartNumber]);
  else
    return NULL;
}

// IMPLEMENT PRIVATE FUNCTIONS.

usart::usart(usart_imp* implementation)
{
  /*attach the USART implementation*/
  imp = implementation;
}

// IMPLEMENT USART IMPLEMENTATION FUNCTIONS

/**
* Initialises and sets the mode of the USART according to the options provided to it.
* 
* @param  mode		USART setup mode to be applied during initialisation
* @return 0 for success, -1 for error.
*/
int8_t usart_imp::set_mode(usart_setup_mode mode)
{
  /* Turn on the transmission and reception hardware circuitry */
  _SFR_MEM8(registerTable.UCSRB_address) |= ((1 << RXEN_BIT) | (1 <<TXEN_BIT));
  
  /* 
   * Switch which mode to set the USART up for, depending on what is provided 
   */
  switch (mode)
  {
    case ASYNCHRONOUS_USART:
    {
      /* Set UMSELn1:0 bits to 0x00 */
      _SFR_MEM8(registerTable.UCSRC_address) &= (~(1 << UMSEL1_BIT) & ~(1 << UMSEL0_BIT));
      
      break;
    }
    case SYNCHRONOUS_USART:
    {
      /* Set UMSELn1:0 bits to 0x01 */
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UMSEL1_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UMSEL0_BIT);
      
     /* For compatibility with future devices, clear the UDREn bit in the UCSRAn register whenever UCSRAn is being written to (source: datasheet) */
      _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << UDRE_BIT);
    /* For synchronous mode, write the Double USART transmission speed bit to zero */
      _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << U2X_BIT);
      
      break;
    }
    case MASTER_SPI:
    {
      /* Set UMSELn1:0 bits to 0x03 */
      _SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UMSEL1_BIT) | (1 << UMSEL0_BIT));
      
      break;
    }
    default:	/* return -1 for all other invalid settings */
      return -1;      
  }
  
  /* Save the set mode within the implementation */
  setMode = mode;
  return 0;
}

/**
* Configures the serial format to be used for the USART.
*
* @param size		Character size to be used in serial format
* @param parityType	Type of parity to use for format ('DISABLED' for no parity)
* @param numberBits	Number of stop bits in frame
* @return 0 for success, -1 for error.
*/
int8_t usart_imp::set_frame(uint8_t size, parity_option parityType, uint8_t numberBits)
{
  /*
   * Switch which frame size to choose depending on which value is provided
   */
  switch (size)
  {
    case 5:
    {
      /* Set the UCSZn2:0 bits to 0x00 */
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) &= (~(1 << UCSZ1_BIT) & ~(1 << UCSZ0_BIT));
      
      break;
    }
    case 6:
    {
      /* Set the UCSZn2:0 bits to 0x01 */
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCSZ1_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCSZ0_BIT);
      
      break;
    }
    case 7:
    {
      /* Set the UCSZn2:0 bits to 0x02 */
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCSZ0_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCSZ1_BIT);
      
      break;
    }
    case 8:
    {
      /* Set the UCSZn2:0 bits to 0x03 */
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UCSZ2_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UCSZ1_BIT) | (1 << UCSZ0_BIT));
      
      break;
    }
    default:	/* All other invalid cases return -1 */
      return -1;
  }
  
  /*
   * Switch which parity option to apply depending on what is provided.
   */
  switch (parityType)
  {
    case N:
    {
      /* Set the UPMn bits to 0x00 */
      _SFR_MEM8(registerTable.UCSRC_address) &= (~(1 << UPM1_BIT) & ~(1 << UPM0_BIT));
      
      break;
    }
    case E:
    {
      /* Set the UPMn bits to 0x02 */
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UPM0_BIT);
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UPM1_BIT);
      
      break;
    }
    case O:
    {
      /* Set the UPMn bits to 0x03 */
      _SFR_MEM8(registerTable.UCSRC_address) |= ((1 << UPM0_BIT) | (1 << UPM1_BIT));
      
      break;
    }
    default:	/* All other invalid options */
      return -1;
  }
  
  /*
   * Switch which stop bit option to use depending on what is provided
   */
  switch (numberBits)
  {
    case 1:
    {
      /* Set the USBSn bit to 0x00 */
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << USBS_BIT);
      
      break;
    }
    case 2:
    {
      /* Set the USBSn bit to 0x01 */
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << USBS_BIT);
      
      break;
    }
    default:	/* All other invalid options */
      return -1;
  } 
  
  return 0;
    
}

/**
* Applies the desired Baud rate for USART communication.
*
* @param rate	Desired Baud rate to use for communication.
* @return 0 for success, -1 for error.
*/
int8_t usart_imp::set_baud_rate(baud_rate rate)
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
   */
  
  uint32_t K;
  
  /* Check to see if Asynchronus mode (U2Xn set) is applied */
  if ((setMode == ASYNCHRONOUS_USART) && ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << U2X_BIT)) == 0))
    K = 16UL;
  /* Check to see if if Asynchronus mode (U2Xn cleared) is applied */
  else if ((setMode == ASYNCHRONOUS_USART) && ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << U2X_BIT)) == 1))
    K = 8UL;
  /* Check to see if Synchronous Master mode is applied */
  else
    K = 2UL;
  
  /* Set the UBBR value according to the equation above */
  _SFR_MEM16(registerTable.UBRR_address) = (((F_CPU / (rate * K))) - 1);
  
  return 0;
}

/**
* Sets the clock polarity for USART communication. (Only applies in Synchronous operation!)
*
* @param option 	Clock polarity option provided.
* @return 0 for success, -1 for error.
*/
int8_t usart_imp::set_clock_polarity(clock_polarity_option option)
{
  /*
   * Switch depending on the clock polarity option provided
   */
  switch (option)
  {
    case OPTION_1:
    {
      _SFR_MEM8(registerTable.UCSRC_address) &= ~(1 << UCPOL_BIT);
      
      break;
    }
    case OPTION_2:
    {
      _SFR_MEM8(registerTable.UCSRC_address) |= (1 << UCPOL_BIT);
      
      break;
    }
  }
    
  return 0;
}

/**
* Doubles the USART transmission speed. (only applies in Asynchronous mode!)
*
* @param value		Value to set the USART Double mode to. True to set it, false to clear it.
* @return 0 for success, -1 for error.
*/
int8_t usart_imp::double_usart_speed(bool value)
{
  /* For compatibility with future devices, clear the UDREn bit in the UCSRAn register whenever UCSRAn is being written to (source: datasheet) */
  _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << UDRE_BIT);
  
  if (value)	/* Enable U2X mode */
    _SFR_MEM8(registerTable.UCSRA_address) |= (1 << U2X_BIT);
  else		/* Disable U2X mode */
    _SFR_MEM8(registerTable.UCSRA_address) &= ~(1 << U2X_BIT);

  return 0;
}

/**
* Indicates whether or not the USART data buffer is empty or not at the time of checking.
*
* @param void.
* @return boolean variable that is true if buffer is empty, false otherwise.
*/
bool usart_imp::buffer_is_empty(void)
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
*/
int8_t usart_imp::transmit_byte(uint8_t data)
{
  /* Copy the the data byte to transmit into the USART buffer */
  _SFR_MEM8(registerTable.UDR_address) = data;
  
  return 0;
}

/**
* Indicates whether the transmission is complete, i.e no new data
* exists in the transmit buffer.
*
* @param void.
* @return boolean variable that is true if transmission is complete, false otherwise.
*/
bool usart_imp::transmission_complete(void)
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
*/
bool usart_imp::receive_complete(void)
{
  if ((_SFR_MEM8(registerTable.UCSRA_address) & (1 << RXC_BIT)) > 0)
    return true;
  else
    return false;
}

/**
* Transmits one byte via the configured USART connection. Function only returns
* when there is unread data in the input buffer.
*
* @param void.
* @return The received byte.
*/
uint8_t usart_imp::receive_byte(void)
{
  /* Wait for new unread data to arrive */
  //while ((_SFR_MEM8(registerTable.UCSR0A_ADDRESS) & (1 << RXC_BIT)) == 0) {};
  
  return (_SFR_MEM8(registerTable.UDR_address));
}

/**
* Enables an interrupt to be be associated with a USART connection.
*
* @param interrupt		One of the possible interrupt types that are available.
* @param ISRptr		Pointer to the user-defined ISR.
* @return 0 for success, -1 for error.
*/
int8_t usart_imp::enable_interrupt(usart_interrupt_types interrupt, void (*ISRptr)(void))
{  
  /* Place the user interrupt function pointer into the appropriate element of the function pointer array */
  usartInterrupts[(NUM_USART_CHANNELS * (int8_t)usartNumber) + (int8_t)interrupt] = ISRptr;  
  
  /* Set the interrupt bit in the UCSRnB register */
  switch (interrupt)
  {
    case USART_RX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) |= (1 << RXCIE_BIT);
      
      break;
    }
    case USART_TX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) |= (1 << TXCIE_BIT);
      
      break;
    }
    case USART_UDRE:
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
*/
int8_t usart_imp::disable_interrupt(usart_interrupt_types interrupt)
{
  /* Clear the user interrupt function pointer in the appropriate element of the function pointer array */
  usartInterrupts[(NUM_USART_CHANNELS * (int8_t)usartNumber) + (int8_t)interrupt] = NULL; 
  
  /* Set the interrupt bit in the UCSRnB register */
  switch (interrupt)
  {
    case USART_RX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << RXCIE_BIT);
      
      break;
    }
    case USART_TX:
    {
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << TXCIE_BIT);
      
      break;
    }
    case USART_UDRE:
    {
      _SFR_MEM8(registerTable.UCSRB_address) &= ~(1 << UDRIE_BIT);
      
      break;
    }
  }
  
  return 0;
}

// IMPLEMENT EXTRANEOUS FUNCTIONS
/**
* Initialises the USART implementation instances and codes the required
* register addresses, semaphore addresses and GPIO locations.
*
* @param void.
* @return void.
*/
void initialise_USARTs(void)
{
  /* Initialise each USART with its particular USART number */
  for (uint8_t i = 0; i < NUM_USART_CHANNELS; i++)
  {
    usart_imps[i].usartNumber = (usart_number)i;
  }
  
  /* Assign the addresses of the register locations */
  usart_imps[(int8_t)USART_0].registerTable.UDR_address = UDR0_ADDRESS;
  usart_imps[(int8_t)USART_0].registerTable.UCSRA_address = UCSR0A_ADDRESS;
  usart_imps[(int8_t)USART_0].registerTable.UCSRB_address = UCSR0B_ADDRESS;
  usart_imps[(int8_t)USART_0].registerTable.UBRR_address = UBRR0_ADDRESS;
  
  usart_imps[(int8_t)USART_1].registerTable.UDR_address = UDR1_ADDRESS;
  usart_imps[(int8_t)USART_1].registerTable.UCSRA_address = UCSR1A_ADDRESS;
  usart_imps[(int8_t)USART_1].registerTable.UCSRB_address = UCSR1B_ADDRESS;
  usart_imps[(int8_t)USART_1].registerTable.UBRR_address = UBRR1_ADDRESS;
  
  usart_imps[(int8_t)USART_2].registerTable.UDR_address = UDR2_ADDRESS;
  usart_imps[(int8_t)USART_2].registerTable.UCSRA_address = UCSR2A_ADDRESS;
  usart_imps[(int8_t)USART_2].registerTable.UCSRB_address = UCSR2B_ADDRESS;
  usart_imps[(int8_t)USART_2].registerTable.UBRR_address = UBRR2_ADDRESS;
  
  usart_imps[(int8_t)USART_3].registerTable.UDR_address = UDR3_ADDRESS;
  usart_imps[(int8_t)USART_3].registerTable.UCSRA_address = UCSR3A_ADDRESS;
  usart_imps[(int8_t)USART_3].registerTable.UCSRB_address = UCSR3B_ADDRESS;
  usart_imps[(int8_t)USART_3].registerTable.UBRR_address = UBRR3_ADDRESS;
  
  /* Assign the GPIO addresses and semaphore addresses for each USART instance */
  usart_imps[(int8_t)USART_0].usartPinCollection.tx_address.port = USART0_TX_PORT;
  usart_imps[(int8_t)USART_0].usartPinCollection.tx_address.pin = USART0_TX_PIN;
  usart_imps[(int8_t)USART_0].usartPinCollection.tx_s = &semaphores[(int8_t)USART0_TX_PORT][(int8_t)USART0_TX_PIN];
  
  usart_imps[(int8_t)USART_0].usartPinCollection.rx_address.port = USART0_RX_PORT;
  usart_imps[(int8_t)USART_0].usartPinCollection.rx_address.pin = USART0_RX_PIN;
  usart_imps[(int8_t)USART_0].usartPinCollection.rx_s = &semaphores[(int8_t)USART0_RX_PORT][(int8_t)USART0_RX_PIN];
  
  usart_imps[(int8_t)USART_1].usartPinCollection.tx_address.port = USART1_TX_PORT;
  usart_imps[(int8_t)USART_1].usartPinCollection.tx_address.pin = USART1_TX_PIN;
  usart_imps[(int8_t)USART_1].usartPinCollection.tx_s = &semaphores[(int8_t)USART1_TX_PORT][(int8_t)USART1_TX_PIN];
  
  usart_imps[(int8_t)USART_1].usartPinCollection.rx_address.port = USART1_RX_PORT;
  usart_imps[(int8_t)USART_1].usartPinCollection.rx_address.pin = USART1_RX_PIN;
  usart_imps[(int8_t)USART_1].usartPinCollection.rx_s = &semaphores[(int8_t)USART1_RX_PORT][(int8_t)USART1_RX_PIN];
  
  usart_imps[(int8_t)USART_2].usartPinCollection.tx_address.port = USART2_TX_PORT;
  usart_imps[(int8_t)USART_2].usartPinCollection.tx_address.pin = USART2_TX_PIN;
  usart_imps[(int8_t)USART_2].usartPinCollection.tx_s = &semaphores[(int8_t)USART2_TX_PORT][(int8_t)USART2_TX_PIN];
  
  usart_imps[(int8_t)USART_2].usartPinCollection.rx_address.port = USART2_RX_PORT;
  usart_imps[(int8_t)USART_2].usartPinCollection.rx_address.pin = USART2_RX_PIN;
  usart_imps[(int8_t)USART_2].usartPinCollection.rx_s = &semaphores[(int8_t)USART2_RX_PORT][(int8_t)USART2_RX_PIN];
  
  usart_imps[(int8_t)USART_3].usartPinCollection.tx_address.port = USART3_TX_PORT;
  usart_imps[(int8_t)USART_3].usartPinCollection.tx_address.pin = USART3_TX_PIN;
  usart_imps[(int8_t)USART_3].usartPinCollection.tx_s = &semaphores[(int8_t)USART3_TX_PORT][(int8_t)USART3_TX_PIN];
  
  usart_imps[(int8_t)USART_3].usartPinCollection.rx_address.port = USART3_RX_PORT;
  usart_imps[(int8_t)USART_3].usartPinCollection.rx_address.pin = USART3_RX_PIN;
  usart_imps[(int8_t)USART_3].usartPinCollection.rx_s = &semaphores[(int8_t)USART3_RX_PORT][(int8_t)USART3_RX_PIN];
}


/** Declare the ISRptrs
 * 
 * Each USART interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs by way of the function pointer array usartInterrupts[]. Here the
 * ISRs are declared and the user ISR is called if the appropriate element of the function
 * pointer array is non NULL.
 */

ISR(USART0_RX_vect)
{
  /* Clear the RXCn flag in UCSRnA as a safeguard */
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
  /* Clear the RXCn flag in UCSRnA as a safeguard */
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
  /* Clear the RXCn flag in UCSRnA as a safeguard */
    UCSR0A &= (1 << RXC2);
    
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
  /* Clear the RXCn flag in UCSRnA as a safeguard */
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

// ALL DONE.
