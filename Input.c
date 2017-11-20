#include "Game.h"
#include "Input.h"
#include <stdbool.h>
#include <SDL.h>

void inputlistener(t_game* game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		// Escape pressed
		if (e.key.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN)
		{
			game->input->escape = true;
		}
		//Close Window with X
		if (e.type == SDL_QUIT)
			game->input->escape = true;
		// Left Pressed
		if (e.key.keysym.sym == SDLK_LEFT && e.type == SDL_KEYDOWN)
		{
			game->input->left = true;
		}
		if (e.key.keysym.sym == SDLK_LEFT && e.type == SDL_KEYUP)
		{
			game->input->left = false;
		}
		// Right Pressed
		if (e.key.keysym.sym == SDLK_RIGHT && e.type == SDL_KEYDOWN)
		{
			game->input->right = true;
		}
		if (e.key.keysym.sym == SDLK_RIGHT && e.type == SDL_KEYUP)
		{
			game->input->right = false;
		}
		// SpaceBar Pressed
		if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYUP)
		{
			game->input->space = false;
		}
		if (e.key.keysym.sym == SDLK_SPACE && e.type == SDL_KEYDOWN)
		{
			game->input->space = true;
		}
	}
}

void init_input(t_input* input)
{
	input->escape = false;
	input->left = false;
	input->right = false;
	input->space = false;
}
