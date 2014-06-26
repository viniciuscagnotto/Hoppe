#include "include.h"

MainMenu::MainMenu():
m_pStartGame(0),
m_pOptions(0),
m_pStuff(0)
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
	m_pStartGame = g_pSpriteManager->CreateSpriteObject("textures/start_game.png");
	m_pStartGame->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStartGame->m_Y = IwGxGetScreenHeight() * 0.5f - 120.0f;
	AddChild(m_pStartGame);

	m_pOptions = g_pSpriteManager->CreateSpriteObject("textures/start_game.png");
	m_pOptions->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pOptions->m_Y = IwGxGetScreenHeight() * 0.5f;
	AddChild(m_pOptions);

	m_pStuff = g_pSpriteManager->CreateSpriteObject("textures/start_game.png");
	m_pStuff->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStuff->m_Y = IwGxGetScreenHeight() * 0.5f + 120.0f;
	AddChild(m_pStuff);
}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pStartGame);
	m_pStartGame = 0;

	SafeDeleteObject(m_pOptions);
	m_pOptions = 0;

	SafeDeleteObject(m_pStuff);
	m_pStuff = 0;

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
			SwitchTo(kScene_Game);

	if (m_pOptions)
		if (m_pOptions->HitTest(g_pInput->m_X, g_pInput->m_Y))
			SwitchTo(kScene_Options);

	if (m_pStuff)
		if (m_pStuff->HitTest(g_pInput->m_X, g_pInput->m_Y))
			SwitchTo(kScene_Stuff);
}