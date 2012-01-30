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

#include "spi.h"

// INCLUDE SYSTEM HEADER FILES

#include <avr/io.h>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// DEFINE DEVICE PARTICULAR REGISTAR ADDRESSES
#if defined (__AVR_ATmega2560__)

    /* Address locations of registers for SPI */
#	define SPCR_ADDRESS		0x2C	//_SFR_IO8() accessible!
#	define SPSR_ADDRESS		0x2D	//_SFR_IO8() accessible!
#	define SPDR_ADDRESS		0x2E	//_SFR_IO8() accessible!

    /* Port addresses for GPIO pins required for SPI */
#	define SPI0_MISO_PORT		PORT_B
#	define SPI0_MISO_PIN		PIN_3
#	define SPI0_MOSI_PORT		PORT_B
#	define SPI0_MOSI_PIN		PIN_2
#	define SPI0_SCK_PORT		PORT_B
#	define SPI0_SCK_PIN		PIN_1
#	define SPI0_SS_PORT		PORT_B
#	define SPI0_SS_PIN		PIN_0

    /* Generic bit addresses for register manipulation */

   /* GPIO addresses of transmitter and receiver pins for each SPIchannel */

    /* General preprocessor macros for convenience */
#	define NUM_SPI_CHANNELS		1
#	define NUM_SPI_INTERRUPTS	1

#endif

/*
 * Structure to contain all the required register addresses that are needed for the SPI instance functionality
 */
typedef struct REGISTER_ADDRESS_TABLE {
  int16_t SPCR_address;
  int16_t SPSR_address;
  int16_t SPDR_address;
} registerAddressTable_t;

/*
 * Structure to contain the GPIO pin addresses and associated semaphores that represent the peripheral pins for all the SPI channels.
 */
typedef struct SPI_PINS {
  semaphore *MISO_s;
  gpio_pin_address MISO_address;
  semaphore *MOSI_s;
  gpio_pin_address M0SI_address;
  semaphore *SCK_s;
  gpio_pin_address SCK_address;
  semaphore *SS_s;
  gpio_pin_address SS_address;  
} spiPins_t;

// DECLARE IMPORTED GLOBAL VARIABLES
extern semaphore semaphores[NUM_PORTS][NUM_PINS];

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
* Initialises the SPI implementation instances and codes the required
* register addresses, semaphore addresses and GPIO locations.
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
class spi_imp
{
    public:
      
	// Functions
	/**
	* Initialises the SPI interface with the desired Master/Slave parameters and configures the
	* relevant GPIO.
	* 
	* @param  configuration	Configuration for SPI interface (master/slave)
	* @return 0 for success, -1 for error.
	*/
	int8_t initialise(spi_configuration configuration);

	/**
	* Initialises the SPI interface with the desired data mode.
	* Options relate to the combinations of clock polarity & phase
	* settings.
	* 
	* @param  mode			SPI mode to apply to the interface
	* @return 0 for success, -1 for error.
	*/		
	int8_t set_data_mode(spi_mode mode);

	/**
	* Initialises the SPI interface with the desired bit order.
	* Interface can either move the Most-Significant-Bit (MSB) first, or else
	* the Least-Significant-Bit (LSB).
	* 
	* @param  order		Required data order (MSB first or LSB first)
	* @return 0 for success, -1 for error.
	*/		
	int8_t set_bit_order(spi_bit_order order);

	/**
	* Sets the clock divider to be used for the SPI interface.
	*
	* @param divider		A clock divider from one of the enumerated options.
	* @return 0 for success, -1 for error.
	*/
	int8_t set_clock_divider(spi_clock_divider divider);

	/**
	* Enables an interrupt to be be associated with a SPI connection.
	*
	* @param interrupt		One of the possible interrupt types that are available.
	* @param ISRptr		Pointer to the user-defined ISR.
	* @return 0 for success, -1 for error.
	*/
	int8_t enable_interrupt(spi_interrupt_types interrupt, void (*ISRptr)(void));

	/**
	* Enables an interrupt to be be un-associated with a SPI connection.
	*
	* @param interrupt		Which interrupt to disable.
	* @return 0 for success, -1 for error.
	*/
	int8_t disable_interrupt(spi_interrupt_types interrupt);
	
	/**
	* Transfers a byte and receives a byte via the SPI connection 
	*
	* @param data		Byte to transfer via SPI.
	* @return Byte received.
	*/
	uint8_t transfer(uint8_t data);
	
