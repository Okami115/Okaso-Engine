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
    float vertices[] = {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   
    };
    unsigned int indices[] = {  
        0, 1, 2,  
    };

	triangle = new Triangle(vertices, indices, 18, 3);
}

void Game::update()
{
	triangle->Draw();
}

void Game::exit()
{
	delete triangle;
}