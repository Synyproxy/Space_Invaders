#include "Player.h"
#include "Game.h"
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_image.h>

void initPlayer(t_game* game, int w, int h)
{

	t_player* player = malloc(sizeof(t_player));

	if (player == NULL)
		return;

	game->player = player;

	SDL_Rect* rect;

	rect = malloc(sizeof(SDL_Rect));

	rect->w = w;
	rect->h = h;
	rect->x = 547;
	rect->y = 780;

	SDL_Surface* surface = IMG_Load("res/Spaceship.png");

	player->texture = SDL_CreateTextureFromSurface(game->display->renderer, surface);

	SDL_FreeSurface(surface);

	game->player->rect = rect;

	player->mouvementSpeed = 5;
	player->life = 3;

	player->projectile = NULL;
}
