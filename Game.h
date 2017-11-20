#ifndef __GAME__
#define __GAME__
#include "Display.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"
#include "vector.h"

typedef struct s_game t_game;
typedef struct s_input t_input;
typedef struct s_display t_display;

struct s_game
{
	t_display* display;
	t_input* input;
	t_player* player;
	t_enemy* enemies[5][12];
};

bool start(t_game* game);
void rungame(t_game* game);
void endgame(t_game* game);
//Render
void renderAll(t_game* game);
void renderBG(t_display* display);
void renderPlayer(t_player* player, t_display* display);
void renderPlayerProjectile(t_projectile* projectile, t_display* display);
void renderEnemies(t_game* game, t_display* display);
void renderEnemyProjectile(t_projectile* projectile, t_display* display);
//Update
void update(t_game* game);
void updatePlayer(t_player* player, t_input* input, t_display* display);
void updatePlayerProjectile(t_player* player, t_projectile* projectile);
void updateEnemies(t_game* game);
void updateEnemyProjectile(t_game* game, t_projectile* projectile, t_display* display);
//Collisions
void checkCollision(t_game* game);
void checkPlayerProjectileVSEnemy(t_player* player, t_projectile* projectile, t_enemy* enemies[5][12]);
void checkEnemyProjectileVSPlayer(t_player* player, t_projectile* projectile, t_game* game);

//Helpers
void moveDown(t_game* game);
t_vector* pickEnemy(t_enemy* enemies[5][12]);      //This function returns an index of the index of an enemy that can shoot


#endif

