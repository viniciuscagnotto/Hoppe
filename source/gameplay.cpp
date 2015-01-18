#include "header.h"

Gameplay *Gameplay::s_pSelf = 0;

bool Gameplay::s_paused = false;
bool Gameplay::s_isShowingTutorial = false;
bool Gameplay::s_canTap = true;
int Gameplay::s_paintsEachSide = 0;
int Gameplay::s_colorsLimit = 0;


Gameplay::Gameplay() : Scene(kScene_Gameplay),
m_numActiveLines(0)
{
	s_pSelf = this;
}

Gameplay::~Gameplay(){
	Cleanup();
	s_pSelf = 0;
}

void Gameplay::Init(){
	Scene::Init();

	if (g_pAdsManager->IsEnabled())
		g_pAdsManager->NewAd();

	float adsSize = (Iw2DGetSurfaceHeight() * (TOP_ADS_HEIGHT / 100.0f));
	float hudSize = (Iw2DGetSurfaceHeight() * (BOTTOM_HUD_HEIGHT / 100.0f));
	float gameplaySize = (Iw2DGetSurfaceHeight() - adsSize - hudSize);
	float lineSize = gameplaySize / s_kMaxLines;

	m_numActiveLines = s_kStartingLines;
	for (uint i = 0; i < s_kMaxLines; i++){
		m_lines[i] = Line();
		m_lines[i].SetPosY(adsSize + lineSize * 0.5f + lineSize * i);	
	}


	float waitTime = 2.0f;
	s_canTap = true;
	s_isShowingTutorial = false;
	if (g_pSaveData->m_saveData.tutorial){
		s_canTap = false;
		waitTime = 1.0f;
	}

	s_colorsLimit = s_kStartColorsLimit;
	s_paintsEachSide = 1;

	m_timers.Add(new Timer(waitTime, 1, &Gameplay::ShowLine, (void *)this));
}

void Gameplay::Cleanup(){
	m_timers.Clear();

	for (uint i = 0; i < s_kMaxLines; i++)
		m_lines[i].Clean();

	Scene::Cleanup();
}



void Gameplay::Update(float deltaTime, float alphaMul){
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	//if (s_paused && !IsChild(m_pPauseScreen))
	//	Pause(true);

	if (!s_paused && !s_isShowingTutorial){
		m_timers.Update(deltaTime);
		for (uint i = 0; i < s_kMaxLines; i++)
			m_lines[i].Update(deltaTime);

		//if (m_pYourScore){
		//	char str[32];
		//	snprintf(str, 32, "SCORE: %d", s_actualScore);
		//	m_pYourScore->m_Text = str;
		//}
	}

	//if (s_isShowingTutorial){

	//}

	if (CheckTouch())
		HandleTouch();
}

void Gameplay::ShowLine(Timer* pTimer, void* pUserData){
	Gameplay::s_pSelf->SlideLineIn();
}

void Gameplay::SlideLineIn(){

	//if (g_pSaveData->m_saveData.tutorial){

	//}




}


void Gameplay::CheckNextLevel(){

}

void Gameplay::Render(){
	Scene::Render();	
}


void Gameplay::HandleTouch(){
	Scene::HandleTouch();
	
	
}

void Gameplay::Pause(bool pause){
	
}