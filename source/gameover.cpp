#include "header.h"

GameOver::GameOver() : Scene(kScene_GameOver),
m_pMainMenu(0),
m_pPlayAgain(0),
m_pBestScoreTitle(0),
m_pYourScoreTitle(0)
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

	m_pPlayAgain = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_PlayAgain);
	m_pPlayAgain->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pPlayAgain->m_Y = IwGxGetScreenHeight() * 0.75f;
	AddChild(m_pPlayAgain);

	m_pMainMenu = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_MainMenu);
	m_pMainMenu->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pMainMenu->m_Y = m_pPlayAgain->m_Y + m_pPlayAgain->m_H;
	AddChild(m_pMainMenu);

	//Load Scores
	m_pBestScoreTitle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Title_BestScore);
	m_pBestScoreTitle->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pBestScoreTitle->m_Y = IwGxGetScreenWidth() * 0.25f;
	AddChild(m_pBestScoreTitle);



	m_pYourScoreTitle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Title_YourScore);
	m_pYourScoreTitle->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pYourScoreTitle->m_Y = m_pBestScoreTitle->m_Y + m_pBestScoreTitle->m_H * 2;
	AddChild(m_pYourScoreTitle);


	Gameplay::ResetVariables();
}

void GameOver::Cleanup()
{
	SafeDeleteObject(m_pMainMenu);
	m_pMainMenu = 0;
	SafeDeleteObject(m_pPlayAgain);
	m_pPlayAgain = 0;

	SafeDeleteObject(m_pBestScoreTitle);
	m_pBestScoreTitle = 0;
	SafeDeleteObject(m_pYourScoreTitle);
	m_pYourScoreTitle = 0;
	
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