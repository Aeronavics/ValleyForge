/**
 * \file
 *
 * \brief AVR UC3 IISC drivers
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
#include "compiler.h"
#include "iisc.h"

/**
 * \internal
 * \brief IISC Tx Mode Enable
 */
bool tx_is_enabled = false;

/**
 * \internal
 * \brief IISC Rx Mode Enable
 */
bool rx_is_enabled = false;

/**
 * \internal
 * \brief IISC Master Mode Enable
 */
bool is_master = false;

/*! \brief Sets up registers and intializes IISC for use as I2S.
 *
 *  \param iisc Pointer to the correct volatile avr32_iisc_t struct
 *  \param iisc_opt Option structure for IISC Configuration.
 *  \return Status
 *    \retval IISC_OK when no error occured.
 *    \retval IISC_ERROR_ARGUMENT when invalid arguments are passed
 */
status_code_t iisc_init(volatile avr32_iisc_t *iisc,
		iisc_opt_t iisc_opt)
{
	unsigned int mr = 0;

	iisc_reset(iisc);

	// In case IISC Master or IISC Slave Mode is selected
	if ((iisc_opt.mode == IISC_MODE_MASTER) || 
	(iisc_opt.mode == IISC_MODE_SLAVE)) {
		mr = (AVR32_IISC_MR_IMCKMODE_IMCK <<
				AVR32_IISC_MR_IMCKMODE_OFFSET)
				| (AVR32_IISC_MR_TXSAME_SAME <<
				AVR32_IISC_MR_TXSAME_OFFSET)
				| (AVR32_IISC_MR_TXDMA_SINGLE <<
				AVR32_IISC_MR_TXDMA_OFFSET)
				| (AVR32_IISC_MR_RXLOOP_OFF <<
				AVR32_IISC_MR_RXLOOP_OFFSET)
				| (AVR32_IISC_MR_RXDMA_SINGLE <<
				AVR32_IISC_MR_RXDMA_OFFSET)
				| ( 1 <<  /* stereo: 2 channels -1 */ 
				AVR32_IISC_NBCHAN_OFFSET)
				| iisc_opt.option;
		if (iisc_opt.mode == IISC_MODE_MASTER) {
			is_master = true, mr |=
					(AVR32_IISC_MR_MODE_MASTER <<
					AVR32_IISC_MR_MODE_OFFSET);
		}else {
			is_master = false;
		}
		switch (iisc_opt.num_tx_channels) {
			case 1:
				tx_is_enabled = true;
				mr |= AVR32_IISC_MR_TXMONO_MONO << AVR32_IISC_MR_TXMONO_OFFSET;
				break;
			case 2:
				tx_is_enabled = true;
				mr &= ~ AVR32_IISC_MR_TXMONO_MASK;
				mr |= AVR32_IISC_MR_TXMONO_STEREO << AVR32_IISC_MR_TXMONO_OFFSET;
				break;
			default:
				tx_is_enabled = false;
				break;
		}
		switch (iisc_opt.num_rx_channels) {
			case 1:
				rx_is_enabled = true;
				mr |= AVR32_IISC_MR_RXMONO_MONO << AVR32_IISC_MR_RXMONO_OFFSET;
				break;
			case 2:
				rx_is_enabled = true;
				mr &= ~ AVR32_IISC_MR_RXMONO_MASK;
				mr |= AVR32_IISC_MR_RXMONO_STEREO << AVR32_IISC_MR_RXMONO_OFFSET;
				break;
			default:
				rx_is_enabled = false;
				break;
		}
	}
	// In case TDM Mode is selected
	else {
		if (iisc_opt.num_tx_channels != iisc_opt.num_rx_channels) {
			return ERR_INVALID_ARG;
		}
		mr = (AVR32_IISC_MR_IMCKMODE_IMCK <<
				AVR32_IISC_MR_IMCKMODE_OFFSET)
				| (AVR32_IISC_MR_TXSAME_ZERO <<
				AVR32_IISC_MR_TXSAME_OFFSET)
				| (AVR32_IISC_MR_TXDMA_SINGLE <<
				AVR32_IISC_MR_TXDMA_OFFSET)
				| (AVR32_IISC_MR_RXLOOP_OFF <<
				AVR32_IISC_MR_RXLOOP_OFFSET)
				| (AVR32_IISC_MR_RXDMA_SINGLE <<
				AVR32_IISC_MR_RXDMA_OFFSET)
				| (AVR32_IISC_MR_FORMAT_TDM <<
				AVR32_IISC_MR_FORMAT_OFFSET)
				| (iisc_opt.num_tx_channels << AVR32_IISC_MR_NBCHAN_OFFSET)
				| iisc_opt.option;
		if (iisc_opt.mode == IISC_MODE_TDM_MASTER) {
			mr |= (AVR32_IISC_MR_MODE_MASTER <<
					AVR32_IISC_MR_MODE_OFFSET);
		} else {
			mr |= (AVR32_IISC_MR_MODE_SLAVE <<
					AVR32_IISC_MR_MODE_OFFSET);
		}
		tx_is_enabled = true;
		rx_is_enabled = true;
		is_master = true;
	}
	iisc->mr = mr;
	iisc->ier = 0;

	return STATUS_OK;
}

