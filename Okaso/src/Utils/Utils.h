#pragma once
#  define EXPORT __declspec(dllexport)

#include "OkasoDebuger.h"

namespace OkasoEngine_Utilities
{
#pragma region Default Values For Position,UV,Color && Vertex creation
	static const float DEFAULT_INDEX = 1.0f;
	static const float DEFAULT_UV = 0.0f;
	static const float DEFAULT_POS = 0.0f;
#pragma endregion
	
	struct EXPORT position
	{
		float x;
		float y;
		float z;

		position(float x = DEFAULT_POS, float y = DEFAULT_POS, float z = DEFAULT_POS)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	};

	struct EXPORT UV
	{
		float u;
		float v;

		UV(float u = DEFAULT_UV, float v = DEFAULT_UV)
		{
			this->u = u;
			this->v = v;
		}

	};

	struct EXPORT Color
	{
		float red;
		float green;
		float blue;
		float alpha;

		Color(float red = DEFAULT_INDEX, float green = DEFAULT_INDEX, float blue = DEFAULT_INDEX, float alpha = DEFAULT_INDEX)
		{
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}
	};

	struct EXPORT Vertex
	{
		position pos;
		UV uv;
		Color color;

		Vertex(position pos = position(), UV uv = UV(), Color color = Color())
		{
			this->pos = pos;
			this->uv = uv;
			this->color = color;
		}
	};
}
