#ifndef __PLAYER__
#define __PLAYER__

#include <SDL.h>
#include "Projectile.h"

typedef struct s_game t_game;

typedef struct s_player t_player;

struct s_player
{
	SDL_Rect* rect;
	SDL_Texture* texture;
	int mouvementSpeed;
	t_projectile* projectile;
	int life;
};

void initPlayer(t_game* game, int w, int h);

#endif
