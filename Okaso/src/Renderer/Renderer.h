#pragma once
#include "../../libs/GLEW/Include/glew.h"
#include "../Window/Window.h"
#include "../Utils/Utils.h"
namespace OkasoEngine_Render
{
#pragma region Default Values For Renderer creation
    static  OkasoEngine_Window::Window* DEFAULT_WINDOW = NULL;
    static  GLbitfield DEFAULT_MASK = GL_COLOR_BUFFER_BIT;
#pragma endregion
    static class Renderer final
    {
    public:
        Renderer(OkasoEngine_Window::Window* window = DEFAULT_WINDOW, GLbitfield mask = DEFAULT_MASK);
        ~Renderer();
        void RenderScreen();
        void SetWindow(OkasoEngine_Window::Window* window);
        void Setbitfield(GLbitfield mask);
        GLbitfield Getbitfield();
        void DrawTriangle();
        void InitTriangle(float position[6]);
        static Renderer* GetRenderer();

    private:
        OkasoEngine_Window::Window* GLFWW;
        static Renderer* rendererInstance;
        GLbitfield mask;
    };
}
