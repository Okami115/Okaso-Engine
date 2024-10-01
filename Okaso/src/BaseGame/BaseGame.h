#pragma once
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Entity/Entity2D/Shape/Primitives/Triangle.h"
#include "../Utils/Utils.h"
#include "../Input/Input.h"
#include "../Input/KeyCode.h"


class EXPORT Okaso_Engine
{
public:
    /// <summary>
    /// Create The Engine 
    /// </summary>
    Okaso_Engine();

    /// <summary>
    /// Destroy The Engine 
    /// </summary>
    ~Okaso_Engine();

    /// <summary>
    /// Contains The engine core loop
    /// </summary>
    void gameLoop();

    /// <summary>
    /// Virtual Function For the engine loop Implementation
    /// </summary>
    virtual void update();

    /// <summary>
    /// Virtual Function For the initialization of the engine implementation
    /// </summary>
    virtual void init();

    /// <summary>
    /// Virtual Function For the destruction of the engine implementation
    /// </summary>
    virtual void exit();

private:
    OkasoEngine_Render::Renderer* renderer;
    OkasoEngine_Window::Window* window;

    /// <summary>
    /// Initialize the engine core 
    /// </summary>
    void initGame();

    /// <summary>
    /// Destroy the engine core 
    /// </summary>
    void endGame();

protected:
    OkasoEngine_Input::Input* input;
};
