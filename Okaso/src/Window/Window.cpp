#include "window.h"
using namespace OkasoEngine_Utilities;
namespace OkasoEngine_Window
{
    /// <summary>
    /// Creates A new Window
    /// <para> width is for the window initial width
    /// <para> height is for the window initial height
    /// <para> title is for the window Title
    /// </summary>
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

    /// <summary>
    /// Initialize GLFW Window
    /// </summary>
    void Window::initWindow()
    {
        this->GlfWindow = glfwCreateWindow(width, height, title, monitor, GlfWindow);

        /* Make the window's context current */
        glfwMakeContextCurrent(GlfWindow);
        OkasoDebuger::OKE_Debug("INIT :: Window",Info_L);
    }

    /// <summary>
    /// Destroys the Created Window
    /// </summary>
    void Window::destroyWindow()
    {
        OkasoDebuger::OKE_Debug("DELETE :: Window",Info_L);
        glfwDestroyWindow(GlfWindow);
    }

    /// <summary>
    /// Returns the Created Window
    /// </summary>
    GLFWwindow* Window::getWindow()
    {
        return GlfWindow;
    }
}

