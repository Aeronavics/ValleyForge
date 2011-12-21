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


#include "hal/hal.h"
#include "hal/gpio.h"
#include "hal/mem.h"
#include "hal/watchdog.h"
#include "hal/tc.h"


// DEFINE CONSTANTS

#define BLINK_PORT		<<<TC_INSERTS_BLINK_PORT_HERE>>>
#define BLINK_PIN		<<<TC_INSERTS_BLINK_PIN_HERE>>>
#define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>
#define FORCE_BL_PORT		<<<TC_INSERTS_FORCE_BL_PORT_HERE>>>
#define FORCE_BL_PIN		<<<TC_INSERTS_FORCE_BL_PIN_HERE>>>
#define LED_LOGIC		<<<TC_INSERTS_LED_LOGIC_HERE>>>
#define INPUT_LOGIC		<<<TC_INSERTS_INPUT_LOGIC_HERE>>>
#define CLK_SPEED		CLK_SPEED_IN_MHZ*1000000
#define MS_P_S			1000	/*milliseconds per second */
#define TM_PRSCL		1024
#define BOOT_TIMEOUT		500  /* milliseconds*/
#define MAX_TICK_VALUE		10
#define TM_CHAN_VAL		(CLK_SPEED/TM_PRSCL)/(MS_P_S / BOOT_TIMEOUT)/10


#define SHUTDOWNSTATE_MEM	0x0000

#define PAGE_SIZE	256
// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

gpio_pin_address blinkaddress = {BLINK_PORT, BLINK_PIN};
gpio_pin blinkenlight = gpio_pin::grab(blinkaddress);

timer bl_timer = timer::grab(TC_1);

uint8_t timer_tick = 0;

bool	buffer_1_full = false;
bool	buffer_2_full = false;


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

/**
 *	ISR, flashes the LED
 *
 *	Also changes the period if in waiting mode
 *
 *	@param 	none
 *
 *	@return	Nothing.
 */
void blink_func(void);

/**
 *	ISR, increments tick to start program
 *
 *	Also changes the period if in waiting mode
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
	
	uint8_t buffer_1[PAGE_SIZE];
	uint8_t buffer_2[PAGE_SIZE];
	
	uint8_t* buffer_1_pointer = &buffer_1[0];
	uint8_t* buffer_2_pointer = &buffer_2[0];
	
	bool	firmware_finished = false;
	uint8_t active_buffer = 1;
	
	uint32_t page = 0;
	
	bool	firmware_available = false;

	// Enable the watchdog timer.  Even the bootloader must satisfy the watchdog.
	watchdog::enable(WDTO_60MS);
	
	// Turn on the blinkenlight solidly.
	if (blinkenlight.is_valid())
	    blinkenlight.write(LED_LOGIC ? O_LOW : O_HIGH);
	
	
	gpio_pin_address force_bl_add = {FORCE_BL_PORT, FORCE_BL_PIN};
	gpio_pin force_bl = gpio_pin::grab(force_bl_add);

	// Check to see if the pin is not already being used (in this case this would only be if the user specified the led pin and switch pin to be the same).
	if (force_bl.is_valid())
	{
	    // Check the state of the 'application run' marker.
	    if ((is_clean()) && (force_bl.read() == (INPUT_LOGIC ? I_HIGH : I_LOW)))
	    {
		    // The marker seemed clean, and there was no forcing of the bootloader firmware loading so the bootloader will start the application immediately.
	    
		    // Run the application
		    run_application();
	    }
	}

	// Else if we get here, that means that the application didn't end cleanly, and so we might need to load new firmware.
	
	// Fetch whichever peripheral module we are using.
	//bootloader_module mod = get_module();

	// TODO - The function get_module() needs to be implemented such that it returns the appropriate kind of module.

	// Start up whichever peripherals are required by the modules we're using.
	//mod.init();

	// Set up a timer and interrupt to flash the blinkenlight.
	timer_rate bl_rate = {INT, TC_PRE_1024};
	
	bl_timer.set_ocR<uint16_t>(TC_OC_A,  10000);
	bl_timer.set_ocR<uint16_t>(TC_OC_B, TM_CHAN_VAL);
	bl_timer.enable_oc(TC_OC_A, OC_MODE_1);
	bl_timer.enable_oc(TC_OC_B, OC_MODE_1);
	bl_timer.enable_oc_interrupt(TC_OC_A, &blink_func);
	bl_timer.enable_oc_interrupt(TC_OC_B, &tick_func);
	bl_timer.set_rate(bl_rate);
	bl_timer.start();
	// Enable interrupts.
	sei();

	// Now we loop continuously until either some firmware arrives or we decide to try the application code anyway.
	while (1)
	{
		// Touch the watchdog.
		watchdog::pat();

		// The blinkenlight should flash some kind of pattern to indicate what is going on.
		bl_timer.set_ocR<uint16_t>(TC_OC_A,10000);
		
		// Check to see if we've timed out
		if (((!firmware_available) && (timer_tick > MAX_TICK_VALUE)) || firmware_finished)
		{
		    run_application();
		}
		
		// TODO - Wait until some firmware arrives.

		//		Probably, send out a message to indicate that we're now waiting on firmware.  Then wait for some time.  If we
		//		still haven't been given any firmware, then restart the application anyway, since in all likelihood this was an
		//		unforseen crash, and if for instance, the flight controller crashes, then we want to restart it and hope it can
		//		recover, rather than flying into the ground whilst we wait for new software to arrive.

		// TODO - When some firmware arrives, flash it to the RWW flash section.
		
		// If a buffer is full, write it to memory.
		if ((buffer_1_full) || (firmware_finished && (active_buffer == 1)))
		{
		    flash_page(page, &buffer_1[0]);
		    buffer_1_full = false;
		    page += PAGE_SIZE;
		}
		
		if ((buffer_2_full) || (firmware_finished && (active_buffer == 2)))
		{
		    flash_page(page, &buffer_2[0]);
		    buffer_2_full = false;
		    page += PAGE_SIZE;
		}
			
		// TODO - Then check if we've now got a valid program to run.

		// TODO - Then start the application.
	}

	// We should never reach here.
	return 0;
}

void boot_mark_clean(void)
{
	// TODO - This.
	int data = 1;
	write_mem(SHUTDOWNSTATE_MEM, &data, 1);
	// All done.
	return;
}

void boot_mark_dirty(void)
{
	// TODO - This.
	uint8_t data = 0;
	write_mem(SHUTDOWNSTATE_MEM, &data, 1);
	// All done.
	return;
}

// IMPLEMENT PRIVATE FUNCTIONS.

bool is_clean(void)
{
	// TODO - This.
	uint8_t data;
	read_mem(SHUTDOWNSTATE_MEM, &data, 1); 
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
	//mod.exit();

	// Stop the timer and interrupt for the blinkenlight.
	bl_timer.vacate();
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


void blink_func(void)
{
    bl_timer.set_ocR<uint16_t>(TC_OC_A, 10000);
    blinkenlight.write(O_TOGGLE);  
}
// ALL DONE.

void tick_func(void)
{
    timer_tick++;
}