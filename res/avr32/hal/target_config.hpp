/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 * 
 * @file		target_config.h
 * Provides definitions for to be used in implementations.
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
 * This contains device specific definitions for AVR32. Information such as timer size, interrupt
 * specifications and so on are defined here.
 */

// Only include this header file once.
#ifndef __TARGET_CONFIG_H__
#define __TARGET_CONFIG_H__

// INCLUDE REQUIRED HEADER FILES.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

#if defined (__AT32UC3C0512C__)
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