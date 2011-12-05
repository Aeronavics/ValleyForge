/**
 * \file
 *
 * \brief Sensor API Platform Bus Interfaces
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


#ifndef _sensor_bus_h_
#define _sensor_bus_h_


#ifdef __cplusplus
extern "C" {
#endif


// Atmel AVR Software Framework (ASF) Interfaces

#include <compiler.h>
#include <status_codes.h>


//! \brief Platform Bus Type Constants

typedef enum {                          // bus_type_t
	
	BUS_TYPE_UNKNOWN,                   //!< unknown bus
	BUS_TYPE_TWI,                       //!< TWI/I2C bus
	BUS_TYPE_SPI,                       //!< SPI bus
	BUS_TYPE_PMBUS,                     //!< PMBus protocol
	BUS_TYPE_SMBUS                      //!< SMBus protocol

} bus_type_t;


//! \brief Platform Bus Status Constants

typedef status_code_t bus_status_t;


//! \internal Platform Bus Interface Types

#if UC3
#if defined(AVR32_TWI)
typedef volatile avr32_twi_t    twi_bus_t;
#else
typedef volatile avr32_twim_t   twi_bus_t;
#endif
typedef volatile avr32_spi_t    spi_bus_t;
#else
typedef volatile TWI_t          twi_bus_t;
typedef volatile SPI_t          spi_bus_t;
#endif


//! \brief Platform Bus Interface Descriptor

typedef struct {                        // bus_desc_t
	
	bus_type_t      type;               //!< bus type and protocol
	volatile void   *id;                //!< bus interface address
	uint16_t        addr;               //!< device bus address
	bus_status_t    status;             //!< bus transaction status
	bool            no_wait;            //!< bus transaction non-wait option

	/*! \internal
	 *
	 * o Design and implement a full-featured bus abstraction.
	 *
	 *   Once the ASF bus drivers have improved and matured, revisit the
	 *   bus abstraction.  For example, it could be useful to implement a
	 *   separate configurable bus interface library with improved state
	 *   detection and reporting, in addition to support for SMBus and
	 *   PMBus protocols on the AVR TWI interfaces that support these.
	 *
	 * o Review for reentrancy problems that might arise if these interfaces
	 *   are executed via separate asynchronous execution threads (RTOS or
	 *   ISRs, for example).
	 */

#if 0
	//! \internal Bus Event Counters
	// @{

	uint32_t        read_req_count;     //!< number of read transactions
	uint32_t        write_req_count;    //!< number of write transactions
	uint32_t        total_err_count;    //!< number of transaction errors
	uint32_t        addr_err_count;     //!< transaction address errors
	uint32_t        data_err_count;     //!< transaction data errors
	uint32_t        busy_err_count;     //!< resource busy errors
	uint32_t        tout_err_count;     //!< transaction timeouts

	// @}
#endif

#if 0
	//! \name System Bus I/O Access Interfaces
	// @{

	size_t (*bus_read)(struct bus_desc *, uint8_t, void *, size_t);
	size_t (*bus_write)(struct bus_desc *, uint8_t, const void *, size_t);
	bool   (*bus_probe)(struct bus_desc *, int);

	// @}
#endif

} bus_desc_t;


//! \name System Bus I/O Access Methods
//@{
/*! \internal Initialize the bus I/O interface.
 *
 * \param   busif   The address of a system bus (registers) interface.
 * \param   speed   The bus data rate.
 *
 * \retval  true    The bus was initialized.
 * \retval  false   The bus was not initialized.
 */
bool bus_init(volatile void *busif, uint32_t speed);

/*! \brief Read multiple Bytes from a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t bus_read(bus_desc_t *bus, uint8_t addr, void *data, size_t count);

/*! \brief Write multiple Bytes to a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t bus_write(bus_desc_t *bus, uint8_t addr, const void *data, size_t count);

/*! \brief Determine the existence of a bus device
 *
 * This routine determines the existence of a device located at a bus interface
 * and address specified by an initialized \c bus descriptor.
 * Implementations are only required to return \c true when it can be determined
 * that a device is installed at the bus interface address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   arg     Ignored reserved argument.
 *
 * \retval  true    A device responded to the bus address.
 * \retval  false   A device did not respond to the bus address.
 */
bool bus_probe(bus_desc_t *bus, int arg);

/*! \brief Read a single Byte from a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 *
 * \return A value fetched from the device.  This value is
 *         undefined in the event of an I/O error.
 */
static inline uint8_t bus_get (bus_desc_t *bus, uint8_t addr)
{
	uint8_t data = 0;
	bus_read(bus, addr, &data, sizeof(uint8_t));

	return data;
}

/*! \brief Write a single Byte to a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The value of the Byte to write.
 *
 * \return  Nothing.
 */
static inline void bus_put (bus_desc_t *bus, uint8_t addr, uint8_t data)
{
	bus_write(bus, addr, &data, sizeof(uint8_t));
}

/*! \brief Clear a bit at a bus device register or memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   mask    The mask value of the bit to clear.
 *
 * \return  Nothing.
 */
static inline void bus_reg_bitclear (bus_desc_t *bus, uint8_t addr, 
	uint8_t mask)
{
	bus_put(bus, addr, ~mask & bus_get(bus, addr));
}

/*! \brief Set a bit at a bus device register or memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   mask    The mask value of the bit to set.
 *
 * \return  Nothing.
 */
static inline void bus_reg_bitset (bus_desc_t *bus, uint8_t addr, uint8_t mask)
{
	bus_put(bus, addr, mask | bus_get(bus, addr));
}
//@}

/*! \brief Increment bus event counters.
 *
 * This routine is called by the bus interface implementations to update bus
 * event counters when the \c CONF_EVENT_COUNTERS configuration constant is
 * used to build a system.  User applications do not call this function.  The
 * event counters can be printed on a serial console or inspected in a debugger
 * when debugging bus transactions in an application.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   read    Set \c true to indicate a read transaction.
 *
 * \return  Nothing.
 */
#if 0
static inline void bus_event_count (bus_desc_t *bus, bool read)
{
	if (read) {
		++(bus->read_req_count);
	} else {
		++(bus->write_req_count);
	}

	if (STATUS_OK != bus->status) {

		++(bus->total_err_count);

		switch (bus->status) {
			case ERR_BAD_ADDRESS:
				++(bus->addr_err_count);
				break;
			case ERR_BAD_DATA:
				++(bus->data_err_count);
				break;
			case ERR_BUSY:
				++(bus->busy_err_count);
				break;
			case ERR_TIMEOUT:
				++(bus->tout_err_count);
				break;
		}
	}
}
#endif


#ifdef __cplusplus
}
#endif

#endif /* _sensor_bus_h_ */
