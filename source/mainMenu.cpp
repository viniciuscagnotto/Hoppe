#include "header.h"

MainMenu::MainMenu() : Scene(kScene_MainMenu),
m_pStartGame(0)
{

}


MainMenu::~MainMenu()
{
	Cleanup();
}

void MainMenu::Init()
{
	Scene::Init();

	//Start Game Button
	m_pStartGame = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_StartGame);
	m_pStartGame->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pStartGame->m_Y = IwGxGetScreenHeight() * 0.5f;
	AddChild(m_pStartGame);

}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pStartGame);
	m_pStartGame = 0;

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

	if (m_pStartGame){
		if (m_pStartGame->HitTest(g_pInput->m_x, g_pInput->m_y)){
			//g_pAudio->PlaySound("audio/button.wav");
			SwitchTo(kScene_Gameplay);
		}
	}
}