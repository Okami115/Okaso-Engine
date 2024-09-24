#include "Game.h"

#include "Input/Input.h"
#include "Input/KeyCode.h"

Game::Game(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	init();
}

Game::~Game()
{
	exit();
}

void Game::init()
{

	rectangle = new shape::Rectangle();

	rectangle->SetColor(0, 0, 1);
	rectangle->SetPosition(0,windowHeight / 2,0);
	
}

void Game::update()
{
	rectangle->Rotate(0, 0, - 1.0f);
	rectangle->Translate(2.0f,0,0);
	rectangle->Scale(-0.002,-0.002f,0);


	rectangle->Draw();
}

void Game::exit()
{
	delete rectangle;
}