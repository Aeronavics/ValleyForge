/**
 * \file
 *
 * \brief AVR XMEGA 32-bit Real Time Counter driver definitions
 *
 * Copyright (C) 2010 Atmel Corporation. All rights reserved.
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
#ifndef DRIVERS_RTC32_RTC32_H
#define DRIVERS_RTC32_RTC32_H

#include <compiler.h>
#include <conf_rtc32.h>

/**
 * \defgroup rtc32_group 32-bit Real Time Counter (RTC32)
 *
 * This is a driver implementation for the XMEGA RTC32.
 *
 * This driver can be used to keep track of time; setting alarms, with or
 * without function callbacks; initializing and checking the battery backup
 * system.
 *
 * \section rtc32_min_alarm_time Minimum allowed alarm time
 *
 * Due to the RTC32 clock synchronization, there is a minimum alarm time that
 * will generate a interrupt. This minimum time is 2 RTC32 clock cycles.
 *
 * Also, if a new RTC32 clock cycle is imminent at the time of setting the
 * alarm, there is a risk that it will be missed even with the value 2. If there
 * is a risk that this may occur, it is recommended to use a minimum alarm time
 * of 3.
 *
 * @{
 */

/**
 * \def CONFIG_RTC32_COMPARE_INT_LEVEL
 * \brief Configuration symbol for interrupt level to use on alarm
 *
 * Define this in \ref conf_rtc32.h as the desired interrupt level, or leave it
 * undefined to use the default.
 */
#ifdef __DOXYGEN__
# define CONFIG_RTC32_COMPARE_INT_LEVEL
#endif

/**
 * \def CONFIG_RTC32_CLOCK_1024HZ
 * \brief Configuration symbol for selecting 1024Hz clock instead of 1Hz
 *
 * Define this in \ref conf_rtc32.h if 1024Hz clock is desired. Otherwise, leave
 * it undefined.
 */
#ifdef __DOXYGEN__
# define CONFIG_RTC32_CLOCK_1024HZ
#endif

//! \brief Battery backup system status codes
enum vbat_status_code {
/**
 * \brief Backup system is operating and no errors were detected.
 *
 * The backup system is configured and had no issues while main power was
 * lost. Hence, all data stored in the backup domain is valid.
 */
	VBAT_STATUS_OK,

/**
 *  \brief No power detected on VBAT.
 *
 * No power was detected on the VBAT pin and therefore all data within the
 * backup system is invalid.
 *
 * The voltage on the VBAT pin is only sampled after a POR of the device,
 * therefore it is not possible to detect any voltage loss on the VBAT pin
 * during normal operation of the device.
 */
	VBAT_STATUS_NO_POWER,

/**
 *  \brief The backup system must be initialized.
 *
 * A POR was detected on VBAT input, indicating that a supply was connected to
 * the VBAT pin. Since this is also the first start-up of the device, it is
 * necessary to initialize the RTC32.
 */
	VBAT_STATUS_INIT,

/**
 *  \brief A POR was detected on the VBAT input.
 *
 * POR detection also works while the VBAT system is powered from main power,
 * but the detection flag is only latched after a POR of the main system.
 * A POR can happen when the power is lost and restored again on the VBAT pin
 * while main power was also not present, or even when main power was present,
 * but in this case the flag will only be latched after the next POR of the main
 * system.
 * If a POR is detected on VBAT, it should always be treated as if the backup
 * system is in an unknown state, i.e., that all data is invalid.
 */
	VBAT_STATUS_BBPOR,

/**
 * \brief A brown-out was detected on the VBAT input.
 *
 * The backup system is in an unkown state and therefore the time in the RTC32
 * is invalid. This can happen when the voltage on VBAT drops below the
 * brown-out detection level while main power is absent.
 */
	VBAT_STATUS_BBBOD,

/**
 * \brief A failure was detected on the oscillator.
 *
 * The oscillator stopped for at least TBD period of time and because of that
 * we can not rely on the RTC time any more.
 *
 * \todo Determine minimum period for detection of oscillator outage.
 */
	VBAT_STATUS_XOSCFAIL,

};

enum vbat_status_code rtc32_vbat_system_check(bool first_time_init);

/**
 * \brief Callback definition for alarm callback
 *
 * \param time The time of the alarm
 */
typedef void (*rtc32_callback_t)(uint32_t time);

void rtc32_set_callback(rtc32_callback_t callback);
void rtc32_set_time(uint32_t time);
uint32_t rtc32_get_time(void);
void rtc32_set_alarm(uint32_t time);
bool rtc32_alarm_has_triggered(void);

/**
 * \brief Set alarm relative to current time
 *
 * \param offset Offset to current time. This is minimum value, so the alarm
 * might happen at up to one time unit later. See also \ref
 * rtc32_min_alarm_time
 */
static inline void rtc32_set_alarm_relative(uint32_t offset)
{
	Assert(offset >= 2);

	rtc32_set_alarm(rtc32_get_time() + offset);
}

void rtc32_init(void);

//! @}

#endif /* DRIVERS_RTC32_RTC32_H */
