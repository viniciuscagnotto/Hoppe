#include "include.h"

Asteroid::Asteroid()
{
	m_type = kGameObjectType_Asteroid;
}

Asteroid::~Asteroid()
{
	Cleanup();
}

void Asteroid::Init(TriggersManager::ETriggerType triggerType, float posX, float posY, float speedYRatio)
{
	ResourceManager::EResources resource = ResourceManager::kResource_Entity_Asteroid_Small;
	if (triggerType == TriggersManager::kTriggerType_Asteroid_Big ||
		triggerType == TriggersManager::kTriggerType_Asteroid_Big_Shower ||
		triggerType == TriggersManager::kTriggerType_Asteroid_Big_Wall){
		resource = ResourceManager::kResource_Entity_Asteroid_Big;
	}

	GameObject::Init(resource, posX, posY, 1.0f, 1.0f);
	m_speedYRatio = speedYRatio;
	m_triggerType = triggerType;
	m_speed = RandomFloat(-3.0f, 3.0f);

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
