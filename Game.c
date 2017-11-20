#include "Game.h"
#include "my_put_string.h"
#include "Player.h"
#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool start(t_game* game)
{

	game->display = malloc(sizeof(t_display));
	if (game->display == NULL)
		return false;

	game->display->screen_height = 860;
	game->display->screen_width = 1300;

	if (!init(game->display))
	{
		my_put_string("failed to init\n");
		return false;
	}

	game->input = malloc(sizeof(t_input));
	if (game->input == NULL)
		return false;

	init_input(game->input);
	initPlayer(game, 80, 80);
	initEnemies(game);

	return true;
}



void rungame(t_game* game)
{
	while (!game->input->escape)
	{
		inputlistener(game);
		update(game);
		renderAll(game);
	}
}

void renderAll(t_game* game)
{
	//clean the screen
	SDL_RenderClear(game->display->renderer);

	//Render Player
	renderPlayer(game->player, game->display);
	//Render Player Projectile
	if (game->player->projectile != NULL)
		renderPlayerProjectile(game->player->projectile, game->display);

	//Render Enemies
	renderEnemies(game, game->display);
	//Render Enemy Projectile
	if (game->enemies[0][0]->projectile != NULL)
		renderEnemyProjectile(game->enemies[0][0]->projectile, game->display);
	//Render BG
	renderBG(game->display);

	//Render to screen
	SDL_RenderPresent(game->display->renderer);

}

void renderBG(t_display* display)
{
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}

void renderPlayer(t_player* player, t_display* display)
{
	SDL_RenderCopy(display->renderer, player->texture, NULL, player->rect);

}

void renderPlayerProjectile(t_projectile* projectile, t_display* display)
{
	SDL_RenderCopy(display->renderer, projectile->texture, NULL, projectile->rect);

}

void renderEnemies(t_game* game, t_display* display)
{
	int col = 0;
	int row = 0;

	while (row < 5) {
		while (col < 12)
		{
			if (game->enemies[row][col]->isAlive)
				SDL_RenderCopy(display->renderer, game->enemies[row][col]->texture, NULL, game->enemies[row][col]->rect);
			col++;
		}
		col = 0;
		row++;
	}

}

void renderEnemyProjectile(t_projectile* projectile, t_display* display)
{
	SDL_RenderCopy(display->renderer, projectile->texture, NULL, projectile->rect);
}

void update(t_game* game)
{
	if (game->player->life <= 0)
		game->input->escape = true;
	//Update Player
	updatePlayer(game->player, game->input, game->display);
	//Update Projectile
	//If no Player Projectile on Screen Create One
	if (game->input->space && game->player->projectile == NULL)
		initProjectile(game);
	if (game->player->projectile != NULL)
		updatePlayerProjectile(game->player, game->player->projectile);
	//Update enemies
	updateEnemies(game);
	//If no enemy has shot a projectile
	if (game->enemies[0][0]->projectile == NULL)
		enemyInitProjectile(game, pickEnemy(game->enemies));

	if (game->enemies[0][0]->projectile != NULL)
		updateEnemyProjectile(game, game->enemies[0][0]->projectile, game->display);

	//Check Collision
	checkCollision(game);

}

void updatePlayer(t_player* player, t_input* input, t_display* display)
{
	if (input->right && player->rect->x < display->screen_width - player->rect->w)
		player->rect->x += player->mouvementSpeed;
	if (input->left && player->rect->x > 0)
		player->rect->x -= player->mouvementSpeed;
}

void updatePlayerProjectile(t_player* player, t_projectile* projectile)
{
	if (projectile->rect->y < 0)
	{
		free(projectile->rect);
		projectile->rect = NULL;    // TRUST NO ONE
		free(projectile);
		player->projectile = NULL;
	}

	else
	{
		projectile->rect->y -= projectile->mouvementspeed;
	}
}

void updateEnemyProjectile(t_game* game, t_projectile* projectile, t_display* display)
{
	if (projectile->rect->y > display->screen_height)
	{
		free(projectile->rect);
		projectile->rect = NULL;    // TRUST NO ONE
		free(projectile);
		game->enemies[0][0]->projectile = NULL;
	}

	else
	{
		projectile->rect->y += projectile->mouvementspeed;
	}
}

