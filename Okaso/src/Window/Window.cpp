#include "window.h"
using namespace OkasoEngine_Utilities;
namespace OkasoEngine_Window
{
    Window::Window(int width,int height, const char* title, GLFWmonitor* monitor,GLFWwindow* window)
    {
        this->width = width;
        this->height = height;
        this->title = title;
        this->monitor = monitor;
        this->GlfWindow = window;
        initWindow();
    }

    Window::~Window()
    {
        destroyWindow();
    }
    
    void Window::initWindow()
    {
        this->GlfWindow = glfwCreateWindow(width, height, title, monitor, GlfWindow);

        /* Make the window's context current */
        glfwMakeContextCurrent(GlfWindow);
        OkasoDebuger::OKE_Debug("INIT :: Window",Info_L);
    }

    
    void Window::destroyWindow()
    {
        OkasoDebuger::OKE_Debug("DELETE :: Window",Info_L);
        glfwDestroyWindow(GlfWindow);
    }
    
    GLFWwindow* Window::getWindow()
    {
        return GlfWindow;
    }
}

