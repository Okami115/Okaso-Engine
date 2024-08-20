#include "Entity2D.h"

Entity2D::Entity2D()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("Init Entity 2D");
}

Entity2D::~Entity2D()
{
}

void Entity2D::Draw()
{
	Entity::Draw();
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("Step 2 :: Entity 2D");
}