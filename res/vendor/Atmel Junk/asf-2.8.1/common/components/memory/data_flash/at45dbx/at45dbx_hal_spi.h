/**
 * \file
 *
 * \brief Connection of the AT45DBX DataFlash to SPI interface driver.
 *
 * This file manages the connection of the AT45dbx DataFlash driver to an
 * SPI service (could be spi master service or usart in spi mode). The SPI
 * service selection depends on  AT45DBX_USES_SPI_MASTER_SERVICE or 
 * AT45DBX_USES_USART_SPI_SERVICE in conf_at45dbx.h
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

#ifndef _AT45DBX_HAL_SPI_H_
#define _AT45DBX_HAL_SPI_H_

#include "conf_at45dbx.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/*! \name Functions to connect the DataFlash driver with the SPI Multiple-Sector Access Functions
 */
//! @{	
	
// Sanity check to enable connection with only one SPI service
#if defined(AT45DBX_USES_SPI_MASTER_SERVICE) &&  defined(AT45DBX_USES_USART_SPI_SERVICE)
	#error only one SPI service should be selected
#endif
// At least one SPI service should be connnectec...
#if !defined(AT45DBX_USES_SPI_MASTER_SERVICE) &&  !defined(AT45DBX_USES_USART_SPI_SERVICE)
	#error No SPI service selected
#endif

#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)
 	#include "spi_master.h"
	// Create as many spi_device as required...
	#if (AT45DBX_MEM_CNT>0)
		struct spi_device AT45DBX_DEVICE1 = {
			.id = AT45DBX_CS
		};
	#endif
	#if (AT45DBX_MEM_CNT>1)
		struct spi_device AT45DBX_DEVICE2 = {
			.id = AT45DBX_CS2
		};
	#endif
	#if (AT45DBX_MEM_CNT>2)
		struct spi_device AT45DBX_DEVICE3 = {
			.id = AT45DBX_CS3
		};
	#endif
	#if (AT45DBX_MEM_CNT>3)
		struct spi_device AT45DBX_DEVICE4 = {
			.id = AT45DBX_CS4
		};
	#endif

#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	#include "usart_spi.h"
	// Create as many usart_spi_device as required...
	#if (AT45DBX_MEM_CNT>0)
		struct usart_spi_device AT45DBX_DEVICE1 = {
			.id = AT45DBX_CS
		};
	#endif
	#if (AT45DBX_MEM_CNT>1)
		struct usart_spi_device AT45DBX_DEVICE2 = {
			.id = AT45DBX_CS2
		};
	#endif
	#if (AT45DBX_MEM_CNT>2)
		struct usart_spi_device AT45DBX_DEVICE3 = {
			.id = AT45DBX_CS3
		};
	#endif
	#if (AT45DBX_MEM_CNT>3)
		struct usart_spi_device AT45DBX_DEVICE4 = {
			.id = AT45DBX_CS4
		};	
	#endif
#endif

/*! \brief Initialize SPI external ressource for AT45dbx DataFlash driver.
 *
 *  This function initializes the DataFlash component as well as the SPI service
 *  the memory is connected to.
 *  \pre The conf_at45dbx.h file should provide the following information
 *	 - Selection of the SPI service the DataFlash is connected 
 *  (AT45DBX_USES_SPI_MASTER_SERVICE or  AT45DBX_USES_USART_SPI_SERVICE)
 *  - AT45DBX_MEM_SIZE: The DataFlash type the driver is connected to.
 *  - AT45DBX_MEM_CNT: The number of DataFlash components (number of chipselect)
 *  - AT45DBX_SPI_MODULE:  The name of the SPI module used by the DataFlash driver
 *  - AT45DBX_SPI_MASTER_SPEED: The SPI bus speed.
 */
inline void at45dbx_spi_init(void)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)
	spi_master_init(AT45DBX_SPI_MODULE);
	#if (AT45DBX_MEM_CNT==1)
		spi_master_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE1,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT45DBX_MEM_CNT>1)
		spi_master_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE2,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT45DBX_MEM_CNT>2)
		spi_master_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE3,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT45DBX_MEM_CNT>3)
		spi_master_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE4,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	spi_enable(AT45DBX_SPI_MODULE);	
	
// Implementation with USART in SPI mode service
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	usart_spi_init(AT45DBX_SPI_MODULE);
	#if (AT45DBX_MEM_CNT==1)
		usart_spi_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE1,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT45DBX_MEM_CNT>1)
		usart_spi_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE2,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT45DBX_MEM_CNT>2)
		usart_spi_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE3,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
	#if (AT45DBX_MEM_CNT>3)
		usart_spi_setup_device(AT45DBX_SPI_MODULE,&AT45DBX_DEVICE4,SPI_MODE_0,AT45DBX_SPI_MASTER_SPEED,0);
	#endif
