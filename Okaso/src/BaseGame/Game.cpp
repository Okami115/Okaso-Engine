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
    Knuckles = new Sprite("C:/Users/Aula 1/Desktop/Okaso-Engine/Okaso/res/Assets/Knuckles_Sprite_Sheet.png", 0, 0, 1, 1,
                          646, 473, 35, 40);
    rock = new Sprite("C:/Users/Aula 1/Desktop/Okaso-Engine/Okaso/res/Assets/Rock.jfif", 75, 17, 1, 1, 244, 207, 85,
                      60);
    background = new Sprite("C:/Users/Aula 1/Desktop/Okaso-Engine/Okaso/res/Assets/greenhills_background.jpg", 0, 0, 1,
                            1, 1028, 720, 1028, 720);

    idle = Animation(0, 0, 1, 1, 646, 473, 35, 40);
    right = Animation(0, 44, 8, 1, 646, 473, 41, 40);
    spin = Animation(0, 128, 6, 1, 646, 473, 32, 28);
    pushright = Animation(425, 90, 4, 1, 646, 473, 35, 40);

    currentAnimationState = AnimationState::idle;

    Knuckles->SetScale(50, 50, 1);
    Knuckles->SetPosition(Knuckles->GetPosition().x - 300, Knuckles->GetPosition().y - 250, 0);
    Knuckles->ForcePreviousPosAsCurrentPos();
    rock->SetScale(120, 130, 1);
    rock->SetPosition(rock->GetPosition().x + 300, rock->GetPosition().y - 230, 0);
    rock->ForcePreviousPosAsCurrentPos();
    background->SetScale(800, 800, 0);
}

void Game::update()
{
    newAnimationState = AnimationState::idle;

    if (Colitions::CheckCollitions(rock, Knuckles))
    {
        rock->Translate(2.0f, 0, 0);
    }

    if (input->isKeyPressed(KEY_W))
    {
        Knuckles->Translate(0, 2.0f, 0);
        Colitions::CheckCollitions(Knuckles, rock);
        newAnimationState = AnimationState::right;
    }
    if (input->isKeyPressed(KEY_A))
    {
        Knuckles->Translate(-2.0f, 0, 0);
        Knuckles->SetRotation(0, 180.0f, 0);
        Colitions::CheckCollitions(Knuckles, rock);
        newAnimationState = AnimationState::right;
    }

    if (input->isKeyPressed(KEY_A) && input->isKeyPressed(KEY_C))
    {
        Knuckles->Translate(-2.0f, 0, 0);
        Knuckles->SetRotation(0, 180.0f, 0);
        Colitions::CheckCollitions(Knuckles, rock);
        newAnimationState = AnimationState::spin;
    }

    if (input->isKeyPressed(KEY_D))
    {
        Knuckles->Translate(2.0f, 0, 0);
        Knuckles->SetRotation(0, 0, 0);
        if (Colitions::CheckCollitions(Knuckles, rock))
            newAnimationState = AnimationState::pushRight;
        else
            newAnimationState = AnimationState::right;
    }

    if (input->isKeyPressed(KEY_D) && input->isKeyPressed(KEY_C))
    {
        Knuckles->Translate(2.5f, 0, 0);
        Colitions::CheckCollitions(Knuckles, rock);
        newAnimationState = AnimationState::spin;
    }

    if (newAnimationState != currentAnimationState)
    {
        switch (newAnimationState)
        {
        case AnimationState::idle:
            Knuckles->ChangeAnimation(idle);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::right:
            Knuckles->ChangeAnimation(right);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::spin:
            Knuckles->ChangeAnimation(spin);
            currentAnimationState = newAnimationState;
            break;
        case AnimationState::pushRight:
            Knuckles->ChangeAnimation(pushright);
            currentAnimationState = newAnimationState;
            break;
        default:
            break;
        }
    }


    background->Draw();

    rock->UpdateAnimation();
    rock->Draw();

    Knuckles->UpdateAnimation();
    Knuckles->Draw();
}

void Game::exit()
{
    delete triangle;
    delete rectangle;
    delete Knuckles;
}
