#include <functional>

#include "BaseGame.h"
#include "Game.h"

void main()
{

	//OkasoEngine_Render::Renderer::GetRenderer();
	/*
	position pos = position(4.5f, 11.0f);

	Vertex aux = Vertex(pos);

	cout << "Position :: " << aux.pos.x << " " << aux.pos.y << " " << aux.pos.z << endl;
	cout << "UV :: " << aux.uv.u << " " << aux.uv.v << endl;
	cout << "Color :: " << aux.color.red << " " << aux.color.green << " " << aux.color.blue << " " << aux.color.alpha << endl;
	*/

	//Okaso_Engine* basegame = new Okaso_Engine();
	//basegame->gameLoop();
	//delete basegame;

	Game* basegame = new Game(800,600);
	basegame->gameLoop();
	delete basegame;

	//std::function<void ()> func = [basegame]() { basegame->gameLoop(); };
}