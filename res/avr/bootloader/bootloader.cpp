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

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "avr_magic/avr_magic.hpp"

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
#define LED_LOGIC			<<<TC_INSERTS_LED_LOGIC_HERE>>>
#define INPUT_LOGIC			<<<TC_INSERTS_INPUT_LOGIC_HERE>>>
#define PORT_MULTIPLIER		3
#define BLINK_READ			_SFR_IO8((BLINK_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define BLINK_WRITE			_SFR_IO8((BLINK_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define BLINK_MODE			_SFR_IO8((BLINK_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define FORCE_BL_READ		_SFR_IO8((FORCE_BL_PORT_NUM * PORT_MULTIPLIER) + P_READ)
#define FORCE_BL_WRITE		_SFR_IO8((FORCE_BL_PORT_NUM * PORT_MULTIPLIER) + P_WRITE)
#define FORCE_BL_MODE		_SFR_IO8((FORCE_BL_PORT_NUM * PORT_MULTIPLIER) + P_MODE)
#define BLINK_PIN			( 1 << BLINK_PIN_NUM )
#define FORCE_BL_PIN		( 1 << FORCE_BL_PIN_NUM )

#define CLK_SPEED		(CLK_SPEED_IN_MHZ * 1000000)
#define TM_PRSCL		1024
#define TM_CHAN_VAL		((CLK_SPEED / TM_PRSCL) / 1000)
#define BOOT_TIMEOUT	10000	// Timeout in milliseconds.

// Blink times for different states. Times are in ms.

// Idle.
#define IDLE_ON	            500
#define IDLE_OFF            500

// Communicating.
#define COMMUNICATING_ON    55
#define COMMUNICATING_OFF   55

// Error.
#define ERROR_ON            0       // NOTE: these are actually inverted. So the LED stays ON permanently on ERROR
#define ERROR_OFF           6000

#define SHUTDOWNSTATE_MEM	<<<TC_INSERTS_SHUTDOWN_STATE_MEM_HERE>>>

#define CLEAN_FLAG		0xAFAF

#define BOOTLOADER_MODULE	<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>

#define BOOTLOADER_VERSION  0x0100 // TODO - how is this updated.

#define DEVICE_SIGNATURE_0 0x00 // In case of using a  microcontroller with a 32-bit device signature.
#define DEVICE_SIGNATURE_1 SIGNATURE_0
#define DEVICE_SIGNATURE_2 SIGNATURE_1
#define DEVICE_SIGNATURE_3 SIGNATURE_2

	// Define the address at which the bootloader code starts (the RWW section).
#define BOOTLOADER_START_ADDRESS	<<<TC_INSERTS_BOOTLOADER_START_ADDRESS_HERE>>>

	// Define the function used to read a flash byte.
#if defined (__AVR_AT90CAN128__) || (__AVR_ATmega2560__)
	#define READ_FLASH_BYTE(address) pgm_read_byte_far(address)
#else
	#define READ_FLASH_BYTE(address) pgm_read_byte(address)
#endif

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// All periodic functionality is queued by a 1ms timer interrupt.  To time longer periods, you need to accumulate a count of ticks.

volatile uint16_t timeout_tick = 0;

volatile uint16_t blink_tick = 0;

// State the bootloader is in.  At the moment, all this determines is the LED flashing pattern.
State state = IDLE;

volatile uint16_t blink_on = IDLE_ON;
volatile uint16_t blink_off = IDLE_OFF;

volatile bool timeout_expired = false;
volatile bool timeout_enable = true;

BOOTLOADER_MODULE module; // This means all the communication modules must have an object defined in them called - extern <class name> module
Bootloader_module& mod = module;

Firmware_page buffer;

// DEFINE PRIVATE FUNCTION PROTOTYPES.
#ifndef __AVR_AT90CAN128__
void wdt_init(void) __attribute__((naked)) __attribute__((section(".init3")));
#endif
/**
 *	Forces a CPU reset by striking the watchdog.
 *
 *	TAKES:		Nothing.
 *
 *	RETURNS:	This function will NEVER return.
 */
void reboot(void);

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
 *	Flashes a single page of data to NRWW EEPROM.
 *
 *	Blocks until EEPROM IO operations are completed.
 *
 *	NOTE - There is no testing that the arguments provided are valid; invalid arguments may result in undefined behaviour.
 *
 *	TAKES: 		buffer		The firmware_page containing the page of data to be written.
 *
 *	RETURNS: 	Nothing.
 */
