#include "renderer.h"
#include "../Utils/FilesReader.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../Utils/stb_image.h"

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
        basicShader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);
        
        shaderFile = OkasoUtils::ParseShader("../Okaso/res/shader/texture.abrazo");
        textureShader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);

        glEnable(GL_DEPTH);
        glDepthFunc(GL_LESS);

        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        glEnable(GL_SAMPLE_ALPHA_TO_ONE);
        glFrontFace(GL_CCW);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_ALPHA);
        glAlphaFunc(GL_GREATER, 0.1f);

        view = glm::mat4(1.0f);
        proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0), glm::vec3(0,1,0));
    }

    Renderer::~Renderer()
    {
        glDeleteProgram(basicShader);
        glDeleteProgram(textureShader);
        OkasoDebuger::OKE_Debug("DELETE :: Renderer",Info_L);
    }

    void Renderer::BeginDrawing()
    {
        /* Render here */
        glClear(mask);
        glUseProgram(basicShader);
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

    void Renderer::DeleteObjects(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO)
    {
        glDeleteVertexArrays(1, VAO);
        glDeleteBuffers(1, VBO);
        glDeleteBuffers(1, EBO);
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
    
    void Renderer::DrawShape(unsigned int* VAO, glm::mat4 model, int elementsCount, glm::vec3 color)
    {
        glUseProgram(basicShader);

        unsigned int transformLoc = glGetUniformLocation(basicShader, "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model[0][0]);

        unsigned int projLoc = glGetUniformLocation(basicShader, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

        unsigned int viewLoc = glGetUniformLocation(basicShader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        int vertexColorLocation = glGetUniformLocation(basicShader, "ourColor");
        glUniform3f(vertexColorLocation, color.r, color.g, color.b);

        glBindVertexArray(*VAO);
        glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
    }

    void Renderer::InitSprite(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO, const char* path, unsigned int* texture)
    {
        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexSize, index, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        InitTexture(path, texture);
    }

    void Renderer::InitTextureBuffers(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO, unsigned int* texture)
    {
        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexSize, index, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void Renderer::DrawSprite(unsigned int* VAO, glm::mat4 model, int elementsCount, glm::vec3 color, unsigned int* texture)
    {
        glBindTexture(GL_TEXTURE_2D, *texture);

        glUseProgram(textureShader);

        unsigned int transformLoc = glGetUniformLocation(textureShader, "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model[0][0]);

        unsigned int projLoc = glGetUniformLocation(textureShader, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

        unsigned int viewLoc = glGetUniformLocation(textureShader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        int vertexColorLocation = glGetUniformLocation(textureShader, "ourColor");
        glUniform3f(vertexColorLocation, color.r, color.g, color.b);

        glBindVertexArray(*VAO);
        glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
    }

    void Renderer::InitTexture(const char* path, unsigned int* texture)
    {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        int width, height, nrChannels;

        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

        if (data)
        {
            GLenum format;

            if (nrChannels == 1)
            {
                format = GL_RED;
            }
            else if (nrChannels == 3)
            {
                format = GL_RGB;
            }
            else if (nrChannels == 4)
            {
                format = GL_RGBA;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
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
