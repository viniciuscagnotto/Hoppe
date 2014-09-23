#include "header.h"

uint Gameplay::s_numLines = Gameplay::s_kDefaultLines;
bool Gameplay::s_paused = false;
int Gameplay::s_correctTaps = 0;
bool Gameplay::s_newSquare = false;
int Gameplay::s_actualScore = 0;
bool Gameplay::s_gameOver = false;

Gameplay::Gameplay() : Scene(kScene_Gameplay),
m_topAdsHeight(0.0f),
m_bottomHudHeight(0.0f),
m_pCirclesContainer(0),
m_pAlphaLayer(0),
m_pExitBtn(0),
m_pResumeBtn(0),
m_pPauseBtn(0),
m_pPauseScreen(0),
m_pBottomHUD(0),
m_pSound(0),
m_pOn(0),
m_pOff(0)
{
	for (uint i = 0; i < s_kMaxLines; i++)
		m_lines[i] = new SLine();

	m_pCirclesContainer = new CNode();
	s_numLines = s_kDefaultLines;
}

Gameplay::~Gameplay()
{
	Cleanup();

	for (uint i = 0; i < s_kMaxLines; i++){
		delete m_lines[i]->pRight; m_lines[i]->pRight = 0;
		delete m_lines[i]->pLeft; m_lines[i]->pLeft = 0;
		delete m_lines[i]; m_lines[i] = 0;
	}

	delete m_pCirclesContainer;
	m_pCirclesContainer = 0;
}

void Gameplay::Init(){
	Scene::Init();

	if (g_pAdsManager->IsEnabled())
		g_pAdsManager->NewAd();

	float extraSquareDim = EXTRA_SQUARE_DIM;
	if (Game::s_is2X)
		extraSquareDim *= 2.0f;

	int totalSpace = (Game::s_gameSpacement * s_numLines) + Game::s_gameSpacement;
	m_topAdsHeight = IwGxGetScreenHeight() * (TOP_ADS_HEIGHT / 100.0f);
	float squareHeight = m_lines[0]->pLeft->GetHeight() - extraSquareDim;
	m_bottomHudHeight = IwGxGetScreenHeight() - m_topAdsHeight - totalSpace;
	float m_bottomHudPosY = 0;

	AddChild(m_pCirclesContainer);

	m_numSquaresShooting = s_kMinSquaresShooting;
	uint numEqualLines = 0;
	for (uint i = 0; i < s_numLines; i++){
		float yPosition = m_topAdsHeight + (squareHeight * 0.5f) + (squareHeight * i) + Game::s_gameSpacement + (Game::s_gameSpacement * i);

		bool hidden = false;
		bool hasInitialType = false;
		GameObject::EGameObjectColor initialType = GameObject::kGameObjectColor_White;
		if (i >= m_numSquaresShooting){
			hidden = true;
			hasInitialType = true;
		}

		m_lines[i]->pLeft->SetInitialParams(hasInitialType, initialType);
		m_lines[i]->pLeft->SetPosition(m_lines[i]->pLeft->GetWidth(true), yPosition, hidden);
		m_lines[i]->pLeft->AddTo(this);
		m_lines[i]->pLeft->SetIsShooter(true);
		m_lines[i]->pLeft->SetupCircles(m_pCirclesContainer);

		m_lines[i]->pRight->SetInitialParams(true, m_lines[i]->pLeft->GetFront());
		m_lines[i]->pRight->SetPosition(IwGxGetScreenWidth() - m_lines[i]->pRight->GetWidth(true) + extraSquareDim, yPosition, hidden);
		m_lines[i]->pRight->AddTo(this);
		m_lines[i]->pRight->SetIsShooter(false);
		m_lines[i]->pRight->SetupCircles(m_pCirclesContainer);

		m_bottomHudHeight -= m_lines[i]->pLeft->GetHeight() - extraSquareDim;
		m_bottomHudPosY = yPosition + (squareHeight * 0.5f) + Game::s_gameSpacement + (m_bottomHudHeight * 0.5f);

	}

	ResetVariables();
	
	//Bottom HUD
	m_pBottomHUD = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_BlackSquare);
	m_pBottomHUD->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pBottomHUD->m_Y = m_bottomHudPosY;
	m_pBottomHUD->m_ScaleX = IwGxGetScreenWidth() / m_pBottomHUD->m_W;
	m_pBottomHUD->m_ScaleY = m_bottomHudHeight / m_pBottomHUD->m_H;
	AddChild(m_pBottomHUD);

	m_pPauseBtn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Pause);
	m_pPauseBtn->m_X = IwGxGetScreenWidth() - m_pPauseBtn->m_W * 0.5f - Game::s_gameSpacement;
	m_pPauseBtn->m_Y = m_pBottomHUD->m_Y;
	AddChild(m_pPauseBtn);

	//Pause Stuff
	m_pAlphaLayer = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Entity_BlackSquare);
	m_pAlphaLayer->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pAlphaLayer->m_Y = IwGxGetScreenHeight() * 0.5f;
	m_pAlphaLayer->m_ScaleX = IwGxGetScreenWidth() / m_pAlphaLayer->m_W;
	m_pAlphaLayer->m_ScaleY = IwGxGetScreenHeight() /m_pAlphaLayer->m_H;
	m_pAlphaLayer->m_Alpha = 0.65f;
	
	m_pPauseScreen = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Pause_Main);
	m_pPauseScreen->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pPauseScreen->m_Y = IwGxGetScreenHeight() * 0.5f;
	
	m_pResumeBtn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Resume);
	m_pResumeBtn->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pResumeBtn->m_Y = IwGxGetScreenHeight() * 0.5f + m_pResumeBtn->m_H * 0.5f;

	m_pExitBtn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Button_Exit);
	m_pExitBtn->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pExitBtn->m_Y = m_pResumeBtn->m_Y + m_pResumeBtn->m_H + Game::s_gameSpacement * 2;

	m_pSound = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Pause_Sound);
	m_pSound->m_X = IwGxGetScreenWidth() * 0.4f;
	m_pSound->m_Y = m_pResumeBtn->m_Y - m_pResumeBtn->m_H - Game::s_gameSpacement * 2;

	m_pOn = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Pause_On);
	m_pOn->m_X = IwGxGetScreenWidth() * 0.6f;
	m_pOn->m_Y = m_pResumeBtn->m_Y - m_pResumeBtn->m_H - Game::s_gameSpacement * 2;

	m_pOff = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Pause_Off);
	m_pOff->m_X = IwGxGetScreenWidth() * 0.6f;
	m_pOff->m_Y = m_pResumeBtn->m_Y - m_pResumeBtn->m_H - Game::s_gameSpacement * 2;

	m_circleSpeed = s_kCircleSpeed;
	m_timers.Add(new Timer(3.0f, 1, &Gameplay::Shoot, (void *)this));
}

