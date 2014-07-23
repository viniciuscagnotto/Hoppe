#include "include.h"

Game::Game() :m_numVortex(0),
m_pObjectsContainer(0),
m_gameSpeed(s_kGameInitialSpeed)
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

	//Background (Parallax)
	m_background.Create(ResourceManager::kResource_Background_Space, 0.2f);
	if (m_background.GetContainer())
		AddChild(m_background.GetContainer());

	m_backEarth.Create(ResourceManager::kResource_Background_Earth, 0.5f);
	if (m_backEarth.GetContainer())
		AddChild(m_backEarth.GetContainer());

	m_backSatellite.Create(ResourceManager::kResource_Background_Satellite, 0.65f);
	if (m_backSatellite.GetContainer())
		AddChild(m_backSatellite.GetContainer());

	m_pObjectsContainer = new CNode();
	AddChild(m_pObjectsContainer);

	//Loading Player
	m_player.Init();
	m_player.AddTo(this);

	//vortex
	m_numVortex = 0;	

	//Game variables
	m_gameSpeed = s_kGameInitialSpeed;
}

void Game::Cleanup()
{
	m_player.Cleanup();
	CleanupVortexList();

	if(IsChild(m_background.GetContainer()))
		RemoveChild(m_background.GetContainer());
	m_background.Destroy();

	if (IsChild(m_backEarth.GetContainer()))
		RemoveChild(m_backEarth.GetContainer());
	m_backEarth.Destroy();

	if (IsChild(m_backSatellite.GetContainer()))
		RemoveChild(m_backSatellite.GetContainer());
	m_backSatellite.Destroy();

	RemoveChild(m_pObjectsContainer);
	delete(m_pObjectsContainer);
	m_pObjectsContainer = 0;

	Scene::Cleanup();
}

void Game::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	m_background.Update(m_gameSpeed);
	m_backEarth.Update(m_gameSpeed);
	m_backSatellite.Update(m_gameSpeed);

	m_player.Update();
	UpdateVortexList();
	
	if (CheckTouch())
		HandleTouch();
}


void Game::UpdateVortexList(){
	for (uint i = 0; i < m_numVortex; i++){
		Vortex *pVortex = &m_arrayVortex[i];
		if (pVortex){
			pVortex->Update(m_gameSpeed);
			if (pVortex->CanDestroyMe()){
				pVortex->Cleanup();
				m_arrayVortex.RemoveAt(i);
				m_numVortex--;
				continue;
			}

			if (pVortex->CheckHit(&m_player)){
				if (pVortex->GetDistanceX(&m_player) >= 0){
					m_player.SetSpeed(3.0f);
				}else{
					m_player.SetSpeed(-3.0f);
				}
			}
		}
	}
}



void Game::CleanupVortexList(){
	for (uint i = 0; i < m_numVortex; i++){
		m_arrayVortex[i].Cleanup();
		m_arrayVortex[i] = Vortex();
	}
	m_numVortex = 0;
}

void Game::Render()
{
	Scene::Render();
	
}

void Game::HandleTouch()
{
	Scene::HandleTouch();
	if (m_numVortex < s_kMaxVortex){
		m_arrayVortex[m_numVortex++] = Vortex();
		m_arrayVortex[m_numVortex - 1].Init((float)g_pInput->m_X, (float)g_pInput->m_Y);
		m_arrayVortex[m_numVortex - 1].AddTo(m_pObjectsContainer);
	}
}