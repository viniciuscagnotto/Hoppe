#include "template.h"

MainMenu::MainMenu():
m_pStartGame(0),
m_pOptions(0),
m_pStore(0)
{
	m_type = kScene_MainMenu;

}


MainMenu::~MainMenu()
{
	Cleanup();
}

void MainMenu::Init()
{
	Scene::Init();

	//Loading Buttons
	m_pStartGame = g_pSpriteManager->CreateSpriteObject(ResourceManager::kResource_Button_StartGame);
	m_pStartGame->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStartGame->m_Y = IwGxGetScreenHeight() * 0.5f - 120.0f;
	AddChild(m_pStartGame);

	m_pStore = g_pSpriteManager->CreateSpriteObject(ResourceManager::kResource_Button_StartGame);
	m_pStore->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStore->m_Y = IwGxGetScreenHeight() * 0.5f + 120.0f;
	AddChild(m_pStore);

	m_pOptions = g_pSpriteManager->CreateSpriteObject(ResourceManager::kResource_Button_StartGame);
	m_pOptions->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pOptions->m_Y = IwGxGetScreenHeight() * 0.5f;
	AddChild(m_pOptions);
}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pOptions);
	m_pOptions = 0;
	
	SafeDeleteObject(m_pStartGame);
	m_pStartGame = 0;

	SafeDeleteObject(m_pStore);
	m_pStore = 0;

	Scene::Cleanup();
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

    Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();
	
}

void MainMenu::Render()
{
    Scene::Render();
	if (!CheckCurrent())
		return;
}

void MainMenu::HandleTouch()
{
	Scene::HandleTouch();

	if (m_pStartGame)
		if (m_pStartGame->HitTest(g_pInput->m_X, g_pInput->m_Y))
			SwitchTo(kScene_Gameplay);

	if (m_pStore)
		if (m_pStore->HitTest(g_pInput->m_X, g_pInput->m_Y))
			SwitchTo(kScene_Store);

	if (m_pOptions)
		if (m_pOptions->HitTest(g_pInput->m_X, g_pInput->m_Y))
			SwitchTo(kScene_Options);

}