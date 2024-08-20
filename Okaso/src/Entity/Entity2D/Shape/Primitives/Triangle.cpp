#include "Triangle.h"

Triangle::Triangle(float position[6])
{
	renderer->InitTriangle(position);
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	renderer->DrawTriangle();
}