#pragma once
#include "../glm/glm.hpp"
#include "../Input/Input.h"

class Camera
{
public:
    Camera(OkasoEngine_Input::Input* input = nullptr, OkasoEngine_Window::Window* window = nullptr);
    void Update();
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 forward;
    glm::vec3 target = glm::vec3(0.0f);
    bool isThirdPerson = false;
    float distanceToTarget = 5.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;
    float speed = 2.5f;
    float sensitivity = 0.1f;
private:
    void Translate();
    void Rotate();
    void UpdateVectors();
    OkasoEngine_Window::Window* window;
    OkasoEngine_Input::Input* input;
    bool isMouseEnable = false;
};
