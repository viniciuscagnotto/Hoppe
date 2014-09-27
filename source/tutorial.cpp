#include "header.h"

Tutorial::Tutorial() : Scene(kScene_Tutorial),
m_pTutorial(0)
{

}


Tutorial::~Tutorial()
{
	Cleanup();
}

void Tutorial::Init()
{
	Scene::Init();

	if (g_pAdsManager->IsEnabled())
		g_pAdsManager->NewAd();

	//Tutorial Button
	/*m_pTutorial = g_pSpriteManager->CreateSpriteObject(Game::kGameGraphics_Tutorial_Main);
	m_pTutorial->m_X = IwGxGetScreenWidth() * 0.5f;
	m_pTutorial->m_Y = IwGxGetScreenHeight() * 0.5f;
	AddChild(m_pTutorial);
	*/
}

void Tutorial::Cleanup()
{

	//SafeDeleteObject(m_pTutorial);
	//m_pTutorial = 0;

	Scene::Cleanup();
}

void Tutorial::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void Tutorial::Render()
{
	Scene::Render();

}

void Tutorial::HandleTouch()
{
	Scene::HandleTouch();
	g_pAudio->PlaySound("audio/click.wav");
	Gameplay::ResetVariables();
	SwitchTo(kScene_Gameplay);
}