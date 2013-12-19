/********************************************************************************************************************************
 *
 *  FILE: 		startup.c
 *
 *  TARGET:		STM32F10x
 *
 *  AUTHOR: 		Edwin Hayes
 *
 *  DATE CREATED:	17th December 2013
 *
 *	Default source code for providing startup functionality on STM32 Cortex-M series targets.  Configures ISR vectors,
 *	populates BSS and Data sections, then jumps into main.
 *
 ********************************************************************************************************************************/

// INCLUDE THE MATCHING HEADER FILE.

#include "<<<TC_INSERTS_H_FILE_NAME_HERE>>>"

// INCLUDE REQUIRED HEADER FILES FOR IMPLEMENTATION.

// DEFINE PRIVATE MACROS.

// DEFINE PRIVATE FUNCTION PROTOTYPES.

/*
 * Provides an ISR handler for interrupts which have not been configured.  The ISR does nothing, blocking forever.
 *
 * @param	Nothing.
 * @return	Nothing.
 */
void handler_default(void);

/*
 * Provides an ISR handler for the reset interrupt.  The ISR populates BSS and Data sections of RAM, then jumps into main.
 *
 * NOTE - Control flow will probably never return from this ISR, assuming main() blocks forever.
 *
 * @param	Nothing.
 * @return	Nothing.
 */
void handler_reset(void);

// DEFINE PRIVATE TYPES AND STRUCTS.

// DECLARE PRIVATE GLOBAL VARIABLES.

// The all important ISR vector table.
__attribute__ ((section(".isr_vector")))
void (* const table_interrupt_vector[])(void) =
{
	// Core interrupts (exceptions).
	(void *) &_estack,	// 00 - Stack location.
	handler_reset,		// 01 -	(Reset) Reset interrupt handler.
	handler_default,	// 02 - (NMI) Non-maskable interrupt handler.
	handler_default,	// 03 - (HardFault) Handler for all classes of unhandled fault.
	handler_default,	// 04 - (MemManage) Memory management handler.
	handler_default,	// 05 - (BusFault) Prefetch and memory access fault handler.
	handler_default,	// 06 - (UsageFault) Undefined instruction or illegal state handler.
	0, 			// 07 - Reserved.
	0, 			// 08 - Reserved.
	0, 			// 09 - Reserved.
	0, 			// 10 - Reserved.
	handler_default,	// 11 - (SVCall) System service call (SWI) handler.
	handler_default,	// 12 - Reserved for debug monitor.
	0, 			// 13 - Reserved.
	handler_default,	// 14 - (PendSV) Pendable system service call handler.
	handler_default,	// 15 - (SysTick) System tick timer handler.
	// Peripheral interupts (IRQ).
	handler_default,	// 00
	handler_default,	// 01
	handler_default,	// 02
	handler_default,	// 03
	handler_default,	// 04
	handler_default,	// 05
	handler_default,	// 06
	handler_default,	// 07
	handler_default,	// 08
	handler_default,	// 09
	handler_default,	// 10
	handler_default,	// 11
	handler_default,	// 12
	handler_default,	// 13
	handler_default,	// 14
	handler_default,	// 15
	handler_default,	// 16
	handler_default,	// 17
	handler_default,	// 18
	handler_default,	// 19
	handler_default,	// 20
	handler_default,	// 21
	handler_default,	// 22
	handler_default,	// 23
	handler_default,	// 24
	handler_default,	// 25
	handler_default,	// 26
	handler_default,	// 27
	handler_default,	// 28
	handler_default,	// 29
	handler_default,	// 30
	handler_default,	// 31
	handler_default,	// 32
	handler_default,	// 33
	handler_default,	// 34
	handler_default,	// 35
	handler_default,	// 36
	handler_default,	// 37
	handler_default,	// 38
	handler_default,	// 39
	handler_default,	// 40
	handler_default,	// 41
	handler_default,	// 42
	handler_default,	// 43
	handler_default,	// 44
	handler_default,	// 45
	handler_default,	// 46
	handler_default,	// 47
	handler_default,	// 48
	handler_default,	// 49
	handler_default,	// 50
	handler_default,	// 51
	handler_default,	// 52
	handler_default,	// 53
	handler_default,	// 54
	handler_default,	// 55
	handler_default,	// 56
	handler_default,	// 57
	handler_default,	// 58
	handler_default,	// 59
	handler_default 	// 60
};

// IMPLEMENT PUBLIC FUNCTIONS.

// IMPLEMENT PRIVATE FUNCTIONS.

void handler_default(void)
{
	// Loop forever.
	while (1)
	{
		// Do nothing.
	}

	// We should never reach here.
}

void handler_reset(void)
{
	unsigned long *source;
	unsigned long *destination;

	// NOTE - External symbols with the address of each section are provided by the linker.

	// Copy initialised variables from FLASH to RAM, populating the Data section.
	source = &_sidata;
	for (destination = &_sdata; destination < &_edata;)
	{
		*(destination++) = *(source++);
	}

	// Zero uninitialised variables in RAM, populating the BSS.
	for (destination = &_sbss; destination < &_ebss;)
	{
		*(destination++) = 0;
	}

	// Start the main programme.
	main();

	// We should never reach here.
}

// IMPLEMENT INTERRUPT SERVICE ROUTINES.

// ALL DONE.


















