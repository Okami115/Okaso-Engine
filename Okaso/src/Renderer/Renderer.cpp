#include "renderer.h"
using namespace OkasoEngine_Utilities;
namespace OkasoEngine_Render
{
    Renderer::Renderer(OkasoEngine_Window::Window* window, GLbitfield mask)
    {
        this->GLFWW = window;
        this->mask = mask;
        OkasoDebuger::_debuger->OKE_Debug("Renderer Created",Info_L);
        InitTriangle();
    }

    Renderer::~Renderer()
    {
        OkasoDebuger::_debuger->OKE_Debug("Renderer Deleted",Info_L);
    }

    void Renderer::RenderScreen() 
    {
        /* Render here */
        glClear(mask);

        DrawTriangle();

        /* Swap front and back buffers */
        glfwSwapBuffers(GLFWW->getWindow());

        /* Poll for and process events */
        glfwPollEvents();



    }

    void Renderer::SetWindow(OkasoEngine_Window::Window* window) 
    {
        GLFWW = window;
    }
    void Renderer::Setbitfield(GLbitfield mask) 
    {
        this->mask = mask;
    }

    GLbitfield Renderer::Getbitfield() 
    {
        return this->mask;
    }

    void Renderer::DrawTriangle()
    {
        glDrawArrays(GL_TRIANGLES, 0, 3.0f);
    }

    void Renderer::InitTriangle()
    {
        float position[6] =
        {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
        };

        unsigned int buffer;

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
