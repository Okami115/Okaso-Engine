#include "OkasoDebuger.h"

namespace OkasoEngine_Utilities
{
    bool OkasoDebuger::isActive = false;

    /// <summary>
    /// Debugs Information whit the given priority
    /// <para> "msg" is the message that you want to display
    /// <para> "priority" is the type of Debug that you want to do (Debug,Warning,Error,ETC)
    /// </summary>
    void OkasoDebuger::OKE_Debug(string msg, LogPriority priority)
    {
        if (!isActive)
            return;
        
            setConsoleColor(priority);
            cout << msg << endl;
        
    }

    /// <summary>
    /// Change the state of the debuger
    /// <para> "state" true if you whant to show logs, false if you dont
    /// </summary>
    void OkasoDebuger::OkasoDebugerSetActive(bool state) {isActive = state;}

    void OkasoDebuger::setConsoleColor(LogPriority priority)
    {
        // Obtener el handle de la consola
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // Establecer el color del texto
        SetConsoleTextAttribute(hConsole, priority);
    }
}
