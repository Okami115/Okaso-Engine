#include "window.h"
using namespace OkasoEngine_Utilities;
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
        OkasoDebuger::_debuger->OKE_Debug("Window Created",Info_L);
    }

    void Window::destroyWindow()
    {
        OkasoDebuger::_debuger->OKE_Debug("Window Destroyed",Info_L);
    }

    GLFWwindow* Window::getWindow()
    {
        return GlfWindow;
    }
}

