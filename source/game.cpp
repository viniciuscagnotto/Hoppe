#include "include.h"

Game::Game()
{
	m_type = kScene_Game;

}

Game::~Game()
{
   
}

void Game::Init()
{
	Scene::Init();

}

void Game::Cleanup()
{


	Scene::Cleanup();
}

void Game::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;

	Scene::Update(deltaTime, alphaMul);

}

void Game::Render()
{
    Scene::Render();

}
