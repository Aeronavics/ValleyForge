/**
 * \file
 *
 * \brief AVR XMEGA Liquid Crystal Display driver.
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

#ifndef _LCD_H_
#define _LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "compiler.h"
#include <sleepmgr.h>

/**
 * \defgroup lcd_group Liquid Crystal Display (LCD)
 *
 * This is a driver for configuring, enabling/disabling and use of the on-chip
 * LCD controller.
 *
 * \section dependencies Dependencies
 *
 * The LCD module depends on the following modules:
 * - \ref sysclk_group for LCD clock control.
 * - \ref interrupt_group for enabling or disabling interrupts.
 * - \ref sleepmgr_group to unlock LCD controller
 * @{
 */


/**
 * \brief Interrupt event callback function type
 *
 * The interrupt handler can be configured to do a function callback,
 * the callback function must match the lcd_callback_t type.
 *
 */
typedef void (*lcd_callback_t) (void);


//! \name LCD addressing limits
//@{
//! Maximum number of common lines.
#define LCD_MAX_NR_OF_COM  4
//! Maximum number of segment lines.
#if XMEGA_B1
# define LCD_MAX_NBR_OF_SEG  40
#elif XMEGA_B3
# define LCD_MAX_NBR_OF_SEG  25
#else
# error Unsupported part family.
#endif

//@}


//! Clock Source for the LCD
enum lcd_clk_source {
	//! 32.768 kHz from internal 32kHz ULP
	CLK_LCD_SRC_ULP_gc     = (0x00 << CLK_RTCSRC_gp),
	//! 32.768 kHz from 32.768 kHz crystal oscillator on TOSC
	CLK_LCD_SRC_TOSC_gc    = (0x01 << CLK_RTCSRC_gp),
	//! 32.768 kHz from internal 32.768 kHz RC OSC
	CLK_LCS_DRC_RCOSC_gc   = (0x02 << CLK_RTCSRC_gp),
	//! 32.768 kHz from 32.768 kHz crystal oscillator on TOSC
	CLK_LCD_SRC_TOSC32_gc  = (0x05 << CLK_RTCSRC_gp),
	//! 32.768 kHz from internal 32.768 kHz RC OSC
	CLK_LCD_SRC_RCOSC32_gc = (0x06 << CLK_RTCSRC_gp),
	//! External Clock from TOSC1
	CLK_LCD_SRC_EXTCLK_gc  = (0x07 << CLK_RTCSRC_gp),
};


//! Low Power Waveform for the LCD
enum lcd_lp_waveform {
	//! Low Power Waveform disabled
	LCD_LP_WAVE_DISABLE_gc = (0x00 << LCD_LPWAV_bp),
	//! Low Power Waveform enabled
	LCD_LP_WAVE_ENABLE_gc  = (0x01 << LCD_LPWAV_bp)
};

//! LCD Interrupt level
enum lcd_int_level {
	//! Interrupt disabled
	LCD_INTLVL_OFF_gc   = (0x00 << LCD_FCINTLVL_gp),
	//! Low level
	LCD_INTLVL_LO_gc    = (0x01 << LCD_FCINTLVL_gp),
	//! Medium level
	LCD_INTLVL_MED_gc   = (0x02 << LCD_FCINTLVL_gp),
	//! High level
	LCD_INTLVL_HI_gc    = (0x03 << LCD_FCINTLVL_gp),
#ifdef CONFIG_XMEGA_128B1_REVA
	//! Extended interrupt mode, interrupt disabled
	LCD_X_INTLVL_OFF_gc = (1 << LCD_XIME0_bp) | (0x00 << LCD_FCINTLVL_gp),
	//! Extended interrupt mode, low level
	LCD_X_INTLVL_LO_gc  = (1 << LCD_XIME0_bp) | (0x01 << LCD_FCINTLVL_gp),
	//! Extended interrupt mode, medium level
	LCD_X_INTLVL_MED_gc = (1 << LCD_XIME0_bp) | (0x02 << LCD_FCINTLVL_gp),
	//! Extended interrupt mode, high level
	LCD_X_INTLVL_HI_gc  = (1 << LCD_XIME0_bp) | (0x03 << LCD_FCINTLVL_gp),
#endif
};


