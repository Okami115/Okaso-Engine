#include "Entity.h"
#include "../Utils/OkasoDebuger.h"
#include "../Renderer/Renderer.h"

Entity::Entity()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Entity", OkasoEngine_Utilities::Info_L);

	renderer = OkasoEngine_Render::Renderer::GetRenderer();

	traslation = glm::vec3(400, 400, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(100, 100, 100);

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
	traslation = glm::vec3(x, y, z);

	glm::translate(model, traslation);
}

void Entity::SetRotation(float x, float y, float z)
{
	rotation = glm::vec3(x, y, z);

	glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);

	glm::scale(model, scale);
}

glm::vec3 Entity::GetPosition()
{
	return traslation;
}

glm::vec3 Entity::GetRotation()
{
	return rotation;
}

glm::vec3 Entity::GetScale()
{
	return scale;
}