	/**
	* Transfers an array and receives an array of predetermined size via the SPI connection.
	* Note, this function 'blocks' until transfer has been completed. 
	*
	* @param TXdata		Pointer to the array that is to be transmitted.
	* @param RXdata		Pointer to an array where data may be received to.
	* @param numberElements	Number of elements in the arrays (assumed to be the same).
	* @return void.
	*/
	void transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements);
	
	/**
	* Transfers a block of data and receives data via the SPI connection.
	* Note, this function relies on using DMA or similar to achieve 'non-blocking' operation.
	*
	* @param TXdata		Pointer to the array that is to be transmitted.
	* @param RXdata		Pointer to an array where data may be received to.
	* @param numberElements	Number of elements in the arrays (assumed to be the same).
	* @return void.
	*/
	void dma_transfer(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements);
      
	// Public Fields
	/**
	 * Register Address table to store the addresses of the particular SPI 
	 * registers when a SPI is instantiated and initialised.
	 */
	registerAddressTable_t registerTable;
	
	/**
	 * Collection to contain the GPIO addresses and semaphores associated with
	 * each of the GPIO pins which are to be attached to the SPI isntance.
	 */
	spiPins_t spiPinCollection;
		
	//Private functions & Fields
  private:
	
};

/**
 * Class to implement the functionality
 * required for the SPI Slave.
 */
class spi_slave_imp
{
    public:
      
      // Functions
      /**
	* Function to select the associated SPI Slave device and transfer data to/from it.
	*
	* @param  Nothing.
	* @return Nothing.
	*/
	void enable(void)
	{
	  /* Set pin low to enable slave */
	  if (gpio_address.port >= PORT_H)	/* Apply P_OFFSET and use _MEM8 macro if port >= Port H */
	    /* Clear pin on port*/
	    _SFR_MEM8((gpio_address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) &= ~(1 << gpio_address.pin);
	  else
	    /* Set or Clear pin on port*/
	    _SFR_IO8((gpio_address.port * PORT_MULTIPLIER) + P_WRITE) &= ~(1 << gpio_address.pin);	
	}
      
	/**
	  * Function to deselect the associated SPI Slave device.
	  *
	  * @param  Nothing.
	  * @return Nothing.
	  */
	  void disable(void)
	  {
	    /* Set pin high to disable slave */
	    if (gpio_address.port >= PORT_H)	/* Apply P_OFFSET and use _MEM8 macro if port >= Port H */
	      /* Clear pin on port*/
	      _SFR_MEM8((gpio_address.port * PORT_MULTIPLIER) + P_OFFSET + P_WRITE) |= (1 << gpio_address.pin);
	    else
	      /* Set or Clear pin on port*/
	      _SFR_IO8((gpio_address.port * PORT_MULTIPLIER) + P_WRITE) |= (1 << gpio_address.pin);	
	  }

	// Fields      
	/**
	* Semaphore for the Slave Select (SS') pin of the slave attached
	*/
	semaphore* s;
	
	/**
	* Address of the GPIO pin for which the implementation is associated.
	*/
	gpio_pin_address gpio_address;
      
      	//Private functions & Fields
  private:
};

// DECLARE PRIVATE GLOBAL VARIABLES.

/* Array of user ISRs for SPI interrupts */
void (*spiInterrupts[NUM_SPI_INTERRUPTS])(void) = {NULL};

/* Create an array of SPI implementations */
spi_imp spi_imps[NUM_SPI_CHANNELS];

/* Create an array of SPI slave implementations */
spi_slave_imp spi_slave_imps[NUM_PORTS][NUM_PINS];

/* Variable to indicate whether usart_spi[] has been initialised yet */
bool initialised_spi;

/* Enumerated list of SPI interrupts for use in accessing the appropriate function pointer from the function pointer array */
enum spi_interrupts {SPI_STC_int};

// IMPLEMENT PUBLIC FUNCTIONS.

/**
* Initialises the SPI interface with the desired Master/Slave parameters and configures the
* relevant GPIO.
* 
* @param  configuration	Configuration for SPI interface (master/slave)
* @return 0 for success, -1 for error.
*/
int8_t spi::initialise(spi_configuration configuration)
{
  return (imp->initialise(configuration));
}

/**
* Initialises the SPI interface with the desired data mode.
* Options relate to the combinations of clock polarity & phase
* settings.
* 
* @param  mode			SPI mode to apply to the interface
* @return 0 for success, -1 for error.
*/		
int8_t spi::set_data_mode(spi_mode mode)
{
  return (imp->set_data_mode(mode));
}

/**
* Initialises the SPI interface with the desired bit order.
* Interface can either move the Most-Significant-Bit (MSB) first, or else
* the Least-Significant-Bit (LSB).
* 
* @param  order		Required data order (MSB first or LSB first)
* @return 0 for success, -1 for error.
*/		
int8_t spi::set_bit_order(spi_bit_order order)
{
  return (imp->set_bit_order(order));
}

/**
* Sets the clock divider to be used for the SPI interface.
*
* @param divider		A clock divider from one of the enumerated options.
* @return 0 for success, -1 for error.
*/
int8_t spi::set_clock_divider(spi_clock_divider divider)
{
  return (imp->set_clock_divider(divider));
}

/**
* Enables an interrupt to be be associated with a SPI connection.
*
* @param interrupt		One of the possible interrupt types that are available.
* @param ISRptr		Pointer to the user-defined ISR.
* @return 0 for success, -1 for error.
*/
int8_t spi::enable_interrupt(spi_interrupt_types interrupt, void (*ISRptr)(void))
{
  return (imp->enable_interrupt(interrupt, ISRptr));
}

/**
* Enables an interrupt to be be un-associated with a SPI connection.
*
* @param interrupt		Which interrupt to disable.
* @return 0 for success, -1 for error.
*/
int8_t spi::disable_interrupt(spi_interrupt_types interrupt)
{
  return (imp->disable_interrupt(interrupt));
}

/**
* Transfers a byte and receives a byte via the SPI connection 
*
* @param data		Byte to transfer via SPI.
* @return Byte received.
*/
uint8_t spi::transfer(uint8_t data)
{
  return (imp->transfer(data));
}

/**
* Transfers an array and receives an array of predetermined size via the SPI connection.
* Note, this function 'blocks' until transfer has been completed. 
*
* @param TXdata		Pointer to the array that is to be transmitted.
* @param RXdata		Pointer to an array where data may be received to.
* @param numberElements	Number of elements in the arrays (assumed to be the same).
* @return void.
*/
void spi::transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
  (imp->transfer_array(TXdata, RXdata, numberElements));
}

