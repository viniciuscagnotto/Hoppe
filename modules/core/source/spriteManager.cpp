#include "core.h"

SpriteManager* g_pSpriteManager = 0;

bool SpriteObject::IsInScene(){
	if (m_X + RealW() * 0.5f > 0 &&
		m_X - RealW() * 0.5f < IwGxGetScreenWidth() &&
		m_Y + RealH() * 0.5f > 0 &&
		m_Y - RealH() * 0.5f < IwGxGetScreenHeight())
		return true;

	return false;
}

SpriteObject* SpriteManager::CreateSpriteObject(uint resourceIndex)
{
	SpriteObject *pSpriteObject = new SpriteObject();
	pSpriteObject->m_X = 0;
	pSpriteObject->m_Y = 0;
	pSpriteObject->m_AnchorX = 0.5f;
	pSpriteObject->m_AnchorY = 0.5f;
	pSpriteObject->SetImage(g_pResourceManager->GetGraphic(resourceIndex));
	return pSpriteObject;
}

void SpriteManager::DeleteSpriteObject(SpriteObject *pSpriteObject)
{
	if (!pSpriteObject)
		return;

	pSpriteObject->SetImage(0);
	delete pSpriteObject;
	pSpriteObject = 0;
}

bool SpriteManager::Intersects(SpriteObject* pObject1, SpriteObject* pObject2){

	float obj1Left = pObject1->m_X - pObject1->RealW() * 0.5f;
	float obj1Right = pObject1->m_X + pObject1->RealW() * 0.5f;
	float obj1Up = pObject1->m_Y - pObject1->RealH() * 0.5f;
	float obj1Down = pObject1->m_Y + pObject1->RealH() * 0.5f;

	float obj2Left = pObject2->m_X - pObject2->RealW()* 0.5f;
	float obj2Right = pObject2->m_X + pObject2->RealW() * 0.5f;
	float obj2Up = pObject2->m_Y - pObject2->RealH() * 0.5f;
	float obj2Down = pObject2->m_Y + pObject2->RealH() * 0.5f;

	if (obj1Left > obj2Right || obj1Right < obj2Left ||
		obj1Up > obj2Down || obj1Down < obj2Up){
		return false;
	}

	return true;
}