// Copyright (C) 2011  Unison Networks Ltd
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
 *  FILE: 		bootloader.c
 *
 *  TARGET:		All AVR Targets
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	5-12-2011
 *
 *	This is the generic modular bootloader used for AVR targets.  It is able to utilize different peripherals for the
 *	download of new application firmware, though the use of modular plugins.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

// DEFINE CONSTANTS

enum port_offset {P_READ, P_MODE, P_WRITE};
enum port_t {PORT_A, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G, PORT_H, PORT_J, PORT_K, PORT_L};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14}; 
enum input_state {LO,HI};

#define BLINK_PORT_NUM		<<<TC_INSERTS_BLINK_PORT_HERE>>>
#define BLINK_PIN_NUM		<<<TC_INSERTS_BLINK_PIN_HERE>>>
#define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>
#define FORCE_BL_PORT_NUM	<<<TC_INSERTS_FORCE_BL_PORT_HERE>>>
#define FORCE_BL_PIN_NUM	<<<TC_INSERTS_FORCE_BL_PIN_HERE>>>
#define LED_LOGIC		<<<TC_INSERTS_LED_LOGIC_HERE>>>
#define INPUT_LOGIC		<<<TC_INSERTS_INPUT_LOGIC_HERE>>>
#define PORT_MULTIPLIER		3
#define BLINK_READ		_SFR_IO8((BLINK_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define BLINK_WRITE		_SFR_IO8((BLINK_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define BLINK_MODE		_SFR_IO8((BLINK_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define FORCE_BL_READ		_SFR_IO8((FORCE_BL_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define FORCE_BL_WRITE		_SFR_IO8((FORCE_BL_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define FORCE_BL_MODE		_SFR_IO8((FORCE_BL_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define BLINK_PIN		( 1 << BLINK_PIN_NUM )
#define FORCE_BL_PIN		( 1 << FORCE_BL_PIN_NUM )
#define CLK_SPEED		(CLK_SPEED_IN_MHZ * 1000000)
#define MS_P_S			1000	/* Conversion factor; milliseconds per second. */
#define TM_PRSCL		1024
#define BOOT_TIMEOUT		500	/* Timeout in milliseconds. */
#define MAX_TICK_VALUE		10
#define TM_CHAN_VAL		((CLK_SPEED/TM_PRSCL)/(MS_P_S / BOOT_TIMEOUT)/10)

#define LONG_FLASH		1600
#define SHORT_FLASH		800

#define SHUTDOWNSTATE_MEM	<<<TC_INSERTS_SHUTDOWN_STATE_MEM_HERE>>>

#define CLEAN_FLAG		0xAFAF

#define BOOTLOADER_MODULE	<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>


// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

volatile uint8_t timeout_tick = 0;

volatile uint8_t blink_tick;

volatile bool timeout_expired = false;

BOOTLOADER_MODULE module;//This means all the modules must have an object defined in them called- extern <class name> module
BOOTLOADER_MODULE* mod = &module;

firmware_page buffer;

bool firmware_finished;

bool communication_started = false;



//
//
//		TESTING
//		   v
volatile uint8_t second_tick = 0;//Added for testing
volatile bool wait_flag = false;//

void ledon(uint8_t led)
{
	if(led == 0){PORTB &= ~(1<<PB0);}
	if(led == 1){PORTB &= ~(1<<PB1);}
	if(led == 2){PORTB &= ~(1<<PB2);}
	if(led == 3){PORTB &= ~(1<<PB3);}
	if(led == 4){PORTB &= ~(1<<PB4);}
	if(led == 5){PORTB &= ~(1<<PB5);}
	if(led == 6){PORTB &= ~(1<<PB6);}
	if(led == 7){PORTB &= ~(1<<PB7);}
}
void ledoff(uint8_t led)
{
	if(led == 0){PORTB |= (1<<PB0);}
	if(led == 1){PORTB |= (1<<PB1);}
	if(led == 2){PORTB |= (1<<PB2);}
	if(led == 3){PORTB |= (1<<PB3);}
	if(led == 4){PORTB |= (1<<PB4);}
	if(led == 5){PORTB |= (1<<PB5);}
	if(led == 6){PORTB |= (1<<PB6);}
	if(led == 7){PORTB |= (1<<PB7);}
}
void ledtog(uint8_t led)
{
	if(led == 0){PORTB ^= (1<<PB0);}
	if(led == 1){PORTB ^= (1<<PB1);}
	if(led == 2){PORTB ^= (1<<PB2);}
	if(led == 3){PORTB ^= (1<<PB3);}
	if(led == 4){PORTB ^= (1<<PB4);}
	if(led == 5){PORTB ^= (1<<PB5);}
	if(led == 6){PORTB ^= (1<<PB6);}
	if(led == 7){PORTB ^= (1<<PB7);}
}
void wow_init(void)//
{
	second_tick = 0;
	timeout_tick = 0;
	wait_flag = false;
	ledon(3);
	return;
}
void wow(void)//
{
	while(wait_flag == false);
	ledoff(3);
	return;
}
void testing_init(void)//Initialize LEDs 0,1,2,3,4,5,6 and SW 0,1,2,3,4,6,5 for testing
{
	DDRB |= (1<<DDB4)|(1<<DDB5)|(1<<DDB2)|(1<<DDB3)|(1<<DDB6)|(1<<DDB1)|(1<<DDB0);
	PORTB |= (1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB1)|(1<<PB0);//Initally all LEDs off
}
//
//
//		NOT TESTING
//		    V