/**
* Transfers a block of data and receives data via the SPI connection.
* Note, this function relies on using DMA or similar to achieve 'non-blocking' operation.
*
* @param TXdata		Pointer to the array that is to be transmitted.
* @param RXdata		Pointer to an array where data may be received to.
* @param numberElements	Number of elements in the arrays (assumed to be the same).
* @return void.
*/
void spi::dma_transfer(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
  /* Check to see if the target is capable of DMA/PDCA transfer */
  //# if defined (__etc__)
  
  (imp->dma_transfer(TXdata, RXdata, numberElements));
}

/**
* Function to free the SPI instance when it goes out of scope.
*
* @param  Nothing.
* @return Nothing.
*/
spi::~spi(void)
{
  disable();
}

/** 
* Allows access to the SPI to be relinquished and reused elsewhere.
*
* @param  Nothing.
* @return Nothing.
*/
void spi::disable(void)
{
  /* Disable the SPI connection */
  
  /* Release the semaphores associated with the SPI interface */
  
  /* Clear/reset the SPI interrupt vector to prevent it from firing */
}

/**
* Allows a process to request access to a SPI instance and manages the semaphore
* indicating whether access has been granted or not.
*
* @param  spiNumber	The number of a SPI that is desired.
* @return A SPI instance.
*/
spi spi::grab(spi_number spiNumber)
{
  /* Add possible semaphore functionality here */
  
  /* Initialise SPI if it is not already initialised */
  if (!initialised_spi)
  {
    //Initialise USART
    initialise_SPI();
  }
  
  /* Set the local field 'imp' pointer to point to the specific
   * implementation of spi_imp. Check that the semaphores of all crucial GPIO required for SPI interface are available. */
//   if (spi_imps[(int8_t)spiNumber].spiPinCollection.tx_s->procure() && spi_imps[(int8_t)spiNumber].spiPinCollection.rx_s->procure())
//     return spi(&spi_imps[(int8_t)spiNumber]);
//   else
    return NULL;
}

// IMPLEMENT PRIVATE FUNCTIONS.

spi::spi(spi_imp* implementation)
{
  /*attach the SPI implementation*/
  imp = implementation;
}

