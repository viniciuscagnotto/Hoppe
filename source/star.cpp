#include "include.h"

Star::Star()
{
	m_type = kGameObjectType_Star;
}

Star::~Star()
{
	Cleanup();
}

void Star::Init(float posX, float posY, float speedYRatio)
{
	GameObject::Init(ResourceManager::kResource_Entity_Star, posX, posY, 1.0f, 1.0f);
	m_speedYRatio = speedYRatio;
}

void Star::Cleanup()
{
	GameObject::Cleanup();

}

void Star::Update(float gameSpeed)
{
	if (m_destroyMe)
		return;

	GameObject::Update(gameSpeed);
}
