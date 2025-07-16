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
	cube = new Cube();
	cube->SetPosition(10.0f, 0, 0);
	camera->distanceToTarget = 10.0f;

	model = new Model("C:/Users/tomas/Escritorio/Okaso-Engine/Game/assets/Survival_BackPack_2/backpack.obj");
	model->Scale(1.0f, 1.0f, 1.0f);
	model->SetColor(1, 1, 1);
	model->SetPosition(0, 0, 0);
	
	camera->target = model->GetPosition();
	
	renderer->dirLight.direction = glm::vec3(0.0f, -90.0f, 0.0f);
	renderer->dirLight.ambient = glm::vec3(0.2f, 0.3f, 0.2f);
	renderer->dirLight.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	renderer->dirLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	renderer->pointLight->constant = 1.0f;
	renderer->pointLight->linear = 0.09f;
	renderer->pointLight->quadratic = 0.032f;
	renderer->pointLight->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->pointLight->position = glm::vec3(0, 10, 0);
	renderer->pointLight->diffuse = glm::vec3(1, 1, 1);
	renderer->pointLight->specular = glm::vec3(1, 1, 1);

	renderer->spotLight.constant = 1.0f;
	renderer->spotLight.linear = 0.09f;
	renderer->spotLight.quadratic = 0.032f;
	renderer->spotLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->spotLight.diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->spotLight.specular = glm::vec3(0.2f, 0.2f, 0.2f);
	renderer->spotLight.position = glm::vec3(10, 10, 10);
	renderer->spotLight.diffuse = glm::vec3(1, 1, 1);
	renderer->spotLight.specular = glm::vec3(1, 1, 1);
	renderer->spotLight.direction = glm::vec3(0, 0, 0);
}

void Game::update()
{
	cube->Draw();
	model->Draw();
}

void Game::exit()
{
	delete cube;
	delete model;
}
