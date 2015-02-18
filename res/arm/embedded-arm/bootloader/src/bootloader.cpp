// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION
#include "bootloader.hpp"
#include "stm32f4xx/stm32f4xx.h"
#include "stm32f4xx/stm32f4xx_flash.h"
#include "stm32f4xx/misc.h"
#include "CMSIS/core_cm4.h"

// DEFINE CONSTANTS

#define PORT_A				GPIOA_BASE
#define PORT_B				GPIOB_BASE
#define PORT_C				GPIOC_BASE
#define PORT_D				GPIOD_BASE
#define PORT_E				GPIOE_BASE
#define PORT_F				GPIOF_BASE
#define PORT_G				GPIOG_BASE
#define PORT_H				GPIOH_BASE
#define PORT_I				GPIOI_BASE

enum pin_t : uint16_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9, PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15};
enum input_state {LO, HI};

// #define BLINK_PORT_NUM		<<<TC_INSERTS_BLINK_PORT_HERE>>>
// #define BLINK_PIN_NUM		<<<TC_INSERTS_BLINK_PIN_HERE>>>
// #define CLK_SPEED_IN_MHZ	<<<TC_INSERTS_CLK_SPEED_IN_MHZ_HERE>>>
// #define FORCE_BL_PORT_NUM	<<<TC_INSERTS_FORCE_BL_PORT_HERE>>>
// #define FORCE_BL_PIN_NUM	<<<TC_INSERTS_FORCE_BL_PIN_HERE>>>
// #define LED_LOGIC			<<<TC_INSERTS_LED_LOGIC_HERE>>>
// #define INPUT_LOGIC			<<<TC_INSERTS_INPUT_LOGIC_HERE>>>
#define BLINK_PORT_NUM		PORT_D
#define BLINK_PIN_NUM		PIN_15
#define CLK_SPEED_IN_MHZ	(SystemCoreClock / 1000000)
#define FORCE_BL_PORT_NUM	PORT_A
#define FORCE_BL_PIN_NUM	PIN_0
#define LED_LOGIC			1 		// 0 if LED is on when logic level is low. 1 otherwise.
#define INPUT_LOGIC			1 		// 0 if button is on when logic level is low. 1 otherwise.
#define PORT_MULTIPLIER		1
// The port address is cast into the GPIO_TypeDef struct so that memory can be accessed neatly.
#define BLINK_READ			((GPIO_TypeDef *)BLINK_PORT_NUM)->ODR
#define BLINK_WRITE			((GPIO_TypeDef *)BLINK_PORT_NUM)->ODR
#define BLINK_MODE			((GPIO_TypeDef *)BLINK_PORT_NUM)->MODER
#define BLINK_PULL_RES		((GPIO_TypeDef *)BLINK_PORT_NUM)->PUPDR
#define BLINK_OUT_TYPE		((GPIO_TypeDef *)BLINK_PORT_NUM)->OTYPER
#define BLINK_PIN_SPEED		((GPIO_TypeDef *)BLINK_PORT_NUM)->OSPEEDR
#define BLINK_ALT_FUNC_L	((GPIO_TypeDef *)BLINK_PORT_NUM)->AFR[0]
#define BLINK_ALT_FUNC_H	((GPIO_TypeDef *)BLINK_PORT_NUM)->AFR[1]
#define FORCE_BL_READ		((GPIO_TypeDef *)FORCE_BL_PORT_NUM)->IDR
#define FORCE_BL_MODE		((GPIO_TypeDef *)FORCE_BL_PORT_NUM)->MODER
#define FORCE_BL_PUL_RES	((GPIO_TypeDef *)FORCE_BL_PORT_NUM)->PUPDR

#define BLINK_PIN 			( 1 << BLINK_PIN_NUM )
#define FORCE_BL_PIN		( 1 << FORCE_BL_PIN_NUM )

#define CLK_SPEED 			SystemCoreClock
#define SYSTICK_FREQ_HZ		1000
#define BOOT_TIMEOUT		10000  // Timeout in milliseconds.

#define APP_START_ADDRESS	0x08004000

