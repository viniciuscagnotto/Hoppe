#include "header.h"

MainMenu::MainMenu() : Scene(kScene_MainMenu),
m_pPlay(0),
m_pLogo(0),
m_pSettings(0)
{

}


MainMenu::~MainMenu()
{
	Cleanup();
}

void MainMenu::Init()
{
	Scene::Init();
	if (g_pAdsManager->IsEnabled())
		g_pAdsManager->NewAd();

	//Logo
	m_pLogo = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Logo_Main);
	m_pLogo->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pLogo->m_Y = IwGxGetScreenHeight() * 0.35f;
	AddChild(m_pLogo);

	//Start Game Button
	m_pPlay = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_StartGame);
	m_pPlay->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pPlay->m_Y = IwGxGetScreenHeight() * 0.65f;
	AddChild(m_pPlay);

	//Options Button
	m_pSettings = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Settings);
	m_pSettings->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pSettings->m_Y = m_pPlay->m_Y + m_pPlay->m_H;
	AddChild(m_pSettings);
}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pPlay);
	m_pPlay = 0;

	SafeDeleteObject(m_pLogo);
	m_pLogo = 0;

	SafeDeleteObject(m_pSettings);
	m_pSettings = 0;

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

	if (m_pPlay){
		if (m_pPlay->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/click.wav");
			SwitchTo(kScene_Tutorial);
		}
	}

	if (m_pSettings){
		if (m_pSettings->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/click.wav"); 
		//	SwitchTo(kScene_Options);

			if (g_pFacebookManager != 0)
			{
				char str[256];
				snprintf(str, 64, "I just scored 10 points");
				g_pFacebookManager->PostUpdate(str);
			}
		}
	}
}