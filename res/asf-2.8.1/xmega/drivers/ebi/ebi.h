/**
 * \file
 *
 * \brief External bus interface (EBI) functions
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
#ifndef DRIVERS_EBI_EBI_H
#define DRIVERS_EBI_EBI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "compiler.h"

#include "sleepmgr.h"

// Header patch to support old headers versions from IAR and GCC compilers.
#ifndef EBI_CS_ASPACE_gm
# define EBI_CS_ASPACE_gm       EBI_CS_ASIZE_gm
# define EBI_CS_ASPACE_t        EBI_CS_ASIZE_t
# define EBI_CS_ASPACE_256B_gc  EBI_CS_ASIZE_256B_gc
# define EBI_CS_ASPACE_512B_gc  EBI_CS_ASIZE_512B_gc
# define EBI_CS_ASPACE_1KB_gc   EBI_CS_ASIZE_1KB_gc
# define EBI_CS_ASPACE_2KB_gc   EBI_CS_ASIZE_2KB_gc
# define EBI_CS_ASPACE_4KB_gc   EBI_CS_ASIZE_4KB_gc
# define EBI_CS_ASPACE_8KB_gc   EBI_CS_ASIZE_8KB_gc
# define EBI_CS_ASPACE_16KB_gc  EBI_CS_ASIZE_16KB_gc
# define EBI_CS_ASPACE_32KB_gc  EBI_CS_ASIZE_32KB_gc
# define EBI_CS_ASPACE_64KB_gc  EBI_CS_ASIZE_64KB_gc
# define EBI_CS_ASPACE_128KB_gc EBI_CS_ASIZE_128KB_gc
# define EBI_CS_ASPACE_256KB_gc EBI_CS_ASIZE_256KB_gc
# define EBI_CS_ASPACE_512KB_gc EBI_CS_ASIZE_512KB_gc
# define EBI_CS_ASPACE_1MB_gc   EBI_CS_ASIZE_1MB_gc
# define EBI_CS_ASPACE_2MB_gc   EBI_CS_ASIZE_2MB_gc
# define EBI_CS_ASPACE_4MB_gc   EBI_CS_ASIZE_4MB_gc
# define EBI_CS_ASPACE_8MB_gc   EBI_CS_ASIZE_8MB_gc
# define EBI_CS_ASPACE_16M_gc   EBI_CS_ASIZE_16M_gc
#endif


/**
 * \defgroup ebi_group External Bus Interface (EBI)
 *
 * This is a driver for configuring, enablig, disabling and use of the on-chip
 * external bus interface (EBI).
 *
 * \section dependencies Dependencies
 *
 * The external bus interface depends on the following modules:
 *  - \ref sysclk_group for peripheral clock control and getting bus speeds.
 *  - \ref sleepmgr_group for setting available sleep mode.
 *
 * @{
 */

//! Chip select on the EBI that can be configured for SDRAM operation
#define EBI_SDRAM_CS    3

//! Externel bus interface chip select configuration
struct ebi_cs_config {
	//! EBI chip select control A register
	uint8_t         ctrla;
	//! EBI chip select control B register
	uint8_t         ctrlb;
	//! EBI chip select base address register
	uint16_t        base_address;
};

//! Externel bus interface SDRAM configuration
struct ebi_sdram_config {
	//! EBI SDRAM control A register
	uint8_t         sdramctrla;
	//! EBI SDRAM control B register
	uint8_t         sdramctrlb;
	//! EBI SDRAM control C register
	uint8_t         sdramctrlc;
	//! EBI SDRAM refresh period register
	uint16_t        refresh_period;
	//! EBI SDRAM initialization delay register
	uint16_t        init_delay;
};

//! \name External Bus Interface management
//@{
void ebi_cs_write_config(const uint8_t cs, const struct ebi_cs_config *config);
void ebi_cs_read_config(const uint8_t cs, struct ebi_cs_config *config);

void ebi_sdram_write_config(const struct ebi_sdram_config *config);
void ebi_sdram_read_config(struct ebi_sdram_config *config);

void ebi_enable_cs(const uint8_t cs, const struct ebi_cs_config *config);
void ebi_disable_cs(const uint8_t cs);

/**
 * \brief Check if SDRAM is ready for access
 *
 * This function must be checked after the SDRAM chip select has been enabled.
 * It will return true when the SDRAM is initialized.
 *
 * \retval true when SDRAM is ready, false otherwize
 */
static inline bool ebi_sdram_is_ready(void)
{
	return (EBI.CS3.CTRLB & EBI_CS_SDINITDONE_bm);
}

//@}

//! \name External Bus Interface Chip Select configuration helper functions
//@{

/**
 * \brief Set chip select mode
 *
 * This function helps the caller setting the chip select mode. The different
 * modes are provided by an EBI_CS_MODE_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_cs_config variable
 * \param mode Chip select mode given by an EBI_CS_MODE_t type
 */