/*! \brief IISC Enable function
 *
 *  \param iisc Pointer to the correct volatile avr32_iisc_t struct
 *
 */
void iisc_enable(volatile avr32_iisc_t *iisc)
{
	if (tx_is_enabled == true) {
		iisc_enable_transmission(iisc);
	}
	if (rx_is_enabled == true) {
		iisc_enable_reception(iisc);
	}
	if (is_master == true) {
		iisc_enable_master(iisc);
	}
}

/*! \brief IISC Disable function
 *
 *  \param iisc Pointer to the correct volatile avr32_iisc_t struct
 *
 */
void iisc_disable(volatile avr32_iisc_t *iisc)
{
	if (tx_is_enabled == true) {
		iisc_disable_transmission(iisc);
	}
	if (rx_is_enabled == true) {
		iisc_disable_reception(iisc);
	}
	if (is_master == true) {
		iisc_enable_slave(iisc);
	}
}

/*! \brief Write a single message of data
 *
 *  \param iisc Pointer to the correct volatile avr32_iisc_t struct
 *  \param data The data to write
 *
 *  \return Status
 *    \retval IISC_OK when no error occured.
 *    \retval IISC_TIMEOUT when a timeout occured while trying to transfer
 */
status_code_t iisc_write(volatile avr32_iisc_t *iisc, uint32_t data)
{
	unsigned int timeout = IISC_RETRY_VALUE;

	while (!(iisc->sr & AVR32_IISC_SR_TXRDY_MASK) && timeout) {
		--timeout;
	}

	if (timeout == 0) {
		return ERR_TIMEOUT;
	}

	iisc->thr = data;

	return STATUS_OK;
}

/*! \brief Read a single message of data
 *
 *  \param iisc Pointer to the correct volatile avr32_iisc_t struct
 *  \param *data The data to read
 *
 *  \return Status
 *    \retval IISC_OK when no error occured.
 *    \retval IISC_TIMEOUT when a timeout occured while trying to transfer
 */
status_code_t iisc_read(volatile avr32_iisc_t *iisc, uint32_t *data)
{
	unsigned int timeout = IISC_RETRY_VALUE;

	while (!(iisc->sr & AVR32_IISC_SR_RXRDY_MASK) && timeout) {
		--timeout;
	}

	if (timeout == 0) {
		return ERR_TIMEOUT;
	}

	*data = iisc->rhr;

	return STATUS_OK;
}

/*! \brief Disables the specified IISC interrupts.
 *
 * \param iisc Base address of the IISC instance.
 * \param int_mask Bit-mask of IISC interrupts (\c AVR32_IDR_x_MASK).
 */
void iisc_disable_interrupts(volatile avr32_iisc_t *iisc,
		unsigned long int_mask)
{
	irqflags_t      iflags;
	iflags = cpu_irq_save();
	iisc->idr = int_mask;
	// Read back the SR register
	iisc->sr;
	cpu_irq_restore(iflags);
}

/*! \brief Enables the specified IISC interrupts.
 *
 * \param iisc Base address of the IISC instance.
 * \param int_mask Bit-mask of IISC interrupts (\c AVR32_IER_x_MASK).
 */
void iisc_enable_interrupts(volatile avr32_iisc_t *iisc,
		unsigned long int_mask)
{
	iisc->ier = int_mask;
}

/*! \brief Returns the IISC status.
 *
 * \param iisc Base address of the IISC instance.
 *
 * \return The IISC Status Register.
 */
unsigned long iisc_get_status(volatile avr32_iisc_t *iisc)
{
	return iisc->sr;
}
