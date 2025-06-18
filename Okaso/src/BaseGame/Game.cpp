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
	triangle->SetColor(1,0,0);
	triangle->SetPosition(0,0, 0);
	triangle->SetScale(1,1,1);
	camera->target = triangle->GetPosition();
	camera->distanceToTarget = 100.0f;
}

void Game::update()
{
	triangle->Draw();
}

void Game::exit()
{
	delete triangle;
}
