#pragma once
#include <iostream>
#include "../../libs/GLEW/Include/glew.h"
#include "../Window/Window.h"

using namespace std;

namespace OkasoEngine_Render
{
    static  OkasoEngine_Window::Window* DEFAULT_WINDOW = new OkasoEngine_Window::Window();
    static  GLbitfield DEFAULT_MASK = GL_COLOR_BUFFER_BIT;
    class Renderer final
    {
    public:
        Renderer(OkasoEngine_Window::Window* window, GLbitfield mask = DEFAULT_MASK);
        ~Renderer();
        void RenderScreen();
        void SetWindow(OkasoEngine_Window::Window* window);
        void Setbitfield(GLbitfield mask);
        GLbitfield Getbitfield();
        void DrawTriangle();
        void InitTriangle();

    private:
        OkasoEngine_Window::Window* GLFWW;
        GLbitfield mask;
    };
}