void Gameplay::Cleanup(){
	m_timers.Clear();

	for (uint i = 0; i < s_kMaxLines; i++){
		m_lines[i]->isBusy = false;
		m_lines[i]->pLeft->RemoveFromParent();
		m_lines[i]->pRight->RemoveFromParent();
	}

	if (IsChild(m_pCirclesContainer))
		RemoveChild(m_pCirclesContainer);

	//Bottom HUD
	SafeDeleteObject(m_pBottomHUD);
	m_pBottomHUD = 0;
	SafeDeleteObject(m_pPauseBtn);
	m_pPauseBtn = 0;

	//Pause Stuff
	SafeDeleteObject(m_pExitBtn);
	m_pExitBtn = 0;
	SafeDeleteObject(m_pResumeBtn);
	m_pResumeBtn = 0;
	SafeDeleteObject(m_pPauseScreen);
	m_pPauseScreen = 0;
	SafeDeleteObject(m_pAlphaLayer);
	m_pAlphaLayer = 0;
	SafeDeleteObject(m_pSound);
	m_pSound = 0;
	SafeDeleteObject(m_pOn);
	m_pOn = 0;
	SafeDeleteObject(m_pOff);
	m_pOff = 0;

	Scene::Cleanup();
}

void Gameplay::Shoot(Timer* pTimer, void* pUserData){
	Gameplay *pGame = (Gameplay *)pUserData;
	pGame->RandomShoot();
}

void Gameplay::RandomShoot(){
	float shootSpeed = m_circleSpeed;
	if (Game::s_is2X)
		shootSpeed *= 2.0f;

	uint wrongShooter = L_RandomInt(0, m_numSquaresShooting - 1);
	for (uint i = 0; i < m_numSquaresShooting; i++){
		if (i == wrongShooter){
			m_lines[i]->Shoot(shootSpeed, false);
		}else{
			m_lines[i]->Shoot(shootSpeed);
		}
	}
}

