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

    void Input::Update()
    {
        for (int key = 0; key < GLFW_KEY_LAST; ++key)
        {
            previousKeys[key] = currentKeys[key];
            currentKeys[key] = glfwGetKey(engineWindow->getWindow(), key) == GLFW_PRESS;
        }

        UpdateMouse();
    }

    
    void Input::setInputWindow(OkasoEngine_Window::Window* engineWindow){ this->engineWindow = engineWindow; }

    bool Input::isKeyPressed(int key)
    {
        return glfwGetKey(engineWindow->getWindow(), key) == GLFW_PRESS;
    }

    bool Input::isKeyDown(int key)
    {
        return currentKeys[key] && !previousKeys[key];
    }

    void Input::callBack(OkasoEngine_Window::Window* engineWindow, int key, int scancode, int action, int mods)
    {
    
    }
    void Input::UpdateMouse()
    {
        double xpos, ypos;
        glfwGetCursorPos(engineWindow->getWindow(), &xpos, &ypos);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        deltaX = static_cast<float>(xpos - lastX);
        deltaY = static_cast<float>(ypos - lastY);

        lastX = xpos;
        lastY = ypos;
    }
    
    float Input::GetMouseDeltaX() const { return deltaX; }
    float Input::GetMouseDeltaY() const { return deltaY; }
}