// IMPLEMENT SPI IMPLEMENTATION FUNCTIONS

/**
* Initialises the SPI interface with the desired Master/Slave parameters and configures the
* relevant GPIO.
* 
* @param  configuration	Configuration for SPI interface (master/slave)
* @return 0 for success, -1 for error.
*/
int8_t spi_imp::initialise(spi_configuration configuration)
{
  /* Turn on the transmission and reception hardware circuitry */
   
  /* 
   * Switch which mode to set the USART up for, depending on what is provided 
   */
//   switch (configuration)
//   {
//     
//   }
  
  return 0;
}

/**
* Initialises the SPI interface with the desired data mode.
* Options relate to the combinations of clock polarity & phase
* settings.
* 
* @param  mode			SPI mode to apply to the interface
* @return 0 for success, -1 for error.
*/		
int8_t spi_imp::set_data_mode(spi_mode mode)
{
  /* Manipulate the registers depending on which mode is supplied */
//   switch (mode)
//   {
//   }
  
  return 0;
}

/**
* Initialises the SPI interface with the desired bit order.
* Interface can either move the Most-Significant-Bit (MSB) first, or else
* the Least-Significant-Bit (LSB).
* 
* @param  order		Required data order (MSB first or LSB first)
* @return 0 for success, -1 for error.
*/		
int8_t spi_imp::set_bit_order(spi_bit_order order)
{
   /* Manipulate the registers depending on which data order is supplied */
//   switch (mode)
//   {
//   }
  
  return 0;
}

/**
* Sets the clock divider to be used for the SPI interface.
*
* @param divider		A clock divider from one of the enumerated options.
* @return 0 for success, -1 for error.
*/
int8_t spi_imp::set_clock_divider(spi_clock_divider divider)
{
  /* Manipulate the registers depending on which clock divider is supplied */
//   switch (mode)
//   {
//   }

  return 0;
}

/**
* Enables an interrupt to be be associated with a SPI connection.
*
* @param interrupt		One of the possible interrupt types that are available.
* @param ISRptr		Pointer to the user-defined ISR.
* @return 0 for success, -1 for error.
*/
int8_t spi_imp::enable_interrupt(spi_interrupt_types interrupt, void (*ISRptr)(void))
{
  /* Place the user ISR in the relevant element of the ISR function pointer array */
  
  return 0;
}

/**
* Enables an interrupt to be be un-associated with a SPI connection.
*
* @param interrupt		Which interrupt to disable.
* @return 0 for success, -1 for error.
*/
int8_t spi_imp::disable_interrupt(spi_interrupt_types interrupt)
{
  /* Remove the user ISR from the relevant element of the ISR function pointer array */
  
  return 0;
}

/**
* Transfers a byte and receives a byte via the SPI connection 
*
* @param data		Byte to transfer via SPI.
* @return Byte received.
*/
uint8_t spi_imp::transfer(uint8_t data)
{
  /* Transfer the byte to the SPI data register */
  
  /* Check the transmission is complete... */
  
  /* Check the receive is complete */
  
  /* Return the received contents of the SPI data register */
  
  return 0;
}

