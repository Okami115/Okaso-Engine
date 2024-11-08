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
	/// Set the Entity Position to the Previous Position
	/// </summary>
	void SetPreviousPosition();

	/// <summary>
	/// Force the update of the Previous Pos whit a new value
	/// <para> x : Entity x PreviousPos
	/// <para> y : Entity y PreviousPos
	/// <para> z : Entity z PreviousPos
	/// </summary>
	void ForceUpdatePreviousPos(float x, float y, float z);

	/// <summary>
	/// Force the update of the Previous Pos to be the current Entity pos
	/// </summary>
	void ForcePreviousPosAsCurrentPos();

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

	/// <summary>
	/// Adds a Value to the Entity Rotation
	/// <para> x : Adds x to the x rotation value
	/// <para> y : Adds y to the y rotation value
	/// <para> z : Adds z to the z rotation value
	/// </summary>
	void Rotate(float x = 0, float y = 0, float z = 0);

	/// <summary>
	/// Adds a Value to the Entity Position
	/// <para> x : Adds x to the x Position value
	/// <para> y : Adds y to the y Position value
	/// <para> z : Adds z to the z Position value
	/// </summary>
	void Translate(float x = 0, float y = 0, float z = 0);

	/// <summary>
	/// Adds a Value to the Entity Scale
	/// <para> x : Adds x to the x Scale value
	/// <para> y : Adds y to the y Scale value
	/// <para> z : Adds z to the z Scale value
	/// </summary>
	void Scale(float x = 0, float y = 0, float z = 0);

	/// <summary>
	/// Adds a Value to the Entity Color
	/// <para> r : Adds r to the Red Color value
	/// <para> g : Adds g to the Green Color value
	/// <para> b : Adds b to the Blue Color value
	/// </summary>
	void Colorate(float r = 0, float g = 0, float b = 0);

	/// <summary>
	/// Returns The Entity Position
	/// </summary>
	glm::vec3 GetPosition();

	/// <summary>
	/// Returns The Entity previous Position
	/// </summary>
	glm::vec3 GetPreviousPosition();

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
	glm::vec3 previousTraslation;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 color;
	glm::mat4 model;
};

