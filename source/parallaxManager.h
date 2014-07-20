#if !defined(__PARALLAX_MANAGER_H__)
#define __PARALLAX_MANAGER_H__

class ParallaxManager
{
private:
	CSprite *m_pContainer;
	SpriteObject *m_pSprite1;
	SpriteObject *m_pSprite2;
	SpriteObject *m_pSprite3;

	float m_startingSpeed;
	float m_speed;
	bool m_isInitiated;
public:
	ParallaxManager();

	void Create(ResourceManager::EResources id, float startingSpeed);
	void Update();
	void Reset();
	void Destroy();

	CSprite *GetContainer(){ return m_pContainer; };
	void SetSpeed(float newSpeed) { m_speed = newSpeed; };
	void IncrementSpeed(float addSpeed) { m_speed += addSpeed;  };
};

#endif //__PARALLAX_MANAGER_H__