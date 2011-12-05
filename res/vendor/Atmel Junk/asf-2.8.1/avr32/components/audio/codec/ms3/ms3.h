/*This file is prepared for Doxygen automatic documentation generation.*/
/*! \file ******************************************************************
 *
 * \brief Bang & Olufsen MS3 header file.
 *
 * - Compiler:           IAR EWAVR32 and GNU GCC for AVR32
 * - Supported devices:  All AVR32 devices can be used.
 * - AppNote:
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 ***************************************************************************/

/* Copyright (C) 2011, Atmel Corporation All rights reserved.
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
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "compiler.h"


// Configuration for the hardware module (TWI or TWIM) depending of the UC3 series
#if (UC3A3 || UC3C || UC3L)
#  define MS3_TWI                  (&AVR32_TWIM0)
#else
#  define MS3_TWI                  (&AVR32_TWI)
#endif

#define MS3_TWI_ADDRESS   (0xDC >> 1)
#define MS3_HP_VOL_L      0x0C
#define MS3_HP_VOL_R      0x0D
#define MS3_SP_VOL_L      0x0A
#define MS3_SP_VOL_R      0x0B
#define MS3_MUTE_VOL_CTRL 0x0E
#define MS3_LEFT_CHANNEL  1
#define MS3_RIGHT_CHANNEL 2
#define MS3_VOL_MIN       0x30
#define MS3_VOL_MAX       0xA8
#define MS3_VOL_STEP      3

extern void ms3_dac_start(U32 sample_rate_hz,
                             U8 num_channels,
                             U8 bits_per_sample,
                             bool swap_channels,
                             void (*callback)(U32 arg),
                             U32 callback_opt,
                             U32 pba_hz);


extern void ms3_dac_setup(U32 sample_rate_hz,
                             U8 num_channels,
                             U8 bits_per_sample,
                             bool swap_channels,
                             void (*callback)(U32 arg),
                             U32 callback_opt,
                             U32 pba_hz);

extern bool ms3_dac_output(void *sample_buffer, size_t sample_length);

extern void ms3_dac_increase_volume(void);

extern void ms3_dac_decrease_volume(void);

extern void ms3_dac_flush(void);

extern void ms3_dac_stop(void);

extern void ms3_dac_set_volume(U8 volume);

extern U8 ms3_dac_get_volume(void);

extern bool ms3_dac_is_volume_boosted(void);

extern void ms3_dac_mute(bool mute);

extern bool ms3_dac_is_volume_muted(void);
