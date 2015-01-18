#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

class GameObject
{
public:
	enum EGameObjectType{
		kGameObjectType_Text = 0,
		kGameObjectType_Paint,
		
		kGameObjectType_Count
	};

	enum ETextType{
		kText_Filled = 0,
		kText_Stroke,

		kText_Count
	};

	enum EColor{
		kColor_Red = 0,
		kColor_Blue,
		kColor_Green,
		kColor_Yellow,
		kColor_Orange,
		kColor_Violet,
		kColor_Indigo,

		kColor_Count
	};

protected:
	EGameObjectType m_type;
	ETextType m_textType;
	EColor m_textColor;
	EColor m_color;

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
	void RemoveFromParent();
	bool CheckHit(GameObject* pGameObject);
	
	void AddAlpha(float amount);
	void SetAlpha(float newAlpha);
	float GetAlpha(){ return (m_pSprite ? m_pSprite->m_Alpha : 0.0f); };
	void SetVisible(bool visible);
	bool IsVisible(){ return m_pSprite ? m_pSprite->m_IsVisible : false; };
	bool CanDestroyMe(){ return m_destroyMe; };

	void SetScale(float scaleX, float scaleY);
	void SetPosition(float posX, float posY);
	float GetWidth(bool half = false);
	float GetHeight(bool half = false);

	void RunAnimation(uint animationState){ m_pSprite->RunAnimation(animationState); };
	SpriteObject* GetSprite(){ return m_pSprite; };

	EGameObjectType GetType(){ return m_type; };
	ETextType GetTextType(){ return m_textType; };
	EColor GetTextColor(){ return m_textColor; };
	EColor GetColor(){ return m_color; };
};

class SquareObject;

#endif  // __GAME_OBJECT_H__

