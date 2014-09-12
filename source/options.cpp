#include "header.h"

Options::Options() : Scene(kScene_Options),
m_pBack(0),
m_pTitle(0),
m_pSound(0),
m_pOn(0),
m_pOff(0),
m_pBlackCircle(0),
m_pWhiteCircle(0)
{

}


Options::~Options()
{
	Cleanup();
}

void Options::Init()
{
	Scene::Init();

	if (g_pAdsManager->IsEnabled())
		g_pAdsManager->NewAd();

	//Title
	m_pTitle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Title_Options);
	m_pTitle->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pTitle->m_Y = IwGxGetScreenHeight() * 0.25f;
	AddChild(m_pTitle);
	
	//Back Button
	m_pBack = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Back);
	m_pBack->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pBack->m_Y = IwGxGetScreenHeight() * 0.75f;
	AddChild(m_pBack);

	//Sound Here
	m_pSound = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_Sound);
	m_pSound->m_X = IwGxGetScreenWidth() * 0.25f;
	m_pSound->m_Y = IwGxGetScreenHeight() * 0.5f - m_pSound->m_H * 0.5f;
	AddChild(m_pSound);

	m_pBlackCircle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_BlackCircle);
	m_pBlackCircle->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pBlackCircle->m_Y = m_pSound->m_Y;
	AddChild(m_pBlackCircle);

	m_pWhiteCircle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_WhiteCircle);
	m_pWhiteCircle->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pWhiteCircle->m_Y = m_pSound->m_Y;
	AddChild(m_pWhiteCircle);

	m_pOn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_On);
	m_pOn->m_X = m_pBlackCircle->m_X + m_pBlackCircle->m_W * 0.5f + m_pOn->m_W * 0.5f + Game::s_gameSpacement * 2;
	m_pOn->m_Y = m_pSound->m_Y;
	AddChild(m_pOn);

	m_pOff = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_Off);
	m_pOff->m_X = m_pWhiteCircle->m_X + m_pWhiteCircle->m_W * 0.5f + m_pOff->m_W * 0.5f + Game::s_gameSpacement * 2;
	m_pOff->m_Y = m_pSound->m_Y;
	AddChild(m_pOff);

	if (g_pSaveData->m_saveData.mute){
		m_pBlackCircle->m_IsVisible = false;
		m_pOn->m_IsVisible = false;
	}else{
		m_pWhiteCircle->m_IsVisible = false;
		m_pOff->m_IsVisible = false;
	}
}

void Options::Cleanup()
{
	SafeDeleteObject(m_pBack);
	m_pBack = 0;
	SafeDeleteObject(m_pTitle);
	m_pTitle = 0;

	SafeDeleteObject(m_pSound);
	m_pSound = 0;
	SafeDeleteObject(m_pOn);
	m_pOn = 0;
	SafeDeleteObject(m_pOff);
	m_pOff = 0;

	SafeDeleteObject(m_pWhiteCircle);
	m_pWhiteCircle = 0;
	SafeDeleteObject(m_pBlackCircle);
	m_pBlackCircle = 0;

	Scene::Cleanup();
}

void Options::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void Options::Render()
{
	Scene::Render();
	
}

void Options::HandleTouch()
{
	Scene::HandleTouch();
	if (m_pBack){
		if (m_pBack->HitTest(g_pInput->m_x, g_pInput->m_y)){
			g_pAudio->PlaySound("audio/click.wav");
			SwitchTo(kScene_MainMenu);
		}
	}

	if (g_pSaveData->m_saveData.mute){
		if (m_pOff && m_pWhiteCircle){
			if (m_pOff->HitTest(g_pInput->m_x, g_pInput->m_y) || m_pWhiteCircle->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pSaveData->m_saveData.mute = false;
				g_pSaveData->Save();
				g_pAudio->SetMute(false);
				g_pAudio->PlaySound("audio/click.wav");

				m_pWhiteCircle->m_IsVisible = false;
				m_pOff->m_IsVisible = false;
				m_pBlackCircle->m_IsVisible = true;
				m_pOn->m_IsVisible = true;
			}
		}
	}else{
		if (m_pOn && m_pBlackCircle){
			if (m_pOn->HitTest(g_pInput->m_x, g_pInput->m_y) || m_pBlackCircle->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pSaveData->m_saveData.mute = true;
				g_pSaveData->Save();
				g_pAudio->SetMute(true);
				
				m_pWhiteCircle->m_IsVisible = true;
				m_pOff->m_IsVisible = true;
				m_pBlackCircle->m_IsVisible = false;
				m_pOn->m_IsVisible = false;
			}
		}
	}


}