void write_flash_page(Firmware_page& buffer);

/**
 *	Reads a single page of data from NRWW EEPROM into a buffer.
 *
 *	Blocks until EEPROM IO operations are completed.
 *
 *	NOTE - There is no testing that the arguments provided are valid; invalid arguments may result in undefined behaviour.
 *
 *	TAKES:		buffer		A firmware_page buffer to read into, with the appropriate address details completed.
 *
 *	RETURNS:	Nothing.
 */
void read_flash_page(Firmware_page& buffer);

// IMPLEMENT PUBLIC STATIC FUNCTIONS.

int main(void)
{
	// Check the state of the 'application run' marker, and the state of the force-bootloader input pin.
	if ((is_clean()) && (((FORCE_BL_READ & FORCE_BL_PIN) >> FORCE_BL_PIN_NUM) == (INPUT_LOGIC ? LO : HI)))
	{
		// The marker seemed clean, and the force-bootloader input is not asserted, so start the application immediately.

		// Run the application.
		run_application();
	}

		// Set interrupts into bootloader-land, rather than the application-land.
	MCUCR = (1 << IVCE);
	MCUCR = (1 << IVSEL);

	// Disable the watchdog timer before enabling it.  Even the bootloader must satisfy the watchdog.
	wdt_reset();
	wdt_disable();
	wdt_enable(WDTO_500MS);

	// Set Blinky Pin to output.
	BLINK_MODE |= BLINK_PIN;

	// Set Force BL Pin to input.
	FORCE_BL_MODE &= ~FORCE_BL_PIN;

	// Turn on the blinkenlight solidly.
	BLINK_WRITE = (LED_LOGIC) ? (BLINK_WRITE|BLINK_PIN) : (BLINK_WRITE & ~BLINK_PIN);

	// Else if we get here, that means that the application didn't end cleanly, and so we might need to load new firmware.

	// Start up whichever peripherals are required by the modules we're using.
	mod.init();

	// Set up TIM0 into output compare mode as a free running 1ms timer to queue any periodic functionality.

#if defined (__AVR_AT90CAN128__)
	// CTC, no clock yet.
	TCCR0A = 0b00001000;
	OCR0A = (uint8_t) TM_CHAN_VAL;
	// Enable Timer Output Compare interrupt.
	TIMSK0 = 0b00000010;
#else
	// CTC on.
	TCCR0A = 0b00000010;
	OCR0A = (uint8_t) TM_CHAN_VAL;
	// Enable Timer Output Compare interrupt.
	TIMSK0 = 0b00000010;
#endif

	// Enable interrupts.
	sei();

	// NOTE - Don't start the timer until after interrupts have been enabled!

#if defined (__AVR_AT90CAN128__)
	// Prescalar: 1024.  This starts the 1ms timer.
	TCCR0A = 0b00001101;
#else
	// Prescalar: 1024.  This starts the 1ms timer.
	TCCR0B = 0b00000101;
#endif

	// Set the bootloader into idle mode.
	set_bootloader_state(IDLE);

	// Now we loop continuously until either some firmware arrives or we decide to try the application code anyway.
	while (true)
	{
		// During this loop, the blinken light should be flashing, which tell us that things are still working as expected.

		// Touch the watchdog.
		wdt_reset();

		// If we wait around for a long time without any sign of some new firmware arriving, then start the application anyway.
		if (timeout_expired)
		{
			// For whatever reason, no new firmware is coming, so just start the application instead.
			run_application();

			// We should never reach here.
		}

		// Perform any module specific functionality which needs to be executed as fast as possible.
		mod.event_idle();

		// If the buffer is ready to be written, write it to memory.
		if (buffer.ready_to_write)
		{
			// Write the buffer to flash. This blocks, with interrupts disabled, whilst the operation is in progress.
			write_flash_page(buffer);
		}

		// If the buffer is ready to be read from, read it back again.
		if (buffer.ready_to_read)
		{
			// Read from flash into the buffer.  This blocks, with interrupts disabled, whilst the operation is in progress.
			read_flash_page(buffer);
		}
	}

	// We should never reach here.
	return 0;
}

