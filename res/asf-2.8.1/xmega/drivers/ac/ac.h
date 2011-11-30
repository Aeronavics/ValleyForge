/**
 * \file
 *
 * \brief Analog comparator (AC) functions
 *
 * Copyright (C) 2010-2011 Atmel Corporation. All rights reserved.
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
#ifndef DRIVERS_AC_AC_H
#define DRIVERS_AC_AC_H

#include <stdint.h>

#include "compiler.h"
#include "parts.h"

#include "status_codes.h"
#include "pmic.h"

/**
 * \defgroup analog_comparator_group Analog Comparator (AC)
 *
 * This is a driver for configuring, enablig, disabling and use of the on-chip
 * analog comparator (AC).
 *
 * \section dependencies Dependencies
 *
 * The analog comparator depends on the following modules:
 *  - \ref pmic_group for interrupt functionality.
 *  - \ref sysclk_group for peripheral clock control.
 *  - \ref sleepmgr_group for setting available sleep mode.
 *
 * @{
 */

//! Analog comparator channel configuration struct
struct ac_config {
	//! Comparator control register
	uint8_t         acctrl;
	//! Comparator mux control register
	uint8_t         acmuxctrl;
	//! Control register B register
	uint8_t         ctrlb;
	//! Window mode control register
	uint8_t         winctrl;
};

//! Analog comparator status values
enum ac_status_t {
	//! Compare value is above window or reference value
	AC_STATUS_ABOVE     = AC_WSTATE_ABOVE_gc,
	//! Compare value is below window or reference value
	AC_STATUS_BELOW     = AC_WSTATE_BELOW_gc,
	//! Compare value is inside window
	AC_STATUS_INSIDE    = AC_WSTATE_INSIDE_gc,
};

//! Analog comparator modes
enum ac_mode_t {
	//! Analog comparator in normal single trigger value mode
	AC_MODE_SINGLE,
	//! Analog comparator in window trigger mode
	AC_MODE_WINDOW,
};

//! Analog comparator interrupt modes
enum ac_interrupt_mode_t {
	//! Interrupt on both edges
	AC_INT_MODE_BOTH_EDGES      = AC_INTMODE_BOTHEDGES_gc,
	//! Interrupt on falling edge
	AC_INT_MODE_FALLING_EDGE    = AC_INTMODE_FALLING_gc,
	//! Interrupt on rising edge
	AC_INT_MODE_RISING_EDGE     = AC_INTMODE_RISING_gc,
	//! Interrupt when above window
	AC_INT_MODE_ABOVE_WINDOW    = AC_WINTMODE_ABOVE_gc,
	//! Interrupt when inside window
	AC_INT_MODE_INSIDE_WINDOW   = AC_WINTMODE_INSIDE_gc,
	//! Interrupt when below window
	AC_INT_MODE_BELOW_WINDOW    = AC_WINTMODE_BELOW_gc,
	//! Interrupt when outside the window
	AC_INT_MODE_OUTSIDE_WINDOW  = AC_WINTMODE_OUTSIDE_gc,
};

/**
 * \brief Interrupt event callback function type
 *
 * The interrupt handler can be configured to do a function callback upon a
 * compare interrupt, the callback function must match the ac_callback_t type.
 *
 * Example:
 * \code
 * void my_ac_callback(AC_t *ac, uint8_t channel, enum ac_status_t status) {
 *      // Add desired functionality.
 * }
 * \endcode
 *
 * Then add this callback function to the analog comparator interrupt routine
 * by setting it in the driver.
 *
 * \code
 * ac_set_interrupt_callback(ACA, 0, my_ac_callback);
 * \endcode
 */
typedef void (*ac_callback_t) (AC_t *ac, uint8_t channel,
		enum ac_status_t status);

//! \name Management functions
//@{

void ac_write_config(AC_t *ac, uint8_t channel, struct ac_config *config);
void ac_read_config(AC_t *ac, uint8_t channel, struct ac_config *config);
enum ac_status_t ac_get_status(AC_t *ac, uint8_t channel);
void ac_enable(AC_t *ac, uint8_t channel);
void ac_disable(AC_t *ac, uint8_t channel);

//@}

//! \name Interrupt management functions
//@{

void ac_set_interrupt_callback(AC_t *ac, ac_callback_t callback);

/**
 * \brief Set analog comparator channel interrupt mode
 *
 * This function allows the caller to set which analog comparator channel
 * interrupt mode should cause an interrupt to trigger.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param mode Interrupt mode given by an \ref ac_interrupt_mode_t value
 */
static inline void ac_set_interrupt_mode(struct ac_config *config,
		enum ac_interrupt_mode_t mode)
{
	if (mode & AC_INTMODE_gm) {
		config->acctrl &= ~AC_INTMODE_gm;
		config->acctrl |= mode;
	} else {
		config->winctrl &= ~AC_WINTMODE_gm;
		config->winctrl |= mode;
	}
}

/**
 * \brief Set analog comparator channel interrupt level
 *
 * This function allows the caller to set the analog comparator channel
 * interrupt level. The interrupt levels are defined by the
 * \see enum pmic_level defines.
 *
 * \pre ac_set_mode() must be called before this function.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param level Analog comparator interrupt level
 */
