#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

class GameObject
{
public:
	enum EGameObjectType{
		kGameObjectType_Player = 0,
		kGameObjectType_Vortex,
		kGameObjectType_Asteroid, 
		kGameObjectType_Comet, 
		kGameObjectType_Satellite,
		kGameObjectType_BlackHole,
		kGameObjectType_Star,

		kGameObjectType_Count
	};

protected:
	EGameObjectType m_type;
	bool m_destroyMe;
	float m_speed;
	float m_maxSpeed;
	float m_speedYRatio;
	CNode *m_pParent;
	TriggersManager::ETriggerType m_triggerType;

	SpriteObject* m_pSprite1;
	SpriteObject* m_pSprite2;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Init(ResourceManager::EResources id, float posX, float posY, float scaleX = 1.0f, float scaleY = 1.0f);
	virtual void Cleanup();
	virtual void Update(float gameSpeed = 0.0f);
	virtual void Interact(GameObject *go) {};

	void AddTo(CNode *pScene);
	bool CheckHit(GameObject* gameObject);
	float GetDistanceX(GameObject* gameObject);

	void AddSpeed(float amount);
	void SetSpeed(float newSpeed){ m_speed = newSpeed; };
	void AddAlpha(float amount);
	void SetAlpha(float newAlpha);
	float GetAlpha(){ return (m_pSprite1 ? m_pSprite1->m_Alpha : 0.0f); };
	void SetVisible(bool visible);
	bool IsVisible(){ return m_pSprite1 ? m_pSprite1->m_IsVisible : false; };
	bool CanDestroyMe(){ return m_destroyMe; };

	SpriteObject* GetSprite1(){ return m_pSprite1; };
	SpriteObject* GetSprite2(){ return m_pSprite2; };
	EGameObjectType GetType(){ return m_type; };
};

#endif  // __GAME_OBJECT_H__

