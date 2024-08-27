#include "OkasoDebuger.h"

namespace OkasoEngine_Utilities
{
    bool OkasoDebuger::isActive = false;
    bool OkasoDebuger::showDebug_L = false;
    bool OkasoDebuger::showWarning_L = false;
    bool OkasoDebuger::showInfo_L = false;
    bool OkasoDebuger::showError_L = false;
    bool OkasoDebuger::showFatal_L = false;

    /// <summary>
    /// Debugs Information whit the given priority
    /// <para> "msg" is the message that you want to display
    /// <para> "priority" is the type of Debug that you want to do (Debug,Warning,Error,ETC)
    /// </summary>
    void OkasoDebuger::OKE_Debug(string msg, LogPriority priority)
    {
        if (!isActive)
            return;

        switch (priority)
        {
        case Debug_L:
            if (!showDebug_L)
                return;
            break;
        case Warning_L:
            if (!showWarning_L)
                return;
            break;
        case Info_L:
            if (!showInfo_L)
                return;
            break;
        case Error_L:
            if (!showError_L)
                return;
            break;
        case Fatal_L:
            if (!showFatal_L)
                return;
            break;
        }

        setConsoleColor(priority);
        cout << msg << endl;
        setConsoleColor(Debug_L);
    }

    /// <summary>
    /// Change the state of the debuger
    /// <para> "state" true if you whant to show any logs, false if you dont
    /// </summary>
    void OkasoDebuger::OkasoDebugerSetActive(bool state)
    {
        isActive = state;
        showDebug_L = state;
        showWarning_L = state;
        showInfo_L = state;
        showError_L = state;
        showFatal_L = state;
    }

    /// <summary>
    /// Change the state of the Debug Logs
    /// <para> This Type's of logs are use for common testing  purposes
    /// <para> "state" true if you  to show Debug logs or false if you dont
    /// </summary>
    void OkasoDebuger::SetActiveDebug_L(bool state) { showDebug_L = state; }
    /// <summary>
    /// Change the state of the Warning Logs
    /// <para> This Type's of logs are use for Warnings About the engine function
    /// <para> "state" true if you  to show Warning logs or false if you dont
    /// </summary>
    void OkasoDebuger::SetActiveWarning_L(bool state) { showWarning_L = state; }
    /// <summary>
    /// Change the state of the Info Logs
    /// <para> This Type's of logs are use for Engine or Implementation Info
    /// <para> "state" true if you  to show Info logs or false if you dont
    /// </summary>
    void OkasoDebuger::SetActiveInfo_L(bool state) { showInfo_L = state; }
    /// <summary>
    /// Change the state of the Error Logs
    /// <para> This Type's of logs are use for common Engine Errors
    /// <para> "state" true if you  to show Error logs or false if you dont
    /// </summary>
    void OkasoDebuger::SetActiveError_L(bool state) { showError_L = state; }
    /// <summary>
    /// Change the state of the Fatal Logs
    /// <para> This Type's of logs are use for Fatal Engine Errors
    /// <para> "state" true if you  to show Fatal logs or false if you dont
    /// </summary>
    void OkasoDebuger::SetActiveFatal_L(bool state) { showFatal_L = state; }

    void OkasoDebuger::setConsoleColor(LogPriority priority)
    {
        // Obtener el handle de la consola
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // Establecer el color del texto
        SetConsoleTextAttribute(hConsole, priority);
    }
}
