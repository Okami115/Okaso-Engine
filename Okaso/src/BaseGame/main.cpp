#include "BaseGame.h"

void main()
{
	OkasoEngine_Render::Renderer::GetRenderer();

	Okaso_Engine* basegame = new Okaso_Engine();
	basegame->gameLoop();
	delete basegame;
}