#include "Entity2D.h"

Entity2D::Entity2D()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Entity 2D",OkasoEngine_Utilities::Info_L);
}

Entity2D::~Entity2D()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Entity 2D",OkasoEngine_Utilities::Info_L);
}

void Entity2D::Draw()
{
	Entity::Draw();
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Entity 2D");
}