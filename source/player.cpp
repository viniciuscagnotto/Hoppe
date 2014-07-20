#include "include.h"

Player::Player()
{

}

Player::~Player()
{
	Cleanup();
}

void Player::Init()
{
	float playerX = IwGxGetScreenWidth() * 0.5f;
	float playerY = IwGxGetScreenHeight() * 0.8f;
	GameObject::Init(ResourceManager::kResource_Entity_Player, playerX, playerY, 0.5f, 0.7f);
}

void Player::Cleanup()
{
	GameObject::Cleanup();
	
}

void Player::Update()
{
	GameObject::Update();

}
