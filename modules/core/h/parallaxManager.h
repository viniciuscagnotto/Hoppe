#ifndef __PARALLAX_MANAGER_H__
#define __PARALLAX_MANAGER_H__

class ParallaxManager
{
private:
	CSprite *m_pContainer;
	SpriteObject *m_pSprite1;
	SpriteObject *m_pSprite2;
	SpriteObject *m_pSprite3;

	float m_speedRatio;
	bool m_isInitiated;
public:
	ParallaxManager();

	void Create(ResourceManager::EResources id, float speedRatio);
	void Update(float gameSpeed);
	void Reset();
	void Destroy();

	CSprite *GetContainer(){ return m_pContainer; };
};

#endif //__PARALLAX_MANAGER_H__