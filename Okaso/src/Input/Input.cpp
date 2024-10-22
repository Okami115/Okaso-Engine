#include "Input.h"

namespace OkasoEngine_Input
{
    Input::Input(OkasoEngine_Window::Window* engineWindow)
    {
        this->engineWindow = engineWindow;
        OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Input", OkasoEngine_Utilities::Info_L);
    }

    Input::Input()
    {
        OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Input without window", OkasoEngine_Utilities::Info_L);
    }

    Input::~Input()
    {
        OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("Destroy :: Input", OkasoEngine_Utilities::Info_L);
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