// DEFINE PRIVATE FUNCTION PROTOTYPES.

/**
 *	Checks the value of the 'application run' mark in EEPROM.
 *
 *	Blocks until EEPROM IO operations are completed.
 *
 *	TAKES:		Nothing.
 *	
 *	RETURNS:	True if the 'application run' mark is 'clean', false if it is 'dirty' or absent.
 */
bool is_clean(void);

/**
 *	Runs the application code, exiting the bootloader.
 *	
 *	TAKES: 		Nothing.
 *
 *	RETURNS: 	This function will NEVER return.
 */
void run_application(void);

/**
 *	Flashes a single page of data to RWW EEPROM.
 *
 *	Blocks until EEPROM IO operations are completed.
 *
 *	NOTE - There is no testing that the arguments provided are valid; invalid arguments may result in undefined behaviour.
 *
 *	TAKES: 		buffer		The firmware_page containing the page of data to be written.
 *
 *	RETURNS: 	Nothing.
 */
void flash_page(volatile firmware_page& buffer);

/**
 *	Reads FLASH memory from a page into a buffer.
 *
 *	TAKES:		buffer		The firmware_page buffer to be written to.
 *	
 *	RETURNS:	Nothing.
 */
void read_flash_page(volatile firmware_page& current_firmware_page);

/**
 *	Executes the procedure required for the received message.
 *
 *	TAKES: 		Nothing.
 *
 *	RETURNS: 	Nothing.
 */
void filter_message(void);

/**
 *	ISR, flashes the LED. Also changes the period if in waiting mode.
 *
 *	@param 	none
 *
 *	@return	Nothing.
 */
void blink_func(void);

/**
 *	ISR, increments tick to start application programme. Also changes the period if in waiting mode.
 *
 *	@param 	none
 *
 *	@return	Nothing.
 */
void tick_func(void);


// IMPLEMENT PUBLIC FUNCTIONS.

