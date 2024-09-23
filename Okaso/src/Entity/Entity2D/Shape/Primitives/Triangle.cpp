#include "Triangle.h"

namespace shape
{
	Triangle::Triangle()
	{
		OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Triangle",OkasoEngine_Utilities::Info_L);
	
		float vertex[] = 
		{
			-100.0f, -100.0f, 0.0f, 
			100.0f, -100.0f, 0.0f,
			0.0f,  100.0f, 0.0f,
		};
		unsigned int index[] = 
		{
			0, 1, 2,
		};
	
		VBO = new unsigned int;
		EBO = new unsigned int;
		VAO = new unsigned int;
	
		renderer->InitShape(vertex, 9 ,index, 3,  VBO, EBO, VAO);
	}
	
	Triangle::~Triangle()
	{
		OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Triangle",OkasoEngine_Utilities::Info_L);
	}
	
	void Triangle::Draw()
	{
		//OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Triangle",OkasoEngine_Utilities::Info_L);
		renderer->DrawShape(VAO, model, 3, GetColor());
	}
}

