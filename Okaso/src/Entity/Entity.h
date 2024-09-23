#pragma once
#include "../Renderer/Renderer.h"

class EXPORT Entity
{
public:
	Entity();
	void UpdateMatrix();
	~Entity();
	virtual void Draw();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetColor(float x, float y, float z);
	void Rotate(float x = 0, float y = 0, float z = 0);
	void Translate(float x = 0, float y = 0, float z = 0);

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	glm::vec3 GetColor();

private:

protected:
	OkasoEngine_Render::Renderer* renderer;
	glm::vec3 traslation;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 color;
	glm::mat4 model;
};

