// Copyright (C) 2014  Unison Networks Ltd
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


/********************************************************************************************************************************
 *
 *  FILE:               test_hal_gpio_avr.cpp
 *
 *  SUB-SYSTEM:         HAL Validation
 *
 *  COMPONENT:          test_hal_gpio_avr
 *
 *  TARGET:             ATmega64C1
 *
 *  PLATFORM:           BareMetal
 *
 *  AUTHOR:             Ben O'Brien
 *
 *  DATE CREATED:       26-11-2014
 *
 *  -------------------------------------------------------------------------------------------------------------------------------
 *  DESCRIPTION 
 *  -------------------------------------------------------------------------------------------------------------------------------
 *  Turns on 8 LEDs (or sets 8 outputs low on PORTB) and turns them on or off based on button input from (port C) is
 *  pressed.
 *  Program runs on the ATmega64M1, ATmega64C1, AT90CAN128 or ATmega2560.

 *  -------------------------------------------------------------------------------------------------------------------------------
 *  CONFIGURATION DETAILS
 *  -------------------------------------------------------------------------------------------------------------------------------
 *  Currently compatible with AVR_ATmega64M1
 * 
 *  TODO: Make compatible with AVR_ATmega64C1
 * 	TODO: Make compatible with AVR_AT90CAN128
 *  TODO: Make compatible with AVR_ATmega2560
 * 
 *  Eight LEDs, connected to port B on pins 0, 1, 2, 3, 4, 5, 6, 7
 *	Eight buttons, connected to port C on pins 0, 1, 2, 3, 4, 5, 6, 7
 * 
 ********************************************************************************************************************************/

// MATCHING HEADER FILE. --------------------------------------------------------------------------------------------------------

#include "test_hal_gpio_avr.hpp"

// Arrays contain pointers to the button and LED pins.
Gpio_pin* buttons[NUM_PINS];
Gpio_pin* LEDs[NUM_PINS];


enum button_numbers_t
{
	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
	BUTTON_7
};

enum LED_numbers_t
{
	LED_0 = 0,
	LED_1 = 1,
	LED_2 = 2,
	LED_3 = 3,
	LED_4 = 4,
	LED_5 = 5,
	LED_6 = 6,
	LED_7 = 7
};

// The current button states
// Bit 0 is the current state. 7 previous states are stored in sequence and shifted left when a new state is registered.
volatile int8_t button_states[NUM_PINS] = 
{
	0, 
	0, 
	0, 
	0, 
	0, 
	0, 
	0, 
	0
};

// The current LED states
// Bit 0 is the current state. 7 previous states are stored in sequence and shifted left when a new state is registered.
int8_t LED_states[NUM_PINS] = 
{
	0, 
	0, 
	0, 
	0, 
	0, 
	0, 
	0, 
	0
};


/* -------------------------------------------------------------------------
* Buttons
* -----------------------------------------------------------------------*/
int8_t update_button(uint8_t button_number)
{
	if(button_number < NUM_PINS)
	{
		uint8_t state = buttons[button_number]->read();
		// NOTE - Bit shifting is used to save the previous button state.
		button_states[button_number] = button_states[button_number] << 1;
		if(state)
		{
			//set the first bit to 1
			button_states[button_number] |= 0x1;
		} 
		else
		{
			//set the first bit to 0
			button_states[button_number] &= ~(0x1); 
		}
		
		// All done.
		return(0);
	}
	
	// NOTE - if it reaches here, the button number is out of range.

	// All done.
	return(-1);
}

int8_t get_button_state(uint8_t button_number, uint8_t index)
{
	// NOTE - Bit shifting is used to save the previous button state.
	if(button_number < NUM_PINS)
	{
		return((Gpio_input_state)(button_states[button_number] & (1<<index)));
	}
	// NOTE - if it reaches here, the button number is out of range.
	
	// All done.
	return(GPIO_I_ERROR);
}


bool is_button_down(uint8_t button_number)
{
	return(get_button_state(button_number, 0));
}

bool is_button_released(uint8_t button_number)
{
	return(!get_button_state(button_number, 0) && get_button_state(button_number, 1));
}

bool is_button_pressed(uint8_t button_number)
{
	return(get_button_state(button_number, 0) && !get_button_state(button_number, 1));
}


void disable_button_interrupts()
{
	for(uint8_t i = BUTTON_1; i <= BUTTON_7; i++)
	{
		buttons[i]->disable_interrupt();
	}
	int_off();
	interrupts_on = false;
}