/**
* Transfers an array and receives an array of predetermined size via the SPI connection.
* Note, this function 'blocks' until transfer has been completed. 
*
* @param TXdata		Pointer to the array that is to be transmitted.
* @param RXdata		Pointer to an array where data may be received to.
* @param numberElements	Number of elements in the arrays (assumed to be the same).
* @return void.
*/
void spi_imp::transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
  for (uint8_t i = 0; i < numberElements; i++)
  {
    /* Check to see if there is room in the SPI register */
    
    /* transfer the byte from the TXdata array and receive a byte into the RXdata array */
    *RXdata = transfer(*TXdata);
    
    /* Increment the pointers */
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
*/
void spi_imp::dma_transfer(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
  /* Initialise the DMA controller for SPI */
  
  /* Provide the data to transmit ad the location of the received byte */
  
}

// IMPLEMENT EXTRANEOUS FUNCTIONS
/**
* Initialises the SPI implementation instances and codes the required
* register addresses, semaphore addresses and GPIO locations.
*
* @param void.
* @return void.
*/
void initialise_SPI(void)
{
  /* Initialise each SPI with its particular SPI number */
//   for (uint8_t i = 0; i < NUM_SPI_CHANNELS; i++)
//   {
//     spi_imps[i].spiNumber = (spi_number)i;
//   }
//   
//   /* Assign the addresses of the register locations */
//   spi_imps[(int8_t)SPI_0].registerTable.SPCR_address = SPCR_ADDRESS;
//   spi_imps[(int8_t)SPI_0].registerTable.SPSR_address = SPSR_ADDRESS;
//   spi_imps[(int8_t)SPI_0].registerTable.SPDR_address = SPDR_ADDRESS;
//   
//   /* Assign the GPIO addresses and semaphore addresses for each SPI instance */
//   spi_imps[(int8_t)SPI_0].spiPinCollection.MISO_address.port = SPI0_MISO_PORT;
//   spi_imps[(int8_t)SPI_0].spiPinCollection.tx_address.pin = SPI0_MISO_PIN;
//   spi_imps[(int8_t)SPI_0].spiPinCollection.tx_s = &semaphores[(int8_t)SPI0_MISO_PORT][(int8_t)SPI0_MISO_PIN];
//   
//   etc.
}


/** Declare the ISRptrs
 * 
 * Each SPI interrupt type is tied to a relevant interrupt vector. These are associated
 * with the user ISRs by way of the function pointer array spiInterrupts[]. Here the
 * ISRs are declared and the user ISR is called if the appropriate element of the function
 * pointer array is non NULL.
 */

ISR(SPI_STC_vect)
{
  if (spiInterrupts[SPI_STC_int])  
    spiInterrupts[SPI_STC_int]();
}

/**
 * Implement the functions required for the SPI slave instances
 */

/**
* Function to select the associated SPI Slave device and transfer data to/from it.
*
* @param  Nothing.
* @return Nothing.
*/
void spi_slave::enable(void)
{
  /* Set the slave IO pin LOW to select */
  (imp->enable());
}

/**
* Function to deselect the associated SPI Slave device.
*
* @param  Nothing.
* @return Nothing.
*/
void spi_slave::disable(void)
{
  /* Set the slave IO pin HIGH to de-select */
 (imp->disable());
}

/** 
* Allows access to the SPI Slave to be relinquished and reused elsewhere.
*
* @param  Nothing.
* @return Nothing.
*/
void spi_slave::vacate(void)
{
  /* Check to make sure the instance has not already been vacated */
  if (imp != NULL)
  {
    /* Give up the semaphore for the slave */
    imp->s->vacate();
    
    imp = NULL;
  } 
  
}

/**
* Function to free the SPI slave instance when it goes out of scope.
*
* @param  Nothing.
* @return Nothing.
*/
spi_slave::~spi_slave(void)
{
  vacate();
}

/**
* Allows a process to request attachment of a SPI Slave and manages the semaphore
* indicating whether access has been granted or not.
*
* @param  slaveAddress		The GPIO address of the slave select (SS') pin that is to be attached.
* @return A SPI slave instance.
*/
spi_slave spi_slave::attach(gpio_pin_address slaveAddress)
{
  /* Assign the address of the semaphore in semaphores array */
  spi_slave_imps[slaveAddress.port][slaveAddress.pin].s = &semaphores[slaveAddress.port][slaveAddress.pin];
    
  /* Grab the semaphore of the pin for which the user has provided the slaveAddress */
  if (spi_slave_imps[slaveAddress.port][slaveAddress.pin].s->procure())
  {
    /* Fill the GPIO address field in the implementation with the GPIO address of the slave */
    spi_slave_imps[slaveAddress.port][slaveAddress.pin].gpio_address.port = slaveAddress.port;
    spi_slave_imps[slaveAddress.port][slaveAddress.pin].gpio_address.pin = slaveAddress.pin;
    
    /* Initialise the Slave GPIO pin as an output */
    if (slaveAddress.port >= PORT_H)
      _SFR_MEM8((slaveAddress.port * PORT_MULTIPLIER) + P_OFFSET + P_MODE) |= (1 << slaveAddress.pin);
    else
      _SFR_IO8((slaveAddress.port * PORT_MULTIPLIER) + P_MODE) |= (1 << slaveAddress.pin);

    return spi_slave(&spi_slave_imps[slaveAddress.port][slaveAddress.pin]);
  }
  else
    return NULL;
}

// IMPLEMENT PRIVATE FUNCTIONS.

spi_slave::spi_slave(spi_slave_imp* implementation)
{
  /*attach the SPI Slave implementation*/
  imp = implementation;
}

// ALL DONE.
