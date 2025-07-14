#pragma once
#include "../glm/glm.hpp"

class Light
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class dirLight : public Light
{
public:
    glm::vec3 direction;
};

class pointLight : public Light
{
public:
    glm::vec3 position;
    float constant;
    float quadratic;
    float linear;
};

class spotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float quadratic;
    float outerCutOff;
    float constant;
    float linear;
};
