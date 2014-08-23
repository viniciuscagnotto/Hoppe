#include "header.h"

Player::Player() :GameObject(kGameObjectType_Player)
{
	Init();
}

Player::~Player()
{
	Cleanup();
}

void Player::Init()
{
	float playerX = (float)IwGxGetScreenWidth() * 0.5f;
	float playerY = (float)IwGxGetScreenHeight() * 0.5f;
	GameObject::Init(Game::kGameGraphics_Entity_Player, playerX, playerY);
	m_isAlive = true;
}

void Player::Cleanup()
{
	GameObject::Cleanup();
	
}

void Player::Update()
{
	GameObject::Update();

	m_pSprite->m_X += 5.0f;

}