static inline void ebi_cs_set_mode(struct ebi_cs_config *config,
		EBI_CS_MODE_t mode)
{
	config->ctrla &= ~EBI_CS_MODE_gm;
	config->ctrla |= mode;
}

/**
 * \brief Set chip select address size
 *
 * This function helps the caller setting the chip select address size. The
 * different sizes are provided by an EBI_CS_ASPACE_t type from the toolchain
 * header files.
 *
 * \param config Pointer to an \ref ebi_cs_config variable
 * \param size Chip select address size given by an EBI_CS_ASPACE_t type
 */
static inline void ebi_cs_set_address_size(struct ebi_cs_config *config,
		EBI_CS_ASPACE_t size)
{
	config->ctrla &= ~EBI_CS_ASPACE_gm;
	config->ctrla |= size;
}

/**
 * \brief Set chip select SRAM wait states
 *
 * This function helps the caller setting the chip select SRAM wait states. The
 * different SRAM wait states (cycles) are provided by an EBI_CS_SRWS_t type
 * from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_cs_config variable
 * \param cycles Chip select SRAM wait states given by an EBI_CS_SRWS_t type
 */
static inline void ebi_cs_set_sram_wait_states(struct ebi_cs_config *config,
		EBI_CS_SRWS_t cycles)
{
	config->ctrlb &= ~EBI_CS_SRWS_gm;
	config->ctrlb |= cycles;
}

/**
 * \brief Set chip select base address
 *
 * This function helps the caller setting the chip select base address, e.g.,
 * the lowest address space enabled by the chip select.
 *
 * \param config Pointer to an \ref ebi_cs_config variable
 * \param address The chip select base address
 */
static inline void ebi_cs_set_base_address(struct ebi_cs_config *config,
		uint32_t address)
{
	config->base_address = (address >> 8) & 0xfff0;
}

//@}

//! \name External Bus Interface SDRAM configuration helper functions
//@{

/**
 * \brief Set SDRAM mode
 *
 * This function helps the caller setting the SDRAM mode. The different modes
 * are provided by an EBI_CS_SDMODE_t type from the toolchain header files.
 *
 * \note This function needs a pointer to an \ref ebi_cs_config struct, not an
 * \ref ebi_sdram_config struct as the other SDRAM configuration helper
 * function does.
 *
 * \param config Pointer to an \ref ebi_cs_config variable
 * \param mode SDRAM mode given by an EBI_CS_SDMODE_t type
 */
static inline void ebi_sdram_set_mode(struct ebi_cs_config *config,
		EBI_CS_SDMODE_t mode)
{
	config->ctrlb &= ~EBI_CS_SDMODE_gm;
	config->ctrlb |= mode;
}

/**
 * \brief Set SDRAM CAS latency
 *
 * This function helps the caller setting the SDRAM CAS latency.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param cas SDRAM CAS latency, 2 or 3
 */
static inline void ebi_sdram_set_cas_latency(struct ebi_sdram_config *config,
		const uint8_t cas)
{
	Assert(cas == 2 || cas == 3);

	if (cas == 3) {
		config->sdramctrla |= EBI_SDCAS_bm;
	} else {
		config->sdramctrla &= ~EBI_SDCAS_bm;
	}
}

/**
 * \brief Set number of SDRAM row bits
 *
 * This function helps the caller setting the number of SDRAM row bits.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param bits Number of row bits, 11 or 12
 */
static inline void ebi_sdram_set_row_bits(struct ebi_sdram_config *config,
		const uint8_t bits)
{
	Assert(bits == 11 || bits == 12);

	if (bits == 12) {
		config->sdramctrla |= EBI_SDROW_bm;
	} else {
		config->sdramctrla &= ~EBI_SDROW_bm;
	}
}

/**
 * \brief Set number of SDRAM column bits
 *
 * This function helps the caller setting the number of SDRAM column bits.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param bits Number of column bits, 8 to 11
 */
static inline void ebi_sdram_set_col_bits(struct ebi_sdram_config *config,
		const uint8_t bits)
{
	Assert(bits >= 8 || bits <= 11);

	config->sdramctrla &= ~EBI_SDCOL_gm;
	config->sdramctrla |= (bits - 8) << EBI_SDCOL_gp;
}

/**
 * \brief Set SDRAM refresh period
 *
 * This function helps the caller setting the SDRAM refresh period as a number
 * of peripheral 2x clock cycles (CLKper2).
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param period SDREAM refresh period, number of CLKper2 cycles
 */
static inline void ebi_sdram_set_refresh_period(
		struct ebi_sdram_config *config, const uint16_t period)
{
	config->refresh_period = period;
}

/**
 * \brief Set SDRAM initialization delay
 *
 * This function helps the caller setting the SDRAM initialization delay as a
 * number of peripheral 2x clock cycles (CLKper2).
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDREAM initialization delay, number of CLKper2 cycles
 */
