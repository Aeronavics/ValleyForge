/**
 * \file
 *
 * \brief AVR XMEGA Advanced Encryption Standard (AES) driver
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
#ifndef AES_H
#define AES_H

#include <compiler.h>
/**
 * \defgroup aes_group Advanced Encryption Standard (AES)
 *
 * This is a driver for the AVR XMEGA AES crypto module. It provides functions
 * for configuring the AES modules, reseting and starting AES encryption and
 * dectyption operations.
 *
 * \note
 * 1. After the AES has been configured, data and key must be loaded into register
 * before any operations can be done.\n
 * 2. The functions for loading configurations/data/key are not protected
 * against interrupts.
 *
 * @{
 */

/**
 * \name AES Configuration Define
 *
 * @{
 */

/**
 * \brief Length of one key block.
 * Always 128-bits (16 bytes).
 */
#define AES_KEY_SIZE	16

//! AES key block type
typedef uint8_t t_key[AES_KEY_SIZE];

/**
 * \brief Length of one data block.
 * Always 128-bits (16 bytes).
 */
#define AES_DATA_SIZE	16

//! AES data block type
typedef uint8_t t_data[AES_DATA_SIZE];

//! AES encryption/decryption direction settings
enum aes_dec{
	AES_ENCRYPT,                     //!< encryption.
	AES_DECRYPT = AES_DECRYPT_bm,    //!< decryption.
};

//! AES Auto Start Trigger settings
enum aes_auto{
	AES_MANUAL,                      //!< manual start mode.
	AES_AUTO = AES_AUTO_bm,          //!< auto start mode.
};

//! AES State XOR Load Enable settings
enum aes_xor{
	AES_XOR_OFF,                    //!< state direct load.
	AES_XOR_ON = AES_XOR_bm,        //!< state XOR load.
};

//! AES Interrupt Enable / Level settings
enum aes_intlvl{
	AES_INTLVL_OFF = AES_INTLVL_OFF_gc,  //!< Interrupt Disabled
	AES_INTLVL_LO  = AES_INTLVL_LO_gc,   //!< Low Level
	AES_INTLVL_MED = AES_INTLVL_MED_gc,  //!< Medium Level
	AES_INTLVL_HI  = AES_INTLVL_HI_gc,   //!< High Level
};

//! AES interrupt callback function pointer.
typedef void (*aes_callback_t)(void);

/** @} */

/**
 * \name AES Function Define
 *
 * @{
 */

//! This function starts a decryption/encryption.
static inline void aes_start(void)
{
	AES.CTRL |= AES_START_bm;
}
//! This function resets all registers in AES module.
static inline void aes_software_reset(void)
{
	AES.CTRL = AES_RESET_bm;
}

void aes_configure(enum aes_dec decrypt, enum aes_auto _start,
	enum aes_xor xor);

void aes_set_key(t_key k_in);

void aes_get_key(t_key k_out);

void aes_write_inputdata(t_data d_in);

void aes_read_outputdata(t_data d_out);

void aes_isr_configure(enum aes_intlvl intlvl);

void aes_set_callback(aes_callback_t callback);

/** @} */

/** @} */

#endif  // AES_H

