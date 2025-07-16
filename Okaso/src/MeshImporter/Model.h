#pragma once
#include <string>
#include "../Entity/Entity.h"
#include "../Utils/Utils.h"
#include "../Utils/TextureImporter.h"

#include "../../libs/assimp/scene.h"
#include "../../libs/assimp/mesh.h"
#include "../../libs/assimp/material.h"

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

    void SetNewTextures(const char* path, const char* type)
    {
        OkasoEngine_Utilities::Texture texture = OkasoEngine_Utilities::Texture(path, type);
        TextureImporter::InitTexture(path, texture.id);
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

class EXPORT Model : public Entity
{
public:
    Model(const char* path) { loadModel(path); }
    ~Model();
    void Draw() override;

private:
    std::vector<OkasoEngine_Utilities::Texture> textures_loaded;
    std::vector<Mesh> meshes;
    const char* directory;

    void setNewTextures(const char* path, const char* type);
    void loadModel(const char* path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<OkasoEngine_Utilities::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName);
};