static inline void ac_set_interrupt_level(struct ac_config *config,
		enum pmic_level level)
{
	if (config->winctrl & AC_INTLVL_gm) {
		config->winctrl &= ~AC_WINTLVL_gm;
		config->winctrl |= (level << AC_WINTLVL_gp);
	} else {
		config->acctrl &= ~AC_INTLVL_gm;
		config->acctrl |= (level << AC_INTLVL_gp);
	}
}

//@}

//! \name Configuration helper functions
//@{

/**
 * \brief Set analog comparator mode
 *
 * This function helps the caller setting the analog comparator mode for a
 * channel configuration. For AVR XMEGA this can be normal where it will
 * trigger at a defined value, or window mode, where two analog comparators are
 * combined to make two limits and three operating areas. The modes are defined
 * in the \ref ac_mode_t type.
 *
 * \note This function must be called before any other analog comparator
 * channel or window configuration. This is due to some of the set functions
 * depends on which mode the channels should be configured for.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param mode Analog comparator mode given by a \ref ac_mode_t value
 */
static inline void ac_set_mode(struct ac_config *config, enum ac_mode_t mode)
{
	if (mode == AC_MODE_SINGLE) {
		config->winctrl = 0;
	} else {
		config->winctrl |= AC_WEN_bm;
	}
}

/**
 * \brief Set analog comparator reference for positive line
 *
 * This function helps the caller setting the analog comparator reference
 * source for the positive line, for a given channel configuration. The
 * references are defined in the toolchain header files in the form of
 * \a AC_MUXPOS_*_gc, where * represents the various available references.
 *
 * \note In window mode the positive reference is the input signal.
 *
 * \see Chip-specific datasheet or header file for available mux configuration.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param reference Analog comparator positive reference
 */
static inline void ac_set_positive_reference(struct ac_config *config,
		AC_MUXPOS_t reference)
{
	config->acmuxctrl &= ~AC_MUXPOS_gm;
	config->acmuxctrl |= reference;
}

/**
 * \brief Set analog comparator reference for negative line
 *
 * This function helps the caller setting the analog comparator reference
 * source for the negative line, for a given channel configuration. The
 * references are defined in the toolchain header files in the form of
 * \a AC_MUXNEG_*_gc, where * represents the various available references.
 *
 *
 * \note In window mode the negative reference is the compare levels, analog
 * comparator channel 0 hold the upper limit of the window, while channel 1
 * hold the lower limit of the window.
 *
 * \see Chip-specific datasheet or header file for available mux configuration.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param reference Analog comparator negative reference
 */
static inline void ac_set_negative_reference(struct ac_config *config,
		AC_MUXNEG_t reference)
{
	config->acmuxctrl &= ~AC_MUXNEG_gm;
	config->acmuxctrl |= reference;
}

/**
 * \brief Set analog comparator hysteresis
 *
 * This function helps the caller setting the analog comparator hysteresis for
 * a channel configuration. The hysteresises are defined in the toolchain
 * header files in the form of \a AC_HYSMODE_*_gc, where * represents \a NONE,
 * \a SMALL and \a LARGE.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param hysteresis Analog comparator hysteresis config
 */
static inline void ac_set_hysteresis(struct ac_config *config,
		AC_HYSMODE_t hysteresis)
{
	config->acctrl &= ~AC_HYSMODE_gm;
	config->acctrl |= hysteresis;
}

/**
 * \brief Set analog comparator voltage scale
 *
 * This function helps the caller setting the analog comparator voltage scaler
 * for a channel configuration, the voltage scale is a numeric value.
 *
 * \note The analog comparator has one voltage scaler shared between the
 * channels. If both channels use the output from the voltage scaler they must
 * both share the same configuration.
 *
 * \param config Pointer to an \ref ac_config variable
 * \param scale Numeric value of the voltage scale
 */
static inline void ac_set_voltage_scaler(struct ac_config *config, uint8_t scale)
{
	Assert(scale < 64);
	config->ctrlb = scale;
}

#if XMEGA_A
/**
 * \brief Set analog comparator high-speed mode
 *
 * This function helps the caller setting the analog comparator high-speed mode
 * for a channel configuration. High-speed mode enables the shortest
 * propagation delay, on the expense of power consumption.
 *
 * \note Enabling high-speed mode automatically disables low-power mode.
 *
 * \param config Pointer to an \ref ac_config variable
 */
static inline void ac_set_high_speed_mode(struct ac_config *config)
{
	config->acctrl |= AC_HSMODE_bm;
}
#endif

#if XMEGA_A
/**
 * \brief Set analog comparator low-power mode
 *
 * This function helps the caller setting the analog comparator low-power mode
 * for a channel configuration. Low-power mode lowers the power consumption, on
 * the expense of propagation delay.
 *
 * \note Enabling low-power mode automatically disables high-speed mode.
 *
 * \param config Pointer to an \ref ac_config variable
 */
static inline void ac_set_low_power_mode(struct ac_config *config)
{
	config->acctrl &= ~AC_HSMODE_bm;
}
#endif
//@}

//! @}

#endif /* DRIVERS_AC_AC_H */
