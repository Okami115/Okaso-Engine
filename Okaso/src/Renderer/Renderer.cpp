#include "renderer.h"
#include "../Utils/FilesReader.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

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

        ShaderProgram shaderFile = OkasoUtils::ParseShader("../Okaso/res/shader/basic.abrazo");

        shader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);
        
        view = glm::mat4(1.0f);
        proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0), glm::vec3(0,1,0));
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

    void Renderer::DrawShape(unsigned int* VAO, glm::mat4 model, int elementsCount, glm::vec3 color)
    {
        glUseProgram(shader);

        unsigned int transformLoc = glGetUniformLocation(shader, "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model[0][0]);

        unsigned int projLoc = glGetUniformLocation(shader, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

        unsigned int viewLoc = glGetUniformLocation(shader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        int vertexColorLocation = glGetUniformLocation(shader, "ourColor");
        glUniform3f(vertexColorLocation, color.r, color.g, color.b);

        glBindVertexArray(*VAO);
        glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
    }

    void Renderer::InitShape(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO)
    {

        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexSize, index, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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
