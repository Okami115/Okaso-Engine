﻿#include "renderer.h"
#include "../Utils/FilesReader.h"

using namespace OkasoEngine_Utilities;

namespace OkasoEngine_Render
{
    static int CompileProgram(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();

        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char* message = (char*)alloca(lenght * sizeof(char));
            glGetShaderInfoLog(id, lenght, &lenght, message);

            OkasoDebuger::OKE_Debug("FAILED IN SHADER COMPILE :: "+
                (string)(type == GL_VERTEX_SHADER ? "VERTEX SHADER" : "FRAGMENT SHADER")
                + (string)message, Fatal_L);
        }


        return id;
    }

    static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileProgram(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileProgram(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;

    }

    Renderer* Renderer::rendererInstance = nullptr;
    Renderer::Renderer(OkasoEngine_Window::Window* window, GLbitfield mask)
    {
        this->GLFWW = window;
        this->mask = mask;
        rendererInstance = this;
        OkasoDebuger::OKE_Debug("Renderer Created",Info_L);
    }

    Renderer::~Renderer()
    {
        OkasoDebuger::OKE_Debug("Renderer Deleted",Info_L);
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

        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

        ShaderProgram shaderFile = OkasoUtils::ParseShader("res/shader/basic.abrazo");

        unsigned int shader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);
        glUseProgram(shader);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteProgram(shader);
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
