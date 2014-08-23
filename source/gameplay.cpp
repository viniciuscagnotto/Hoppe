#include "header.h"

Gameplay::Gameplay() : Scene(kScene_Gameplay), 
m_pPlayer(0)
{
	
}

Gameplay::~Gameplay()
{
	Cleanup();
}

void Gameplay::Init()
{
	Scene::Init();

	//Background (Parallax)
	m_background.Create(Game::kGameGraphics_Background_Space, 0.2f);
	if (m_background.GetContainer())
		AddChild(m_background.GetContainer());

	//Loading Player
	m_pPlayer = new Player();
	m_pPlayer->AddTo(this);
}

void Gameplay::Cleanup()
{
	//Cleanup Player
	delete m_pPlayer;
	m_pPlayer = 0;

	//Cleanup Background
	if (IsChild(m_background.GetContainer()))
		RemoveChild(m_background.GetContainer());
	m_background.Destroy();

	Scene::Cleanup();
}

void Gameplay::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);
	
	m_background.Update(1.0f);
	m_pPlayer->Update();

	if (CheckTouch())
		HandleTouch();
}

void Gameplay::Render()
{
	Scene::Render();
	
}

void Gameplay::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}