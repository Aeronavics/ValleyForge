// Copyright (C) 2015  Aeronavics Ltd
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

/**
 *
 * @addtogroup		hal	Hardware Abstraction Library
 *
 * @file		atmega328.hpp
 * Provides target configuration for the ATmega328 family of chips
 *
 *
 * @author 		Sam Dirks
 *
 * @date		9/11/2015
 *
 * @section Licence
 *
 * Copyright (C) 2015  Aeronavics Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @brief
 * This contains device specific definitions for AVR architecture targets. Information such as timer size, interrupt specifications and so on are defined here.
 */

// Only include this header file once.
#pragma once


/* Watchdog timer. */

enum Watchdog_timeout
{
	WDTO_15MS,
	WDTO_30MS,
	WDTO_60MS,
	WDTO_120MS,
	WDTO_250MS,
	WDTO_500MS,
	WDTO_1S,
	WDTO_2S,
	WDTO_4S,
	WDTO_8S
};

/* GPIO */

#define INT_BIT				7	// The global interrupt enable bit in the status register

#define NUM_PORTS			3
#define NUM_PINS			8

#define NUM_BANKS			3	// Contains 3 PC_INT banks. Only one pin on each bank can be used at a time.
#define EXT_INT_SIZE		2	// Number of external interrupts

#define PORT_MULTIPLIER		3

#define EXTERNAL_NUM_INTERRUPTS	(NUM_BANKS + EXT_INT_SIZE + 1) 	// NOTE - fixed overflow bug	[14:13,4 Dec 2014]

#define PC_INT_SIZE		24

enum int_bank_t {PCINT_0, PCINT_1, PCINT_2, PCINT_NONE, EINT_0, EINT_1};
enum port_t {PORT_B=1, PORT_C, PORT_D};
enum pin_t {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};

// This shows which pins have External Interrupts, and which have pin change interrupts assignable. The ATmega2560 has only 8 External Pin interrupts, and a range of Pin Change interrupts.
static const int_bank_t PC_INT[NUM_PORTS][NUM_PINS] =
						   {{PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0, PCINT_0},	 // B
							{PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_1, PCINT_NONE}, // C
							{PCINT_2, PCINT_2, EINT_0, EINT_1, PCINT_2, PCINT_2, PCINT_2, PCINT_2}};	 // D

/* Timer/Counter */

#define T0_SIZE			8
#define T0_PWM			1
#define T0_OC			2
#define T0_IC			0
#define T0_AS			0
#define T0_REV			0

#define T1_SIZE			16
#define T1_PWM			1
#define T1_OC			2
#define T1_IC			1
#define T1_AS			0
#define T1_REV			0

#define T2_SIZE			8
#define T2_PWM			1
#define T2_OC			2
#define T2_IC			0
#define T2_AS			1
#define T2_REV			0

#define NUM_8_BIT_TIMERS	2
#define NUM_16_BIT_TIMERS	1
#define NUM_TIMERS		(NUM_8_BIT_TIMERS + NUM_16_BIT_TIMERS)

enum Tc_number {TC_0, TC_1, TC_2};
enum Tc_oc_channel {TC_OC_A, TC_OC_B};
enum Tc_oc_mode {TC_OC_NONE, TC_OC_MODE_1, TC_OC_MODE_2, TC_OC_MODE_3, TC_OC_MODE_4, TC_OC_MODE_5, TC_OC_MODE_6, TC_OC_MODE_7, TC_OC_MODE_8, TC_OC_MODE_9, TC_OC_MODE_10, TC_OC_MODE_11, TC_OC_MODE_12, TC_OC_MODE_13, TC_OC_MODE_14, TC_OC_MODE_15};
enum Tc_oc_channel_mode {TC_OC_CHANNEL_MODE_0, TC_OC_CHANNEL_MODE_1, TC_OC_CHANNEL_MODE_2, TC_OC_CHANNEL_MODE_3};
enum Tc_ic_channel {TC_IC_A};
enum Tc_ic_mode {TC_IC_NONE, TC_IC_MODE_1, TC_IC_MODE_2, TC_IC_MODE_3, TC_IC_MODE_4};
enum Tc_clk_src {TC_SRC_INT};
enum Tc_prescalar {TC_PRE_1, TC_PRE_8, TC_PRE_32, TC_PRE_64, TC_PRE_128, TC_PRE_256, TC_PRE_1024};

enum Tc_int_vect {TIMER0_OVF_int, TIMER0_COMPA_int, TIMER0_COMPB_int, TIMER1_OVF_int, TIMER1_COMPA_int, TIMER1_COMPB_int, TIMER1_CAPT_int, TIMER2_OVF_int, TIMER2_COMPA_int, TIMER2_COMPB_int};
// TODO - Realised this might be an issue if not all the timers are the same size.							

/* Servo */

#define SERVO_TC_CLK TC_SRC_INT
#define SERVO_TC_PRE TC_PRE_8
#define SERVO_PRE_DEVISOR 8
#define SERVO_OC_MODE TC_OC_NONE
#define SERVO_SET TC_OC_CHANNEL_MODE_3
#define SERVO_CLEAR TC_OC_CHANNEL_MODE_2

#define SERVO_TIMER_MAX_INTERRUPTS 4
#define SERVO_TIMER_MAX_CHANNELS 3

enum Servo_state {SERVO_LOW, SERVO_HIGH};
enum Servo_int_type {SERVO_OC_A, SERVO_OC_B, SERVO_IC_A, SERVO_OVF};
static const uint8_t Timer_size[] = {8, 16, 8};

// ALL DONE.
