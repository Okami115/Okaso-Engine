#pragma once
#include "../glm/glm.hpp"
#include "../Input/Input.h"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 forward;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;
    float speed = 2.5f;
    float sensitivity = 0.1f;
    Camera(OkasoEngine_Input::Input* input = nullptr, OkasoEngine_Window::Window* window = nullptr);
    void Translate();
    void Rotate();
    void UpdateVectors();
private:
    OkasoEngine_Window::Window* window;
    OkasoEngine_Input::Input* input;
    bool isMouseEnable = false;
};