/**
 * \brief LCD clock initialization.
 *
 * This function enables the LCD clock.
 *
 * The function enables the LCD input clock.
 * Then the module source clock for the LCD will be the same than for the RTC.
 * In the same time, the LCD power reduction bit is cleared.
 *
 * \param  lcd_clk_source  Clock source to use for the LCD.
 *
 */
static inline void lcd_clk_init(enum lcd_clk_source lcd_clk_source)
{
	// Enable sys clock for LCD Module
	PR.PRGEN &= ~PR_LCD_bm;
	CLK.RTCCTRL = (uint8_t)((CLK.RTCCTRL & ~CLK_RTCSRC_gm)
			| (lcd_clk_source | CLK_RTCEN_bm));
}


/**
 * \brief LCD glass connection initialization.
 *
 * This function sets the LCD glass connection.
 *
 * The function enables COM & SEG swapping, LCD port mask and the using (or no)
 * of an External Resistor Bias Generation. This function also clears
 * all the display memory (=> all pixels "off") and lets the LCD disabled.
 *
 * \param  com_swp   COM swapping (false: no swapping, true: COM swapping).
 * \param  seg_swp   SEG swapping (false: no swapping, true: SEG swapping).
 * \param  port_mask Number of SEG used.
 * \param  x_bias    External bias (false: internal gen., true: external gen.).
 */
static inline void lcd_connection_init(bool com_swp, bool seg_swp,
		uint8_t port_mask, bool x_bias)
{
	LCD.CTRLA = (com_swp ? LCD_COMSWP_bm : 0)
			| (seg_swp ? LCD_SEGSWP_bm : 0)
			| (x_bias ? LCD_XBIAS_bm : 0) | LCD_CLRDT_bm;
	LCD.CTRLC = (port_mask << LCD_PMSK_gp) & LCD_PMSK_gm;
}


/**
 * \brief LCD timing initialization.
 *
 * This function enables the LCD timing.
 *
 * The function sets the prescaler, the dividor and the duty cycle of the LCD.
 *
 * \param  lcd_pres    prescaler of the clock source.
 * \param  lcd_clkdiv  Divider of the prescaled clock source.
 * \param  lcd_lp_wave type of waveform, low power or default waveform.
 * \param  lcd_duty    duty cycle (operating mode) applied to the LCD.
 *
 * Timing setup examples with input clock rate 32.768 kHz, for different LCD
 * operating frequencies:
 * - 256 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy1_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 128 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy2_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 85.3 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy3_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 64 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy4_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 51.2 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy5_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 42.7 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy6_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 36.6 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy7_gc | LCD_DUTY_1_4_gc
 * \endcode
 * - 32 Hz:
 * \code
 * LCD.CTRB = LCD_PRESC_16_gc | LCD_CLKDIV_DivBy8_gc | LCD_DUTY_1_4_gc
 * \endcode
 */
static inline void lcd_timing_init(enum LCD_PRESC_enum lcd_pres,
		enum LCD_CLKDIV_enum lcd_clkdiv,
		enum lcd_lp_waveform lcd_lp_wave,
		enum LCD_DUTY_enum lcd_duty)
{
	LCD.CTRLB = ((uint8_t)lcd_pres) | ((uint8_t)lcd_clkdiv)
			| ((uint8_t)lcd_lp_wave) | ((uint8_t)lcd_duty);
}


/*! \brief LCD interrupt initialization.
 *
 *  This function sets the interrupt behaviour.
 *
 *  The function defines the interrupt level and sets the number of frames
 *  between 2 interrupts. Note that this function takes care of the waveform
 *  type (default or low power waveform) so 'lcd_timing_init()' function must
 *  be called before. 
 *
 *  \param  int_level    LCD module interrupt level.
 *  \param  frame_count  Number of frames between 2 interrupts.
 *                       (2 <= frame_count <= 64 for low power waveform)
 *                       (1 <= frame_count <= 32 for default waveform)
 */
