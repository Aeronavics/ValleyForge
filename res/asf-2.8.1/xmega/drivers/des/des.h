/**
 * \file
 *
 * \brief AVR XMEGA Data Encryption Standard (DES) driver
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
#ifndef DES_H
#define DES_H

#include <compiler.h>
/**
 * \defgroup des_group Data Encryption Standard (DES)
 *
 * This is a driver for the AVR XMEGA DES core instruction. It provides
 * functions for des, 3des and CBC des encryption and dectyption operations.
 *
 * \section des_satrt_condition DES Start Setting
 * DES is supported by a DES instruction in the AVR XMEGA core. The 8-byte key
 * and 8-byte data blocks must be loaded into the Register file, and then DES
 * must be executed 16 times to encrypt/decrypt the data block.
 *
 * \note The functions for loading configurations/data/key are not protected
 * against interrupts.
 *
 * @{
 */

/**
 *  \brief  Function that does a DES decryption on one 64-bit data block.
 *
 *  \param  ciphertext  Pointer to the ciphertext that shall be decrypted.
 *  \param  plaintext   Pointer to where in memory the plaintext (answer) shall be stored.
 *  \param  key         Pointer to the DES key.
 *
 */
void des_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t *key);


/**
 *  \brief  Function that does a DES encryption on one 64-bit data block.
 *
 *  \param  plaintext  Pointer to the plaintext that shall be encrypted.
 *  \param  ciphertext Pointer to where in memory the ciphertext (answer) shall be stored.
 *  \param  key        Pointer to the DES key.
 *
 */
void des_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key);


/**
 *  \brief  Function that does a 3DES encryption on one 64-bit data block.
 *
 *  \param  plaintext   Pointer to the plaintext that shall be encrypted.
 *  \param  ciphertext  Pointer to where in memory the ciphertext (answer) shall be stored.
 *  \param  keys        Pointer to the array of the 3 DES keys.
 *
 */
void des_3des_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *keys);


/**
 *  \brief  Function that does a 3DES decryption on one 64-bit data block.
 *
 *  \param  ciphertext  Pointer to the ciphertext that shall be decrypted.
 *  \param  plaintext   Pointer to where in memory the plaintext (answer) shall be stored.
 *  \param  keys        Pointer to the array of the 3 DES keys.
 *
 */
void des_3des_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t *keys);


/**
 *  \brief  Function that does DES Cipher Block Chaining encryption on a
 *          given number of 64-bit data block.
 *
 *  \param   plaintext    Pointer to the plaintext that shall be encrypted.
 *  \param   ciphertext   Pointer to where in memory the ciphertext(answer) shall be stored.
 *  \param   keys         Pointer to the array of the one or three DES keys needed.
 *  \param   init         Pointer to initial vector used in in CBC.
 *  \param   triple_DES   Bool that indicate if 3DES or DES shall be used.
 *  \param   block_length Value that tells how many blocks to encrypt.
 *
 */
void des_cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext,
                     uint8_t *keys, uint8_t *init,
                     bool triple_DES, uint16_t block_length);


/**
 *  \brief  Function that does DES Cipher Block Chaining decryption on a
 *          given number of 64-bit data block.
 *
 *  \param   ciphertext    Pointer to the ciphertext that shall be decrypted.
 *  \param   plaintext     Pointer to where in memory the plaintext (answer) shall be stored.
 *  \param   keys          Pointer to the array of the one or three DES keys needed.
 *  \param   init          Pointer to initial vector used in in CBC.
 *  \param   triple_DES    Bool that indicate if 3DES or DES shall be used.
 *  \param   block_length  Value that tells how many blocks to encrypt.
 *
 *  \note    The pointer to the ciphertext and plaintext must not be the same
 *           because the CBC algorithm uses previous values of the ciphertext
 *           to calculate the plaintext.
 */
void des_cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext,
                     uint8_t *keys, uint8_t *init,
                     bool triple_DES, uint16_t block_length);

/* @}*/

#endif /* DES_H */

