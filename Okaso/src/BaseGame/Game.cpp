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
	cube = new Cube();
	cube->SetColor(0, 0, 1);
	cube->SetPosition(0, 0, 0);
	camera->target = cube->GetPosition();
	camera->distanceToTarget = 100.0f;
}

void Game::update()
{
	cube->Draw();
}

void Game::exit()
{
	delete cube;
}
