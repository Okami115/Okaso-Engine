﻿#pragma once
#include "../../libs/GLEW/Include/glew.h"
#include "../Window/Window.h"
#include "../Utils/Utils.h"
using namespace std;
namespace OkasoEngine_Render
{
#pragma region Default Values For Renderer creation
    static  OkasoEngine_Window::Window* DEFAULT_WINDOW = new OkasoEngine_Window::Window();
    static  GLbitfield DEFAULT_MASK = GL_COLOR_BUFFER_BIT;
#pragma endregion
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