// Blink times for different states. Times are in ms.

#define BLINK_PRSCL			(8400 - 1)
#define BLINK_RELOAD		(10000 - 1)

// Idle
#define IDLE_ON				100
#define IDLE_OFF			100

// Communicating
#define COMMUNICATING_ON	6000
#define COMMUNICATING_OFF	0

// Error
#define ERROR_ON			200
#define ERROR_OFF			1000

// #define SHUTDOWN_STATE_MEM	<<<TC_INSERTS_SHUTDOWN_STATE_MEM_HERE>>>
// #define SHUTDOWN_STATE_MEM	0x08003FFF
#define SHUTDOWN_STATE_MEM	0x080E0000

#define CLEAN_FLAG			0xAFAF

// #define BOOTLOADER_MODULE	<<<TC_INSERTS_BOOTLOADER_ACTIVE_MODULE_HERE>>>
#define BOOTLOADER_MODULE	bootloader_module_can

#define BOOTLOADER_VERSION	0x001  // TODO - how is this updated.

#define DEVICE_SIGNATURE_0	0x00
#define DEVICE_SIGNATURE_1	0x00
#define DEVICE_SIGNATURE_2	0x00
#define DEVICE_SIGNATURE_3	0x00

// Define the address at which the bootloader code starts
#define BOOTLOADER_START_ADDRESS	0x00000000

// DEFINE PRIVATE TYPES AND STRUCTS

// DECLARE PRIVATE GLOBAL VARIABLES

// All periodic functionality is queued by the 1ms systick interrupt. To time longer periods, you need to accumulate a count of ticks.
volatile uint16_t timeout_tick = 0;

volatile uint16_t blink_tick = 0;

// State the bootloader is in.  At the moment, all this determines is the LED flashing pattern.
State state = BOOT_IDLE;

volatile uint16_t blink_on = IDLE_ON;
volatile uint16_t blink_off = IDLE_OFF;

volatile bool timeout_expired = false;
volatile bool timeout_enable = true;

BOOTLOADER_MODULE module; // This means all the communication modules must have an object defined in them called - extern <class name> module.
Bootloader_module& mod = module;

Firmware_page buffer;

// DEFINE PRIVATE FUNCTION PROTOTYPES

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

// IMPLEMENT PUBLIC STATIC FUNCTIONS

