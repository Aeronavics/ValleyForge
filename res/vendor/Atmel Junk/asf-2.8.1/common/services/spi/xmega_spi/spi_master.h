/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief SPI Master driver for AVR.
 *
 * This file defines a useful set of functions for the SPI interface on AVR
 * devices.
 *
 * - Compiler:           IAR and GNU GCC for AVR
 * - Supported devices:  All AVR devices with an SPI module can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ******************************************************************************/

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

#ifndef _SPI_MASTER_H_
#define _SPI_MASTER_H_

#include "compiler.h"
#include "status_codes.h"
#include "ioport.h"
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/**
 * \defgroup xmega_spi_master_group XMEGA SPI master service.
 *
 * This is the API for SPI master service on XMEGA.
 *
 * @{
 */

/*! \name Spi Master Management Configuration
 */
//! @{
#include "conf_spi_master.h"

//! Default Config Spi Master Dummy Field
#ifndef CONFIG_SPI_MASTER_DUMMY
#define CONFIG_SPI_MASTER_DUMMY              0xFF
#endif
//! @}

/**
 * \brief Clock phase
 */
#define SPI_CPHA	(1 << 0)

/**
 * \brief Clock polarity
 */
#define SPI_CPOL	(1 << 1)

/**
 * \brief SPI mode 0
 */
#define SPI_MODE_0	0
/**
 * \brief SPI mode 1
 */
#define SPI_MODE_1	(SPI_CPHA)
/**
 * \brief SPI mode 2
 */
#define SPI_MODE_2	(SPI_CPOL)
/**
 * \brief SPI mode 3
 */
#define SPI_MODE_3	(SPI_CPOL | SPI_CPHA)

typedef uint8_t spi_flags_t;
typedef uint32_t board_spi_select_id_t;

//! \brief Polled SPI device defintion
struct spi_device {
	//! Board specific select id
	port_pin_t	id;
};

/*! \brief Initializes the SPI in master mode.
 *
 * \param spi       Base address of the SPI instance.
 *
 */
extern void spi_master_init(SPI_t *spi);

/**
 * \brief Setup a SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param spi Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific seclet id
 */
extern void spi_master_setup_device(SPI_t *spi, struct spi_device *device, 
     spi_flags_t flags, unsigned long baud_rate,
     board_spi_select_id_t sel_id);

/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
extern void spi_enable(SPI_t *spi);

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
extern void spi_disable(SPI_t *spi);


/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI is enabled, otherwise \c 0.
 */
extern bool spi_is_enabled(SPI_t *spi);

/**
 * \brief Select given device on the SPI bus
 *
 * Set device specific setting and calls board chip select.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 */
extern void spi_select_device(SPI_t *spi, struct spi_device *device);

/**
 * \brief Deselect given device on the SPI bus
 *
 * Calls board chip deselect.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern void spi_deselect_device(SPI_t *spi, struct spi_device *device);

/*! \brief Write one byte to a SPI device.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded 
 *
 */
__always_inline static inline void spi_write_single(SPI_t *spi, uint8_t data)
{
	spi_put(spi,data);
}

/**
 * \brief Send a sequence of bytes to a SPI device
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to write
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_write_packet(SPI_t *spi,const uint8_t *data, size_t len);


/*! \brief Receive one byte from a SPI device.
 *
 * \param spi Base address of the SPI instance.
 * \param data Pointer to the data byte where to store the received data.
 *
 */
inline static void spi_read_single(SPI_t *spi, uint8_t *data)
{
	*data=spi_get(spi);
}

/**
 * \brief Receive a sequence of bytes from a SPI device
 *
 * All bytes sent out on SPI bus are sent as value 0.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to read
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_read_packet(SPI_t *spi, uint8_t *data, size_t len);

/*! \brief Tests if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
inline static bool spi_is_rx_full(SPI_t *spi)
{
	return spi_is_tx_ok(spi); 
}

//! @}

#ifdef __cplusplus
}
#endif
#endif  // _SPI_MASTER_H_
