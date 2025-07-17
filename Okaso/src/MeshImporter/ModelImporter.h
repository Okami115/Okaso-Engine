#pragma once
#include "../Utils/Utils.h"
#include "../../libs/assimp/scene.h"
#include "../../libs/assimp/mesh.h"
#include "../../libs/assimp/material.h"
#include "Model.h"

class EXPORT ModelImporter
{
private:
    std::vector<OkasoEngine_Utilities::Texture> textures_loaded;
    std::vector<Mesh> meshes;
    string directory;
    
public:
    void setNewTextures(const char* path, const char* type);
    vector<Mesh> loadModel(string path, bool invertTexture, OkasoEngine_Render::Renderer renderer);
    void processNode(aiNode* node, const aiScene* scene, bool invertTexture, OkasoEngine_Render::Renderer renderer);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, bool invertTexture, OkasoEngine_Render::Renderer renderer);
    std::vector<OkasoEngine_Utilities::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName, bool invertTexture);
};
