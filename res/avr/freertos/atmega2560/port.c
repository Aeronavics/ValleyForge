/*
	FreeRTOS.org V4.8.0 - Copyright (C) 2003-2008 Richard Barry.

	This file is part of the FreeRTOS.org distribution.

	FreeRTOS.org is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS.org is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS.org; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS.org, without being obliged to provide
	the source code for any proprietary components.  See the licensing section 
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************
	***************************************************************************
    *                                                                         *
    * SAVE TIME AND MONEY!  We can port FreeRTOS.org to your own hardware,    *
    * and even write all or part of your application on your behalf.          *
    * See http://www.OpenRTOS.com for details of the services we provide to   *
    * expedite your project.                                                  *
    *                                                                         *
    ***************************************************************************
    ***************************************************************************

	Please ensure to read the configuration and relevant port sections of the
	online documentation.

	http://www.FreeRTOS.org - Documentation, latest information, license and 
	contact details.

	http://www.SafeRTOS.com - A version that is certified for use in safety 
	critical systems.

	http://www.OpenRTOS.com - Commercial support, development, porting, 
	licensing and training services.
*/

/* 

Changes from V2.6.0

	+ AVR port - Replaced the inb() and outb() functions with direct memory
	  access.  This allows the port to be built with the 20050414 build of
	  WinAVR.
*/

#include <stdlib.h>
#include <avr/interrupt.h>

#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------------------------
 * Implementation of functions defined in portable.h for the AVR port.
 *----------------------------------------------------------------------------*/

/* If we're using the Real Time Clock counter, check the processor for Timer 0
 * or Timer 2 usage
 */

#ifndef USE_RTC_TIMER
	#define USE_RTC_TIMER
#endif
#ifdef USE_RTC_TIMER
	#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		#define __ATmegaxx0__
		#define TIMER_COMPARE_SIG	SIG_OUTPUT_COMPARE2A
	#else
		#define TIMER_COMPARE_SIG	SIG_OUTPUT_COMPARE0A
	#endif
#else
	#define TIMER_COMPARE_SIG	SIG_OUTPUT_COMPARE1A
#endif

/* Start tasks with interrupts enables. */
#define portFLAGS_INT_ENABLED					( ( portSTACK_TYPE ) 0x80 )

/* Hardware constants for timer 1. */
#define portCLEAR_COUNTER_ON_MATCH				( ( unsigned portCHAR ) (1 << WGM12) )
#define portPRESCALE_64							( ( unsigned portCHAR ) (1 << CS11) | (1 << CS10) )
#define portCLOCK_PRESCALER						( ( unsigned portLONG ) 64 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE	( ( unsigned portCHAR ) (1 << OCIE1A) )

#if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#  define TIMSK TIMSK1		// ATmega640/1280/2560 has more than one TIMSK register
#endif

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
typedef void tskTCB;
extern volatile tskTCB * volatile pxCurrentTCB;

portTickType portTicksPerSecond;

/*-----------------------------------------------------------*/

/* 
 * Macro to save all the general purpose registers, the save the stack pointer
 * into the TCB.  
 * 
 * The first thing we do is save the flags then disable interrupts.  This is to 
 * guard our stack against having a context switch interrupt after we have already 
 * pushed the registers onto the stack - causing the 32 registers to be on the 
 * stack twice. 
 * 
 * r1 is set to zero as the compiler expects it to be thus, however some
 * of the math routines make use of R1. 
 * 
 * The interrupts will have been disabled during the call to portSAVE_CONTEXT()
 * so we need not worry about reading/writing to the stack pointer. 
 *
 * Note that for the ATmega256x we also need to store the RAMPZ and EIND registers.
 */
