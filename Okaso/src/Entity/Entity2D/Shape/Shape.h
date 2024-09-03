#pragma once
#include "../Entity2D.h"

class Shape : public Entity2D
{
public:
	Shape();
	~Shape();
	void Draw() override;
	unsigned int* VBO;
	unsigned int* EBO;
	unsigned int* VAO;
private:

};