#include "Model.h"

Model::~Model()
{
    
}

void Model::Draw()
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(renderer, model);
}

