/**
 * \file
 *
 * \brief Atmel AVR32 TWI Master Bus Interfaces
 *
 * This module provides general access to the Atmel two-wire master (TWIM)
 * bus interface implemented on UC3L and UC3A3 microcontrollers.  It is a
 * lightweight replacement to the Atmel Software Framework drivers for the
 * TWIM interface on a given part.  The Common Sensors API Service will use
 * this module unless the \c CONF_CUSTOM_BUS configuration constant is defined
 * for an application build.
 *
 * Copyright (C) 2011 Atmel Corporation. All rights reserved.
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
#ifndef _twim_h_
#define _twim_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <status_codes.h>

//! \brief TWIM Bus Interface Constants
// @{

#define SMBUS_PROTOCOL  (false)
#define BUS_MAX_RETRY   (2)

// @}


//! \brief Supported TWI Bus Transfer Rates

typedef enum {                      // bus speed constants

	TWI_SPEED_STANDARD  = 100000,   //!< standard, 100k bit-per-second
	TWI_SPEED_FAST      = 400000    //!< fast, 400k bit-per-second

} twi_speed_t;

//! \name System Bus I/O Access Methods
// @{
/*! \brief Initialize the TWI (master) bus I/O interface.
 *
 * \param   bus     The address of an AVR32 TWI master interface.
 * \param   speed   The bus data rate.
 *
 * \retval  true    The bus was initialized.
 * \retval  false   The bus was not initialized.
 */
bool twim_init (volatile void *bus, uint32_t speed);

/*! \brief Read multiple Bytes from a bus interface.
 *
 * \param   dev     device (twi/i2c slave) address
 * \param   reg     The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return STATUS_OK if all Bytes were read, else an error code.
 */
status_code_t twim_read (uint16_t dev, uint8_t reg, void *data, size_t count);

/*! \brief Write multiple Bytes to a bus interface.
 *
 * \param   dev     device (twi/i2c slave) address
 * \param   reg     The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return STATUS_OK if all Bytes were written, else an error code.
 */
status_code_t twim_write (uint16_t dev, uint8_t reg, const void *data, 
	size_t count);

/*! \brief Read a single Byte from a bus interface.
 *
 * \param   dev     device (twi/i2c slave) address
 * \param   reg     The device register or memory address.
 *
 * \return A value fetched from the device.  This value is
 *         undefined in the event of an I/O error.
 */
static inline uint8_t twim_get (uint16_t dev, uint8_t reg)
{
	uint8_t data = 0;
	(void) twim_read (dev, reg, &data, sizeof (data));
	return data;
}

/*! \brief Write a single Byte to a bus interface.
 *
 * \param   dev     device (twi/i2c slave) address
 * \param   reg     The device register or memory address.
 * \param   data    The value of the Byte to write.
 *
 * \return  Nothing.
 */
static inline void twim_put (uint16_t dev, uint8_t reg, uint8_t data)
{
	(void) twim_write (dev, reg, &data, sizeof (data));
}
// @}


#ifdef __cplusplus
}
#endif

#endif /* _twim_h_ */