static inline void lcd_interrupt_init(enum lcd_int_level int_level, uint8_t frame_count)
{
	LCD.INTCTRL = (int_level << LCD_FCINTLVL0_bp);
	
#ifndef CONFIG_XMEGA_128B1_REVA  // XMEGA_B rev. higher than revA
	if (LCD.CTRLB & LCD_LPWAV_bm) {
		frame_count >>= 1;
	}
	if (frame_count != 0) {
		frame_count -= 1;
	}
	if (frame_count > 31) {
		frame_count = 31;
	}
	LCD.INTCTRL |= (frame_count << LCD_XIME0_bp);
#endif
}


/**
 * \brief LCD blinking initialization.
 *
 * This function sets the frequency of the hardware display blinking.
 *
 * The function defines the blinking rate. In the same time, the hardware
 * display blinking is disabled.
 *
 * \param  lcd_blink_rate  Hardware display blinking frequency.
 */
static inline void lcd_blinkrate_init(enum LCD_BLINKRATE_enum lcd_blink_rate)
{
	LCD.CTRLD = (uint8_t)((LCD.CTRLD & ~LCD_BLINKRATE_gm) | lcd_blink_rate);
}


/**
 * \brief Set the LCD contrast.
 *
 * This function finely sets the LCD contrast.
 *
 * Transfer function: VLCD = 3.0 V + (fcont[5:0] * 0.016 V)
 *
 * \param  fcont  -32 <= signed contrast value <= 31.
 */
static inline void lcd_set_contrast(int8_t fcont)
{
	if (fcont > ((int8_t)(LCD_FCONT_gm >> 1))) {
		LCD.CTRLF = LCD_FCONT_gm >> 1;
	} else if (fcont < ((int8_t)(((~LCD_FCONT_gm) >> 1) | 0x80))) {
		LCD.CTRLF = ((~LCD_FCONT_gm) >> 1) | 0x80;
	} else {
		LCD.CTRLF = fcont;
	}
}


/**
 * \brief Enable LCD.
 *
 * This function enables the LCD module.
 */
static inline void lcd_enable(void)
{
	sleepmgr_lock_mode(SLEEPMGR_PSAVE);
	LCD.CTRLA |= (1 << LCD_ENABLE_bp) | (1 << LCD_SEGON_bp);
}


/**
 * \brief Disable LCD.
 *
 * This function disables the LCD module.
 *
 */
static inline void lcd_disable(void)
{
	sleepmgr_unlock_mode(SLEEPMGR_PSAVE);
	LCD.CTRLA &= ~(1 << LCD_ENABLE_bp);
}


/**
 * \brief Set the blinking of pixels.
 *
 * This function sets the blinking of pixels in LCD module on SEG0 & SEG1.
 * Each bit position corresponds to one pixel.
 *
 * \param  pix_com  Pixel coordinate - COMx - of the pixel (icon).
 * \param  pix_seg  Pixel coordinate - SEGy - of the pixel (icon).
 *
 */
static inline void lcd_set_blink_pixel(uint8_t pix_com, uint8_t pix_seg)
{
	LCD.CTRLE |= 1 << ((LCD_BPS10_bp * pix_seg) + pix_com);
}

/**
 * \brief Clear the blinking of pixels.
 *
 * This function clears the blinking of pixels in LCD module on SEG0 & SEG1.
 * Each bit position corresponds to one pixel.
 *
 * \param  pix_com  Pixel coordinate - COMx - of the pixel (icon).
 * \param  pix_seg  Pixel coordinate - SEGy - of the pixel (icon).
 *
 */
static inline void lcd_clear_blink_pixel(uint8_t pix_com, uint8_t pix_seg)
{
	LCD.CTRLE &= ~(1 << ((LCD_BPS10_bp * pix_seg) + pix_com));
}

