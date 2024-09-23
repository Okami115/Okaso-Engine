#include "baseGame.h"
#include "../Entity/Entity2D/Entity2D.h"

using namespace OkasoEngine_Utilities;

Okaso_Engine::Okaso_Engine()
{
    OkasoDebuger::OkasoDebugerSetActive(true);
    initGame();
}

Okaso_Engine::~Okaso_Engine()
{
    endGame();
}

void Okaso_Engine::initGame()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        OkasoDebuger::OKE_Debug("GLFW::FAIL::INIT",Fatal_L);
        endGame();
        return;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = new OkasoEngine_Window::Window();
    if (!window)
    {
        OkasoDebuger::OKE_Debug("WINDOW::FAIL::INIT",Fatal_L);
        endGame();
        return;
    }
    
    if (glewInit() != GLEW_OK)
    {
        OkasoDebuger::OKE_Debug("GLEW::FAIL::INIT",Fatal_L);
        endGame();
        return;
    }

    

    renderer = new OkasoEngine_Render::Renderer(window);
    if (!renderer)
    {
        OkasoDebuger::OKE_Debug("RENDERER::FAIL::INIT",Fatal_L);
        endGame();
        return;
    }

    init();
}

void Okaso_Engine::update()
{
    
}

void Okaso_Engine::init()
{
}

void Okaso_Engine::exit()
{
}

void Okaso_Engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        renderer->BeginDrawing();
        update();
        renderer->EndDrawing();
    }
}

void Okaso_Engine::endGame()
{
    exit();
    delete renderer;
    delete window;
    glfwTerminate();
}