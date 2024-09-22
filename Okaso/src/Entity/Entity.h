#pragma once
#include "../Renderer/Renderer.h"

class EXPORT Entity
{
public:
	Entity();
	~Entity();
	virtual void Draw();

private:

protected:
	OkasoEngine_Render::Renderer* renderer;
};

