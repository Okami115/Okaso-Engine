﻿#include "Game.h"

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
	//triangle = new shape::Triangle();
	//
	//rectangle = new shape::Rectangle();
	//
	//rectangle->SetColor(0, 1, 0);
	sprite = new Sprite("C:/Users/tomas/Escritorio/Okaso-Engine/Okaso/res/Assets/the division.png");
	sprite->SetRotation(180, 0, 0);
}

void Game::update()
{
	//if (input->isKeyPressed(KEY_D))
	//{
	//	triangle->Translate(0,0.5f,0);
	//}
	//triangle->Rotate(0,0,0.5f);
	//
	//rectangle->Rotate(0, 0, - 0.01f);
	//
	//
	//rectangle->Draw();
	//
	//triangle->Draw();

	sprite->Draw();
}

void Game::exit()
{
	delete triangle;
	delete rectangle;
	delete sprite;
}