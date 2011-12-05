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

// Sensor Platform Board Configuration

#include    <conf_sensors.h>
#include    <sensors/sensor_bus.h>

#if defined(CONF_CUSTOM_BUS) && defined(CONF_SENSOR_BUS_TWI)

//! \internal Sensor API Bus I/O Implementations

#include    "twim.h"

#define twim_init               bus_init
#define twim_read               bus_read
#define twim_write              bus_write

//! \internal TWIM Bus Interface Constants

#if defined(AVR32_TWIM0_IRQ_GROUP)
#   define TWIM0_IRQ_GROUP      AVR32_TWIM0_IRQ_GROUP
#else
#   define TWIM0_IRQ_GROUP      (AVR32_TWIM0_IRQ / 32)
#endif

#if defined(AVR32_TWIM1_IRQ_GROUP)
#   define TWIM1_IRQ_GROUP      AVR32_TWIM1_IRQ_GROUP
#else
#   define TWIM1_IRQ_GROUP      (AVR32_TWIM1_IRQ / 32)
#endif

#if defined(CONFIG_TWIM_INT_LVL)
#   define TWIM_INT_LVL         CONFIG_TWIM_INT_LVL
#else
#   define TWIM_INT_LVL         2
#endif

#if (AVR32_TWIM_H_VERSION == 100)
#   define AVR32_TWIM_IDR_MASK  (0x00007f1f)
#   define AVR32_TWIM_SCR_MASK  (0x00007f08)
#endif

//! \internal Default Events (Interrupt Enable Register (IER) bits).

#define MASTER_STANDARD_EVENTS \
   (AVR32_TWIM_IER_ANAK_MASK  | AVR32_TWIM_IER_DNAK_MASK  | \
	AVR32_TWIM_IER_IDLE_MASK  | AVR32_TWIM_IER_ARBLST_MASK)

#define MASTER_TRANSMIT_EVENTS \
   (AVR32_TWIM_IER_TXRDY_MASK | MASTER_STANDARD_EVENTS)

#define MASTER_RECEIVE_EVENTS  \
   (AVR32_TWIM_IER_RXRDY_MASK | MASTER_STANDARD_EVENTS)


//! \internal Transfer Message Descriptor

typedef struct {                        // transfer message descriptor

 // uint32_t                chip;       //!< slave 7-bit bus address
	uint32_t                addr;       //!< slave register or memory address
 // uint8_t                 addr_length;//!< address data size (1-3 bytes)
	void                    *buffer;    //!< source / destination data buffer
	uint32_t                length;     //!< source / destination data size

} twi_package_t;

//! \internal UC3 TWIM Bus Command Registers Descriptor

typedef struct {                        // twi_cmd_t - bus command format

	union {
		uint32_t            cmdr;       // UC3 TWI master CMDR register word
		avr32_twim_cmdr_t   CMDR;       // UC3 TWI master CMDR bit fields
	};
	union {
		uint32_t            ncmdr;      // UC3 TWI master NCMDR register word
		avr32_twim_ncmdr_t  NCMDR;      // UC3 TWI master NCMDR bit fields
	};
	union {
		uint32_t            ier;        // UC3 TWI master IER register word
		avr32_twim_ier_t    IER;        // UC3 TWI master IER bit fields
	};

} twi_cmd_t;

/*! \internal TWIM Master Transfer Data Descriptors
 *
 * The TWI master bus interrupt handler uses the following structure
 * to receive arguments and return status to the application.
 */
static struct {                         //  bus transfer descriptor

	twi_bus_t               *bus;       // bus register interface
	const twi_package_t     *pkg;       // bus message descriptor
 // int                     addr_count; // bus transfer address data counter
	size_t                  data_count; // bus transfer payload data counter
	bool                    read;       // bus transfer direction
	bool                    locked;     // bus busy or unavailable
	volatile bool           start;      // transfer start / restart
	volatile bool           stop;       // transfer stop condition
	int8_t                  retries;    // transfer retry counter

} transfer;

//! \internal Mask TWI master interrupts at the bus interface.

inline static void bus_irq_disable(twi_bus_t *bus, uint32_t idr_mask)
{ 
	bus->idr = idr_mask; bus->sr; 
}