int main(void)
{
	// Set interrupts into bootloader-land, rather than the application-land.
	MCUCR = (1<<IVCE);
	MCUCR = (1<<IVSEL);
	
	// Set Blinky Pin to output.
	BLINK_MODE |= BLINK_PIN;
	
	// Set Force BL Pin to input. 
	FORCE_BL_MODE &= ~BLINK_PIN;
	
	
	// Enable the watchdog timer.  Even the bootloader must satisfy the watchdog.
	//wdt_enable(WDTO_500MS);
	
	// Turn on the blinkenlight solidly.
	BLINK_WRITE = ( LED_LOGIC ) ? ( BLINK_WRITE | BLINK_PIN ) : ( BLINK_WRITE & ~BLINK_PIN );
	
	
	// Check the state of the 'application run' marker.
	if ((is_clean()) && ((( FORCE_BL_READ & FORCE_BL_PIN ) >> FORCE_BL_PIN_NUM ) == (INPUT_LOGIC ? LO : HI)))
	{
		// The marker seemed clean, and there was no forcing of the bootloader firmware loading so start the application immediately.
		// Run the application.
		run_application();
	}


	// Else if we get here, that means that the application didn't end cleanly, and so we might need to load new firmware.

	// Start up whichever peripherals are required by the modules we're using.
	mod->init();
	testing_init();
	
	// Set up a timer and interrupt to flash the blinkenlight..
	
	// Normal port operation, not connected to a pin.CTC on.
	TCCR1A = 0b00000000;
	OCR1AH = (uint8_t)( (uint16_t) LONG_FLASH >> 8 );
	OCR1AL = (uint8_t)( (uint16_t) LONG_FLASH);
	// Enable Timer Output Compare interrupt.
	TIMSK1 = 0b00000010;
	
#if defined (__AVR_AT90CAN128__)
	// CTC, no clock yet.
	TCCR0A = 0b00001000;
	// Enable Timer Output Compare interrupt.
	TIMSK0 = 0b00000010;
		
#else
	// CTC on
	TCCR0A = 0b00000010;
	OCR0A = (uint8_t)TM_CHAN_VAL;
	// Enable Timer Output Compare interrupt
	TIMSK0 = 0b00000010;
#endif	
	
	// Enable interrupts.
	sei();
	// Prescalar: 1024
	TCCR1B = 0b00001101;
	
#if defined (__AVR_AT90CAN128__)
	// Prescalar: 1024
	TCCR0A = 0b00001101;
#else
	// Prescalar: 1024
	TCCR0B = 0b00000101;
#endif
	// Don't start the timer until after interrupts have been enabled!

	// Now we loop continuously until either some firmware arrives or we decide to try the application code anyway.
	while (1)
	{
		// Touch the watchdog.
		//wdt_reset();

		// The blinkenlight should flash some kind of pattern to indicate what is going on.
		// If the flashing period keeps changing, we know we are making it around the loop fine
		
		// Check to see if we've timed out
		if (((!mod->reception_message.message_received) && timeout_expired) || firmware_finished)
		{
			run_application();
		}
		
		//check for a new message
		if (mod->reception_message.message_received == false)
		{
			//empty mailbox
			//
			//check if communication with host has already occured
			if(communication_started == false)
			{
				//Send message to host to say that bootloader is awaiting messages
				mod->alert_host();
				
				//wait_time()-wait for period of time before restarting application
				wow_init();
				wow();

				//check message again
				if (mod->reception_message.message_received== false)
				{
					//If still no message then run application, program may have crashed
					run_application();
				}
			}
		}
		else
		{
			//Filter messages.	
			/*//If we are filtering a message then communication with host must have occured
			if(communication_started == false)
			{
				communication_started = true;
			}

			//Once can is working just put filter message - mod->filter_message(buffer, firmware_finished);*/
						
			filter_message();
		}

		// If the buffer is ready, write it to memory.
		if (buffer.ready_to_flash)
		{
			// Write the buffer to flash. This blocks, with interrupts disabled, whilst the operation is in progress.
			flash_page(buffer);
		}
		/*if(buffer.ready_to_read_flash)
		{
			read_flash_page(buffer);	//Implemented with new filter.
		}*/
	}
	// We should never reach here.
	return 0;
}


void boot_mark_clean(void)
{
	// Set the clean flag in EEPROM.
	uint16_t data = CLEAN_FLAG;
	void * address = (void *)SHUTDOWNSTATE_MEM;
	eeprom_busy_wait();
	eeprom_write_block(&data, address, 2);
	eeprom_busy_wait();

	// All done.
	return;
}

