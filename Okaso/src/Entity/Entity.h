#pragma once
#include "../Renderer/Renderer.h"

class Entity
{
public:
	Entity();
	~Entity();
	virtual void Draw();

private:

protected:
	OkasoEngine_Render::Renderer* renderer;
};

