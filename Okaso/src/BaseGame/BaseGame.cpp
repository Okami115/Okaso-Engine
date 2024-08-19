#include "baseGame.h"
using namespace OkasoEngine_Utilities;
Okaso_Engine::Okaso_Engine()
{
    OkasoDebuger::_debuger->OkasoDebugerSetActive(true);
    OkasoDebuger::_debuger->OkasoDebug("Init Debugger",LogPriority::Info_L);
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
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = new OkasoEngine_Window::Window(640, 480, "Okaso_Engine V1.0 - 130824", NULL, NULL);

    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW::FAIL::INIT" << endl;
    }

    if (!window)
    {
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