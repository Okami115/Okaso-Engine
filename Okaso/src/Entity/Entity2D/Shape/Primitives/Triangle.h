#pragma once
#include "../Shape.h"

class Triangle : public Shape
{
public:
	Triangle(float* position, unsigned int* index, int vertexSize, int indexSize);
	~Triangle();
	void Draw() override;

private:
	float position[6];
	unsigned int index[3];
	int vertexSize;
	int indexSize;

};

