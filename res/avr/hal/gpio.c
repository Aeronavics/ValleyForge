/********************************************************************************************************************************
 *
 *  FILE: 			gpio.c
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	7-12-2011
 *
 *	This is the implementation for gpio for the atmega2560.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "gpio.h"
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// The addresses for GPIO are PINA,DDRA,PORTA,PINB,DDRB,PORTB... i.e each type is 3 away from the same on the next port.
#define PORT_MULTIPLIER		3
// So to access a for example PORTC would be 3 * PORT_D(2) + 3 = 0x09.
enum port_offset	{P_READ, P_MODE, P_WRITE};


// DECLARE IMPORTED GLOBAL VARIABLES.
extern semaphore semaphores[NUM_PORTS][NUM_PINS];
extern semaphore pc_int_sem[NUM_BANKS];

/**
 * A Class that implements the functions for gpio
 * One instance for each pin.
 * Reads, writes, and sets direction of pins
 */
class gpio_pin_imp
{
	public:

		// Functions.
		/**
		 * Sets the direction of the pin
		 * by manipulating the data direction register
		 * 
		 * @param mode	the direction (INPUT=0,OUTPUT=1)
		 * @return int8_t error code
		 */
		int8_t set_mode(gpio_mode mode)
		{
				/* Check to see if parameters are right size */
				if (address.port >= NUM_PORTS) 
				{
					/* Parameter is wrong size*/
					return I_ERROR;
				}
				
				/* Set/clear data direction register pin */
				_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_MODE) & ~(1 << address.pin) ) | (mode?(1 << address.pin):~(1 << address.pin));
				
				return 0;
		}

		/**
		 * Writes to the pin attached to the implementation
		 * 
		 * @param value	sets the pin to (O_LOW, O_HIGH, or O_TOGGLE)
		 * @return int8_t error code
		 */
		int8_t write (gpio_output_state value)

		{
				if (address.port >= NUM_PORTS) 
				{
					/* Parameter is wrong size*/
					return I_ERROR;
				}
				/* Set/clear port register register pin */
				if (value == O_TOGGLE)
				{		/*Toggle value*/
				
						_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = (_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | ~(_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE));
				}
				else
				{
						/* Set or Clear pin on port*/
						_SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) = ( _SFR_IO8((address.port * PORT_MULTIPLIER) + P_WRITE) & ~(1 << address.pin) ) | (value?(1 << address.pin):(pin_t)O_LOW);
				}
				return 0;
		}

		/**
		 * Reads the pin attached to the implementation
		 * 
		 * @param Nothing.
		 * @return int8_t error code
		 */
		gpio_input_state read (void)

		{
			
				if (address.port >= NUM_PORTS) 
				{
					/* Parameter is wrong size*/
					return I_ERROR;
				}
			
				/* Read and return pin */
				return ((_SFR_IO8((address.port * PORT_MULTIPLIER) + P_READ) & (1 << address.pin)) ? I_LOW : I_HIGH);
		}
		
		
		/**
		 * Attaches an interrupt to the pin
		 * 
		 * @param Nothing.
		 * @return int8_t error code
		 */
		int8_t init_interrupt(uint8_t mode, void* ISR(void))
		
		{
		    
		  
		}
		// Fields.
		gpio_pin_address address;
		semaphore* s;	
};

// DECLARE PRIVATE GLOBAL VARIABLES.

// One implementation for each pin.
gpio_pin_imp gpio_pin_imps[NUM_PORTS][NUM_PINS];

// To show whether we have carrried out the initialisation yet.
bool done_init;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

void gpio_init(void);

// IMPLEMENT PUBLIC FUNCTIONS.
// See gpio.h for descriptions of these functions.
gpio_pin::~gpio_pin(void)
{
	// Make sure we have vacated the semaphore before we go out of scope.
	vacate();

	// All done.
	return;
}

gpio_pin::gpio_pin(gpio_pin_imp* implementation)
{
	// Attach the implementation.
	imp = implementation;

	// All done.
	return;
}

int8_t gpio_pin::set_mode(gpio_mode mode)
{
	return (imp->set_mode(mode));
}

int8_t gpio_pin::write(gpio_output_state value)
{
	return (imp->write(value));
}

gpio_input_state gpio_pin::read(void)
{
	return (imp->read());
}

bool gpio_pin::is_valid(void)
{
	return (imp != NULL);
}

void gpio_pin::vacate(void)
{
	// Check if we're already vacated, since there shouldn't be an error if you vacate twice.
	if (imp != NULL)
	{		
		// We haven't vacated yet, so vacate the semaphore.
		imp->s->vacate();
	}

	// Break the link to the implementation.
	imp = NULL;

	// The gpio_pin is now useless.
	
	// All done.
	return;
}

gpio_pin gpio_pin::grab(gpio_pin_address address)
{
	// Check if the GPIO stuff has been initialized.
	if (!done_init)
	{
		// Initialize the GPIO stuff.
		gpio_init();
	}

	// Try to procure the semaphore.
	if (gpio_pin_imps[address.port][address.pin].s->procure())
	{
		// We got the semaphore!
		return gpio_pin(&gpio_pin_imps[address.port][address.pin]);
	}
	else
	{
		// Procuring the semaphore failed, so the pin is already in use.
		return NULL;
	}
}


int8_t init_interrupt(uint8_t mode, void* ISR(void))
{
      imp->attach_interrupt(mode,ISR);  
}

// IMPLEMENT PRIVATE FUNCTIONS.

void gpio_init(void)
{
	// Attach the gpio pin implementations to the semaphores which control the corresponding pins.
	for (uint8_t i = 0; i < NUM_PORTS; i++)
	{
		for (uint8_t j = 0; j < NUM_PINS; j++)
		{
			// Attach the semaphores to those in the pin implementations.
			gpio_pin_imps[i][j].s = &semaphores[i][j];
			gpio_pin_imps[i][j].address.port = (port_t)i;
			gpio_pin_imps[i][j].address.pin = (pin_t)j;
		}
	}

	// We don't need to do this again.
	done_init = true;

	// All done.
	return;
}

// ALL DONE.
