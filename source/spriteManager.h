#if !defined(__SPRITE_MANAGER_H__)
#define __SPRITE_MANAGER_H__

class SpriteObject : public CSprite
{
public:
	CIw2DImage* m_pTexture;

	SpriteObject() : m_pTexture(0){};
	bool IsInScene();
	float RealW(){ return m_W * m_ScaleX; };
	float RealH(){ return m_H * m_ScaleY; };
};

class SpriteManager
{
public:
	SpriteObject* CreateSpriteObject(ResourceManager::EResources id);
	void DeleteSpriteObject(SpriteObject *pSpriteObject);
	bool Intersects(SpriteObject *pObject1, SpriteObject *pObject2);
};

extern SpriteManager* g_pSpriteManager;


#endif //__SPRITE_MANAGER_H__