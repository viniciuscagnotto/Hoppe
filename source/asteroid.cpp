#include "include.h"

Asteroid::Asteroid()
{
	m_type = kGameObjectType_Asteroid;
}

Asteroid::~Asteroid()
{
	Cleanup();
}

void Asteroid::Init(float posX, float posY, float speedYRatio)
{
	GameObject::Init(ResourceManager::kResource_Entity_Asteroid, posX, posY, 1.0f, 1.0f);
	m_speedYRatio = speedYRatio;
}

void Asteroid::Cleanup()
{
	GameObject::Cleanup();

}

void Asteroid::Update(float gameSpeed)
{
	if (m_destroyMe)
		return;

	GameObject::Update(gameSpeed);
}
