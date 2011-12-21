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

// DEFINE CONSTANTS

#define BLINK_PORT		<<<TC_INSERTS_BLINK_PORT_HERE>>>
#define BLINK_PIN		<<<TC_INSERTS_BLINK_PIN_HERE>>>
#define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>
#define FORCE_BL_PORT		<<<TC_INSERTS_FORCE_BL_PORT_HERE>>>
#define FORCE_BL_PIN		<<<TC_INSERTS_FORCE_BL_PIN_HERE>>>
#define LED_LOGIC		<<<TC_INSERTS_LED_LOGIC_HERE>>>
#define INPUT_LOGIC		<<<TC_INSERTS_INPUT_LOGIC_HERE>>>
#define CLK_SPEED		(CLK_SPEED_IN_MHZ * 1000000)
#define MS_P_S			1000	/* Conversion factor; milliseconds per second. */
#define TM_PRSCL		1024
#define BOOT_TIMEOUT		500	/* Timeout in milliseconds. */
#define MAX_TICK_VALUE		10
#define TM_CHAN_VAL		((CLK_SPEED/TM_PRSCL)/(MS_P_S / BOOT_TIMEOUT)/10)

#define LONG_FLASH		16000
#define SHORT_FLASH		9500

#define SHUTDOWNSTATE_MEM	0x0200	/* TODO - There needs to be a toolchain macro here to stick in the appropriate address.*/

#define CLEAN_FLAG		0xAFAF

#define BOOTLOADER_MODULE	<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

gpio_pin_address blinkaddress = {BLINK_PORT, BLINK_PIN};
gpio_pin blinkenlight = gpio_pin::grab(blinkaddress);

timer blink_timer = timer::grab(TC_1);
timer bl_timeout  = timer::grab(TC_3);

volatile uint8_t timeout_tick;

volatile bool timeout_expired;

BOOTLOADER_MODULE mod_imp = BOOTLOADER_MODULE(); // Which ever bootloader module we are using.
bootloader_module* mod = &mod_imp;

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
	MCUCR |= (1<<IVSEL);
	
	// Initialise the hal.
	init_hal();

	// Enable the watchdog timer.  Even the bootloader must satisfy the watchdog.
	watchdog::enable(WDTO_60MS);
	
	// Turn on the blinkenlight solidly.
	if (blinkenlight.is_valid())
	    blinkenlight.write(LED_LOGIC ? O_LOW : O_HIGH);
	
	gpio_pin_address force_bl_add = {FORCE_BL_PORT, FORCE_BL_PIN};
	gpio_pin force_bl = gpio_pin::grab(force_bl_add);

	// Check to see if the pin is not already being used (this would only happen if the user specified the led and switch to be the same pin).
	if (force_bl.is_valid())
	{
	    // Check the state of the 'application run' marker.
	    if ((is_clean()) && (force_bl.read() == (INPUT_LOGIC ? I_HIGH : I_LOW)))
	    {
		    // The marker seemed clean, and there was no forcing of the bootloader firmware loading so start the application immediately.
	    
		    // Run the application.
		    run_application();
	    }
	}

	// Else if we get here, that means that the application didn't end cleanly, and so we might need to load new firmware.

	// Start up whichever peripherals are required by the modules we're using.
	mod->init();

	// Set up a timer and interrupt to flash the blinkenlight..
	timer_rate blink_rate = {INT, TC_PRE_1024};
	blink_timer.set_rate(blink_rate);
	blink_timer.set_ocR(TC_OC_A,  SHORT_FLASH);
	blink_timer.enable_oc(TC_OC_A, OC_MODE_1);
	blink_timer.enable_oc_interrupt(TC_OC_A, &blink_func);
	
	// Set up a timer and interrupt to measure the time elapsed.
	timer_rate timeout_rate = {INT, TC_PRE_1024};
	bl_timeout.set_rate(timeout_rate);
	bl_timeout.set_ocR(TC_OC_A, TM_CHAN_VAL);
	bl_timeout.enable_oc(TC_OC_A, OC_MODE_1);
	bl_timeout.enable_oc_interrupt(TC_OC_A, &tick_func);

	
	
	// Enable interrupts.
	int_on();

	// TODO - Replace this with something non-target specific.

	// Don't start the timer until after interrupts have been enabled!
	blink_timer.start();

	// Now we loop continuously until either some firmware arrives or we decide to try the application code anyway.
	while (1)
	{
		// Touch the watchdog.
		watchdog::pat();

		// The blinkenlight should flash some kind of pattern to indicate what is going on.
		// If the flashing period keeps changing, we know we are making it around the loop fine.
		blink_timer.set_ocR(TC_OC_A, LONG_FLASH);
		
		// Check to see if we've timed out
		if (((!firmware_available) && timeout_expired) || firmware_finished)
		{
		    // Run the application.
		    run_application();
		}
		
		// TODO - Wait until some firmware arrives.

		//		Probably, send out a message to indicate that we're now waiting on firmware.  Then wait for some time.  If we
		//		still haven't been given any firmware, then restart the application anyway, since in all likelihood this was an
		//		unforseen crash, and if for instance, the flight controller crashes, then we want to restart it and hope it can
		//		recover, rather than flying into the ground whilst we wait for new software to arrive.

		// If the buffer is ready, write it to memory.
		if (buffer.ready_to_flash)
		{
			// Write the buffer to flash. This blocks, with interrupts disabled, whilst the operation is in progress.
			flash_page(buffer);
		}
			
		// TODO - Then check if we've now got a valid program to run.
	}

	// We should never reach here.
	return 0;
}

