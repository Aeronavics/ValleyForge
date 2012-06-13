/**
 *
 *  @file 		
 *  Sets up the hal, defines types and enumerations, and regulates semaphores. This is the header file which matches hal.c.  
 *  It provides important common functionality required to allow using the ValleyForge HAL.
 *
 *  @addtogroup		hal	Hardware Abstraction Library
 *
 *  @author		Edwin Hayes
 *
 *  @date		11-12-2011
 *
 * 
 */

/**
 * @mainpage
 * 
 * Welcome to the ValleyForge Doxygen Documentation.
 * This is a test.
 * A link to a class <gpio_pin>
 **/

// Only include this header file once.
#ifndef __HAL_H__
#define __HAL_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// Include semaphores.
#include "semaphore.h"

// DEFINE PUBLIC MACROS.

/* The constants that allow access to the Port registers in memory (DDRx, PORTx & PINx) */
/* NB: ATmega 2560 particular */
#define PORT_MULTIPLIER		3
#define P_OFFSET		235

// DEFINE PUBLIC TYPES AND ENUMERATIONS.

enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14}; 

/* Offset constants that facilitate access to the particular GPIO registers (DDRx, PORTx, PINx) */
enum port_offset	{P_READ, P_MODE, P_WRITE};

struct gpio_pin_address
{
	port_t port;
	pin_t pin;
};

// INCLUDE REQUIRED HEADER FILES THAT DEPEND ON TYPES DEFINED HERE.
#include "target_config.h"

// DECLARE PUBLIC GLOBAL VARIABLES.

// DEFINE PUBLIC FUNCTION PROTOTYPES.


/**
 * initialises the hal by creating semaphores and such.
 * 
 * @param none
 * @return none
 */
void init_hal(void);

/**
 * Enables global interrupts.
 * 
 * @param none
 * @return none
 */
void int_on(void);

/**
 * Disables global interrupts.
 * 
 * @param none
 * @return none
 */
void int_off(void);

/**
 * Restores interrupts to the state they were in before int_off was called.
 * 
 * @param none
 * @return none
 */
void int_restore(void);

#endif /*__HAL_H__*/

// ALL DONE.
