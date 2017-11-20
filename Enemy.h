#ifndef __ENEMY__
#define __ENEMY__

#include <SDL.h>
#include <stdbool.h>
#include "Projectile.h"

typedef struct s_game t_game;

typedef struct s_enemy t_enemy;

struct s_enemy
{
	SDL_Rect* rect;
	SDL_Texture* texture;
	bool isAlive;
	int mouvementSpeed;
	bool hitleftwall;
	t_projectile* projectile;
};


void initEnemies(t_game* game);
t_enemy* initEnemy(t_game* game, int x, int y);

#endif