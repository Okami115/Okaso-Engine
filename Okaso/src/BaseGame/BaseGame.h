#pragma once
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Entity/Entity2D/Shape/Primitives/Triangle.h"
#include "../Utils/Utils.h"

class EXPORT Okaso_Engine
{
public:
     Okaso_Engine();
    ~Okaso_Engine();
    void gameLoop();
    virtual void update();
    virtual void init();
    virtual void exit();
private:
    OkasoEngine_Render::Renderer* renderer;
    OkasoEngine_Window::Window* window;
    void initGame();
    void endGame();
};