#if 0 // always_inline requires optimization of at least -O1
void portSAVE_CONTEXT( void )  __attribute__ ( ( naked, always_inline ) );
void portSAVE_CONTEXT( void )
{
	asm volatile (	"push	r0						\n\t"
					"in		r0, __SREG__			\n\t"
					"cli							\n\t"
					"push	r0						\n\t"
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
					"in		r0, 0x3b				\n\t"
					"push	r0						\n\t"
					"in		r0, 0x3c				\n\t"
					"push	r0						\n\t"
#endif
					"push	r1						\n\t"
					"clr	r1						\n\t"
					"push	r2						\n\t"
					"push	r3						\n\t"
					"push	r4						\n\t"
					"push	r5						\n\t"
					"push	r6						\n\t"
					"push	r7						\n\t"
					"push	r8						\n\t"
					"push	r9						\n\t"
					"push	r10						\n\t"
					"push	r11						\n\t"
					"push	r12						\n\t"
					"push	r13						\n\t"
					"push	r14						\n\t"
					"push	r15						\n\t"
					"push	r16						\n\t"
					"push	r17						\n\t"
					"push	r18						\n\t"
					"push	r19						\n\t"
					"push	r20						\n\t"
					"push	r21						\n\t"
					"push	r22						\n\t"
					"push	r23						\n\t"
					"push	r24						\n\t"
					"push	r25						\n\t"
					"push	r26						\n\t"
					"push	r27						\n\t"
					"push	r28						\n\t"
					"push	r29						\n\t"
					"push	r30						\n\t"
					"push	r31						\n\t"
					"lds	r26, pxCurrentTCB		\n\t"
					"lds	r27, pxCurrentTCB + 1	\n\t"
					"in		r0, 0x3d				\n\t"
					"st		x+, r0					\n\t"
					"in		r0, 0x3e				\n\t"
					"st		x+, r0					\n\t"
				);
}
#endif

