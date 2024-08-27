#include "Entity.h"
#include "../Utils/OkasoDebuger.h"
#include "../Renderer/Renderer.h"

Entity::Entity()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("INIT :: Entity",OkasoEngine_Utilities::Info_L);

	renderer = OkasoEngine_Render::Renderer::GetRenderer();
}

Entity::~Entity()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DELETE :: Entity",OkasoEngine_Utilities::Info_L);
}

void Entity::Draw()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("DRAW :: Entity");
}