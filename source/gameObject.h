#if !defined(__GAME_OBJECT_H__)
#define __GAME_OBJECT_H__

class GameObject
{
protected:
	bool m_destroyMe;
	float m_speed;
	Scene *m_pParent;

	SpriteObject* m_pSprite1;
	SpriteObject* m_pSprite2;

public:
	GameObject();
	~GameObject();

	void Init(ResourceManager::EResources id, float posX, float posY, float scaleX, float scaleY);
	void Cleanup();
	void Update();

	void AddTo(Scene *pScene);
	bool CheckHit(GameObject* gameObject);
	float GetDistanceX(GameObject* gameObject);

	void AddSpeed(float amount){ m_speed += amount; };
	void SetSpeed(float newSpeed){ m_speed = newSpeed; };
	void ChangeAlpha(float amount);
	float GetAlpha(){ return (m_pSprite1 ? m_pSprite1->m_Alpha : 0.0f); };
	bool CanDestroyMe(){ return m_destroyMe; };

	SpriteObject* GetSprite1(){ return m_pSprite1; };
	SpriteObject* GetSprite2(){ return m_pSprite2; };
};

#endif  // __GAME_OBJECT_H__