/*! \internal TWI Master interrupt handler.
 *
 * This is the common interrupt service routine for TWI Master interrupts.
 * On systems with multiple master interfaces, this routine will service
 * events on the interface (TWIM0 or TWIM1, for example) specified in the
 * \c bus parameter.
 *
 * \return  Nothing
 */
static inline void twim_irq_handler(void)
{
	twi_bus_t * const bus = transfer.bus;

	if (bus->SR.anak || bus->SR.dnak) {
		//
		// On Address or Data NAK from the slave the VALID bits in the CMDR
		// and NCMDR command registers are not cleared.  Discard the transfer
		// by clearing the command registers completely.
		//
		bus->ncmdr = 0;
		bus->cmdr  = 0;
	} else if (bus->SR.arblst) {
		//
		// On arbitration lost attempt to restart the transaction if the
		// retry counter hasn't expired, otherwise discard the transaction.
		//
		if (transfer.retries--) {
			transfer.start = true;
		} else {
			bus->ncmdr = 0;
			bus->cmdr  = 0;
		}
	} else if (transfer.data_count < transfer.pkg->length) {
		//
		// Perform data transactions if holding registers are available.
		//
		if (transfer.read && bus->SR.rxrdy) {
			uint8_t * const data = transfer.pkg->buffer;
			data[transfer.data_count++] = bus->rhr;
		} else if ((false == transfer.read) && bus->SR.txrdy) {
			const uint8_t * const data = transfer.pkg->buffer;
			bus->thr = data[transfer.data_count++];
		}
	}
	//
	// Disable all bus interrupts when IDLE is set in the bus interface.
	//
	if (bus->SR.idle) {
		transfer.stop = (false == transfer.start);
		bus_irq_disable(bus, AVR32_TWIM_IDR_MASK);
	}
}

//! \internal TWI Master Interrupt Vectors

ISR (twim0_irq, TWIM0_IRQ_GROUP, TWIM_INT_LVL) 
{ 
	twim_irq_handler (); 
}

ISR (twim1_irq, TWIM1_IRQ_GROUP, TWIM_INT_LVL) 
{ 
	twim_irq_handler (); 
}

/*! \internal Start a TWI master transfer and wait for completion.
 *
 * This routine will perform a TWI master transaction on a specified \c bus
 * interface.  The \c pkg transaction package descriptor must be initialized
 * with fields indicating buffer address and size.  The AVR32 TWIM
 * device-specific command register settings required to perform the
 * transaction are in the \c cmd parameter.
 *
 * If the specified TWIM interface is not available due to an existing
 * transaction, this routine will wait (block) until the bus becomes free
 * if the \c no_wait parameter is \c false, otherwise this routine will return
 * immediately with an \c ERR_BUSY status if the bus is not available.
 *
 * In addition to the transfer Byte counter returned, one of the following
 * \ref status_code_t values will be set in the \c bus status field:
 *
 *      - STATUS_OK if the transfer completes, else
 *      - ERR_BAD_ADDRESS to indicate an address error.
 *      - ERR_BAD_DATA to indicate a data error.
 *      - ERR_BUSY to indicate an unavailable bus.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   pkg     AVR32 TWI master transfer package descriptor.
 * \param   cmd     Specifies device-specific bus commands.
 * \param   read    Specifies the transfer direction.
 *
 * \return The number of Bytes transferred, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
static inline size_t twim_transfer(bus_desc_t *bus, const twi_package_t *pkg, 
	const twi_cmd_t *cmd, bool read)
{
	bus->status = STATUS_OK;
	//
	// Initiate a transaction when the bus is ready.
	//
	while (transfer.locked) {

		if (bus->no_wait) {
			bus->status = ERR_BUSY;
			return 0;
		}

		cpu_relax();
	}
	irqflags_t const flags = cpu_irq_save();
		transfer.locked = true;
	cpu_irq_restore(flags);
	//
	// Initiailze the bus transfer descriptor for this transaction.
	//
 // transfer.bus        = bus->id;
	transfer.pkg        = pkg;
	transfer.data_count = 0;
	transfer.read       = read;
	transfer.start      = true;
	transfer.stop       = false;
	transfer.retries    = BUS_MAX_RETRY;
	//
	// Execute the master transaction by writing the command (CMDR), next
	// command (NCMDR), and event (interrupt) enable registers.  Clear all
	// status register events prior to enabling TWIM bus interrupts.
	//
	do  {
		if (transfer.start) {
			transfer.start      = false;
			transfer.bus->scr   = AVR32_TWIM_SCR_MASK;
			transfer.bus->cmdr  = cmd->cmdr;
			transfer.bus->ncmdr = cmd->ncmdr;
			transfer.bus->thr   = pkg->addr;
			transfer.bus->ier   = cmd->ier;
		}

		cpu_relax();

	} while (false == transfer.stop);
	//
	// Test and report bus error status.
	//
	if (transfer.bus->SR.anak) { 
		bus->status = ERR_BAD_ADDRESS; 
	} else if (transfer.bus->SR.dnak) { 
		bus->status = ERR_BAD_DATA; 
	} else if (transfer.bus->SR.arblst) { 
		bus->status = ERR_BUSY; 
	}
	//
	// Save the transfer data counter value before unlocking.
	//
	size_t const data_count = transfer.data_count;
	//
	// Release soft-lock on the global bus interface registers.
	//
	transfer.locked = false;
	//
	// Return the number of Bytes transferred to the API.
	//
	return data_count;
}

/*! \internal Set the twi bus speed in conjunction with the clock frequency
 *
 * \param twi    Base address of the TWI (i.e. &AVR32_TWI).
 * \param speed  The desired TWI bus speed (bits-per-second).
 *
 * \return STATUS_OK when the speed is set, else ERR_INVALID_ARG to
 * indicate an error.
 */
