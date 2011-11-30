/**
 * \file
 *
 * \brief NHD C12832 A1Z Monochrome LCD display graphic library glue
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

#include "gfx_mono_sdl.h"

static void gfx_mono_init(void)
{
}
/*
	uint8_t readback;

    // Make sure data read does not auto-increment address, so that we can read-modify-write.
    S6B1713_SetReadModifyWriteOn();

	// Set starting address.
    S6B1713_SetPageAddress( y >> 3);
    S6B1713_SetColumnAddress( x );

    // A dummy read is required after column address setup
    volatile uint8_t dummy = S6B1713_ReadData(); 

	// Read 8-pixel high column, modify correct pixel and write back.
    readback = S6B1713_ReadData(); 
    S6B1713_WriteData( readback | (1 << (y & 0x07)) );
*/


void gfx_mono_framebuffer_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_coord_t color)
{
	uint8_t page;
	uint8_t column;
	uint8_t temp;
	uint8_t pixelmask;

	printf("Putting pixel:\t\t x=%d\ty=%d\n",x,y);
	// Sanity checks
	if ((x < 0) || (x > GFX_MONO_LCD_WIDTH-1) || (y < 0) ||\
			(y > GFX_MONO_LCD_HEIGHT-1)) {
		return;
	}

	page = y / 8;
	pixelmask = (1 << (y - (page * 8)));

	// Read single byte from LCD controller or framebuffer
	//gfx_mono_get_page(&temp, page, column, 1);
	temp = gfx_mono_get_byte(page,x);
	switch(color){
		case GFX_PIXEL_SET:
			temp |= pixelmask;
			break;
		case GFX_PIXEL_CLR:
			temp &= ~pixelmask;
			break;
		case GFX_PIXEL_XOR:
			temp ^= pixelmask;
			break;
	}

	// Write back byte to display or framebuffer
	//gfx_mono_put_page(&temp, page, column, 1);
	gfx_mono_put_byte(page, x, temp);
}


uint8_t gfx_mono_framebuffer_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	uint8_t page;
	uint8_t column;
	uint8_t pixelmask;
	uint8_t temp;

	// Sanity checks
	if ((x < 0) || (x > GFX_MONO_LCD_WIDTH-1) || (y < 0) ||\
			(y > GFX_MONO_LCD_HEIGHT-1)) {
		return;
	}

	page = y / 8;
	column = x;
	pixelmask = (1 << ((page << 3) - y));

	gfx_mono_get_page(&temp, page, column, 1);


	return temp;

}


static uint8_t *fbpointer;

void gfx_mono_set_framebuffer(uint8_t *framebuffer){
	fbpointer = framebuffer;
}

void gfx_mono_framebuffer_put_page(const gfx_mono_color_t *data, gfx_coord_t page,\
		gfx_coord_t column, gfx_coord_t width)
{

		gfx_coord_t *framebuffer_pt = fbpointer + ((page * GFX_MONO_LCD_WIDTH) + column);

		do {
			*framebuffer_pt++ = *data++;
		} while(--width > 0);
}

void gfx_mono_framebuffer_get_page(gfx_mono_color_t *data, gfx_coord_t page,\
		gfx_coord_t column, gfx_coord_t width)
{
		gfx_coord_t *framebuffer_pt = fbpointer + ((page * GFX_MONO_LCD_WIDTH) + column);
		do {
			*data++ = *framebuffer_pt++;
		} while(--width > 0);
}

void gfx_mono_framebuffer_put_byte(gfx_coord_t page, gfx_coord_t column, uint8_t data)
{
	*(fbpointer + ((page * GFX_MONO_LCD_WIDTH) + column)) = data;
}

uint8_t gfx_mono_framebuffer_get_byte(gfx_coord_t page, gfx_coord_t column)
{
	return *(fbpointer + ((page * GFX_MONO_LCD_WIDTH) + column));
}


void gfx_mono_framebuffer_mask_byte(gfx_coord_t page, gfx_coord_t column,\
         gfx_mono_color_t pixelmask, gfx_mono_color_t color)
{
	gfx_mono_color_t temp;

	temp = gfx_mono_get_byte(page, column);

	switch(color) {
		case GFX_PIXEL_SET:
			temp |= pixelmask;
			break;
		case GFX_PIXEL_CLR:
			temp &= ~pixelmask;
			break;
		case GFX_PIXEL_XOR:
			temp ^= pixelmask;
			break;
	}

	gfx_mono_put_byte(page, column, temp);
}

