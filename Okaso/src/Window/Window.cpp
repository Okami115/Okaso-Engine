#include <iostream>

#include "window.h"

namespace OkasoEngine_Window
{
    
    Window::Window(int width,int height, const char* title, GLFWmonitor* monitor,GLFWwindow* share)
    {
        this->width = width;
        this->height = height;
        this->title = title;
        this->monitor = monitor;
        this->share = share;
        initWindow();
    }

    Window::~Window()
    {
        destroyWindow();
    }

    void Window::initWindow()
    {
        this->GlfWindow = glfwCreateWindow(width, height, title, monitor, share);

        /* Make the window's context current */
        glfwMakeContextCurrent(GlfWindow);
        std::cout << "Window Created" << std::endl;
    }

    void Window::destroyWindow()
    {
        std::cout << "Window Destroyed" << std::endl;
    }

    GLFWwindow* Window::getWindow()
    {
        return GlfWindow;
    }
}

