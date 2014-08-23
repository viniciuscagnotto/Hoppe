#include "header.h"

IAP::IAP() : Scene(kScene_IAP)
{

}


IAP::~IAP()
{
	Cleanup();
}

void IAP::Init()
{
	Scene::Init();

}

void IAP::Cleanup()
{

	Scene::Cleanup();
}

void IAP::Update(float deltaTime, float alphaMul)
{
	if (!CheckCurrent())
		return;

	Scene::Update(deltaTime, alphaMul);

	if (CheckTouch())
		HandleTouch();

}

void IAP::Render()
{
	Scene::Render();

}

void IAP::HandleTouch()
{
	Scene::HandleTouch();
	SwitchTo(kScene_MainMenu);
}