#pragma once
#include "BaseGame.h"
#include "../Entity/Entity2D/Shape/Primitives/Triangle.h"
#include "../Entity/Entity2D/Shape/Primitives/Rectangle.h"
#include "../Entity/Entity2D/Sprite/Sprite.h"

enum class AnimationState
{
    idle,
    walk,
    down,
    left,
    up,
    right,
    Push,
    Atack
};

class EXPORT Game final : public Okaso_Engine
{
private:
    int windowWidth = 800;
    int windowHeight = 400;
    Sprite* Knuckles;
    Sprite* rock;
    Sprite* background;

    bool isColicion;

    Animation idle;
    Animation walk;
    Animation atack;
    Animation push;

    AnimationState currentAnimationState;
    AnimationState newAnimationState;
    
public:
    Game(int windowWidth,int windowHeight);
    ~Game();
    void init() override;
    void update() override;
    void exit() override;
};