void enable_button_interrupts()
{
	
	/* -------------------------------------------------------------------------
	 * Initialising Interrupts. Displays an error message if an
	 * error occurred.
	 * -----------------------------------------------------------------------*/
	int8_t status = GPIO_INT_SUCCESS;

	int8_t error_message = 0;
	// TODO - Renable
	for(uint8_t i = BUTTON_1; i <= BUTTON_7; i++)
	{
		status = buttons[i]->enable_interrupt(GPIO_INT_ANY_EDGE, &on_button_press);
		error_message |=  (1<<(3+status)) & 0xf;
	}
	
	// Enable global interrupts
	int_on();
	
	if(status != GPIO_INT_SUCCESS && status != GPIO_INT_ALREADY_DONE)
	{
		/* ERROR MESSAGE DISPLAY
		
		 * Display the error message on the LEDs (LED7 is the left-most LED)
		 * x = don't care condition
		
		 * GPIO_INT_OUT_OF_RANGE 	-> 	x x x x 0 0 1 0		(-2)
		 * GPIO_INT_ALREADY_TAKEN 	->	x x x x 0 1 0 0		(-1)
		
		 * The number of the LED that the error occurred at is encoded as
		 * a 4-bit binary number in the left half of the display.
		 *	E.g. LED7 				-> 0 1 1 1 x x x x
		 *		LED2 				-> 0 0 1 0 x x x x
		 */
		
		
		uint32_t flashing_timer = 0;
		while(interrupts_on)
		{
			if(flashing_timer <= 24000)
			{
				display_number_as_binary(((flashing_timer/512))&error_message, LEDs, NUM_PINS);
			} else 
			{
				flashing_timer = 0;
			}
			
			update_button(BUTTON_0);
			if(is_button_pressed(BUTTON_0))
			{
				interrupts_on = false;
				for(uint8_t i = BUTTON_1; i <= BUTTON_7; i++)
				{
					buttons[i]->disable_interrupt();
				}
				int_off();
				set_LED_state(LED_0, GPIO_O_LOW);
				
			}
			
			// Incrementing the flashing timer
			flashing_timer ++;
		}
	}
}



/* -------------------------------------------------------------------------
* LEDs
* -----------------------------------------------------------------------*/


int8_t set_LED_state(uint8_t led_number, int8_t state)
{
	// NOTE - Bit shifting is used to save the previous LED state.
	if(led_number < NUM_PINS)
	{
		LED_states[led_number] = LED_states[led_number] << 1;
		
		switch(state)
		{
			case GPIO_O_LOW:
				LED_states[led_number] |= 0x1;
				break;
			case GPIO_O_HIGH:
				LED_states[led_number] &= ~(0x1);
				break;
			case GPIO_O_TOGGLE:
				LED_states[led_number] |= 0x01 & ~get_LED_state(led_number, 1);
				break;
			default:
				// Invalid state
				return(-2); 
				break;
		}
		return(0);
	}
	// NOTE - if it reaches here, the LED number is out of range.
	
	// All done.
	return(GPIO_ERROR);
}

bool get_LED_state(uint8_t led_number, uint8_t index)
{
	// NOTE - Bit shifting is used to save the previous button state.
	if(led_number < NUM_PINS)
	{
		return(LED_states[led_number] & (1<<index));
	}
	// NOTE - if it reaches here, the LED number is out of range. Defaults to false.
	
	// All done.
	return(false);
}

int8_t update_LED(uint8_t led_number)
{
	if(led_number < NUM_PINS)
	{
		LEDs[led_number]->write((Gpio_output_state)get_LED_state(led_number, TEST_CURRENT_STATE));
	} else
	{
		return(GPIO_ERROR);
	}
	return(0);
}


void update_display()
{
	for(uint8_t i = 0; i <= LED_7; i++)
	{
		update_LED(i);
	}
}


void display_number_as_binary(int8_t number, Gpio_pin** display_LEDs, uint8_t num_LEDs)
{
	for (uint8_t led = 0; led < num_LEDs; led ++)
	{
		if (number & (1 << led))
		{
			display_LEDs[led]->write(GPIO_O_LOW);
		} else 
		{
			display_LEDs[led]->write(GPIO_O_HIGH);
		}
	}
	// All done.
}


#define CLEAR_LEDS() display_number_as_binary(0, LEDs, NUM_PINS)

/* -------------------------------------------------------------------------
* Main Implementation
* -----------------------------------------------------------------------*/

