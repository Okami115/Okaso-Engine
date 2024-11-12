#include "Sprite.h"

Sprite::Sprite(const char* spritePath, int initialX, int initialY, int maxFrames, float maxAnimationTime, int spriteWidth, int spriteHeight, int frameWidth, int frameHeight)
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Sprite", OkasoEngine_Utilities::Info_L);

	path = spritePath;

	vertex = new float[20]
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 
	};

	index = new unsigned int[6]
	{
		0, 1, 3,
		0, 2, 3
	};

	VBO = new unsigned int;
	EBO = new unsigned int;
	VAO = new unsigned int;

	renderer->InitSprite(vertex, 20, index, 6, VBO, EBO, VAO, path, &texture);

	animation = Animation(initialX, initialY, maxFrames, maxAnimationTime, spriteWidth, spriteHeight, frameWidth, frameHeight);
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

void Sprite::UpdateAnimation()
{
	if (animation.hasFrames())
	{
		animation.update();
		int numberOfUVS = 4;
		int strife = 3;
		int row = 5;
		for (int i = 0; i < numberOfUVS; ++i)
		{
			ChangeUVCoord(strife + (i * row), animation.currentFrame->getUVCoord(i));
		}
		renderer->DeleteObjects(VAO, VBO, EBO);
		renderer->InitTextureBuffers(vertex, 20, index, 6, VBO, EBO, VAO, &texture);
	}
}

void Sprite::ChangeUVCoord(int strife, glm::vec2 UVS)
{
	vertex[strife] = UVS.x;
	vertex[strife + 1] = UVS.y;
}

void Sprite::ChangeAnimation(Animation animation)
{
	this->animation = animation;
}