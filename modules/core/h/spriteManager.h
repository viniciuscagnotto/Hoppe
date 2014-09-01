#ifndef __SPRITE_MANAGER_H__
#define __SPRITE_MANAGER_H__

class SpriteObject : public CSprite
{
public:
	static const uint s_kMaxAnimations = 16;

	struct SAnimation{
		CAtlas *animationAtlas;
		float duration;
		int repeat;

		SAnimation(){
			Cleanup();
		};

		void Cleanup(){
			animationAtlas = 0;
			duration = 1.0f;
			repeat = 1;
		};
	};

private:
	EasyArray<SAnimation, s_kMaxAnimations> m_animations;
	uint m_animationState;

public:
	SpriteObject();
	void Cleanup();
	bool IsInScene();

	void AddAnimation(uint animationState, uint atlasIndex, float duration = 1.0f, int repeat = 1);
	void RunAnimation(uint animationState);

	float RealW(){ return m_W * m_ScaleX; };
	float RealH(){ return m_H * m_ScaleY; };
};

class SpriteManager
{
public:
	SpriteObject* CreateSpriteObject();
	SpriteObject* CreateSpriteObject(uint resourceIndex);
	void DeleteSpriteObject(SpriteObject *pSpriteObject);
	bool Intersects(SpriteObject *pObject1, SpriteObject *pObject2);
};

extern SpriteManager* g_pSpriteManager;


#endif //__SPRITE_MANAGER_H__