#pragma once
#include "../Utils/Utils.h"
#include "../Utils/TextureImporter.h"
#include "../Renderer/Renderer.h"


class EXPORT Mesh
{
public:
    std::vector<OkasoEngine_Utilities::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<OkasoEngine_Utilities::Texture> textures;

    Mesh(std::vector<OkasoEngine_Utilities::Vertex> vertices, std::vector<unsigned int> indices, std::vector<OkasoEngine_Utilities::Texture> textures, OkasoEngine_Render::Renderer* renderer)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        VBO = new unsigned int;
        EBO = new unsigned int;
        VAO = new unsigned int;

        renderer->InitMesh(VAO, VBO, EBO, vertices, indices, textures);
    }

    void SetNewTextures(const char* path, const char* type, bool flip = true)
    {
        OkasoEngine_Utilities::Texture texture = OkasoEngine_Utilities::Texture(type, path);
        TextureImporter::InitTexture(path, texture.id, flip);
        textures.push_back(texture);
    };
    
    void Draw(OkasoEngine_Render::Renderer* renderer, glm::mat4 model)
    {
        renderer->DrawMesh(*VAO, indices.size(), glm::vec3(), model, DEFAULT_MATERIAL, textures, true);
    }

private:
    unsigned int* VAO;
    unsigned int* VBO;
    unsigned int* EBO;

};
