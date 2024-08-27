#include "renderer.h"
using namespace OkasoEngine_Utilities;
namespace OkasoEngine_Render
{
    Renderer* Renderer::rendererInstance = nullptr;
    Renderer::Renderer(OkasoEngine_Window::Window* window, GLbitfield mask)
    {
        this->GLFWW = window;
        this->mask = mask;
        rendererInstance = this;
        OkasoDebuger::OKE_Debug("INIT :: Renderer",Info_L);
    }

    Renderer::~Renderer()
    {
        OkasoDebuger::OKE_Debug("DELETE :: Renderer",Info_L);
    }

    void Renderer::BeginDrawing()
    {
        /* Render here */
        glClear(mask);
    }

    void Renderer::EndDrawing() 
    {
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

    void Renderer::InitTriangle(float position[6])
    {
        unsigned int buffer;
        /* glGenBuffers Genera Buffers para que los puedas usar
        *  El 1 En este caso es por qie solo queremos un buffer para el dibujado del triangulo
        *  El unsigned int que le pasamos es para asignarle un espacio en memoria para que utilice
        *  este unsigned int buffer seria como el ID del buffer que vamos a generar
        */
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Renderer* Renderer::GetRenderer()
    {
        if (rendererInstance == nullptr)
        {
            rendererInstance = new Renderer();
        }

        return rendererInstance;
    }
}
