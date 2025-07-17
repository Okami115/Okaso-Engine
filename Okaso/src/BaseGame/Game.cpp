#include "Game.h"

Game::Game(int windowWidth, int windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	init();
}

Game::~Game()
{
	exit();
}

void Game::init()
{

	modelA = new Model("C:/Users/tomas/Escritorio/Okaso-Engine/Game/assets/Okami/Okami_V2.fbx", false);
	modelA->SetScale(0.01f, 0.01f, 0.01f);
	modelA->SetPosition(0, 0, 0);
	
	modelB = new Model("C:/Users/tomas/Escritorio/Okaso-Engine/Game/assets/Mesh/harpa.fbx", false);
	modelB->SetScale(0.1f, 0.1f, 0.1f);
	modelB->SetPosition(2.5f, 0, 0);
	
	cube = new Cube();
	cube->SetPosition(5.0f, 0, 0);

	modelC = new Model("C:/Users/tomas/Escritorio/Okaso-Engine/Game/assets/Mesh/torch.fbx", false);
	modelC->SetScale(0.1f, 0.1f, 0.1f);
	modelC->SetPosition(10, 0, 0);

	modelD = new Model("C:/Users/tomas/Escritorio/Okaso-Engine/Game/assets/Mesh/book.fbx", false);
	modelD->SetScale(0.1f, 0.1f, 0.1f);
	modelD->SetPosition(12.5f, 0, 0);
	modelD->SetRotation(0, 0, 0);
	
	camera->target = modelA->GetPosition();
	camera->distanceToTarget = 5.0f;
	
	renderer->dirLight.direction = glm::vec3(0.0f, -90.0f, 0.0f);
	renderer->dirLight.ambient = glm::vec3(0.2f, 0.3f, 0.2f);
	renderer->dirLight.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	renderer->dirLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	renderer->pointLight->constant = 1.0f;
	renderer->pointLight->linear = 0.09f;
	renderer->pointLight->quadratic = 0.132f;
	renderer->pointLight->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	renderer->pointLight->position = glm::vec3(12.0f, 1, 0);
	renderer->pointLight->diffuse = glm::vec3(1, 1, 1);
	renderer->pointLight->specular = glm::vec3(1, 1, 1);

	renderer->spotLight.constant = 1.0f;
	renderer->spotLight.linear = 0.09f;
	renderer->spotLight.quadratic = 0.032f;
	renderer->spotLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->spotLight.diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->spotLight.specular = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->spotLight.position = glm::vec3(13.0f, 0, 0);
	renderer->spotLight.diffuse = glm::vec3(1, 1, 1);
	renderer->spotLight.specular = glm::vec3(1, 1, 1);
	renderer->spotLight.direction = glm::vec3(1, 1, 1);
}

void Game::update()
{
	cube->Draw();
	modelA->Draw();
	modelB->Draw();
	modelC->Draw();
	modelD->Draw();

	if (goToLeft)
	{
		lightPosX += 0.1f;
		if (lightPosX > 13)
		goToLeft = false;
	}
	else
	{
		lightPosX -= 0.1f;
		if (lightPosX < 0)
			goToLeft = true;
	}
	
	renderer->pointLight->position = glm::vec3(lightPosX, 1, 0);
}

void Game::exit()
{
	delete cube;
	delete modelA;
	delete modelB;
	delete modelC;
	delete modelD;
}
