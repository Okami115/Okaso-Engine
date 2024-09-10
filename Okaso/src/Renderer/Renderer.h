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
    static EXPORT class Renderer final
    {
    public:
        Renderer(OkasoEngine_Window::Window* window = DEFAULT_WINDOW, GLbitfield mask = DEFAULT_MASK);
        ~Renderer();
        void EndDrawing();
        void BeginDrawing();
        void SetWindow(OkasoEngine_Window::Window* window);
        void Setbitfield(GLbitfield mask);
        GLbitfield Getbitfield();
        void DrawShape(unsigned int* VAO);
        void InitShape(float* vertices, int vertexCount, unsigned int* indices, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO);
        static Renderer* GetRenderer();

    private:
        OkasoEngine_Window::Window* GLFWW;
        unsigned int shader;
        static Renderer* rendererInstance;
        GLbitfield mask;
    };
}
