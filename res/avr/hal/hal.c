/********************************************************************************************************************************
 *
 *  FILE: 		    hal.c
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

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

#ifdef (__AVR_ATmega2560__)
	#define NUM_PORTS		12
#elif defined (__AVR_ATmega64M1__)
	#define NUM_PORTS		4
#elif defined (__AVR_AT90CAN128__)
	#define	NUM_PORTS		6
	
#endif
#define NUM_PINS			8
#define TOTAL_PINS			NUM_PORTS * PINS_PER_PORT

semaphore semaphores[NUM_PORTS][NUM_PINS];

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
