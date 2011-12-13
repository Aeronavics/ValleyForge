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

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

#define PORT_MUTLIPLIER		3
enum port_offset	{P_READ, P_MODE, P_WRITE}


// DECLARE IMPORTED GLOBAL VARIABLES.
extern semaphore semaphores[NUM_PORTS][NUM_PINS];


class gpio_pin_imp
{
	public:

		// Functions.

		int8_t pinMode(pin_mode_t mode);
		{
				/* Check to see if parameters are right size */
				
				
				/* Set/clear data direction register pin */
				_SFR_IO8((address->port * PORT_MULTIPLIER) + P_MODE) = (_SFR_IO8((address->port * PORT_MULTIPLIER) + P_MODE) & ~address->pin ) | (mode?address->pin:~address->pin);
				
				return 0;
		}

		
		int8_t pinWrite (pin_state_t value);

		{
			
				/* Set/clear port register register pin */
				if (value == TOGGLE)
				{		/*Toggle value*/
				
						_SFR_IO8((address->port * PORT_MULTIPLIER) + P_WRITE) = (_SFR_IO8((address->port * PORT_MULTIPLIER) + P_WRITE) & ~address->pin ) | ~(_SFR_IO8((address->port * PORT_MULTIPLIER) + P_WRITE));
				}
				else
				{
						/* Set or Clear pin on port*/
						_SFR_IO8((address->port * PORT_MULTIPLIER) + P_WRITE) = ( _SFR_IO8((address->port * PORT_MULTIPLIER) + P_WRITE) & ~address->pin ) | (value?address->pin:O_LOW);
				}
				return 0;
		}

		/* This reads the specified Pin */
		gpio_input_state pinRead (void);

		{
			
				if (address->port >= NUM_PORTS) 
				{
					/* Parameter is wrong size*/
					return I_ERROR;
				}
			
				/* Read and return pin */
				return ((_SFR_IO8((address->port * PORT_MULTIPLIER) + P_READ) & address->pin) ? I_LOW : I_HIGH);
		}

		// Fields.
		gpio_pin_address address;
		semaphore& s;	
};

// DECLARE PRIVATE GLOBAL VARIABLES.

gpio_pin_imp gpio_pin_imps[PORTS][PINS];

bool done_init;

// DEFINE PRIVATE FUNCTION PROTOTYPES.

void gpio_init(void);

// IMPLEMENT PUBLIC FUNCTIONS.

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

int8_t gpio_pin::pinMode(gpio_mode mode)
{
	return (imp->pinMode(mode));
}

int8_t gpio_pin::pinWrite(gpio_output_state value)
{
	return (imp->pinWrite(value));
}

gpio_input_state gpio_pin::pinRead(void)
{
	return (imp->pinRead());
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
		imp->s.vacate();
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
	if (gpio_pin_imps[address.port][address.pin].s.procure())
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

// IMPLEMENT PRIVATE FUNCTIONS.

void gpio_init(void)
{
	// Attach the gpio pin implementations to the semaphores which control the corresponding pins.
	for (uint8_t i = 0; i < NUM_PORTS; i++)
	{
		for (uint8_t j = 0; j < NUM_PINS; j++)
		{
			gpio_pin_imps[i][j].s = semaphores[i][j];
			gpio_pin_imps[i][j].address.port = i;
			gpio_pin_imps[i][j].address.pin = j;
		}
	}

	// We don't need to do this again.
	done_init = true;

	// All done.
	return;
}

// ALL DONE.