#ifndef __AVR_3_BYTE_PC__
/* 2-Byte PC Save */
#define portSAVE_CONTEXT()									\
	asm volatile (	"push	r0						\n\t"	\
					"in		r0, __SREG__			\n\t"	\
					"cli							\n\t"	\
					"push	r0						\n\t"	\
					"push	r1						\n\t"	\
					"clr	r1						\n\t"	\
					"push	r2						\n\t"	\
					"push	r3						\n\t"	\
					"push	r4						\n\t"	\
					"push	r5						\n\t"	\
					"push	r6						\n\t"	\
					"push	r7						\n\t"	\
					"push	r8						\n\t"	\
					"push	r9						\n\t"	\
					"push	r10						\n\t"	\
					"push	r11						\n\t"	\
					"push	r12						\n\t"	\
					"push	r13						\n\t"	\
					"push	r14						\n\t"	\
					"push	r15						\n\t"	\
					"push	r16						\n\t"	\
					"push	r17						\n\t"	\
					"push	r18						\n\t"	\
					"push	r19						\n\t"	\
					"push	r20						\n\t"	\
					"push	r21						\n\t"	\
					"push	r22						\n\t"	\
					"push	r23						\n\t"	\
					"push	r24						\n\t"	\
					"push	r25						\n\t"	\
					"push	r26						\n\t"	\
					"push	r27						\n\t"	\
					"push	r28						\n\t"	\
					"push	r29						\n\t"	\
					"push	r30						\n\t"	\
					"push	r31						\n\t"	\
					"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"in		r0, 0x3d				\n\t"	\
					"st		x+, r0					\n\t"	\
					"in		r0, 0x3e				\n\t"	\
					"st		x+, r0					\n\t"	\
				);
#else
/* 3-Byte PC Save */
#define portSAVE_CONTEXT()									\
	asm volatile (	"push	r0						\n\t"	\
					"in		r0, __SREG__			\n\t"	\
					"cli							\n\t"	\
					"push	r0						\n\t"	\
					"in		r0, 0x3b				\n\t"	\
					"push	r0						\n\t"	\
					"in		r0, 0x3c				\n\t"	\
					"push	r0						\n\t"	\
					"push	r1						\n\t"	\
					"clr	r1						\n\t"	\
					"push	r2						\n\t"	\
					"push	r3						\n\t"	\
					"push	r4						\n\t"	\
					"push	r5						\n\t"	\
					"push	r6						\n\t"	\
					"push	r7						\n\t"	\
					"push	r8						\n\t"	\
					"push	r9						\n\t"	\
					"push	r10						\n\t"	\
					"push	r11						\n\t"	\
					"push	r12						\n\t"	\
					"push	r13						\n\t"	\
					"push	r14						\n\t"	\
					"push	r15						\n\t"	\
					"push	r16						\n\t"	\
					"push	r17						\n\t"	\
					"push	r18						\n\t"	\
					"push	r19						\n\t"	\
					"push	r20						\n\t"	\
					"push	r21						\n\t"	\
					"push	r22						\n\t"	\
					"push	r23						\n\t"	\
					"push	r24						\n\t"	\
					"push	r25						\n\t"	\
					"push	r26						\n\t"	\
					"push	r27						\n\t"	\
					"push	r28						\n\t"	\
					"push	r29						\n\t"	\
					"push	r30						\n\t"	\
					"push	r31						\n\t"	\
					"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"in		r0, 0x3d				\n\t"	\
					"st		x+, r0					\n\t"	\
					"in		r0, 0x3e				\n\t"	\
					"st		x+, r0					\n\t"	\
				);
#endif
/* 
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer. 
 */

#if 0 // always_inline requires optimization of at least -O1
void portRESTORE_CONTEXT( void )  __attribute__ ( ( naked, always_inline ) );
void portRESTORE_CONTEXT( void )
{
	asm volatile (	"lds	r26, pxCurrentTCB		\n\t"
					"lds	r27, pxCurrentTCB + 1	\n\t"
					"ld		r28, x+					\n\t"
					"out	__SP_L__, r28			\n\t"
					"ld		r29, x+					\n\t"
					"out	__SP_H__, r29			\n\t"
					"pop	r31						\n\t"
					"pop	r30						\n\t"
					"pop	r29						\n\t"
					"pop	r28						\n\t"
					"pop	r27						\n\t"
					"pop	r26						\n\t"
					"pop	r25						\n\t"
					"pop	r24						\n\t"
					"pop	r23						\n\t"
					"pop	r22						\n\t"
					"pop	r21						\n\t"
					"pop	r20						\n\t"
					"pop	r19						\n\t"
					"pop	r18						\n\t"
					"pop	r17						\n\t"
					"pop	r16						\n\t"
					"pop	r15						\n\t"
					"pop	r14						\n\t"
					"pop	r13						\n\t"
					"pop	r12						\n\t"
					"pop	r11						\n\t"
					"pop	r10						\n\t"
					"pop	r9						\n\t"
					"pop	r8						\n\t"
					"pop	r7						\n\t"
					"pop	r6						\n\t"
					"pop	r5						\n\t"
					"pop	r4						\n\t"
					"pop	r3						\n\t"
					"pop	r2						\n\t"
					"pop	r1						\n\t"
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
					"pop	r0						\n\t"
					"out	0x3c, r0				\n\t"
					"pop	r0						\n\t"
					"out	0x3b, r0				\n\t"
#endif
					"pop	r0						\n\t"
					"out	__SREG__, r0			\n\t"
					"pop	r0						\n\t"
				);
}
#endif

#ifndef __AVR_3_BYTE_PC__
/* 2-Byte PC Restore */
#define portRESTORE_CONTEXT()								\
	asm volatile (	"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"ld		r28, x+					\n\t"	\
					"out	__SP_L__, r28			\n\t"	\
					"ld		r29, x+					\n\t"	\
					"out	__SP_H__, r29			\n\t"	\
					"pop	r31						\n\t"	\
					"pop	r30						\n\t"	\
					"pop	r29						\n\t"	\
					"pop	r28						\n\t"	\
					"pop	r27						\n\t"	\
					"pop	r26						\n\t"	\
					"pop	r25						\n\t"	\
					"pop	r24						\n\t"	\
					"pop	r23						\n\t"	\
					"pop	r22						\n\t"	\
					"pop	r21						\n\t"	\
					"pop	r20						\n\t"	\
					"pop	r19						\n\t"	\
					"pop	r18						\n\t"	\
					"pop	r17						\n\t"	\
					"pop	r16						\n\t"	\
					"pop	r15						\n\t"	\
					"pop	r14						\n\t"	\
					"pop	r13						\n\t"	\
					"pop	r12						\n\t"	\
					"pop	r11						\n\t"	\
					"pop	r10						\n\t"	\
					"pop	r9						\n\t"	\
					"pop	r8						\n\t"	\
					"pop	r7						\n\t"	\
					"pop	r6						\n\t"	\
					"pop	r5						\n\t"	\
					"pop	r4						\n\t"	\
					"pop	r3						\n\t"	\
					"pop	r2						\n\t"	\
					"pop	r1						\n\t"	\
					"pop	r0						\n\t"	\
					"out	__SREG__, r0			\n\t"	\
					"pop	r0						\n\t"	\
				);
#else
/* 3-Byte PC Restore */
#define portRESTORE_CONTEXT()								\
	asm volatile (	"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"ld		r28, x+					\n\t"	\
					"out	__SP_L__, r28			\n\t"	\
					"ld		r29, x+					\n\t"	\
					"out	__SP_H__, r29			\n\t"	\
					"pop	r31						\n\t"	\
					"pop	r30						\n\t"	\
					"pop	r29						\n\t"	\
					"pop	r28						\n\t"	\
					"pop	r27						\n\t"	\
					"pop	r26						\n\t"	\
					"pop	r25						\n\t"	\
					"pop	r24						\n\t"	\
					"pop	r23						\n\t"	\
					"pop	r22						\n\t"	\
					"pop	r21						\n\t"	\
					"pop	r20						\n\t"	\
					"pop	r19						\n\t"	\
					"pop	r18						\n\t"	\
					"pop	r17						\n\t"	\
					"pop	r16						\n\t"	\
					"pop	r15						\n\t"	\
					"pop	r14						\n\t"	\
					"pop	r13						\n\t"	\
					"pop	r12						\n\t"	\
					"pop	r11						\n\t"	\
					"pop	r10						\n\t"	\
					"pop	r9						\n\t"	\
					"pop	r8						\n\t"	\
					"pop	r7						\n\t"	\
					"pop	r6						\n\t"	\
					"pop	r5						\n\t"	\
					"pop	r4						\n\t"	\
					"pop	r3						\n\t"	\
					"pop	r2						\n\t"	\
					"pop	r1						\n\t"	\
					"pop	r0						\n\t"	\
					"out	0x3c, r0				\n\t"	\
					"pop	r0						\n\t"	\
					"out	0x3b, r0				\n\t"	\
					"pop	r0						\n\t"	\
					"out	__SREG__, r0			\n\t"	\
					"pop	r0						\n\t"	\
				);
#endif



/*-----------------------------------------------------------*/

/*
 * Perform hardware setup to enable ticks from timer 1, compare match A.
 */
static void prvSetupTimerInterrupt( void );
/*-----------------------------------------------------------*/

/* 
 * See header file for description. 
 */
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
{
#ifdef __AVR_3_BYTE_PC__
//unsigned portLONG  ulAddress;
#endif
unsigned portSHORT usAddress;

	/* Place a few bytes of known values on the bottom of the stack. 
	This is just useful for debugging. */

	*pxTopOfStack = 0x11;
	pxTopOfStack--;
	*pxTopOfStack = 0x22;
	pxTopOfStack--;
	*pxTopOfStack = 0x33;
	pxTopOfStack--;

	/* Simulate how the stack would look after a call to vPortYield() generated by 
	the compiler. */

	/*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

	/* The start of the task code will be popped off the stack last, so place
	it on first. */

#ifdef __AVR_3_BYTE_PC__
	/* The AVR ATmega2560/ATmega2561 have 256KBytes of program memory and a 17-bit
	 * program counter.  When a code address is stored on the stack, it takes 3 bytes
	 * instead of 2 for the other ATmega* chips.
	 *
	 * Store 0 as the top byte since we force all task routines to the bottom 128K
	 * of flash.
	 *
	 * In order to do this properly, we would need to get a full 3-byte poinbter to 
	 * pxCode.  That requires a change to GCC.  Not likely to happen any time soon.
	 */
	usAddress = ( unsigned portSHORT ) pxCode;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

//	usAddress >>= 8;
//	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	*pxTopOfStack = 0;
	pxTopOfStack--;
#else
	usAddress = ( unsigned portSHORT ) pxCode;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;
#endif

	/* Next simulate the stack as if after a call to portSAVE_CONTEXT().  
	 * portSAVE_CONTEXT places the flags on the stack immediately after r0
	 * to ensure the interrupts get disabled as soon as possible, and so ensuring
	 * the stack use is minimal should a context switch interrupt occur.
	 */
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* R0 */
	pxTopOfStack--;
	*pxTopOfStack = portFLAGS_INT_ENABLED;
	pxTopOfStack--;

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)

	/* If we have an ATmega256x, we are also saving the RAMPZ and EIND registers.
	 * We should default those to 0.
	 */
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* EIND */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* RAMPZ */
	pxTopOfStack--;

#endif


	/* Now the remaining registers.   The compiler expects R1 to be 0. */
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* R1 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x02;	/* R2 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x03;	/* R3 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x04;	/* R4 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x05;	/* R5 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x06;	/* R6 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x07;	/* R7 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x08;	/* R8 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x09;	/* R9 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x10;	/* R10 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x11;	/* R11 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x12;	/* R12 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x13;	/* R13 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x14;	/* R14 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x15;	/* R15 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x16;	/* R16 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x17;	/* R17 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x18;	/* R18 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x19;	/* R19 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x20;	/* R20 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x21;	/* R21 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x22;	/* R22 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x23;	/* R23 */
	pxTopOfStack--;

	/* Place the parameter on the stack in the expected location. */
	usAddress = ( unsigned portSHORT ) pvParameters;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

	*pxTopOfStack = ( portSTACK_TYPE ) 0x26;	/* R26 X */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x27;	/* R27 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x28;	/* R28 Y */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x29;	/* R29 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x30;	/* R30 Z */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x31;	/* R31 */
	pxTopOfStack--;

	/*lint +e950 +e611 +e923 */

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

portBASE_TYPE xPortStartScheduler( void )
{
	/* In this port we ignore the parameter and use the configUSE_PREEMPTION
	definition instead. */

	/* Setup the hardware to generate the tick. */
	prvSetupTimerInterrupt();

	/* Restore the context of the first task that is going to run. */
	portRESTORE_CONTEXT();

	/* Simulate a function call end as generated by the compiler.  We will now
	jump to the start of the task the context of which we have just restored. */
	asm volatile ( "ret" );

	/* Should not get here. */
	return pdTRUE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* It is unlikely that the AVR port will get stopped.  If required simply
	disable the tick interrupt here. */
}
/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
void vPortYield( void ) __attribute__ ( ( naked ) );
void vPortYield( void )
{
	portSAVE_CONTEXT();
	vTaskSwitchContext();
	portRESTORE_CONTEXT();

	asm volatile ( "ret" );
}
/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick.  This must be identical to 
 * vPortYield() from the call to vTaskSwitchContext() onwards.  The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
void vPortYieldFromTick( void ) __attribute__ ( ( naked ) );
void vPortYieldFromTick( void )
{
	portSAVE_CONTEXT();
	vTaskIncrementTick();
	vTaskSwitchContext();
	portRESTORE_CONTEXT();

	asm volatile ( "ret" );
}
/*-----------------------------------------------------------*/

void vPortSystemClockEnable( portBASE_TYPE Enable )
{
	portCHAR uc;

#ifndef USE_RTC_TIMER
	uc = TIMSK;
	if ( Enable )
	{
		uc |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
	}
	else
	{
		uc &= ~portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
	}
	TIMSK = uc;
#else

#ifdef __ATmegaxx0__
	uc = TIMSK2;
	if ( Enable )
	{
		uc |= (1 << OCIE2A);
	}
	else
	{
		uc &= ~(1 << OCIE2A);
	}
	TIMSK2 = uc;
#else
	uc = TIMSK;
	if ( Enable )
	{
		uc |= (1 << OCIE0);
	}
	else
	{
		uc &= ~(1 << OCIE0);
	}
	TIMSK = uc;
#endif // __ATmegaxx0__

#endif // USE_RTC_TIMER
}

/*-----------------------------------------------------------*/

#ifndef USE_RTC_TIMER
/*
 * Setup timer 1 compare match A to generate a tick interrupt.
 */
static void prvSetupTimerInterrupt( void )
{
unsigned portLONG ulCompareMatch;
unsigned portCHAR ucHighByte, ucLowByte;

	/* Set up system to enable yield on clock tick */
	portEnableYieldFromTick = pdTRUE;

	/* Using 16bit timer 1 to generate the tick.  Correct fuses must be
	selected for the configCPU_CLOCK_HZ clock. */

	ulCompareMatch = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

	/* We only have 16 bits so have to scale to get our required tick rate. */
	ulCompareMatch /= portCLOCK_PRESCALER;

	/* Adjust for correct value. */
	ulCompareMatch -= ( unsigned portLONG ) 1;

	/* Setup compare match value for compare match A.  Interrupts are disabled 
	before this is called so we need not worry here. */
	ucLowByte = ( unsigned portCHAR ) ( ulCompareMatch & ( unsigned portLONG ) 0xff );
	ulCompareMatch >>= 8;
	ucHighByte = ( unsigned portCHAR ) ( ulCompareMatch & ( unsigned portLONG ) 0xff );
	OCR1AH = ucHighByte;
	OCR1AL = ucLowByte;

	/* Setup clock source and compare match behaviour. */
	ucLowByte = portCLEAR_COUNTER_ON_MATCH | portPRESCALE_64;
	TCCR1B = ucLowByte;

	/* Enable the interrupt - this is okay as interrupt are currently globally
	disabled. */
	ucLowByte = TIMSK;
	ucLowByte |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
	TIMSK = ucLowByte;
}

#else // use RTC timer
/*
 * Setup Crystal-controlled timer compare match A to generate a tick interrupt.
 */
static void prvSetupTimerInterrupt( void )
{
	unsigned portSHORT usCompareMatch;
	unsigned portCHAR i;

	/* Using 8bit timer 0 (or 2) to generate the tick.  A 32.768 KHz crystal
	 * must be attached to the appropriate pins.  We then adjust the number
	 * to a power of two so we can get EXACT seconds for the Real Time clock.
	 */

	usCompareMatch = ((unsigned long) 32768) / configTICK_RATE_HZ;

	if ( usCompareMatch > 192 )
	{
		usCompareMatch = 256;
	}
	else
	{
		for (i = 7; i >= 1; i--)
		{
			if ( usCompareMatch & ((unsigned short)1 << i) )
			{
				/* found the power - now let's see if we round up or down */
				if ( usCompareMatch & ((unsigned short)1 << (i-1)) )
				{
					usCompareMatch = ((unsigned short)1 << (i+1));
				}
				else
				{
					usCompareMatch = ((unsigned short)1 << i);
				}
				break;
			}
		}
	}

	portTicksPerSecond = ((unsigned long) 32768) / usCompareMatch;

	/* Adjust for correct value. */
	usCompareMatch -= ( unsigned portLONG ) 1;

#ifdef __ATmegaxx0__		
	/* ATmega640/1280/2560 uses Timer2 for the real time clock */
	TIMSK2 = 0;									// disable timer interrupts
	TIFR2 = 0x7;								// clear all pending interrupts

	ASSR = (1 << AS2);							// set timer to run from xtal
	TCNT2 = 0x00;								// clear the counter
	TCCR2A = (1 << WGM21);						// mode CTC (clear on counter match)
	TCCR2B = (1 << CS20);						// div. sys clock by 1
	OCR2A = usCompareMatch;

	while ( ASSR & 0x07 );						// wait for timer to be ready

	TIMSK2 |= (1 << OCIE2A);					// interrupt on timer2 compare match

#else					
	/* ATmega128 et. al. uses Timer0 for the real time clock */
	TIMSK &= ~( (1 << TOIE0) | (1 << OCIE0) );	// disable timer0 interrupts

	ASSR = (1 << AS0);							// set timer to run from xtal
	TCNT0 = 0x00;								// clear the counter
	TCCR0 = ( (1 << WGM01) | (1 << CS00);		// div. sys clock by 1
	OCR0 = usCompareMatch;

	while ( ASSR & 0x07 );						// wait for timer to be ready

	TIMSK |= (1 << OCIE0);						// interrupt on timer0 compare match

#endif
}

#endif // USE_RTC_TIMER

/*-----------------------------------------------------------*/

#if configUSE_PREEMPTION == 1

	/*
	 * Tick ISR for preemptive scheduler.  We can use a naked attribute as
	 * the context is saved at the start of vPortYieldFromTick().  The tick
	 * count is incremented after the context is saved.
	 */


	ISR( TIMER_COMPARE_SIG, ISR_NAKED ISR_SECTION )
	{
		vPortYieldFromTick();
		asm volatile ( "reti" );
	}
#else

	/*
	 * Tick ISR for the cooperative scheduler.  All this does is increment the
	 * tick count.  We don't need to switch context, this can only be done by
	 * manual calls to taskYIELD();
	 */
	ISR( TIMER_COMPARE_SIG, ISR_NAKED ISR_SECTION )
	{
		vTaskIncrementTick();
		asm volatile ( "reti" );
	}
#endif


