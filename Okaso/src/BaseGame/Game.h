#pragma once
#include "BaseGame.h"
#include "../Entity/Entity2D/Shape/Primitives/Triangle.h"
#include "../Entity/Entity2D/Shape/Primitives/Rectangle.h"
#include "../Entity/Entity2D/Sprite/Sprite.h"

enum class AnimationState
{
    idle,
    right,
    spin,
    pushRight
};

class EXPORT Game final : public Okaso_Engine
{
private:
    int windowWidth = 800;
    int windowHeight = 400;
    shape::Triangle* triangle;
    shape::Rectangle* rectangle;
    Sprite* Knuckles;
    Sprite* rock;
    Sprite* background;

    Animation idle;
    Animation left;
    Animation right;
    Animation up;
    Animation down;
    Animation spin;
    Animation pushright;

    AnimationState currentAnimationState;
    AnimationState newAnimationState;
    
public:
    Game(int windowWidth,int windowHeight);
    ~Game();
    void init() override;
    void update() override;
    void exit() override;
};
