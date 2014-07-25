#include "include.h"

Game::Game() :m_numVortex(0),
m_numGameObjects(0),
m_pObjectsContainer(0),
m_gameSpeed((float)s_kInitialSpeed),
m_paused(true),
m_distance(0)
//m_pPlayer(0)
{
	m_type = kScene_Game;
	for (uint i = 0; i < s_kMaxGameObjects; i++)
		m_gameObjects[i] = 0;
}

Game::~Game()
{
	Cleanup();
}

void Game::Init()
{
	m_paused = true;
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

	//triggers
	m_triggers.Reset();

	//game objects
	for (uint i = 0; i < s_kMaxGameObjects; i++)
		m_gameObjects[i] = 0;
	m_numGameObjects = 0;
	m_numVortex = 0;

	//Loading Player
	Player *pPlayer = new Player();
	pPlayer->AddTo(this);
	m_gameObjects[m_numGameObjects++] = pPlayer;

	//Game variables
	m_gameSpeed = (float)s_kInitialSpeed;
	m_gameSpeedIncrease = 0.0025f;
	m_paused = false;
	m_distance = 0;


	//Load Distance Label - TODO: Change way to load labels
	float fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;
	float actualFontHeight = FONT_HEIGHT * fontScale;
	
	m_distanceText = new CLabel();
	m_distanceText->m_X = 50 * fontScale;
	m_distanceText->m_Y = 10 * fontScale;
	m_distanceText->m_W = FONT_DESIGN_WIDTH;
	m_distanceText->m_H = actualFontHeight;
	m_distanceText->m_Text = "0m";
	m_distanceText->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	m_distanceText->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	m_distanceText->m_Font = g_pResourceManager->GetFont(ResourceManager::kFont_Arial_8);
	m_distanceText->m_ScaleX = fontScale;
	m_distanceText->m_ScaleY = fontScale;
	m_distanceText->m_Color = CColor(0xff, 0xff, 0x30, 0xff);
	AddChild(m_distanceText);
}

void Game::Cleanup()
{
	//Player
	//m_pPlayer->Cleanup();
	//delete m_pPlayer;
	//m_pPlayer = 0;

	//Game Objects
	CleanupGameObjects();

	//Parallax
	if (IsChild(m_background.GetContainer()))
		RemoveChild(m_background.GetContainer());
	m_background.Destroy();

	if (IsChild(m_backEarth.GetContainer()))
		RemoveChild(m_backEarth.GetContainer());
	m_backEarth.Destroy();

	if (IsChild(m_backSatellite.GetContainer()))
		RemoveChild(m_backSatellite.GetContainer());
	m_backSatellite.Destroy();

	//Container
	if (m_pObjectsContainer){
		RemoveChild(m_pObjectsContainer);
		delete(m_pObjectsContainer);
		m_pObjectsContainer = 0;
	}

	//Distance Text
	if (m_distanceText){
		RemoveChild(m_distanceText);
		delete m_distanceText;
		m_distanceText = 0;
	}

	Scene::Cleanup();
}

void Game::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	if (m_paused)
		return;

	Scene::Update(deltaTime, alphaMul);

	m_background.Update(m_gameSpeed);
	m_backEarth.Update(m_gameSpeed);
	m_backSatellite.Update(m_gameSpeed);

	//m_pPlayer->Update();
	UpdateGameObjects();
	
	if (m_distanceText){
		char str[32];
		snprintf(str, 32, "D: %d - S: %d", (int)floorf(m_distance / METER), (int)floorf(m_gameSpeed));
		m_distanceText->m_Text = str;
	}


	if (CheckTouch())
		HandleTouch();

	//Update Speed
	m_distance += m_gameSpeed;
	m_gameSpeed += m_gameSpeedIncrease;
	if (m_gameSpeed > (float)s_kMaxSpeed)
		m_gameSpeed = (float)s_kMaxSpeed;
}


void Game::UpdateGameObjects(){
	//Remove Objects
	for (uint i = 0; i < m_numGameObjects; i++){
		GameObject *pGameObject = m_gameObjects[i];
		if (!pGameObject)
			continue;

		pGameObject->Update(m_gameSpeed);
		if (pGameObject->CanDestroyMe()){
			if (pGameObject->GetType() == GameObject::kGameObjectType_Vortex)
				m_numVortex--;

			pGameObject->Cleanup();
			delete pGameObject;
			pGameObject = 0;
			m_gameObjects.RemoveAt(i);
			m_numGameObjects--;
			i--;
			continue;
		}

		for (uint j = i; j < m_numGameObjects; j++){
			pGameObject->Interact(m_gameObjects[j]);
		}
	}
}


void Game::CleanupGameObjects(){
	for (uint i = 0; i < m_numGameObjects; i++){
		GameObject *pGameObject = m_gameObjects[i];
		if (!pGameObject)
			continue;

		pGameObject->Cleanup();
		delete pGameObject;
		pGameObject = 0;
		m_gameObjects[i] = 0;

	}
	m_numVortex = 0;
	m_numGameObjects = 0;
}

void Game::Render()
{
	Scene::Render();
	
}

void Game::HandleTouch()
{
	Scene::HandleTouch();
	if (m_numVortex < s_kMaxVortex){
		Vortex *newVortex = new Vortex();
		newVortex->Init((float)g_pInput->m_X, (float)g_pInput->m_Y);
		newVortex->AddTo(m_pObjectsContainer);
		m_gameObjects[m_numGameObjects++] = newVortex;
		m_numVortex++;
	}
}