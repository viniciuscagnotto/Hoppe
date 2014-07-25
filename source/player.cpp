#include "include.h"

Player::Player()
{
	m_type = kGameObjectType_Player;
	Init();
}

Player::~Player()
{
	Cleanup();
}

void Player::Init()
{
	float playerX = IwGxGetScreenWidth() * 0.5f;
	float playerY = IwGxGetScreenHeight() * 0.8f;
	GameObject::Init(ResourceManager::kResource_Entity_Player, playerX, playerY, 0.5f, 0.5f);
}

void Player::Cleanup()
{
	GameObject::Cleanup();
	
}

void Player::Update()
{
	GameObject::Update();
}

void Player::Interact(GameObject *go){
	switch (go->GetType()){
		case kGameObjectType_Vortex:
		{
			if(CheckHit(go)){
				if (GetDistanceX(go) >= 0){
					SetSpeed(-3.0f);
				}else{
					SetSpeed(3.0f);
				}
			}
			break;
		}
		case kGameObjectType_Asteroid:
		{

			break;
		}
		default:
			break;
	};
}