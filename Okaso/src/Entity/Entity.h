#pragma once
#include "../Renderer/Renderer.h"

class EXPORT Entity
{
public:
	Entity();
	void UpdateMatrix();
	~Entity();
	virtual void Draw();

	/// <summary>
	/// Set the Entity Position
	/// <para> x : Entity x Position
	/// <para> y : Entity y Position
	/// <para> z : Entity z Position
	/// </summary>
	void SetPosition(float x, float y, float z);

	/// <summary>
	/// Set the Entity Rotation
	/// <para> x : Entity x Rotation
	/// <para> y : Entity y Rotation
	/// <para> z : Entity z Rotation
	/// </summary>
	void SetRotation(float x, float y, float z);

	/// <summary>
	/// Set the Entity Scale
	/// <para> x : Entity x Scale
	/// <para> y : Entity y Scale
	/// <para> z : Entity z Scale
	/// </summary>
	void SetScale(float x, float y, float z);

	/// <summary>
	/// Set the Entity Color
	/// <para> r : Entity Red value
	/// <para> g : Entity Green value
	/// <para> b : Entity Blue value
	/// </summary>
	void SetColor(float r, float g, float b);
	
	void Rotate(float x = 0, float y = 0, float z = 0);
	void Translate(float x = 0, float y = 0, float z = 0);
	void Scale(float x = 0, float y = 0, float z = 0);
	void Colorate(float r = 0, float g = 0, float b = 0);

	/// <summary>
	/// Returns The Entity Position
	/// </summary>
	glm::vec3 GetPosition();

	/// <summary>
	/// Returns The Entity Rotation
	/// </summary>
	glm::vec3 GetRotation();

	/// <summary>
	/// Returns The Entity Scale
	/// </summary>
	glm::vec3 GetScale();

	/// <summary>
	/// Returns The Entity Color
	/// </summary>
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