void updateEnemies(t_game* game)
{
	if (!game->enemies[0][0]->hitleftwall)
	{
		// moveleft until hit leftwall
		int col = 0;
		int row = 0;

		while (row < 5) {
			while (col < 12)
			{
				game->enemies[row][col]->rect->x -= game->enemies[0][0]->mouvementSpeed * 1;
				//An Alive enemy has hit bottom
				if (game->enemies[row][col]->rect->y >= 700 && game->enemies[row][col]->isAlive)
					game->input->escape = true;
				col++;
			}
			col = 0;
			row++;
		}
		if (game->enemies[0][0]->rect->x == 0)
		{
			game->enemies[0][0]->hitleftwall = true;
			moveDown(game);
		}
	}
	else
	{
		//move right until hit rightwall
		int col = 0;
		int row = 0;

		while (row < 5) {
			while (col < 12)
			{
				game->enemies[row][col]->rect->x -= game->enemies[0][0]->mouvementSpeed * -1;
				col++;
			}
			col = 0;
			row++;
		}
		if (game->enemies[0][11]->rect->x >= game->display->screen_width - game->enemies[0][0]->rect->w)
		{
			game->enemies[0][0]->hitleftwall = false;
			moveDown(game);
		}
	}
}

void moveDown(t_game* game)
{
	int row = 0;
	int col = 0;

	while (row < 5) {
		while (col < 12)
		{
			game->enemies[row][col]->rect->y += 20;
			col++;
		}
		col = 0;
		row++;
	}
}

void checkCollision(t_game* game)
{
	//Check Player Projectile VS Enemy
	if (game->player->projectile)
		checkPlayerProjectileVSEnemy(game->player, game->player->projectile, game->enemies);
	//Check Enemy Projectile VS Player

	if (game->enemies[0][0]->projectile)
		checkEnemyProjectileVSPlayer(game->player, game->enemies[0][0]->projectile, game);

}

void checkPlayerProjectileVSEnemy(t_player* player, t_projectile* projectile, t_enemy* enemies[5][12])
{

	int row = 0;
	int col = 0;
	int playerProjectileLeft = projectile->rect->x;
	int playerProjectileRight = projectile->rect->w;
	int playerProjectileTop = projectile->rect->y;
	int playerProjectileBot = projectile->rect->h;

	int enemyLeft;
	int enemyRight;
	int enemyTop;
	int enemyBot;

	while (row  <  5) {
		while (col < 12)
		{
			if (enemies[row][col]->isAlive) {

				enemyLeft = enemies[row][col]->rect->x;
				enemyRight = enemies[row][col]->rect->w;
				enemyTop = enemies[row][col]->rect->y;
				enemyBot = enemies[row][col]->rect->h;

				if (playerProjectileLeft < enemyLeft + enemyRight &&
					playerProjectileLeft + playerProjectileRight > enemyLeft &&
					playerProjectileTop < enemyTop + enemyBot &&
					playerProjectileBot + playerProjectileTop > enemyTop)
				{
					// collision detected!
					free(player->projectile);
					player->projectile = NULL;
					enemies[row][col]->isAlive = false;
				}
			}
			col++;
		}
		col = 0;
		row++;
	}
}

void checkEnemyProjectileVSPlayer(t_player* player, t_projectile* projectile, t_game* game)
{
	int EnemyProjectileLeft = projectile->rect->x;
	int EnemyProjectileRight = projectile->rect->w;
	int EnemyProjectileTop = projectile->rect->y;
	int EnemyProjectileBot = projectile->rect->h;

	int PlayerLeft = player->rect->x;
	int PlayerRight = player->rect->w;
	int PlayerTop = player->rect->y;
	int PlayerBot = player->rect->h;

	if (EnemyProjectileLeft < PlayerLeft + PlayerRight &&
		EnemyProjectileLeft + EnemyProjectileRight > PlayerLeft &&
		EnemyProjectileTop < PlayerTop + PlayerBot &&
		EnemyProjectileBot + EnemyProjectileTop > PlayerTop)
	{
		// collision detected!
		free(game->enemies[0][0]->projectile);
		game->enemies[0][0]->projectile = NULL;
		player->life--;
	}


}

t_vector* pickEnemy(t_enemy* enemies[5][12])
{
	t_vector* vector = malloc(sizeof(t_vector));
	if (vector == NULL)
		return NULL;

	bool aliveInThisRow = false;

	int row = 4;
	int col = 0;
	int randy = 666;

	while (row > 0)
	{
		while (col < 12)
		{
			randy = rand();
			if (enemies[row][col]->isAlive)
				aliveInThisRow = true;
			if (enemies[row][col]->isAlive && randy % 7 == 0)
			{
				// You have been chosen buddy
				printf("Picked enemy %d, %d\n", row, col);
				vector->x = row;
				vector->y = col;
				return vector;
			}
			col++;
		}
		if (aliveInThisRow)
			row++;
		col = 0;
		row--;
	}
	return NULL;
}

void endgame(t_game* game)
{

	free(game->player->rect);
	//free(game->player->texture);
	free(game->player->projectile);
	//free(game->display->renderer);
	//free(game->display->window);

	int row = 0;
	int col = 0;
	while (row < 5) {
		while (col < 12)
		{
			//free(game->enemies[row][col]->texture);
			free(game->enemies[row][col]->rect);
			free(game->enemies[row][col]);
			col++;
		}
		col = 0;
		row++;
	}

}




