#pragma once
#include "../Renderer/Renderer.h"

class EXPORT Entity
{
public:
	Entity();
	~Entity();
	virtual void Draw();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

private:

protected:
	OkasoEngine_Render::Renderer* renderer;
	glm::vec3 traslation;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 model;
};

