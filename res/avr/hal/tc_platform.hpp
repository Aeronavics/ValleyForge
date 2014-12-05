/********************************************************************************************************************************
 *
 *  FILE:               tc_platform.hpp
 *
 *  SUB-SYSTEM:         avr_tc_test
 *
 *  COMPONENT:          2tcTest
 *
 *  TARGET:             ATmega64C1
 *
 *  PLATFORM:           BareMetal
 *
 *  AUTHOR:             Kevin
 *
 *  DATE CREATED:       27-11-2014
 *
 *	This is the header file which matches tc_platform.cpp...
 * 
 ********************************************************************************************************************************/

// Only include this header file once.
#ifndef __TC_PLATFORM_H__
#define __TC_PLATFORM_H__

// INCLUDE REQUIRED HEADER FILES FOR INTERFACE.

// Include the required IO header file.
#include <<<TC_INSERTS_IO_FILE_NAME_HERE>>>

// Include the STDINT fixed width types.
#include <<<TC_INSERTS_STDINT_FILE_NAME_HERE>>>

#include <stdint.h>

// DEFINE PUBLIC MACROS.

// Generic AVR register addresses

// TIMSK addresses
#	define TIMSK5_ADDRESS		0x73
#	define TIMSK4_ADDRESS		0x72
#	define TIMSK3_ADDRESS		0x71
#	define TIMSK2_ADDRESS		0x70
#	define TIMSK1_ADDRESS		0x6F
#	define TIMSK0_ADDRESS		0x6E

// Timer/Counter 0.
#	define OCR0B_ADDRESS		0x48
#	define OCR0A_ADDRESS		0x47
#	define TCNT0_ADDRESS		0x46
#	define TCCR0B_ADDRESS		0x45
#	define TCCR0A_ADDRESS		0x44

// Timer/Counter 1.
#	define OCR1C_ADDRESS		0x8C
#	define OCR1B_ADDRESS		0x8A
#	define OCR1A_ADDRESS		0x88
#	define ICR1_ADDRESS		0x86
#	define TCNT1_ADDRESS		0x84
#	define TCCR1B_ADDRESS		0x81
#	define TCCR1A_ADDRESS		0x80

#if defined (__AVR_ATmega2560__) || defined (__AVR_AT90CAN128__)
// Timer/Counter 2.
#	define OCR2B_ADDRESS		0xB4
#	define OCR2A_ADDRESS		0xB3
#	define TCNT2_ADDRESS		0xB2
#	define TCCR2B_ADDRESS		0xB1
#	define TCCR2A_ADDRESS		0xB0

// Timer/Counter 3.
#	define OCR3C_ADDRESS		0x9C
#	define OCR3B_ADDRESS		0x9A
#	define OCR3A_ADDRESS		0x98
#	define ICR3_ADDRESS		0x96
#	define TCNT3_ADDRESS		0x94
#	define TCCR3B_ADDRESS		0x91
#	define TCCR3A_ADDRESS		0x90
#endif

#ifdef __AVR_ATmega2560__
// Timer/Counter 4.
#	define OCR4C_ADDRESS		0xAC
#	define OCR4B_ADDRESS		0xAA
#	define OCR4A_ADDRESS		0xA8
#	define ICR4_ADDRESS		0xA6
#	define TCNT4_ADDRESS		0xA4
#	define TCCR4B_ADDRESS		0xA1
#	define TCCR4A_ADDRESS		0xA0

// Timer/Counter 5.
#	define OCR5C_ADDRESS		0x12C
#	define OCR5B_ADDRESS		0x12A
#	define OCR5A_ADDRESS		0x128
#	define ICR5_ADDRESS		0x126
#	define TCNT5_ADDRESS		0x124
#	define TCCR5B_ADDRESS		0x121
#	define TCCR5A_ADDRESS		0x120
#endif

// TIMSK generic bits.
#	define ICIE_BIT			5
#	define OCIEC_BIT			3
#	define OCIEB_BIT			2
#	define OCIEA_BIT			1
#	define TOIE_BIT			0

// TCCRC generic bits
#	define FOCA_BIT			7
#	define FOCB_BIT			6
#	define FOCC_BIT			5

// TCCRB generic bits
#	define ICNC_BIT			7
#	define ICES_BIT			6
#	define WGM3_BIT			4			
#	define WGM2_BIT			3	
#	define CS2_BIT			2				
#	define CS1_BIT			1
#	define CS0_BIT			0
	