/**
 * \brief Clear the blinking of all pixels.
 *
 * This function clears the blinking of all pixels in LCD module on SEG0 & SEG1.
 *
 */
static inline void lcd_clear_blink_all_pixel(void)
{
	LCD.CTRLE = 0;
}

/**
 * \brief LCD blink enable.
 *
 * This function enables the blinking mode in LCD module.
 */
static inline void lcd_blink_enable(void)
{
	// Blinking "on"
	LCD.CTRLD |= 1 << LCD_BLINKEN_bp;
}


/**
 * \brief LCD blink disable.
 *
 * This function disables the blinking mode in LCD module.
 */
static inline void lcd_blink_disable(void)
{
	// Blinking "off"
	LCD.CTRLD &= ~LCD_BLINKEN_bm;
}


/**
 * \brief LCD frame interrupt callback function
 *
 * This function allows the caller to set and change the interrupt callback
 * function. Without setting a callback function the interrupt handler in the
 * driver will only clear the interrupt flags.
 *
 * \param callback Reference to a callback function
 */
void lcd_set_frame_interrupt_callback(lcd_callback_t callback);


/**
 * \brief Send a sequence of ASCII characters to LCD device.
 *
 * This function enables/disables LCD pixels via the digit decoder.
 *
 * \param  lcd_tdg    Type of digit decoder.
 * \param  first_seg  First SEG where the first data will be writen.
 * \param  data       Data buffer.
 * \param  width      Number of data.
 * \param  dir        Direction (==0: Left->Right, !=0: Left<-Right).
 */
void lcd_write_packet(enum LCD_TDG_enum lcd_tdg, uint8_t first_seg,
		const uint8_t *data, size_t width, uint8_t dir);


/*! \brief Wait for n interrupt periods.
 *
 *  This function counts interrupt periods and returns when the count is
 *  reached. This function only runs if LCD interrupt is disabled.
 *
 *  \param  n_int  Number of interrupt periods.
 */
void lcd_wait_n_int(uint8_t n_int);


/**
 * \brief Set pixel (icon) in LCD display memory.
 *
 * This function sets a pixel in LCD (icon) display memory. If a parameter
 * is out of range, then the function doesn't set any bit.
 *
 * \param  pix_com  Pixel coordinate - COMx - of the pixel (icon).
 * \param  pix_seg  Pixel coordinate - SEGy - of the pixel (icon).
 */
void lcd_set_pixel(uint8_t pix_com, uint8_t pix_seg);


/**
 * \brief Clear pixel (icon) in LCD display memory.
 *
 * This function clears a pixel in LCD (icon) display memory. If a parameter
 * is out of range, then the function doesn't clear any bit.
 *
 * \param  pix_com  Pixel coordinate - COMx - of the pixel (icon).
 * \param  pix_seg  Pixel coordinate - SEGy - of the pixel (icon).
 */
void lcd_clear_pixel(uint8_t pix_com, uint8_t pix_seg);


/**
 * \brief Toggle pixel (icon) in LCD display memory.
 *
 * This function toggles a pixel in LCD (icon) display memory. If a parameter
 * is out of range, then the function doesn't toggle any bit.
 *
 * \param  pix_com  Pixel coordinate - COMx - of the pixel (icon).
 * \param  pix_seg  Pixel coordinate - SEGy - of the pixel (icon).
 */
void lcd_tgl_pixel(uint8_t pix_com, uint8_t pix_seg);


/**
 * \brief Get pixel value (icon) in LCD display memory.
 *
 * This function returns the pixel value in LCD (icon) display memory.
 *
 * \param  pix_com  Pixel coordinate - COMx - of the pixel (icon).
 * \param  pix_seg  Pixel coordinate - SEGy - of the pixel (icon).
 */
bool lcd_get_pixel(uint8_t pix_com, uint8_t pix_seg);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // _LCD_H_


