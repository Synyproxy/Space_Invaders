#ifndef __INPUT__
#define __INPUT__
#include <stdbool.h>

typedef struct s_game t_game;

typedef struct s_input t_input;

struct s_input
{
	bool escape;
	bool left;
	bool right;
	bool space;

};

void inputlistener(t_game* game);
void init_input(t_input* input);
#endif
