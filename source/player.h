#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player : public GameObject
{
public:


private:
	bool m_isAlive;

public:
	Player();
	~Player();

	void Init();
	void Cleanup();
	void Update();

	bool IsAlive(){ return m_isAlive; };
};

#endif  // __PLAYER_H__

