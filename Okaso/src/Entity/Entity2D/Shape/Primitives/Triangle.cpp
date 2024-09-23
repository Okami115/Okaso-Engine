#include "Triangle.h"

Triangle::Triangle(float* position, unsigned int* index, int vertexSize, int indexSize)
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Triangle",OkasoEngine_Utilities::Info_L);

	VBO = new unsigned int;
	EBO = new unsigned int;
	VAO = new unsigned int;

	renderer->InitShape(position, vertexSize ,index, indexSize,  VBO, EBO, VAO);
}

Triangle::~Triangle()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Triangle",OkasoEngine_Utilities::Info_L);
}

void Triangle::Draw()
{
	//OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Triangle",OkasoEngine_Utilities::Info_L);
	renderer->DrawShape(VAO, model);
}
