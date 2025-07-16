#pragma once
#include "BaseGame.h"
#include "Entity/Entity3D/Cube.h"
#include "../MeshImporter/Model.h"


class EXPORT Game final : public Okaso_Engine
{
private:
    int windowWidth = 800;
    int windowHeight = 400;
    Cube* cube;
    Model* modelA;
    Model* modelB;
    Model* modelC;
    
public:
    Game(int windowWidth,int windowHeight);
    ~Game();
    void init() override;
    void update() override;
    void exit() override;
};
