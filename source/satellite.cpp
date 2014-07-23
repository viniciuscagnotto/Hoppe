#include "include.h"

Satellite::Satellite()
{
	m_type = kGameObjectType_Satellite;
}

Satellite::~Satellite()
{
	Cleanup();
}

void Satellite::Init(float posX, float posY, float speedYRatio)
{
	GameObject::Init(ResourceManager::kResource_Entity_Satellite, posX, posY, 1.0f, 1.0f);
	m_speedYRatio = speedYRatio;
}

void Satellite::Cleanup()
{
	GameObject::Cleanup();

}

void Satellite::Update(float gameSpeed)
{
	if (m_destroyMe)
		return;

	GameObject::Update(gameSpeed);
}
