/********************************************************************************************************************************
 *
 *  FILE: 		gpio_test.c
 *
 *  SUB-SYSTEM:		testing
 *
 *  COMPONENT:		example
 *
 *  TARGET:		Any (originally ATmega2560)
 *
 *  PLATFORM:		BareMetal
 *
 *  AUTHOR: 		Zac Frank
 *
 *  DATE CREATED:	14-12-2011
 *
 *	This is an example program for using the gpio. It makes an output pin respond to an input pin.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.
#include <avr/io.h>
#include "hal/hal.h"
#include "hal/gpio.h"


int main(void) 
{
	// Initialise the hal (eg semaphores)
	init_hal();
	
	// Choose pin addresses (edit as necessary for PCB design)
	gpio_pin_address out_address = {PORT_A, PIN_6};
	gpio_pin_address in_address = {PORT_B, PIN_4};
	
	// Ask for permission for a pin
	gpio_pin out_pin = gpio_pin::grab(out_address);
	
	// Check to see if the pin is free
	if (out_pin.is_valid())
	{
		// set pin to output and write a hi (turn led off)
		out_pin.set_mode(OUTPUT);
		out_pin.write(O_HIGH);
		
		// Grab another pin for input.
		gpio_pin in_pin = gpio_pin::grab(in_address);
		
		// if the pin is free
		if (in_pin.is_valid())
		{
			// set to input, then go on forever, checking the input and changing the output accordingly.
			in_pin.set_mode(INPUT);
			while(1)
			{
				// toggle the output pin with the input switch.
				if (in_pin.read())
				{
					out_pin.write(O_HIGH);
				}
				else
				{
					out_pin.write(O_LOW);
				}
			}		
		}
	}
	return 0;
}

// IMPLEMENT PRIVATE FUNCTIONS.

// ALL DONE.
