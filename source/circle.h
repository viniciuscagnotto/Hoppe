#ifndef __CIRCLE_H__
#define __CIRCLE_H__

class Circle : public GameObject
{
public:
	

private:
	bool m_isActive;
	bool m_tapped;
	float m_speed;
	GameObject *m_pReceiver;

public:
	Circle(EGameObjectColor color);
	~Circle();

	void Init();
	void Cleanup();
	void Update();
	
	bool IsActive() { return m_isActive; };
	void SetIsActive(bool active){ m_isActive = active; SetVisible(active); };
	bool IsTapped() { return m_tapped; };
	void SetTapped(bool tapped) { m_tapped = tapped; };
	
	float GetSpeed(){ return m_speed; };
	void SetSpeed(float speed) {m_speed = speed; };

	GameObject *GetReceiver() { return m_pReceiver; };
	void SetReceiver(GameObject *pReceiver){ m_pReceiver = pReceiver; };
};

#endif  // __CIRCLE_H__


