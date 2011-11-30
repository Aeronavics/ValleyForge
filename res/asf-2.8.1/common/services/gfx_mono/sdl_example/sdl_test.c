#include "compiler.h"
#include "gfx_mono.h"
#include <stdio.h>
#include <sys/time.h>



int8_t sinus[] = {
   0, 0, 1, 2, 3, 3, 4, 5, 6, 7, 7, 8, 9,10,10,11,
  12,12,13,14,15,15,16,17,17,18,19,19,20,20,21,22,
  22,23,23,24,24,25,25,26,26,27,27,27,28,28,28,29,
  29,29,30,30,30,30,31,31,31,31,31,31,31,31,31,31,
  32,31,31,31,31,31,31,31,31,31,31,30,30,30,30,29,
  29,29,28,28,28,27,27,27,26,26,25,25,24,24,23,23,
  22,22,21,20,20,19,19,18,17,17,16,15,15,14,13,12,
  12,11,10,10, 9, 8, 7, 7, 6, 5, 4, 3, 3, 2, 1, 0,
   0, 0,-1,-2,-3,-3,-4,-5,-6,-7,-7,-8,-9,-10,-10,-11,
  -12,-12,-13,-14,-15,-15,-16,-17,-17,-18,-19,-19,-20,-20,-21,-22,
  -22,-23,-23,-24,-24,-25,-25,-26,-26,-27,-27,-27,-28,-28,-28,-29,
  -29,-29,-30,-30,-30,-30,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,
  -32,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-30,-30,-30,-30,-29,
  -29,-29,-28,-28,-28,-27,-27,-27,-26,-26,-25,-25,-24,-24,-23,-23,
  -22,-22,-21,-20,-20,-19,-19,-18,-17,-17,-16,-15,-15,-14,-13,-12,
  -12,-11,-10,-10,-9,-8,-7,-7,-6,-5,-4,-3,-3,-2,-1, 0,
  };

uint8_t smiley_data[16] = { 0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
		0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C};

void mcu_code(void){
    static int iter;
    uint8_t i;
    static uint16_t step=0;
    int page,column;
    uint8_t data;

	struct timeval starttime, endtime;
	long elapsed_utime;    /* elapsed time in microseconds */
    long elapsed_mtime;    /* elapsed time in milliseconds */
	long elapsed_seconds;  /* diff between seconds counter */
	long elapsed_useconds; /* diff between microseconds counter */

	struct gfx_mono_bitmap smiley;

	smiley.type = GFX_MONO_BITMAP_RAM;
	smiley.width = 8;
	smiley.height = 16;
	smiley.data.pixmap = smiley_data;

  // clear screen
	data = 0;
	for(page = 0; page < 4; page++){
		for(column = 0; column < 128; column++) {
			gfx_mono_put_page(&data, page, column, 1);
		}
	}

	gfx_mono_put_page(smiley_data, 2, step, 8);
	gfx_mono_put_page(&smiley_data[8],3,20,8);
	gfx_mono_generic_put_bitmap(&smiley, 50, 2);

	// straight line and a sinus of increasing frequency
	/*
	for(i = 0; i < 128; i++) {
		gfx_mono_draw_pixel(i,  16 + sinus[ (((i*step*500) >> 8) % 256)]/2, GFX_PIXEL_SET );
	}
	*/


	//vertical line
	gfx_mono_draw_vertical_line(20, 4, 28, GFX_PIXEL_SET);
	gfx_mono_draw_vertical_line(20, 10, 22, GFX_PIXEL_SET);
	gfx_mono_draw_vertical_line(29, 1, 31, GFX_PIXEL_SET);

	gfx_mono_draw_horizontal_line(10,10,20, GFX_PIXEL_SET);
	gfx_mono_draw_horizontal_line(20,10,20, GFX_PIXEL_CLR);
	gfx_mono_draw_horizontal_line(10,13,20, GFX_PIXEL_XOR);

	printf("------------ circle ---------------\n");
	gfx_mono_draw_circle(60, 16, 5, GFX_PIXEL_SET, GFX_WHOLE);
	printf("-------------/circle---------------\n");

	while(1);

/*
	gfx_mono_draw_line(10,10,100,0, GFX_PIXEL_SET);

	gfx_mono_draw_rect(20,20,60,5,GFX_PIXEL_SET);

	gfx_mono_draw_filled_rect(82,20,20,5,GFX_PIXEL_SET);

	//whole circle
	gfx_mono_draw_circle(50, 16, 8, GFX_PIXEL_SET,GFX_WHOLE);

	//half circle

	gfx_mono_draw_filled_circle(100, 16, 8, GFX_PIXEL_SET, 0xFF);


	gfx_mono_draw_circle(64,16,15,GFX_PIXEL_SET, 0xFF);
	gfx_mono_draw_filled_circle(64,16,14,GFX_PIXEL_XOR, (1 << step));

	*/

	if(!(iter%500)){
		if (step++ >= 120) {
			step = 0;
		}
	}

	iter++;

}

