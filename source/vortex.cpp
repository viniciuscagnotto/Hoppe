#include "include.h"

Vortex::Vortex() :m_alphaDeduction(0.0f),
m_force(0.0f)
{
	m_type = kGameObjectType_Vortex;
}

Vortex::~Vortex()
{
	Cleanup();
}

void Vortex::Init(float posX, float posY, float speedYRatio)
{
	GameObject::Init(ResourceManager::kResource_Entity_Vortex, posX, posY, 0.25f, 0.25f);
	m_speedYRatio = speedYRatio;
	m_alphaDeduction = 0.09f;
	m_force = 0.05f;
}

void Vortex::Cleanup()
{
	GameObject::Cleanup();

}

void Vortex::Update(float gameSpeed)
{
	if (m_destroyMe)
		return; 

	GameObject::Update(gameSpeed);

	if (GetAlpha() > 0){
		AddAlpha(-m_alphaDeduction);
	}else{
		SetVisible(false);
		m_destroyMe = true;
	}
}
