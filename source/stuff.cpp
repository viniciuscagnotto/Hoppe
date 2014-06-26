#include "include.h"

Stuff::Stuff()
{
	m_type = kScene_Stuff;

}


Stuff::~Stuff()
{
	Cleanup();
}

void Stuff::Init()
{
	Scene::Init();

}

void Stuff::Cleanup()
{

	Scene::Cleanup();
}

void Stuff::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void Stuff::Render()
{
	Scene::Render();

}

void Stuff::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}