void boot_mark_clean(void)
{
	// Set the clean flag in EEPROM.
	uint16_t data = CLEAN_FLAG;
	void* address = (void*)(SHUTDOWNSTATE_MEM);
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
	void* address = (void*)(SHUTDOWNSTATE_MEM);
	eeprom_busy_wait();
	eeprom_write_block(&data, address, 2);
	eeprom_busy_wait();

	// All done.
	return;
}

void reboot_to_bootloader(void)
{
	// Mark the status flag as 'dirty' so that the bootloader will remain resident next time.
	boot_mark_dirty();

	// NOTE - We don't bother to tidy anything up, the CPU reset will take care of that.

	// Reboot the microcontroller.
	reboot();

	// We should never reach here.
	return;
}

void reboot_to_application(void)
{
	// Mark the status flag as 'clean' so that the bootloader will start the application directly next time.
	boot_mark_clean();

	// NOTE - We don't bother to tidy anything up, the CPU reset will take care of that.

	// Reboot the microcontroller.
	reboot();

	// We should never reach here.
	return;
}

void start_application(void)
{
	// Run the application.
	run_application();

	// We should never reach here.
	return;
}

void set_bootloader_timeout(bool enable)
{
	// NOTE - This isn't interrupt safe, but a race condition will only cause mistiming, so it's not a biggie.

	// Set the state of the bootloader timeout enable flag.
	timeout_enable = enable;

	// If the timeout is now disabled, then we want to reset the associated counter so we start again from the beginning.
	timeout_tick = (enable) ? timeout_tick : 0;

	// All done.
	return;
}

uint16_t get_bootloader_version(void)
{
	return BOOTLOADER_VERSION;
}

void get_device_signature(uint8_t* device_signature)
{
	device_signature[0] = DEVICE_SIGNATURE_0;
	device_signature[1] = DEVICE_SIGNATURE_1;
	device_signature[2] = DEVICE_SIGNATURE_2;
	device_signature[3] = DEVICE_SIGNATURE_3;

	// All done.
	return;
}

void set_bootloader_state(State new_state)
{
	state = new_state;
	switch (state)
	{
		case IDLE:
			blink_on = IDLE_ON;
			blink_off = IDLE_OFF;
			break;

		case COMMUNICATING:
			blink_on = COMMUNICATING_ON;
			blink_off = COMMUNICATING_OFF;
			break;

		case ERROR:
			blink_on = ERROR_ON;
			blink_off = ERROR_OFF;
			break;
	}
}

void get_bootloader_information(Shared_bootloader_constants* bootloader_information)
{
	bootloader_information->bootloader_version = BOOTLOADER_VERSION;

	// All done.
	return;
}

#ifndef __AVR_AT90CAN128__
void wdt_init(void)
{
    MCUSR = 0;
    wdt_disable();

    return;
}
#endif
// IMPLEMENT PRIVATE STATIC FUNCTIONS.

void reboot(void)
{
	// Make sure the watchdog is set to strike as quickly as possible.
	wdt_disable();
	wdt_enable(WDTO_15MS);

	// Loop continuously until the watchdog strikes.
	while (true)
	{
		// Do nothing while we wait for the watchdog to strike.
	}

	// We should never reach here.
	return;
}

bool is_clean(void)
{
	// Read the clean flag from EEPROM.
	uint16_t data;

	eeprom_busy_wait();
	eeprom_read_block(&data, (void*)(SHUTDOWNSTATE_MEM), 2);
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

	// Stop the ms timer.
	TIMSK0 = 0b00000000;

	// Shut down whatever module we were using.  This should return any affected peripherals to their initial states.
	mod.exit();

	// Put interrupts back into application-land.
	MCUCR = (1 << IVCE);
	MCUCR = (0 << IVSEL);

	// Make sure the blinkenlight is disabled.
	BLINK_WRITE = (LED_LOGIC) ? (BLINK_WRITE & ~BLINK_PIN) : (BLINK_WRITE | BLINK_PIN);

	// Stop the timer and return them to original state.
#if defined (__AVR_AT90CAN128__)
	TCCR0A = 0b00000000;
	OCR0A = 0;
#else
	TCCR0A = 0b00000000;
	TCCR0B = 0b00000000;
	OCR0A = 0;
	OCR0B = 0;
#endif

	// Stop the watchdog. If the user wants it in their application they can set it up themselves.
	wdt_reset();
	wdt_disable();

	// Jump into the application.
	asm("jmp 0x0000");

	// We should never reach here.
	return;
}

