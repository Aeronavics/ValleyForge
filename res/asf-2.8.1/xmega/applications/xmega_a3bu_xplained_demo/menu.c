/**
 * \file
 *
 * \brief simple menu system
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

#include "sysfont.h"
#include "bitmaps.h"
#include "keyboard.h"
#include "menu.h"


/**
 * \brief Draw menu strings and an icon by the current selection.
 *
 * \param menu     a menu struct with menu settings
 * \param redraw   clear screen before drawing menu
 */
void menu_draw(struct menu *menu, bool redraw)
{
	static bool redraw_state;
	uint8_t i;
	uint8_t line = 1;
	uint8_t menu_page = menu->current_selection / MENU_ELEMENTS_PER_SCREEN;

	if (menu->current_page != menu_page || redraw == true) {
		// clear screen if we have changed the page or menu and prepare redraw
		gfx_mono_draw_filled_rect(0, 8, 127, 23, GFX_PIXEL_CLR);
		redraw_state = true;
	}
	menu->current_page = menu_page;

	// Clear old icon
	gfx_mono_draw_filled_rect(0, 8, 4, 23, GFX_PIXEL_CLR);

	// Put icon on current selection
	gfx_mono_put_bitmap(&bitmap_arrow_right, 0, 8 * ((menu->current_selection % MENU_ELEMENTS_PER_SCREEN) + 1));

	// Print visible options if page or menu has changed
	if (redraw_state == true) {
		for (i = menu_page * MENU_ELEMENTS_PER_SCREEN;
				i < menu_page * MENU_ELEMENTS_PER_SCREEN + MENU_ELEMENTS_PER_SCREEN &&
				i < menu->num_elements; i++) {
			gfx_mono_draw_progmem_string((char PROGMEM_PTR_T)menu->strings[i], 5, line * 8, &sysfont);
			line++;
		}
		redraw_state = false;
	}

}

/**
 *\brief Display a menu and handle user input
 *
 * \param menu  a menu struct with menu options
 *
 * \retval the selected menu option
 */
uint8_t menu_handler(struct menu *menu) {
	struct keyboard_event input;

	// Clear screen
	gfx_mono_draw_filled_rect(0, 0, 127, 31, GFX_PIXEL_CLR);

	// Draw the menu title on the top of the screen
	gfx_mono_draw_progmem_string((char PROGMEM_PTR_T)menu->title, 3, 0, &sysfont);

	// Draw menu options below
	menu_draw(menu, true);

	while (1) {
		// Handle key input
		keyboard_get_key_state(&input);
		if (input.type != KEYBOARD_RELEASE) {
			continue;
		}

		switch (input.keycode) {
			case KEYBOARD_DOWN:
				if (menu->current_selection == menu->num_elements - 1) {
					menu->current_selection = 0;
				} else {
					menu->current_selection++;
				}
				// Update menu on display
				menu_draw(menu, false);
				break;
			case KEYBOARD_UP:
				if (menu->current_selection) {
					menu->current_selection--;
				} else {
					menu->current_selection = menu->num_elements - 1;
				}
				// update menu on display
				menu_draw(menu, false);
				break;
			case KEYBOARD_ENTER:
				// Got what we want; now return it
				return menu->current_selection;
			case KEYBOARD_BACK:
				// User pressed "back" key, return MENU_RETURN
				return MENU_RETURN;
			default:
				// Unknown key event
				break;
		}
	}
}

