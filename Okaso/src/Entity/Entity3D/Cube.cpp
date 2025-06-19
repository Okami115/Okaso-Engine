#include "Cube.h"
Cube::Cube()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Cube", OkasoEngine_Utilities::Info_L);

    float vertices[] = {
        // Front face
        -100.0f, -100.0f,  100.0f,
         100.0f, -100.0f,  100.0f,
        -100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,
        // Back face
        -100.0f, -100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,
         100.0f,  100.0f, -100.0f
    };

    unsigned int indices[] = {
        0, 1, 3, 0, 3, 2,      // Front
        1, 5, 7, 1, 7, 3,      // Right
        5, 4, 6, 5, 6, 7,      // Back
        4, 0, 2, 4, 2, 6,      // Left
        2, 3, 7, 2, 7, 6,      // Top
        4, 5, 1, 4, 1, 0       // Bottom
    };

    VBO = new unsigned int;
    EBO = new unsigned int;
    VAO = new unsigned int;

    renderer->InitShape(vertices, 24, indices, 36, VBO, EBO, VAO);
}

Cube::~Cube()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Cube", OkasoEngine_Utilities::Info_L);
}

void Cube::Draw()
{
    renderer->DrawShape(VAO, model, 36, GetColor());
}