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
	Yellowtriangle = new shape::Triangle();
	Pinktriangle = new shape::Triangle();

	Yellowtriangle->SetPosition(100,500,0);
	Pinktriangle->SetPosition(700,100,0);

	Yellowtriangle->SetColor(1, 1, 0);
	Pinktriangle->SetColor(1, 0, 0.5f);

	Yellowtriangle->SetScale(0.5f,0.5f,0.5f);
	Pinktriangle->SetScale(0.5f,0.5f,0.5f);
}

void Game::update()
{	
	Yellowtriangle->Rotate(0,0,1);
	Pinktriangle->Rotate(0,0,-1);

	Yellowtriangle->Translate(0,-1,0);
	Pinktriangle->Translate(0,1,0);

	Yellowtriangle->Draw();
	Pinktriangle->Draw();

}

void Game::exit()
{
	delete Yellowtriangle;
	delete Pinktriangle;
}