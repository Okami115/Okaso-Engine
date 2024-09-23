#pragma once
#include "../Entity2D.h"

class EXPORT Shape : public Entity2D
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