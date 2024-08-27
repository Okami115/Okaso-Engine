#include "Triangle.h"

Triangle::Triangle(float position[6])
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Triangle",OkasoEngine_Utilities::Info_L);
	renderer->InitTriangle(position);
}

Triangle::~Triangle()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Triangle",OkasoEngine_Utilities::Info_L);
}

void Triangle::Draw()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Triangle",OkasoEngine_Utilities::Info_L);
	renderer->DrawTriangle();
}