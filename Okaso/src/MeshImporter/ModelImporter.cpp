#include "ModelImporter.h"

#include "../Utils/TextureImporter.h"
#include "../assimp/scene.h"
#include "../assimp/postprocess.h"
#include "../assimp/Importer.hpp"
#include <../assimp/types.h>

void ModelImporter::setNewTextures(const char* path, const char* type)
{
    for (Mesh& mesh : meshes)
    {
        mesh.SetNewTextures(path, type);
    }
}

vector<Mesh> ModelImporter::loadModel(string path, bool invertTexture, OkasoEngine_Render::Renderer renderer)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(
      path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
      aiProcess_JoinIdenticalVertices);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        cout << "ERROR :: ASSIMP ::" << import.GetErrorString() << endl;
        return vector<Mesh>();
    }
    directory = path.substr(0, path.find_last_of('/'));
    
    processNode(scene->mRootNode, scene, invertTexture, renderer);
    
    return meshes;
}

void ModelImporter::processNode(aiNode* node, const aiScene* scene, bool invertTexture, OkasoEngine_Render::Renderer renderer)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
        meshes.push_back(processMesh(mesh, scene, invertTexture, renderer));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, invertTexture, renderer);
    }
}

Mesh ModelImporter::processMesh(aiMesh* mesh, const aiScene* scene, bool invertTexture, OkasoEngine_Render::Renderer renderer)
{
    std::vector<OkasoEngine_Utilities::Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<OkasoEngine_Utilities::Texture> textures;

    // Vértices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        OkasoEngine_Utilities::Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // Índices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    // Material y texturas
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        
        vector<OkasoEngine_Utilities::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", invertTexture);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<OkasoEngine_Utilities::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", invertTexture);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        vector<OkasoEngine_Utilities::Texture> baseColorMaps = loadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_baseColor", invertTexture);
        textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());

        vector<OkasoEngine_Utilities::Texture> normalsMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normals", invertTexture);
        textures.insert(textures.end(), normalsMaps.begin(), normalsMaps.end());

        std::vector<OkasoEngine_Utilities::Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height", invertTexture);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        std::vector<OkasoEngine_Utilities::Texture> metallicMaps = loadMaterialTextures(material, aiTextureType_METALNESS, "texture_metalness", invertTexture);
        textures.insert(textures.end(), metallicMaps.begin(), metallicMaps.end());

        std::vector<OkasoEngine_Utilities::Texture> roughnessMaps = loadMaterialTextures(material, aiTextureType_SHININESS, "texture_roughness", invertTexture);
        textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());
    }
    
    return Mesh(vertices, indices, textures, &renderer);
}

std::vector<OkasoEngine_Utilities::Texture> ModelImporter::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName, bool invertTexture)
{
    std::vector<OkasoEngine_Utilities::Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        string name = str.C_Str();
        string dir = directory;
        string path = dir + "/" + name;

        // Evitar cargar la misma textura más de una vez
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (textures_loaded[j].path == path) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            OkasoEngine_Utilities::Texture texture = OkasoEngine_Utilities::Texture(typeName, path.c_str());
            TextureImporter::InitTexture(path.c_str(), texture.id, invertTexture);
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}