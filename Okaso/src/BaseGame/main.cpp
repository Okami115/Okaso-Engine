#include <functional>

#include "BaseGame.h"
#include "Game.h"

void main()
{
	Game* basegame = new Game(800,600);
	basegame->gameLoop();
	delete basegame;
}