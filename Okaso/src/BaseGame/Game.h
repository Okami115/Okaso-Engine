#pragma once
#include "BaseGame.h"
#include "../Entity/Entity2D/Sprite/Sprite.h"


class EXPORT Game final : public Okaso_Engine
{
private:
    int windowWidth = 800;
    int windowHeight = 400;
    shape::Triangle* triangle;
    
public:
    Game(int windowWidth,int windowHeight);
    ~Game();
    void init() override;
    void update() override;
    void exit() override;
};
