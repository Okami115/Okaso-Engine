#pragma once
#include "../../libs/GLEW/Include/glew.h"
#include "../../libs/GLFW/Include/glfw3.h"
#include "../Utils/Utils.h"
namespace OkasoEngine_Window
{
#pragma region Default Values For Window creation
    static const int DEFAULT_WIDTH = 1240;
    static const int DEFAULT_HEIGHT = 720;
    static const char* DEFAULT_TITLE = "OkasoEngine_Window";
    static  GLFWmonitor* DEFAULT_MONITOR = NULL;
    static  GLFWwindow* DEFAULT_WINDOW = NULL;
#pragma endregion
    class EXPORT Window final
    {
    public:
        Window(int width = DEFAULT_WIDTH,int height = DEFAULT_HEIGHT, const char* title = DEFAULT_TITLE
        , GLFWmonitor* monitor = DEFAULT_MONITOR,GLFWwindow* window = DEFAULT_WINDOW);
        ~Window();
        GLFWwindow* getWindow();
    private:
        int width;
        int height;
        const char* title;
        GLFWmonitor* monitor;
        GLFWwindow* GlfWindow;
        void initWindow();
        void destroyWindow();
    };
}
