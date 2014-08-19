#include "template.h"

Items::Items()
{
	m_type = kScene_Items;

}


Items::~Items()
{
	Cleanup();
}

void Items::Init()
{
	Scene::Init();

}

void Items::Cleanup()
{

	Scene::Cleanup();
}

void Items::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void Items::Render()
{
	Scene::Render();

}

void Items::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}