#pragma once
#include "../Entity2D.h"
#include "../../../Animation/Animation.h"

class EXPORT Sprite : public Entity2D
{
public:
	/// <summary>
	/// Create a new Sprite
	/// </summary>

	Sprite(const char* spritePath, int initialX = 0, int initialY = 0, int maxFrames = 1, float maxAnimationTime = 0, 
		int spriteWidth = 0, int spriteHeight = 0, int frameWidth= 0, int frameHeight = 0);

	/// <summary>
	/// Destroy a new Sprite
	/// </summary>
	~Sprite();

	/// <summary>
	/// Draw a new Sprite
	/// </summary>
	void Draw() override;

	void UpdateAnimation();
	void ChangeAnimation();
	void ChangeAnimation(Animation animation);
	void ChangeUVCoord(int strife, glm::vec2 UVS);

private:
	unsigned int* VBO;
	unsigned int* EBO;
	unsigned int* VAO;

	const char* path;
	unsigned int texture;
	Animation animation;

	int width;
	int height;

	float* vertex;
	unsigned int* index;

};