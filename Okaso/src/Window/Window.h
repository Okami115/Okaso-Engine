#pragma once
#include "../../libs/GLEW/Include/glew.h"
#include "../../libs/GLFW/Include/glfw3.h"

namespace OkasoEngine_Window
{
#pragma region Default Values For Window creation
    static const int DEFAULT_WIDTH = 1240;
    static const int DEFAULT_HEIGHT = 720;
    static const char* DEFAULT_TITLE = "OkasoEngine_Window";
    static  GLFWmonitor* DEFAULT_MONITOR = NULL;
    static  GLFWwindow* DEFAULT_SHARE = NULL;
#pragma endregion
    class Window final
    {
    public:
        Window(int width = DEFAULT_WIDTH,int height = DEFAULT_HEIGHT, const char* title = DEFAULT_TITLE
        , GLFWmonitor* monitor = DEFAULT_MONITOR,GLFWwindow* share = DEFAULT_SHARE);
        ~Window();
        GLFWwindow* getWindow();
    private:
        GLFWwindow* GlfWindow;
        int width;
        int height;
        const char* title;
        GLFWmonitor* monitor;
        GLFWwindow* share;
        void initWindow();
        void destroyWindow();
    };
}