static inline void ebi_sdram_set_initialization_delay(
		struct ebi_sdram_config *config, const uint16_t delay)
{
	config->init_delay = delay;
}

/**
 * \brief Set SDRAM mode delay
 *
 * This function helps the caller setting the SDRAM mode delay as a number of
 * peripheral 2x clock cycles (CLKper2). The different modes are provided by an
 * EBI_MRDLY_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDRAM mode delay given by an EBI_MRDLY_t type
 */
static inline void ebi_sdram_set_mode_delay(struct ebi_sdram_config *config,
		const EBI_MRDLY_t delay)
{
	config->sdramctrlb &= ~EBI_MRDLY_gm;
	config->sdramctrlb |= delay;
}

/**
 * \brief Set SDRAM row cycle delay
 *
 * This function helps the caller setting the SDRAM row cycle delay as a number
 * of peripheral clock 2x cycles (CLKper2). The different delays are provided
 * by an EBI_ROWCYCDLY_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDRAM row cycle delay given by an EBI_ROWCYCDLY_t type
 */
static inline void ebi_sdram_set_row_cycle_delay(
		struct ebi_sdram_config *config, const EBI_ROWCYCDLY_t delay)
{
	config->sdramctrlb &= ~EBI_ROWCYCDLY_gm;
	config->sdramctrlb |= delay;
}

/**
 * \brief Set SDRAM row to pre-charge delay
 *
 * This function helps the caller setting the SDRAM row to pre-charge delay as
 * a number of peripheral clock 2x cycles (CLKper2). The different delays are
 * provided by an EBI_RPDLY_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDRAM row to pre-charge delay given by an EBI_ROWCYCDLY_t type
 */
static inline void ebi_sdram_set_row_to_precharge_delay(
		struct ebi_sdram_config *config, const EBI_RPDLY_t delay)
{
	config->sdramctrlb &= ~EBI_RPDLY_gm;
	config->sdramctrlb |= delay;
}

/**
 * \brief Set SDRAM write recovery delay
 *
 * This function helps the caller setting the SDRAM write recovery delay as a
 * number of peripheral clock 2x cycles (CLKper2). The different delays are
 * provided by an EBI_WRDLY_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDRAM write recovery delay given by an EBI_WRDLY_t type
 */
static inline void ebi_sdram_set_write_recovery_delay(
		struct ebi_sdram_config *config, const EBI_WRDLY_t delay)
{
	config->sdramctrlc &= ~EBI_WRDLY_gm;
	config->sdramctrlc |= delay;
}

/**
 * \brief Set SDRAM exit self refresh to active delay
 *
 * This function helps the caller setting the SDRAM exit self refresh to active
 * delay as a number of peripheral clock 2x cycles (CLKper2). The different
 * delays are provided by an EBI_ESRDLY_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDRAM exit self refresh to active delay given by an
 *              EBI_ESRDLY_t type
 */
static inline void ebi_sdram_set_self_refresh_to_active_delay(
		struct ebi_sdram_config *config, const EBI_ESRDLY_t delay)
{
	config->sdramctrlc &= ~EBI_ESRDLY_gm;
	config->sdramctrlc |= delay;
}

/**
 * \brief Set SDRAM row to column delay
 *
 * This function helps the caller setting the SDRAM row to column delay as a
 * number of peripheral clock 2x cycles (CLKper2). The different delays are
 * provided by an EBI_ROWCOLDLY_t type from the toolchain header files.
 *
 * \param config Pointer to an \ref ebi_sdram_config variable
 * \param delay SDRAM row to column delay given by an EBI_ROWCOLDLY_t type
 */
static inline void ebi_sdram_set_row_to_col_delay(
		struct ebi_sdram_config *config, const EBI_ROWCOLDLY_t delay)
{
	config->sdramctrlc &= ~EBI_ROWCOLDLY_gm;
	config->sdramctrlc |= delay;
}

//@}

//! \name External Bus Interface SDRAM power management
//@{

/**
 * \brief Enable SDRAM self refresh mode
 *
 * This function makes the EBI hardware send a command to the SDRAM to enter
 * self refresh mode.
 */
static inline void ebi_sdram_enable_self_refresh(void)
{
	irqflags_t      iflags = cpu_irq_save();

	EBI.CS3.CTRLB |= EBI_CS_SDSREN_bm;
	sleepmgr_unlock_mode(SLEEPMGR_IDLE);

	cpu_irq_restore(iflags);
}

/**
 * \brief Disable SDRAM self refresh mode
 *
 * This function makes the EBI hardware send a command to the SDRAM to leave
 * self refresh mode.
 */
static inline void ebi_sdram_disable_self_refresh(void)
{
	irqflags_t      iflags = cpu_irq_save();

	sleepmgr_lock_mode(SLEEPMGR_IDLE);
	EBI.CS3.CTRLB &= ~EBI_CS_SDSREN_bm;

	cpu_irq_restore(iflags);
}

//@}

//! @}

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_EBI_EBI_H */
