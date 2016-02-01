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
#define SERVO_TC_PRE TC_PRE_8 // This devisor must be set such that the timer ticks period is ~500ns
#define SERVO_PRE_DEVISOR 8
#define SERVO_OC_MODE TC_OC_NONE
#define SERVO_SET TC_OC_CHANNEL_MODE_3
#define SERVO_CLEAR TC_OC_CHANNEL_MODE_2
#define SERVO_IC_RISING TC_IC_MODE_2
#define SERVO_IC_FALLING TC_IC_MODE_1

#define SERVO_TIMER_MAX_INTERRUPTS 4
#define SERVO_TIMER_MAX_CHANNELS 3

enum Servo_state {SERVO_LOW, SERVO_HIGH};
enum Servo_int_type {SERVO_OC_A, SERVO_OC_B, SERVO_IC_A, SERVO_OVF};
static const uint8_t Timer_size[] = {8, 16, 8};

/* ADC */

enum Adc_clock_src_pre {ADC_SRC_INT_PRE_2, ADC_SRC_INT_PRE_4, ADC_SRC_INT_PRE_8, ADC_SRC_INT_PRE_16, ADC_SRC_INT_PRE_32, ADC_SRC_INT_PRE_64, ADC_SRC_INT_PRE_128};
enum Adc_speed_mode {ADC_SPEED_MODE_NORMAL};
enum Adc_auxiliary_supply {ADC_AUXILIARY_SUPPLY_NONE};
enum Adc_multi_adc_mode {ADC_MULTI_ADC_MODE_NONE};
enum Adc_multi_adc_dma_mode {ADC_MULTI_ADC_DMA_MODE_NONE};
enum Adc_unit {ADC_UNIT_0};
enum Adc_conv_channel {ADC_CONV_CHANNEL_REGULAR};
enum Adc_input_channel {ADC_INPUT_CHANNEL_0 = 0x00, ADC_INPUT_CHANNEL_1 = 0x01, ADC_INPUT_CHANNEL_2 = 0x02, ADC_INPUT_CHANNEL_3 = 0x03, ADC_INPUT_CHANNEL_4 = 0x04, ADC_INPUT_CHANNEL_5 = 0x05, ADC_INPUT_CHANNEL_6 = 0x06, ADC_INPUT_CHANNEL_7 = 0x07, ADC_INPUT_CHANNEL_8 = 0x08, ADC_INPUT_CHANNEL_1_1V = 0x0E, ADC_INPUT_CHANNEL_0V = 0x0F};
enum Adc_input_mode {ADC_INPUT_MODE_NONE};
enum Adc_conversion_status {ADC_CONVERSION_COMPLETE, ADC_CONVERSION_NOT_COMPLETE};
enum Adc_data_alignment {ADC_DATA_RIGHT_ALIGNED, ADC_DATA_LEFT_ALIGNED};
enum Adc_resolution {ADC_RESOLUTION_NONE};
enum Adc_operating_mode {ADC_OPERATING_MODE_MANUAL, ADC_OPERATING_MODE_TRIGGERED};
enum Adc_sampling_time {ADC_SAMPLING_TIME_NONE};
enum Adc_reference_source {ADC_REFERENCE_SOURCE_AREF, ADC_REFERENCE_SOURCE_AVCC_CAP, ADC_REFERENCE_SOURCE_1_1V_CAP};
enum Adc_interrupt_source {ADC_INTERRUPT_SOURCE_CONVERSION_COMPLETE};
enum Adc_trigger_source  {ADC_TRIGGER_SOURCE_FR = 0x00, ADC_TRIGGER_SOURCE_ACOMP = 0x01, ADC_TRIGGER_SOURCE_EXTI0 = 0x02, ADC_TRIGGER_SOURCE_TC0OCA = 0x03, ADC_TRIGGER_SOURCE_TC0OVF = 0x04, ADC_TRIGGER_SOURCE_TC1OCB = 0x05, ADC_TRIGGER_SOURCE_TC1OVF = 0x06, ADC_TRIGGER_SOURCE_TC1ICA = 0x07};
enum Adc_trigger_edge {ADC_TRIGGER_EDGE_RISING};
enum Adc_watchdog {ADC_WATCHDOG_NONE};
enum Adc_watchdog_mode {ADC_WATCHDOG_MODE_NONE};
enum Adc_watchdog_channel {ADC_WATCHDOG_CHANNEL_NONE};
enum Adc_dma_mode {ADC_DMA_MODE_NONE};
enum Adc_oversampling_mode {ADC_OVERSAMPLING_MODE_NONE};
enum Adc_oversampling_ratio {ADC_OVERSAMPLING_RATIO_NONE};
enum Adc_oversampling_shift {ADC_OVERSAMPLING_SHIFT_NONE};

/* I2C */

#define I2C_SDA_PORT    PORT_C
#define I2C_SDA_PIN     PIN_4
#define I2C_SCL_PORT    PORT_C
#define I2C_SCL_PIN     PIN_5

enum I2c_number{I2C_0};

// ALL DONE.
