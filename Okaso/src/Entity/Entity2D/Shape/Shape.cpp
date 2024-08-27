#include "Shape.h"

Shape::Shape()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: SHAPE",OkasoEngine_Utilities::Info_L);
}

Shape::~Shape()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: SHAPE",OkasoEngine_Utilities::Info_L);
}

void Shape::Draw()
{
    OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: SHAPE",OkasoEngine_Utilities::Info_L);
}