#include "include.h"

Comet::Comet()
{
	m_type = kGameObjectType_Comet;
}

Comet::~Comet()
{
	Cleanup();
}

void Comet::Init(float posX, float posY, float speedYRatio)
{
	GameObject::Init(ResourceManager::kResource_Entity_Comet, posX, posY, 1.0f, 1.0f);
	m_speedYRatio = speedYRatio;
}

void Comet::Cleanup()
{
	GameObject::Cleanup();

}

void Comet::Update(float gameSpeed)
{
	if (m_destroyMe)
		return;

	GameObject::Update(gameSpeed);
}
