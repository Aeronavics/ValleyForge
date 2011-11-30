#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "compiler.h"
#include "gfx_mono.h"

#define WIDTH    128
#define HEIGHT   32

#define FRAMEBUFFER_SIZE   ((WIDTH * HEIGHT) / 8)

uint8_t framebuffer[FRAMEBUFFER_SIZE];


SDL_Surface *screen;

void putpixel(int x, int y, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4);
  ptr[lineoffset + x] = color;
}

void render_framebuffer()
{
	int i,page,pix;
	int x,y;
  // Lock surface if needed
  if (SDL_MUSTLOCK(screen))
    if (SDL_LockSurface(screen) < 0)
      return;

  // Ask SDL for the time in milliseconds
  int tick = SDL_GetTicks();



	for(i = 0; i < WIDTH; i++){
		for(page = 0; page < (HEIGHT / 8); page++){
			for(pix = 0; pix < 8; pix++){
				x = i*2;
				y = ((page * 8) + pix)*2;
				if (framebuffer[(page*WIDTH)+i] & (1 << pix)){
					putpixel(x, y, 0x0);
					putpixel(x+1, y, 0x0);
					putpixel(x, y+1, 0x0);
					putpixel(x+1, y+1, 0x0);
				} else {
					putpixel(x, y, 0xFFFFFF);
					putpixel(x+1, y, 0xFFFFFF);
					putpixel(x, y+1, 0xFFFFFF);
					putpixel(x+1, y+1, 0xFFFFFF);
				}
			}
		}
	}

  // Unlock if needed
  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);

  // Tell SDL to update the whole screen
  SDL_UpdateRect(screen, 0, 0, WIDTH*2, HEIGHT*2);
}




// Entry point
int main(int argc, char *argv[])
{
	int i=0;

  // Initialize SDL's subsystems - in this case, only video.
  if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }

	for(i = 0; i < FRAMEBUFFER_SIZE; i++) {
		framebuffer[i] = 0xAA;
	}

  // Register SDL_Quit to be called at exit; makes sure things are
  // cleaned up when we quit.
  atexit(SDL_Quit);

  screen = SDL_SetVideoMode(WIDTH*2, HEIGHT*2, 32, SDL_SWSURFACE);

  // If we fail, return error.
  if ( screen == NULL )
  {
    fprintf(stderr, "Unable to set videomode, error: %s\n", SDL_GetError());
    exit(1);
  }

// Main loop: loop forever.
  while (1)
  {
    // Render stuff


	gfx_mono_set_framebuffer(framebuffer);
	mcu_code();
  render_framebuffer();
    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_KEYDOWN:
        break;
      case SDL_KEYUP:
        // If escape is pressed, return (and thus, quit)
        if (event.key.keysym.sym == SDLK_ESCAPE)
          return 0;
        break;
      case SDL_QUIT:
        return(0);
      }
    }
  }
  return 0;
}