void write_flash_page(Firmware_page& buffer)
{
	// Disable interrupts.
	cli();

	// TODO - Replace this with something non-target specific.

	// Limit the page number to the application (NRWW) section.
	if (buffer.page < BOOTLOADER_START_ADDRESS)
	{
		// Get a pointer to the start of the data we're going to write.
		uint8_t* data = static_cast<uint8_t*>(buffer.data);	// NOTE - Because we've now disabled interrupts, we can treat data as non-volatile.

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

			// Fill the temporary EEPROM page buffer with the created word.
			boot_page_fill((buffer.page + i), w);
		}

		// Write the temporary EEPROM page buffer to the FLASH.
		boot_page_write(buffer.page);
		boot_spm_busy_wait();

		// Reenable the RWW EEPROM again.
		boot_rww_enable();

		// Clear the buffer so that it may be used again.
		buffer.ready_to_write = false;
		buffer.page = 0;
		buffer.current_byte = 0;
	}
	// Else something went terribly wrong, but we assume bootloader code always works.

	// Re-enable interrupts.
	sei();

	// All done.
	return;
}

void read_flash_page(Firmware_page& buffer)
{
	// Disable interrupts.
	cli();

	// TODO - Replace this with something non-target specific.

	// Limit the page number to the application (NRWW) section.
	if (buffer.page < BOOTLOADER_START_ADDRESS)
	{
		// Wait until the EEPROM is ready.
		eeprom_busy_wait();

		// Read flash page out byte by byte, up until the desired length.
		for (uint16_t i = 0; i < buffer.code_length; i++)
		{
			// Read a single byte from the flash.
			buffer.data[i] = READ_FLASH_BYTE(buffer.page + i);
		}

		// Clear the buffer so that it may be used again.
		buffer.ready_to_read = false;
		buffer.page = 0;
		buffer.current_byte = 0;
	}
	// Else something went terribly wrong, but we assume bootloader code always works.

	// Re-enable interrupts.
	sei();

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

/**
 * This ISR is called by a timer compare event on Timer/Counter 0; this is used to provide a 1ms periodic event which is used for boot
 * timeout detection, status LED blinking, and other periodic functionality.
 *
 */
#if defined (__AVR_AT90CAN128__)
ISR(TIMER0_COMP_vect)
#else
ISR(TIMER0_COMPA_vect)
#endif
{
	// Count how long has elapsed since the last time the module periodic event was fired.
	static uint16_t module_periodic_count = 0;
	module_periodic_count++;

	// Check if it is time for the event to be fired again.
	if (module_periodic_count >= MODULE_EVENT_PERIOD)
	{
		// Perform any module specific functionality which needs to be performed on a periodic basis.
		mod.event_periodic();

		// Start counting again.
		module_periodic_count = 0;
	}

	// Check if the bootloader timeout is actually enabled.
	if (timeout_enable)
	{
		// Advance the tick count.
		timeout_tick++;

		// Check if the timeout period has now expired.
		timeout_expired = (timeout_tick > BOOT_TIMEOUT);
	}
	else
	{
		// Reset the timeout count, so that if we restart the timeout, the counter starts again.
		timeout_tick = 0;
	}

	// Static bool indicating if the blink LED is on or off.
	static bool blink_state = false;

	// Increment the blink LED tick.
	blink_tick++;

	// Check which state the LED should be in.
	if (blink_state)
	{
		// Turn the LED on.
		BLINK_WRITE = (LED_LOGIC) ? (BLINK_WRITE | BLINK_PIN) : (BLINK_WRITE & ~BLINK_PIN);

		// If we've timed out, toggle the state of the LED.
		if (blink_tick >= blink_off)
		{
			// Change state to off.
			blink_state = false;

			// Start the tick counter again.
			blink_tick = 0;
		}
	}
	else
	{
		// Turn the LED off.
		BLINK_WRITE = (LED_LOGIC) ? (BLINK_WRITE & ~BLINK_PIN) : (BLINK_WRITE | BLINK_PIN);

		// If we've timed out, toggle the state of the LED.
		if (blink_tick >= blink_on)
		{
			// Change state to on.
			blink_state = true;

			// State the tick counter again.
			blink_tick = 0;
		}
	}

	// All done.
	return;
}

// ALL DONE.
