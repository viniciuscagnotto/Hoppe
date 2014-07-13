#include "include.h"

GetStars::GetStars()
{
	m_type = kScene_GetStars;

}


GetStars::~GetStars()
{
	Cleanup();
}

void GetStars::Init()
{
	Scene::Init();

}

void GetStars::Cleanup()
{

	Scene::Cleanup();
}

void GetStars::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void GetStars::Render()
{
	Scene::Render();

}

void GetStars::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}