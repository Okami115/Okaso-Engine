#pragma once
#include "../../libs/GLEW/Include/glew.h"
#include "../Window/Window.h"
#include "../Utils/Utils.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

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
        void DrawShape(unsigned int* VAO, glm::mat4 model, int vertexCount, glm::vec3 color);
        void InitShape(float* vertices, int vertexCount, unsigned int* indices, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO);
        static Renderer* GetRenderer();
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;

    private:
        OkasoEngine_Window::Window* GLFWW;
        unsigned int shader;
        static Renderer* rendererInstance;
        GLbitfield mask;
        glm::mat4 proj;
        glm::mat4 view;
    };
}
