#include "template.h"

Store::Store()
{
	m_type = kScene_Store;

}


Store::~Store()
{
	Cleanup();
}

void Store::Init()
{
	Scene::Init();

}

void Store::Cleanup()
{

	Scene::Cleanup();
}

void Store::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void Store::Render()
{
	Scene::Render();

}

void Store::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}