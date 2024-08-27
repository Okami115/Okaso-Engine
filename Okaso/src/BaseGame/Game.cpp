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
    float position[6] =
    {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    triangle = new Triangle(position);
}

void Game::update()
{
    triangle->Draw();
}

void Game::exit()
{
    delete triangle;
    
}