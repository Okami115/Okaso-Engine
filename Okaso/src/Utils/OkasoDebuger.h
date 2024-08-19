#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

namespace OkasoEngine_Utilities
{
    enum LogPriority {Debug_L = 7,Warning_L = 6,Info_L = 3,Error_L = 4,Fatal_L = 5};
    class OkasoDebuger
    {
    public:
        static void OkasoDebug(string msg,LogPriority priority);
        static void OkasoDebugerSetActive(bool state);
        static OkasoDebuger* _debuger;
        
    private:
        static void setConsoleColor(LogPriority priority);
        static bool isActive;
    };
}

