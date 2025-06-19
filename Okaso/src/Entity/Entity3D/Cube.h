#pragma once
#include "../Entity.h"

class EXPORT Cube  : public Entity
{
public:
    Cube();
    ~Cube();
    void Draw() override;
private:
    unsigned int* VBO;
    unsigned int* EBO;
    unsigned int* VAO;
};
