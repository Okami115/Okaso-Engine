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
        /// <summary>
        /// Creates A Renderer
        /// <para> window : Window for the program to renderise in 
        /// <para> mask : the mask for the window render
        /// </summary>
        Renderer(OkasoEngine_Window::Window* window = DEFAULT_WINDOW, GLbitfield mask = DEFAULT_MASK);
        ~Renderer();
        
        /// <summary>
        /// Begins The Drawing Process of OpenGL
        /// </summary>
        void BeginDrawing();

        /// <summary>
        /// Ends The Drawing Process of OpenGL
        /// </summary>
        void EndDrawing();

        /// <summary>
        /// Set's a new window for the renderer
        /// </summary>
        void SetWindow(OkasoEngine_Window::Window* window);

        /// <summary>
        /// Set's a new mask for the renderer
        /// </summary>
        void Setbitfield(GLbitfield mask);

        /// <summary>
        /// Returns the renderer mask
        /// </summary>
        GLbitfield Getbitfield();

        void DeleteObjects(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO);

        /// <summary>
        /// Creates a new Entity
        /// <para> vertex : Entity vertex
        /// <para> vertexCount : max count of vertex on the shape
        /// <para> index : index of the vertex positions
        /// <para> indexSize : max count of vertex index
        /// <para> VBO : Vertex Buffer Object
        /// <para> EBO : Element Buffer Object 
        /// <para> VAO : Vertex Array Object
        /// </summary>
        void InitShape(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO);

        /// <summary>
        /// Renders a shape
        /// <para> VAO : Vertex Array Object
        /// <para> model : model matrix of the object
        /// <para> vertexCount : max count of vertex on the shape
        /// <para> color : color of the shape
        /// </summary>
        void DrawShape(unsigned int* VAO, glm::mat4 model, int vertexCount, glm::vec3 color);

        void InitSprite(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO, const char* path, unsigned int* texture);

        void InitTextureBuffers(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO, unsigned int* texture);

        void DrawSprite(unsigned int* VAO, glm::mat4 model, int elementsCount, glm::vec3 color, unsigned int* texture);

        void InitTexture(const char* path, unsigned int* texture);

        /// <summary>
        /// Returns the current Renderer
        /// </summary>
        static Renderer* GetRenderer();
        
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;

    private:
        OkasoEngine_Window::Window* GLFWW;
        unsigned int basicShader;
        unsigned int textureShader;
        static Renderer* rendererInstance;
        GLbitfield mask;
        glm::mat4 proj;
        glm::mat4 view;
    };
}
