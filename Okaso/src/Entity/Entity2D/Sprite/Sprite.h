#pragma once
#include "../Entity2D.h"

class EXPORT Sprite : public Entity2D
{
public:
	/// <summary>
	/// Create a new Sprite
	/// </summary>
	Sprite(const char* spritePath);

	/// <summary>
	/// Destroy a new Sprite
	/// </summary>
	~Sprite();

	/// <summary>
	/// Draw a new Sprite
	/// </summary>
	void Draw() override;

	unsigned int* VBO;
	unsigned int* EBO;
	unsigned int* VAO;

	const char* path;
	unsigned int texture;
private:

};