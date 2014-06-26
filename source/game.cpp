#include "include.h"

Game::Game():
m_pStar(0)
{
	m_type = kScene_Game;

}

Game::~Game()
{
	Cleanup();
}

void Game::Init()
{
	Scene::Init();

	//Loading Star
	m_pStar = g_pSpriteManager->CreateSpriteObject("textures/star.png");
	m_pStar->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStar->m_Y = IwGxGetScreenHeight() * 0.5f;
	AddChild(m_pStar);
}

void Game::Cleanup()
{
	SafeDeleteObject(m_pStar);
	m_pStar = 0;

	Scene::Cleanup();
}

void Game::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (m_pStar)
		m_pStar->m_Angle += 7;

	if (CheckTouch())
		HandleTouch();
}

void Game::Render()
{
	Scene::Render();
	if (!CheckCurrent())
		return;
}

void Game::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}