#include "header.h"

Gameplay::Gameplay() : Scene(kScene_Gameplay)
{
	
}

Gameplay::~Gameplay()
{
	Cleanup();
}

void Gameplay::Init()
{
	Scene::Init();

}

void Gameplay::Cleanup()
{
	
	Scene::Cleanup();
}

void Gameplay::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);
	
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
	SwitchTo(kScene_MainMenu);
}