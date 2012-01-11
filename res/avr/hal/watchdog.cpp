/********************************************************************************************************************************
 *
 *  FILE: 		watchdog.c
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Paul Bowler
 *
 *  DATE CREATED:	14-12-2011
 *
 *	Description Provides functionality for the watchdog processor timers utilised in the ATmega2560.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "watchdog.h"

// INCLUDE REQUIRED HEADER FILES.
#include <avr/wdt.h>
#include <avr/interrupt.h>

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

// IMPLEMENT PUBLIC FUNCTIONS.

/**
* Gets run whenever the instance of class gpio_pin goes out of scope.
* Does nothing, since the watchdog class cannot be instantiated.
*
* @param  Nothing.
* @return Nothing.
*/
watchdog::~watchdog(void)
{
	//Nothing required.
}

/**
* Resets the watchdog timer so it doesn't overflow and trigger a system reset.
* 
* @param  Nothing.
* @return Nothing.
*/
void watchdog::pat(void)
{
	/*Reset the watch dog timer before the timer expires
	to avoid a watchdog-initiated device reset*/
	wdt_reset();
}

/**
 * Sets the timeout of the watchdog timer and starts the watchdog running.
 * 
 * @param time_out	One of 10 possible different values for the timeout value of the watchdog
 * @return Nothing.
 */
int8_t watchdog::enable(uint8_t time_out)
{
	//Check to see if time_out is an appropriate value for target
	
	//If it is then enable timer...
	
	/*Initialise the watchdog timer with one of the
	predetermined options available*/
	wdt_enable(time_out);
	
	/*For the ATmega 2560, all timeout options are possible so return success*/
	return 0;
	
	//Otherwise return -1 to indicate an error
	//return -1;
}

/** 
* Disables the watchdog timer.
*
* @param  Nothing.
* @return Nothing.
*/
void watchdog::disable(void)
{
	/*Disable the watchdog timer that is currently enabled*/
	wdt_disable();
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
