#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#define kCircle_Active (1<<0)
#define kCircle_Tapped (1<<1)
#define kCircle_Exploding (1<<2)

class Circle : public GameObject
{
public:
	

private:
	int state;
	float m_speed;
	SquareObject *m_pReceiver;

public:
	Circle(EGameObjectColor color);
	~Circle();

	void Init();
	void Cleanup();
	void Update();
	
	bool IsActive() { return L_GetBitState(state, kCircle_Active); };
	void SetIsActive(bool active){ L_SetBitState(&state, kCircle_Active, active); SetVisible(active); };
	bool IsTapped() { return L_GetBitState(state, kCircle_Tapped); };
	void SetTapped(bool tapped) { L_SetBitState(&state, kCircle_Tapped, tapped); };
	bool IsExploding() { return L_GetBitState(state, kCircle_Exploding); };
	void SetExploding(bool exploding) { L_SetBitState(&state, kCircle_Exploding, exploding); };

	void Reset(){ SetVisible(false); state = 0; m_speed = 0.0f; SetAlpha(1.0f); }; 
	
	float GetSpeed(){ return m_speed; };
	void SetSpeed(float speed) {m_speed = speed; };

	SquareObject *GetReceiver() { return m_pReceiver; };
	void SetReceiver(SquareObject *pReceiver){ m_pReceiver = pReceiver; };
};

#endif  // __CIRCLE_H__

