#include "OkasoDebuger.h"

namespace OkasoEngine_Utilities
{
    bool OkasoDebuger::isActive = false;
    bool OkasoDebuger::showDebug_L = false;
    bool OkasoDebuger::showWarning_L = false;
    bool OkasoDebuger::showInfo_L = false;
    bool OkasoDebuger::showError_L = false;
    bool OkasoDebuger::showFatal_L = false;

    
    void OkasoDebuger::OKE_Debug(string msg, LogPriority priority)
    {
        if (!isActive)
            return;

        string msgType = "";

        switch (priority)
        {
        case Debug_L:
            if (!showDebug_L)
                return;
            msgType = "Debug_L :: ";
            break;
        case Warning_L:
            if (!showWarning_L)
                return;
            msgType = "Warning_L :: ";
            break;
        case Info_L:
            if (!showInfo_L)
                return;
            msgType = "Info_L :: ";
            break;
        case Error_L:
            if (!showError_L)
                return;
            msgType = "Error_L :: ";
            break;
        case Fatal_L:
            if (!showFatal_L)
                return;
            msgType = "Fatal_L :: ";
            break;
        }

        setConsoleColor(priority);
        cout << msgType << msg << endl;
        setConsoleColor(Debug_L);
    }

    
    void OkasoDebuger::OkasoDebugerSetActive(bool state)
    {
        isActive = state;
        showDebug_L = state;
        showWarning_L = state;
        showInfo_L = state;
        showError_L = state;
        showFatal_L = state;
    }

    
    void OkasoDebuger::SetActiveDebug_L(bool state) { showDebug_L = state; }
    
    void OkasoDebuger::SetActiveWarning_L(bool state) { showWarning_L = state; }
    
    void OkasoDebuger::SetActiveInfo_L(bool state) { showInfo_L = state; }
    
    void OkasoDebuger::SetActiveError_L(bool state) { showError_L = state; }
    
    void OkasoDebuger::SetActiveFatal_L(bool state) { showFatal_L = state; }

    void OkasoDebuger::setConsoleColor(LogPriority priority)
    {
        // Obtener el handle de la consola
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // Establecer el color del texto
        SetConsoleTextAttribute(hConsole, priority);
    }
}