void boot_mark_dirty(void)
{
	// Clear the clean flag in EEPROM, thus making the memory 'dirty'.
	uint16_t data = 0;
	void * address = (void *)SHUTDOWNSTATE_MEM;
	eeprom_busy_wait();
	eeprom_write_block(&data,address, 2);
	eeprom_busy_wait();

	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

bool is_clean(void)
{
	// Read the clean flag from EEPROM.
	uint8_t data;
	
	eeprom_busy_wait();
	eeprom_read_block(&data, (void *)SHUTDOWNSTATE_MEM, 2);
	eeprom_busy_wait();
	// Check if the flag was 'clean' or not.
	if (data == CLEAN_FLAG)
	{
		// The flag was clean.
		return true;
	}
	// Else the flag is presumed dirty.
	return false;
}

void run_application(void)
{
	// Disable interrupts.
	cli();

	// Set the application run marker to 'dirty', so that the application must 'clean' it when it shuts down.
	boot_mark_dirty();

	// TODO - Make sure we're all good to go.

	// Shut down whatever module we were using.  This should return any affected peripherals to their initial states.
	mod->exit();

	// Stop the timer and interrupt for the blinkenlight.
	TIMSK1 = 0b00000000;
	TIMSK0 = 0b00000000;
	BLINK_WRITE = ( LED_LOGIC ) ? ( BLINK_WRITE & ~BLINK_PIN ) : ( BLINK_WRITE | BLINK_PIN );

	// Put interrupts back into application-land.
	MCUCR = (1<<IVCE);
	MCUCR = 0;
	
	// Stop timers and return them to original state.
	TCCR1B = 0b00000000;
	TCCR1A = 0b00000000;
#if defined (__AVR_AT90CAN128__)
	TCCR0A = 0b00000000;
#else
	TCCR0B = 0b00000000;
#endif	
	OCR1A = 0;
	OCR0A = 0;
	// Stop the watchdog. If the user wants it in their application they can set it up themselves.
	//wdt_disable();
	
	// Jump into the application.
	asm("jmp 0x0000");

	// We will never reach here.
	return;
}

void flash_page(volatile firmware_page& buffer)
{
	// Disable interrupts.
	cli();

	// TODO - Replace this with something non-target specific.

	// Get a pointer to the start of the data we're going to write.
	uint8_t* data = (uint8_t*) buffer.data;	// NOTE - Because we've now disabled interrupts, we can treat data as non-volatile.

	// Wait until the EEPROM is ready.
	eeprom_busy_wait();

	// Erase the FLASH page that we are about to write.
	boot_page_erase(buffer.page);
	boot_spm_busy_wait();

	// Set up the page of data to write, one word (two bytes) at at time.
	for (uint16_t i = 0; i < buffer.code_length; i += 2)
	{
		// Set up a little-endian word composed of the next two bytes of data to be written.
		uint16_t w = *data++;
		w += (*data++) << 8;

		// Fill the temporary page buffer with the created word.
		boot_page_fill((buffer.page + i), w);
	}

	// Write the temporary page buffer to the FLASH.
	boot_page_write(buffer.page);
	boot_spm_busy_wait();

	// Reenable the RWW EEPROM again.
	boot_rww_enable();
	
	// Clear the buffer so that it may be used again.
	buffer.ready_to_flash = false;
	buffer.page = 0;
	buffer.current_byte = 0;

	// Re-enable interrupts.
	sei();

	// All done.
	return;
}

void read_flash_page(volatile firmware_page& current_firmware_page)
{
	//Read flash page out byte by byte, up until the desired length
	for(uint16_t i = 0 ; i < current_firmware_page.code_length ; i++)
	{
		current_firmware_page.data[i] = pgm_read_byte_far(current_firmware_page.page + i);
	}
}

void filter_message(void)
{
	//If we are filtering a message then communication with host must have occured
	if(communication_started == false)
	{
		communication_started = true;
	}

	//Filter messages.
	//Once can is working just put filter message - mod->filter();
	if(mod->reception_message.message_type == mod->WRITE_DATA)
	{
		mod->write_data_procedure(buffer);
	}

	else if(mod->reception_message.message_type == mod->READ_MEMORY)
	{
		mod->read_memory_procedure(buffer);
		read_flash_page(buffer);
		mod->send_flash_page(buffer);
	}

	else if(mod->reception_message.message_type == mod->GET_INFO)
	{
		mod->get_info_procedure();
	}

	else if(mod->reception_message.message_type == mod->START_RESET)
	{
		mod->start_reset_procedure(firmware_finished);
	}

	else if(mod->reception_message.message_type == mod->WRITE_MEMORY)
	{
		mod->write_memory_procedure(buffer);
	}

	mod->reception_message.message_received = false;//reset message flag
}

ISR(TIMER1_COMPA_vect)
{
	// NOTE This can be edited to whatever is desired. Currently it toggles the led and then changes the time for the next toggle. This results of it being on more than off.
	static int change = 1;
	    // Toggle the blinkenlight.
	if (change)
	{
		OCR1A = ( uint16_t )(SHORT_FLASH);
		change = 0;
	}
	else
	{
		OCR1A = ( uint16_t )(LONG_FLASH);
		change = 1;
	}
	BLINK_WRITE = ( BLINK_WRITE & BLINK_PIN ) ? (BLINK_WRITE & ~BLINK_PIN) : (BLINK_WRITE | BLINK_PIN); 
	  // blink_tick = 0;
	
	// All done.
	return;
}


#if defined (__AVR_AT90CAN128__)

ISR(TIMER0_COMP_vect)

#else

ISR(TIMER0_COMPA_vect)

#endif

{
	// Advance the tick count.
	timeout_tick++;
	
	// Check if the timeout period has now expired.
	//timeout_expired = (timeout_tick > MAX_TICK_VALUE);
	
	//Period of time used as wait.
	if(timeout_tick > 254)
	{
		second_tick++;
		if(second_tick > 127)
		{
			second_tick = 0;
			wait_flag = true;
		}		
		timeout_tick = 0;
	}

	// All done.
	return;
}

// ALL DONE.
