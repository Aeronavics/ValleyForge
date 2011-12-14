/********************************************************************************************************************************
 *
 *  FILE: 		hal.h
 *
 *  LIBRARY:		hal
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	11-12-2011
 *
 *	This is the header file which matches hal.c.  It provides important common functionality required to allow using the
 *	ValleyForge HAL.
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __HAL_H__
#define __HAL_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// Include semaphores.
#include "semaphore.h"

// DEFINE PUBLIC MACROS.

#define PINS <<<TC_INSERTS_NUMBER_OF_PINS_HERE>>>

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

#if defined (__AVR_ATmega2560__)
#	define NUM_PORTS		12
#elif defined (__AVR_ATmega64M1__)
#	define NUM_PORTS		4
#elif defined (__AVR_AT90CAN128__)
	#define	NUM_PORTS		6
	
#endif
#define NUM_PINS			8
#define TOTAL_PINS			NUM_PORTS * PINS_PER_PORT

enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_I, PORT_J, PORT_K, PORT_L};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14}; 

// DECLARE PUBLIC GLOBAL VARIABLES.

extern semaphore semaphores[NUM_PORTS][NUM_PINS];

// DEFINE PUBLIC FUNCTION PROTOTYPES.

void init_hal(void);

#endif /*__HAL_H__*/

// ALL DONE.
