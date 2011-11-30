/**
 * \file
 *
 * \brief Calendar.
 *
 * Copyright (c) 2011 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef _CALENDAR_H_INCLUDED_
#define _CALENDAR_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
/**
*
* \defgroup calendar_group Calendar service
 *
 * This is the common API for a calendar service.
 * It provides functionality to convert UNIX timestamps to dates and back. It
 * also provides functionality for calculating the difference between dates and
 * converting timestamps to dates with different time zones and back.
 * \note
 * This module is a pure software module, and does not interface
 * hardware calendar peripherals (e.g. the AST on UC3L)
 *
 *
 *
 * @{
 */

//! Calendar structure to hold a date
struct calendar_date {
	uint8_t second;        //!< 0-59
	uint8_t minute;        //!< 0-59
	uint8_t hour;          //!< 0-23
	uint8_t date;          //!< 0-30 \note First day of month is 0, not 1.
	uint8_t month;         //!< 0 January - 11 December
	uint16_t year;         //!< 1970-2105
	uint8_t dayofweek;     //!< 0 Sunday  - 6 Saturday
};

bool calendar_is_date_valid(struct calendar_date *date);

void calendar_timestamp_to_date(uint32_t timestamp, struct calendar_date
		*date_out);

void calendar_timestamp_to_date_tz(uint32_t timestamp, int8_t hour,
		uint8_t min, struct calendar_date *date_out);

uint32_t calendar_date_to_timestamp(struct calendar_date *date);

uint32_t calendar_date_to_timestamp_tz(struct calendar_date *date, int8_t hour,
		uint8_t min);

void calendar_time_between_dates(struct calendar_date *date_end,
		struct calendar_date *date_start, struct calendar_date *date_out);

void calendar_add_second_to_date(struct calendar_date *date);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _CALENDAR_H_INCLUDED_ */