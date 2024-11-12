#include "Entity.h"
#include "../Utils/OkasoDebuger.h"
#include "../Renderer/Renderer.h"

Entity::Entity()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Entity", OkasoEngine_Utilities::Info_L);

	renderer = OkasoEngine_Render::Renderer::GetRenderer();

	traslation = glm::vec3(renderer->SCR_WIDTH /2, renderer->SCR_HEIGHT / 2, 0);
	previousTraslation = traslation;
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	color = glm::vec3(1, 1, 1);

	UpdateMatrix();
}

void Entity::UpdateMatrix()
{
	glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));


	model = (glm::translate(glm::mat4(1.0f), traslation)) * (rotationY * rotationX * rotationZ) * glm::scale(glm::mat4(1.0f), scale);
}

Entity::~Entity()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Entity",OkasoEngine_Utilities::Info_L);
}

void Entity::Draw()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Entity");
}

void Entity::SetPosition(float x, float y, float z)
{
	previousTraslation = traslation;
	traslation = glm::vec3(x, y, z);
	UpdateMatrix();
}

void Entity::SetPreviousPosition()
{
	traslation = previousTraslation;
	UpdateMatrix();
}

void Entity::ForceUpdatePreviousPos(float x, float y, float z)
{
	previousTraslation = glm::vec3(x, y, z);
}

void Entity::ForcePreviousPosAsCurrentPos()
{
	previousTraslation = traslation;
}

void Entity::SetRotation(float x, float y, float z)
{
	rotation = glm::vec3(x, y, z);

	UpdateMatrix();
}

void Entity::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);

	UpdateMatrix();
}

void Entity::SetColor(float r, float g, float z)
{
	color = glm::vec3(r, g, z);

	UpdateMatrix();
}

void Entity::Rotate(float x, float y, float z)
{
	SetRotation(rotation.x + x,rotation.y + y,rotation.z + z);
}

void Entity::Translate(float x, float y, float z)
{
	SetPosition(traslation.x + x,traslation.y + y,traslation.z + z);
}

void Entity::Scale(float x, float y, float z)
{
	SetScale(scale.x + x,scale.y + y,scale.z + z);
}

void Entity::Colorate(float r, float g, float b)
{
	SetColor(color.x + r,color.y + g,color.z + b);
}

glm::vec3 Entity::GetPosition()
{
	return traslation;
}

glm::vec3 Entity::GetPreviousPosition()
{
	return previousTraslation;
}

glm::vec3 Entity::GetRotation()
{
	return rotation;
}

glm::vec3 Entity::GetScale()
{
	return scale;
}

glm::vec3 Entity::GetColor()
{
	return color;
}
