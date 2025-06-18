#pragma once
#include "../glm/glm.hpp"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 forward;
    Camera();
    void Translate();
};