int main(void)
{
	// Configure the watchdog timer to trigger every 512ms
	// Even the bootloader must satisfy the watchdog.
	// The watchdog timer cannot be disabled without a system reset. If it is enabled here, the application
	// will need to also use it.
	#warning "Watchdog not enabled."
	// IWDG->KR	= 0x5555;  // Unlock the prescaler and reload registers
	// IWDG->PR	= 0x0;
	// IWDG->RLR	= 0xFFF;
	// IWDG->KR	= 0xCCCC;  // Start the watchdog

	// This terrible line turns the address of BLINK_PORT_NUM (which is actually GPIOx_BASE) into a bitmask from
	// zero to nine.
	// This is achieved by eliminating the top half of the address (since this only gives the address of AHB1PERIPH_BASE),
	// dividing by 0x400 (since that is the size of each GPIO's register set) and then bitshifting '1' by the result.
	// GPIOA_BASE results in 0x00, GPIOB_BASE results in 0x01, etc.
	RCC->AHB1ENR 		|= (1 << ((BLINK_PORT_NUM & 0xFFFF)/0x400));  // Enable the LED port peripheral clock
	RCC->AHB1ENR 		|= (1 << ((FORCE_BL_PORT_NUM & 0xFFFF)/0x400));  // Enable the FORCE_BL port peripheral clock

	// Configure the Blink LED GPIO
	BLINK_MODE	 		|= (((uint32_t)0x1) << (BLINK_PIN_NUM*2));  // Set LED pin as output
	BLINK_OUT_TYPE 		|= (((uint32_t)0x0) << (BLINK_PIN_NUM*2));  // Configure as push-pull
	BLINK_PIN_SPEED		|= (((uint32_t)0x3) << (BLINK_PIN_NUM*2));  // Configure the pin switching speed
	BLINK_PULL_RES 		|= (((uint32_t)0x0) << (BLINK_PIN_NUM*2));  // Disable the pull-up/pull-down resistor

	// Configure the boot button GPIO
	FORCE_BL_MODE		|= (((uint32_t)0x1) << (BLINK_PIN_NUM*2));  // Set FORCE_BL pin as input
	FORCE_BL_PUL_RES	|= (((uint32_t)0x0) << (BLINK_PIN_NUM*2));  // Disable the pull-up/pull-down resistor

	// Turn on the blinkenlight solidly.
	BLINK_WRITE = (LED_LOGIC) ? (BLINK_WRITE|BLINK_PIN) : (BLINK_WRITE & ~BLINK_PIN);

	// Check the state of the 'application run' marker, and the state of the force-bootloader input pin.
	if ((is_clean()) && (((FORCE_BL_READ & FORCE_BL_PIN) >> FORCE_BL_PIN_NUM) == (INPUT_LOGIC ? LO : HI)))
	{
		// The marker seemed clean, and the force-bootloader input is not asserted, so start the application immediately.
		BLINK_WRITE &= ~BLINK_PIN;

		// Run the application.
		run_application();
	}
	// Else if we get here, that means that the application didn't end cleanly, and so we might need to load new firmware.

	// Start up whichever peripherals are required by the modules we're using.
	#warning mod.init();

    // Set up the SysTick Interrupt to produce a 1ms interrupt for any periodic functionality.
    if (SysTick_Config(SystemCoreClock/(8*SYSTICK_FREQ_HZ)))
    {
    	// There was an error while configuring the SysTick.
    	while (true);
    }
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

    // Set the bootloader into idle mode.
    set_bootloader_state(BOOT_IDLE);

    while (1);

    // Now we loop continuously until either some firmware arrives or we decide to try the application code anyway.
	while (true)
	{
		// During this loop, the blinken light should be flashing, which tells us that things are still working as expected.

		// Touch the watchdog.
		#warning wdt_reset();

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
			// Write the buffer to flash. This blocks, with interrupts disabled whilst the operation is in progress.
			write_flash_page(buffer);
		}

		// If the buffer is ready to be read from, read it back again.
		if (buffer.ready_to_read)
		{
			// Read from flash into the buffer. This blocks, with interrupts disabled, whilst the operation is in progress.
			read_flash_page(buffer);
		}
	}

	// We should never reach here.
	return 0;
}

void boot_mark_clean(void)
{
	// Unlock the EEPROM for programming.
	FLASH_Unlock();

	// Clear the clean flag in EEPROM, thus making the memory 'dirty'.
	FLASH_ProgramHalfWord(SHUTDOWN_STATE_MEM, CLEAN_FLAG);

	// Lock the EEPROM after writing.
	FLASH_Lock();

	// All done.
	return;
}

void boot_mark_dirty(void)
{
	// Unlock the EEPROM for programming.
	FLASH_Unlock();

	// Clear the clean flag in EEPROM, thus making the memory 'dirty'.
	FLASH_ProgramHalfWord(SHUTDOWN_STATE_MEM, 0x0000);

	// Lock the EEPROM after writing.
	FLASH_Lock();

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
	// Run the application
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
		case BOOT_IDLE:
			blink_on = IDLE_ON;
			blink_off = IDLE_OFF;
			break;
			
		case BOOT_COMMUNICATING:
			blink_on = COMMUNICATING_ON;
			blink_off = COMMUNICATING_OFF;
			break;
		
		case BOOT_ERROR:
			blink_on = ERROR_ON;
			blink_off = ERROR_OFF;
			break;
	}
}

// IMPLEMENT PRIVATE STATIC FUNCTIONS

void reboot(void) 
{
	// Asserts the SYSRESETREQ flag in the Application interrupt and reset control register (AIRCR)
	// Causes an immediate system reset.
	NVIC_SystemReset();

	return;
}

