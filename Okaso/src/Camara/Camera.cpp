#include "Camera.h"

Camera::Camera()
{
    position = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
    right = glm::vec3(0, 0, 1);
    forward = glm::vec3(0, 0, 1);
}

void Camera::Translate()
{
    position -= forward * 0.1f;
}