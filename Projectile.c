#include "Projectile.h"
#include "Game.h"
#include <SDL_image.h>


void initProjectile(t_game* game)
{
	t_projectile* projectile = malloc(sizeof(t_projectile));

	if (projectile == NULL)
		return;


	game->player->projectile = projectile;

	SDL_Rect* rect;

	rect = malloc(sizeof(SDL_Rect));

	rect->w = 8;
	rect->h = 40;
	rect->x = game->player->rect->x + 40;
	rect->y = game->player->rect->y - 10;


	SDL_Surface* surface = IMG_Load("res/Projectile.png");

	projectile->texture = SDL_CreateTextureFromSurface(game->display->renderer, surface);

	SDL_FreeSurface(surface);

	game->player->projectile->rect = rect;

	projectile->mouvementspeed = 20;
}

void enemyInitProjectile(t_game* game, t_vector* vector)
{

	if (vector == NULL)
		return;

	t_projectile* projectile = malloc(sizeof(t_projectile));

	if (projectile == NULL)
		return;


	game->enemies[0][0]->projectile = projectile;


	game->enemies[0][0]->projectile->rect = malloc(sizeof(SDL_Rect));

	game->enemies[0][0]->projectile->rect->w = 8;
	game->enemies[0][0]->projectile->rect->h = 40;
	game->enemies[0][0]->projectile->rect->x = game->enemies[vector->x][vector->y]->rect->x + 40;
	game->enemies[0][0]->projectile->rect->y = game->enemies[vector->x][vector->y]->rect->y + 30;


	SDL_Surface* surface = IMG_Load("res/ProjectileEnemy.png");

	projectile->texture = SDL_CreateTextureFromSurface(game->display->renderer, surface);

	SDL_FreeSurface(surface);

	projectile->mouvementspeed = 3;
}

