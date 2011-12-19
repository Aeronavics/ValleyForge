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

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

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
 *	TAKES: 		page	The byte address of the page to flash.
 *			data	Pointer to the data to be written to EEPROM.
 *
 *	RETURNS: 	Nothing.
 */
void flash_page(uint32_t page, uint8_t* data);

// IMPLEMENT PUBLIC FUNCTIONS.

int main(void)
{
	// TODO - Set interrupts into bootloader-land, rather than the application-land.

	// TODO - Enable the watchdog timer.  Even the bootloader must satisfy the watchdog.

	// TODO - Turn on the blinkenlight solidly.

	// Check the state of the 'application run' marker.
	if (is_clean())
	{
		// The marker seemed clean, so the bootloader will start the application immediately.
	
		// Run the application
		run_application();
	}

	// Else if we get here, that means that the application didn't end cleanly, and so we might need to load new firmware.

	// TODO - Probably need to read some configuration information from EEPROM, such as which ID this component is.

	// Fetch whichever peripheral module we are using.
	bootloader_module mod = get_module();

	// TODO - The function get_module() needs to be implemented such that it returns the appropriate kind of module.

	// Start up whichever peripherals are required by the modules we're using.
	mod.init();

	// TODO - Set up a timer and interrupt to flash the blinkenlight.

	// Enable interrupts.
	sei();

	// Now we loop continuously until either some firmware arrives or we decide to try the application code anyway.
	while (1)
	{
		// Touch the watchdog.
		wdt_reset();

		// TODO - The blinkenlight should flash some kind of pattern to indicate what is going on.

		// TODO - Wait until some firmware arrives.

		//		Probably, send out a message to indicate that we're now waiting on firmware.  Then wait for some time.  If we
		//		still haven't been given any firmware, then restart the application anyway, since in all liklihood this was an
		//		unforseen crash, and if for instance, the flight controller crashes, then we want to restart it and hope it can
		//		recover, rather than flying into the ground whilst we wait for new software to arrive.

		// TODO - When some firmware arrives, flash it to the RWW flash section.
			
		// TODO - Then check if we've now got a valid programme to run.

		// TODO - Then start the application.
	}

	// We should never reach here.
	return 0;
}

void boot_mark_clean(void)
{
	// TODO - This.
	
	// All done.
	return;
}

void boot_mark_dirty(void)
{
	// TODO - This.

	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

bool is_clean(void)
{
	// TODO - This.

	// TODO - For the moment, we return false.
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
	mod.exit();

	// TODO - Stop the timer and interrupt for the blinkenlight.

	// TODO - Put interrupts back into application-land.
	
	// Jump into the application.
	asm("jmp 0000");

	// We will never reach here.
	return;
}

void flash_page(uint32_t page, uint8_t* data)
{
	// Disable interrupts.
	uint8_t sreg = SREG;
	cli();

	// Wait until the EEPROM is ready.
	eeprom_busy_wait();

	// Erase the EEPROM page that we are about to write.
	boot_page_erase(page);
	boot_spm_busy_wait();

	// Set up the page of data to write, one word (two bytes) at at time.
	for (uint16_t i = 0; i < SPM_PAGESIZE; i += 2)
	{
		// Set up a little-endian word composed of the next two bytes of data to be written.
		uint16_t w = *data++;
		w += (*data++) << 8;

		// Fill the temporary page buffer with the created word.
		boot_page_fill(page + i, w);
	}

	// Write the temporary page buffer to the EEPROM.
	boot_page_write(page);
	boot_spm_busy_wait();

	// Reenable the RWW EEPROM again.
	boot_rww_enable();
	
	// Re-enable interrupts.
	SREG = sreg;

	// All done.
	return;
}

// ALL DONE.