void boot_mark_clean(void)
{
	// Set the clean flag in EEPROM.
	uint16_t data = CLEAN_FLAG;
	write_mem(SHUTDOWNSTATE_MEM, &data, 1);

	// All done.
	return;
}

void boot_mark_dirty(void)
{
	// Clear the clean flag in EEPROM, thus making the memory 'dirty'.
	uint8_t data = 0;
	write_mem(SHUTDOWNSTATE_MEM, &data, 1);

	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

bool is_clean(void)
{
	// Read the clean flag from EEPROM.
	uint8_t data;
	read_mem(SHUTDOWNSTATE_MEM, &data, 1);

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
	int_off();

	// TODO - Replace this with something non-target specific.

	// Set the application run marker to 'dirty', so that the application must 'clean' it when it shuts down.
	boot_mark_dirty();

	// TODO - Make sure we're all good to go.

	// Shut down whatever module we were using.  This should return any affected peripherals to their initial states.
	mod->exit();

	// TODO - Does vacating the timer actually stop it?  The timer needs to end up EXACTLY as it started. Yes

	// Stop the timer and interrupt for the blinkenlight.
	blink_timer.vacate();
	blinkenlight.write(LED_LOGIC ? O_LOW: O_HIGH);
	blinkenlight.vacate();

	// Put interrupts back into application-land.
	MCUCR |= (1<<IVCE);
	MCUCR &= ~(1<<IVSEL);
	
	// Jump into the application.
	asm("jmp 0000");

	// We will never reach here.
	return;
}

void flash_page(volatile firmware_page& buffer)
{
	// Disable interrupts.
	int_off();

	// TODO - Replace this with something non-target specific.

	// Get a pointer to the start of the data we're going to write.
	uint8_t* data = (uint8_t*) buffer.data;	// NOTE - Because we've now disabled interrupts, we can treat data as non-volatile.

	// Wait until the EEPROM is ready.
	eeprom_busy_wait();

	// Erase the EEPROM page that we are about to write.
	boot_page_erase(buffer.page);
	boot_spm_busy_wait();

	// Set up the page of data to write, one word (two bytes) at at time.
	for (uint16_t i = 0; i < SPM_PAGESIZE; i += 2)
	{
		// Set up a little-endian word composed of the next two bytes of data to be written.
		uint16_t w = *data++;
		w += (*data++) << 8;

		// Fill the temporary page buffer with the created word.
		boot_page_fill((buffer.page + i), w);
	}

	// Write the temporary page buffer to the EEPROM.
	boot_page_write(buffer.page);
	boot_spm_busy_wait();

	// Reenable the RWW EEPROM again.
	boot_rww_enable();
	
	// Clear the buffer so that it may be used again.
	buffer.ready_to_flash = false;
	buffer.page = 0;
	buffer.current_byte = 0;

	// Re-enable interrupts.
	int_restore();

	// All done.
	return;
}

void blink_func(void)
{
	// Reset the output compare register.
	blink_timer.set_ocR(TC_OC_A, SHORT_FLASH);

	// Toggle the blinkenlight.
	blinkenlight.write(O_TOGGLE);  

	// All done.
	return;
}

void tick_func(void)
{
	// Advance the tick count.
	timeout_tick++;
	
	// Check if the timeout period has now expired.
	timeout_expired = (timeout_tick > MAX_TICK_VALUE);

	// All done.
	return;
}

// ALL DONE.
