/********************************************************************************************************************************
 *
 *  FILE: 		target_config.h
 *
 *  SUB-SYSTEM:		hal
 *
 *  COMPONENT:		hal
 *
 *  AUTHOR: 		Zac Frank
 *
 *  DATE CREATED:	15-12-2011
 *
 *	This contains device specific definitions for avr.
 * 
 ********************************************************************************************************************************/

/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file		target_config.h
 * Provides definitions for to be used in implementations.
 * 
 * @todo This file should really be split up and put into the implementation folders, not the general ones.
 * 
 * @author 		Zac Frank
 *
 * @date		15-12-2011
 *  
 * @section Licence
 * 
 * LICENCE GOES HERE
 * 
 * @brief
 * This contains device specific definitions for avr. Information such as timer size, interrupt
 * specifications and so on are defined here.
 */

// Only include this header file once.
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

enum int_bank_t {PCINT_0, PCINT_1, PCINT_2, PCINT_3, PCINT_4, PCINT_NONE, EINT_0, EINT_1, EINT_2, EINT_3, EINT_4, EINT_5, EINT_6, EINT_7};

#if defined (__AVR_ATmega2560__)
#	define NUM_PORTS		12
#	define NUM_PINS			8

#	define T0_SIZE			8
#	define T0_PWM			1
#	define T0_OC			2
#	define T0_IC			0
#	define T0_AS			0
#	define T0_REV			0

#	define T1_SIZE			16
#	define T1_PWM			1
#	define T1_OC			3
#	define T1_IC			1
#	define T1_AS			0
#	define T1_REV			0

#	define T2_SIZE			8
#	define T2_PWM			1
#	define T2_OC			2
#	define T2_IC			0
#	define T2_AS			1
#	define T2_REV			0

#	define T3_SIZE			16
#	define T3_PWM			1
#	define T3_OC			3
#	define T3_IC			1
#	define T3_AS			0
#	define T3_REV			0

#	define T4_SIZE			16
#	define T4_PWM			1
#	define T4_OC			3
#	define T4_IC			1
#	define T4_AS			0
#	define T4_REV			0

#	define T5_SIZE			16
#	define T5_PWM			1
#	define T5_OC			3
#	define T5_IC			1
#	define T5_AS			0
#	define T5_REV			0


#	define NUM_BANKS		3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
#	define EXT_INT_SIZE		8
#	define INT_DIFF_OFFSET		3

#	define EXTERNAL_NUM_INTERRUPTS	NUM_BANKS + EXT_INT_SIZE
							      
#	define PC_INT_SIZE		24

#	define NUM_8_BIT_TIMERS		2
#	define NUM_16_BIT_TIMERS	4
# 	define NUM_TIMERS		NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS


#	define INT_BIT			7

// This shows which pins have External Interrupts, and which have pin change interrupts assignable. The ATmega2560 has only 
// 8 External Pin interrupts, and a range of Pin Change interrupts.
static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =  {{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},	// A
							{PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0},				// B
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// C
							{EINT_0, EINT_1, EINT_2, EINT_3, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  			// D
							{PCINT_2, PCINT_NONE, PCINT_NONE, PCINT_NONE, EINT_4, EINT_5, EINT_6, EINT_7},				// E
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// F
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// G
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// H
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE},  	// I
							{PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_2, PCINT_NONE},		 		// J
							{PCINT_3, PCINT_3, PCINT_3, PCINT_3, PCINT_3, PCINT_3, PCINT_3, PCINT_3},				// K
							{PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE, PCINT_NONE}};	// L
						     
						         

#elif defined (__AVR_ATmega64M1__)
#	define NUM_PORTS		4
#	define NUM_PINS			8

#	define T0_SIZE			8
#	define T0_PWM			1
#	define T0_OC			2
#	define T0_IC			0
#	define T0_AS			0
#	define T0_REV			0

#	define T1_SIZE			16
#	define T1_PWM			1
#	define T1_OC			2
#	define T1_IC			1
#	define T1_AS			0
#	define T1_REV			0

#	define T2_SIZE			0
#	define T3_SIZE			0
#	define T4_SIZE			0
#	define T5_SIZE			0
						// NOTE THESE NUMBERS (below) ARE WRONG, THEY ARE JUST COPY PASTED SO IT WILL COMPILE. IF TO BE USED THEY WILL HAVE TO BE FILLED IN!
#	define NUM_BANKS		3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
#	define EXT_INT_SIZE		8
#	define INT_DIFF_OFFSET		3

#	define EXTERNAL_NUM_INTERRUPTS	NUM_BANKS + EXT_INT_SIZE
							      
#	define PC_INT_SIZE		24

#	define NUM_8_BIT_TIMERS		1
#	define NUM_16_BIT_TIMERS	1
# 	define NUM_TIMERS		NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS

#	define INT_BIT			7

#elif defined (__AVR_AT90CAN128__)
#	define NUM_PORTS		6
#	define NUM_PINS			8
	
#	define T0_SIZE			8
#	define T0_PWM			1
#	define T0_OC			2
#	define T0_IC			0
#	define T0_AS			0
#	define T0_REV			0

#	define T1_SIZE			16
#	define T1_PWM			1
#	define T1_OC			3
#	define T1_IC			1
#	define T1_AS			0
#	define T1_REV			0

#	define T2_SIZE			8
#	define T2_PWM			1
#	define T2_OC			2
#	define T2_IC			0
#	define T2_AS			0
#	define T2_REV			0

#	define T3_SIZE			16
#	define T3_PWM			1
#	define T3_OC			3
#	define T3_IC			1
#	define T3_AS			0
#	define T3_REV			0

#	define T4_SIZE			0
#	define T5_SIZE			0
						// NOTE THESE NUMBERS (below) ARE WRONG, THEY ARE JUST COPY PASTED SO IT WILL COMPILE. IF TO BE USED THEY WILL HAVE TO BE FILLED IN!
#	define NUM_BANKS		3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
#	define EXT_INT_SIZE		8
#	define INT_DIFF_OFFSET		3

#	define EXTERNAL_NUM_INTERRUPTS	NUM_BANKS + EXT_INT_SIZE
							      
#	define PC_INT_SIZE		24

#	define NUM_8_BIT_TIMERS		2
#	define NUM_16_BIT_TIMERS	1
# 	define NUM_TIMERS		NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS

#	define INT_BIT			7

#elif defined (__AT32UC3C0512C__)
#	define NUM_PORTS		4
#	define NUM_PINS			32
	
#	define T0_SIZE			16
#	define T0_PWM			1
#	define T0_OC			2
#	define T0_IC			2
#	define T0_AS			0
#	define T0_REV			1

#	define T1_SIZE			16
#	define T1_PWM			1
#	define T1_OC			2
#	define T1_IC			2
#	define T1_AS			0
#	define T1_REV			1

#	define T2_SIZE			16
#	define T2_PWM			1
#	define T2_OC			2
#	define T2_IC			2
#	define T2_AS			0
#	define T2_REV			1

#	define T3_SIZE			32
#	define T3_PWM			1
#	define T3_OC			2
#	define T3_IC			0
#	define T3_AS			1
#	define T3_REV			0

#	define T4_SIZE			0
#	define T5_SIZE			0


	
#endif

#define TOTAL_PINS			NUM_PORTS * PINS_PER_PORT

#endif /*__TARGET_CONFIG_H__*/