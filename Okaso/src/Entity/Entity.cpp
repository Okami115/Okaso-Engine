#include "Entity.h"
#include "../Utils/OkasoDebuger.h"
#include "../Renderer/Renderer.h"

Entity::Entity()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("Init Entity");

	renderer = OkasoEngine_Render::Renderer::GetRenderer();
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	OkasoEngine_Utilities::OkasoDebuger::OKE_Debug("Step 1 :: Entity");
}