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
	triangle = new shape::Triangle();

	rectangle = new shape::Rectangle();

	rectangle->SetColor(0, 1, 0);
	triangle->SetColor(1, 0, 0);
	
}

void Game::update()
{
	if (input->isKeyPressed(KEY_W))
	{
		triangle->Translate(0,2.0f,0);
	}
	if (input->isKeyPressed(KEY_S))
	{
		triangle->Translate(0,-2.0f,0);
	}
	if (input->isKeyPressed(KEY_D))
	{
		triangle->Translate(2.0f,0,0);
	}
	if (input->isKeyPressed(KEY_A))
	{
		triangle->Translate(-2.0f,0,0);
	}
	if (input->isKeyPressed(KEY_E))
	{
		triangle->Rotate(0,0,-2.0f);
	}
	if (input->isKeyPressed(KEY_Q))
	{
		triangle->Rotate(0,0,2.0f);
	}

	//rectangle->Rotate(0, 0, -1.0f);


	//rectangle->Draw();

	triangle->Draw();

}

void Game::exit()
{
	delete triangle;
	delete rectangle;
}