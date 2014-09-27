#include "header.h"

GameOver::GameOver() : Scene(kScene_GameOver),
m_pMainMenu(0),
m_pPlayAgain(0),
m_pBestScoreTitle(0),
m_pYourScoreTitle(0),
m_pBestScore(0),
m_pYourScore(0),
m_pFacebook(0),
m_actualScore(0)
{

}


GameOver::~GameOver()
{
	Cleanup();
}

void GameOver::Init()
{
	Scene::Init();

	if (g_pAdsManager->IsEnabled())
		g_pAdsManager->NewAd();

	//Buttons
	m_pFacebook = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Facebook);
	m_pFacebook->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pFacebook->m_Y = IwGxGetScreenHeight() * 0.60f;
	AddChild(m_pFacebook);

	//Buttons
	m_pPlayAgain = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_PlayAgain);
	m_pPlayAgain->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pPlayAgain->m_Y = m_pFacebook->m_Y + m_pFacebook->m_H * 3.0f;
	AddChild(m_pPlayAgain);

	m_pMainMenu = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_MainMenu);
	m_pMainMenu->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pMainMenu->m_Y = m_pPlayAgain->m_Y + m_pPlayAgain->m_H;
	AddChild(m_pMainMenu);

	//Load Scores
	m_pBestScoreTitle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Title_BestScore);
	m_pBestScoreTitle->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pBestScoreTitle->m_Y = IwGxGetScreenWidth() * 0.30f;
	AddChild(m_pBestScoreTitle);


	float fontScale = 1.0f;
	if (Game::s_is2X)
		fontScale = 2.0f;

	m_pBestScore = new CLabel();
	m_pBestScore->m_AnchorX = m_pBestScore->m_AnchorY = 0.5f;
	m_pBestScore->m_W = 300 * fontScale;
	m_pBestScore->m_H = 30 * fontScale;
	m_pBestScore->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pBestScore->m_Y = m_pBestScoreTitle->m_Y + m_pBestScoreTitle->m_H * 0.88f;
	m_pBestScore->m_AlignHor = m_pBestScore->m_AlignVer= IW_2D_FONT_ALIGN_CENTRE;
	m_pBestScore->m_Font = g_pResourceManager->GetFont((uint)Game::kGameFonts_BestScore);
	m_pBestScore->m_ScaleX = m_pBestScore->m_ScaleY = fontScale + (0.3f * fontScale);
	m_pBestScore->m_Color = CColor(0x00, 0x00, 0x00, 0xff);

	char str[32];
	snprintf(str, 32, "%d", g_pSaveData->m_saveData.topScore);
	m_pBestScore->m_Text = str;
	AddChild(m_pBestScore);


	m_pYourScoreTitle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Title_YourScore);
	m_pYourScoreTitle->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pYourScoreTitle->m_Y = m_pBestScoreTitle->m_Y + m_pBestScoreTitle->m_H * 2;
	AddChild(m_pYourScoreTitle);


	m_pYourScore = new CLabel();
	m_pYourScore->m_AnchorX = m_pYourScore->m_AnchorY = 0.5f;
	m_pYourScore->m_W = 300 * fontScale;
	m_pYourScore->m_H = 20 * fontScale;;
	m_pYourScore->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pYourScore->m_Y = m_pYourScoreTitle->m_Y + m_pYourScoreTitle->m_H * 0.85f;
	m_pYourScore->m_AlignHor = m_pYourScore->m_AlignVer = IW_2D_FONT_ALIGN_CENTRE;
	m_pYourScore->m_Font = g_pResourceManager->GetFont((uint)Game::kGameFonts_BestScore);
	m_pYourScore->m_ScaleX = m_pYourScore->m_ScaleY = fontScale + (0.3f * fontScale);
	m_pYourScore->m_Color = CColor(0x00, 0x00, 0x00, 0xff);

	char str2[32];
	snprintf(str2, 32, "%d", Gameplay::s_actualScore);
	m_pYourScore->m_Text = str2;
	AddChild(m_pYourScore);
	m_actualScore = Gameplay::s_actualScore;


	Gameplay::ResetVariables();
}

void GameOver::Cleanup()
{
	SafeDeleteObject(m_pFacebook);
	m_pFacebook = 0;
	SafeDeleteObject(m_pMainMenu);
	m_pMainMenu = 0;
	SafeDeleteObject(m_pPlayAgain);
	m_pPlayAgain = 0;

	SafeDeleteObject(m_pBestScoreTitle);
	m_pBestScoreTitle = 0;
	SafeDeleteObject(m_pYourScoreTitle);
	m_pYourScoreTitle = 0;
	
	if (m_pBestScore){
		RemoveChild(m_pBestScore);
		delete m_pBestScore;
		m_pBestScore = 0;
	}

	if (m_pYourScore){
		RemoveChild(m_pYourScore);
		delete m_pYourScore;
		m_pYourScore = 0;
	}

	Scene::Cleanup();
}

void GameOver::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void GameOver::Render()
{
	Scene::Render();

}

void GameOver::HandleTouch()
{
	Scene::HandleTouch();

	if (m_pFacebook){
		if (m_pFacebook->HitTest(g_pInput->m_x, g_pInput->m_y)){
			//Share Score

		}
	}

	if (m_pMainMenu){
		if (m_pMainMenu->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/click.wav");
			SwitchTo(kScene_MainMenu);
		}
	}

	if (m_pPlayAgain){
		if (m_pPlayAgain->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/click.wav");
			SwitchTo(kScene_Gameplay);
		}
	}
}