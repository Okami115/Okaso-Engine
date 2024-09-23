#include "Rectangle.h"

namespace shape
{
	Rectangle::Rectangle()
	{
		OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Rectangle", OkasoEngine_Utilities::Info_L);
	
		float vertex[] =
		{
			-100.0f, -100.0f, 0.0f,
			100.0f, -100.0f, 0.0f,
			-100.0f,  100.0f, 0.0f,
			100.0f, 100.0f, 0.0f
		};
		unsigned int index[] =
		{
			0, 1, 3,
			0, 2, 3
		};
	
		VBO = new unsigned int;
		EBO = new unsigned int;
		VAO = new unsigned int;
	
		renderer->InitShape(vertex, 12, index, 6, VBO, EBO, VAO);
	}

	Rectangle::~Rectangle()
	{
		OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Rectangle", OkasoEngine_Utilities::Info_L);
	}
	
	void Rectangle::Draw()
	{
		//OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Triangle",OkasoEngine_Utilities::Info_L);
		renderer->DrawShape(VAO, model, 6, GetColor());
	}
}