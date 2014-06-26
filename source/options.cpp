#include "include.h"

Options::Options()
{
	m_type = kScene_Options;

}


Options::~Options()
{
	Cleanup();
}

void Options::Init()
{
	Scene::Init();

}

void Options::Cleanup()
{

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
	SwitchTo(kScene_MainMenu);
}