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
 *  AUTHOR: 		George Xian
 *
 *  DATE CREATED:	12-01-2012
 *
 *	Functionality to provide implementation for SPI in target devices.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE IMPLEMENTATION SPECIFIC HEADER FILES.
#include "hal/gpio.hpp"

// DEFINE PRIVATE MACROS.


// DEFINE DEVICE PARTICULAR REGISTAR ADDRESSES
/* Private define ------------------------------------------------------------*/
#define SPI0_MISO_PORT		PORT_A
#define SPI0_MISO_PIN		PIN_6
#define SPI0_MOSI_PORT		PORT_A
#define SPI0_MOSI_PIN		PIN_7
#define SPI0_SCK_PORT		PORT_A
#define SPI0_SCK_PIN		PIN_5
#define SPI0_SS_PORT		PORT_A
#define SPI0_SS_PIN			PIN_4

#define SPI1_MISO_PORT		PORT_B
#define SPI1_MISO_PIN		PIN_14
#define SPI1_MOSI_PORT		PORT_B
#define SPI1_MOSI_PIN		PIN_15
#define SPI1_SCK_PORT		PORT_B
#define SPI1_SCK_PIN		PIN_13
#define SPI1_SS_PORT		PORT_B
#define SPI1_SS_PIN			PIN_12

#define NUM_SPI_CHANNELS	2
#define NUM_SPI_INTERRUPTS	0	//don't know, won't implement yet

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
	int8_t set_master_slave(spi_configuration configuration);

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
	* Sets the commuincation direction and how many lines are used
	* 
	* @param direction			Direction and line setting from one of the enumeration options
	* @return 0 for success, -1 for error
	*/
	int8_t set_data_direction(spi_data_direction dir);

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
	* Sets the data frame format to 8bit or 16bit
	* 
	* @param data_frame_size	A data frame size from enum options
	* @return 0 for success, -1 for error
	*/
	int8_t set_frame_format(spi_frame_format data_frame_size);
	
	/**
	* Sets the slave select method
	* 
	* @param mode				Option between hardware and software slave select mode
	* @return 0 for success, -1 for error
	*/
	int8_t slave_select_mode(spi_slave_select_mode mode);

	/**
	* Enables an interrupt to be be associated with a SPI connection.
	*
	* @param interrupt		One of the possible interrupt types that are available.
	* @param ISRptr		Pointer to the user-defined ISR.
	* @return 0 for success, -1 for error.
	*/
	int8_t enable_interrupt(spi_interrupt_types interrupt, void (*ISRptr)(void));
	
	/**
	* Enables the SPI channel
	* 
	* @param Nothing.
	* @return 0 for success, -1 for error
	*/
	int8_t enable(void);

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
	* Returns the current status of the SPI buffer
	* 
	* @param Nothing.
	* @return Status of SPI buffer
	*/
	spi_status get_status(void);
	
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
	
	/**
	* Allows SPI to be relinquished
	*/
	void disable(void);
      
	// Public Fields
	/**
	* Address of the register to access SPI functionality 
	*/ 
	SPI_TypeDef* spi_reg_address;
	
	/**
	 * Semaphores of all GPIO pins consumed
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
	int8_t enable(void);
      
	/**
	* Function to deselect the associated SPI Slave device.
	*
	* @param  Nothing.
	* @return Nothing.
	*/
	int8_t disable(void);

	// Fields  
	/**
	* Address of the GPIO pin for which the implementation is associated.
	*/
	gpio_pin_address gpio_address;
      
      	//Private functions & Fields
  private:
};

// DECLARE PRIVATE GLOBAL VARIABLES.
/* Create an array of SPI implementations */
/* Array of user ISRs for SPI interrupts */
void (*spiInterrupts[NUM_SPI_INTERRUPTS])(void) = {};

/* Create an array of SPI implementations */
spi_imp spi_imps[NUM_SPI_CHANNELS];