// TCCRA generic bits. TCCRA for 8bit TCs in AT90CAN128 are different
#	define COMA1_BIT		7
#	define COMA0_BIT		6
#	define COMB1_BIT		5
#	define COMB0_BIT		4
#	define COMC1_BIT		3
#	define COMC0_BIT		2
#	define WGM1_BIT		1
#	define WGM0_BIT		0

#ifdef __AVR_AT90CAN128__
// TCCRA for 8bit timer/counters in AT90CAN128
#	define WGM0_8TC_BIT		6
#	define COMA1_8TC_BIT		5
#	define COMA0_8TC_BIT		4
#	define WGM1_8TC_BIT		3
#endif

#	define COM_BIT_OFFSET		2
#	define MAX_TIMER_PINS		4

#ifdef (__AVR_ATmega2560__)
// Timer/Counter Peripheral Pin Addresses and Associated Constants.
#	define TC0_OC_A_PORT		PORT_B
#	define TC0_OC_A_PIN		PIN_7
#	define TC0_OC_B_PORT		PORT_G
#	define TC0_OC_B_PIN		PIN_5

#	define TC1_OC_A_PORT		PORT_B
#	define TC1_OC_A_PIN		PIN_5
#	define TC1_OC_B_PORT		PORT_B
#	define TC1_OC_B_PIN		PIN_6
#	define TC1_OC_C_PORT		PORT_B
#	define TC1_OC_C_PIN		PIN_7
#	define TC1_IC_A_PORT		PORT_D
#	define TC1_IC_A_PIN		PIN_4

#	define TC2_OC_A_PORT		PORT_B
#	define TC2_OC_A_PIN		PIN_4
#	define TC2_OC_B_PORT		PORT_H
#	define TC2_OC_B_PIN		PIN_6

#	define TC3_OC_A_PORT		PORT_E
#	define TC3_OC_A_PIN		PIN_3
#	define TC3_OC_B_PORT		PORT_E
#	define TC3_OC_B_PIN		PIN_4
#	define TC3_OC_C_PORT		PORT_E
#	define TC3_OC_C_PIN		PIN_5
#	define TC3_IC_A_PORT		PORT_E
#	define TC3_IC_A_PIN		PIN_7

#	define TC4_OC_A_PORT		PORT_H
#	define TC4_OC_A_PIN		PIN_3
#	define TC4_OC_B_PORT		PORT_H
#	define TC4_OC_B_PIN		PIN_4
#	define TC4_OC_C_PORT		PORT_H
#	define TC4_OC_C_PIN		PIN_5
#	define TC4_IC_A_PORT		PORT_L
#	define TC4_IC_A_PIN		PIN_0

#	define TC5_OC_A_PORT		PORT_L
#	define TC5_OC_A_PIN		PIN_3
#	define TC5_OC_B_PORT		PORT_L
#	define TC5_OC_B_PIN		PIN_4
#	define TC5_OC_C_PORT		PORT_L
#	define TC5_OC_C_PIN		PIN_5
#	define TC5_IC_A_PORT		PORT_L
#	define TC5_IC_A_PIN		PIN_1

#	define IC_CHANNEL_OFFSET		3
#	define TC_OC_CHANNEL_A		0 			// I don't know why these are enumerated
#	define TC_OC_CHANNEL_B		1
#	define TC_OC_CHANNEL_C		2
#	define TC_IC_CHANNEL_A		3

// Interrupt Pointer Array values and offsets.
#	define NUM_TIMER0_INTERRUPTS	3
#	define TIMER0_OFFSET		0
#	define NUM_TIMER1_INTERRUPTS	5
#	define TIMER1_OFFSET		3
#	define NUM_TIMER2_INTERRUPTS	3
#	define TIMER2_OFFSET		8
#	define NUM_TIMER3_INTERRUPTS	5
#	define TIMER3_OFFSET		11
#	define NUM_TIMER4_INTERRUPTS	5
#	define TIMER4_OFFSET		16
#	define NUM_TIMER5_INTERRUPTS	5
#	define TIMER5_OFFSET		21
#	define NUM_TIMER_INTERRUPTS	(NUM_TIMER0_INTERRUPTS + NUM_TIMER1_INTERRUPTS + NUM_TIMER2_INTERRUPTS + NUM_TIMER3_INTERRUPTS + NUM_TIMER4_INTERRUPTS + NUM_TIMER5_INTERRUPTS)

