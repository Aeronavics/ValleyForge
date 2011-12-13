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

typedef uint8_t port_t;
typedef uint8_t pin_t;

enum port {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_I, PORT_J, PORT_K, PORT_L};

// DECLARE PUBLIC GLOBAL VARIABLES.

extern semaphore semaphores[];

// DEFINE PUBLIC FUNCTION PROTOTYPES.

#endif /*__HAL_H__*/

// ALL DONE.
