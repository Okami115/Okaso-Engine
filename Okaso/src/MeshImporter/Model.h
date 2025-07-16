#pragma once
#include <string>
#include "../Entity/Entity.h"
#include "../Utils/Utils.h"

#include "../../libs/assimp/scene.h"
#include "../../libs/assimp/mesh.h"
#include "../../libs/assimp/material.h"

class EXPORT Mesh : public Entity
{
public:
    std::vector<OkasoEngine_Utilities::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<OkasoEngine_Utilities::Texture> textures;

    Mesh(std::vector<OkasoEngine_Utilities::Vertex> vertices, std::vector<unsigned int> indices, std::vector<OkasoEngine_Utilities::Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        renderer->InitMesh(VAO, VBO, EBO, vertices, indices, textures);
    }

    void Draw() override { renderer->DrawMesh(*VAO, indices.size(), glm::vec3(), model, DEFAULT_MATERIAL, textures, true); }

private:
    unsigned int* VAO;
    unsigned int* VBO;
    unsigned int* EBO;

};

class EXPORT Model : public Entity
{
public:
    Model(const std::string& path) { loadModel(path); }
    void Draw() override;

private:
    std::vector<OkasoEngine_Utilities::Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<OkasoEngine_Utilities::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};