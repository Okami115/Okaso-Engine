#include "renderer.h"
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
        OkasoDebuger::OKE_Debug("INIT :: Renderer",Info_L);

        ShaderProgram shaderFile = OkasoUtils::ParseShader("res/shader/basic.abrazo");

        shader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);

    }

    Renderer::~Renderer()
    {
        glDeleteProgram(shader);
        OkasoDebuger::OKE_Debug("DELETE :: Renderer",Info_L);
    }

    void Renderer::BeginDrawing()
    {
        /* Render here */
        glClear(mask);
        glUseProgram(shader);
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

    void Renderer::DrawShape(unsigned int* VAO)
    {
        glUseProgram(shader);
        glBindVertexArray(*VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Renderer::InitShape(float* vertices, int vertexCount, unsigned int* indices, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO)
    {

        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexSize, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
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
