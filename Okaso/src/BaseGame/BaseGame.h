#pragma once
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Utils/Utils.h"
class Okaso_Engine
{
public:
    Okaso_Engine();
    ~Okaso_Engine();
    void gameLoop();
private:
    OkasoEngine_Render::Renderer* renderer;
    OkasoEngine_Window::Window* window;
    void initGame();
    void endGame();
};
