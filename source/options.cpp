#include "header.h"

Options::Options() : Scene(kScene_Options),
m_pBack(0),
m_pTitle(0),
m_pSound(0),
m_pSoundOn(0),
m_pSoundOff(0),
m_pSoundBlackCircle(0),
m_pSoundWhiteCircle(0),
m_pTutorial(0),
m_pTutorialOn(0),
m_pTutorialOff(0),
m_pTutorialBlackCircle(0),
m_pTutorialWhiteCircle(0)
{

}


Options::~Options()
{
	Cleanup();
}

void Options::Init()
{
	Scene::Init();

	//if (g_pAdsManager->IsEnabled())
	//	g_pAdsManager->NewAd();

	//Back Button
	m_pBack = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Back);
	m_pBack->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pBack->m_Y = (IwGxGetScreenHeight() * 0.67f) + m_pBack->m_H;
	AddChild(m_pBack);

	//Title
	m_pTitle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Title_Options);
	m_pTitle->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pTitle->m_Y = IwGxGetScreenHeight() * 0.25f;
	AddChild(m_pTitle);
	
	float spacement = 70.0f;
	if (Game::s_is2X)
		spacement *= 2.0f;

	//Sound Here
	m_pSound = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_Sound);
	m_pSound->m_X = IwGxGetScreenWidth() * 0.25f;
	m_pSound->m_Y = m_pTitle->m_Y + spacement +  (m_pSound->m_H * 0.5f);
	AddChild(m_pSound);

	m_pSoundBlackCircle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_BlackCircle);
	m_pSoundBlackCircle->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pSoundBlackCircle->m_Y = m_pSound->m_Y;
	AddChild(m_pSoundBlackCircle);

	m_pSoundWhiteCircle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_WhiteCircle);
	m_pSoundWhiteCircle->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pSoundWhiteCircle->m_Y = m_pSound->m_Y;
	AddChild(m_pSoundWhiteCircle);

	m_pSoundOn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_On);
	m_pSoundOn->m_X = m_pSoundBlackCircle->m_X + m_pSoundBlackCircle->m_W * 0.5f + m_pSoundOn->m_W * 0.5f + Game::s_gameSpacement * 2;
	m_pSoundOn->m_Y = m_pSound->m_Y;
	AddChild(m_pSoundOn);

	m_pSoundOff = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_Off);
	m_pSoundOff->m_X = m_pSoundWhiteCircle->m_X + m_pSoundWhiteCircle->m_W * 0.5f + m_pSoundOff->m_W * 0.5f + Game::s_gameSpacement * 2;
	m_pSoundOff->m_Y = m_pSound->m_Y;
	AddChild(m_pSoundOff);

	if (g_pSaveData->m_saveData.mute){
		m_pSoundBlackCircle->m_IsVisible = false;
		m_pSoundOn->m_IsVisible = false;
	}else{
		m_pSoundWhiteCircle->m_IsVisible = false;
		m_pSoundOff->m_IsVisible = false;
	}

	//Tutorial
	m_pTutorial = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_Tutorial);
	m_pTutorial->m_X = IwGxGetScreenWidth() * 0.25f;
	m_pTutorial->m_Y = m_pSound->m_Y + (m_pTutorial->m_H * 1.45f);
	AddChild(m_pTutorial);

	m_pTutorialBlackCircle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_BlackCircle);
	m_pTutorialBlackCircle->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pTutorialBlackCircle->m_Y = m_pTutorial->m_Y;
	AddChild(m_pTutorialBlackCircle);

	m_pTutorialWhiteCircle = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_WhiteCircle);
	m_pTutorialWhiteCircle->m_X = IwGxGetScreenWidth() * 0.65f;
	m_pTutorialWhiteCircle->m_Y = m_pTutorial->m_Y;
	AddChild(m_pTutorialWhiteCircle);

	m_pTutorialOn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_On);
	m_pTutorialOn->m_X = m_pTutorialBlackCircle->m_X + m_pTutorialBlackCircle->m_W * 0.5f + m_pTutorialOn->m_W * 0.5f + Game::s_gameSpacement * 2;
	m_pTutorialOn->m_Y = m_pTutorial->m_Y;
	AddChild(m_pTutorialOn);

	m_pTutorialOff = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Options_Off);
	m_pTutorialOff->m_X = m_pTutorialWhiteCircle->m_X + m_pTutorialWhiteCircle->m_W * 0.5f + m_pTutorialOff->m_W * 0.5f + Game::s_gameSpacement * 2;
	m_pTutorialOff->m_Y = m_pTutorial->m_Y;
	AddChild(m_pTutorialOff);

	if (!g_pSaveData->m_saveData.tutorial){
		m_pTutorialBlackCircle->m_IsVisible = false;
		m_pTutorialOn->m_IsVisible = false;
	}else{
		m_pTutorialWhiteCircle->m_IsVisible = false;
		m_pTutorialOff->m_IsVisible = false;
	}
}

