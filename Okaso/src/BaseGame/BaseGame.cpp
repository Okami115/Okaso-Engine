#include "baseGame.h"
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
        return;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = new OkasoEngine_Window::Window(640, 480, "Okaso_Engine V1.0 - 130824", NULL, NULL);

    if (glewInit() != GLEW_OK)
        OkasoDebuger::OKE_Debug("GLEW::FAIL::INIT",Fatal_L);

    if (!window)
    {
        OkasoDebuger::OKE_Debug("WINDOW::FAIL::INIT",Fatal_L);
        glfwTerminate();
        return;
    }

    renderer = new OkasoEngine_Render::Renderer(window);
}

void Okaso_Engine::gameLoop()
{
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        renderer->RenderScreen();
    }
}

void Okaso_Engine::endGame()
{
    glfwTerminate();
}