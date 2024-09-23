#include "Game.h"

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
	triangle = new shape::Triangle();

	rectangle = new shape::Rectangle();

	rectangle->SetColor(0, 1, 0);
	triangle->SetColor(1, 0, 0);
	
}

void Game::update()
{
	triangle->Rotate(0,0,0.5f);
	triangle->Translate(0,0.5f,0);
	rectangle->Rotate(0, 0, - 0.01f);


	rectangle->Draw();

	triangle->Draw();

}

void Game::exit()
{
	delete triangle;
	delete rectangle;
}