#ifndef __SQUARE_H__
#define __SQUARE_H__

//-SQUARE --------------------------------------------------------
class Square : public GameObject
{
public:


private:


public:
	Square(EGameObjectColor color);
	~Square();

	void Init();
	void Cleanup();
	void Update();
};

//-SQUARE OBJECT --------------------------------------------------------
class SquareObject{
public:
	
private:
	Square *m_pWhite;
	Square *m_pBlack;
	GameObject::EGameObjectColor m_front;
	bool m_isShooter;
	bool m_left;
	bool m_isSwitching;

	float m_frontPosX;
	float m_backPosX;

public:
	SquareObject(bool leftSide);
	~SquareObject();

	void Update();

	void AddTo(CNode *pParent);
	void RemoveFromParent();
	void SetIsShooter(bool shooter) { m_isShooter = shooter; };
	bool IsShooter() {return m_isShooter; };

	void SetScale(float scaleX, float scaleY);
	void SetPosition(float posX, float posY);
	float GetWidth(bool half = false);
	float GetHeight(bool half = false);

	void SetInitialParams();
	void Switch();

	void onFrontRetreat(CTween* pTween);
	void onBackAdvance(CTween* pTween);

};



#endif  // __SQUARE_H__

