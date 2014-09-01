#include "header.h"

Galinha::Galinha() :GameObject(kGameObjectType_Galinha)
{
	Init();
}

Galinha::~Galinha()
{
	Cleanup();
}

void Galinha::Init()
{
	float playerX = (float)IwGxGetScreenWidth() * 0.8f;
	float playerY = (float)IwGxGetScreenHeight() * 0.2f;
	GameObject::Init(playerX, playerY);

	m_pSprite->AddAnimation(kAnimationStates_Run, Game::kGameAtlases_Galinha_Run, 0.4f, 99);
	m_pSprite->AddAnimation(kAnimationStates_Run_Catarro, Game::kGameAtlases_Galinha_Run_Catarro, 0.4f, 99);
	m_pSprite->AddAnimation(kAnimationStates_Damage, Game::kGameAtlases_Galinha_Damage, 0.4f, 99);
	m_pSprite->AddAnimation(kAnimationStates_Apaixonada, Game::kGameAtlases_Galinha_Apaixonada, 0.4f, 99);
	RunAnimation(kAnimationStates_Run);
}

void Galinha::Cleanup()
{
	GameObject::Cleanup();

}

void Galinha::Update()
{
	GameObject::Update();

}
