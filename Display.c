#include "Display.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "my_put_string.h"
#include "Player.h"
#include <stdbool.h>
#include <stdio.h>


bool init(t_display* display)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0 && IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		success = false;
		my_put_string("Video failed to Initialize\n");
	}
	else	// Video Initalized
	{
		// Create the window
		display->window = SDL_CreateWindow("Space Invadah",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			display->screen_width,
			display->screen_height,
			SDL_WINDOW_RESIZABLE);
		if (display->window == NULL)
		{
			success = false;
			my_put_string("Failed to create Window\n");
		}
		else	// Renderer
		{
			//Renderer 
			display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (display->renderer == NULL)
			{
				my_put_string("Failed to Initilize Renderer");
				success = false;
			}
		}
	}


	return success;
}