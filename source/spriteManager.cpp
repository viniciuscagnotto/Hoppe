#include "include.h"

SpriteManager* g_pSpriteManager = 0;

SpriteObject* SpriteManager::CreateSpriteObject(const char* filename)
{
	SpriteObject *pSpriteObject = new SpriteObject();
	pSpriteObject->m_X = 0;
	pSpriteObject->m_Y = 0;
	pSpriteObject->m_AnchorX = 0.5f;
	pSpriteObject->m_AnchorY = 0.5f;
	pSpriteObject->m_pTexture = Iw2DCreateImage(filename);
	pSpriteObject->SetImage(pSpriteObject->m_pTexture);
	return pSpriteObject;
}

void SpriteManager::DeleteSpriteObject(SpriteObject *pSpriteObject)
{
	if (!pSpriteObject)
		return;

	if (pSpriteObject->m_pTexture)
		delete pSpriteObject->m_pTexture;
	
	delete pSpriteObject;
	pSpriteObject = 0;
}