// Definitions required for Port Directionality Control.
#	define PORT_REGISTER_MULTIPLIER		0x03
#	define LOWER_REGISTER_PORT_OFFSET	0x01
#	define HIGHER_REGISTER_PORT_OFFSET	0xEC
#endif

#if defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega64C1__)
	
// Timer/Counter Peripheral Pin Addresses and Associated Constants.
/**
*	Port E of the ATmega64 series is not used. Avionics board connects the pins
*	to an oscillator, effectively making it inaccessible.
**/
#	define TC0_OC_A_PORT		PORT_D
#	define TC0_OC_A_PIN		PIN_3
// #	define TC0_OC_B_PORT		PORT_E
// #	define TC0_OC_B_PIN		PIN_1

#	define TC1_OC_A_PORT		PORT_D
#	define TC1_OC_A_PIN		PIN_2
#	define TC1_OC_B_PORT		PORT_C
#	define TC1_OC_B_PIN		PIN_1
#	define TC1_IC_A_PORT		PORT_D
#	define TC1_IC_A_PIN 	PIN_4
#	define TC1_IC_B_PORT		PORT_C
#	define TC1_IC_B_PIN		PIN_3

#	define IC_CHANNEL_OFFSET		2	
#	define TC_OC_CHANNEL_A		0
#	define TC_OC_CHANNEL_B		1
#	define TC_IC_CHANNEL_A		2
#	define TC_IC_CHANNEL_B		3

// Interrupt Pointer Array values and offsets.
#	define NUM_TIMER0_INTERRUPTS	2
#	define TIMER0_OFFSET		0
#	define NUM_TIMER1_INTERRUPTS	4
#	define TIMER1_OFFSET		2
#	define NUM_TIMER_INTERRUPTS	(NUM_TIMER0_INTERRUPTS + NUM_TIMER1_INTERRUPTS )

// Definitions required for Port Directionality Control.
// #	define PORT_REGISTER_MULTIPLIER		0x03		// What is this for?
// #	define LOWER_REGISTER_PORT_OFFSET	0x01		//
// #	define HIGHER_REGISTER_PORT_OFFSET	0xEC	//
	
#ifdef __AVR_AT90CAN128__

// Timer/Counter Peripheral Pin Addresses and Associated Constants.
#	define TC0_OC_A_PORT		PORT_B
#	define TC0_OC_A_PIN		PIN_7

#	define TC1_OC_A_PORT		PORT_B
#	define TC1_OC_A_PIN		PIN_5
#	define TC1_OC_B_PORT		PORT_B
#	define TC1_OC_B_PIN		PIN_6
#	define TC1_OC_C_PORT		PORT_B
#	define TC1_OC_C_PIN		PIN_7
#	define TC1_IC_A_PORT		PORT_D
#	define TC1_IC_A_PIN		PIN_4

#	define TC2_OC_B_PORT		PORT_B
#	define TC2_OC_B_PIN		PIN_4

#	define TC3_OC_A_PORT		PORT_E
#	define TC3_OC_A_PIN		PIN_3
#	define TC3_OC_B_PORT		PORT_E
#	define TC3_OC_B_PIN		PIN_4
#	define TC3_OC_C_PORT		PORT_E
#	define TC3_OC_C_PIN		PIN_5
#	define TC3_IC_A_PORT		PORT_E
#	define TC3_IC_A_PIN		PIN_7

#	define IC_CHANNEL_OFFSET		2
#	define TC_OC_CHANNEL_A		0
#	define TC_OC_CHANNEL_B		1
#	define TC_OC_CHANNEL_C		2
#	define TC_IC_CHANNEL_A		3

// Interrupt Pointer Array values and offsets.
#	define NUM_TIMER0_INTERRUPTS	1
#	define TIMER0_OFFSET		0
#	define NUM_TIMER1_INTERRUPTS	4
#	define TIMER1_OFFSET		1
#	define NUM_TIMER2_INTERRUPTS	2
#	define TIMER2_OFFSET		5
#	define NUM_TIMER2_INTERRUPTS	4
#	define TIMER2_OFFSET		7
#	define NUM_TIMER_INTERRUPTS	(NUM_TIMER0_INTERRUPTS + NUM_TIMER1_INTERRUPTS + NUM_TIMER2_INTERRUPTS + NUM_TIMER3_INTERRUPTS)

#else
	#error "No support for this target."
#endif

#endif // __TC_PLATFORM_H__

// ALL DONE.
