#if !defined(__SPRITE_MANAGER_H__)
#define __SPRITE_MANAGER_H__

class SpriteManager;

class SpriteObject : public CSprite
{
public:
	CIw2DImage* m_pTexture;

	SpriteObject() : m_pTexture(0){};
};

class SpriteManager
{
public:
	SpriteObject* CreateSpriteObject(const char* filename);
	void DeleteSpriteObject(SpriteObject *pSpriteObject);
};

extern SpriteManager* g_pSpriteManager;


#endif //__SPRITE_MANAGER_H__