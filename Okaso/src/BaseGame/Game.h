#pragma once
#include "BaseGame.h"
#include "../Entity/Entity2D/Shape/Primitives/Triangle.h"

class Game final : public Okaso_Engine
{
private:
    int windowWidth = 800;
    int windowHeight = 400;
    Triangle* triangle;
public:
    Game(int windowWidth,int windowHeight);
    ~Game();
    void init() override;
    void update() override;
    void exit() override;
};
