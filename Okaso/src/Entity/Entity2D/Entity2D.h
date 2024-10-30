#pragma once
#include "../Entity.h"
#include "../../Utils/OkasoDebuger.h"

class EXPORT Entity2D : public Entity
{
public:
	/// <summary>
	/// Create a new Entity2D
	/// </summary>
	Entity2D();
	
	/// <summary>
	/// Destroy a new Entity2D
	/// </summary>
	~Entity2D();

	/// <summary>
	/// Draw a new Entity2D
	/// </summary>
	void Draw() override;
private:

};

