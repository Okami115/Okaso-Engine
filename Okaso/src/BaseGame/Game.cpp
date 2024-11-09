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
    sprite = new Sprite("C:/Users/tomas/Escritorio/Okaso-Engine/Okaso/res/Assets/atlas.png", 0, 0, 3, 1, 1200, 1040, 120, 130);
    sprite2 = new Sprite("C:/Users/tomas/Escritorio/Okaso-Engine/Okaso/res/Assets/atlas.png", 0, 0, 3, 1, 1200, 1040, 120, 130);
    background = new Sprite("C:/Users/tomas/Escritorio/Okaso-Engine/Okaso/res/Assets/background.jpg", 0, 0, 1, 1, 2560, 1440, 2560, 1440);

    idle = Animation(0, 0, 3, 1, 1200, 1040, 120, 130);
    down = Animation(0, 520, 10, 1, 1200, 1040, 120, 130);
    left = Animation(0, 650, 10, 1, 1200, 1040, 120, 130);
    up = Animation(0, 780, 10, 1, 1200, 1040, 120, 130);
    right = Animation(0, 910, 10, 1, 1200, 1040, 120, 130);

    currentAnimationState = AnimationState::idle;

    sprite->SetScale(120, 130, 1);
    sprite2->SetScale(120, 130, 1);
    background->SetScale(800, 800, 0);
    sprite2->SetPosition(sprite2->GetPosition().x, sprite2->GetPosition().y + 200, 0);
    sprite2->ForcePreviousPosAsCurrentPos();
    sprite2->SetColor(1, 0, 0);
}

void Game::update()
{
    newAnimationState = AnimationState::idle;

    if (input->isKeyPressed(KEY_W))
    {
        sprite->Translate(0, 0.1f, 0);
        Colitions::CheckCollitions(sprite, sprite2);
        newAnimationState = AnimationState::up;
    }
    if (input->isKeyPressed(KEY_A))
    {
        sprite->Translate(-0.1f, 0, 0);
        Colitions::CheckCollitions(sprite, sprite2);
        newAnimationState = AnimationState::left;
    }
    if (input->isKeyPressed(KEY_S))
    {
        sprite->Translate(0, -0.1f, 0);
        Colitions::CheckCollitions(sprite, sprite2);
        newAnimationState = AnimationState::down;
    }
    if (input->isKeyPressed(KEY_D))
    {
        sprite->Translate(0.1f, 0, 0);
        Colitions::CheckCollitions(sprite, sprite2);
        newAnimationState = AnimationState::right;
    }

    if (newAnimationState != currentAnimationState)
    {
        switch (newAnimationState)
        {
        case AnimationState::idle:
            sprite->ChangeAnimation(idle);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::down:
            sprite->ChangeAnimation(down);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::left:
            sprite->ChangeAnimation(left);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::up:
            sprite->ChangeAnimation(up);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::right:
            sprite->ChangeAnimation(right);
            currentAnimationState = newAnimationState;
            break;
        default:
            break;
        }
    }

    if (Colitions::CheckCollitions(sprite, sprite2))
    {
        cout << "Collision" << endl;
    }

    background->Draw();

    sprite2->UpdateAnimation();
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