#endif	
}

/*! \brief Select one external DataFlash component
 *
 * \param mem_id  The DataFlash index number.
 */
inline void at45dbx_spi_select_device(uint8_t mem_id)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)	
	#if (AT45DBX_MEM_CNT==1)	
	spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);	
	#else
	switch(mem_id) {
	case 1:
		spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);
		break;
		
	case 2:
		spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE2);
		break;

	case 3:
		spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE3);
		break;

	case 4:
		spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE4);
		break;
		
	default:
		/* unhandled_case(id); */
		return;			
	}
	#endif
	
// Implementation with USART in SPI mode service
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	#if (AT45DBX_MEM_CNT==1)	
	usart_spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);	
	#else
	switch(mem_id) {
	case 1:
		usart_spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);
		break;
		
	case 2:
		usart_spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE2);
		break;

	case 3:
		usart_spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE3);
		break;

	case 4:
		usart_spi_select_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE4);
		break;
		
	default:
		/* unhandled_case(id); */
		return;			
	}
#endif
	
#endif	
}

/*! \brief Unselect one external DataFlash component
 *
 * \param mem_id  The DataFlash index number.
 */
inline void at45dbx_spi_deselect_device(uint8_t mem_id)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)	
	#if (AT45DBX_MEM_CNT==1)
	spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);
	#else
	switch(mem_id) {
	case 1:
		spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);
		break;
		
	case 2:
		spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE2);
		break;

	case 3:
		spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE3);
		break;

	case 4:
		spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE4);
		break;
		
	default:
		/* unhandled_case(id); */
		return;	
	}
	#endif
	
// Implementation with USART in SPI mode service	
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	#if (AT45DBX_MEM_CNT==1)
	usart_spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);
	#else
	switch(mem_id) {
	case 1:
		usart_spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE1);
		break;
		
	case 2:
		usart_spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE2);
		break;

	case 3:
		usart_spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE3);
		break;

	case 4:
		usart_spi_deselect_device(AT45DBX_SPI_MODULE, &AT45DBX_DEVICE4);
		break;
		
	default:
		/* unhandled_case(id); */
		return;	
	}
#endif
#endif	
}

/*! \brief Send one byte to the DataFlash.
 *
 * \param data The data byte to send.
 * \pre The DataFlash should be selected first using at45dbx_spi_select_device
 */
inline void at45dbx_spi_write_byte(uint8_t data)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)
	spi_write_packet(AT45DBX_SPI_MODULE, &data, 1);
// Implementation with USART in SPI mode service	
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	usart_spi_write_packet(AT45DBX_SPI_MODULE, &data, 1);	
#endif	
}

/*! \brief Get one byte (read) from the DataFlash.
 *
 * \return The received byte.
 * \pre The DataFlash should be selected first using at45dbx_spi_select_device
 */
inline void at45dbx_spi_read_byte(uint8_t *data)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)	
	spi_read_packet(AT45DBX_SPI_MODULE, data, 1);

// Implementation with USART in SPI mode service
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	usart_spi_read_packet(AT45DBX_SPI_MODULE, data, 1);
#endif	
}


/**
 * \brief Receive a sequence of bytes from a DataFlash
 *
 *
 * \param data   data buffer to read
 * \param len    Length of data
 * \pre The DataFlash should be selected first using at45dbx_spi_select_device
 */
inline void at45dbx_spi_read_packet(void const *data, size_t len)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)	
	spi_read_packet(AT45DBX_SPI_MODULE, (uint8_t*)data, len);	
	
// Implementation with USART in SPI mode service
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	usart_spi_read_packet(AT45DBX_SPI_MODULE, (uint8_t*)data, len);
#endif	
}

/**
 * \brief Send a sequence of bytes to a DataFlashfrom
 *
 *
 * \param data   data buffer to write
 * \param len    Length of data
 * \pre The DataFlash should be selected first using at45dbx_spi_select_device
 *
 */
inline void at45dbx_spi_write_packet(void const *data, size_t len)
{
#if defined( AT45DBX_USES_SPI_MASTER_SERVICE)	
	spi_write_packet(AT45DBX_SPI_MODULE, (uint8_t*)data, len);	
	
// Implementation with USART in SPI mode service
#elif defined(AT45DBX_USES_USART_SPI_SERVICE)
	usart_spi_write_packet(AT45DBX_SPI_MODULE, (uint8_t*)data, len);	
#endif	
}

//! @}

#ifdef __cplusplus
}
#endif

#endif  // _AT45DBX_HAL_SPI_H_
