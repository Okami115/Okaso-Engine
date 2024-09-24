#pragma once
#include "BaseGame.h"
#include "../Entity/Entity2D/Shape/Primitives/Triangle.h"
#include "../Entity/Entity2D/Shape/Primitives/Rectangle.h"

class EXPORT Game final : public Okaso_Engine
{
private:
    int windowWidth = 800;
    int windowHeight = 400;
    shape::Triangle* Yellowtriangle;
    shape::Triangle* Pinktriangle;
public:
    Game(int windowWidth,int windowHeight);
    ~Game();
    void init() override;
    void update() override;
    void exit() override;
};
