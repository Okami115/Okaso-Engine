#pragma once
#include <iostream>
#include "../../libs/GLEW/Include/glew.h"
#include "../../libs/GLFW/Include/glfw3.h"
#include "../Window/Window.h"

using namespace std;

class Renderer
{
public:
    Renderer(Window* window);
    Renderer(Window* window, GLbitfield mask);
    ~Renderer();
    void RenderScreen();
    void SetWindow(Window* window);
    void Setbitfield(GLbitfield mask);
    GLbitfield Getbitfield();
    void DrawTriangle();
    void InitTriangle();
private:
    Window* GLFWW;
    GLbitfield mask;
};
