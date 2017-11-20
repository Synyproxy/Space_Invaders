#include <stdbool.h>
#include <SDL_image.h>
#include "Enemy.h"
#include "Game.h"

void initEnemies(t_game *game) {

	int row = 0;
	int col = 0;
	int xStartpos = 150;
	int yStartpos = 60;
	int rowOffset = 10;
	int colOffset = 5;

	while (row < 5) {
		while (col < 12)
		{
			game->enemies[row][col] = initEnemy(game, xStartpos, yStartpos);
			xStartpos += 80 + colOffset;
			col++;
		}
		xStartpos = 150;
		yStartpos += 80 + rowOffset;
		col = 0;
		row++;
	}

	game->enemies[0][0]->projectile = NULL;

}

t_enemy* initEnemy(t_game* game, int x, int y)
{
	t_enemy* enemy = malloc(sizeof(t_enemy));

	if (enemy == NULL)
		return NULL;

	enemy->rect = malloc(sizeof(SDL_Rect));

	enemy->rect->w = 60;
	enemy->rect->h = 60;
	enemy->rect->x = x;
	enemy->rect->y = y;

	SDL_Surface* surface = IMG_Load("res/Enemy.png");
	enemy->texture = SDL_CreateTextureFromSurface(game->display->renderer, surface);
	SDL_FreeSurface(surface);

	enemy->mouvementSpeed = 2;
	enemy->isAlive = true;
	enemy->hitleftwall = false;

	return enemy;
}
