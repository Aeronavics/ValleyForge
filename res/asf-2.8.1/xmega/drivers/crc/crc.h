/**
 * \file
 *
 * \brief Cyclic Redundancy Check module driver
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
#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#include <compiler.h>
#include <stdint.h>
#include <stdbool.h>
#include <nvm.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup crc_group CRC module driver
 * \brief Low-level driver implementation for the AVR XMEGA AU Cyclic
 * Redundancy Check (CRC) module.
 *
 * A cyclic redundancy check (CRC) is an error detection technique test
 * algorithm used to find accidental errors in data, and it is commonly used to
 * determine the correctness of a data transmission, and data present in the
 * data and program memories. The CRC module takes a data stream or a block of
 * data as input and generates a 16- or 32-bit output that can be appended to
 * the data and used as a checksum. When the same data are later received or
 * read, the device or application can either repeat the calculation for the
 * data with the appended checksum, which should result in the checksum zero
 * flag being set. The other option is to calculate the checksum and compare it
 * to the one calculated earlier.
 * If the new CRC result does not match the one calculated earlier or zero, the
 * block contains a data error. The application is then able to the detect this
 * and may take a corrective action, such as requesting the data to be sent
 * again or simply not using the incorrect data.
 * The CRC module in XMEGA devices supports two commonly used CRC polynomials;
 * CRC-16 (CRC-CCITT) and CRC-32 (IEEE 802.3).
 *
 */
//! @{

//! Perform a CRC calculation on an address range in flash
#define CRC_FLASH_RANGE    NVM_CMD_FLASH_RANGE_CRC_gc
//! Perform a CRC calculation on the application section
#define CRC_BOOT           NVM_CMD_BOOT_CRC_gc
//! Perform a CRC calculation on the boot loader section
#define CRC_APP            NVM_CMD_APP_CRC_gc

//! Enum to indicate wether to use CRC-16 or CRC-32
enum crc_16_32_t {
	CRC_16BIT,
	CRC_32BIT,
};

void crc_set_initial_value(uint32_t value);

void crc32_append_value(uint32_t value, void *ptr);
void crc16_append_value(uint16_t value, void *ptr);

uint32_t crc_flash_checksum(NVM_CMD_t crc_type, flash_addr_t
		flash_addr, uint32_t len);

uint32_t crc_io_checksum(void *data, uint16_t len,
		enum crc_16_32_t crc_16_32);

void crc_io_checksum_byte_start(enum crc_16_32_t crc_16_32);
void crc_io_checksum_byte_add(uint8_t data);
uint32_t crc_io_checksum_byte_stop(void);

void crc_dma_checksum_start(uint8_t dma_channel, enum crc_16_32_t crc_16_32);
uint32_t crc_dma_checksum_stop(void);
//! @}

#ifdef __cplusplus
}
#endif

#endif /* CRC_H_INCLUDED */
