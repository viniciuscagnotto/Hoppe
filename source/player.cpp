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
	GameObject::Init(ResourceManager::kResource_Entity_Player, playerX, playerY);
	m_isAlive = true;
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
	if (!m_isAlive)
		return;

	switch (go->GetType()){
		case kGameObjectType_Vortex:
		{
			Vortex *pVortex = (Vortex *)go;
			if (CheckHit(go)){
				if (GetDistanceX(go) >= 0){
					if (m_speed > 0){
						SetSpeed(0.0f);
					}

					AddSpeed(-pVortex->GetForce());
				}
				else{
					if (m_speed < 0){
						SetSpeed(0.0f);
					}

					AddSpeed(pVortex->GetForce());
				}
			}
			break;
		}
		case kGameObjectType_Asteroid:
			if (CheckHit(go)){
				m_isAlive = false;
			}

			break;
		default:
			break;
	};
}