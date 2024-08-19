#include "OkasoDebuger.h"

namespace OkasoEngine_Utilities
{
    bool OkasoDebuger::isActive = false;

    void OkasoDebuger::OkasoDebug(string msg, LogPriority priority)
    {
        if (!isActive)
            return;
        
            setConsoleColor(priority);
            cout << msg << endl;
        
    }

    void OkasoDebuger::OkasoDebugerSetActive(bool state) {isActive = state;}

    void OkasoDebuger::setConsoleColor(LogPriority priority)
    {
        // Obtener el handle de la consola
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // Establecer el color del texto
        SetConsoleTextAttribute(hConsole, priority);
    }
}
