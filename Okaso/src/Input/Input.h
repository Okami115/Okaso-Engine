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
        void setInputWindow(OkasoEngine_Window::Window* engineWindow);
    
        bool isKeyPressed(KeyKode keycode);
        bool isKeyRepeated(KeyKode keycode);
        void callBack(OkasoEngine_Window::Window* engineWindow, int key, int scancode, int action, int mods);
        bool isKeyReleased(KeyKode keycode);
    
    private:
        OkasoEngine_Window::Window* engineWindow;
    };
}

