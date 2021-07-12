#include"Game.h"
#include<time.h>

int main()
{
	srand(time(NULL));
	Game game;
	game.Run();

	return 0;
}