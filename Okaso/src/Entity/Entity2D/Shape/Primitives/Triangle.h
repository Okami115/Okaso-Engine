#pragma once
#include "../Shape.h"

class Triangle : public Shape
{
public:
	Triangle(float position[6]);
	~Triangle();
	void Draw() override;

private:
	float position[6];

};

