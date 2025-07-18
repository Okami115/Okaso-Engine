#pragma once
#  define EXPORT __declspec(dllexport)

#include "OkasoDebuger.h"
#include "../glm/glm.hpp"
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

	class EXPORT Vertex
	{
	public:
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		int m_BoneIDs[4];
		float m_Weights[4];
		
		Vertex(glm::vec3 pos = glm::vec3(), glm::vec3 normal = glm::vec3(), glm::vec2 TexCoords = glm::vec3(), glm::vec3 Tangent = glm::vec3(), glm::vec3 bitangent = glm::vec3())
		{
			this->Position = pos;
			this->Normal = normal;
			this->TexCoords = TexCoords;
			this->Tangent = Tangent;
			this->Bitangent = bitangent;
		}
	};

	class EXPORT Texture
	{
	public:
		unsigned int* id;
		const char* type;
		const char* path;

		Texture(const char* type, const char* path)
		{
			id = new unsigned int();
			this->type = type;
			this->path = path;
		}
	};
}
