#pragma once
#include "KeyCode.h"
#include "../Utils/Utils.h"
#include "../Window/Window.h"

namespace OkasoEngine_Input
{
    class EXPORT Input final
    {
    public:
        Input(OkasoEngine_Window::Window* engineWindow);
        Input();
        ~Input();
        void Update();
        void setInputWindow(OkasoEngine_Window::Window* engineWindow);

        bool isKeyPressed(int key);
        bool isKeyDown(int key);
        void callBack(OkasoEngine_Window::Window* engineWindow, int key, int scancode, int action, int mods);

        void UpdateMouse();
        float GetMouseDeltaX() const;
        float GetMouseDeltaY() const;
    
    private:
        OkasoEngine_Window::Window* engineWindow;

        double lastX = 0.0;
        double lastY = 0.0;
        float deltaX = 0.0f;
        float deltaY = 0.0f;
        bool firstMouse = true;

        
        bool currentKeys[GLFW_KEY_LAST] = { false };
        bool previousKeys[GLFW_KEY_LAST] = { false };
    };
}