/* Create an array of SPI slave implementations */
spi_slave_imp spi_slave_imps[NUM_PORTS][NUM_PINS];

/* Variable to indicate whether usart_spi[] has been initialised yet */
bool initialised_spi;

/* Enumerated list of SPI interrupts for use in accessing the appropriate function pointer from the function pointer array */
enum spi_interrupts {SPI_STC_int};


// IMPLEMENT PUBLIC FUNCTIONS.
/* ************************* MASTER ********************************* */
int8_t spi::initialise(spi_configuration configuration)
{
	int8_t ret = imp->set_master_slave(configuration);
	imp->enable();
	return ret;
}

int8_t spi::set_data_mode(spi_mode mode)
{
	imp->set_data_direction(SPI_2LINE_FULL_DUPLEX);
	imp->set_frame_format(SPI_8BIT);	//8bit is compatible with other 8bit targets
	return imp->set_data_mode(mode);
}

int8_t spi::set_bit_order(spi_bit_order order)
{
	return imp->set_bit_order(order);
}

int8_t spi::set_clock_divider(spi_clock_divider divider)
{
	return imp->set_clock_divider(divider);	
}

uint8_t spi::transfer(uint8_t data)
{
	return imp->transfer(data);
}

void spi::transfer_array(uint8_t *TXdata, uint8_t *RXdata, int8_t numberElements)
{
	for (uint8_t i=0; i<numberElements; i++)
	{
		RXdata[i] = transfer(TXdata[i]);	
	}
}

