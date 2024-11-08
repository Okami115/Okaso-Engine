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
    sprite = new Sprite("C:/GithubRepo/Okaso-Engine/Okaso/res/Assets/atlas.png", 0, 520, 10, 1, 1200, 1040, 120, 130);
    sprite2 = new Sprite("C:/GithubRepo/Okaso-Engine/Okaso/res/Assets/the division.png", 0, 512, 1, 0, 512, 512, 512,
                         512);
    sprite->SetScale(120, 120, 1);
    sprite2->SetScale(512 / 3, 512 / 3, 1);
    sprite2->SetPosition(sprite2->GetPosition().x, sprite2->GetPosition().y + 200, 0);
    sprite2->ForceCurrentPosAsPreviousPos();
}

void Game::update()
{
    if (input->isKeyPressed(KEY_W))
    {
        sprite->Translate(0, 1.0f, 0);
        Colitions::CheckCollitions(sprite, sprite2);
    }
    if (input->isKeyPressed(KEY_A))
    {
        sprite->Translate(-1.0f, 0, 0);
        Colitions::CheckCollitions(sprite, sprite2);
    }
    if (input->isKeyPressed(KEY_S))
    {
        sprite->Translate(0, -1.0f, 0);
        Colitions::CheckCollitions(sprite, sprite2);
    }
    if (input->isKeyPressed(KEY_D))
    {
        sprite->Translate(1.0f, 0, 0);
        Colitions::CheckCollitions(sprite, sprite2);
    }

    if (Colitions::CheckCollitions(sprite, sprite2))
    {
        cout << "Collision" << endl;
    }

    sprite2->Draw();

    sprite->UpdateAnimation();
    sprite->Draw();
}

void Game::exit()
{
    delete triangle;
    delete rectangle;
    delete sprite;
}
