#include "include.h"

BlackHole::BlackHole()
{
	m_type = kGameObjectType_BlackHole;
}

BlackHole::~BlackHole()
{
	Cleanup();
}

void BlackHole::Init(float posX, float posY, float speedYRatio)
{
	GameObject::Init(ResourceManager::kResource_Entity_BlackHole, posX, posY, 1.0f, 1.0f);
	m_speedYRatio = speedYRatio;
}

void BlackHole::Cleanup()
{
	GameObject::Cleanup();

}

void BlackHole::Update(float gameSpeed)
{
	if (m_destroyMe)
		return;

	GameObject::Update(gameSpeed);
}