static status_code_t set_bus_speed(twi_bus_t * twi, uint32_t speed)
{
	status_code_t status = ERR_INVALID_ARG;
	//
	// Validate the requested TWI transfer rate.
	//
	if ((TWI_SPEED_STANDARD != speed) && (TWI_SPEED_FAST != speed)) { 
		return status; 
	}

	//
	// Get the current running PBA clock frequency (Hz.).
	//
	uint32_t const pba_hz = sysclk_get_pba_hz();
	//
	// The Clock Waveform Generator Register (CWGR) controls the TWCK
	// waveform.  Bus timings are functions of cycles of a prescaled clock
	// selected through the EXP field in the CWGR register.
	//
	// The basic prescaled clock value is calculated as 1/2 the clock-per-bit
	// rate given by the peripheral bus frequency and requested TWI SCL rate.
	//
	// As (3) of the CWGR fields must fit within 8-bits, the prescaled value
	// will be divided down by additional powers of 2 specified in the EXP
	// field (3-bits max) until the prescaled value is 8-bits at most.
	//            
	//                          F_clkpb
	//      F_prescaled  =  -----------------
	//                         2^(EXP + 1)
	//
	// TWCK rise and fall times are determined by external circuitry, while
	// clock low and high time periods are determined by prescaled clock
	// cycles in the additional CWGR fields:
	//                                                   100kHz    400kHz
	//  Field    Symbol    Parameter                     Min.      Min.
	//  ----------------------------------------------------------------------
	//  LOW      T_low     low period SCL clock          4.7 us    1.3 us
	//  LOW      T_buf     free time btwn. START & STOP  4.7 us    1.3 us
	//  HIGH     T_high    high period SCL clock         4.0 us    0.6 us
	//  STASTO   T_hd;sta  hold time (repeated) START    4.0 us    0.6 us
	//  STASTO   T_su;sta  set-up time repeated START    4.7 us    0.6 us
	//  STASTO   T_su;sto  set-up time STOP condition    4.0 us    0.6 us
	//  DATA     T_hd;dat  data hold time                0   us    0.9 us
	//  DATA     T_su;dat  set-up time DATA              250 ns    100 ns
	//
	uint32_t f_prescaled = (pba_hz / speed / 2);    // clocks-per-bit
	uint32_t cwgr_exp    = 0;
	//
	// Calculate additional powers, if any, for the prescalar value.
	//
	while ((f_prescaled > 0xff) && (cwgr_exp <= 0x7)) {
		++cwgr_exp;
		f_prescaled /= 2;
	}
	//
	// Assume most CWGR settings have to yield a period of at least
	// 4.7 microseconds for standard-mode and 1.33 microseconds for
	// fast-mode where:
	//
	//      f_prescaled = min_period_seconds * pba_hz
	//
	// Calculate the minimum required prescaled frequency as the
	// ceiling of these values to round up for integer division.
	//
	const uint32_t min_hz = (TWI_SPEED_STANDARD == speed)
		? ((10000000 / 47) + 1) : ((100000000 / 133) + 1);

	while ((f_prescaled > 0) && ((pba_hz / f_prescaled) <  min_hz)) { 
		
		--f_prescaled; 
	}

	if (f_prescaled && (cwgr_exp <= 0x7)) {
		twi->CWGR.exp    = cwgr_exp;
		twi->CWGR.data   = 0;
		twi->CWGR.stasto = f_prescaled;
		twi->CWGR.high   = (f_prescaled / 2);
		twi->CWGR.low    = (f_prescaled / 2);

		status = STATUS_OK;
	}

	return status;
}

