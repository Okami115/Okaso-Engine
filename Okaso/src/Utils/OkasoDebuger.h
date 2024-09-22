#pragma once
#include <iostream>
#include <Windows.h>
#include "Utils.h"
using namespace std;

namespace OkasoEngine_Utilities
{
    enum LogPriority {Debug_L = 7,Warning_L = 6,Info_L = 3,Error_L = 4,Fatal_L = 5};
    class OkasoDebuger
    {
    public:
        static void OKE_Debug(string msg,LogPriority priority = Debug_L);
        static void OkasoDebugerSetActive(bool state);
        static void SetActiveDebug_L(bool state);
        static void SetActiveWarning_L(bool state);
        static void SetActiveInfo_L(bool state);
        static void SetActiveError_L(bool state);
        static void SetActiveFatal_L(bool state);
        
    private:
        static void setConsoleColor(LogPriority priority);
        static bool isActive;
        static bool showDebug_L;
        static bool showWarning_L;
        static bool showInfo_L;
        static bool showError_L;
        static bool showFatal_L;
    };
}

