#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

class GameObject
{
public:
	enum EGameObjectType{
		kGameObjectType_Galinha = 0,
		
		kGameObjectType_Count
	};

protected:
	EGameObjectType m_type;
	bool m_destroyMe;
	CNode *m_pParent;
	SpriteObject* m_pSprite;

public:
	GameObject();
	GameObject(EGameObjectType gameObjectType);
	virtual ~GameObject();

	virtual void Init(float posX, float posY, float scaleX = 1.0f, float scaleY = 1.0f);
	virtual void Init(Game::EGameGraphics id, float posX, float posY, float scaleX = 1.0f, float scaleY = 1.0f);
	virtual void Cleanup();
	virtual void Update();
	virtual void Interact(GameObject *pGameObject) {};

	void AddTo(CNode *pScene);
	bool CheckHit(GameObject* pGameObject);
	
	void AddAlpha(float amount);
	void SetAlpha(float newAlpha);
	float GetAlpha(){ return (m_pSprite ? m_pSprite->m_Alpha : 0.0f); };
	void SetVisible(bool visible);
	bool IsVisible(){ return m_pSprite ? m_pSprite->m_IsVisible : false; };
	bool CanDestroyMe(){ return m_destroyMe; };

	void RunAnimation(uint animationState){ m_pSprite->RunAnimation(animationState); };
	SpriteObject* GetSprite(){ return m_pSprite; };
};

#endif  // __GAME_OBJECT_H__