int main(void)
{
	uint8_t i, led, button;
	
	/* -------------------------------------------------------------------------
	 * Buttons
	 * -----------------------------------------------------------------------*/
	// Defining the addresses for all of the buttons.
	IO_pin_address button_addresses[NUM_PINS];
	for(uint8_t button = BUTTON_0; button < NUM_PINS; button ++)
	{
		button_addresses[button].port = BUTTON_PORT;
		button_addresses[button].pin = (pin_t)button;
	}
	
	// Defining the addresses for all of the LEDs
	IO_pin_address LED_addresses[NUM_PINS];
	for(led = LED_0; led <= LED_7; led ++)
	{
		LED_addresses[led].port = LED_PORT;
		LED_addresses[led].pin = (pin_t)led;
	}
	
	// Initialising the Buttons, based on the predefined addresses.
	Gpio_pin button_pin0(button_addresses[BUTTON_0]);
	Gpio_pin button_pin1(button_addresses[BUTTON_1]);
	Gpio_pin button_pin2(button_addresses[BUTTON_2]);
	Gpio_pin button_pin3(button_addresses[BUTTON_3]);
	Gpio_pin button_pin4(button_addresses[BUTTON_4]);
	Gpio_pin button_pin5(button_addresses[BUTTON_5]);
	Gpio_pin button_pin6(button_addresses[BUTTON_6]);
	Gpio_pin button_pin7(button_addresses[BUTTON_7]);
	
	// Initialising the LEDs, based on the predefined addresses
	Gpio_pin led_pin0(LED_addresses[LED_0]);
	Gpio_pin led_pin1(LED_addresses[LED_1]);
	Gpio_pin led_pin2(LED_addresses[LED_2]);
	Gpio_pin led_pin3(LED_addresses[LED_3]);
	Gpio_pin led_pin4(LED_addresses[LED_4]);
	Gpio_pin led_pin5(LED_addresses[LED_5]);
	Gpio_pin led_pin6(LED_addresses[LED_6]);
	Gpio_pin led_pin7(LED_addresses[LED_7]);
	
	// Pointers to each of the activated Gpio Button pins are placed in an array.
	buttons[BUTTON_0] = &button_pin0;
	buttons[BUTTON_1] = &button_pin1;
	buttons[BUTTON_2] = &button_pin2;
	buttons[BUTTON_3] = &button_pin3;
	buttons[BUTTON_4] = &button_pin4;
	buttons[BUTTON_5] = &button_pin5;
	buttons[BUTTON_6] = &button_pin6;
	buttons[BUTTON_7] = &button_pin7;
	
	// Pointers to each of the activated Gpio LED pins are placed in an array
	LEDs[LED_0] = &led_pin0;
	LEDs[LED_1] = &led_pin1;
	LEDs[LED_2] = &led_pin2;
	LEDs[LED_3] = &led_pin3;
	LEDs[LED_4] = &led_pin4;
	LEDs[LED_5] = &led_pin5;
	LEDs[LED_6] = &led_pin6;
	LEDs[LED_7] = &led_pin7;
	
	// Setting the propeties of each of the pins, each associated with a button.
	for(button = BUTTON_0; button <= BUTTON_7; button ++)
	{
		buttons[button]->set_mode(GPIO_INPUT_PU);
	}
	
	// Setting the propeties of each of the pins, each associated with an LED
	for(led = LED_0; led <= LED_7; led ++)
	{
		LEDs[led]->set_mode(GPIO_OUTPUT_PP);
		LEDs[led]->write(GPIO_O_HIGH);
	}
	 
	/* -------------------------------------------------------------------------
	* The main loop
	* -----------------------------------------------------------------------*/
	set_LED_state(LED_0, !interrupts_on);
	
	while (1)
	{	
		// Button zero is always polled, in case interrupts are non-functional.
		update_button(BUTTON_0);
		
		//Updating button state via polling
		if(!interrupts_on)
		{
			for(button = BUTTON_1; button <= BUTTON_7; button++)
			{
				update_button(button);
			}
		}
		
		//Every odd numbered button switches its corresponding LED on if held down. If an odd numbered LED is not held down, its LED will be off.
		//Every even numbered button (including button 0) toggles its corresponding LED. 
		//Button 0 also controls whether interrupts or polling methods are used for buttons 1 to 7. Button 0 is itself always polled.
		for(i = BUTTON_1; i <= BUTTON_7; i += 2)
		{
			set_LED_state(i, !is_button_down(i));
			
			if(i != BUTTON_7)
			{
				if(is_button_released(i+1))
				{
					set_LED_state(i+1, GPIO_O_TOGGLE);
				}
			}
		}
		

		if(is_button_pressed(BUTTON_0))
		{
			interrupts_on = !interrupts_on;
			if(!interrupts_on)
			{
				disable_button_interrupts();
			} else
			{
				enable_button_interrupts();
			}
		} 
		set_LED_state(LED_0, !interrupts_on);
		// Update the display based on the current states of the LEDs
		update_display();
	}
	
	
	// All done.
	return 0;
}


// INTERRUPT SERVICE ROUTINES.

void on_button_press(void)
{
	if(interrupts_on)
	{
		for(uint8_t i = BUTTON_1; i <= BUTTON_7; i++)
		{
			update_button(i);
		}
		
	}
	// TODO - Account for a possible lack of debouncing
}


// ALL DONE.
