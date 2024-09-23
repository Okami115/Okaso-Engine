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
        /// <summary>
        /// Debugs Information whit the given priority
        /// <para> "msg" is the message that you want to display
        /// <para> "priority" is the type of Debug that you want to do (Debug,Warning,Error,ETC)
        /// </summary>
        static void OKE_Debug(string msg,LogPriority priority = Debug_L);
        
        /// <summary>
        /// Change the state of the debuger
        /// <para> "state" true if you whant to show any logs, false if you dont
        /// </summary>
        static void OkasoDebugerSetActive(bool state);

        /// <summary>
        /// Change the state of the Debug Logs
        /// <para> This Type's of logs are use for common testing  purposes
        /// <para> "state" true if you  to show Debug logs or false if you dont
        /// </summary>
        static void SetActiveDebug_L(bool state);

        /// <summary>
        /// Change the state of the Warning Logs
        /// <para> This Type's of logs are use for Warnings About the engine function
        /// <para> "state" true if you  to show Warning logs or false if you dont
        /// </summary>
        static void SetActiveWarning_L(bool state);

        /// <summary>
        /// Change the state of the Info Logs
        /// <para> This Type's of logs are use for Engine or Implementation Info
        /// <para> "state" true if you  to show Info logs or false if you dont
        /// </summary>
        static void SetActiveInfo_L(bool state);

        /// <summary>
        /// Change the state of the Error Logs
        /// <para> This Type's of logs are use for common Engine Errors
        /// <para> "state" true if you  to show Error logs or false if you dont
        /// </summary>
        static void SetActiveError_L(bool state);

        /// <summary>
        /// Change the state of the Fatal Logs
        /// <para> This Type's of logs are use for Fatal Engine Errors
        /// <para> "state" true if you  to show Fatal logs or false if you dont
        /// </summary>
        static void SetActiveFatal_L(bool state);
        
    private:
        /// <summary>
        /// Change the color of the text in the console
        /// <para> LogPriority if for setting the color based on the type of log 
        /// </summary>
        static void setConsoleColor(LogPriority priority);
        static bool isActive;
        static bool showDebug_L;
        static bool showWarning_L;
        static bool showInfo_L;
        static bool showError_L;
        static bool showFatal_L;
    };
}

