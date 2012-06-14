/**
 * 
 *  @addtogroup		hal	Hardware Abstraction Library
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
 *  @section Licence
 *  LICENCE GOES HERE
 * 
 *  @section Description
 *  In order to use the Hardware Abstraction Library, some aspects need to be set up beforehand. There are also some
 *  functions that are relevant to all modules, such as global interrupts, and are therefore placed in this separate
 *  hal.h header file.
 * 
 *  @section Example
 * 
 *  @code
 *  #include "hal.h"
 *  #include "gpio.h"
 * 
 *  init_hal();
 * 
 *  int_on();
 *  
 *  gpio_pin_address my_pin_address;
 *  my_pin_address.port = PORT_B;
 *  my_pin_address.pin = PIN_5;
 *  gpio_pin my_pin = gpio_pin::grab(my_pin_address);
 *  if (my_pin.is_valid())
 *  {
 *  	my_pin.set_mode(OUTPUT);
 *  	my_pin.write(HIGH);
 *  }
 *  @endcode 
 */

/**
 * @mainpage
 * 
 * Welcome to the ValleyForge Doxygen Documentation.
 * This is a test.
 * A link to a class gpio_pin
 */

// Only include this header file once.
#ifndef __HAL_H__
#define __HAL_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

// Include semaphores.
#include "semaphore.h"

// DEFINE PUBLIC MACROS.



// DEFINE PUBLIC TYPES AND ENUMERATIONS.
// Port and pin enumerations, these should be used by the user when creating a new gpio_pin_address.
enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15}; 

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
 * initialises the hal by creating semaphores and any other initialisation that is required.
 */
void init_hal(void);

/**
 * Enables global interrupts.
 */
void int_on(void);

/**
 * Disables global interrupts.
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
