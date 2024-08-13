#pragma once
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"

class Okaso_Engine
{
public:
    Okaso_Engine();
    ~Okaso_Engine();
    void gameLoop();
private:
    Renderer* renderer;
    Window* window;
    void initGame();
    void endGame();
};
