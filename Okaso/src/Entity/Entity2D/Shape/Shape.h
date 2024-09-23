#pragma once
#include "../Entity2D.h"

class EXPORT Shape : public Entity2D
{
public:
	/// <summary>
	/// Create a new Shape
	/// </summary>
	Shape();

	/// <summary>
	/// Destroy a new Shape
	/// </summary>
	~Shape();

	/// <summary>
	/// Draw a new Shape
	/// </summary>
	void Draw() override;
	
	unsigned int* VBO;
	unsigned int* EBO;
	unsigned int* VAO;
private:

};