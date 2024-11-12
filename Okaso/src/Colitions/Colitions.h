#pragma once
#include "../Entity/Entity2D/Entity2D.h"
#include "../Utils/OkasoDebuger.h"
#include <cmath>

class EXPORT Colitions
{
public:
    Colitions();
    ~Colitions();
    /// <summary>
    /// CheckCollitions between two Entities
    /// </summary>
    static bool CheckCollitions(Entity2D a,Entity2D b);
    /// <summary>
    /// CheckCollitions between two Entities
    /// </summary>
    static bool CheckCollitions(Entity2D *a,Entity2D *b);
};
