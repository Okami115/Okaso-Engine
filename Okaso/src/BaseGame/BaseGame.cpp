#include "baseGame.h"

Okaso_Engine::Okaso_Engine()
{
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
    window = new Window(640, 480, "Okaso_Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return;
    }
    renderer = new Renderer(window);
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