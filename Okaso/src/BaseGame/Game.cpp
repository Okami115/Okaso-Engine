#include "Game.h"

#include "Colitions/Colitions.h"
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
	Knuckles = new Sprite("../Game/Sprite Sheets_Ejercicios Practicos/Knuckles_Sprite_Sheet.png", 1, 1, 1, 1, 646, 473, 36, 39);
	rock = new Sprite("../Game/Sprite Sheets_Ejercicios Practicos/Rock.png", 74, 21, 1, 1, 244, 207, 87, 60);

	idle = Animation(1, 1, 1, 1, 646, 473, 36, 40);
	walk = Animation(337, 44, 4, 0.5f, 646, 473, 39, 39);
	atack = Animation(0, 128, 7, 1, 646, 473, 32, 32);
	push = Animation(425, 94, 4, 1, 646, 473, 35, 35);

	Knuckles->SetScale(80, 80, 1);
	Knuckles->Translate(-100, 0, 0);
	rock->SetScale(87, 60, 1);
	Knuckles->ForcePreviousPosAsCurrentPos();
	rock->ForcePreviousPosAsCurrentPos();

	isColicion = false;
}

void Game::update()
{
	newAnimationState = AnimationState::idle;

	float dirX = 0;
	float dirY = 0;

	if (input->isKeyPressed(KEY_W))
	{
		Knuckles->Translate(0, 1.1f, 0);
		dirY = 1.1f;
		isColicion = Colitions::CheckCollitions(Knuckles, rock, false);
		newAnimationState = AnimationState::walk;
	}
	if (input->isKeyPressed(KEY_S))
	{
		Knuckles->Translate(0, -1.1f, 0);
		dirY = -1.1f;
		isColicion = Colitions::CheckCollitions(Knuckles, rock, false);
		newAnimationState = AnimationState::walk;
	}
	if (input->isKeyPressed(KEY_A))
	{
		Knuckles->Translate(-1.1f, 0, 0);
		dirX = -1.1f;
		Knuckles->SetScale(-80, 80, 1);
		isColicion = Colitions::CheckCollitions(Knuckles, rock, true);
		newAnimationState = AnimationState::walk;
	}
	if (input->isKeyPressed(KEY_D))
	{
		Knuckles->Translate(1.1f, 0, 0);
		dirX = 1.1f;
		Knuckles->SetScale(80, 80, 1);
		isColicion = Colitions::CheckCollitions(Knuckles, rock, true);
		newAnimationState = AnimationState::walk;
	}
	if (input->isKeyPressed(KEY_ENTER))
	{
		isColicion = Colitions::CheckCollitions(Knuckles, rock, true);
		newAnimationState = AnimationState::Atack;
	}


	if (isColicion)
	{
		if (dirX != 0) 
		{
			newAnimationState = AnimationState::Push;
			rock->Translate(dirX, 0, 0);
			isColicion = false;
		}
	}


	if (newAnimationState != currentAnimationState)
	{
		switch (newAnimationState)
		{
		case AnimationState::idle:
			Knuckles->ChangeAnimation(idle);
			currentAnimationState = newAnimationState;
			break;
		case AnimationState::walk:
			Knuckles->ChangeAnimation(walk);
			currentAnimationState = newAnimationState;
			break;
		case AnimationState::Push:
			Knuckles->ChangeAnimation(push);
			currentAnimationState = newAnimationState;
			break;
		case AnimationState::Atack:
			Knuckles->ChangeAnimation(atack);
			currentAnimationState = newAnimationState;
			break;
		default:
			break;
		}
	}


	rock->UpdateAnimation();
	rock->Draw();

	Knuckles->UpdateAnimation();
	Knuckles->Draw();
}

void Game::exit()
{
	delete Knuckles;
	delete rock;
}