void Options::Cleanup()
{
	SafeDeleteObject(m_pBack);
	m_pBack = 0;
	SafeDeleteObject(m_pTitle);
	m_pTitle = 0;

	//Sound
	SafeDeleteObject(m_pSound);
	m_pSound = 0;
	SafeDeleteObject(m_pSoundOn);
	m_pSoundOn = 0;
	SafeDeleteObject(m_pSoundOff);
	m_pSoundOff = 0;

	SafeDeleteObject(m_pSoundWhiteCircle);
	m_pSoundWhiteCircle = 0;
	SafeDeleteObject(m_pSoundBlackCircle);
	m_pSoundBlackCircle = 0;

	//Tutorial
	SafeDeleteObject(m_pTutorial);
	m_pTutorial = 0;
	SafeDeleteObject(m_pTutorialOn);
	m_pTutorialOn = 0;
	SafeDeleteObject(m_pTutorialOff);
	m_pTutorialOff = 0;

	SafeDeleteObject(m_pTutorialWhiteCircle);
	m_pTutorialWhiteCircle = 0;
	SafeDeleteObject(m_pTutorialBlackCircle);
	m_pTutorialBlackCircle = 0;

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
		if (m_pSoundOff && m_pSoundWhiteCircle){
			if (m_pSoundOff->HitTest(g_pInput->m_x, g_pInput->m_y) || m_pSoundWhiteCircle->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pSaveData->m_saveData.mute = false;
				g_pSaveData->Save();
				g_pAudio->SetMute(false);
				g_pAudio->PlaySound("audio/click.wav");

				m_pSoundWhiteCircle->m_IsVisible = false;
				m_pSoundOff->m_IsVisible = false;
				m_pSoundBlackCircle->m_IsVisible = true;
				m_pSoundOn->m_IsVisible = true;
			}
		}
	}else{
		if (m_pSoundOn && m_pSoundBlackCircle){
			if (m_pSoundOn->HitTest(g_pInput->m_x, g_pInput->m_y) || m_pSoundBlackCircle->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pSaveData->m_saveData.mute = true;
				g_pSaveData->Save();
				g_pAudio->SetMute(true);
				
				m_pSoundWhiteCircle->m_IsVisible = true;
				m_pSoundOff->m_IsVisible = true;
				m_pSoundBlackCircle->m_IsVisible = false;
				m_pSoundOn->m_IsVisible = false;
			}
		}
	}

	if (!g_pSaveData->m_saveData.tutorial){
		if (m_pTutorialOff && m_pTutorialWhiteCircle){
			if (m_pTutorialOff->HitTest(g_pInput->m_x, g_pInput->m_y) || m_pTutorialWhiteCircle->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pSaveData->m_saveData.tutorial = true;
				g_pSaveData->Save();
				g_pAudio->PlaySound("audio/click.wav");

				m_pTutorialWhiteCircle->m_IsVisible = false;
				m_pTutorialOff->m_IsVisible = false;
				m_pTutorialBlackCircle->m_IsVisible = true;
				m_pTutorialOn->m_IsVisible = true;
			}
		}
	}else{
		if (m_pTutorialOn && m_pTutorialBlackCircle){
			if (m_pTutorialOn->HitTest(g_pInput->m_x, g_pInput->m_y) || m_pTutorialBlackCircle->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pSaveData->m_saveData.tutorial = false;
				g_pSaveData->Save();
				g_pAudio->PlaySound("audio/click.wav");

				m_pTutorialWhiteCircle->m_IsVisible = true;
				m_pTutorialOff->m_IsVisible = true;
				m_pTutorialBlackCircle->m_IsVisible = false;
				m_pTutorialOn->m_IsVisible = false;
			}
		}
	}

}