bool is_clean(void)
{
	// Read the clean flag from EEPROM
	if (*(uint16_t *)SHUTDOWN_STATE_MEM == CLEAN_FLAG)
	{
		// The flag was clean.
		return true;
	}
	// Else the flag is presumed dirty.
	return false;
}

void run_application(void)
{
	// Disable Interrupts.
	__disable_irq();

	// Set the application run marker to 'dirty', so that the application must 'clean' it when it shuts down.
	boot_mark_dirty();

	// TODO - Make sure we're all good to go.

	// Shut down whatever module we're using. This should return any affected peripherals to their initial states.
	mod.exit();

	// Stop the Systick interrupt.
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Disable the Systick timer and interrupt.
	SysTick->CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

	// Reset all of the GPIO
	RCC->AHB1RSTR |= (RCC_AHB1RSTR_GPIOARST | RCC_AHB1RSTR_GPIOBRST | RCC_AHB1RSTR_GPIOCRST | RCC_AHB1RSTR_GPIODRST | RCC_AHB1RSTR_GPIOERST |
						RCC_AHB1RSTR_GPIOFRST | RCC_AHB1RSTR_GPIOGRST | RCC_AHB1RSTR_GPIOHRST | RCC_AHB1RSTR_GPIOIRST);

	// If the watchdog was enabled, it cannot be disabled without a hardware reset. The application will have to use it too.

	// Start execution of the application code.
	const uint32_t app_start_address = APP_START_ADDRESS;  // Load the #define into a variable for the extended asm command.
	asm("ldr R0, %[app_address]"::[app_address] "m" (app_start_address):);  // Load the firmware address into register 0 using an extended asm command.
	asm("ldr sp, [R0]");  // Load the stack pointer with the value stored at the firmware start address.
	asm("ldr pc, [R0, #4]");  // Load the program counter value stored in the second word from the firmware start address.
}

void write_flash_page(Firmware_page& buffer) 
{
	// Disable Interrupts
	__disable_irq();

	// Get the address in FLASH for the next byte of memory.
	uint32_t address = buffer.page;

	// Unlock the FLASH for writing.
	FLASH_Unlock();

	// Erase the FLASH page that we're about to write.
	#warning "This doesn't really work for the STM32F4xx. The flash pages are massive and not regularly sized."

	// Write the data from the page to FLASH, one byte at a time.
	for (uint16_t i = 0; i < buffer.code_length; i++)
	{
		// Write the byte to memory.
		FLASH_ProgramByte(address, buffer.data[i]);
		// Increment to the next memory location
		address++;
	}

	// Lock the flash
	FLASH_Lock();

	// Clear the buffer so that it may be used again.
	buffer.ready_to_write = false;
	buffer.page = 0;
	buffer.current_byte = 0;

	// Re-enable interrupts.
	__enable_irq();
	// Service any interrupts that occurred since interrupts were disabled.
	__ISB();

	// All Done.
	return;
}

void read_flash_page(Firmware_page& buffer) 
{
	// Disable interrupts.
	__disable_irq();

	// Read flash out byte by byte, up until the desired length.
	for (uint16_t i = 0; i < buffer.code_length; i++)
	{
		buffer.data[i] = *(uint8_t *)buffer.page;
	}

	// Re-enable interrupts.
	__enable_irq();
	// Service any interrupts that occurred since interrupts were disabled.
	__ISB();

	// All done.
	return;
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

/*
 * This ISR is called every millisecond. This is used to cue any periodic events.
 *
 */
extern "C" void SysTick_Handler(void) 
{
	// NOTE - The SysTick interrupt does not need clearing.

	// Count how long has elapsed since the last time the module periodic event was fired.
	static uint16_t module_periodic_count = 0;
	module_periodic_count++;

	#warning
	// // Check if it is time for the event to be fired again.
	// if (module_periodic_count >= MODULE_EVENT_PERIOD)
	// {
	// 	// Perform any module specific functionality which needs to be performed on a periodic basis.
	// 	mod.event_periodic();

	// 	// Start counting again.
	// 	module_periodic_count = 0;
	// }

	// Check if the bootloader timeout is actually enabled.
	if (timeout_enable)
	{
		// Advance the tick ount.
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
