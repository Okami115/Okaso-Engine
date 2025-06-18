#include "Camera.h"

Camera::Camera(OkasoEngine_Input::Input* input)
{
    position = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
    right = glm::vec3(1, 0, 0);
    forward = glm::vec3(0, 0, -1);

    UpdateVectors();
    
    this->input = input;
}

void Camera::Translate()
{
    if (input != nullptr)
    {
        if(input->isKeyPressed(KEY_W))
        {
            position -= forward * 0.1f;
        }
        if(input->isKeyPressed(KEY_S))
        {
            position += forward * 0.1f;
        }
        if(input->isKeyPressed(KEY_A))
        {
            position -= right * 0.1f;
        }
        if(input->isKeyPressed(KEY_D))
        {
            position += right * 0.1f;
        }
    }
}

void Camera::Rotate()
{
    if (input != nullptr)
    {
        float rotationSpeed = 1.0f;

        if (input->isKeyPressed(KEY_LEFT))
        {
            yaw -= rotationSpeed;
        }
        if (input->isKeyPressed(KEY_RIGHT))
        {
            yaw += rotationSpeed;
        }
        if (input->isKeyPressed(KEY_UP))
        {
            pitch += rotationSpeed;
        }
        if (input->isKeyPressed(KEY_DOWN))
        {
            pitch -= rotationSpeed;
        }
        
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        UpdateVectors();
    }
}

void Camera::UpdateVectors()
{
    glm::vec3 newForward;
    newForward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newForward.y = sin(glm::radians(pitch));
    newForward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(newForward);
    
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
}