#include "Game.h"
#include <stdlib.h>

int main(void)
{
	t_game game;

	if (!start(&game))
		return EXIT_FAILURE;
	rungame(&game);
	endgame(&game);

	return EXIT_SUCCESS;
}