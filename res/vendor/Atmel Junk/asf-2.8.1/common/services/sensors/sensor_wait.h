/**
 * \file
 *
 * \brief AVR functions for busy-wait delay loops
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
 
#ifndef _sensor_wait_h_
#define _sensor_wait_h_

#ifdef __cplusplus
extern "C" {
#endif


#if defined(UC3)
#	include <cycle_counter.h>
#elif defined(XMEGA)

//! \brief Delays program execution for \a n processor cycles.

__always_optimize
static inline void __portable_avr_delay_cycles(uint32_t n)
{
	do { barrier(); } while (--n);
}

#if !defined(__DELAY_CYCLE_INTRINSICS__)
#	define delay_cycles            __portable_avr_delay_cycles
#	define cpu_ms_2_cy(ms, f_cpu)  (((uint64_t)(ms) * (f_cpu) + 999) / 6e3)
#	define cpu_us_2_cy(us, f_cpu)  (((uint64_t)(us) * (f_cpu) + 999999ul) / 6e6)
#else
#  if defined(__GNUC__)
#	define delay_cycles            __builtin_avr_delay_cycles
#  elif defined(__ICCAVR__)
#	define delay_cycles            __delay_cycles
#  endif
#	define cpu_ms_2_cy(ms, f_cpu)  (((uint64_t)(ms) * (f_cpu) + 999) / 1e3)
#	define cpu_us_2_cy(us, f_cpu)  (((uint64_t)(us) * (f_cpu) + 999999ul) / 1e6)
#endif

#define cpu_delay_ms(delay, f_cpu) delay_cycles(cpu_ms_2_cy(delay, f_cpu))
#define cpu_delay_us(delay, f_cpu) delay_cycles(cpu_us_2_cy(delay, f_cpu))

#endif


#ifdef __cplusplus
}
#endif

#endif /* _sensor_wait_h_ */
