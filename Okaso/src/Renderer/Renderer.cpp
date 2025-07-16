#include "renderer.h"
#include "../Utils/FilesReader.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../Camara/Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include <fstream>
#include <vector>

#include "../MeshImporter/Model.h"
#include "../Utils/stb_image.h"
#include "../Utils/Material.h"

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

            OkasoDebuger::OKE_Debug("FAILED IN SHADER COMPILE :: " +
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

    Renderer::Renderer(OkasoEngine_Window::Window* window, Camera* camera, GLbitfield mask)
    {
        this->GLFWW = window;
        this->mask = mask;
        rendererInstance = this;
        OkasoDebuger::OKE_Debug("INIT :: Renderer", Info_L);

        ShaderProgram shaderFile = OkasoUtils::ParseShader("../Okaso/res/shader/basic.abrazo");
        basicShader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);

        shaderFile = OkasoUtils::ParseShader("../Okaso/res/shader/texture.abrazo");
        textureShader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);

        shaderFile = OkasoUtils::ParseShader("../Okaso/res/shader/ligthning.abrazo");
        lightingShader = CreateShader(shaderFile.vertexShader, shaderFile.fragmentShader);

        this->camera = camera;

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
        glEnable(GL_SAMPLE_ALPHA_TO_ONE);
        glFrontFace(GL_CCW);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.1f);

        float aspectRatio = window->GetWindowWidth() / window->GetWindowHeight();

        view = glm::mat4(1.0f);
        proj = glm::perspective(45.0f, aspectRatio, 0.001f, 1000.0f);
        view = glm::lookAt(camera->position, camera->position + camera->forward, camera->up);
    }

    Renderer::~Renderer()
    {
        glDeleteProgram(basicShader);
        glDeleteProgram(textureShader);
        OkasoDebuger::OKE_Debug("DELETE :: Renderer", Info_L);
    }

    void Renderer::BeginDrawing()

    {
        /* Render here */
        view = glm::lookAt(camera->position, camera->position + camera->forward, camera->up);
        OkasoDebuger::OKE_Debug(
            "CAMERA :: Position " + std::to_string(camera->position.x) + " " + std::to_string(camera->position.y) + " "
            + std::to_string(camera->position.z), Info_L);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, index, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

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

        int vertexColorLocation = glGetUniformLocation(basicShader, "objectColor");
        glUniform3f(vertexColorLocation, color.r, color.g, color.b);

        glBindVertexArray(*VAO);
        glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
    }

    void Renderer::Init3DEntity(float* vertex, int vertexCount, unsigned int* index, int indexSize, unsigned int* VBO, unsigned int* EBO, unsigned int* VAO, const char* path, unsigned int* texture)
    {
        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, vertex, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexSize, index, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        InitTexture(path, texture);
    }

    void Renderer::Draw3DEntity(unsigned int VAO, int sizeIndices, glm::vec3 color, glm::mat4x4 model, Material material, unsigned& texture, bool isUsingTexture)
    {
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(lightingShader);

        unsigned int transformLoc = glGetUniformLocation(lightingShader, "model");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &model[0][0]);

        unsigned int projLoc = glGetUniformLocation(lightingShader, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &proj[0][0]);

        unsigned int viewLoc = glGetUniformLocation(lightingShader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        int vertexColorLocation = glGetUniformLocation(lightingShader, "objectColor");
        glUniform3f(vertexColorLocation, color.r, color.g, color.b);

        int useTextureLoc = glGetUniformLocation(lightingShader, "useTexture");
        glUniform1i(useTextureLoc, isUsingTexture);

        int viewPosLocation = glGetUniformLocation(lightingShader, "viewPos");
        glUniform3f(viewPosLocation, camera->position.x, camera->position.y, camera->position.z);

        int dirLightLoc = glGetUniformLocation(lightingShader, "dirLight.direction");
        glUniform3f(dirLightLoc, dirLight.direction.x, dirLight.direction.y, dirLight.direction.z);

        dirLightLoc = glGetUniformLocation(lightingShader, "dirLight.diffuse");
        glUniform3f(dirLightLoc, dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z);

        dirLightLoc = glGetUniformLocation(lightingShader, "dirLight.specular");
        glUniform3f(dirLightLoc, dirLight.specular.x, dirLight.specular.y, dirLight.specular.z);

        dirLightLoc = glGetUniformLocation(lightingShader, "dirLight.ambient");
        glUniform3f(dirLightLoc, dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z);


        for (int i = 0; i < 1; i++)
        {
            int pointLightsLoc = glGetUniformLocation(lightingShader,
                                                      ("pointLights[" + std::to_string(i) + "].position").c_str());
            glUniform3f(pointLightsLoc, pointLight[i].position.x, pointLight[i].position.y, pointLight[i].position.z);

            pointLightsLoc = glGetUniformLocation(lightingShader,
                                                  ("pointLights[" + std::to_string(i) + "].ambient").c_str());
            glUniform3f(pointLightsLoc, pointLight[i].ambient.x, pointLight[i].ambient.y, pointLight[i].ambient.z);

            pointLightsLoc = glGetUniformLocation(lightingShader,
                                                  ("pointLights[" + std::to_string(i) + "].diffuse").c_str());
            glUniform3f(pointLightsLoc, pointLight[i].diffuse.x, pointLight[i].diffuse.y, pointLight[i].diffuse.z);

            pointLightsLoc = glGetUniformLocation(lightingShader,
                                                  ("pointLights[" + std::to_string(i) + "].specular").c_str());
            glUniform3f(pointLightsLoc, pointLight[i].specular.x, pointLight[i].specular.y, pointLight[i].specular.z);

            pointLightsLoc = glGetUniformLocation(lightingShader,
                                                  ("pointLights[" + std::to_string(i) + "].linear").c_str());
            glUniform1f(pointLightsLoc, pointLight[i].linear);

            pointLightsLoc = glGetUniformLocation(lightingShader,
                                                  ("pointLights[" + std::to_string(i) + "].constant").c_str());
            glUniform1f(pointLightsLoc, pointLight[i].constant);

            pointLightsLoc = glGetUniformLocation(lightingShader,
                                                  ("pointLights[" + std::to_string(i) + "].quadratic").c_str());
            glUniform1f(pointLightsLoc, pointLight[i].quadratic);
        }


        int spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.position");
        glUniform3f(spotLightsLoc, spotLight.position.x, spotLight.position.y, spotLight.position.z);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.ambient");
        glUniform3f(spotLightsLoc, spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.diffuse");
        glUniform3f(spotLightsLoc, spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.specular");
        glUniform3f(spotLightsLoc, spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.direction");
        glUniform3f(spotLightsLoc, spotLight.direction.x, spotLight.direction.y, spotLight.direction.z);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.cutOff");
        glUniform1f(spotLightsLoc, spotLight.cutOff);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.quadratic");
        glUniform1f(spotLightsLoc, spotLight.quadratic);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.outerCutOff");
        glUniform1f(spotLightsLoc, spotLight.outerCutOff);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.constant");
        glUniform1f(spotLightsLoc, spotLight.constant);

        spotLightsLoc = glGetUniformLocation(lightingShader, "spotLight.linear");
        glUniform1f(spotLightsLoc, spotLight.linear);

        int materialLoc = glGetUniformLocation(lightingShader, "material.ambient");
        glUniform3f(materialLoc, material.ambient.x, material.ambient.y, material.ambient.z);

        materialLoc = glGetUniformLocation(lightingShader, "material.diffuse");
        glUniform3f(materialLoc, material.diffuse.x, material.diffuse.y, material.diffuse.z);

        materialLoc = glGetUniformLocation(lightingShader, "material.specular");
        glUniform3f(materialLoc, material.specular.x, material.specular.y, material.specular.z);

        materialLoc = glGetUniformLocation(lightingShader, "material.shininess");
        glUniform1f(materialLoc, material.shininess);

        glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
    }

    void Renderer::InitMesh(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO, vector<Vertex> vertices, vector<unsigned int> indices, vector<OkasoEngine_Utilities::Texture> textures)
    {
        glGenVertexArrays(1, VAO);
        glGenBuffers(1, VBO);
        glGenBuffers(1, EBO);

        glBindVertexArray(*VAO);

        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Posición
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        // Normales
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        // Coordenadas de textura
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            InitTexture(textures[i].path.c_str(), &textures[i].id);
        }
    }

    void Renderer::DrawMesh(unsigned int VAO, int sizeIndices, glm::vec3 color, glm::mat4x4 model, Material material, vector<Texture> textures, bool isUsingTexture)
    {
        glBindVertexArray(VAO);

        if (textures.size() > 0)
            glBindTexture(GL_TEXTURE_2D, textures[0].id); // Asumiendo una sola textura

        glUseProgram(lightingShader);

        glUniformMatrix4fv(glGetUniformLocation(lightingShader, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader, "projection"), 1, GL_FALSE, &proj[0][0]);

        glUniform3f(glGetUniformLocation(lightingShader, "objectColor"), color.r, color.g, color.b);
        glUniform1i(glGetUniformLocation(lightingShader, "useTexture"), isUsingTexture);

        glUniform3f(glGetUniformLocation(lightingShader, "viewPos"), camera->position.x, camera->position.y, camera->position.z);

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader, "dirLight.direction"), dirLight.direction.x, dirLight.direction.y, dirLight.direction.z);
        glUniform3f(glGetUniformLocation(lightingShader, "dirLight.diffuse"), dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader, "dirLight.specular"), dirLight.specular.x, dirLight.specular.y, dirLight.specular.z);
        glUniform3f(glGetUniformLocation(lightingShader, "dirLight.ambient"), dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z);

        // Point lights
        for (int i = 0; i < 1; i++)
        {
            std::string prefix = "pointLights[" + std::to_string(i) + "].";
            glUniform3f(glGetUniformLocation(lightingShader, (prefix + "position").c_str()), pointLight[i].position.x, pointLight[i].position.y, pointLight[i].position.z);
            glUniform3f(glGetUniformLocation(lightingShader, (prefix + "ambient").c_str()), pointLight[i].ambient.x, pointLight[i].ambient.y, pointLight[i].ambient.z);
            glUniform3f(glGetUniformLocation(lightingShader, (prefix + "diffuse").c_str()), pointLight[i].diffuse.x, pointLight[i].diffuse.y, pointLight[i].diffuse.z);
            glUniform3f(glGetUniformLocation(lightingShader, (prefix + "specular").c_str()), pointLight[i].specular.x, pointLight[i].specular.y, pointLight[i].specular.z);
            glUniform1f(glGetUniformLocation(lightingShader, (prefix + "linear").c_str()), pointLight[i].linear);
            glUniform1f(glGetUniformLocation(lightingShader, (prefix + "constant").c_str()), pointLight[i].constant);
            glUniform1f(glGetUniformLocation(lightingShader, (prefix + "quadratic").c_str()), pointLight[i].quadratic);
        }

        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader, "spotLight.position"), spotLight.position.x, spotLight.position.y, spotLight.position.z);
        glUniform3f(glGetUniformLocation(lightingShader, "spotLight.ambient"), spotLight.ambient.x, spotLight.ambient.y, spotLight.ambient.z);
        glUniform3f(glGetUniformLocation(lightingShader, "spotLight.diffuse"), spotLight.diffuse.x, spotLight.diffuse.y, spotLight.diffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader, "spotLight.specular"), spotLight.specular.x, spotLight.specular.y, spotLight.specular.z);
        glUniform3f(glGetUniformLocation(lightingShader, "spotLight.direction"), spotLight.direction.x, spotLight.direction.y, spotLight.direction.z);
        glUniform1f(glGetUniformLocation(lightingShader, "spotLight.cutOff"), spotLight.cutOff);
        glUniform1f(glGetUniformLocation(lightingShader, "spotLight.outerCutOff"), spotLight.outerCutOff);
        glUniform1f(glGetUniformLocation(lightingShader, "spotLight.linear"), spotLight.linear);
        glUniform1f(glGetUniformLocation(lightingShader, "spotLight.constant"), spotLight.constant);
        glUniform1f(glGetUniformLocation(lightingShader, "spotLight.quadratic"), spotLight.quadratic);

        // Material
        glUniform3f(glGetUniformLocation(lightingShader, "material.ambient"), material.ambient.x, material.ambient.y, material.ambient.z);
        glUniform3f(glGetUniformLocation(lightingShader, "material.diffuse"), material.diffuse.x, material.diffuse.y, material.diffuse.z);
        glUniform3f(glGetUniformLocation(lightingShader, "material.specular"), material.specular.x, material.specular.y, material.specular.z);
        glUniform1f(glGetUniformLocation(lightingShader, "material.shininess"), material.shininess);

        glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
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

    void Renderer::InitTexture(const char* path, unsigned int* texture)
    {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float borderColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        int width, height, nrChannels;

        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

        if (data)
        {
            OkasoDebuger::OKE_Debug("GOOD :: INIT TEXTURE", Info_L);

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
            OkasoDebuger::OKE_Debug("ERROR :: INIT TEXTURE", Error_L);
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
