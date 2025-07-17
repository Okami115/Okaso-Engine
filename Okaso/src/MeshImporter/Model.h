#pragma once
#include <string>

#include "../Entity/Entity.h"
#include "../Utils/Utils.h"
#include "mesh.h"
#include "ModelImporter.h"

class EXPORT Model : public Entity
{
public:
    Model(const char* path, bool invertTexture) { meshes = renderer->modelImporter->loadModel(path, invertTexture, *renderer); }
    ~Model();
    void Draw() override;

private:
    std::vector<Mesh> meshes;
    
};
