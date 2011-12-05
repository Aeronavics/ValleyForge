// This file has been prepared for Doxygen automatic documentation generation.
/*! \file *********************************************************************
 *
 * \brief Resistive Touch driver
 *
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/
/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */
#ifndef _RTOUCH_H_
#define _RTOUCH_H_



/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include <stdbool.h>



/*============================ TYPES =========================================*/

//! Info for one calibration point, raw samples and actual panel position.
typedef struct rtouch_calibration_point_struct
{
    uint16_t panelX; //!< Actual panel X coordinate.
    uint16_t panelY; //!< Actual panel Y coordinate.
    uint16_t rawX; //!< Raw X sample value.
    uint16_t rawY; //!< Raw Y sample value.
} rtouch_calibration_point_t;

//!  Collection of the three calibration points required to compute calibration.
typedef struct rtouch_calibration_points_struct
{
    rtouch_calibration_point_t point1;
    rtouch_calibration_point_t point2;
    rtouch_calibration_point_t point3;
} rtouch_calibration_points_t;

//! Calibration matrix coefficients, computed from three calibration points.
typedef struct rtouch_calibration_matrix_struct
{
    int32_t A;
	int32_t B;
	int32_t C;
    int32_t D;
	int32_t E;
	int32_t F;
    int32_t K;
} rtouch_calibration_matrix_t;

//! Event type used by event struct TOUCH_event_t.
typedef enum rtouch_event_type_enum
{
	RTOUCH_NO_EVENT,
	RTOUCH_PRESS,
	RTOUCH_MOVE,
	RTOUCH_RELEASE
} rtouch_event_type_t;


//! User-friendly touch event structure.
typedef struct rtouch_event_struct
{
	rtouch_event_type_t type;
	int16_t rawX; //!< Raw X sample.
	int16_t rawY; //!< Raw Y sample.
	int16_t panelX; //!< Calibrated panel X position.
	int16_t panelY; //!< Calibrated panel Y position.
} rtouch_event_t;


typedef void (* rtouch_event_handler_t)( rtouch_event_t const * event );



/*============================ PROTOTYPES ====================================*/

#ifdef __cplusplus
extern "C" {
#endif


//! Initialize touch panel driver.
void rtouch_init(void);
//! Disable driver.
void rtouch_disable(void);
//! Enable driver.
void rtouch_enable(void);

//! Get last event.
void rtouch_get_event(rtouch_event_t * event);
//! True if touched.
bool rtouch_is_touched(void);

//! Compute a calibration matrix from three calibration points.
void rtouch_compute_calibration_matrix(
	rtouch_calibration_points_t const * points,
	rtouch_calibration_matrix_t * matrix );
//! Assign a calibration matrix to the driver.
void rtouch_set_calibration_matrix(rtouch_calibration_matrix_t const *source);
//! Get the current calibration matrix.
void rtouch_get_calibration_matrix(rtouch_calibration_matrix_t *destination);

//! Set new event handler.
void rtouch_set_event_handler(rtouch_event_handler_t handler);
//! Get current event handler.
rtouch_event_handler_t rtouch_get_event_handler(void);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
/* EOF */
