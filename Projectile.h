#ifndef __PROJECTILE__
#define __PROJECTILE__

#include <SDL.h>
#include "vector.h"

typedef struct s_game t_game;

typedef struct s_projectile t_projectile;

struct s_projectile
{
	SDL_Rect* rect;
	SDL_Texture* texture;
	int mouvementspeed;
	int gravity;
};

void initProjectile(t_game* game);
//Inits an enemy projectile from the position of the launching enemy
void enemyInitProjectile(t_game* game, t_vector* vector);

#endif