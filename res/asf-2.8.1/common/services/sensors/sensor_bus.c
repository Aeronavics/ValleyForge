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

//! \internal Sensor Platform Board Configuration

#include    <conf_sensors.h>
#include    "sensor_bus.h"

#if defined(CONF_FRAMEWORK_BUS)

//! \internal Sensor API Bus I/O Implementations

#if defined(CONF_SENSOR_BUS_SPI)

#include    <spi/spi_master.h>

#define spi_bus_init    bus_init
#define spi_bus_read    bus_read
#define spi_bus_write   bus_write
#define spi_bus_probe   bus_probe

/*! \internal Initialize the SPI master bus I/O interface.
 *
 * \param   bus        The address of an AVR or AVR32 bus interface descriptor.
 * \param   bus_speed  The bus data rate.
 *
 * \retval  true       The bus was initialized.
 * \retval  false      The bus was not initialized.
 */
bool spi_bus_init(volatile void *bus, uint32_t bus_speed)
{
	spi_bus_t *const spi = bus;
	struct spi_device device;
	//
	// Initialize the Atmel Software Framework SPI master driver.
	//
	spi_master_init(spi);
	spi_master_setup_device(spi, &device, SPI_MODE_0, bus_speed, 0);
	spi_enable(spi);

	return spi_is_enabled(spi);
}

/*! \internal Read bytes from remote device using SPI (master) interface
 *
 * This routine reads "count" Bytes of data into location "data" from
 * a specified SPI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address
 * that is capable of storing the specified "count" Bytes of data.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t spi_bus_read
	(bus_desc_t *bus, uint8_t addr, void *data, size_t count)
{
	struct spi_device device = { .id = bus->addr };

	spi_select_device(bus->id, &device);
	bus->status = spi_read_packet(bus->id, data, count);
	spi_deselect_device(bus->id, &device);

	return (STATUS_OK == bus->status) ? count : 0;
}

/*! \internal Write bytes to remote device using SPI (master) interface
 *
 * This routine writes "count" Bytes of data from location "data" to
 * a specified SPI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t spi_bus_write
	(bus_desc_t *bus, uint8_t addr, const void *data, size_t count)
{
	struct spi_device device = { .id = bus->addr };

	spi_select_device(bus->id, &device);
	bus->status = spi_write_packet(bus->id, data, count);
	spi_deselect_device(bus->id, &device);

	return (STATUS_OK == bus->status) ? count : 0;
}

/*! \internal Determine the existence of a bus device
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
bool spi_bus_probe(bus_desc_t *bus, int arg)
{
	bus->status = ERR_UNSUPPORTED_DEV;
	return false;
}
#endif // defined(CONF_SENSOR_BUS_SPI)


#if defined(CONF_SENSOR_BUS_TWI)

#include    <twi/twi_master.h>

#define twi_bus_init    bus_init
#define twi_bus_read    bus_read
#define twi_bus_write   bus_write
#define twi_bus_probe   bus_probe

/*! \internal Initialize the TWI (master) bus I/O interface.
 *
 * \param   bus        The address of an AVR or AVR32 bus interface descriptor.
 * \param   bus_speed  The bus data rate.
 *
 * \retval  true       The bus was initialized.
 * \retval  false      The bus was not initialized.
 */
bool twi_bus_init(volatile void *bus, uint32_t bus_speed)
{
	twi_bus_t * const twi = bus;
	//
	// Specify TWI master bus configuration options.
	//
	twi_options_t twi_options = { .speed = bus_speed, .chip = 0 };
	//
	// Initialize the Atmel Software Framework TWI master driver.
	//
	return (STATUS_OK == twi_master_setup (twi, &twi_options));
}

/*! \internal Read bytes from remote device using TWI (master) interface
 *
 * This routine reads "count" Bytes of data into location "data" from
 * a specified TWI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address
 * that is capable of storing the specified "count" Bytes of data.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t twi_bus_read
	(bus_desc_t *bus, uint8_t addr, void *data, size_t count)
{
	twi_package_t const pkg = {
		.chip        = bus->addr,
		.addr        = addr,
		.addr_length = sizeof(addr),
		.buffer      = data,
		.length      = count,
		.no_wait   	 = bus->no_wait};

	bus->status = twi_master_read(bus->id, &pkg);
	return (STATUS_OK == bus->status) ? count : 0;
}

/*! \internal Write bytes to remote device using TWI (master) interface
 *
 * This routine writes "count" Bytes of data from location "data" to
 * a specified TWI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t twi_bus_write (bus_desc_t *bus, uint8_t addr, const void *data, 
	size_t count)
{
	twi_package_t const pkg = {
		.chip        = bus->addr,
		.addr        = addr,
		.addr_length = sizeof(addr),
		.buffer      = (void *) data,
		.length      = count,
		.no_wait	 = bus->no_wait};

	bus->status = twi_master_write(bus->id, &pkg);
	return (STATUS_OK == bus->status) ? count : 0;
}

/*! \internal Determine the existence of a bus device
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
bool twi_bus_probe(bus_desc_t *bus, int arg)
{
	bus->status = ERR_UNSUPPORTED_DEV;
	return false;
}
#endif // defined(CONF_SENSOR_BUS_TWI)

#endif // defined(CONF_FRAMEWORK_BUS)
