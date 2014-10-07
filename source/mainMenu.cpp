#include "header.h"

MainMenu::MainMenu() : Scene(kScene_MainMenu),
m_pPlay(0),
m_pLogo(0),
m_pSettings(0),
m_pBestScore(0)
{

}


MainMenu::~MainMenu()
{
	Cleanup();
}

void MainMenu::Init()
{
	Scene::Init();
	
	//if (g_pAdsManager->IsEnabled())
	//	g_pAdsManager->NewAd();

	//Logo
	m_pLogo = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Logo_Main);
	m_pLogo->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pLogo->m_Y = IwGxGetScreenHeight() * 0.35f;
	AddChild(m_pLogo);

	//Start Game Button
	m_pPlay = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_StartGame);
	m_pPlay->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pPlay->m_Y = IwGxGetScreenHeight() * 0.67f;
	AddChild(m_pPlay);

	//Options Button
	m_pSettings = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Settings);
	m_pSettings->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pSettings->m_Y = m_pPlay->m_Y + m_pPlay->m_H;
	AddChild(m_pSettings);

	//Best Score
	float fontScale = 1.0f;
	if (Game::s_is2X)
		fontScale = 2.0f;
	
	if(g_pSaveData->m_saveData.topScore > 0){
		m_pBestScore = new CLabel();
		m_pBestScore->m_AnchorX = 0.0f;
		m_pBestScore->m_AnchorY = 0.5f;
		m_pBestScore->m_W = 200 * fontScale;
		m_pBestScore->m_H = 20 * fontScale;
		m_pBestScore->m_X = 8.0f * fontScale;
		m_pBestScore->m_Y = IwGxGetScreenHeight() - (20.0f * fontScale);
		m_pBestScore->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
		m_pBestScore->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
		m_pBestScore->m_Font = g_pResourceManager->GetFont((uint)Game::kGameFonts_BestScore);
		m_pBestScore->m_ScaleX = m_pBestScore->m_ScaleY = fontScale;
		m_pBestScore->m_Color = CColor(0x00, 0x00, 0x00, 0xff);

		char str[32];
		snprintf(str, 32, "BEST SCORE: %d", g_pSaveData->m_saveData.topScore);
		m_pBestScore->m_Text = str;
		AddChild(m_pBestScore);
	}

}

void MainMenu::Cleanup()
{
	SafeDeleteObject(m_pPlay);
	m_pPlay = 0;

	SafeDeleteObject(m_pLogo);
	m_pLogo = 0;

	SafeDeleteObject(m_pSettings);
	m_pSettings = 0;

	if (m_pBestScore){
		RemoveChild(m_pBestScore);
		delete m_pBestScore;
		m_pBestScore = 0;
	}

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
			SwitchTo(kScene_Gameplay);
		}
	}

	if (m_pSettings){
		if (m_pSettings->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/click.wav"); 
			SwitchTo(kScene_Options);
		}
	}
}