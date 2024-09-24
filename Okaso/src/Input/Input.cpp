#include "Input.h"

namespace OkasoEngine_Input
{
    Input::Input(OkasoEngine_Window::Window* engineWindow)
    {
        this->engineWindow = engineWindow;
        std::cout << "Input Created" << std::endl;
    }

    Input::Input()
    {
        std::cout << "Input Created whit no window" << std::endl;
    }

    Input::~Input()
    {
        std::cout << "Input Destroyed" << std::endl;
    }
    void Input::setInputWindow(OkasoEngine_Window::Window* engineWindow){ this->engineWindow = engineWindow; }

    bool Input::isKeyPressed(KeyKode keycode) { return glfwGetKey(engineWindow->getWindow(),keycode) == PRESED; }
    bool Input::isKeyReleased(KeyKode keycode) { return glfwGetKey(engineWindow->getWindow(),keycode) == RELEASED; }
    bool Input::isKeyRepeated(KeyKode keycode)
    {
        if (keycode)
            return glfwGetKey(engineWindow->getWindow(),keycode) == REPEATED;
    }

    void Input::callBack(OkasoEngine_Window::Window* engineWindow, int key, int scancode, int action, int mods)
    {
    
    }
}

