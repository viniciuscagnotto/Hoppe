#include "template.h"

Customize::Customize()
{
	m_type = kScene_Customize;

}


Customize::~Customize()
{
	Cleanup();
}

void Customize::Init()
{
	Scene::Init();

}

void Customize::Cleanup()
{

	Scene::Cleanup();
}

void Customize::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void Customize::Render()
{
	Scene::Render();

}

void Customize::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}