void Gameplay::RandomSwitch(){
	if (!s_newSquare){
		for (uint i = 0; i < m_numSquaresShooting; i++){
			float chance = L_Random();
			if (chance >= 0.70f){
				m_lines[i]->SwitchBoth();
			}else if (chance <= 0.4f){
				m_lines[i]->ChangeShooter();
			}
		}
	}

	s_newSquare = false;
	m_timers.Add(new Timer(0.75f, 1, &Gameplay::Shoot, (void *)this));
}

void Gameplay::CheckNextLevel(){
	if (s_correctTaps == s_kTapsToLevel2 || s_correctTaps == s_kTapsToLevel3 || s_correctTaps == s_kTapsToLevel4){
		m_numSquaresShooting++;
		s_newSquare = true;
		m_lines[m_numSquaresShooting - 1]->SlideIn();
	}
}

void Gameplay::SetAllCirclesToFade(){
	for (uint i = 0; i < m_numSquaresShooting; i++)
		m_lines[i]->SetAllCirclesToFade();
}

void Gameplay::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);
	
	if (s_gameOver)
		return;

	if (s_paused && !IsChild(m_pPauseScreen))
		Pause(true);

	if (!s_paused){
		m_timers.Update(deltaTime);
		for (uint i = 0; i < s_numLines; i++)
			m_lines[i]->Update(deltaTime);
	}

	if (CheckTouch())
		HandleTouch();
}

void Gameplay::Render()
{
	Scene::Render();
	
}

void Gameplay::HandleTouch()
{
	Scene::HandleTouch();
	
	if (s_paused){
		if (m_pResumeBtn){
			if (m_pResumeBtn->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pAudio->PlaySound("audio/click.wav");
				Pause(false);
			}
		}

		if (m_pExitBtn){
			if (m_pExitBtn->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pAudio->PlaySound("audio/click.wav");
				ResetVariables();
				SwitchTo(Scene::kScene_MainMenu);
			}
		}

		if (g_pSaveData->m_saveData.mute){
			if (m_pOff){
				if (m_pOff->HitTest(g_pInput->m_x, g_pInput->m_y)){
					g_pSaveData->m_saveData.mute = false;
					g_pSaveData->Save();
					g_pAudio->SetMute(false);
					g_pAudio->PlaySound("audio/click.wav");

					m_pOff->m_IsVisible = false;
					m_pOn->m_IsVisible = true;
				}
			}
		}else{
			if (m_pOn){
				if (m_pOn->HitTest(g_pInput->m_x, g_pInput->m_y)){
					g_pSaveData->m_saveData.mute = true;
					g_pSaveData->Save();
					g_pAudio->SetMute(true);

					m_pOff->m_IsVisible = true;
					m_pOn->m_IsVisible = false;
				}
			}
		}

	}else{
		for (uint i = 0; i < s_numLines; i++)
			m_lines[i]->CheckTap(g_pInput->m_x, g_pInput->m_y);

		if (m_pPauseBtn){
			if (m_pPauseBtn->HitTest(g_pInput->m_x, g_pInput->m_y)){
				g_pAudio->PlaySound("audio/click.wav");
				Pause(true);
			}
		}
	}
}

void Gameplay::Pause(bool pause){
	s_paused = pause;
	if (s_paused){
		if (!IsChild(m_pAlphaLayer))
			AddChild(m_pAlphaLayer);

		if (!IsChild(m_pPauseScreen))
			AddChild(m_pPauseScreen);

		if (!IsChild(m_pResumeBtn))
			AddChild(m_pResumeBtn);

		if (!IsChild(m_pExitBtn))
			AddChild(m_pExitBtn);

		if (!IsChild(m_pSound))
			AddChild(m_pSound);

		if (!IsChild(m_pOn))
			AddChild(m_pOn);

		if (!IsChild(m_pOff))
			AddChild(m_pOff);

		if (g_pSaveData->m_saveData.mute){
			m_pOff->m_IsVisible = true;
			m_pOn->m_IsVisible = false;
		}else{
			m_pOff->m_IsVisible = false;
			m_pOn->m_IsVisible = true;
		}
	}else{
		if (IsChild(m_pAlphaLayer))
			RemoveChild(m_pAlphaLayer);

		if (IsChild(m_pPauseScreen))
			RemoveChild(m_pPauseScreen);

		if (IsChild(m_pResumeBtn))
			RemoveChild(m_pResumeBtn);

		if (IsChild(m_pExitBtn))
			RemoveChild(m_pExitBtn);

		if (IsChild(m_pSound))
			RemoveChild(m_pSound);

		if (IsChild(m_pOn))
			RemoveChild(m_pOn);

		if (IsChild(m_pOff))
			RemoveChild(m_pOff);
	}
}
