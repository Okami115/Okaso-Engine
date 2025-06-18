#include "Camera.h"

Camera::Camera(OkasoEngine_Input::Input* input, OkasoEngine_Window::Window* window)
{
    position = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
    right = glm::vec3(1, 0, 0);
    forward = glm::vec3(0, 0, -1);

    UpdateVectors();
    
    this->input = input;
    this->window = window;
}

void Camera::Translate()
{
    if (input != nullptr)
    {
        if (!isMouseEnable)
        {
            if(input->isKeyPressed(KEY_LEFT_SHIFT))
                speed = 5.0f;
            else
                speed = 2.5f;

            
            if(input->isKeyPressed(KEY_W))
            {
                position += forward * 0.1f * speed;
            }
            if(input->isKeyPressed(KEY_S))
            {
                position -= forward * 0.1f * speed;
            }
            if(input->isKeyPressed(KEY_A))
            {
                position -= right * 0.1f * speed;
            }
            if(input->isKeyPressed(KEY_D))
            {
                position += right * 0.1f * speed;
            }
        }

        if (input->isKeyPressed(KEY_ESCAPE))
        {
            if (input->isKeyDown(GLFW_KEY_ESCAPE))
            {
                isMouseEnable = !isMouseEnable;

                glfwSetInputMode(window->getWindow(),
                    GLFW_CURSOR,
                    isMouseEnable ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
            }
        }
    }
}

void Camera::Rotate()
{
    if (input != nullptr)
    {
        if (!isMouseEnable)
        {
            float dx = input->GetMouseDeltaX();
            float dy = input->GetMouseDeltaY();

            yaw += dx * sensitivity;
            pitch -= dy * sensitivity;
            
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;
        }

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