spi::spi(spi_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

spi::~spi(void)
{
	disable();
}

void spi::disable(void)
{
	imp->disable();
	
	//switch off peripheral clock
	RCC->APB2ENR &= ~(1<<12);
	
	//release semaphore
	imp->spiPinCollection.MISO_s->vacate();
	imp->spiPinCollection.MOSI_s->vacate();
	imp->spiPinCollection.SCK_s->vacate();
	imp->spiPinCollection.SS_s->vacate();
}

int8_t spi::set_slave_select_mode(spi_slave_select_mode mode)
{
	return imp->slave_select_mode(mode);
}

spi spi::grab(spi_number spiNumber)
{
	if (!initialised_spi)
	{
		initialise_SPI();
	}
	
	//Enable the peripheral clock
	RCC->APB2ENR |= (1<<12);	//SP1EN 1
	RCC->APB2ENR |= (1<<0);		//AFIOEN 1
	
	switch(spiNumber)
	{
		case(0):	
			//switch on GPIO_A clock
			RCC->APB2ENR |= (1<<2); 
			break;
		case(1):
			//switch on GPIO_B clock
			RCC->APB2ENR |= (1<<3);
			break;
	}
	
	// Try to procure the semaphore.
	int_off();	//must check all semaphore states atomically
	if (spi_imps[spiNumber].spiPinCollection.MISO_s->check_free() 
	    && spi_imps[spiNumber].spiPinCollection.MOSI_s->check_free() 
	    && spi_imps[spiNumber].spiPinCollection.SCK_s->check_free()
	    && spi_imps[spiNumber].spiPinCollection.SS_s->check_free())
	{
		spi_imps[spiNumber].spiPinCollection.MISO_s->procure();
		spi_imps[spiNumber].spiPinCollection.MOSI_s->procure();
		spi_imps[spiNumber].spiPinCollection.SCK_s->procure();
		spi_imps[spiNumber].spiPinCollection.SS_s->procure();
		
		switch (spiNumber)
		{
			case(0):
				//set bits of interest to 0 (GPIOA pin 4, 5, 6, 7)
				GPIOA->CRL &= ~((0b1111<<16) | (0b1111<<20) | (0b1111<<24) | (0b1111<<28));	
				//set pin to alternate function push-pull at 50MHz
				GPIOA->CRL |= ((0b1011<<16) | (0b1011<<20) | (0b1011<<24) | (0b1011<<28));	
				break;
			case(1):
				GPIOB->CRH &= ~((0b1111<<16) | (0b1111<<20) | (0b1111<<24) | (0b1111<<28));	
				GPIOB->CRH |= ((0b1011<<16) | (0b1011<<20) | (0b1011<<24) | (0b1011<<28));	
				break;
		}
		
		int_restore();
		// We got the semaphore!
		return spi(&spi_imps[spiNumber]);
	}
	else
	{
		int_restore();
		// Procuring the semaphores failed, so the pin is already in use.
		return NULL;
	}
}

spi_status spi::get_status(void)
{
	return imp->get_status();
}

/* ************************** SLAVE ********************************* */
spi_slave::spi_slave(spi_slave_imp* implementation)
{
	imp = implementation;
	
	return;
}

int8_t spi_slave::enable(void)
{
	return imp->enable();
}

int8_t spi_slave::disable(void)
{
	return imp->disable();
}

spi_slave spi_slave::attach(gpio_pin_address slaveAddress)
{
	return spi_slave(&spi_slave_imps[slaveAddress.port][slaveAddress.pin]);
}

// IMPLEMENT PRIVATE FUNCTIONS.


// IMPLEMENT SPI IMPLEMENTATION FUNCTIONS
/* ************************** MASTER ******************************** */
int8_t spi_imp::set_master_slave(spi_configuration configuration)
{	
	//set master or slave
	switch(configuration) 
	{
		case(SPI_MASTER):
			spi_reg_address->CR1 |= ((uint32_t) (1<<2));	//MSTR 1
			break;
		case(SPI_SLAVE):
			spi_reg_address->CR1 &= ~((uint32_t) (1<<2));	//MSTR 0
			break;
	}
  
	return 0;
}

int8_t spi_imp::set_data_mode(spi_mode mode)
{	
	//set data frame format to 8bit (to be compatible with supported 8bit targets
	spi_reg_address->CR1 &= ~(1<<11);
	
	spi_reg_address->CR1 |= (1<<15);			//bidirectional mode
	
	spi_reg_address->CR1 &= ((uint32_t) 0b11);	//reset the curret value of selected bit
	switch(mode)
	{
		case(SPI_MODE_0):
			spi_reg_address->CR1 &= ~((uint32_t) (1<<1));	//CPOL 0
			spi_reg_address->CR1 &= ~((uint32_t) (1<<0));	//CPHA 0
			break;
		case(SPI_MODE_1):
			spi_reg_address->CR1 &= ~((uint32_t) (1<<1));	//CPOL 0
			spi_reg_address->CR1 |= ((uint32_t) (1<<0));	//CPHA 1
			break;
		case(SPI_MODE_2):
			spi_reg_address->CR1 |= ((uint32_t) (1<<1));	//CPOL 1
			spi_reg_address->CR1 &= ~((uint32_t) (1<<0));	//CPHA 0
			break;
		case(SPI_MODE_3):
			spi_reg_address->CR1 |= ((uint32_t) (1<<1));	//CPOL 1
			spi_reg_address->CR1 |= ((uint32_t) (1<<1));	//CPHA 1
			break;
	}
	return 0;
}

int8_t spi_imp::set_data_direction(spi_data_direction dir)
{
	switch(dir)
	{
		case(SPI_2LINE_FULL_DUPLEX):
			spi_reg_address->CR1 &= ~((uint32_t) 1<<15);	//BIDIMODE 0
			spi_reg_address->CR1 &= ~((uint32_t) 1<<14);	//BIODE 0
			spi_reg_address->CR1 &= ~((uint32_t) 1<<10);	//RXONLY 0
			break;
		case(SPI_2LINE_RX):
			spi_reg_address->CR1 |= ((uint32_t) 1<<10);		//RXONLY 1
			spi_reg_address->CR1 &= ~((uint32_t) 1<<15);	//BIDIMODE 0
			spi_reg_address->CR1 &= ~((uint32_t) 1<<14);	//BIODE 0
			break;
		case(SPI_1LINE_RX):
			spi_reg_address->CR1 |= ((uint32_t) 1<<15);		//BIDIMODE 1
			spi_reg_address->CR1 &= ~((uint32_t) 1<<14);	//BIODE 0
			spi_reg_address->CR1 &= ~((uint32_t) 1<<10);	//RXONLY 0
			break;
		case(SPI_1LINE_TX):
			spi_reg_address->CR1 |= ((uint32_t) 0b11<<14);	//BIMODE 1, BIODE 1
			spi_reg_address->CR1 &= ~((uint32_t) 1<<10);	//RXONLY 0
			break;
	}
	
	return 0;
}

int8_t spi_imp::set_bit_order(spi_bit_order order)
{
	switch(order)
	{
		case(MSB_FIRST):
			spi_reg_address->CR1 &= ~((uint32_t) (1<<7));	//LSBFIRST 0
			break;
		case(LSB_FIRST):
			spi_reg_address->CR1 |= ((uint32_t) (1<<7));	//LSBFIRST 1
			break;
	}
	return 0;
}

int8_t spi_imp::set_clock_divider(spi_clock_divider divider) 
{
	//create the required value for the SPIx->CR1 bit for selected baud rate
	uint32_t BR = divider;						
	uint32_t tempreg = spi_reg_address->CR1;
	//make sure that bits of the register's value that are going to be set are 0 before being set
	tempreg &= ~((uint32_t) 0b111<<3);			
	//create the final value for the CR1 register
	tempreg |= (BR<<3);							
	spi_reg_address->CR1 = tempreg;		
	
	return 0;	
}

int8_t spi_imp::set_frame_format(spi_frame_format data_frame_size)
{
	switch(data_frame_size)
	{
		case(SPI_8BIT):
			spi_reg_address->CR1 &= ~(1<<11);	//DFF 0
			break;
		case(SPI_16BIT):
			spi_reg_address->CR1 |= (1<<11);	//DFF 1
			break;
	}
	return 0;
}

int8_t spi_imp::slave_select_mode(spi_slave_select_mode mode)
{
	switch(mode)
	{
		case(SPI_HARDWARE_SS):
			spi_reg_address->CR1 |= (1<<9);
			break;
		case(SPI_SOFTWARE_SS):
			spi_reg_address->CR1 &= ~(1<<9);
			break;
	}
	return 0;
}

int8_t spi_imp::enable(void)
{
	spi_reg_address->CR1 |= ((uint32_t) (1 << 6));	//SPE 1
	
	return 0;
}

void spi_imp::disable(void)
{
	spi_reg_address->CR1 &= ((uint32_t) (1 << 6));	//SPE 0
}

uint8_t spi_imp::transfer(uint8_t data)
{
	//copy received message (if exists) to memory
	uint8_t rec_msg = spi_reg_address->DR;	
	
	spi_reg_address->DR = data;
	
	return rec_msg;
}

spi_status spi_imp::get_status(void)
{
	uint16_t status = spi_reg_address->SR;	//copy for test integrity
	
	switch(status)
	{
		case(1<<0):
			return SPI_RXNE;
		case(1<<1):
			return SPI_TXE;
		case(1<<2):
			return SPI_CHSIDE;
		case(1<<3):
			return SPI_UNDERRUN;
		case(1<<4):
			return SPI_CRCERR;
		case(1<<5):
			return SPI_MODEFAULT;
		case(1<<6):
			return SPI_OVERRUN;
		case(1<<7):
			return SPI_BUSY;
	}
}

/* *************************** SLAVE ******************************** */
int8_t spi_slave_imp::enable(void)
{
	gpio_pin SS = gpio_pin::grab(gpio_address);
	
	if (true) 	//TODO: if semaphore successful
	{
		SS.set_mode(OUTPUT_PP);
		SS.write(O_LOW);
		SS.vacate();
		return 0;
	}
	else
	{
		return -1;
	}	
}

int8_t spi_slave_imp::disable(void)
{
	gpio_pin SS = gpio_pin::grab(gpio_address);
	
	if (true) 	//TODO: if semaphore successful
	{
		SS.set_mode(OUTPUT_PP);
		SS.write(O_HIGH);
		SS.vacate();
		return 0;
	}
	else
	{
		return -1;
	}	
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
	for (uint8_t i=0; i<NUM_SPI_CHANNELS; i++)
	{
		//store the address of the register as a field
		spi_imps[i].spi_reg_address = (SPI_TypeDef*) (SPI1_BASE + 0x800*i);
		
		//NB: 2 SPI channels on STM32F103
		switch(i)
		{
			case(0):
				spi_imps[i].spiPinCollection.MISO_address.port = SPI0_MISO_PORT;
				spi_imps[i].spiPinCollection.MISO_address.pin = SPI0_MISO_PIN;
				spi_imps[i].spiPinCollection.MISO_s = &semaphores[SPI0_MISO_PORT][SPI0_MISO_PIN];
				
				spi_imps[i].spiPinCollection.M0SI_address.port = SPI0_MOSI_PORT;
				spi_imps[i].spiPinCollection.M0SI_address.pin = SPI0_MOSI_PIN;
				spi_imps[i].spiPinCollection.MOSI_s = &semaphores[SPI0_MOSI_PORT][SPI0_MOSI_PIN];
				
				spi_imps[i].spiPinCollection.SCK_address.port = SPI0_SCK_PORT;
				spi_imps[i].spiPinCollection.SCK_address.pin = SPI0_SCK_PIN;
				spi_imps[i].spiPinCollection.MOSI_s = &semaphores[SPI0_SCK_PORT][SPI0_SCK_PIN];
				
				spi_imps[i].spiPinCollection.SS_address.port = SPI0_SS_PORT;
				spi_imps[i].spiPinCollection.SS_address.pin = SPI0_SS_PIN;
				spi_imps[i].spiPinCollection.SS_s = &semaphores[SPI0_SS_PORT][SPI0_SS_PIN];
				
				break;
			case(1):
				spi_imps[i].spiPinCollection.MISO_address.port = SPI1_MISO_PORT;
				spi_imps[i].spiPinCollection.MISO_address.pin = SPI1_MISO_PIN;
				spi_imps[i].spiPinCollection.MISO_s = &semaphores[SPI1_MISO_PORT][SPI1_MISO_PIN];
				
				spi_imps[i].spiPinCollection.M0SI_address.port = SPI1_MOSI_PORT;
				spi_imps[i].spiPinCollection.M0SI_address.pin = SPI1_MOSI_PIN;
				spi_imps[i].spiPinCollection.MOSI_s = &semaphores[SPI1_MOSI_PORT][SPI1_MOSI_PIN];
				
				spi_imps[i].spiPinCollection.SCK_address.port = SPI1_SCK_PORT;
				spi_imps[i].spiPinCollection.SCK_address.pin = SPI1_SCK_PIN;
				spi_imps[i].spiPinCollection.MOSI_s = &semaphores[SPI1_SCK_PORT][SPI1_SCK_PIN];
				
				spi_imps[i].spiPinCollection.SS_address.port = SPI1_SS_PORT;
				spi_imps[i].spiPinCollection.SS_address.pin = SPI1_SS_PIN;
				spi_imps[i].spiPinCollection.SS_s = &semaphores[SPI1_SS_PORT][SPI1_SS_PIN];
			
				break;
		}		
	}
	
	for (uint8_t i=0; i<NUM_PORTS; i++)
	{
		for(uint8_t j=0; j<NUM_PINS; j++)
		{
			spi_slave_imps[i][j].gpio_address.port = (port_t) i;
			spi_slave_imps[i][j].gpio_address.pin = (pin_t) j;
		}
	}
	
	initialised_spi = true;
}
