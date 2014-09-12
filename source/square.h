#ifndef __SQUARE_H__
#define __SQUARE_H__

//-SQUARE --------------------------------------------------------
class Square : public GameObject
{
public:
	static const uint s_kMaxCircles = 8;

private:
	EasyArray<Circle*, s_kMaxCircles> m_circles;
	float m_circleInitialPos;
	
public:
	Square(EGameObjectColor color);
	~Square();

	void Init();
	void Cleanup();
	void Update(float deltaTime);

	void SetReceiver(SquareObject *pReceiver);
	void AddCirclesTo(CNode *pContainer, float posX);
	void RemoveCirclesFromParent();

	void Shoot(float speed);
	void CheckTap(float x, float y);
	bool HasIncomingCircle(bool isLeft);

	void EndGame();
	static void OnGameOver(CTween *pTween);
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

	float m_switchSpeed;
	float m_shootSpeed;

public:
	SquareObject(bool leftSide);
	~SquareObject();

	void Update(float deltaTime);
	
	void SetReceiver(SquareObject *pReceiver);
	void AddTo(CNode *pParent);
	void RemoveFromParent();
	void SetIsShooter(bool shooter) { m_isShooter = shooter; };
	bool IsShooter() {return m_isShooter; };
	bool IsLeft(){ return m_left; };
	bool IsSwitching() { return m_isSwitching; };
	void SetToSwitch() { m_isSwitching = true; g_pAudio->PlaySound("audio/switch.wav"); };

	void SetScale(float scaleX, float scaleY);
	void SetPosition(float posX, float posY);
	float GetWidth(bool half = false);
	float GetHeight(bool half = false);

	void SetInitialParams();
	void SetupCircles(CNode *pContainer);
	
	void Switch();
	void Shoot(float speed);
	Square *GetFrontSquare();
	GameObject::EGameObjectColor GetFront() { return m_front; };
	void SwitchFront();
	bool CanSwitch(SquareObject *pShooter);

	void CheckTap(float x, float y);
};



#endif  // __SQUARE_H__

