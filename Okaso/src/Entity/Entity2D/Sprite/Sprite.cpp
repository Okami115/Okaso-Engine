#include "Sprite.h"

Sprite::Sprite(const char* spritePath)
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Sprite", OkasoEngine_Utilities::Info_L);

	path = spritePath;

	float vertex[] =
	{
		-256.0f, -256.0f, 0.0f, 0.0f, 0.0f,
		256.0f, -256.0f, 0.0f, 1.0f, 0.0f,
		-256.0f,  256.0f, 0.0f, 0.0f, 1.0f,
		256.0f, 256.0f, 0.0f, 1.0f, 1.0f
	};
	unsigned int index[] =
	{
		0, 1, 3,
		0, 2, 3
	};

	VBO = new unsigned int;
	EBO = new unsigned int;
	VAO = new unsigned int;

	renderer->InitSprite(vertex, 20, index, 6, VBO, EBO, VAO, path, &texture);
}

Sprite::~Sprite()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Sprite", OkasoEngine_Utilities::Info_L);
}

void Sprite::Draw()
{
	//OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Triangle",OkasoEngine_Utilities::Info_L);
	renderer->DrawSprite(VAO, model, 6, GetColor(), &texture);
}