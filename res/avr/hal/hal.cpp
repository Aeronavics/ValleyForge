/********************************************************************************************************************************
 *
 *  FILE: 		hal.c
 *
 *  LIBRARY:		hal
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	11-12-2011
 *
 *	Provides important common functionality required to allow using the ValleyForge HAL.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.


// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

bool done_sem_init;

semaphore semaphores[NUM_PORTS][NUM_PINS];
semaphore pc_int_sem[NUM_BANKS];

static bool int_flag = ((SREG & (1 << INT_BIT)) ? true : false);

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

void init_hal(void)
{
    // Attach the gpio pin implementations to the semaphores which control the corresponding pins.
	for (uint8_t i = 0; i < NUM_PORTS; i++)
	{
		for (uint8_t j = 0; j < NUM_PINS; j++)
		{
			semaphores[i][j] = semaphore();
		}
	}
	
	for (uint8_t i = 0; i < NUM_BANKS; i++)
	{
			pc_int_sem[i] = semaphore();
	}
	// We don't need to do this again.
	done_sem_init = true;

	// All done.
	return;
}

void int_on(void)
{
	sei();
}

void int_off(void)
{
	int_flag = ((SREG & (1 << INT_BIT)) ? true : false);
	cli();
}

void int_restore(void)
{
	SREG = (int_flag ? (SREG | (1 << INT_BIT)) : (SREG & ~(1 << INT_BIT)));
}
// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
