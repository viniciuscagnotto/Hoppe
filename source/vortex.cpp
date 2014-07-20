#include "include.h"

Vortex::Vortex()
{

}

Vortex::~Vortex()
{
	Cleanup();
}

void Vortex::Init(float posX, float posY)
{
	GameObject::Init(ResourceManager::kResource_Entity_Vortex, posX, posY, 0.25f, 0.25f);
}

void Vortex::Cleanup()
{
	GameObject::Cleanup();

}

void Vortex::Update()
{
	GameObject::Update();

	if (GetAlpha() > 0){
		AddAlpha(-0.05f);
	}else{
		m_destroyMe = true;
	}
}
