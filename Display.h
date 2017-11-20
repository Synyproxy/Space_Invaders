#ifndef __DISPLAY__
#define __DISPLAY__
#include <SDL.h>
#include <stdbool.h>
#include "Player.h"

typedef struct s_display t_display;

struct s_display
{
	int screen_height;
	int screen_width;
	SDL_Window* window;
	SDL_Renderer* renderer;
	t_player* player;
	//SDL_Surface* surface; 
};

bool init(t_display* display);		//init SDL


#endif

