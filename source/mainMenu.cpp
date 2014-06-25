#include "include.h"

MainMenu::MainMenu()
{
	m_type = kScene_MainMenu;

}


MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
	Scene::Init();

}

void MainMenu::Cleanup()
{



	Scene::Cleanup();
}

void MainMenu::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;

    Scene::Update(deltaTime, alphaMul);

}

void MainMenu::Render()
{
    Scene::Render();
}
