﻿#pragma once
#include "../../libs/GLEW/Include/glew.h"
#include "../../libs/GLFW/Include/glfw3.h"

class Window
{
private:
    GLFWwindow* GlfWindow;
    int width;
    int height;
    const char* title;
    GLFWmonitor* monitor;
    GLFWwindow* share;
    void initWindow();
    void destroyWindow();
public:

    Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    Window(int width, int height, const char* title);
    Window(int width, int height);
    ~Window();
    GLFWwindow* getWindow();
};

