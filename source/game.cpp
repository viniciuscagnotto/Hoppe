#include "include.h"

Game::Game()
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
	m_background.Create(ResourceManager::kResource_Background_Space, 1.5f);
	if (m_background.GetContainer())
		AddChild(m_background.GetContainer());

	m_backEarth.Create(ResourceManager::kResource_Background_Earth, 3.0f);
	if (m_backEarth.GetContainer())
		AddChild(m_backEarth.GetContainer());

	m_backSatellite.Create(ResourceManager::kResource_Background_Satellite, 5.0f);
	if (m_backSatellite.GetContainer())
		AddChild(m_backSatellite.GetContainer());

	//Loading Player
	m_player.Init();
	m_player.AddTo(this);
	//m_player.AddSpeed(1.0f);

	//Vortex List
	for (unsigned int i = 0; i < s_kMaxVortex; i++)
		m_vortexList[i] = 0;
	m_numVortex = 0;
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

	Scene::Cleanup();
}

void Game::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);
	m_background.Update();
	m_backEarth.Update();
	m_backSatellite.Update();

	m_player.Update();
	UpdateVortexList();
	
	if (CheckTouch())
		HandleTouch();
}

void Game::UpdateVortexList(){
	for (unsigned int i = 0; i < m_numVortex; i++){
		Vortex *pVortex = m_vortexList[i];
		if (pVortex){
			pVortex->Update();
			if (pVortex->CanDestroyMe()){
				pVortex->Cleanup();
				delete pVortex;
				m_vortexList[i] = 0;

				//test
				for (unsigned int j = i+1; j < m_numVortex; j++){
					m_vortexList[i] = m_vortexList[j];
				}

				m_numVortex--;
				continue;
			}

			if (pVortex->CheckHit(&m_player)){
				m_player.AddSpeed(0.04f);
			}

		}
	}
}



void Game::CleanupVortexList(){
	for (unsigned int i = 0; i < m_numVortex; i++){
		Vortex *pVortex = m_vortexList[i];
		if (pVortex){
			pVortex->Cleanup();
			delete pVortex;
			m_vortexList[i] = 0;

		}
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
	
	Vortex *newVortex = new Vortex();
	newVortex->Init((float)g_pInput->m_X, (float)g_pInput->m_Y);
	newVortex->AddTo(this);
	m_vortexList[m_numVortex++] = newVortex;
}