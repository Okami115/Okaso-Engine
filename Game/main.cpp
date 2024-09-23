#include <iostream>
#include <BaseGame/Game.h>


void main()
{
	Game* basegame = new Game(800, 600);
	basegame->gameLoop();
	delete basegame;
}