/*! \internal Initialize the TWI (master) bus I/O interface.
 *
 * \param   bus     The address of an AVR32 TWI master interface.
 * \param   speed   The bus data rate.
 *
 * \retval  true    The bus was initialized.
 * \retval  false   The bus was not initialized.
 */
bool twim_init(volatile void * bus, uint32_t speed)
{
	twi_bus_t * const twi = bus;
	bool bus_enabled = false;
	//
	// Enable the required TWI master peripheral bus clock.
	//
	if ((uint32_t) twi == AVR32_TWIM0_ADDRESS) {
		sysclk_enable_pba_module(SYSCLK_TWIM0);
	} else if ((uint32_t) twi == AVR32_TWIM1_ADDRESS) {
		sysclk_enable_pba_module(SYSCLK_TWIM1);
	} else {
		return false;
	}
	//
	// Disable all TWI master interrupt events before performing a software
	// reset of the TWI master.  The master must be enabled in order to run
	// the reset function and the master will be disabled at the conclusion
	// of the reset.
	//
	cpu_irq_disable();
	bus_irq_disable(twi, AVR32_TWIM_IDR_MASK);

	twi->CR.men   = 1;
	twi->CR.swrst = 1;

	transfer.bus  = twi;

	irq_register_handler(twim0_irq, AVR32_TWIM0_IRQ, TWIM_INT_LVL);
	irq_register_handler(twim1_irq, AVR32_TWIM1_IRQ, TWIM_INT_LVL);

	cpu_irq_enable();
	//
	// If the TWI master bus timing registers are successfully configured,
	// enable the TWI master interface and, optionally, the SMBus mode.
	//
	if (STATUS_OK == set_bus_speed(twi, speed)) {

		twi->CR.men = 1;

		if (SMBUS_PROTOCOL) {
			twi->CR.smen = 1;
			twi->smbtr   = (uint32_t) -1;
		}

		bus_enabled = true;
	}

	return bus_enabled;
}

/*! \internal Read multiple Bytes from a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   reg     The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t twim_read(bus_desc_t *bus, uint8_t reg, void *data, size_t count)
{
	twi_package_t const pkg = {
		.addr        = reg,
		.buffer      = data,
		.length      = count 
	};

	twi_cmd_t cmd    = {{0}, {0}, {MASTER_RECEIVE_EVENTS}};

	cmd.CMDR.nbytes  = sizeof(reg);
	cmd.CMDR.valid   = 1;
	cmd.CMDR.start   = 1;
	cmd.CMDR.sadr    = bus->addr;

	cmd.NCMDR.nbytes = count;
	cmd.NCMDR.valid  = 1;
	cmd.NCMDR.stop   = 1;
	cmd.NCMDR.start  = 1;
	cmd.NCMDR.read   = 1;
	cmd.NCMDR.sadr   = bus->addr;

	return twim_transfer(bus, &pkg, &cmd, true);
}

/*! \internal Write multiple Bytes to a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   reg     The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t twim_write(bus_desc_t *bus, uint8_t reg, const void *data, size_t count)
{
	twi_package_t const pkg = {
		.addr        = reg,
		.buffer      = (void *) data,
		.length      = count 
	};

	twi_cmd_t cmd    = {{0}, {0}, {MASTER_TRANSMIT_EVENTS}};

	cmd.CMDR.nbytes  = sizeof(reg) + count;
	cmd.CMDR.valid   = 1;
	cmd.CMDR.stop    = 1;
	cmd.CMDR.start   = 1;
	cmd.CMDR.sadr    = bus->addr;

	return twim_transfer(bus, &pkg, &cmd, false);
}

#endif // defined(CONF_CUSTOM_BUS) && defined(CONF_SENSOR_BUS_TWI)
