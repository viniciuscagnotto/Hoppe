#include "header.h"

MainMenu::MainMenu() : Scene(kScene_MainMenu),
m_pStartGame(0),
m_pFazendeiroRun1(0),
m_pFazendeiroRun2(0),
m_pFazendeiroRun3(0),
m_pFazendeiroRun4(0),
m_pFazendeiroRun5(0)
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

	//Fazendeiro Run - ANIMATION TEST
	m_pFazendeiroRun1 = g_pSpriteManager->CreateAnimatedSprite(Game::kGameAtlases_FazendeiroRun, 0.2f, 10);
	m_pFazendeiroRun1->m_X = IwGxGetScreenWidth() * 0.2f;
	m_pFazendeiroRun1->m_Y = IwGxGetScreenHeight() * 0.2f;
	AddChild(m_pFazendeiroRun1);

	m_pFazendeiroRun2 = g_pSpriteManager->CreateAnimatedSprite(Game::kGameAtlases_FazendeiroRun, 0.4f, 10);
	m_pFazendeiroRun2->m_X = IwGxGetScreenWidth() * 0.35f;
	m_pFazendeiroRun2->m_Y = IwGxGetScreenHeight() * 0.2f;
	AddChild(m_pFazendeiroRun2);

	m_pFazendeiroRun3 = g_pSpriteManager->CreateAnimatedSprite(Game::kGameAtlases_FazendeiroRun, 0.6f, 10);
	m_pFazendeiroRun3->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pFazendeiroRun3->m_Y = IwGxGetScreenHeight() * 0.2f;
	AddChild(m_pFazendeiroRun3);

	m_pFazendeiroRun4 = g_pSpriteManager->CreateAnimatedSprite(Game::kGameAtlases_FazendeiroRun, 0.8f, 10);
	m_pFazendeiroRun4->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pFazendeiroRun4->m_Y = IwGxGetScreenHeight() * 0.2f;
	AddChild(m_pFazendeiroRun4);

	m_pFazendeiroRun5 = g_pSpriteManager->CreateAnimatedSprite(Game::kGameAtlases_FazendeiroRun, 1.0f, 10);
	m_pFazendeiroRun5->m_X = IwGxGetScreenWidth() * 0.8f;
	m_pFazendeiroRun5->m_Y = IwGxGetScreenHeight() * 0.2f;
	AddChild(m_pFazendeiroRun5);

}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pStartGame);
	m_pStartGame = 0;

	SafeDeleteObject(m_pFazendeiroRun1);
	m_pFazendeiroRun1 = 0;
	SafeDeleteObject(m_pFazendeiroRun2);
	m_pFazendeiroRun2 = 0;
	SafeDeleteObject(m_pFazendeiroRun3);
	m_pFazendeiroRun3 = 0;
	SafeDeleteObject(m_pFazendeiroRun4);
	m_pFazendeiroRun4 = 0;
	SafeDeleteObject(m_pFazendeiroRun5);
	m_pFazendeiroRun5 = 0;

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
			g_pAudio->PlaySound("audio/button.wav");
			SwitchTo(kScene_Gameplay);
		}
	}
}